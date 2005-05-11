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

#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/err.h>
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

   Returns 1 on success, 0 otherwise.  */

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

  /* Specify whether the connect should fail if the verification of
     the peer fails or if it should go ahead.  */
  SSL_CTX_set_verify (ssl_ctx,
		      opt.check_cert ? SSL_VERIFY_PEER : SSL_VERIFY_NONE, NULL);

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

  /* Since fd_write unconditionally assumes partial writes (and
     handles them correctly), allow them in OpenSSL.  */
  SSL_CTX_set_mode (ssl_ctx, SSL_MODE_ENABLE_PARTIAL_WRITE);

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
    goto error;
  if (!SSL_set_fd (ssl, fd))
    goto error;
  SSL_set_connect_state (ssl);
  if (SSL_connect (ssl) <= 0 || ssl->state != SSL_ST_OK)
    goto error;

  /* Register FD with Wget's transport layer, i.e. arrange that
     SSL-enabled functions are used for reading, writing, and polling.
     That way the rest of Wget can keep using fd_read, fd_write, and
     friends and not care what happens underneath.  */
  fd_register_transport (fd, openssl_read, openssl_write, openssl_poll,
			 openssl_peek, openssl_close, ssl);
  DEBUGP (("Connected %d to SSL 0x%0*lx\n", fd, 2 * sizeof (void *),
	   (unsigned long) ssl));
  return 1;

 error:
  print_errors ();
  if (ssl)
    SSL_free (ssl);
  return 0;
}

/* Return 1 is STRING (case-insensitively) matches PATTERN, 0
   otherwise.  The recognized wildcard character is "*", which matches
   any character in STRING except ".".  Any number of the "*" wildcard
   may be present in the pattern.

   This is used to match of hosts as indicated in rfc2818: "Names may
   contain the wildcard character * which is considered to match any
   single domain name component or component fragment. E.g., *.a.com
   matches foo.a.com but not bar.foo.a.com. f*.com matches foo.com but
   not bar.com."  */

static int
pattern_match (const char *pattern, const char *string)
{
  const char *p = pattern, *n = string;
  char c;
  for (; (c = TOLOWER (*p++)) != '\0'; n++)
    if (c == '*')
      {
	for (c = TOLOWER (*p); c == '*'; c = TOLOWER (*++p))
	  ;
	for (; *n != '\0'; n++)
	  if (TOLOWER (*n) == c && pattern_match (p, n))
	    return 1;
	  else if (*n == '.')
	    return 0;
	return c == '\0';
      }
    else
      {
	if (c != TOLOWER (*n))
	  return 0;
      }
  return *n == '\0';
}

/* Check that the identity of the remote host, as presented by its
   server certificate, corresponds to HOST, which is the host name the
   user thinks he's connecting to.  This assumes that FD has been
   connected to an SSL context using ssl_connect.  Return 1 if the
   identity checks out, 0 otherwise.

   If opt.check_cert is 0, this always returns 1, but still warns the
   user about the mismatches, if any.  */

int
ssl_check_server_identity (int fd, const char *host)
{
  X509 *peer_cert = NULL;
  char peer_CN[256];
  long vresult;
  int retval;

  /* If the user has specified --no-check-cert, we still want to warn
     him about problems with the server's certificate.  */
  const char *severity = opt.check_cert ? _("ERROR") : _("WARNING");

  SSL *ssl = (SSL *) fd_transport_context (fd);
  assert (ssl != NULL);

  peer_cert = SSL_get_peer_certificate (ssl);
  if (!peer_cert)
    {
      logprintf (LOG_NOTQUIET, _("%s: No certificate presented by %s.\n"),
		 severity, escnonprint (host));
      retval = 0;
      goto out;
    }

#ifdef ENABLE_DEBUG
  if (opt.debug)
    {
      char *subject = X509_NAME_oneline (X509_get_subject_name (peer_cert), 0, 0);
      char *issuer = X509_NAME_oneline (X509_get_issuer_name (peer_cert), 0, 0);
      DEBUGP (("certificate:\n  subject: %s\n  issuer:  %s\n",
	       escnonprint (subject), escnonprint (issuer)));
      OPENSSL_free (subject);
      OPENSSL_free (issuer);
    }
#endif

  vresult = SSL_get_verify_result (ssl);
  if (vresult != X509_V_OK)
    {
      logprintf (LOG_NOTQUIET,
		 _("%s: Certificate verification error for %s: %s\n"),
		 severity, escnonprint (host),
		 X509_verify_cert_error_string (vresult));
      retval = 0;
      goto out;
    }

  /* Check that the common name in the presented certificate matches
     HOST.  This should be improved in the following ways:

     - It should use dNSName/ipAddress subjectAltName extensions if
       available; according to rfc2818: "If a subjectAltName extension
       of type dNSName is present, that MUST be used as the identity."

     - When matching against common names, it should loop over all
       common names and choose the most specific (apparently the last
       one).  */

  peer_CN[0] = '\0';
  X509_NAME_get_text_by_NID (X509_get_subject_name (peer_cert),
			     NID_commonName, peer_CN, sizeof (peer_CN));
  if (!pattern_match (peer_CN, host))
    {
      logprintf (LOG_NOTQUIET, _("\
%s: certificate common name `%s' doesn't match requested host name `%s'.\n"),
		 severity, escnonprint (peer_CN), escnonprint (host));
      retval = 0;
      goto out;
    }

  /* The certificate was found, verified, and matched HOST. */
  retval = 1;

 out:
  if (peer_cert)
    X509_free (peer_cert);

  /* Allow --no-check-cert to disable certificate checking. */
  return opt.check_cert ? retval : 1;
}

