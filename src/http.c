/* HTTP support.
   Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001, 2002
   Free Software Foundation, Inc.

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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <assert.h>
#include <errno.h>
#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif
#ifndef errno
extern int errno;
#endif

#include "wget.h"
#include "utils.h"
#include "url.h"
#include "host.h"
#include "rbuf.h"
#include "retr.h"
#include "headers.h"
#include "connect.h"
#include "netrc.h"
#ifdef HAVE_SSL
# include "gen_sslfunc.h"
#endif /* HAVE_SSL */
#include "cookies.h"
#ifdef USE_DIGEST
# include "gen-md5.h"
#endif
#include "convert.h"

extern char *version_string;
extern LARGE_INT total_downloaded_bytes;


static int cookies_loaded_p;
struct cookie_jar *wget_cookie_jar;

#define TEXTHTML_S "text/html"
#define TEXTXHTML_S "application/xhtml+xml"
#define HTTP_ACCEPT "*/*"

/* Some status code validation macros: */
#define H_20X(x)        (((x) >= 200) && ((x) < 300))
#define H_PARTIAL(x)    ((x) == HTTP_STATUS_PARTIAL_CONTENTS)
#define H_REDIRECTED(x) ((x) == HTTP_STATUS_MOVED_PERMANENTLY	\
                         || (x) == HTTP_STATUS_MOVED_TEMPORARILY \
			 || (x) == HTTP_STATUS_TEMPORARY_REDIRECT)

/* HTTP/1.0 status codes from RFC1945, provided for reference.  */
/* Successful 2xx.  */
#define HTTP_STATUS_OK			200
#define HTTP_STATUS_CREATED		201
#define HTTP_STATUS_ACCEPTED		202
#define HTTP_STATUS_NO_CONTENT		204
#define HTTP_STATUS_PARTIAL_CONTENTS	206

/* Redirection 3xx.  */
#define HTTP_STATUS_MULTIPLE_CHOICES	300
#define HTTP_STATUS_MOVED_PERMANENTLY	301
#define HTTP_STATUS_MOVED_TEMPORARILY	302
#define HTTP_STATUS_NOT_MODIFIED	304
#define HTTP_STATUS_TEMPORARY_REDIRECT  307

/* Client error 4xx.  */
#define HTTP_STATUS_BAD_REQUEST		400
#define HTTP_STATUS_UNAUTHORIZED	401
#define HTTP_STATUS_FORBIDDEN		403
#define HTTP_STATUS_NOT_FOUND		404

/* Server errors 5xx.  */
#define HTTP_STATUS_INTERNAL		500
#define HTTP_STATUS_NOT_IMPLEMENTED	501
#define HTTP_STATUS_BAD_GATEWAY		502
#define HTTP_STATUS_UNAVAILABLE		503


/* Parse the HTTP status line, which is of format:

   HTTP-Version SP Status-Code SP Reason-Phrase

   The function returns the status-code, or -1 if the status line is
   malformed.  The pointer to reason-phrase is returned in RP.  */
static int
parse_http_status_line (const char *line, const char **reason_phrase_ptr)
{
  /* (the variables must not be named `major' and `minor', because
     that breaks compilation with SunOS4 cc.)  */
  int mjr, mnr, statcode;
  const char *p;

  *reason_phrase_ptr = NULL;

  /* The standard format of HTTP-Version is: `HTTP/X.Y', where X is
     major version, and Y is minor version.  */
  if (strncmp (line, "HTTP/", 5) != 0)
    return -1;
  line += 5;

  /* Calculate major HTTP version.  */
  p = line;
  for (mjr = 0; ISDIGIT (*line); line++)
    mjr = 10 * mjr + (*line - '0');
  if (*line != '.' || p == line)
    return -1;
  ++line;

  /* Calculate minor HTTP version.  */
  p = line;
  for (mnr = 0; ISDIGIT (*line); line++)
    mnr = 10 * mnr + (*line - '0');
  if (*line != ' ' || p == line)
    return -1;
  /* Wget will accept only 1.0 and higher HTTP-versions.  The value of
     minor version can be safely ignored.  */
  if (mjr < 1)
    return -1;
  ++line;

  /* Calculate status code.  */
  if (!(ISDIGIT (*line) && ISDIGIT (line[1]) && ISDIGIT (line[2])))
    return -1;
  statcode = 100 * (*line - '0') + 10 * (line[1] - '0') + (line[2] - '0');

  /* Set up the reason phrase pointer.  */
  line += 3;
  /* RFC2068 requires SPC here, but we allow the string to finish
     here, in case no reason-phrase is present.  */
  if (*line != ' ')
    {
      if (!*line)
	*reason_phrase_ptr = line;
      else
	return -1;
    }
  else
    *reason_phrase_ptr = line + 1;

  return statcode;
}

#define WMIN(x, y) ((x) > (y) ? (y) : (x))

/* Send the contents of FILE_NAME to SOCK/SSL.  Make sure that exactly
   PROMISED_SIZE bytes are sent over the wire -- if the file is
   longer, read only that much; if the file is shorter, report an error.  */

static int
post_file (int sock, void *ssl, const char *file_name, long promised_size)
{
  static char chunk[8192];
  long written = 0;
  int write_error;
  FILE *fp;

  /* Only one of SOCK and SSL may be active at the same time. */
  assert (sock > -1 || ssl != NULL);
  assert (sock == -1 || ssl == NULL);

  DEBUGP (("[writing POST file %s ... ", file_name));

  fp = fopen (file_name, "rb");
  if (!fp)
    return -1;
  while (!feof (fp) && written < promised_size)
    {
      int towrite;
      int length = fread (chunk, 1, sizeof (chunk), fp);
      if (length == 0)
	break;
      towrite = WMIN (promised_size - written, length);
#ifdef HAVE_SSL
      if (ssl)
	write_error = ssl_iwrite (ssl, chunk, towrite);
      else
#endif
	write_error = iwrite (sock, chunk, towrite);
      if (write_error < 0)
	{
	  fclose (fp);
	  return -1;
	}
      written += towrite;
    }
  fclose (fp);

  /* If we've written less than was promised, report a (probably
     nonsensical) error rather than break the promise.  */
  if (written < promised_size)
    {
      errno = EINVAL;
      return -1;
    }

  assert (written == promised_size);
  DEBUGP (("done]\n"));
  return 0;
}

/* Functions to be used as arguments to header_process(): */

struct http_process_range_closure {
  long first_byte_pos;
  long last_byte_pos;
  long entity_length;
};

/* Parse the `Content-Range' header and extract the information it
   contains.  Returns 1 if successful, -1 otherwise.  */
static int
http_process_range (const char *hdr, void *arg)
{
  struct http_process_range_closure *closure
    = (struct http_process_range_closure *)arg;
  long num;

  /* Certain versions of Nutscape proxy server send out
     `Content-Length' without "bytes" specifier, which is a breach of
     RFC2068 (as well as the HTTP/1.1 draft which was current at the
     time).  But hell, I must support it...  */
  if (!strncasecmp (hdr, "bytes", 5))
    {
      hdr += 5;
      /* "JavaWebServer/1.1.1" sends "bytes: x-y/z", contrary to the
	 HTTP spec. */
      if (*hdr == ':')
	++hdr;
      hdr += skip_lws (hdr);
      if (!*hdr)
	return 0;
    }
  if (!ISDIGIT (*hdr))
    return 0;
  for (num = 0; ISDIGIT (*hdr); hdr++)
    num = 10 * num + (*hdr - '0');
  if (*hdr != '-' || !ISDIGIT (*(hdr + 1)))
    return 0;
  closure->first_byte_pos = num;
  ++hdr;
  for (num = 0; ISDIGIT (*hdr); hdr++)
    num = 10 * num + (*hdr - '0');
  if (*hdr != '/' || !ISDIGIT (*(hdr + 1)))
    return 0;
  closure->last_byte_pos = num;
  ++hdr;
  for (num = 0; ISDIGIT (*hdr); hdr++)
    num = 10 * num + (*hdr - '0');
  closure->entity_length = num;
  return 1;
}

/* Place 1 to ARG if the HDR contains the word "none", 0 otherwise.
   Used for `Accept-Ranges'.  */
static int
http_process_none (const char *hdr, void *arg)
{
  int *where = (int *)arg;

  if (strstr (hdr, "none"))
    *where = 1;
  else
    *where = 0;
  return 1;
}

/* Place the malloc-ed copy of HDR hdr, to the first `;' to ARG.  */
static int
http_process_type (const char *hdr, void *arg)
{
  char **result = (char **)arg;
  /* Locate P on `;' or the terminating zero, whichever comes first. */
  const char *p = strchr (hdr, ';');
  if (!p)
    p = hdr + strlen (hdr);
  while (p > hdr && ISSPACE (*(p - 1)))
    --p;
  *result = strdupdelim (hdr, p);
  return 1;
}

/* Check whether the `Connection' header is set to "keep-alive". */
static int
http_process_connection (const char *hdr, void *arg)
{
  int *flag = (int *)arg;
  if (!strcasecmp (hdr, "Keep-Alive"))
    *flag = 1;
  return 1;
}

/* Commit the cookie to the cookie jar. */

int
http_process_set_cookie (const char *hdr, void *arg)
{
  struct url *u = (struct url *)arg;

  /* The jar should have been created by now. */
  assert (wget_cookie_jar != NULL);

  cookie_jar_process_set_cookie (wget_cookie_jar, u->host, u->port, u->path,
				 hdr);
  return 1;
}


/* Persistent connections.  Currently, we cache the most recently used
   connection as persistent, provided that the HTTP server agrees to
   make it such.  The persistence data is stored in the variables
   below.  Ideally, it would be in a structure, and it should be
   possible to cache an arbitrary fixed number of these connections.

   I think the code is quite easy to extend in that direction.  */

/* Whether a persistent connection is active. */
static int pc_active_p;
/* Host and port of currently active persistent connection. */
static struct address_list *pc_last_host_ip;
static unsigned short pc_last_port;

/* File descriptor of the currently active persistent connection. */
static int pc_last_fd;

#ifdef HAVE_SSL
/* Whether a ssl handshake has occoured on this connection */
static int pc_active_ssl;
/* SSL connection of the currently active persistent connection. */
static SSL *pc_last_ssl;
#endif /* HAVE_SSL */

