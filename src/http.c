/* HTTP support.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif
#include <ctype.h>
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

#ifdef WINDOWS
# include <winsock.h>
#endif

#include "wget.h"
#include "utils.h"
#include "url.h"
#include "host.h"
#include "rbuf.h"
#include "retr.h"
#include "headers.h"
#include "connect.h"
#include "fnmatch.h"
#include "netrc.h"
#if USE_DIGEST
# include "md5.h"
#endif

extern char *version_string;

#ifndef errno
extern int errno;
#endif
#ifndef h_errno
extern int h_errno;
#endif


#define TEXTHTML_S "text/html"
#define HTTP_ACCEPT "*/*"

/* Some status code validation macros: */
#define H_20X(x)        (((x) >= 200) && ((x) < 300))
#define H_PARTIAL(x)    ((x) == HTTP_STATUS_PARTIAL_CONTENTS)
#define H_REDIRECTED(x) (((x) == HTTP_STATUS_MOVED_PERMANENTLY)	\
			 || ((x) == HTTP_STATUS_MOVED_TEMPORARILY))

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
  char *p;

  *result = xstrdup (hdr);
  p = strrchr (hdr, ';');
  if (p)
    {
      int len = p - hdr;
      *result = (char *)xmalloc (len + 1);
      memcpy (*result, hdr, len);
      (*result)[len] = '\0';
    }
  else
    *result = xstrdup (hdr);
  return 1;
}


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
  long dltime;			/* time of the download */
};

/* Free the elements of hstat X.  */
#define FREEHSTAT(x) do					\
{							\
  FREE_MAYBE ((x).newloc);				\
  FREE_MAYBE ((x).remote_time);				\
  FREE_MAYBE ((x).error);				\
  (x).newloc = (x).remote_time = (x).error = NULL;	\
} while (0)

static char *create_authorization_line PARAMS ((const char *, const char *,
						const char *, const char *,
						const char *));
static char *basic_authentication_encode PARAMS ((const char *, const char *,
						  const char *));
static int known_authentication_scheme_p PARAMS ((const char *));

static time_t http_atotm PARAMS ((char *));

/* Retrieve a document through HTTP protocol.  It recognizes status
   code, and correctly handles redirections.  It closes the network
   socket.  If it receives an error from the functions below it, it
   will print it if there is enough information to do so (almost
   always), returning the error to the caller (i.e. http_loop).

   Various HTTP parameters are stored to hs.  Although it parses the
   response code correctly, it is not used in a sane way.  The caller
   can do that, though.

   If u->proxy is non-NULL, the URL u will be taken as a proxy URL,
   and u->proxy->url will be given to the proxy server (bad naming,
   I'm afraid).  */
