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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#ifdef HAVE_SSL

#include <assert.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

#include "wget.h"
#include "connect.h"

#ifndef errno
extern int errno;
#endif

static int verify_callback PARAMS ((int, X509_STORE_CTX *));

static void
ssl_init_prng (void)
{
#if SSLEAY_VERSION_NUMBER >= 0x00905100
  if (RAND_status () == 0)
    {
      char rand_file[256];
      time_t t;
      long l,seed;

      t = time(NULL);
      /* gets random data from egd if opt.sslegdsock was set */
      if (opt.sslegdsock != NULL)
	RAND_egd(opt.sslegdsock);
      /* gets the file ~/.rnd or $RANDFILE if set */
      RAND_file_name(rand_file, 256);
      if (rand_file != NULL)
	{
	  /* Seed as much as 1024 bytes from RAND_file_name */
	  RAND_load_file(rand_file, 1024);
	}
      /* Seed in time (mod_ssl does this) */
      RAND_seed((unsigned char *)&t, sizeof(time_t));
      /* Initialize system's random number generator */
      RAND_bytes((unsigned char *)&seed, sizeof(long));
#ifndef WINDOWS
      srand48(seed);
      while (RAND_status () == 0)
	{
	  /* Repeatedly seed the PRNG using the system's random number
	     generator until it has been seeded with enough data.  */
	  l = lrand48();
	  RAND_seed((unsigned char *)&l, sizeof(long));
	}
#else /* WINDOWS */
      RAND_screen();
      if (RAND_status() == 0)
        /* Here we should probably disable the whole ssl protocol ? HEH */
        DEBUGP (("SSL random data generator not seeded correctly, %i",RAND_status()));
#endif /* WINDOWS */
      if (rand_file != NULL)
	{
	  /* Write a rand_file */
	  RAND_write_file(rand_file);
	}
    }
#endif /* SSLEAY_VERSION_NUMBER >= 0x00905100 */
  return;
}


/* Creates a SSL Context and sets some defaults for it */
uerr_t
init_ssl (SSL_CTX **ctx)
{
  SSL_METHOD *meth = NULL;
  int verify = SSL_VERIFY_NONE;
  SSL_library_init ();
  SSL_load_error_strings ();
  SSLeay_add_all_algorithms ();
  SSLeay_add_ssl_algorithms ();
  meth = SSLv23_client_method ();
  *ctx = SSL_CTX_new (meth);
  SSL_CTX_set_verify (*ctx, verify, verify_callback);
  if (*ctx == NULL) return SSLERRCTXCREATE;
  if (opt.sslcertfile)
    {
      if (SSL_CTX_use_certificate_file (*ctx, opt.sslcertfile,
					SSL_FILETYPE_PEM) <= 0)
	return SSLERRCERTFILE;
      if (opt.sslcertkey == NULL) 
	opt.sslcertkey=opt.sslcertfile;
      if (SSL_CTX_use_PrivateKey_file (*ctx, opt.sslcertkey,
				       SSL_FILETYPE_PEM) <= 0)
	return SSLERRCERTKEY;
  }
  ssl_init_prng();
  return 0; /* Succeded */
}

/* Sets up a SSL structure and performs the handshake on fd 
   Returns 0 if everything went right
   Returns 1 if something went wrong ----- TODO: More exit codes
*/
int
connect_ssl (SSL **con, SSL_CTX *ctx, int fd) 
{
  *con = (SSL *)SSL_new (ctx);
  SSL_set_fd (*con, fd);
  SSL_set_connect_state (*con); 
  SSL_connect (*con);  
  if ((*con)->state != SSL_ST_OK)
    return 1;
  /*while((SSLerror=ERR_get_error())!=0)
    printf("%s\n", ERR_error_string(SSLerror,NULL));*/

  return 0;
}

void
shutdown_ssl (SSL* con)
{
  SSL_shutdown (con);
  if (con != NULL)
    SSL_free (con);
}

void
free_ssl_ctx (SSL_CTX * ctx)
{
  SSL_CTX_free (ctx);
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
    case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
      ok = 1;
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
  for (curerr = ERR_get_error (); curerr; curerr = ERR_get_error ())
    {
      DEBUGP (("OpenSSL: %s\n", ERR_error_string (curerr, errbuff)));
      ++ocerr;
    }
  return ocerr;
}

/* SSL version of iread. Only exchanged read for SSL_read 
   Read at most LEN bytes from FD, storing them to BUF.  This is
   virtually the same as read(), but takes care of EINTR braindamage
   and uses select() to timeout the stale connections (a connection is
   stale if more than OPT.TIMEOUT time is spent in select() or
   read()).  */
int
ssl_iread (SSL *con, char *buf, int len)
{
  int res;
  int fd;
  BIO_get_fd (con->rbio, &fd);
  do
    {
#ifdef HAVE_SELECT
      if (opt.timeout)
	{
	  
	  do
	    {
	      res = select_fd (fd, opt.timeout, 0);
	    }
	  while (res == -1 && errno == EINTR);
	  if (res <= 0)
	    {
	      /* Set errno to ETIMEDOUT on timeout.  */
	      if (res == 0)
		/* #### Potentially evil!  */
		errno = ETIMEDOUT;
	      return -1;
	    }
	}
#endif
      res = SSL_read (con, buf, len);
    }
  while (res == -1 && errno == EINTR);

  return res;
}

/* SSL version of iwrite. Only exchanged write for SSL_write 
   Write LEN bytes from BUF to FD.  This is similar to iread(), but
   doesn't bother with select().  Unlike iread(), it makes sure that
   all of BUF is actually written to FD, so callers needn't bother
   with checking that the return value equals to LEN.  Instead, you
   should simply check for -1.  */
int
ssl_iwrite (SSL *con, char *buf, int len)
{
  int res = 0;
  int fd;
  BIO_get_fd (con->rbio, &fd);
  /* `write' may write less than LEN bytes, thus the outward loop
     keeps trying it until all was written, or an error occurred.  The
     inner loop is reserved for the usual EINTR f*kage, and the
     innermost loop deals with the same during select().  */
  while (len > 0)
    {
      do
	{
#ifdef HAVE_SELECT
	  if (opt.timeout)
	    {
	      do
		{
		  res = select_fd (fd, opt.timeout, 1);
		}
	      while (res == -1 && errno == EINTR);
	      if (res <= 0)
		{
		  /* Set errno to ETIMEDOUT on timeout.  */
		  if (res == 0)
		    /* #### Potentially evil!  */
		    errno = ETIMEDOUT;
		  return -1;
		}
	    }
#endif
	  res = SSL_write (con, buf, len);
	}
      while (res == -1 && errno == EINTR);
      if (res <= 0)
	break;
      buf += res;
      len -= res;
    }
  return res;
}
#endif /* HAVE_SSL */