/* Mark the persistent connection as invalid.  This is used by the
   CLOSE_* macros after they forcefully close a registered persistent
   connection.  This does not close the file descriptor -- it is left
   to the caller to do that.  (Maybe it should, though.)  */

static void
invalidate_persistent (void)
{
  pc_active_p = 0;
#ifdef HAVE_SSL
  pc_active_ssl = 0;
#endif /* HAVE_SSL */
  if (pc_last_host_ip != NULL)
    {
      address_list_release (pc_last_host_ip);
      pc_last_host_ip = NULL;
    }
  DEBUGP (("Invalidating fd %d from further reuse.\n", pc_last_fd));
}

/* Register FD, which should be a TCP/IP connection to HOST:PORT, as
   persistent.  This will enable someone to use the same connection
   later.  In the context of HTTP, this must be called only AFTER the
   response has been received and the server has promised that the
   connection will remain alive.

   If a previous connection was persistent, it is closed. */

#ifdef HAVE_SSL
static void
register_persistent (const char *host, unsigned short port, int fd, SSL *ssl)
{
#else
static void
register_persistent (const char *host, unsigned short port, int fd)
{
#endif
  if (pc_active_p)
    {
      if (pc_last_fd == fd)
	{
	  /* The connection FD is already registered.  Nothing to
	     do. */
	  return;
	}
      else
	{
	  /* The old persistent connection is still active; let's
	     close it first.  This situation arises whenever a
	     persistent connection exists, but we then connect to a
	     different host, and try to register a persistent
	     connection to that one.  */
#ifdef HAVE_SSL
	  /* The ssl disconnect has to take place before the closing
             of pc_last_fd.  */
	  if (pc_last_ssl)
	    shutdown_ssl(pc_last_ssl);
#endif
	  CLOSE (pc_last_fd);
	  invalidate_persistent ();
	}
    }

  assert (pc_last_host_ip == NULL);

  /* This lookup_host cannot fail, because it has the results in the
     cache.  */
  pc_last_host_ip = lookup_host (host, 1);
  assert (pc_last_host_ip != NULL);

  pc_last_port = port;
  pc_last_fd = fd;
  pc_active_p = 1;
#ifdef HAVE_SSL
  pc_last_ssl = ssl;
  pc_active_ssl = ssl ? 1 : 0;
#endif
  DEBUGP (("Registered fd %d for persistent reuse.\n", fd));
}

#ifdef HAVE_SSL
# define SHUTDOWN_SSL(ssl) do {		\
  if (ssl)				\
    shutdown_ssl (ssl);			\
} while (0)
#else
# define SHUTDOWN_SSL(ssl) 
#endif

/* Return non-zero if a persistent connection is available for
   connecting to HOST:PORT.  */

#ifdef HAVE_SSL
static int
persistent_available_p (const char *host, unsigned short port, int ssl)
{
#else
static int
persistent_available_p (const char *host, unsigned short port)
{
#endif
  int success;
  struct address_list *this_host_ip;

  /* First, check whether a persistent connection is active at all.  */
  if (!pc_active_p)
    return 0;
  /* Second, check if the active connection pertains to the correct
     (HOST, PORT) ordered pair.  */
  if (port != pc_last_port)
    return 0;

#ifdef HAVE_SSL
  /* Second, a): check if current connection is (not) ssl, too.  This
     test is unlikely to fail because HTTP and HTTPS typicaly use
     different ports.  Yet it is possible, or so I [Christian
     Fraenkel] have been told, to run HTTPS and HTTP simultaneus on
     the same port.  */
  if (ssl != pc_active_ssl)
    return 0;
#endif /* HAVE_SSL */

  this_host_ip = lookup_host (host, 1);
  if (!this_host_ip)
    return 0;

  /* To equate the two host names for the purposes of persistent
     connections, they need to share all the IP addresses in the
     list.  */
  success = address_list_match_all (pc_last_host_ip, this_host_ip);
  address_list_release (this_host_ip);
  if (!success)
    return 0;

  /* Third: check whether the connection is still open.  This is
     important because most server implement a liberal (short) timeout
     on persistent connections.  Wget can of course always reconnect
     if the connection doesn't work out, but it's nicer to know in
     advance.  This test is a logical followup of the first test, but
     is "expensive" and therefore placed at the end of the list.  */
  if (!test_socket_open (pc_last_fd))
    {
      /* Oops, the socket is no longer open.  Now that we know that,
         let's invalidate the persistent connection before returning
         0.  */
      CLOSE (pc_last_fd);
#ifdef HAVE_SSL
      SHUTDOWN_SSL (pc_last_ssl);
      pc_last_ssl = NULL;
#endif
      invalidate_persistent ();
      return 0;
    }
  return 1;
}

/* The idea behind these two CLOSE macros is to distinguish between
   two cases: one when the job we've been doing is finished, and we
   want to close the connection and leave, and two when something is
   seriously wrong and we're closing the connection as part of
   cleanup.

   In case of keep_alive, CLOSE_FINISH should leave the connection
   open, while CLOSE_INVALIDATE should still close it.

   Note that the semantics of the flag `keep_alive' is "this
   connection *will* be reused (the server has promised not to close
   the connection once we're done)", while the semantics of
   `pc_active_p && (fd) == pc_last_fd' is "we're *now* using an
   active, registered connection".  */

#define CLOSE_FINISH(fd) do {			\
  if (!keep_alive)				\
    {						\
      SHUTDOWN_SSL (ssl);			\
      CLOSE (fd);				\
      if (pc_active_p && (fd) == pc_last_fd)	\
	invalidate_persistent ();		\
    }						\
} while (0)

#define CLOSE_INVALIDATE(fd) do {		\
  SHUTDOWN_SSL (ssl);				\
  CLOSE (fd);					\
  if (pc_active_p && (fd) == pc_last_fd)	\
    invalidate_persistent ();			\
} while (0)

struct http_stat
{
  long len;			/* received length */
  long contlen;			/* expected length */
  long restval;			/* the restart value */
  int res;			/* the result of last read */
  char *newloc;			/* new location (redirection) */
  char *remote_time;		/* remote time-stamp string */
  char *error;			/* textual HTTP error */
  int statcode;			/* status code */
  double dltime;		/* time of the download in msecs */
  int no_truncate;		/* whether truncating the file is
				   forbidden. */
  const char *referer;		/* value of the referer header. */
  char **local_file;		/* local file. */
};

static void
free_hstat (struct http_stat *hs)
{
  FREE_MAYBE (hs->newloc);
  FREE_MAYBE (hs->remote_time);
  FREE_MAYBE (hs->error);

  /* Guard against being called twice. */
  hs->newloc = NULL;
  hs->remote_time = NULL;
  hs->error = NULL;
}

static char *create_authorization_line PARAMS ((const char *, const char *,
						const char *, const char *,
						const char *));
static char *basic_authentication_encode PARAMS ((const char *, const char *,
						  const char *));
static int known_authentication_scheme_p PARAMS ((const char *));

time_t http_atotm PARAMS ((const char *));

#define BEGINS_WITH(line, string_constant)				\
  (!strncasecmp (line, string_constant, sizeof (string_constant) - 1)	\
   && (ISSPACE (line[sizeof (string_constant) - 1])			\
       || !line[sizeof (string_constant) - 1]))

/* Retrieve a document through HTTP protocol.  It recognizes status
   code, and correctly handles redirections.  It closes the network
   socket.  If it receives an error from the functions below it, it
   will print it if there is enough information to do so (almost
   always), returning the error to the caller (i.e. http_loop).

   Various HTTP parameters are stored to hs.  Although it parses the
   response code correctly, it is not used in a sane way.  The caller
   can do that, though.

   If PROXY is non-NULL, the connection will be made to the proxy
   server, and u->url will be requested.  */