static uerr_t
gethttp (struct urlinfo *u, struct http_stat *hs, int *dt)
{
  char *request, *type, *command, *path;
  char *user, *passwd;
  char *pragma_h, *referer, *useragent, *range, *wwwauth, *remhost;
  char *authenticate_h;
  char *proxyauth;
  char *all_headers;
  int sock, hcount, num_written, all_length, remport, statcode;
  long contlen, contrange;
  struct urlinfo *ou;
  uerr_t err;
  FILE *fp;
  int auth_tried_already;
  struct rbuf rbuf;

  /* Let the others worry about local filename...  */
  if (!(*dt & HEAD_ONLY))
    assert (u->local != NULL);

  authenticate_h = 0;
  auth_tried_already = 0;

 again:
  /* We need to come back here when the initial attempt to retrieve
     without authorization header fails.  */

  /* Initialize certain elements of struct hstat.  */
  hs->len = 0L;
  hs->contlen = -1;
  hs->res = -1;
  hs->newloc = NULL;
  hs->remote_time = NULL;
  hs->error = NULL;

  /* Which structure to use to retrieve the original URL data.  */
  if (u->proxy)
    ou = u->proxy;
  else
    ou = u;

  /* First: establish the connection.  */
  logprintf (LOG_VERBOSE, _("Connecting to %s:%hu... "), u->host, u->port);
  err = make_connection (&sock, u->host, u->port);
  switch (err)
    {
    case HOSTERR:
      logputs (LOG_VERBOSE, "\n");
      logprintf (LOG_NOTQUIET, "%s: %s.\n", u->host, herrmsg (h_errno));
      return HOSTERR;
      break;
    case CONSOCKERR:
      logputs (LOG_VERBOSE, "\n");
      logprintf (LOG_NOTQUIET, "socket: %s\n", strerror (errno));
      return CONSOCKERR;
      break;
    case CONREFUSED:
      logputs (LOG_VERBOSE, "\n");
      logprintf (LOG_NOTQUIET,
		 _("Connection to %s:%hu refused.\n"), u->host, u->port);
      CLOSE (sock);
      return CONREFUSED;
    case CONERROR:
      logputs (LOG_VERBOSE, "\n");
      logprintf (LOG_NOTQUIET, "connect: %s\n", strerror (errno));
      CLOSE (sock);
      return CONERROR;
      break;
    case NOCONERROR:
      /* Everything is fine!  */
      logputs (LOG_VERBOSE, _("connected!\n"));
      break;
    default:
      abort ();
      break;
    } /* switch */

  if (u->proxy)
    path = u->proxy->url;
  else
    path = u->path;
  command = (*dt & HEAD_ONLY) ? "HEAD" : "GET";
  referer = NULL;
  if (ou->referer)
    {
      referer = (char *)alloca (9 + strlen (ou->referer) + 3);
      sprintf (referer, "Referer: %s\r\n", ou->referer);
    }
  if (*dt & SEND_NOCACHE)
    pragma_h = "Pragma: no-cache\r\n";
  else
    pragma_h = "";
  if (hs->restval)
    {
      range = (char *)alloca (13 + numdigit (hs->restval) + 4);
      /* #### Gag me!  Some servers (e.g. WebSitePro) have been known
         to misinterpret the following `Range' format, and return the
         document as multipart/x-byte-ranges MIME type!

	 #### TODO: Interpret MIME types, recognize bullshits similar
	 the one described above, and deal with them!  */
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
  user = ou->user;
  passwd = ou->passwd;
  search_netrc (u->host, (const char **)&user, (const char **)&passwd, 0);
  user = user ? user : opt.http_user;
  passwd = passwd ? passwd : opt.http_passwd;

  wwwauth = NULL;
  if (authenticate_h && user && passwd)
    {
      wwwauth = create_authorization_line (authenticate_h, user, passwd,
					   command, ou->path);
    }

  proxyauth = NULL;
  if (u->proxy)
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
	  proxy_user = u->user;
	  proxy_passwd = u->passwd;
	}
      /* #### This is junky.  Can't the proxy request, say, `Digest'
         authentication?  */
      if (proxy_user && proxy_passwd)
	proxyauth = basic_authentication_encode (proxy_user, proxy_passwd,
						 "Proxy-Authorization");
    }
  remhost = ou->host;
  remport = ou->port;
  /* Allocate the memory for the request.  */
  request = (char *)alloca (strlen (command) + strlen (path)
			    + strlen (useragent)
			    + strlen (remhost) + numdigit (remport)
			    + strlen (HTTP_ACCEPT)
			    + (referer ? strlen (referer) : 0)
			    + (wwwauth ? strlen (wwwauth) : 0)
			    + (proxyauth ? strlen (proxyauth) : 0)
			    + (range ? strlen (range) : 0)
			    + strlen (pragma_h)
			    + (opt.user_header ? strlen (opt.user_header) : 0)
			    + 64);
  /* Construct the request.  */
  sprintf (request, "\
%s %s HTTP/1.0\r\n\
User-Agent: %s\r\n\
Host: %s:%d\r\n\
Accept: %s\r\n\
%s%s%s%s%s%s\r\n",
	  command, path, useragent, remhost, remport, HTTP_ACCEPT, 
	  referer ? referer : "", 
	  wwwauth ? wwwauth : "", 
	  proxyauth ? proxyauth : "", 
	  range ? range : "",
	  pragma_h, 
	  opt.user_header ? opt.user_header : "");
  DEBUGP (("---request begin---\n%s---request end---\n", request));
   /* Free the temporary memory.  */
  FREE_MAYBE (wwwauth);
  FREE_MAYBE (proxyauth);

  /* Send the request to server.  */
  num_written = iwrite (sock, request, strlen (request));
  if (num_written < 0)
    {
      logputs (LOG_VERBOSE, _("Failed writing HTTP request.\n"));
      free (request);
      CLOSE (sock);
      return WRITEFAILED;
    }
  logprintf (LOG_VERBOSE, _("%s request sent, awaiting response... "),
	     u->proxy ? "Proxy" : "HTTP");
  contlen = contrange = -1;
  type = NULL;
  statcode = -1;
  *dt &= ~RETROKF;

  /* Before reading anything, initialize the rbuf.  */
  rbuf_initialize (&rbuf, sock);

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
	  free (hdr);
	  FREE_MAYBE (type);
	  FREE_MAYBE (hs->newloc);
	  FREE_MAYBE (all_headers);
	  CLOSE (sock);
	  return HEOF;
	}
      else if (status == HG_ERROR)
	{
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("Read error (%s) in headers.\n"),
		     strerror (errno));
	  free (hdr);
	  FREE_MAYBE (type);
	  FREE_MAYBE (hs->newloc);
	  FREE_MAYBE (all_headers);
	  CLOSE (sock);
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

      /* Print the header if requested.  */
      if (opt.server_response && hcount != 1)
	logprintf (LOG_VERBOSE, "\n%d %s", hcount, hdr);

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
	      free (hdr);
	      break;
	    }
	  else if (!*error)
	    hs->error = xstrdup (_("(no description)"));
	  else
	    hs->error = xstrdup (error);

	  if ((statcode != -1)
#ifdef DEBUG
	      && !opt.debug
#endif
	      )
	    logprintf (LOG_VERBOSE, "%d %s", statcode, error);

	  goto done_header;
	}

      /* Exit on empty header.  */
      if (!*hdr)
	{
	  free (hdr);
	  break;
	}

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
    done_header:
      free (hdr);
    }

  logputs (LOG_VERBOSE, "\n");

  if ((statcode == HTTP_STATUS_UNAUTHORIZED)
      && authenticate_h)
    {
      /* Authorization is required.  */
      FREE_MAYBE (type);
      type = NULL;
      FREEHSTAT (*hs);
      CLOSE (sock);
      if (auth_tried_already)
	{
	  /* If we have tried it already, then there is not point
	     retrying it.  */
	  logputs (LOG_NOTQUIET, _("Authorization failed.\n"));
	  free (authenticate_h);
	  return AUTHFAILED;
	}
      else if (!known_authentication_scheme_p (authenticate_h))
	{
	  free (authenticate_h);
	  logputs (LOG_NOTQUIET, _("Unknown authentication scheme.\n"));
	  return AUTHFAILED;
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
      free (authenticate_h);
      authenticate_h = NULL;
    }

  /* 20x responses are counted among successful by default.  */
  if (H_20X (statcode))
    *dt |= RETROKF;

  if (type && !strncasecmp (type, TEXTHTML_S, strlen (TEXTHTML_S)))
    *dt |= TEXTHTML;
  else
    /* We don't assume text/html by default.  */
    *dt &= ~TEXTHTML;

  if (contrange == -1)
    hs->restval = 0;
  else if (contrange != hs->restval ||
	   (H_PARTIAL (statcode) && contrange == -1))
    {
      /* This means the whole request was somehow misunderstood by the
	 server.  Bail out.  */
      FREE_MAYBE (type);
      FREE_MAYBE (hs->newloc);
      FREE_MAYBE (all_headers);
      CLOSE (sock);
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
	  CLOSE (sock);
	  FREE_MAYBE (type);
	  FREE_MAYBE (all_headers);
	  return NEWLOCATION;
	}
    }
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
      /* In case someone cares to look...  */
      hs->len = 0L;
      hs->res = 0;
      FREE_MAYBE (type);
      FREE_MAYBE (all_headers);
      CLOSE (sock);
      return RETRFINISHED;
    }

  /* Open the local file.  */
  if (!opt.dfp)
    {
      mkalldirs (u->local);
      if (opt.backups)
	rotate_backups (u->local);
      fp = fopen (u->local, hs->restval ? "ab" : "wb");
      if (!fp)
	{
	  logprintf (LOG_NOTQUIET, "%s: %s\n", u->local, strerror (errno));
	  CLOSE (sock);
	  FREE_MAYBE (all_headers);
	  return FOPENERR;
	}
    }
  else                      /* opt.dfp */
    fp = opt.dfp;

  /* #### This confuses the code that checks for file size.  There
     should be some overhead information.  */
  if (opt.save_headers)
    fwrite (all_headers, 1, all_length, fp);
  reset_timer ();
  /* Get the contents of the document.  */
  hs->res = get_contents (sock, fp, &hs->len, hs->restval,
			  (contlen != -1 ? contlen : 0),
			  &rbuf);
  hs->dltime = elapsed_time ();
  if (!opt.dfp)
    fclose (fp);
  else
    fflush (fp);
  FREE_MAYBE (all_headers);
  CLOSE (sock);
  if (hs->res == -2)
    return FWRITEERR;
  return RETRFINISHED;
}

