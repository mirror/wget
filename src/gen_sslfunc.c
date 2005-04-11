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
#include "gen_sslfunc.h"

#ifndef errno
extern int errno;
#endif

SSL_CTX *ssl_ctx;

static void
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

  /* Still not enough randomness, most likely because neither
     /dev/random nor EGD were available.  Resort to a simple and
     stupid method -- seed OpenSSL's PRNG with libc PRNG.  This is
     cryptographically weak, but people who care about strong
     cryptography should install /dev/random (default on Linux) or
     specify their own source of randomness anyway.  */

  logprintf (LOG_VERBOSE, _("Warning: using a weak random seed.\n"));

  while (RAND_status () == 0 && maxrand-- > 0)
    {
      unsigned char rnd = random_number (256);
      RAND_seed (&rnd, sizeof (rnd));
    }
#endif /* SSLEAY_VERSION_NUMBER >= 0x00905100 */
}

static int
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

/* Print SSL errors. */

static void
ssl_print_errors (void) 
{
  unsigned long curerr = 0;
  while ((curerr = ERR_get_error ()) != 0)
    logprintf (LOG_NOTQUIET, "OpenSSL: %s\n", ERR_error_string (curerr, NULL));
}

/* Creates a SSL Context and sets some defaults for it */
uerr_t
ssl_init ()
{
  SSL_METHOD *meth = NULL;
  int verify;
  int can_validate;

  if (ssl_ctx)
    return 0;

  /* Init the PRNG.  If that fails, bail out.  */
  ssl_init_prng ();
  if (RAND_status () == 0)
    {
      logprintf (LOG_NOTQUIET,
		 _("Could not seed OpenSSL PRNG; disabling SSL.\n"));
      scheme_disable (SCHEME_HTTPS);
      return SSLERRCTXCREATE;
    }

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
      ssl_print_errors ();
      return SSLERRCTXCREATE;
    }

  ssl_ctx = SSL_CTX_new (meth);
  if (meth == NULL)
    {
      ssl_print_errors ();
      return SSLERRCTXCREATE;
    }
  /* Can we validate the server Cert ? */
  if (opt.sslcadir != NULL || opt.sslcafile != NULL)
    {
      SSL_CTX_load_verify_locations (ssl_ctx, opt.sslcafile, opt.sslcadir);
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

  SSL_CTX_set_verify (ssl_ctx, verify, verify_callback);

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

      if (SSL_CTX_use_certificate_file (ssl_ctx, opt.sslcertfile,
					ssl_cert_type) <= 0)
	{
	  ssl_print_errors ();
  	  return SSLERRCERTFILE;
	}
      if (SSL_CTX_use_PrivateKey_file  (ssl_ctx, opt.sslcertkey,
					ssl_cert_type) <= 0)
	{
	  ssl_print_errors ();
	  return SSLERRCERTKEY;
	}
    }

  return 0; /* Succeded */
}

static int
ssl_read (int fd, char *buf, int bufsize, void *ctx)
{
  int ret;
  SSL *ssl = (SSL *) ctx;
  do
    ret = SSL_read (ssl, buf, bufsize);
  while (ret == -1
	 && SSL_get_error (ssl, ret) == SSL_ERROR_SYSCALL
	 && errno == EINTR);
  return ret;
}

static int
ssl_write (int fd, char *buf, int bufsize, void *ctx)
{
  int ret = 0;
  SSL *ssl = (SSL *) ctx;
  do
    ret = SSL_write (ssl, buf, bufsize);
  while (ret == -1
	 && SSL_get_error (ssl, ret) == SSL_ERROR_SYSCALL
	 && errno == EINTR);
  return ret;
}

static int
ssl_poll (int fd, double timeout, int wait_for, void *ctx)
{
  SSL *ssl = (SSL *) ctx;
  if (timeout == 0)
    return 1;
  if (SSL_pending (ssl))
    return 1;
  return select_fd (fd, timeout, wait_for);
}

static int
ssl_peek (int fd, char *buf, int bufsize, void *ctx)
{
  int ret;
  SSL *ssl = (SSL *) ctx;
  do
    ret = SSL_peek (ssl, buf, bufsize);
  while (ret == -1
	 && SSL_get_error (ssl, ret) == SSL_ERROR_SYSCALL
	 && errno == EINTR);
  return ret;
}

static void
ssl_close (int fd, void *ctx)
{
  SSL *ssl = (SSL *) ctx;
  SSL_shutdown (ssl);
  SSL_free (ssl);

#ifdef WINDOWS
  closesocket (fd);
#else
  close (fd);
#endif

  DEBUGP (("Closed %d/SSL 0x%0lx\n", fd, (unsigned long) ssl));
}

/* Sets up a SSL structure and performs the handshake on fd.  The
   resulting SSL structure is registered with the file descriptor FD
   using fd_register_transport.  That way subsequent calls to xread,
   xwrite, etc., will use the appropriate SSL functions.

   Returns 1 on success, 0 on failure.  */

int
ssl_connect (int fd) 
{
  SSL *ssl;

  assert (ssl_ctx != NULL);
  ssl = SSL_new (ssl_ctx);
  if (!ssl)
    goto err;
  if (!SSL_set_fd (ssl, fd))
    goto err;
  SSL_set_connect_state (ssl);
  if (SSL_connect (ssl) <= 0 || ssl->state != SSL_ST_OK)
    goto err;

  /* Register FD with Wget's transport layer, i.e. arrange that
     SSL-enabled functions are used for reading, writing, and polling.
     That way the rest of Wget can keep using xread, xwrite, and
     friends and not care what happens underneath.  */
  fd_register_transport (fd, ssl_read, ssl_write, ssl_poll, ssl_peek,
			 ssl_close, ssl);
  DEBUGP (("Connected %d to SSL 0x%0*lx\n", fd, 2 * sizeof (void *),
	   (unsigned long) ssl));
  return 1;

 err:
  ssl_print_errors ();
  if (ssl)
    SSL_free (ssl);
  return 0;
}