static uerr_t
gethttp (struct url *u, struct http_stat *hs, int *dt, struct url *proxy)
{
  char *request, *type, *command, *full_path;
  char *user, *passwd;
  char *pragma_h, *referer, *useragent, *range, *wwwauth;
  char *authenticate_h;
  char *proxyauth;
  char *all_headers;
  char *port_maybe;
  char *request_keep_alive;
  int sock, hcount, all_length, statcode;
  int write_error;
  long contlen, contrange;
  struct url *conn;
  FILE *fp;
  int auth_tried_already;
  struct rbuf rbuf;
#ifdef HAVE_SSL
  static SSL_CTX *ssl_ctx = NULL;
  SSL *ssl = NULL;
#endif
  char *cookies = NULL;

  /* Whether this connection will be kept alive after the HTTP request
     is done. */
  int keep_alive;

  /* Flags that detect the two ways of specifying HTTP keep-alive
     response.  */
  int http_keep_alive_1, http_keep_alive_2;

  /* Whether keep-alive should be inhibited. */
  int inhibit_keep_alive;

  /* Whether we need to print the host header with braces around host,
     e.g. "Host: [3ffe:8100:200:2::2]:1234" instead of the usual
     "Host: symbolic-name:1234". */
  int squares_around_host = 0;

  /* Headers sent when using POST. */
  char *post_content_type, *post_content_length;
  long post_data_size = 0;

#ifdef HAVE_SSL
  /* initialize ssl_ctx on first run */
  if (!ssl_ctx)
    {
      uerr_t err = init_ssl (&ssl_ctx);
      if (err != 0)
	{
	  switch (err)
	    {
	    case SSLERRCTXCREATE:
	      /* this is fatal */
	      logprintf (LOG_NOTQUIET, _("Failed to set up an SSL context\n"));
	      ssl_printerrors ();
	      return err;
	    case SSLERRCERTFILE:
	      /* try without certfile */
	      logprintf (LOG_NOTQUIET,
			 _("Failed to load certificates from %s\n"),
			 opt.sslcertfile);
	      ssl_printerrors ();
	      logprintf (LOG_NOTQUIET,
			 _("Trying without the specified certificate\n"));
	      break;
	    case SSLERRCERTKEY:
	      logprintf (LOG_NOTQUIET,
			 _("Failed to get certificate key from %s\n"),
			 opt.sslcertkey);
	      ssl_printerrors ();
	      logprintf (LOG_NOTQUIET,
			 _("Trying without the specified certificate\n"));
	      break;
	    default:
	      break;
	    }
	}
    }
#endif /* HAVE_SSL */

  if (!(*dt & HEAD_ONLY))
    /* If we're doing a GET on the URL, as opposed to just a HEAD, we need to
       know the local filename so we can save to it. */
    assert (*hs->local_file != NULL);

  authenticate_h = 0;
  auth_tried_already = 0;

  inhibit_keep_alive = !opt.http_keep_alive || proxy != NULL;

 again:
  /* We need to come back here when the initial attempt to retrieve
     without authorization header fails.  (Expected to happen at least
     for the Digest authorization scheme.)  */

  keep_alive = 0;
  http_keep_alive_1 = http_keep_alive_2 = 0;

  post_content_type = NULL;
  post_content_length = NULL;

  /* Initialize certain elements of struct http_stat.  */
  hs->len = 0L;
  hs->contlen = -1;
  hs->res = -1;
  hs->newloc = NULL;
  hs->remote_time = NULL;
  hs->error = NULL;

  /* If we're using a proxy, we will be connecting to the proxy
     server. */
  conn = proxy ? proxy : u;

  /* First: establish the connection.  */
  if (inhibit_keep_alive
      ||
#ifndef HAVE_SSL
      !persistent_available_p (conn->host, conn->port)
#else
      !persistent_available_p (conn->host, conn->port,
			       u->scheme == SCHEME_HTTPS)
#endif /* HAVE_SSL */
      )
    {
      struct address_list *al = lookup_host (conn->host, 0);
      if (!al)
	return HOSTERR;
      set_connection_host_name (conn->host);
      sock = connect_to_many (al, conn->port, 0);
      set_connection_host_name (NULL);
      address_list_release (al);

      if (sock < 0)
	return CONNECT_ERROR (errno);

#ifdef HAVE_SSL
     if (conn->scheme == SCHEME_HTTPS)
       if (connect_ssl (&ssl, ssl_ctx,sock) != 0)
	 {
	   logputs (LOG_VERBOSE, "\n");
	   logprintf (LOG_NOTQUIET, _("Unable to establish SSL connection.\n"));
	   ssl_printerrors ();
	   CLOSE (sock);
	   return CONSSLERR;
	 }
#endif /* HAVE_SSL */
    }
  else
    {
      logprintf (LOG_VERBOSE, _("Reusing connection to %s:%hu.\n"),
		 conn->host, conn->port);
      /* #### pc_last_fd should be accessed through an accessor
         function.  */
      sock = pc_last_fd;
#ifdef HAVE_SSL
      ssl = pc_last_ssl;
#endif /* HAVE_SSL */
      DEBUGP (("Reusing fd %d.\n", sock));
    }

  if (*dt & HEAD_ONLY)
    command = "HEAD";
  else if (opt.post_file_name || opt.post_data)
    command = "POST";
  else
    command = "GET";

  referer = NULL;
  if (hs->referer)
    {
      referer = (char *)alloca (9 + strlen (hs->referer) + 3);
      sprintf (referer, "Referer: %s\r\n", hs->referer);
    }

  if (*dt & SEND_NOCACHE)
    pragma_h = "Pragma: no-cache\r\n";
  else
    pragma_h = "";

  if (hs->restval)
    {
      range = (char *)alloca (13 + numdigit (hs->restval) + 4);
      /* Gag me!  Some servers (e.g. WebSitePro) have been known to
         respond to the following `Range' format by generating a
         multipart/x-byte-ranges MIME document!  This MIME type was
         present in an old draft of the byteranges specification.
         HTTP/1.1 specifies a multipart/byte-ranges MIME type, but
         only if multiple non-overlapping ranges are requested --
         which Wget never does.  */
      sprintf (range, "Range: bytes=%ld-\r\n", hs->restval);
    }
  else
    range = NULL;
  if (opt.useragent)
    STRDUP_ALLOCA (useragent, opt.useragent);
  else
    {
      useragent = (char *)alloca (10 + strlen (version_string));
      sprintf (useragent, "Wget/%s", version_string);
    }
  /* Construct the authentication, if userid is present.  */
  user = u->user;
  passwd = u->passwd;
  search_netrc (u->host, (const char **)&user, (const char **)&passwd, 0);
  user = user ? user : opt.http_user;
  passwd = passwd ? passwd : opt.http_passwd;

  wwwauth = NULL;
  if (user && passwd)
    {
      if (!authenticate_h)
	{
	  /* We have the username and the password, but haven't tried
	     any authorization yet.  Let's see if the "Basic" method
	     works.  If not, we'll come back here and construct a
	     proper authorization method with the right challenges.

	     If we didn't employ this kind of logic, every URL that
	     requires authorization would have to be processed twice,
	     which is very suboptimal and generates a bunch of false
	     "unauthorized" errors in the server log.

	     #### But this logic also has a serious problem when used
	     with stronger authentications: we *first* transmit the
	     username and the password in clear text, and *then*
	     attempt a stronger authentication scheme.  That cannot be
	     right!  We are only fortunate that almost everyone still
	     uses the `Basic' scheme anyway.

	     There should be an option to prevent this from happening,
	     for those who use strong authentication schemes and value
	     their passwords.  */
	  wwwauth = basic_authentication_encode (user, passwd, "Authorization");
	}
      else
	{
	  /* Use the full path, i.e. one that includes the leading
	     slash and the query string, but is independent of proxy
	     setting.  */
	  char *pth = url_full_path (u);
	  wwwauth = create_authorization_line (authenticate_h, user, passwd,
					       command, pth);
	  xfree (pth);
	}
    }

  proxyauth = NULL;
  if (proxy)
    {
      char *proxy_user, *proxy_passwd;
      /* For normal username and password, URL components override
	 command-line/wgetrc parameters.  With proxy authentication,
	 it's the reverse, because proxy URLs are normally the
	 "permanent" ones, so command-line args should take
	 precedence.  */
      if (opt.proxy_user && opt.proxy_passwd)
	{
	  proxy_user = opt.proxy_user;
	  proxy_passwd = opt.proxy_passwd;
	}
      else
	{
	  proxy_user = proxy->user;
	  proxy_passwd = proxy->passwd;
	}
      /* #### This does not appear right.  Can't the proxy request,
         say, `Digest' authentication?  */
      if (proxy_user && proxy_passwd)
	proxyauth = basic_authentication_encode (proxy_user, proxy_passwd,
						 "Proxy-Authorization");
    }

  /* String of the form :PORT.  Used only for non-standard ports. */
  port_maybe = NULL;
  if (u->port != scheme_default_port (u->scheme))
    {
      port_maybe = (char *)alloca (numdigit (u->port) + 2);
      sprintf (port_maybe, ":%d", u->port);
    }

  if (!inhibit_keep_alive)
    request_keep_alive = "Connection: Keep-Alive\r\n";
  else
    request_keep_alive = NULL;

  if (opt.cookies)
    cookies = cookie_jar_generate_cookie_header (wget_cookie_jar, u->host,
						 u->port, u->path,
#ifdef HAVE_SSL
						 u->scheme == SCHEME_HTTPS
#else
						 0
#endif
				 );

  if (opt.post_data || opt.post_file_name)
    {
      post_content_type = "Content-Type: application/x-www-form-urlencoded\r\n";
      if (opt.post_data)
	post_data_size = strlen (opt.post_data);
      else
	{
	  post_data_size = file_size (opt.post_file_name);
	  if (post_data_size == -1)
	    {
	      logprintf (LOG_NOTQUIET, "POST data file missing: %s\n",
			 opt.post_file_name);
	      post_data_size = 0;
	    }
	}
      post_content_length = xmalloc (16 + numdigit (post_data_size) + 2 + 1);
      sprintf (post_content_length,
	       "Content-Length: %ld\r\n", post_data_size);
    }

  if (proxy)
    full_path = xstrdup (u->url);
  else
    /* Use the full path, i.e. one that includes the leading slash and
       the query string.  E.g. if u->path is "foo/bar" and u->query is
       "param=value", full_path will be "/foo/bar?param=value".  */
    full_path = url_full_path (u);

  if (strchr (u->host, ':'))
    squares_around_host = 1;

  /* Allocate the memory for the request.  */
  request = (char *)alloca (strlen (command)
			    + strlen (full_path)
			    + strlen (useragent)
			    + strlen (u->host)
			    + (port_maybe ? strlen (port_maybe) : 0)
			    + strlen (HTTP_ACCEPT)
			    + (request_keep_alive
			       ? strlen (request_keep_alive) : 0)
			    + (referer ? strlen (referer) : 0)
			    + (cookies ? strlen (cookies) : 0)
			    + (wwwauth ? strlen (wwwauth) : 0)
			    + (proxyauth ? strlen (proxyauth) : 0)
			    + (range ? strlen (range) : 0)
			    + strlen (pragma_h)
			    + (post_content_type
			       ? strlen (post_content_type) : 0)
			    + (post_content_length
			       ? strlen (post_content_length) : 0)
			    + (opt.user_header ? strlen (opt.user_header) : 0)
			    + 64);
  /* Construct the request.  */
  sprintf (request, "\
%s %s HTTP/1.0\r\n\
User-Agent: %s\r\n\
Host: %s%s%s%s\r\n\
Accept: %s\r\n\
%s%s%s%s%s%s%s%s%s%s\r\n",
	   command, full_path,
	   useragent,
	   squares_around_host ? "[" : "", u->host, squares_around_host ? "]" : "",
	   port_maybe ? port_maybe : "",
	   HTTP_ACCEPT,
	   request_keep_alive ? request_keep_alive : "",
	   referer ? referer : "",
	   cookies ? cookies : "", 
	   wwwauth ? wwwauth : "", 
	   proxyauth ? proxyauth : "", 
	   range ? range : "",
	   pragma_h,
	   post_content_type ? post_content_type : "",
	   post_content_length ? post_content_length : "",
	   opt.user_header ? opt.user_header : "");
  DEBUGP (("---request begin---\n%s", request));

  /* Free the temporary memory.  */
  FREE_MAYBE (wwwauth);
  FREE_MAYBE (proxyauth);
  FREE_MAYBE (cookies);
  xfree (full_path);

  /* Send the request to server.  */
#ifdef HAVE_SSL
  if (conn->scheme == SCHEME_HTTPS)
    write_error = ssl_iwrite (ssl, request, strlen (request));
  else
#endif
    write_error = iwrite (sock, request, strlen (request));

  if (write_error >= 0)
    {
      if (opt.post_data)
	{
	  DEBUGP (("[POST data: %s]\n", opt.post_data));
#ifdef HAVE_SSL
	  if (conn->scheme == SCHEME_HTTPS)
	    write_error = ssl_iwrite (ssl, opt.post_data, post_data_size);
	  else
#endif
	    write_error = iwrite (sock, opt.post_data, post_data_size);
	}
      else if (opt.post_file_name && post_data_size != 0)
	{
#ifdef HAVE_SSL
	  if (conn->scheme == SCHEME_HTTPS)
	    write_error = post_file (-1, ssl, opt.post_file_name,
				     post_data_size);
	  else
#endif
	    write_error = post_file (sock, NULL, opt.post_file_name,
				     post_data_size);
	}
    }
  DEBUGP (("---request end---\n"));

  if (write_error < 0)
    {
      logprintf (LOG_VERBOSE, _("Failed writing HTTP request: %s.\n"),
		 strerror (errno));
      CLOSE_INVALIDATE (sock);
      return WRITEFAILED;
    }
  logprintf (LOG_VERBOSE, _("%s request sent, awaiting response... "),
	     proxy ? "Proxy" : "HTTP");
  contlen = contrange = -1;
  type = NULL;
  statcode = -1;
  *dt &= ~RETROKF;

  /* Before reading anything, initialize the rbuf.  */
  rbuf_initialize (&rbuf, sock);
#ifdef HAVE_SSL
  if (conn->scheme == SCHEME_HTTPS)
    rbuf.ssl = ssl;
  else
    rbuf.ssl = NULL;
#endif /* HAVE_SSL */
  all_headers = NULL;
  all_length = 0;
  /* Header-fetching loop.  */
  hcount = 0;
  while (1)
    {
      char *hdr;
      int status;

      ++hcount;
      /* Get the header.  */
      status = header_get (&rbuf, &hdr,
			   /* Disallow continuations for status line.  */
			   (hcount == 1 ? HG_NO_CONTINUATIONS : HG_NONE));

      /* Check for errors.  */
      if (status == HG_EOF && *hdr)
	{
	  /* This used to be an unconditional error, but that was
             somewhat controversial, because of a large number of
             broken CGI's that happily "forget" to send the second EOL
             before closing the connection of a HEAD request.

	     So, the deal is to check whether the header is empty
	     (*hdr is zero if it is); if yes, it means that the
	     previous header was fully retrieved, and that -- most
	     probably -- the request is complete.  "...be liberal in
	     what you accept."  Oh boy.  */
	  logputs (LOG_VERBOSE, "\n");
	  logputs (LOG_NOTQUIET, _("End of file while parsing headers.\n"));
	  xfree (hdr);
	  FREE_MAYBE (type);
	  FREE_MAYBE (all_headers);
	  CLOSE_INVALIDATE (sock);
	  return HEOF;
	}
      else if (status == HG_ERROR)
	{
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("Read error (%s) in headers.\n"),
		     strerror (errno));
	  xfree (hdr);
	  FREE_MAYBE (type);
	  FREE_MAYBE (all_headers);
	  CLOSE_INVALIDATE (sock);
	  return HERR;
	}

      /* If the headers are to be saved to a file later, save them to
	 memory now.  */
      if (opt.save_headers)
	{
	  int lh = strlen (hdr);
	  all_headers = (char *)xrealloc (all_headers, all_length + lh + 2);
	  memcpy (all_headers + all_length, hdr, lh);
	  all_length += lh;
	  all_headers[all_length++] = '\n';
	  all_headers[all_length] = '\0';
	}

      /* Check for status line.  */
      if (hcount == 1)
	{
	  const char *error;
	  /* Parse the first line of server response.  */
	  statcode = parse_http_status_line (hdr, &error);
	  hs->statcode = statcode;
	  /* Store the descriptive response.  */
	  if (statcode == -1) /* malformed response */
	    {
	      /* A common reason for "malformed response" error is the
                 case when no data was actually received.  Handle this
                 special case.  */
	      if (!*hdr)
		hs->error = xstrdup (_("No data received"));
	      else
		hs->error = xstrdup (_("Malformed status line"));
	      xfree (hdr);
	      break;
	    }
	  else if (!*error)
	    hs->error = xstrdup (_("(no description)"));
	  else
	    hs->error = xstrdup (error);

	  if ((statcode != -1)
#ifdef ENABLE_DEBUG
	      && !opt.debug
#endif
	      )
	    {
             if (opt.server_response)
	       logprintf (LOG_VERBOSE, "\n%2d %s", hcount, hdr);
             else
	       logprintf (LOG_VERBOSE, "%2d %s", statcode, error);
	    }

	  goto done_header;
	}

      /* Exit on empty header.  */
      if (!*hdr)
	{
	  xfree (hdr);
	  break;
	}

      /* Print the header if requested.  */
      if (opt.server_response && hcount != 1)
	logprintf (LOG_VERBOSE, "\n%2d %s", hcount, hdr);

      /* Try getting content-length.  */
      if (contlen == -1 && !opt.ignore_length)
	if (header_process (hdr, "Content-Length", header_extract_number,
			    &contlen))
	  goto done_header;
      /* Try getting content-type.  */
      if (!type)
	if (header_process (hdr, "Content-Type", http_process_type, &type))
	  goto done_header;
      /* Try getting location.  */
      if (!hs->newloc)
	if (header_process (hdr, "Location", header_strdup, &hs->newloc))
	  goto done_header;
      /* Try getting last-modified.  */
      if (!hs->remote_time)
	if (header_process (hdr, "Last-Modified", header_strdup,
			    &hs->remote_time))
	  goto done_header;
      /* Try getting cookies. */
      if (opt.cookies)
	if (header_process (hdr, "Set-Cookie", http_process_set_cookie, u))
	  goto done_header;
      /* Try getting www-authentication.  */
      if (!authenticate_h)
	if (header_process (hdr, "WWW-Authenticate", header_strdup,
			    &authenticate_h))
	  goto done_header;
      /* Check for accept-ranges header.  If it contains the word
	 `none', disable the ranges.  */
      if (*dt & ACCEPTRANGES)
	{
	  int nonep;
	  if (header_process (hdr, "Accept-Ranges", http_process_none, &nonep))
	    {
	      if (nonep)
		*dt &= ~ACCEPTRANGES;
	      goto done_header;
	    }
	}
      /* Try getting content-range.  */
      if (contrange == -1)
	{
	  struct http_process_range_closure closure;
	  if (header_process (hdr, "Content-Range", http_process_range, &closure))
	    {
	      contrange = closure.first_byte_pos;
	      goto done_header;
	    }
	}
      /* Check for keep-alive related responses. */
      if (!inhibit_keep_alive)
	{
	  /* Check for the `Keep-Alive' header. */
	  if (!http_keep_alive_1)
	    {
	      if (header_process (hdr, "Keep-Alive", header_exists,
				  &http_keep_alive_1))
		goto done_header;
	    }
	  /* Check for `Connection: Keep-Alive'. */
	  if (!http_keep_alive_2)
	    {
	      if (header_process (hdr, "Connection", http_process_connection,
				  &http_keep_alive_2))
		goto done_header;
	    }
	}
    done_header:
      xfree (hdr);
    }

  logputs (LOG_VERBOSE, "\n");

  if (contlen != -1
      && (http_keep_alive_1 || http_keep_alive_2))
    {
      assert (inhibit_keep_alive == 0);
      keep_alive = 1;
    }
  if (keep_alive)
    /* The server has promised that it will not close the connection
       when we're done.  This means that we can register it.  */