/* The genuine HTTP loop!  This is the part where the retrieval is
   retried, and retried, and retried, and...  */
uerr_t
http_loop (struct urlinfo *u, char **newloc, int *dt)
{
  static int first_retrieval = 1;

  int count;
  int use_ts, got_head = 0;	/* time-stamping info */
  char *tms, *suf, *locf, *tmrate;
  uerr_t err;
  time_t tml = -1, tmr = -1;	/* local and remote time-stamps */
  long local_size = 0;		/* the size of the local file */
  struct http_stat hstat;	/* HTTP status */
  struct stat st;

  *newloc = NULL;

  /* Warn on (likely bogus) wildcard usage in HTTP.  Don't use
     has_wildcards_p because it would also warn on `?', and we that
     shows up in CGI paths a *lot*.  */
  if (strchr (u->url, '*'))
    logputs (LOG_VERBOSE, _("Warning: wildcards not supported in HTTP.\n"));

  /* Determine the local filename.  */
  if (!u->local)
    u->local = url_filename (u->proxy ? u->proxy : u);

  if (!opt.output_document)
    locf = u->local;
  else
    locf = opt.output_document;

  if (opt.noclobber && file_exists_p (u->local))
    {
      /* If opt.noclobber is turned on and file already exists, do not
	 retrieve the file */
      logprintf (LOG_VERBOSE, _("\
File `%s' already there, will not retrieve.\n"), u->local);
      /* If the file is there, we suppose it's retrieved OK.  */
      *dt |= RETROKF;

      /* #### Bogusness alert.  */
      /* If its suffix is "html" or (yuck!) "htm", we suppose it's
	 text/html, a harmless lie.  */
      if (((suf = suffix (u->local)) != NULL)
	  && (!strcmp (suf, "html") || !strcmp (suf, "htm")))
	*dt |= TEXTHTML;
      free (suf);
      /* Another harmless lie: */
      return RETROK;
    }

  use_ts = 0;
  if (opt.timestamping)
    {
      if (stat (u->local, &st) == 0)
	{
	  use_ts = 1;
	  tml = st.st_mtime;
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
      /* Wait before the retrieval (unless this is the very first
	 retrieval).  */
      if (!first_retrieval && opt.wait)
	sleep (opt.wait);
      if (first_retrieval)
	first_retrieval = 0;
      /* Get the current time string.  */
      tms = time_str (NULL);
      /* Print fetch message, if opt.verbose.  */
      if (opt.verbose)
	{
	  char *hurl = str_url (u->proxy ? u->proxy : u, 1);
	  char tmp[15];
	  strcpy (tmp, "        ");
	  if (count > 1)
	    sprintf (tmp, _("(try:%2d)"), count);
	  logprintf (LOG_VERBOSE, "--%s--  %s\n  %s => `%s'\n",
		     tms, hurl, tmp, locf);
#ifdef WINDOWS
	  ws_changetitle (hurl, 1);
#endif
	  free (hurl);
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
	  && file_exists_p (u->local))
	if (stat (u->local, &st) == 0)
	  hstat.restval = st.st_size;
      /* Decide whether to send the no-cache directive.  */
      if (u->proxy && (count > 1 || (opt.proxy_cache == 0)))
	*dt |= SEND_NOCACHE;
      else
	*dt &= ~SEND_NOCACHE;

      /* Try fetching the document, or at least its head.  :-) */
      err = gethttp (u, &hstat, dt);
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
	  FREEHSTAT (hstat);
	  printwhat (count, opt.ntry);
	  continue;
	  break;
	case HOSTERR: case CONREFUSED: case PROXERR: case AUTHFAILED:
	  /* Fatal errors just return from the function.  */
	  FREEHSTAT (hstat);
	  return err;
	  break;
	case FWRITEERR: case FOPENERR:
	  /* Another fatal error.  */
	  logputs (LOG_VERBOSE, "\n");
	  logprintf (LOG_NOTQUIET, _("Cannot write to `%s' (%s).\n"),
		     u->local, strerror (errno));
	  FREEHSTAT (hstat);
	  return err;
	  break;
	case NEWLOCATION:
	  /* Return the new location to the caller.  */
	  if (!hstat.newloc)
	    {
	      logprintf (LOG_NOTQUIET,
			 _("ERROR: Redirection (%d) without location.\n"),
			 hstat.statcode);
	      return WRONGCODE;
	    }
	  FREEHSTAT (hstat);
	  return NEWLOCATION;
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
	      char *hurl = str_url (u->proxy ? u->proxy : u, 1);
	      logprintf (LOG_NONVERBOSE, "%s:\n", hurl);
	      free (hurl);
	    }
	  logprintf (LOG_NOTQUIET, _("%s ERROR %d: %s.\n"),
		     tms, hstat.statcode, hstat.error);
	  logputs (LOG_VERBOSE, "\n");
	  FREEHSTAT (hstat);
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
Local file `%s' is more recent, not retrieving.\n\n"), u->local);
		  FREEHSTAT (hstat);
		  return RETROK;
		}
	      else if (tml >= tmr)
		logprintf (LOG_VERBOSE, _("\
The sizes do not match (local %ld), retrieving.\n"), local_size);
	      else
		logputs (LOG_VERBOSE,
			 _("Remote file is newer, retrieving.\n"));
	    }
	  FREEHSTAT (hstat);
	  continue;
	}
      if (!opt.dfp
	  && (tmr != (time_t) (-1))
	  && !opt.spider
	  && ((hstat.len == hstat.contlen) ||
	      ((hstat.res == 0) &&
	       ((hstat.contlen == -1) ||
		(hstat.len >= hstat.contlen && !opt.kill_longer)))))
	{
	  touch (u->local, tmr);
	}
      /* End of time-stamping section.  */

      if (opt.spider)
	{
	  logprintf (LOG_NOTQUIET, "%d %s\n\n", hstat.statcode, hstat.error);
	  return RETROK;
	}

      /* It is now safe to free the remainder of hstat, since the
	 strings within it will no longer be used.  */
      FREEHSTAT (hstat);

      tmrate = rate (hstat.len - hstat.restval, hstat.dltime);

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
	  opt.downloaded += hstat.len;
	  return RETROK;
	}
      else if (hstat.res == 0) /* No read error */
	{
	  if (hstat.contlen == -1)  /* We don't know how much we were
				       supposed to get, so...  */
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
	      opt.downloaded += hstat.len;
	      return RETROK;
	    }
	  else if (hstat.len < hstat.contlen) /* meaning we lost the
						 connection too soon */
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - Connection closed at byte %ld. "),
			 tms, tmrate, hstat.len);
	      printwhat (count, opt.ntry);
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
	      opt.downloaded += hstat.len;
	      return RETROK;
	    }
	  else			/* the same, but not accepted */
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - Connection closed at byte %ld/%ld. "),
			 tms, tmrate, hstat.len, hstat.contlen);
	      printwhat (count, opt.ntry);
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
	      continue;
	    }
	  else			/* hstat.res == -1 and contlen is given */
	    {
	      logprintf (LOG_VERBOSE,
			 _("%s (%s) - Read error at byte %ld/%ld (%s). "),
			 tms, tmrate, hstat.len, hstat.contlen,
			 strerror (errno));
	      printwhat (count, opt.ntry);
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
   than local timezone (mktime assumes the latter).

   Contributed by Roger Beeman <beeman@cisco.com>, with the help of
   Mark Baushke <mdb@cisco.com> and the rest of the Gurus at CISCO.  */
static time_t
mktime_from_utc (struct tm *t)
{
  time_t tl, tb;

  tl = mktime (t);
  if (tl == -1)
    return -1;
  tb = mktime (gmtime (&tl));
  return (tl <= tb ? (tl + (tl - tb)) : (tl - (tb - tl)));
}

/* Check whether the result of strptime() indicates success.
   strptime() returns the pointer to how far it got to in the string.
   The processing has been successful if the string is at `GMT' or
   `+X', or at the end of the string.

   In extended regexp parlance, the function returns 1 if P matches
   "^ *(GMT|[+-][0-9]|$)", 0 otherwise.  P being NULL (a valid result of
   strptime()) is considered a failure and 0 is returned.  */
static int
check_end (char *p)
{
  if (!p)
    return 0;
  while (ISSPACE (*p))
    ++p;
  if (!*p
      || (p[0] == 'G' && p[1] == 'M' && p[2] == 'T')
      || ((p[0] == '+' || p[1] == '-') && ISDIGIT (p[1])))
    return 1;
  else
    return 0;
}

/* Convert TIME_STRING time to time_t.  TIME_STRING can be in any of
   the three formats RFC2068 allows the HTTP servers to emit --
   RFC1123-date, RFC850-date or asctime-date.  Timezones are ignored,
   and should be GMT.

   We use strptime() to recognize various dates, which makes it a
   little bit slacker than the RFC1123/RFC850/asctime (e.g. it always
   allows shortened dates and months, one-digit days, etc.).  It also
   allows more than one space anywhere where the specs require one SP.
   The routine should probably be even more forgiving (as recommended
   by RFC2068), but I do not have the time to write one.

   Return the computed time_t representation, or -1 if all the
   schemes fail.

   Needless to say, what we *really* need here is something like
   Marcus Hennecke's atotm(), which is forgiving, fast, to-the-point,
   and does not use strptime().  atotm() is to be found in the sources
   of `phttpd', a little-known HTTP server written by Peter Erikson.  */
static time_t
http_atotm (char *time_string)
{
  struct tm t;

  /* Roger Beeman says: "This function dynamically allocates struct tm
     t, but does no initialization.  The only field that actually
     needs initialization is tm_isdst, since the others will be set by
     strptime.  Since strptime does not set tm_isdst, it will return
     the data structure with whatever data was in tm_isdst to begin
     with.  For those of us in timezones where DST can occur, there
     can be a one hour shift depending on the previous contents of the
     data area where the data structure is allocated."  */
  t.tm_isdst = -1;

  /* Note that under foreign locales Solaris strptime() fails to
     recognize English dates, which renders this function useless.  I
     assume that other non-GNU strptime's are plagued by the same
     disease.  We solve this by setting only LC_MESSAGES in
     i18n_initialize(), instead of LC_ALL.

     Another solution could be to temporarily set locale to C, invoke
     strptime(), and restore it back.  This is slow and dirty,
     however, and locale support other than LC_MESSAGES can mess other
     things, so I rather chose to stick with just setting LC_MESSAGES.

     Also note that none of this is necessary under GNU strptime(),
     because it recognizes both international and local dates.  */

  /* NOTE: We don't use `%n' for white space, as OSF's strptime uses
     it to eat all white space up to (and including) a newline, and
     the function fails if there is no newline (!).

     Let's hope all strptime() implementations use ` ' to skip *all*
     whitespace instead of just one (it works that way on all the
     systems I've tested it on).  */

  /* RFC1123: Thu, 29 Jan 1998 22:12:57 */
  if (check_end (strptime (time_string, "%a, %d %b %Y %T", &t)))
    return mktime_from_utc (&t);
  /* RFC850:  Thu, 29-Jan-98 22:12:57 */
  if (check_end (strptime (time_string, "%a, %d-%b-%y %T", &t)))
    return mktime_from_utc (&t);
  /* asctime: Thu Jan 29 22:12:57 1998 */
  if (check_end (strptime (time_string, "%a %b %d %T %Y", &t)))
    return mktime_from_utc (&t);
  /* Failure.  */
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
  res = (char *)malloc (len2 + 11 + strlen (header));
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

/* Response value needs to be in lowercase, so we cannot use HEXD2ASC
   from url.h.  See RFC 2069 2.1.2 for the syntax of response-digest.  */
#define HEXD2asc(x) (((x) < 10) ? ((x) + '0') : ((x) - 10 + 'a'))

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
      *buf++ = HEXD2asc (*hash >> 4);
      *buf++ = HEXD2asc (*hash & 0xf);
    }
  *buf = '\0';
}

/* Take the line apart to find the challenge, and compose a digest
   authorization header.  See RFC2069 section 2.1.2.  */
char *
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
      for (i = 0; i < ARRAY_SIZE (options); i++)
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
      if (i == ARRAY_SIZE (options))
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
    struct md5_ctx ctx;
    unsigned char hash[MD5_HASHLEN];
    unsigned char a1buf[MD5_HASHLEN * 2 + 1], a2buf[MD5_HASHLEN * 2 + 1];
    unsigned char response_digest[MD5_HASHLEN * 2 + 1];

    /* A1BUF = H(user ":" realm ":" password) */
    md5_init_ctx (&ctx);
    md5_process_bytes (user, strlen (user), &ctx);
    md5_process_bytes (":", 1, &ctx);
    md5_process_bytes (realm, strlen (realm), &ctx);
    md5_process_bytes (":", 1, &ctx);
    md5_process_bytes (passwd, strlen (passwd), &ctx);
    md5_finish_ctx (&ctx, hash);
    dump_hash (a1buf, hash);

    /* A2BUF = H(method ":" path) */
    md5_init_ctx (&ctx);
    md5_process_bytes (method, strlen (method), &ctx);
    md5_process_bytes (":", 1, &ctx);
    md5_process_bytes (path, strlen (path), &ctx);
    md5_finish_ctx (&ctx, hash);
    dump_hash (a2buf, hash);

    /* RESPONSE_DIGEST = H(A1BUF ":" nonce ":" A2BUF) */
    md5_init_ctx (&ctx);
    md5_process_bytes (a1buf, MD5_HASHLEN * 2, &ctx);
    md5_process_bytes (":", 1, &ctx);
    md5_process_bytes (nonce, strlen (nonce), &ctx);
    md5_process_bytes (":", 1, &ctx);
    md5_process_bytes (a2buf, MD5_HASHLEN * 2, &ctx);
    md5_finish_ctx (&ctx, hash);
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


#define HACK_O_MATIC(line, string_constant)				\
  (!strncasecmp (line, string_constant, sizeof (string_constant) - 1)	\
   && (ISSPACE (line[sizeof (string_constant) - 1])			\
       || !line[sizeof (string_constant) - 1]))

static int
known_authentication_scheme_p (const char *au)
{
  return HACK_O_MATIC (au, "Basic") || HACK_O_MATIC (au, "Digest");
}

#undef HACK_O_MATIC

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
#ifdef USE_DIGEST
  else if (!strncasecmp (au, "Digest", 6))
    wwwauth = digest_authentication_encode (au, user, passwd, method, path);
#endif /* USE_DIGEST */
  return wwwauth;
}
