/* SSL support.
   Copyright (C) 2000 Free Software Foundation, Inc.
   Contributed by Christian Fraenkel.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#include <config.h>

#ifdef HAVE_SSL

#include <assert.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif

#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

#include "wget.h"
#include "utils.h"
#include "connect.h"
#include "url.h"

#ifndef errno
extern int errno;
#endif

void
ssl_init_prng (void)
{
  /* It is likely that older versions of OpenSSL will fail on
     non-Linux machines because this code is unable to seed the PRNG
     on older versions of the library.  */

#if SSLEAY_VERSION_NUMBER >= 0x00905100
  char rand_file[256];
  int maxrand = 500;

  /* First, seed from a file specified by the user.  This will be
     $RANDFILE, if set, or ~/.rnd.  */
  RAND_file_name (rand_file, sizeof (rand_file));
  if (rand_file)
    /* Seed at most 16k (value borrowed from curl) from random file. */
    RAND_load_file (rand_file, 16384);

  if (RAND_status ())
    return;

  /* Get random data from EGD if opt.sslegdsock was set.  */
  if (opt.sslegdsock && *opt.sslegdsock)
    RAND_egd (opt.sslegdsock);

  if (RAND_status ())
    return;

#ifdef WINDOWS
  /* Under Windows, we can try to seed the PRNG using screen content.
     This may or may not work, depending on whether we'll calling Wget
     interactively.  */

  RAND_screen ();
  if (RAND_status ())
    return;
#endif

  /* Still not enough randomness, presumably because neither random
     file nor EGD have been available.  Use the stupidest possible
     method -- seed OpenSSL's PRNG with the system's PRNG.  This is
     insecure in the cryptographic sense, but people who care about
     security will use /dev/random or their own source of randomness
     anyway.  */

  while (RAND_status () == 0 && maxrand-- > 0)
    {
      unsigned char rnd = random_number (256);
      RAND_seed (&rnd, sizeof (rnd));
    }

  if (RAND_status () == 0)
    {
      logprintf (LOG_NOTQUIET,
		 _("Could not seed OpenSSL PRNG; disabling SSL.\n"));
      scheme_disable (SCHEME_HTTPS);
    }
#endif /* SSLEAY_VERSION_NUMBER >= 0x00905100 */
}

int
verify_callback (int ok, X509_STORE_CTX *ctx)
{
  char *s, buf[256];
  s = X509_NAME_oneline (X509_get_subject_name (ctx->current_cert), buf, 256);
  if (ok == 0) {
    switch (ctx->error) {
    case X509_V_ERR_CERT_NOT_YET_VALID:
    case X509_V_ERR_CERT_HAS_EXPIRED:
      /* This mean the CERT is not valid !!! */
      ok = 0;
      break;
    case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
      /* Unsure if we should handle that this way */
      ok = 1;
      break;
    }
  }
  return ok;
}

/* pass all ssl errors to DEBUGP
   returns the number of printed errors */
int
ssl_printerrors (void) 
{
  int ocerr = 0;
  unsigned long curerr = 0;
  char errbuff[1024];
  memset(errbuff, 0, sizeof(errbuff));
  while ( 0 != (curerr = ERR_get_error ()))
    {
      DEBUGP (("OpenSSL: %s\n", ERR_error_string (curerr, errbuff)));
      ++ocerr;
    }
  return ocerr;
}