#ifndef HAVE_SSL
    register_persistent (conn->host, conn->port, sock);
#else
    register_persistent (conn->host, conn->port, sock, ssl);
#endif /* HAVE_SSL */

  if ((statcode == HTTP_STATUS_UNAUTHORIZED)
      && authenticate_h)
    {
      /* Authorization is required.  */
      FREE_MAYBE (type);
      type = NULL;
      free_hstat (hs);
      CLOSE_INVALIDATE (sock);	/* would be CLOSE_FINISH, but there
				   might be more bytes in the body. */
      if (auth_tried_already)
	{
	  /* If we have tried it already, then there is not point
	     retrying it.  */
	failed:
	  logputs (LOG_NOTQUIET, _("Authorization failed.\n"));
	  xfree (authenticate_h);
	  return AUTHFAILED;
	}
      else if (!known_authentication_scheme_p (authenticate_h))
	{
	  xfree (authenticate_h);
	  logputs (LOG_NOTQUIET, _("Unknown authentication scheme.\n"));
	  return AUTHFAILED;
	}
      else if (BEGINS_WITH (authenticate_h, "Basic"))
	{
	  /* The authentication scheme is basic, the one we try by
             default, and it failed.  There's no sense in trying
             again.  */
	  goto failed;
	}
      else
	{
	  auth_tried_already = 1;
	  goto again;
	}
    }
  /* We do not need this anymore.  */
  if (authenticate_h)
    {
      xfree (authenticate_h);
      authenticate_h = NULL;
    }

  /* 20x responses are counted among successful by default.  */
  if (H_20X (statcode))
    *dt |= RETROKF;

  /* Return if redirected.  */
  if (H_REDIRECTED (statcode) || statcode == HTTP_STATUS_MULTIPLE_CHOICES)
    {
      /* RFC2068 says that in case of the 300 (multiple choices)
	 response, the server can output a preferred URL through
	 `Location' header; otherwise, the request should be treated
	 like GET.  So, if the location is set, it will be a
	 redirection; otherwise, just proceed normally.  */
      if (statcode == HTTP_STATUS_MULTIPLE_CHOICES && !hs->newloc)
	*dt |= RETROKF;
      else
	{
	  logprintf (LOG_VERBOSE,
		     _("Location: %s%s\n"),
		     hs->newloc ? hs->newloc : _("unspecified"),
		     hs->newloc ? _(" [following]") : "");
	  CLOSE_INVALIDATE (sock);	/* would be CLOSE_FINISH, but there
					   might be more bytes in the body. */
	  FREE_MAYBE (type);
	  FREE_MAYBE (all_headers);
	  return NEWLOCATION;
	}
    }

  /* If content-type is not given, assume text/html.  This is because
     of the multitude of broken CGI's that "forget" to generate the
     content-type.  */
  if (!type ||
        0 == strncasecmp (type, TEXTHTML_S, strlen (TEXTHTML_S)) ||
        0 == strncasecmp (type, TEXTXHTML_S, strlen (TEXTXHTML_S)))
    *dt |= TEXTHTML;
  else
    *dt &= ~TEXTHTML;

  if (opt.html_extension && (*dt & TEXTHTML))
    /* -E / --html-extension / html_extension = on was specified, and this is a
       text/html file.  If some case-insensitive variation on ".htm[l]" isn't
       already the file's suffix, tack on ".html". */
    {
      char*  last_period_in_local_filename = strrchr(*hs->local_file, '.');

      if (last_period_in_local_filename == NULL ||
	  !(strcasecmp(last_period_in_local_filename, ".htm") == EQ ||
	    strcasecmp(last_period_in_local_filename, ".html") == EQ))
	{
	  size_t  local_filename_len = strlen(*hs->local_file);
	  
	  *hs->local_file = xrealloc(*hs->local_file,
				     local_filename_len + sizeof(".html"));
	  strcpy(*hs->local_file + local_filename_len, ".html");

	  *dt |= ADDED_HTML_EXTENSION;
	}
    }

  if (contrange == -1)
    {
      /* We did not get a content-range header.  This means that the
	 server did not honor our `Range' request.  Normally, this
	 means we should reset hs->restval and continue normally.  */

      /* However, if `-c' is used, we need to be a bit more careful:

         1. If `-c' is specified and the file already existed when
         Wget was started, it would be a bad idea for us to start
         downloading it from scratch, effectively truncating it.  I
         believe this cannot happen unless `-c' was specified.

	 2. If `-c' is used on a file that is already fully
	 downloaded, we're requesting bytes after the end of file,
	 which can result in server not honoring `Range'.  If this is
	 the case, `Content-Length' will be equal to the length of the
	 file.  */
      if (opt.always_rest)
	{
	  /* Check for condition #2. */
	  if (hs->restval > 0	            /* restart was requested. */
	      && contlen != -1              /* we got content-length. */
	      && hs->restval >= contlen     /* file fully downloaded
					       or has shrunk.  */
	      )
	    {
	      logputs (LOG_VERBOSE, _("\
\n    The file is already fully retrieved; nothing to do.\n\n"));
	      /* In case the caller inspects. */
	      hs->len = contlen;
	      hs->res = 0;
	      /* Mark as successfully retrieved. */
	      *dt |= RETROKF;
	      FREE_MAYBE (type);
	      FREE_MAYBE (all_headers);
	      CLOSE_INVALIDATE (sock);	/* would be CLOSE_FINISH, but there
					   might be more bytes in the body. */
	      return RETRUNNEEDED;
	    }

	  /* Check for condition #1. */
	  if (hs->no_truncate)
	    {
	      logprintf (LOG_NOTQUIET,
			 _("\
\n\
Continued download failed on this file, which conflicts with `-c'.\n\
Refusing to truncate existing file `%s'.\n\n"), *hs->local_file);
	      FREE_MAYBE (type);
	      FREE_MAYBE (all_headers);
	      CLOSE_INVALIDATE (sock);
	      return CONTNOTSUPPORTED;
	    }

	  /* Fallthrough */
	}

      hs->restval = 0;
    }
  else if (contrange != hs->restval ||
	   (H_PARTIAL (statcode) && contrange == -1))
    {
      /* This means the whole request was somehow misunderstood by the
	 server.  Bail out.  */
      FREE_MAYBE (type);
      FREE_MAYBE (all_headers);
      CLOSE_INVALIDATE (sock);
      return RANGEERR;
    }

  if (hs->restval)
    {
      if (contlen != -1)
	contlen += contrange;
      else
	contrange = -1;        /* If conent-length was not sent,
				  content-range will be ignored.  */
    }
  hs->contlen = contlen;

  if (opt.verbose)
    {
      if ((*dt & RETROKF) && !opt.server_response)
	{
	  /* No need to print this output if the body won't be
	     downloaded at all, or if the original server response is
	     printed.  */
	  logputs (LOG_VERBOSE, _("Length: "));
	  if (contlen != -1)
	    {
	      logputs (LOG_VERBOSE, legible (contlen));
	      if (contrange != -1)
		logprintf (LOG_VERBOSE, _(" (%s to go)"),
			   legible (contlen - contrange));
	    }
	  else
	    logputs (LOG_VERBOSE,
		     opt.ignore_length ? _("ignored") : _("unspecified"));
	  if (type)
	    logprintf (LOG_VERBOSE, " [%s]\n", type);
	  else
	    logputs (LOG_VERBOSE, "\n");
	}
    }
  FREE_MAYBE (type);
  type = NULL;			/* We don't need it any more.  */

  /* Return if we have no intention of further downloading.  */
  if (!(*dt & RETROKF) || (*dt & HEAD_ONLY))
    {
      /* In case the caller cares to look...  */
      hs->len = 0L;
      hs->res = 0;
      FREE_MAYBE (type);
      FREE_MAYBE (all_headers);
      CLOSE_INVALIDATE (sock);	/* would be CLOSE_FINISH, but there
				   might be more bytes in the body. */
      return RETRFINISHED;
    }

  /* Open the local file.  */
  if (!opt.dfp)
    {
      mkalldirs (*hs->local_file);
      if (opt.backups)
	rotate_backups (*hs->local_file);
      fp = fopen (*hs->local_file, hs->restval ? "ab" : "wb");
      if (!fp)
	{
	  logprintf (LOG_NOTQUIET, "%s: %s\n", *hs->local_file, strerror (errno));
	  CLOSE_INVALIDATE (sock); /* would be CLOSE_FINISH, but there
				      might be more bytes in the body. */
	  FREE_MAYBE (all_headers);
	  return FOPENERR;
	}
    }
  else				/* opt.dfp */
    {
      extern int global_download_count;
      fp = opt.dfp;
      /* To ensure that repeated "from scratch" downloads work for -O
	 files, we rewind the file pointer, unless restval is
	 non-zero.  (This works only when -O is used on regular files,
	 but it's still a valuable feature.)

	 However, this loses when more than one URL is specified on
	 the command line the second rewinds eradicates the contents
	 of the first download.  Thus we disable the above trick for
	 all the downloads except the very first one.

         #### A possible solution to this would be to remember the
	 file position in the output document and to seek to that
	 position, instead of rewinding.

         We don't truncate stdout, since that breaks
	 "wget -O - [...] >> foo".
      */
      if (!hs->restval && global_download_count == 0 && opt.dfp != stdout)
	{
	  /* This will silently fail for streams that don't correspond
	     to regular files, but that's OK.  */
	  rewind (fp);
	  /* ftruncate is needed because opt.dfp is opened in append
	     mode if opt.always_rest is set.  */
	  ftruncate (fileno (fp), 0);
	  clearerr (fp);
	}
    }

  /* #### This confuses the code that checks for file size.  There
     should be some overhead information.  */
  if (opt.save_headers)
    fwrite (all_headers, 1, all_length, fp);

  /* Get the contents of the document.  */
  hs->res = get_contents (sock, fp, &hs->len, hs->restval,
			  (contlen != -1 ? contlen : 0),
			  &rbuf, keep_alive, &hs->dltime);

  if (hs->res >= 0)
    CLOSE_FINISH (sock);
  else
    CLOSE_INVALIDATE (sock);

  {
    /* Close or flush the file.  We have to be careful to check for
       error here.  Checking the result of fwrite() is not enough --
       errors could go unnoticed!  */
    int flush_res;
    if (!opt.dfp)
      flush_res = fclose (fp);
    else
      flush_res = fflush (fp);
    if (flush_res == EOF)
      hs->res = -2;
  }
  FREE_MAYBE (all_headers);
  if (hs->res == -2)
    return FWRITEERR;
  return RETRFINISHED;
}

