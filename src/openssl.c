/* SSL support via OpenSSL library.
   Copyright (C) 2000-2005 Free Software Foundation, Inc.
   Originally contributed by Christian Fraenkel.

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
#include "ssl.h"

#ifndef errno
extern int errno;
#endif

/* Application-wide SSL context.  This is common to all SSL
   connections.  */
SSL_CTX *ssl_ctx;

/* Initialize the SSL's PRNG using various methods. */

static void
init_prng (void)
{
  char namebuf[256];
  const char *random_file;

  if (RAND_status ())
    /* The PRNG has been seeded; no further action is necessary. */
    return;

  /* Seed from a file specified by the user.  This will be the file
     specified with --random-file, $RANDFILE, if set, or ~/.rnd, if it
     exists.  */
  if (opt.random_file)
    random_file = opt.random_file;
  else
    {
      /* Get the random file name using RAND_file_name. */
      namebuf[0] = '\0';
      random_file = RAND_file_name (namebuf, sizeof (namebuf));
    }

  if (random_file && *random_file)
    /* Seed at most 16k (apparently arbitrary value borrowed from
       curl) from random file. */
    RAND_load_file (random_file, 16384);

  if (RAND_status ())
    return;

  /* Get random data from EGD if opt.egd_file was used.  */
  if (opt.egd_file && *opt.egd_file)
    RAND_egd (opt.egd_file);

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

#if 0 /* don't do this by default */
  {
    int maxrand = 500;

    /* Still not random enough, presumably because neither /dev/random
       nor EGD were available.  Try to seed OpenSSL's PRNG with libc
       PRNG.  This is cryptographically weak and defeats the purpose
       of using OpenSSL, which is why it is highly discouraged.  */

    logprintf (LOG_NOTQUIET, _("WARNING: using a weak random seed.\n"));

    while (RAND_status () == 0 && maxrand-- > 0)
      {
	unsigned char rnd = random_number (256);
	RAND_seed (&rnd, sizeof (rnd));
      }
  }
#endif
}

/* #### Someone should audit and document this. */

static int
verify_callback (int ok, X509_STORE_CTX *ctx)
{
  char buf[256];
  /* #### Why are we not using the result of this call? */
  X509_NAME_oneline (X509_get_subject_name (ctx->current_cert),
		     buf, sizeof (buf));
  if (ok == 0)
    {
      switch (ctx->error)
	{
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

/* Print errors in the OpenSSL error stack. */

static void
print_errors (void) 
{
  unsigned long curerr = 0;
  while ((curerr = ERR_get_error ()) != 0)
    logprintf (LOG_NOTQUIET, "OpenSSL: %s\n", ERR_error_string (curerr, NULL));
}

/* Convert keyfile type as used by options.h to a type as accepted by
   SSL_CTX_use_certificate_file and SSL_CTX_use_PrivateKey_file.

   (options.h intentionally doesn't use values from openssl/ssl.h so
   it doesn't depend specifically on OpenSSL for SSL functionality.)  */

static int
key_type_to_ssl_type (enum keyfile_type type)
{
  switch (type)
    {
    case keyfile_pem:
      return SSL_FILETYPE_PEM;
    case keyfile_asn1:
      return SSL_FILETYPE_ASN1;
    default:
      abort ();
    }
}

/* Create an SSL Context and set default paths etc.  Called the first
   time an HTTP download is attempted.

   Returns 0 on success, non-zero otherwise.  */

int
ssl_init ()
{
  SSL_METHOD *meth;

  if (ssl_ctx)
    /* The SSL has already been initialized. */
    return 1;

  /* Init the PRNG.  If that fails, bail out.  */
  init_prng ();
  if (RAND_status () != 1)
    {
      logprintf (LOG_NOTQUIET,
		 _("Could not seed PRNG; consider using --random-file.\n"));
      goto error;
    }

  SSL_library_init ();
  SSL_load_error_strings ();
  SSLeay_add_all_algorithms ();
  SSLeay_add_ssl_algorithms ();

  switch (opt.secure_protocol)
    {
    case secure_protocol_auto:
      meth = SSLv23_client_method ();
      break;
    case secure_protocol_sslv2:
      meth = SSLv2_client_method ();
      break;
    case secure_protocol_sslv3:
      meth = SSLv3_client_method ();
      break;
    case secure_protocol_tlsv1:
      meth = TLSv1_client_method ();
      break;
    default:
      abort ();
    }

  ssl_ctx = SSL_CTX_new (meth);
  if (!ssl_ctx)
    goto error;

  SSL_CTX_set_default_verify_paths (ssl_ctx);
  SSL_CTX_load_verify_locations (ssl_ctx, opt.ca_cert, opt.ca_directory);
  SSL_CTX_set_verify (ssl_ctx,
		      opt.check_cert ? SSL_VERIFY_PEER : SSL_VERIFY_NONE,
		      verify_callback);

  if (opt.cert_file)
    if (SSL_CTX_use_certificate_file (ssl_ctx, opt.cert_file,
				      key_type_to_ssl_type (opt.cert_type))
	!= 1)
      goto error;
  if (opt.private_key)
    if (SSL_CTX_use_PrivateKey_file (ssl_ctx, opt.private_key,
				     key_type_to_ssl_type (opt.private_key_type))
	!= 1)
      goto error;

  return 1;

 error:
  if (ssl_ctx)
    SSL_CTX_free (ssl_ctx);
  print_errors ();
  return 0;
}

static int
openssl_read (int fd, char *buf, int bufsize, void *ctx)
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
openssl_write (int fd, char *buf, int bufsize, void *ctx)
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
openssl_poll (int fd, double timeout, int wait_for, void *ctx)
{
  SSL *ssl = (SSL *) ctx;
  if (timeout == 0)
    return 1;
  if (SSL_pending (ssl))
    return 1;
  return select_fd (fd, timeout, wait_for);
}

static int
openssl_peek (int fd, char *buf, int bufsize, void *ctx)
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
openssl_close (int fd, void *ctx)
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
     That way the rest of Wget can keep using fd_read, fd_write, and
     friends and not care what happens underneath.  */
  fd_register_transport (fd, openssl_read, openssl_write, openssl_poll,
			 openssl_peek, openssl_close, ssl);
  DEBUGP (("Connected %d to SSL 0x%0*lx\n", fd, 2 * sizeof (void *),
	   (unsigned long) ssl));
  return 1;

 err:
  print_errors ();
  if (ssl)
    SSL_free (ssl);
  return 0;
}