/* Creates a SSL Context and sets some defaults for it */
uerr_t
init_ssl (SSL_CTX **ctx)
{
  SSL_METHOD *meth = NULL;
  int verify;
  int can_validate;
  SSL_library_init ();
  SSL_load_error_strings ();
  SSLeay_add_all_algorithms ();
  SSLeay_add_ssl_algorithms ();
  switch (opt.sslprotocol)
    {
      default:
	meth = SSLv23_client_method ();
	break;
      case 1 :
	meth = SSLv2_client_method ();
	break;
      case 2 :
	meth = SSLv3_client_method ();
	break;
      case 3 :
	meth = TLSv1_client_method ();
	break;
    }
  if (meth == NULL)
    {
      ssl_printerrors ();
      return SSLERRCTXCREATE;
    }

  *ctx = SSL_CTX_new (meth);
  if (meth == NULL)
    {
      ssl_printerrors ();
      return SSLERRCTXCREATE;
    }
  /* Can we validate the server Cert ? */
  if (opt.sslcadir != NULL || opt.sslcafile != NULL)
    {
      SSL_CTX_load_verify_locations (*ctx, opt.sslcafile, opt.sslcadir);
      can_validate = 1;
    }
  else
    {
      can_validate = 0;
    }

  if (!opt.sslcheckcert)
    {
      /* check cert but ignore error, do not break handshake on error */
      verify = SSL_VERIFY_NONE;
    }
  else
    {
      if (!can_validate)
	{
	  logprintf (LOG_NOTQUIET, "Warrining validation of Server Cert not possible!\n");
	  verify = SSL_VERIFY_NONE;
	}
     else
	{
	  /* break handshake if server cert is not valid but allow NO-Cert mode */
	  verify = SSL_VERIFY_PEER;
	}
    }

  SSL_CTX_set_verify (*ctx, verify, verify_callback);

  if (opt.sslcertfile != NULL || opt.sslcertkey != NULL)
    {
      int ssl_cert_type;
      if (!opt.sslcerttype)
	ssl_cert_type = SSL_FILETYPE_PEM;
      else
	ssl_cert_type = SSL_FILETYPE_ASN1;

      if (opt.sslcertkey == NULL) 
	opt.sslcertkey = opt.sslcertfile;
      if (opt.sslcertfile == NULL)
	opt.sslcertfile = opt.sslcertkey; 

      if (SSL_CTX_use_certificate_file (*ctx, opt.sslcertfile, ssl_cert_type) <= 0)
	{
	  ssl_printerrors ();
  	  return SSLERRCERTFILE;
	}
      if (SSL_CTX_use_PrivateKey_file  (*ctx, opt.sslcertkey , ssl_cert_type) <= 0)
	{
	  ssl_printerrors ();
	  return SSLERRCERTKEY;
	}
    }

  return 0; /* Succeded */
}

void
shutdown_ssl (SSL* con)
{
  if (con == NULL)
    return;
  if (0==SSL_shutdown (con))
    SSL_shutdown (con);
  SSL_free (con);
}

/* Sets up a SSL structure and performs the handshake on fd 
   Returns 0 if everything went right
   Returns 1 if something went wrong ----- TODO: More exit codes
*/
int
connect_ssl (SSL **con, SSL_CTX *ctx, int fd) 
{
  if (NULL == (*con = SSL_new (ctx)))
    {
      ssl_printerrors ();
      return 1;
    }
  if (!SSL_set_fd (*con, fd))
    {
      ssl_printerrors ();
      return 1;
    }
  SSL_set_connect_state (*con);
  switch (SSL_connect (*con))
    {
      case 1 : 
	return (*con)->state != SSL_ST_OK;
      default:
        ssl_printerrors ();
	shutdown_ssl (*con);
	*con = NULL;
	return 1;
      case 0 :
        ssl_printerrors ();
	SSL_free (*con);
       	*con = NULL;
 	return 1;
    }
  return 0;
}

void
free_ssl_ctx (SSL_CTX * ctx)
{
  SSL_CTX_free (ctx);
}

/* SSL version of iread.  Only exchanged read for SSL_read Read at
   most LEN bytes from FD, storing them to BUF. */

int
ssl_iread (SSL *con, char *buf, int len)
{
  int res, fd;
  BIO_get_fd (con->rbio, &fd);
#ifdef HAVE_SELECT
  if (opt.read_timeout && !SSL_pending (con))
    if (select_fd (fd, opt.read_timeout, 0) <= 0)
      return -1;
#endif
  do
    res = SSL_read (con, buf, len);
  while (res == -1 && errno == EINTR);

  return res;
}

/* SSL version of iwrite.  Only exchanged write for SSL_write Write
   LEN bytes from BUF to FD.  */

int
ssl_iwrite (SSL *con, char *buf, int len)
{
  int res = 0, fd;
  BIO_get_fd (con->rbio, &fd);
  /* `write' may write less than LEN bytes, thus the outward loop
     keeps trying it until all was written, or an error occurred.  The
     inner loop is reserved for the usual EINTR f*kage, and the
     innermost loop deals with the same during select().  */
  while (len > 0)
    {
#ifdef HAVE_SELECT
      if (opt.read_timeout)
	if (select_fd (fd, opt.read_timeout, 1) <= 0)
	  return -1;
#endif
      do
	res = SSL_write (con, buf, len);
      while (res == -1 && errno == EINTR);
      if (res <= 0)
	break;
      buf += res;
      len -= res;
    }
  return res;
}
#endif /* HAVE_SSL */