/* The genuine HTTP loop!  This is the part where the retrieval is
   retried, and retried, and retried, and...  */
uerr_t
http_loop (struct url *u, char **newloc, char **local_file, const char *referer,
	   int *dt, struct url *proxy)
{
  int count;
  int use_ts, got_head = 0;	/* time-stamping info */
  char *filename_plus_orig_suffix;
  char *local_filename = NULL;
  char *tms, *locf, *tmrate;
  uerr_t err;
  time_t tml = -1, tmr = -1;	/* local and remote time-stamps */
  long local_size = 0;		/* the size of the local file */
  size_t filename_len;
  struct http_stat hstat;	/* HTTP status */
  struct stat st;
  char *dummy = NULL;

  /* This used to be done in main(), but it's a better idea to do it
     here so that we don't go through the hoops if we're just using
     FTP or whatever. */
  if (opt.cookies)
    {
      if (!wget_cookie_jar)
	wget_cookie_jar = cookie_jar_new ();
      if (opt.cookies_input && !cookies_loaded_p)
	{
	  cookie_jar_load (wget_cookie_jar, opt.cookies_input);
	  cookies_loaded_p = 1;
	}
    }

  *newloc = NULL;

  /* Warn on (likely bogus) wildcard usage in HTTP.  Don't use
     has_wildcards_p because it would also warn on `?', and we know that
     shows up in CGI paths a *lot*.  */
  if (strchr (u->url, '*'))
    logputs (LOG_VERBOSE, _("Warning: wildcards not supported in HTTP.\n"));

  /* Determine the local filename.  */
  if (local_file && *local_file)
    hstat.local_file = local_file;
  else if (local_file)
    {
      *local_file = url_file_name (u);
      hstat.local_file = local_file;
    }
  else
    {
      dummy = url_file_name (u);
      hstat.local_file = &dummy;
    }

  if (!opt.output_document)
    locf = *hstat.local_file;
  else
    locf = opt.output_document;

  hstat.referer = referer;

  filename_len = strlen (*hstat.local_file);
  filename_plus_orig_suffix = alloca (filename_len + sizeof (".orig"));

  if (opt.noclobber && file_exists_p (*hstat.local_file))
    {
      /* If opt.noclobber is turned on and file already exists, do not
	 retrieve the file */
      logprintf (LOG_VERBOSE, _("\
File `%s' already there, will not retrieve.\n"), *hstat.local_file);
      /* If the file is there, we suppose it's retrieved OK.  */
      *dt |= RETROKF;

      /* #### Bogusness alert.  */
      /* If its suffix is "html" or "htm" or similar, assume text/html.  */
      if (has_html_suffix_p (*hstat.local_file))
	*dt |= TEXTHTML;

      FREE_MAYBE (dummy);
      return RETROK;
    }

  use_ts = 0;
  if (opt.timestamping)
    {
      boolean  local_dot_orig_file_exists = FALSE;

      if (opt.backup_converted)
	/* If -K is specified, we'll act on the assumption that it was specified
	   last time these files were downloaded as well, and instead of just
	   comparing local file X against server file X, we'll compare local
	   file X.orig (if extant, else X) against server file X.  If -K
	   _wasn't_ specified last time, or the server contains files called
	   *.orig, -N will be back to not operating correctly with -k. */
	{
	  /* Would a single s[n]printf() call be faster?  --dan

	     Definitely not.  sprintf() is horribly slow.  It's a
	     different question whether the difference between the two
	     affects a program.  Usually I'd say "no", but at one
	     point I profiled Wget, and found that a measurable and
	     non-negligible amount of time was lost calling sprintf()
	     in url.c.  Replacing sprintf with inline calls to
	     strcpy() and long_to_string() made a difference.
	     --hniksic */
	  memcpy (filename_plus_orig_suffix, *hstat.local_file, filename_len);
	  memcpy (filename_plus_orig_suffix + filename_len,
		  ".orig", sizeof (".orig"));

	  /* Try to stat() the .orig file. */
	  if (stat (filename_plus_orig_suffix, &st) == 0)
	    {
	      local_dot_orig_file_exists = TRUE;
	      local_filename = filename_plus_orig_suffix;
	    }
	}      

      if (!local_dot_orig_file_exists)
	/* Couldn't stat() <file>.orig, so try to stat() <file>. */
	if (stat (*hstat.local_file, &st) == 0)
	  local_filename = *hstat.local_file;

      if (local_filename != NULL)
	/* There was a local file, so we'll check later to see if the version
	   the server has is the same version we already have, allowing us to
	   skip a download. */
	{
	  use_ts = 1;
	  tml = st.st_mtime;
#ifdef WINDOWS
	  /* Modification time granularity is 2 seconds for Windows, so
	     increase local time by 1 second for later comparison. */
	  tml++;
#endif
	  local_size = st.st_size;
	  got_head = 0;
	}
    }
  /* Reset the counter.  */
  count = 0;
  *dt = 0 | ACCEPTRANGES;
  /* THE loop */
  do
    {
      /* Increment the pass counter.  */
      ++count;
      sleep_between_retrievals (count);
      /* Get the current time string.  */
      tms = time_str (NULL);
      /* Print fetch message, if opt.verbose.  */
      if (opt.verbose)
	{
	  char *hurl = url_string (u, 1);
	  char tmp[15];
	  strcpy (tmp, "        ");
	  if (count > 1)
	    sprintf (tmp, _("(try:%2d)"), count);
	  logprintf (LOG_VERBOSE, "--%s--  %s\n  %s => `%s'\n",
		     tms, hurl, tmp, locf);
#ifdef WINDOWS
	  ws_changetitle (hurl, 1);
#endif
	  xfree (hurl);
	}

      /* Default document type is empty.  However, if spider mode is
	 on or time-stamping is employed, HEAD_ONLY commands is
	 encoded within *dt.  */
      if (opt.spider || (use_ts && !got_head))
	*dt |= HEAD_ONLY;
      else
	*dt &= ~HEAD_ONLY;
      /* Assume no restarting.  */
      hstat.restval = 0L;
      /* Decide whether or not to restart.  */
      if (((count > 1 && (*dt & ACCEPTRANGES)) || opt.always_rest)
	  /* #### this calls access() and then stat(); could be optimized. */
	  && file_exists_p (locf))
	if (stat (locf, &st) == 0 && S_ISREG (st.st_mode))
	  hstat.restval = st.st_size;

      /* In `-c' is used and the file is existing and non-empty,
	 refuse to truncate it if the server doesn't support continued
	 downloads.  */
      hstat.no_truncate = 0;
      if (opt.always_rest && hstat.restval)
	hstat.no_truncate = 1;

      /* Decide whether to send the no-cache directive.  We send it in
	 two cases:
	   a) we're using a proxy, and we're past our first retrieval.
	      Some proxies are notorious for caching incomplete data, so
	      we require a fresh get.
	   b) caching is explicitly inhibited. */
      if ((proxy && count > 1)	/* a */
	  || !opt.allow_cache	/* b */
	  )
	*dt |= SEND_NOCACHE;
      else
	*dt &= ~SEND_NOCACHE;

      /* Try fetching the document, or at least its head.  */
      err = gethttp (u, &hstat, dt, proxy);

      /* It's unfortunate that wget determines the local filename before finding
	 out the Content-Type of the file.  Barring a major restructuring of the
	 code, we need to re-set locf here, since gethttp() may have xrealloc()d
	 *hstat.local_file to tack on ".html". */
      if (!opt.output_document)
	locf = *hstat.local_file;
      else
	locf = opt.output_document;

      /* Time?  */
      tms = time_str (NULL);
      /* Get the new location (with or without the redirection).  */
      if (hstat.newloc)
	*newloc = xstrdup (hstat.newloc);
      switch (err)
	{
	case HERR: case HEOF: case CONSOCKERR: case CONCLOSED:
	case CONERROR: case READERR: case WRITEFAILED:
	case RANGEERR:
	  /* Non-fatal errors continue executing the loop, which will
	     bring them to "while" statement at the end, to judge
	     whether the number of tries was exceeded.  */
	  free_hstat (&hstat);
	  printwhat (count, opt.ntry);
	  continue;
	  break;
	case HOSTERR: case CONREFUSED: case PROXERR: case AUTHFAILED: 
	case SSLERRCTXCREATE: case CONTNOTSUPPORTED:
	  /* Fatal errors just return from the function.  */
	  free_hstat (&hstat);
	  FREE_MAYBE (dummy);
	  return err;
	  break;
	case FWRITEERR: case FOPENERR:
	  /* Another fatal error.  */
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("Cannot write to `%s' (%s).\n"),
		     *hstat.local_file, strerror (errno));
	  free_hstat (&hstat);
	  FREE_MAYBE (dummy);
	  return err;
	  break;
	case CONSSLERR:
	  /* Another fatal error.  */
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("Unable to establish SSL connection.\n"));
	  free_hstat (&hstat);
	  FREE_MAYBE (dummy);
	  return err;
	  break;
	case NEWLOCATION:
	  /* Return the new location to the caller.  */
	  if (!hstat.newloc)
	    {
	      logprintf (LOG_NOTQUIET,
			 _("ERROR: Redirection (%d) without location.\n"),
			 hstat.statcode);
	      free_hstat (&hstat);
	      FREE_MAYBE (dummy);
	      return WRONGCODE;
	    }
	  free_hstat (&hstat);
	  FREE_MAYBE (dummy);
	  return NEWLOCATION;
	  break;
	case RETRUNNEEDED:
	  /* The file was already fully retrieved. */
	  free_hstat (&hstat);
	  FREE_MAYBE (dummy);
	  return RETROK;
	  break;
	case RETRFINISHED:
	  /* Deal with you later.  */
	  break;
	default:
	  /* All possibilities should have been exhausted.  */
	  abort ();
	}
      if (!(*dt & RETROKF))
	{
	  if (!opt.verbose)
	    {
	      /* #### Ugly ugly ugly! */
	      char *hurl = url_string (u, 1);
	      logprintf (LOG_NONVERBOSE, "%s:\n", hurl);
	      xfree (hurl);
	    }
	  logprintf (LOG_NOTQUIET, _("%s ERROR %d: %s.\n"),
		     tms, hstat.statcode, hstat.error);
	  logputs (LOG_VERBOSE, "\n");
	  free_hstat (&hstat);
	  FREE_MAYBE (dummy);
	  return WRONGCODE;
	}

      /* Did we get the time-stamp?  */
      if (!got_head)
	{
	  if (opt.timestamping && !hstat.remote_time)
	    {
	      logputs (LOG_NOTQUIET, _("\
Last-modified header missing -- time-stamps turned off.\n"));
	    }
	  else if (hstat.remote_time)
	    {
	      /* Convert the date-string into struct tm.  */
	      tmr = http_atotm (hstat.remote_time);
	      if (tmr == (time_t) (-1))
		logputs (LOG_VERBOSE, _("\
Last-modified header invalid -- time-stamp ignored.\n"));
	    }
	}

      /* The time-stamping section.  */
      if (use_ts)
	{
	  got_head = 1;
	  *dt &= ~HEAD_ONLY;
	  use_ts = 0;		/* no more time-stamping */
	  count = 0;		/* the retrieve count for HEAD is
				   reset */
	  if (hstat.remote_time && tmr != (time_t) (-1))
	    {
	      /* Now time-stamping can be used validly.  Time-stamping
		 means that if the sizes of the local and remote file
		 match, and local file is newer than the remote file,
		 it will not be retrieved.  Otherwise, the normal
		 download procedure is resumed.  */
	      if (tml >= tmr &&
		  (hstat.contlen == -1 || local_size == hstat.contlen))
		{
		  logprintf (LOG_VERBOSE, _("\
Server file no newer than local file `%s' -- not retrieving.\n\n"),
			     local_filename);
		  free_hstat (&hstat);
		  FREE_MAYBE (dummy);
		  return RETROK;
		}
	      else if (tml >= tmr)
		logprintf (LOG_VERBOSE, _("\
The sizes do not match (local %ld) -- retrieving.\n"), local_size);
	      else
		logputs (LOG_VERBOSE,
			 _("Remote file is newer, retrieving.\n"));
	    }
	  free_hstat (&hstat);
	  continue;
	}
      if ((tmr != (time_t) (-1))
	  && !opt.spider
	  && ((hstat.len == hstat.contlen) ||
	      ((hstat.res == 0) &&
	       ((hstat.contlen == -1) ||
		(hstat.len >= hstat.contlen && !opt.kill_longer)))))
	{
	  /* #### This code repeats in http.c and ftp.c.  Move it to a
             function!  */
	  const char *fl = NULL;
	  if (opt.output_document)
	    {
	      if (opt.od_known_regular)
		fl = opt.output_document;
	    }
	  else
	    fl = *hstat.local_file;
	  if (fl)
	    touch (fl, tmr);
	}
      /* End of time-stamping section.  */

      if (opt.spider)
	{
	  logprintf (LOG_NOTQUIET, "%d %s\n\n", hstat.statcode, hstat.error);
	  FREE_MAYBE (dummy);
	  return RETROK;
	}

      tmrate = retr_rate (hstat.len - hstat.restval, hstat.dltime, 0);

      if (hstat.len == hstat.contlen)
	{
	  if (*dt & RETROKF)
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - `%s' saved [%ld/%ld]\n\n"),
			 tms, tmrate, locf, hstat.len, hstat.contlen);
	      logprintf (LOG_NONVERBOSE,
			 "%s URL:%s [%ld/%ld] -> \"%s\" [%d]\n",
			 tms, u->url, hstat.len, hstat.contlen, locf, count);
	    }
	  ++opt.numurls;
	  total_downloaded_bytes += hstat.len;

	  /* Remember that we downloaded the file for later ".orig" code. */
	  if (*dt & ADDED_HTML_EXTENSION)
	    downloaded_file(FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED, locf);
	  else
	    downloaded_file(FILE_DOWNLOADED_NORMALLY, locf);

	  free_hstat (&hstat);
	  FREE_MAYBE (dummy);
	  return RETROK;
	}
      else if (hstat.res == 0) /* No read error */
	{
	  if (hstat.contlen == -1)  /* We don't know how much we were supposed
				       to get, so assume we succeeded. */ 
	    {
	      if (*dt & RETROKF)
		{
		  logprintf (LOG_VERBOSE,
			     _("%s (%s) - `%s' saved [%ld]\n\n"),
			     tms, tmrate, locf, hstat.len);
		  logprintf (LOG_NONVERBOSE,
			     "%s URL:%s [%ld] -> \"%s\" [%d]\n",
			     tms, u->url, hstat.len, locf, count);
		}
	      ++opt.numurls;
	      total_downloaded_bytes += hstat.len;

	      /* Remember that we downloaded the file for later ".orig" code. */
	      if (*dt & ADDED_HTML_EXTENSION)
		downloaded_file(FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED, locf);
	      else
		downloaded_file(FILE_DOWNLOADED_NORMALLY, locf);
	      
	      free_hstat (&hstat);
	      FREE_MAYBE (dummy);
	      return RETROK;
	    }
	  else if (hstat.len < hstat.contlen) /* meaning we lost the
						 connection too soon */
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - Connection closed at byte %ld. "),
			 tms, tmrate, hstat.len);
	      printwhat (count, opt.ntry);
	      free_hstat (&hstat);
	      continue;
	    }
	  else if (!opt.kill_longer) /* meaning we got more than expected */
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - `%s' saved [%ld/%ld])\n\n"),
			 tms, tmrate, locf, hstat.len, hstat.contlen);
	      logprintf (LOG_NONVERBOSE,
			 "%s URL:%s [%ld/%ld] -> \"%s\" [%d]\n",
			 tms, u->url, hstat.len, hstat.contlen, locf, count);
	      ++opt.numurls;
	      total_downloaded_bytes += hstat.len;

	      /* Remember that we downloaded the file for later ".orig" code. */
	      if (*dt & ADDED_HTML_EXTENSION)
		downloaded_file(FILE_DOWNLOADED_AND_HTML_EXTENSION_ADDED, locf);
	      else
		downloaded_file(FILE_DOWNLOADED_NORMALLY, locf);
	      
	      free_hstat (&hstat);
	      FREE_MAYBE (dummy);
	      return RETROK;
	    }
	  else			/* the same, but not accepted */
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - Connection closed at byte %ld/%ld. "),
			 tms, tmrate, hstat.len, hstat.contlen);
	      printwhat (count, opt.ntry);
	      free_hstat (&hstat);
	      continue;
	    }
	}
      else			/* now hstat.res can only be -1 */
	{
	  if (hstat.contlen == -1)
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - Read error at byte %ld (%s)."),
			 tms, tmrate, hstat.len, strerror (errno));
	      printwhat (count, opt.ntry);
	      free_hstat (&hstat);
	      continue;
	    }
	  else			/* hstat.res == -1 and contlen is given */
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - Read error at byte %ld/%ld (%s). "),
			 tms, tmrate, hstat.len, hstat.contlen,
			 strerror (errno));
	      printwhat (count, opt.ntry);
	      free_hstat (&hstat);
	      continue;
	    }
	}
      /* not reached */
      break;
    }
  while (!opt.ntry || (count < opt.ntry));
  return TRYLIMEXC;
}

/* Converts struct tm to time_t, assuming the data in tm is UTC rather
   than local timezone.

   mktime is similar but assumes struct tm, also known as the
   "broken-down" form of time, is in local time zone.  mktime_from_utc
   uses mktime to make the conversion understanding that an offset
   will be introduced by the local time assumption.

   mktime_from_utc then measures the introduced offset by applying
   gmtime to the initial result and applying mktime to the resulting
   "broken-down" form.  The difference between the two mktime results
   is the measured offset which is then subtracted from the initial
   mktime result to yield a calendar time which is the value returned.

   tm_isdst in struct tm is set to 0 to force mktime to introduce a
   consistent offset (the non DST offset) since tm and tm+o might be
   on opposite sides of a DST change.

   Some implementations of mktime return -1 for the nonexistent
   localtime hour at the beginning of DST.  In this event, use
   mktime(tm - 1hr) + 3600.

   Schematically
     mktime(tm)   --> t+o
     gmtime(t+o)  --> tm+o
     mktime(tm+o) --> t+2o
     t+o - (t+2o - t+o) = t

   Note that glibc contains a function of the same purpose named
   `timegm' (reverse of gmtime).  But obviously, it is not universally
   available, and unfortunately it is not straightforwardly
   extractable for use here.  Perhaps configure should detect timegm
   and use it where available.

   Contributed by Roger Beeman <beeman@cisco.com>, with the help of
   Mark Baushke <mdb@cisco.com> and the rest of the Gurus at CISCO.
   Further improved by Roger with assistance from Edward J. Sabol
   based on input by Jamie Zawinski.  */

static time_t
mktime_from_utc (struct tm *t)
{
  time_t tl, tb;
  struct tm *tg;

  tl = mktime (t);
  if (tl == -1)
    {
      t->tm_hour--;
      tl = mktime (t);
      if (tl == -1)
	return -1; /* can't deal with output from strptime */
      tl += 3600;
    }
  tg = gmtime (&tl);
  tg->tm_isdst = 0;
  tb = mktime (tg);
  if (tb == -1)
    {
      tg->tm_hour--;
      tb = mktime (tg);
      if (tb == -1)
	return -1; /* can't deal with output from gmtime */
      tb += 3600;
    }
  return (tl - (tb - tl));
}

/* Check whether the result of strptime() indicates success.
   strptime() returns the pointer to how far it got to in the string.
   The processing has been successful if the string is at `GMT' or
   `+X', or at the end of the string.

   In extended regexp parlance, the function returns 1 if P matches
   "^ *(GMT|[+-][0-9]|$)", 0 otherwise.  P being NULL (which strptime
   can return) is considered a failure and 0 is returned.  */
static int
check_end (const char *p)
{
  if (!p)
    return 0;
  while (ISSPACE (*p))
    ++p;
  if (!*p
      || (p[0] == 'G' && p[1] == 'M' && p[2] == 'T')
      || ((p[0] == '+' || p[0] == '-') && ISDIGIT (p[1])))
    return 1;
  else
    return 0;
}

/* Convert the textual specification of time in TIME_STRING to the
   number of seconds since the Epoch.

   TIME_STRING can be in any of the three formats RFC2068 allows the
   HTTP servers to emit -- RFC1123-date, RFC850-date or asctime-date.
   Timezones are ignored, and should be GMT.

   Return the computed time_t representation, or -1 if the conversion
   fails.

   This function uses strptime with various string formats for parsing
   TIME_STRING.  This results in a parser that is not as lenient in
   interpreting TIME_STRING as I would like it to be.  Being based on
   strptime, it always allows shortened months, one-digit days, etc.,
   but due to the multitude of formats in which time can be
   represented, an ideal HTTP time parser would be even more
   forgiving.  It should completely ignore things like week days and
   concentrate only on the various forms of representing years,
   months, days, hours, minutes, and seconds.  For example, it would
   be nice if it accepted ISO 8601 out of the box.

   I've investigated free and PD code for this purpose, but none was
   usable.  getdate was big and unwieldy, and had potential copyright
   issues, or so I was informed.  Dr. Marcus Hennecke's atotm(),
   distributed with phttpd, is excellent, but we cannot use it because
   it is not assigned to the FSF.  So I stuck it with strptime.  */

time_t
http_atotm (const char *time_string)
{
  /* NOTE: Solaris strptime man page claims that %n and %t match white
     space, but that's not universally available.  Instead, we simply
     use ` ' to mean "skip all WS", which works under all strptime
     implementations I've tested.  */

  static const char *time_formats[] = {
    "%a, %d %b %Y %T",		/* RFC1123: Thu, 29 Jan 1998 22:12:57 */
    "%A, %d-%b-%y %T",		/* RFC850:  Thursday, 29-Jan-98 22:12:57 */
    "%a, %d-%b-%Y %T",		/* pseudo-RFC850:  Thu, 29-Jan-1998 22:12:57
				   (google.com uses this for their cookies.) */
    "%a %b %d %T %Y"		/* asctime: Thu Jan 29 22:12:57 1998 */
  };

  int i;
  struct tm t;

  /* According to Roger Beeman, we need to initialize tm_isdst, since
     strptime won't do it.  */
  t.tm_isdst = 0;

  /* Note that under foreign locales Solaris strptime() fails to
     recognize English dates, which renders this function useless.  We
     solve this by being careful not to affect LC_TIME when
     initializing locale.

     Another solution would be to temporarily set locale to C, invoke
     strptime(), and restore it back.  This is slow and dirty,
     however, and locale support other than LC_MESSAGES can mess other
     things, so I rather chose to stick with just setting LC_MESSAGES.

     GNU strptime does not have this problem because it recognizes
     both international and local dates.  */

  for (i = 0; i < countof (time_formats); i++)
    if (check_end (strptime (time_string, time_formats[i], &t)))
      return mktime_from_utc (&t);

  /* All formats have failed.  */
  return -1;
}

/* Authorization support: We support two authorization schemes:

   * `Basic' scheme, consisting of base64-ing USER:PASSWORD string;

   * `Digest' scheme, added by Junio Hamano <junio@twinsun.com>,
   consisting of answering to the server's challenge with the proper
   MD5 digests.  */

/* How many bytes it will take to store LEN bytes in base64.  */
#define BASE64_LENGTH(len) (4 * (((len) + 2) / 3))

/* Encode the string S of length LENGTH to base64 format and place it
   to STORE.  STORE will be 0-terminated, and must point to a writable
   buffer of at least 1+BASE64_LENGTH(length) bytes.  */
static void
base64_encode (const char *s, char *store, int length)
{
  /* Conversion table.  */
  static char tbl[64] = {
    'A','B','C','D','E','F','G','H',
    'I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X',
    'Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n',
    'o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3',
    '4','5','6','7','8','9','+','/'
  };
  int i;
  unsigned char *p = (unsigned char *)store;

  /* Transform the 3x8 bits to 4x6 bits, as required by base64.  */
  for (i = 0; i < length; i += 3)
    {
      *p++ = tbl[s[0] >> 2];
      *p++ = tbl[((s[0] & 3) << 4) + (s[1] >> 4)];
      *p++ = tbl[((s[1] & 0xf) << 2) + (s[2] >> 6)];
      *p++ = tbl[s[2] & 0x3f];
      s += 3;
    }
  /* Pad the result if necessary...  */
  if (i == length + 1)
    *(p - 1) = '=';
  else if (i == length + 2)
    *(p - 1) = *(p - 2) = '=';
  /* ...and zero-terminate it.  */
  *p = '\0';
}

/* Create the authentication header contents for the `Basic' scheme.
   This is done by encoding the string `USER:PASS' in base64 and
   prepending `HEADER: Basic ' to it.  */
static char *
basic_authentication_encode (const char *user, const char *passwd,
			     const char *header)
{
  char *t1, *t2, *res;
  int len1 = strlen (user) + 1 + strlen (passwd);
  int len2 = BASE64_LENGTH (len1);

  t1 = (char *)alloca (len1 + 1);
  sprintf (t1, "%s:%s", user, passwd);
  t2 = (char *)alloca (1 + len2);
  base64_encode (t1, t2, len1);
  res = (char *)xmalloc (len2 + 11 + strlen (header));
  sprintf (res, "%s: Basic %s\r\n", header, t2);

  return res;
}

#ifdef USE_DIGEST
/* Parse HTTP `WWW-Authenticate:' header.  AU points to the beginning
   of a field in such a header.  If the field is the one specified by
   ATTR_NAME ("realm", "opaque", and "nonce" are used by the current
   digest authorization code), extract its value in the (char*)
   variable pointed by RET.  Returns negative on a malformed header,
   or number of bytes that have been parsed by this call.  */
static int
extract_header_attr (const char *au, const char *attr_name, char **ret)
{
  const char *cp, *ep;

  ep = cp = au;

  if (strncmp (cp, attr_name, strlen (attr_name)) == 0)
    {
      cp += strlen (attr_name);
      if (!*cp)
	return -1;
      cp += skip_lws (cp);
      if (*cp != '=')
	return -1;
      if (!*++cp)
	return -1;
      cp += skip_lws (cp);
      if (*cp != '\"')
	return -1;
      if (!*++cp)
	return -1;
      for (ep = cp; *ep && *ep != '\"'; ep++)
	;
      if (!*ep)
	return -1;
      FREE_MAYBE (*ret);
      *ret = strdupdelim (cp, ep);
      return ep - au + 1;
    }
  else
    return 0;
}

/* Dump the hexadecimal representation of HASH to BUF.  HASH should be
   an array of 16 bytes containing the hash keys, and BUF should be a
   buffer of 33 writable characters (32 for hex digits plus one for
   zero termination).  */
static void
dump_hash (unsigned char *buf, const unsigned char *hash)
{
  int i;

  for (i = 0; i < MD5_HASHLEN; i++, hash++)
    {
      *buf++ = XNUM_TO_digit (*hash >> 4);
      *buf++ = XNUM_TO_digit (*hash & 0xf);
    }
  *buf = '\0';
}

/* Take the line apart to find the challenge, and compose a digest
   authorization header.  See RFC2069 section 2.1.2.  */
static char *
digest_authentication_encode (const char *au, const char *user,
			      const char *passwd, const char *method,
			      const char *path)
{
  static char *realm, *opaque, *nonce;
  static struct {
    const char *name;
    char **variable;
  } options[] = {
    { "realm", &realm },
    { "opaque", &opaque },
    { "nonce", &nonce }
  };
  char *res;

  realm = opaque = nonce = NULL;

  au += 6;			/* skip over `Digest' */
  while (*au)
    {
      int i;

      au += skip_lws (au);
      for (i = 0; i < countof (options); i++)
	{
	  int skip = extract_header_attr (au, options[i].name,
					  options[i].variable);
	  if (skip < 0)
	    {
	      FREE_MAYBE (realm);
	      FREE_MAYBE (opaque);
	      FREE_MAYBE (nonce);
	      return NULL;
	    }
	  else if (skip)
	    {
	      au += skip;
	      break;
	    }
	}
      if (i == countof (options))
	{
	  while (*au && *au != '=')
	    au++;
	  if (*au && *++au)
	    {
	      au += skip_lws (au);
	      if (*au == '\"')
		{
		  au++;
		  while (*au && *au != '\"')
		    au++;
		  if (*au)
		    au++;
		}
	    }
	}
      while (*au && *au != ',')
	au++;
      if (*au)
	au++;
    }
  if (!realm || !nonce || !user || !passwd || !path || !method)
    {
      FREE_MAYBE (realm);
      FREE_MAYBE (opaque);
      FREE_MAYBE (nonce);
      return NULL;
    }

  /* Calculate the digest value.  */
  {
    ALLOCA_MD5_CONTEXT (ctx);
    unsigned char hash[MD5_HASHLEN];
    unsigned char a1buf[MD5_HASHLEN * 2 + 1], a2buf[MD5_HASHLEN * 2 + 1];
    unsigned char response_digest[MD5_HASHLEN * 2 + 1];

    /* A1BUF = H(user ":" realm ":" password) */
    gen_md5_init (ctx);
    gen_md5_update ((unsigned char *)user, strlen (user), ctx);
    gen_md5_update ((unsigned char *)":", 1, ctx);
    gen_md5_update ((unsigned char *)realm, strlen (realm), ctx);
    gen_md5_update ((unsigned char *)":", 1, ctx);
    gen_md5_update ((unsigned char *)passwd, strlen (passwd), ctx);
    gen_md5_finish (ctx, hash);
    dump_hash (a1buf, hash);

    /* A2BUF = H(method ":" path) */
    gen_md5_init (ctx);
    gen_md5_update ((unsigned char *)method, strlen (method), ctx);
    gen_md5_update ((unsigned char *)":", 1, ctx);
    gen_md5_update ((unsigned char *)path, strlen (path), ctx);
    gen_md5_finish (ctx, hash);
    dump_hash (a2buf, hash);

    /* RESPONSE_DIGEST = H(A1BUF ":" nonce ":" A2BUF) */
    gen_md5_init (ctx);
    gen_md5_update (a1buf, MD5_HASHLEN * 2, ctx);
    gen_md5_update ((unsigned char *)":", 1, ctx);
    gen_md5_update ((unsigned char *)nonce, strlen (nonce), ctx);
    gen_md5_update ((unsigned char *)":", 1, ctx);
    gen_md5_update (a2buf, MD5_HASHLEN * 2, ctx);
    gen_md5_finish (ctx, hash);
    dump_hash (response_digest, hash);

    res = (char*) xmalloc (strlen (user)
			   + strlen (user)
			   + strlen (realm)
			   + strlen (nonce)
			   + strlen (path)
			   + 2 * MD5_HASHLEN /*strlen (response_digest)*/
			   + (opaque ? strlen (opaque) : 0)
			   + 128);
    sprintf (res, "Authorization: Digest \
username=\"%s\", realm=\"%s\", nonce=\"%s\", uri=\"%s\", response=\"%s\"",
	     user, realm, nonce, path, response_digest);
    if (opaque)
      {
	char *p = res + strlen (res);
	strcat (p, ", opaque=\"");
	strcat (p, opaque);
	strcat (p, "\"");
      }
    strcat (res, "\r\n");
  }
  return res;
}
#endif /* USE_DIGEST */


#define BEGINS_WITH(line, string_constant)				\
  (!strncasecmp (line, string_constant, sizeof (string_constant) - 1)	\
   && (ISSPACE (line[sizeof (string_constant) - 1])			\
       || !line[sizeof (string_constant) - 1]))

static int
known_authentication_scheme_p (const char *au)
{
  return BEGINS_WITH (au, "Basic")
    || BEGINS_WITH (au, "Digest")
    || BEGINS_WITH (au, "NTLM");
}

#undef BEGINS_WITH

/* Create the HTTP authorization request header.  When the
   `WWW-Authenticate' response header is seen, according to the
   authorization scheme specified in that header (`Basic' and `Digest'
   are supported by the current implementation), produce an
   appropriate HTTP authorization request header.  */
static char *
create_authorization_line (const char *au, const char *user,
			   const char *passwd, const char *method,
			   const char *path)
{
  char *wwwauth = NULL;

  if (!strncasecmp (au, "Basic", 5))
    wwwauth = basic_authentication_encode (user, passwd, "Authorization");
  if (!strncasecmp (au, "NTLM", 4))
    wwwauth = basic_authentication_encode (user, passwd, "Authorization");
#ifdef USE_DIGEST
  else if (!strncasecmp (au, "Digest", 6))
    wwwauth = digest_authentication_encode (au, user, passwd, method, path);
#endif /* USE_DIGEST */
  return wwwauth;
}

void
http_cleanup (void)
{
  if (pc_last_host_ip)
    address_list_release (pc_last_host_ip);
}
