2000-12-30  Dan Harkless  <wget@harkless.org>

	* ftp.c, http.c:  Applied Hack Kampbjørn <hack@hackdata.com>'s
	patch to deal with h_errno not being defined in netdb.h under Cygwin.

	* version.c: Released Wget version 1.6.

2000-12-17  Igor Khristophorov  <igor@atdot.org>

	* http.c (check_end): Fix test for '+' or '-'.

2000-12-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (get_urls_html): Use xmalloc, not malloc.

	* url.c (parseurl): Rename inner loop var from i to ind to avoid
	clash with the function top-level-declared variable i.
	(str_url): Likewise, rename inner-loop i to j.

	* recur.c (parse_robots): Don't declare LEN at top of function.
	(robots_match): Renamed parameter FORBIDDEN to avoid hiding of
	global variable.

	* main.c (main): Change erroneous use of bitwise and to logical.

	* init.c (cmd_address): Don't heap-allocate `sin'; it can be on
	the stack because it will be copied to closure.

	Thanks to Csaba Raduly's run of PC-LINT over the sources.

2000-12-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (basic_authentication_encode): Use xmalloc(), not
	malloc().  Thanks to Csaba Raduly's run of PC-LINT over the
	sources.

2000-12-17  Csaba Raduly  <csaba.raduly@sophos.com>

	* sysdep.h: Test for __EMX__ rather than for EMXOS2 for OS/2
	compilation.

2000-12-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* mswindows.c: Include <errno.h>.

	* ftp-basic.c: Don't attempt to declare errno or h_errno because
	they're not used.

	* main.c: Include <errno.h> because errno is used.

	* ftp.c: Ditto.

	* http.c: Include <netdb.h> for h_errno.

2000-12-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): Furthermore, touch output_document only if
	it is known to be an existing regular file.

2000-12-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_retrieve_list): Ditto.

	* http.c (http_loop): Touch output_document if that is used for
	output.

2000-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_loop_internal): Ditto.

	* http.c (http_loop): Use it.

	* retr.c (sleep_between_retrievals): New function that handles the
	logic of opt.wait and opt.waitretry.

2000-11-24  Karl Eichwalder  <ke@suse.de>

	* main.c (print_help): Untabify.

2000-11-22  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): ftp_getaddress() returns a malloc'ed copy of the
	string; no need to strdup() it.

	* init.c (cleanup): Free opt.ftp_pass only if it's non-NULL.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (check_end): Constify.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Bump version to 1.6-pre.

2000-11-16  Hrvoje Niksic  <hniksic@arsdigita.com>

	* mswindows.h: Define snprintf and vsnprintf to _snprintf and
	_vsnprintf respectively.

2000-11-15  Hrvoje Niksic  <hniksic@arsdigita.com>

	* config.h.in: Do the _XOPEN_SOURCE and _SVID_SOURCE things only
	on Linux.

2000-11-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* host.c (realhost): Add HOST to the list with quality==0 only if
	it wasn't already there.
	Based on analysis by Lu Guohan <feng@public.bjnet.edu.cn>.

2000-11-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c (run_wgetrc): Don't bother killing off '\r' since
	pars_line() skips whitespace at end of line anyway.
	(parse_line): Oops, it didn't.  Now it does.

	* recur.c (parse_robots): Ditto here.

	* ftp-ls.c (ftp_parse_unix_ls): Kill off the newline character
	manually because read_whole_line no longer does.

	* utils.c (read_whole_line): Rewrite to: a) use less memory
	(reallocates to needed size after work), b) work faster -->
	fgets() instead of getc, c) be more correct --> doesn't kill the
	newline character at the end of line.

2000-11-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c (comind): Initialize MAX to array size - 1.

2000-11-08  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (construct): Changed last_slash[-1] to *(last_slash - 1).
	Suggested by Edward J. Sabol.

2000-11-08  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (construct): Handle the case where host name is not
	followed by a slash.

2000-11-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c: commands[] need to be sorted!  ("base" wasn't.)

2000-11-05  Hrvoje Niksic  <hniksic@arsdigita.com>

	* wget.h (DO_REALLOC_FROM_ALLOCA): Use braces to disambiguate
	`if'.

2000-11-05  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (construct): Insert unneeded initialization for the
	compiler to shut up.

	* config.h.in: Define _XOPEN_SOURCE to 500 to get the prototype
	for strptime() (*duh*).  Define _SVID_SOURCE to get S_IFLNK which
	otherwise gets lost when you define _XOPEN_SOURCE.

	* utils.c (touch): Include the file name in the error message.
	From Debian.

2000-11-05  Hrvoje Niksic  <hniksic@arsdigita.com>

	* log.c (logvprintf): Use vsnprintf() in all cases.  If necessary,
	resize the buffer to fit the formated message.  That way, messages
	of arbitrary size may be printed.
	(logvprintf): Use saved_append() to optionally log the last
	several lines of output.
	(logputs): Ditto.
	(log_close): Adapt to new data structures.
	(log_dump): Ditto.
	(redirect_output): Print messages to stderr, not to stdout.

	* log.c (saved_append_1): New function.  Replaces the old logging
	system ("log all output until 10M characters") with a new, much
	more reasonable one ("log last screenful of text").
	(saved_append): New function; call saved_append_1.
	(free_log_line): New function.

2000-11-05  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (construct): Fix comment.
	(find_last_char): Document.

2000-11-04  Hrvoje Niksic  <hniksic@arsdigita.com>

	* snprintf.c: New file.

2000-11-03  Hrvoje Niksic  <hniksic@arsdigita.com>

	* wget.h: If HAVE_STDARG_H is not defined, don't declare argument
	types to logprintf() and debug_logprintf().

2000-11-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_loop_internal): Hide the password from the URL when
	printing non-verbose.  Problem spotted by Dariusz Mlynarczyk
	<darekm@bydg.lomac.com.pl>.

2000-11-02  Junio Hamano  <junio@twinsun.com>

	* ftp-basic.c (ftp_login): Make comparison case-insensitive.

2000-11-02  Tyler Riddle  <triddle@liquidmarket.com>

	* http.c (known_authentication_scheme_p): Recognize NTML
	authentication.
	(create_authorization_line): Treat NTML the same as `Basic'.

2000-11-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): Free url before returning.
	(retrieve_url): Free mynewloc before returning.
	Spotted by Mark A. Mankins <Mankins_Mark@prc.com>.

2000-11-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (parseurl): Remove possible reading past the end of
	sup_protos[].  Spotted by Mark A. Mankins <Mankins_Mark@prc.com>.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (main): In case of opt.downloaded overflowing, print
	<overflow> instead of a totally bogus random value.

	* retr.c (retrieve_from_file): Ditto.

	* recur.c (recursive_retrieve): Ditto.

	* main.c (main): Ditto.

	* http.c (http_loop): Ditto.

	* ftp.c (ftp_loop_internal): Use downloaded_increase() instead of
	`+=', and downloaded_exceeds_quota() instead of the simple-minded
	check.
	(ftp_retrieve_list): Ditto.
	(ftp_retrieve_dirs): Ditto.
	(ftp_retrieve_glob): Ditto.

	* retr.c (downloaded_increase): New function.  Notice overflows of
	opt.downloaded.
	(downloaded_exceeds_quota): Make sure that opt.downloaded is not
	used if it overflowed.

	* options.h (struct options): New member downloaded_overflow.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* wget.h (enum): Remove extra space after last enumeration.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (main): Use legible_very_long() for printing
	opt.downloaded.

	* utils.c (legible_1): New function that operates on strings and
	does the brunt of legible()'s work.
	(legible): Use legible_1().
	(legible_very_long): New function; dump the argument with
	sprintf(), and call legible_1().

	* options.h (struct options): Use VERY_LONG_TYPE for
	opt.downloaded.

	* sysdep.h (VERY_LONG_TYPE): Define it to have a 64-bit or greater
	type.

	* config.h.in: Make sure that SIZEOF_LONG and SIZEOF_LONG_LONG get
	defined.  Define HAVE_LONG_LONG if long long is available.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (long_to_string): Update with a later, better version.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (path_simplify_with_kludge): New function.
	(path_simplify_with_kludge): Disable it.  Instead...
	(parse_dir): ...make sure that at this point the right thing is
	done, i.e. that "query" part of the URL (?...) is always assigned
	to the file, never to the directory portion of the path.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): Detect redirection cycles.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (get_urls_html): Decode HTML entities using
	html_decode_entities.

	* html.c (htmlfindurl): Don't count the `#' in numeric entities
	(&#NNN;) as an HTML fragemnt.
	(html_decode_entities): New function.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html.c (htmlfindurl): Fix recognition of # HTML fragments.

2000-11-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (construct): Rewritten for clarity.  Avoids the
	unnecessary copying and stack-allocation the old version
	performed.

2000-10-31  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): Ditto.

	* http.c (gethttp): Rewind the stream when retrying from scratch.

2000-10-31  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): Use url_concat() to handle relative
	redirections instead of /ad hoc/ code.

	* url.c (url_concat): New function encapsulating weird
	construct().
	(urllen_http_hack): New function.
	(construct): When constructing new URLs, recognize that `?' does
	not form part of the file name in HTTP.

2000-10-13  Adrian Aichner  <adrian@xemacs.org>

	* retr.c: Add msec timing support for WINDOWS.
	* retr.c (reset_timer): GetSystemTime() on WINDOWS.
	* retr.c (elapsed_time): Calculate delta time to msec on WINDOWS.

2000-10-27  Dan Harkless  <wget@harkless.org>

	* retr.c (retrieve_url): Manually applied T. Bharath
 	<TBharath@responsenetworks.com>'s patch to get wget to grok
 	illegal relative URL redirects.  Reformatted and re-commented it.

2000-10-23  Dan Harkless  <wget@harkless.org>

	* connect.c (make_connection and bindport): Manually applied Rob
 	Mayoff <mayoff@dqd.com>'s 1.5.3 patch to add --bind-address,
 	changing coding style to GNU's.

	* ftp.c (ftp_loop_internal): --delete-after wasn't implemented for
 	files downloaded via FTP.  Per a comment, .listing files were not
	counted towards number of bytes and files downloaded because they're 
	deleted anyway.  Well, they aren't under -nr, so count them then.

	* init.c: Manually applied Rob Mayoff's 1.5.3 patch to add
 	--bind-address, alphabetizing, changing coding style to GNU's,
 	commenting, and renaming cmd_ip_address() to cmd_address() to
 	imply hostnames also okay.
		
	* main.c (main): --delete-after didn't delete the root of the
 	tree.  Ignore --convert-links if --delete-after was specified.
  	Manually applied Rob Mayoff's 1.5.3 patch to add --bind-address,
 	fixing duplicate use of added-since-1.5.3 case value.
	(print_help): Clarified that --delete-after deletes local files.
	Rob forgot to add a line for his new --bind-address option.
		
	* options.h (struct options): Manually applied Rob Mayoff's patch
	to add --bind-address (bind_address structure member).
		
	* recur.c (recursive_retrieve): Improved comment; added DEBUGP().
	Ignore --convert-links if --delete-after was specified.
		
	* retr.c (retrieve_from_file): Just added a DEBUGP().
		
2000-10-19  Dan Harkless  <wget@harkless.org>

	* ftp.c (ftp_loop_internal): downloaded_file() enumerators changed.
	(getftp): Applied Piotr Sulecki <Piotr.Sulecki@ios.krakow.pl>'s
	patch to work around FTP servers that incorrectly respond to the
	"REST" command with the remaining size rather than the total file size.
		
	* http.c (gethttp): Improved a comment and added code to tack on
	".html" to text/html files without that extension when -E specified.
	(http_loop): Use new downloaded_file() enumerators and deal with
	the case of gethttp() called xrealloc() on u->local.

	* init.c (commands): Added new "htmlextension" command.
	Also renamed John Daily's cmd_quad() to the more descriptive
	cmd_lockable_boolean(), alpha-sorted the CMD_DECLARE()s and
	removed duplicate cmd_boolean() declaration.

	* main.c (print_help): Added my new -E / --html-extension option.
	(main): Undocumented --email-address option previously used -E synonym.
	Stole it away for the much more deserving --html-extension's use.

	* options.h (struct options): Added html_extension field.

	* url.c (convert_links): URL X that we saved as X.html locally due
	to -E needs to be backed up as X.orig, not X.html.orig.  Added comments.
	(downloaded_file): Now remembers if we added .html extension to a file.

	* url.h (downloaded_file_t): Added extra enumerators to support above.
	(downloaded_file): Now takes and returns a downloaded_file_t.

	* wget.h (unnamed "dt" enum): Added ADDED_HTML_EXTENSION enumerator.
	
2000-10-09  Dan Harkless  <wget@harkless.org>

	* html.c (htmlfindurl): Added unneeded initialization to quiet warning.
		
	* main.c (print_help): Clarified what --retr-symlinks does.
	
2000-09-15  John Daily  <jdaily@cyberdude.com>

	* init.c: Add support for "always" and "never" values to allow
	.wgetrc to override commandline (useful e.g. with .pm files
	calling `wget --passive-ftp' when your firewall doesn't allow that).

	* ftp.c (getftp): passive_ftp is first option to support always/never.

2000-08-30  Dan Harkless  <wget@harkless.org>

	* ftp.c (ftp_retrieve_list): Use new INFINITE_RECURSION #define.
	
	* html.c: htmlfindurl() now takes final `dash_p_leaf_HTML' parameter.
 	Wrapped some > 80-column lines.  When -p is specified and we're at a 
	leaf node, do not traverse <A>, <AREA>, or <LINK> tags other than 
	<LINK REL="stylesheet">.
	
	* html.h (htmlfindurl): Now takes final `dash_p_leaf_HTML' parameter.
	
	* init.c: Added new -p / --page-requisites / page_requisites option.

	* main.c (print_help): Clarified that -l inf and -l 0 both allow
	infinite recursion.  Changed the unhelpful --mirrior description
	to simply give the options it's equivalent to.  Added new -p option.
	(main): Added some comments; handle new -p / --page-requisites.
	
	* options.h (struct options): Added new page_requisites field.

	* recur.c: Changed "URL-s" to "URLs" and "HTML-s" to "HTMLs".
  	Calculate and pass down new `dash_p_leaf_HTML' parameter to
 	get_urls_html().  Use new INFINITE_RECURSION #define.

	* retr.c: Changed "URL-s" to "URLs".  get_urls_html() now takes
	final `dash_p_leaf_HTML' parameter.

	* url.c: get_urls_html() and htmlfindurl() now take final
	`dash_p_leaf_HTML' parameter.

	* url.h (get_urls_html): Now takes final `dash_p_leaf_HTML' parameter.

	* wget.h: Added some comments and new INFINITE_RECURSION #define.
	
2000-08-23  Dan Harkless  <wget@harkless.org>

	* main.c (print_help): -B / --base was not mentioned.

2000-08-22  Dan Harkless  <wget@harkless.org>

	* main.c (print_help): Modified -nc description to mention that it
	also prevents the creation of multiple versions of the same file
	with ".<number>" suffixes.

2000-07-14  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* retr.c (retrieve_url): Consistently strdup opt.referer when
	setting u->referer.

2000-06-09  Dan Harkless  <wget@harkless.org>

	* main.c (print_help): --help output for --waitretry was over 80 cols.

2000-06-09  Hrvoje Niksic  <hniksic@iskon.hr>

	* url.c (encode_string): Fix comment.
	Suggested by Herold Heiko <Heiko.Herold@previnet.it>.

2000-06-01  Const Kaplinsky  <const@ce.cctpu.edu.ru>

	* ftp.c (ftp_retrieve_list): Change permissions only on plain
	files.

2000-06-01  Hrvoje Niksic  <hniksic@iskon.hr>

	* url.c (str_url): Print the port number only if it's different
	from the default port number for that protocol.

2000-05-22  Dan Harkless  <wget@harkless.org>

	* main.c (print_help): Added --help line for Damir Dzeko
 	<ddzeko@zesoi.fer.hr>'s until-now-undocumented --referer option.
  	Removed comments that --referer and --waitretry were undocumented.
  	Changed "`.wgetrc' command" to "`.wgetrc'-style command" on --help
 	line for --execute.

2000-05-18  Hrvoje Niksic  <hniksic@iskon.hr>

	* ftp.c (getftp): Ditto.

	* http.c (gethttp): Check for return value of fclose/fflush.

2000-04-12  Hrvoje Niksic  <hniksic@iskon.hr>

	* host.c (store_hostaddress): Instead of shifting ADDR, start
	copying from the correct address.

2000-04-12  Hrvoje Niksic  <hniksic@iskon.hr>

	* http.c (gethttp): Don't free REQUEST -- it was allocated with
	alloca().
	Pointed out by Gisle Vanem <gvanem@eunet.no>.

2000-04-04  Dan Harkless  <wget@harkless.org>

	* host.c (store_hostaddress): R. K. Owen's patch introduces a
	"left shift count >= width of type" warning on 32-bit
	architectures.  Got rid of it by tricking the compiler w/ a variable.
	
	* url.c (UNSAFE_CHAR): The macro didn't include all the illegal
	characters per RFC1738, namely everything above '~'.  It also
	generated a warning on OSes where char =~ unsigned char.  Fixed.
	
1998-10-17  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_process_type): Removed needless strdup(), a memory
	leak.

1998-09-25  Hrvoje Niksic  <hniksic@srce.hr>

	* html.c (htmlfindurl): Set PH to the first occurrence of `#'.

1998-09-25  Simon Munton  <simonm@m4data.co.uk>

	* init.c (wgetrc_file_name): Don't free HOME under Windows.

1998-12-01  "R. K. Owen"  <rkowen@Nersc.GOV>

	* host.c (store_hostaddress): Fix for big endian 64-bit machines.

1998-12-01  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (UNSAFE_CHAR): New macro.
	(contains_unsafe): Use it.
	(encode_string): Ditto.

1998-12-01  Hrvoje Niksic  <hniksic@srce.hr>

	* main.c (i18n_initialize): Use LC_MESSAGES only if available.

2000-03-31  Hrvoje Niksic  <hniksic@srce.hr>

	* Use TOUPPER/TOLOWER.

1998-12-22  Alexander V. Lukyanov  <lav@yars.free.net>

	* ftp-opie.c (btoe): Zero-terminate OSTORE.

2000-03-21  Hrvoje Niksic  <hniksic@iskon.hr>

	* wget.h (DO_REALLOC_FROM_ALLOCA): Ditto.

	* sysdep.h (ISALNUM): New macro.
	(TOLOWER): Ditto.
	(TOUPPER): Ditto.

2000-03-10  Dan Harkless  <wget@harkless.org>

	* html.c (idmatch): Implemented checking of my new --follow-tags
	and --ignore-tags options.
	
	* init.c (commands): Added comment reminding people adding new
	entries doing allocation to add corresponding freeing in cleanup().
	(commands): Added new followtags and ignoretags commands.
	(cleanup): Free storage for new followtags and ignoretags.
	
	* main.c: Use of "comma-separated list" was random -- normalized
	it.  Did some alphabetization.  Added comments pointing out
	"Options without arguments" and "Options accepting an argument"
	sections of long_options[].  Added new options --follow-tags and
	-G / --ignore-tags.  Added comment that Damir's --referer is
	currently undocumented.  Added comment that Heiko's --waitretry is
	partially undocumented (mentioned in --help but not in
	wget.texi).  Moved improperly sorted 24, 129, and 'G' cases.
	
	* options.h (struct options): Added new fields follow_tags and
	ignore_tags. 
	
	* wget.h: Added "#define EQ 0" so we can say "strcmp(a, b) == EQ".
	
2000-03-02  Dan Harkless  <wget@harkless.org>

	* ftp.c (ftp_loop_internal): Heiko introduced "suggest explicit
	braces to avoid ambiguous `else'" warnings.  Eliminated them.
	
	* http.c (gethttp): Dan Berger's query string patch is totally
 	bogus.  If you have two different URLs, gen_page.cgi?page1 and
 	get_page.cgi?page2, they'll both be saved as get_page.cgi and the
 	second will overwrite the first.  Also, parameters to implicit
 	CGIs, like "http://www.host.com/db/?2000-03-02" cause the URLs to
 	be printed with trailing garbage characters, and could seg fault.
  	Backing out the patch, which Dan B. informed me by email was just
 	a kludge to download StarOffice from Sun made necessary due to
 	wget's unconditional escaping of certain characters (room for an
 	option there?).
	(http_loop): Heiko introduced "suggest explicit braces to avoid
 	ambiguous `else'" warnings.  Eliminated them.
	
	* main.c: Heiko's --wait / --waitretry backwards compatibility
	code looks to have been totally untested -- automatic variable
	'wr' was used without being initialized, and a long int was passed
	into setval()'s char* val parameter.
	
	* recur.c (parse_robots): Applied Edward J. Sabol
	<sabol@alderaan.gsfc.nasa.gov>'s patch for Guan Yang's reported
	problem with "User-agent:<space>*<space>" lines in robots.txt.
	
	* url.c (parseurl, str_url): Removing Dan Berger's code (see
	http.c above for explanation).
	
1999-08-25  Heiko Herold  <Heiko.Herold@previnet.it>

	* ftp.c: Respect new option waitretry.

2000-01-30  Damir Dzeko  <ddzeko@zesoi.fer.hr>

	* http.c (gethttp): Send custom Referer, if required.

1999-09-24  Charles G Waldman  <cgw@fnal.gov>

	* netrc.c (parse_netrc): Allow passwords to contain spaces.

	* netrc.c (parse_netrc): New function.

1999-09-17  Dan Berger  <dberger@ix.netcom.com>

	* http.c (gethttp): Send it.

	* url.c (parseurl): Detect query string in HTTP URL-s.
	(str_url): Print it.

2000-03-02  HIROSE Masaaki  <hirose31@t3.rim.or.jp>

	* html.c (html_allow): Add <link href=...> and <script src=...>.

1999-05-02  andrew deryabin  <djsf@softhome.net>

	* http.c (gethttp): Specify port in `Host' header only if it's
	different from 80.

1998-11-03  Edward J. Sabol  <sabol@alderaan.gsfc.nasa.gov>

	* recur.c (recursive_retrieve): If a finite maximum depth is
	specified, and we're are already at that depth, don't download the
	HTML file for parsing.

2000-03-01  Dan Harkless  <wget@harkless.org>

	* ftp.c (ftp_loop_internal): Call new downloaded_file() function,
	even though we don't do conversion on HTML files retrieved via
	FTP, so _current_ usage of downloaded_file() makes this call unneeded. 
	(ftp_retrieve_list): Added a comment saying where we need to
	stat() a .orig file if FTP'd HTML file conversion is ever implemented.
	(ftp_retrieve_list): "Local file '%s' is more recent," is sometimes
	a lie -- reworded as "Server file no newer than local file '%s' --".
	
	* http.c (http_loop): Fixed a typo and clarified a comment.
	(http_loop): When -K and -N are specified together, compare size
 	and timestamp of server file X against local file X.orig (if
 	extant) rather than converted local file X.
	(http_loop): "Local file '%s' is more recent," is sometimes a lie
 	-- reworded as "Server file no newer than local file '%s' --".
	(http_loop): Call new downloaded_file() function to prevent
	wrongful overwriting of .orig file when -N is specified.
	
	* url.c (convert_links): When -K specified, only rename X to
 	X.orig if downloaded_file() returns TRUE.  Otherwise when we skip
 	file X due to -N, we clobber an X.orig from a previous invocation.
	(convert_links): Call the failsafe xstrdup(), not the real strdup().
	(convert_links): Added a note asking anyone who understands how
	multiple URLs can correspond to a single file to comment it.
	(downloaded_file): Added this new function.
	
	* url.h (downloaded_file): Added prototype for this new function
	as well as its downloaded_file_t enum type.

	* wget.h (boolean): Added this new typedef and TRUE and FALSE #defines.

2000-02-29  Dan Harkless  <wget@harkless.org>

	* version.c: Upped version to developer-only "1.5.3+dev".

2000-02-18  Dan Harkless  <wget@harkless.org>

	* init.c (backup_converted): Added this new option.

	* main.c (-K / --backup-converted): Added this new option.

	* options.h (backup_converted): Added this new option.

	* url.c (convert_links): When backup_converted is specified, save
	file X as X.orig before converting.

	* url.h (urlpos): Fixed typo -- said "Rekative" instead of "Relative".

1998-09-21  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.3 is released.

1998-09-21  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (ftp_getaddress): Don't warn when reverse-lookup of local 
	address doesn't yield FQDN.

1998-09-21  Andreas Schwab  <schwab@issan.informatik.uni-dortmund.de>

	* cmpt.c (strerror): Fix declaration of sys_errlist.

1998-09-11  Hrvoje Niksic  <hniksic@srce.hr>

	* main.c (main): Don't use an array subscript as the first
	argument to STRDUP_ALLOCA.
	From Kaveh R. Ghazi.

1998-09-11  Szakacsits Szabolcs  <szaka@sienet.hu>

	* html.c (htmlfindurl): Download table background.

1998-09-11  Hans Grobler  <grobh@conde.ee.sun.ac.za>

	* init.c (parse_line): Would free *com before allocating it.
	(parse_line): Would free com instead of *com.

1998-09-10  Howard Gayle  <howard@fjst.com>

	* url.c (get_urls_html): Would drop the last character of the
 	link.

1998-09-10  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): Don't print status code if quiet.

1998-09-10  Kaveh R. Ghazi  <ghazi@caip.rutgers.edu>

	* log.c: Use <stdarg.h> only when __STDC__.

1998-09-10  Adam D. Moss  <adam@foxbox.org>

	* html.c (htmlfindurl): Download <layer src=...>.

1998-09-10  Howard Gayle  <howard@fjst.com>

	* ftp.c (ftp_retrieve_list): Don't update the time stamp of a file 
	not retrieved.

1998-06-27  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c: Include <libc.h> on NeXT.

1998-06-26  Heinz Salzmann  <heinz.salzmann@intermetall.de>

	* url.c (get_urls_html): Fix calculation of URL position.

1998-06-23  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.2 is released.

1998-06-23  Dave Love  <d.love@dl.ac.uk>

	* ftp.c, init.c, netrc.c: Include errno.h.

	* http.c: Include errno.h and time header.

	* Makefile.in (exext): Define.
	(install.bin, uninstall.bin): Use it.

1998-06-21  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): Don't attempt to compare local and remote
	sizes if the remote size is unknown.

1998-06-16  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (get_urls_html): Use malloc() instead of alloca in the
 	loop.

1998-06-13  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.2-b4 is released.

1998-06-13  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (get_urls_html): Ignore spaces before and after the URI.

1998-06-08  Wanderlei Antonio Cavassin  <cavassin@conectiva.com.br>

	* ftp.c (getftp): Translate `done'.

1998-06-06  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.2-b3 is released.

1998-06-06  Alexander Kourakos  <awk@bnt.com>

	* init.c (cleanup): Close dfp, don't free it.

1998-06-06  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (make_directory): Twiddle.

	* config.h.in: Added template for access().

1998-06-05  Mathieu Guillaume  <mat@cythere.com>

	* html.c (htmlfindurl): Download <input src=...>

1998-06-03  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (file_exists_p): Use access() with two arguments.

1998-05-27  Martin Kraemer  <Martin.Kraemer@mch.sni.de>

	* netrc.c (parse_netrc): Correct logic.

1998-05-27  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Added `break'; suggested by Lin Zhe Min
 	<ljm@ljm.wownet.net>.

1998-05-24  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.2-b2 is released.

1998-05-18  Juan Jose Rodriguez  <jcnsoft@jal1.telmex.net.mx>

	* mswindows.h: Don't translate mkdir to _mkdir under Borland.

1998-05-17  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (elapsed_time): Return correct value when
	HAVE_GETTIMEOFDAY is undefined.

1998-05-13  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.2-b1 is released.

1998-05-08  Hrvoje Niksic  <hniksic@srce.hr>

	* getopt.c (_getopt_internal): Use exec_name instead of argv[0].
	(_getopt_internal): Don't translate `#if 0'-ed strings.

1998-05-06  Douglas E. Wegscheid  <wegscd@whirlpool.com>

	* mswindows.c (ws_handler): Use fork_to_background().

1998-05-05  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.1 is released.

1998-05-05  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (parse_http_status_line): Avoid `minor' and `major'
 	names.

1998-05-02  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (mkdirhier): Renamed to make_directory.

1998-05-01  Hrvoje Niksic  <hniksic@srce.hr>

	* mswindows.c (fork_to_background): Define under Windows.

	* utils.c (fork_to_background): New function.

	* html.c (htmlfindurl): Removed rerdundant casts.

1998-05-01  Douglas E. Wegscheid  <wegscd@whirlpool.com>

	* mswindows.c (ws_mypath): Cache the path.

1998-04-30  Douglas E. Wegscheid  <wegscd@whirlpool.com>

	* ftp.h: Prefix enum ftype members with FT_.

	* ftp-ls.c, ftp.c, html.h: Adjust accordingly.

	* mswindows.h: Use stat under Borland, _stat under MSVC.

1998-04-28  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (known_authentication_scheme_p): New function.
	(gethttp): Handle authorization more correctly.

	* ftp-basic.h: Removed.

	* cmpt.h: Removed.

	* utils.c: Include <unistd.h> before <pwd.h>; needed under SunOS
	with gcc 2.8.
	(numdigit): Use `while' loop.

	* http.c (create_authorization_line): Detect authentication
 	schemes case-insensitively.

	* http.c (extract_header_attr): Use strdupdelim().
	(digest_authentication_encode): Move declaration of local
 	variables to smaller scope.
	(digest_authentication_encode): Reset REALM, OPAQUE and NONCE.
	(create_authorization_line): Detect authentication schemes
	case-insensitively.

	* utils.c (touch): Constify.

	* http.c (gethttp): Report a nicer error when no data is received.

	* rbuf.h (RBUF_READCHAR): Ditto.

	* ftp-basic.c (ftp_response): Use sizeof.

1998-04-27  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (print_percentage): EXPECTED is long, not int.
	(print_percentage): Use floating-point arithmetic to avoid
	overflow with large files' sizes multiplied with 100.

1998-04-27  Gregor Hoffleit  <flight@mathi.uni-heidelberg.de>

	* config.h.in: Added pid_t stub.

	* sysdep.h (S_ISREG): Moved here from mswindows.h (NeXT doesn't
	define it).

1998-04-20  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5.0 is released.

1998-04-18  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (str_url): Ditto.

	* ftp-basic.c (ftp_rest): Use new name.

	* utils.c (long_to_string): Renamed from prnum().

1998-04-16  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b17 is released.

1998-04-08  Hrvoje Niksic  <hniksic@srce.hr>

	* headers.c (header_get): New argument FLAGS.

	* http.c (gethttp): If request is malformed, bail out of the
 	header loop.
	(gethttp): Check for empty header *after* the status line checks.
	(gethttp): Disallow continuations for status line.

1998-04-08  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b16 is released.

1998-04-08  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (commands): Renamed `always_rest' to `continue'.

1998-04-05  Hrvoje Niksic  <hniksic@srce.hr>

	* all: Use it.

	* log.c (logputs): New argument.
	(logvprintf): Ditto.
	(logprintf): Ditto.

1998-04-04  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_atotm): Update comment.

	* main.c (i18n_initialize): Set LC_MESSAGES, not LC_ALL.

	* wget.h: Renamed ENABLED_NLS to HAVE_NLS.

	* main.c (i18n_initialize): New function.
	(main): Use it.

	* log.c: Include <unistd.h>.

	* retr.c (show_progress): Cast alloca to char *.

1998-04-04  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b15 is released.

1998-04-04  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.h: Declare file_non_directory_p().

1998-04-03  Hrvoje Niksic  <hniksic@srce.hr>

	* main.c (main): It's `tries', not `numtries' now.

1998-04-01  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (getperms): Removed.

1998-04-01  Tim Charron  <tcharron@interlog.com>

	* log.c (logvprintf): Don't use ARGS twice.

1998-04-01  John  <john@futuresguide.com>

	* mswindows.c: Cleaned up.

1998-04-01  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b14 is released.

1998-04-01  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp-opie.c (STRLEN4): New macro.
	(btoe): Use it.

1998-04-01  Junio Hamano  <junio@twinsun.com>

	* http.c: Document all the Digest functions.

1998-04-01  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (file_non_directory_p): Renamed from isfile().

	* mswindows.h (S_ISREG): New macro, suggested by Tim Adam.

1998-03-31  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (mkdirhier): Use 0777 instead of opt.dirmode.

	* init.c (cmd_spec_dotstyle): Use 48 dots per line for binary
 	style.
	(cmd_permissions): Removed.

	* config.h.in: Add template for WORDS_BIGENDIAN.

1998-03-31  Junio Hamano  <junio@twinsun.com>

	* http.c (HEXD2asc): New macro.
	(dump_hash): Use it.

1998-03-31  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b13 is released.

1998-03-31  Hrvoje Niksic  <hniksic@srce.hr>

	* main.c (main): Don't try to use `com'.

1998-03-30  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (cmd_permissions): New function.

1998-03-30  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b12 is released.

1998-03-30  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (commands): Renamed `numtries' to `tries'.
	(cmd_spec_debug): Removed.
	(home_dir): Under Windows, return `C:\' if HOME is undefined.

1998-03-29  Hrvoje Niksic  <hniksic@srce.hr>

	* config.h.in: Define _XOPEN_SOURCE.

	* init.c (check_user_specified_header): New function.
	(cmd_spec_header): Use it.
	(cmd_spec_useragent): New function.

1998-03-29  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b11 is released.

1998-03-28  Hrvoje Niksic  <hniksic@srce.hr>

	* wget.h: Include <libintl.h> only if NLS is enabled.

1998-03-26  Hrvoje Niksic  <hniksic@srce.hr>

	* options.h (struct options): Made `wait' a long.
	(struct options): Ditto for `timeout'.

1998-03-19  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (exists): Renamed to file_exists_p.
	(file_exists_p): Use access() if available.

1998-03-17  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (memfatal): Set save_log_p to 0 to avoid potential
 	infloop.

	* log.c: do_logging -> save_log_p.

	* config.h.in: Added template for HAVE_VSNPRINTF.

1998-03-16  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c: Ditto.

	* http.c: Protect declaration against non-ANSI compiler.

	* log.c (logvprintf): Use vsnprintf() if available.

	* getopt.c (main): Don't translate test stuff.

1998-03-16  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b10 is released.

1998-03-11  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Don't translate "CWD %s".

	* wget.h (GCC_FORMAT_ATTR): Renamed from FORMAT_ATTR.

1998-03-07  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp-opie.c (btoe): Use memcpy() instead of strncat().

	* log.c (logputs): New function.
	(logvprintf): Renamed from vlogmsg; use logputs().

	* retr.c (show_progress): Print `[100%]' when the retrieval is
	finished.

	* init.c (run_wgetrc): Use FILE, not PATH.
	(wgetrc_file_name): Ditto.

1998-03-07  Tim Adam  <tma@osa.com.au>

	* recur.c (parse_robots): Correctly reset `entries' on empty
 	disallow.

1998-03-07  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (cmd_spec_debug): Use cmd_boolean().

1998-02-23  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (gethttp): Create proxy-authorization correctly.

1998-02-22  Hrvoje Niksic  <hniksic@srce.hr>

	* md5.c: Ditto.

	* getopt.c: Use ANSI function definitions.

	* ftp-opie.c: New file.

	* options.h: Don't redefine EXTERN.

	* init.c: Sort it correctly.

1998-02-22  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b9 is released.

1998-02-22  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (recursive_retrieve): Reset `first_time'.

	* ftp.c (getftp): Added `default' clause to switches of uerr_t.

	* rbuf.c (rbuf_peek): Simplified.
	(rbuf_flush): Use MINVAL.

	* wget.h (MINVAL): Moved from url.h.

	* rbuf.h (RBUF_FD): New macro.

	* url.c (add_url): Add to the head of the list.

	* ftp.c (ftp_retrieve_list): Set the permissions to downloaded
 	file.
	(getftp): Set the default permissions to 0600.

1998-02-21  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (get_urls_html): Ditto.
	(convert_links): Ditto.

	* recur.c (parse_robots): Ditto.

	* html.c (ftp_index): Ditto.

	* ftp-ls.c (ftp_parse_unix_ls): Open file as binary.

	* init.c (defaults): Initialize `opt' to zero via memset.

	* http.c (digest_authentication_encode): goto considered harmful.

1998-02-19  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (delelement): Simplify and fix leak.

1998-02-18  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (dump_hash): Use HEXD2ASC instead of home-grown stuff.

	* url.h (HEXD2ASC): Removed warning.

	* init.c (comind): Use binary search.
	(commands): Reorganized.
	(setval): Ditto.
	(cmd_boolean): New function.
	(cmd_number): Ditto.
	(cmd_number_inf): Ditto.
	(cmd_string): Ditto.
	(cmd_vector): Ditto.
	(cmd_directory_vector): Ditto.
	(cmd_bytes): Ditto.
	(cmd_time): Ditto.
	(cmd_spec_debug): Ditto.
	(cmd_spec_dirmode): Ditto.
	(cmd_spec_dirstruct): Ditto.
	(cmd_spec_dotstyle): Ditto.
	(cmd_spec_header): Ditto.
	(cmd_spec_htmlify): Ditto.
	(cmd_spec_mirror): Ditto.
	(cmd_spec_outputdocument): Ditto.
	(cmd_spec_recursive): Ditto.
	(settime): Merged with cmd_time().
	(setbytes): Merged with cmd_bytes().
	(setonoff): Merged with cmd_boolean().
	(onoff): Ditto.

1998-02-17  Hrvoje Niksic  <hniksic@srce.hr>

	* Makefile.in (distclean): Remove `config.h'.

1998-02-17  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b8 is released.

1998-02-17  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (digest_authentication_encode): New function.
	(create_authorization_line): Use it.
	(dump_hash): New function.
	(digest_authentication_encode): Use it.

	* fnmatch.c: Renamed from `mtch.c'.

1998-02-15  Karl Eichwalder  <ke@suse.de>

	* main.c (main): Tag "Written by..." string as translatable.

1998-02-15  Hrvoje Niksic  <hniksic@srce.hr>

	* wget.h (FREE_MAYBE): New macro.

	* http.c (create_authorization_line): Don't use ANSI C string
 	concatenation feature.
	(basic_authentication_encode): Use alloca() for temporary
 	variables.

	* recur.h: Ditto.

	* http.c: Ditto.

	* headers.h: Ditto.

	* ftp-basic.c: Protect declaration against non-ANSI compiler.

	* http.c (create_authorization_line): Cast `unsigned char *' to
	`char *' for sprintf, to shut up the noisy Digital Unix cc.

1998-02-15  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b7 is released.

1998-02-15  Hrvoje Niksic  <hniksic@srce.hr>

	* cmpt.c (strstr): Synched with glibc-2.0.6.

	* ftp-basic.c (calculate_skey_response): Ditto.
	(calculate_skey_response): Use alloca().

	* http.c (create_authorization_line): Work with FSF's version of
 	md5.c.

	* md5.c: New file, from GNU libc.

1998-02-14  Hrvoje Niksic  <hniksic@srce.hr>

	* url.h (URL_CLEANSE): Name the temporary variable more carefully.

1998-02-13  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (basic_authentication_encode): New function, instead of
	the macro.

1998-02-13  Junio Hamano  <junio@twinsun.com>

	* http.c: Add HTTP-DA support.
	* ftp-basic.c: Add Opie/S-key support.
	* config.h.in, Makefile.in: Add HTTP-DA and Opie/S-key support.
	* md5.c, md5.h: New files.

1998-02-13  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_process_range): Renamed from hprocrange().
	(http_process_range): Parse the whole header.

	* headers.c: New file.
	(header_process): New function.
	(header_get): Renamed from fetch_next_header.

	* all: Include utils.h only where necessary.

	* wget.h: Declare xmalloc(), xrealloc() and xstrdup() here.

	* wget.h: Add provisions for dmalloc.

1998-02-12  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b6 is released.

1998-02-12  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_loop): Determine `filename' more precisely.

	* init.c (setval): Don't set `opt.quiet' if output-document is
 	`-'.

	* log.c (log_init): Print to STDERR instead of STDOUT.
	(vlogmsg): Use STDERR by default.
	(logflush): Ditto.

1998-02-11  Simon Josefsson  <jas@pdc.kth.se>

	* host.c: Use addr_in again.

1998-02-08  Karl Eichwalder  <karl@suse.de>

	* http.c (gethttp): Fixed typo.

1998-02-08  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b5 is released.

1998-02-08  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (show_progress): Use it.

	* log.c (logflush): New function.

	* wget.h: Utilize __attribute__ if on gcc.

1998-02-07  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (base64_encode_line): New argument LENGTH.
	(BASIC_AUTHENTICATION_ENCODE): Use it.
	(BASIC_AUTHENTICATION_ENCODE): Take length of HEADER into account.

	* main.c (main): Fixed fprintf() format mismatch.

1998-02-06  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b4 is released.

1998-02-03  Simon Josefsson  <jas@pdc.kth.se>

	* host.c: use sockaddr_in instead of addr_in.

1998-02-04  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (cleanup): Use it.

	* recur.c (recursive_cleanup): New function.

	* retr.c (retrieve_from_file): Ditto.

	* main.c (main): Use it.

	* recur.c (recursive_reset): New function.

	* retr.c (retrieve_from_file): Ditto.

	* main.c (main): Simplify call to recursive_retrieve().

	* recur.c (recursive_retrieve): Removed FLAGS argument.

	* http.c (gethttp): Changed call to iwrite().

1998-02-03  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (get_urls_html): Ditto.
	(free_urlpos): Ditto.
	(mkstruct): Ditto.
	(construct): Ditto.

	* retr.c (retrieve_url): Move declaration of local variables to
	smaller scope.

	* url.c (urlproto): Use it.
	(parseurl): Ditto.
	(str_url): Ditto.
	(get_urls_html): Ditto.

	* utils.h (ARRAY_SIZE): New macro.

	* url.c (proto): Moved from url.h.

	* url.h (URL_CLEANSE): Reformatted.
	(USE_PROXY_P): Renamed from USE_PROXY.

	* ftp-basic.c: Adjust to the new interface of iwrite().

	* ftp-basic.c (ftp_port): Use alloca().

1998-02-03  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b3 is released.

	* host.c (ftp_getaddress): Don't print to stderr directly.

	* init.c (setbytes): Support `g' for gigabytes.
	(cmdtype): New specification CTIME.
	(setval): Use it with settime().
	(commands): Use it for WAIT and TIMEOUT.

1998-02-02  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (BASIC_AUTHENTICATION_ENCODE): New macro.
	(gethttp): Use it.

	* utils.c (unique_name_1): Moved from url.c.
	(unique_name): Ditto.

	* url.c (url_filename): Ditto.

	* log.c (redirect_output): Changed call to unique_name().

	* url.c (unique_name_1): Renamed from unique_name().
	(unique_name): Changed interface.

	* init.c (enum cmdid): Moved from init.h.
	(cmdtype): Ditto.
	(struct cmd): Ditto.

	* main.c (main): Use it.
	(main): Moved `--backups' to not have a short option.

	* options.h (struct options): New member BACKGROUND.

	* main.c (print_help): Rearranged.
	(main): New long options for -n* short options: --no-directories,
 	--no-host-directories, --non-verbose, --no-host-lookup and
 	--dont-remove-listing.

1998-02-01  Hrvoje Niksic  <hniksic@srce.hr>

	* main.c (main): Use log_close().

	* log.c: New variable LOGFP.
	(vlogmsg): Use it.
	(redirect_output): Don't open /dev/null; set LOGFP to stdin
 	instead.
	(log_close): New function.

	* options.h (struct options): Removed LFILE.

	* log.c (log_enable): Removed.

	* main.c (main): Use it.

	* log.c (log_init): New function.

	* url.c (get_urls_html): Removed needless assignment to BASE.

	* host.c (add_hlist): Don't set CMP needlessly.

	* utils.c (match_backwards): Ditto.
	(in_acclist): Ditto.

	* url.c (findurl): Ditto.

	* netrc.c (parse_netrc): Ditto.

	* log.c (log_dump): Ditto.

	* html.c (html_quote_string): Ditto.

	* ftp-basic.c (ftp_request): Made static.

	* connect.c: Made global variables static.

	* url.c (construct): Ditto.

	* init.c (init_path): Avoid assignment inside `if'-condition.

	* ftp.c: Don't include in.h or winsock.h.

	* ftp.c (ftp_loop): Use SZ.

	* connect.c (bindport): Cast &addrlen to int *.
	(conaddr): Ditto.

	* init.c (initialize): Don't use SYSTEM_WGETRC unconditionally.

1998-01-31  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Initialize opt.ftp_pass here.
	(ftp_retrieve_dirs): Use alloca().

	* init.c (defaults): Don't initialize opt.ftp_pass.

	* sysdep.h (S_ISLNK): Declare for OS/2; ditto for lstat.
	From Ivan F. Martinez <ivanfm@ecodigit.com.br>.

1998-01-31  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (parse_robots): Check for comments more correctly.

	* host.c (ftp_getaddress): Use STRDUP_ALLOCA.
	(ftp_getaddress): Add diagnostics when reverse-lookup yields only
 	hostname.

1998-01-31  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget 1.5-b2 is released.

	* netrc.c (NETRC_FILE_NAME): Moved from netrc.h.

	* utils.c (proclist): Pass FNM_PATHNAME to fnmatch().

	* ftp-basic.c (ftp_pasv): Avoid unnecessary casting to unsigned
 	char.

	* log.c: Don't attempt to hide arguments from ansi2knr.

	* cmpt.c: Synched strptime() and mktime() with glibc-2.0.6.

	* ansi2knr.c: Use a later version, from fileutils-3.16l alpha.

	* ftp.c (getftp): Ditto.

	* http.c (gethttp): Use it.

	* retr.c (get_contents): New argument EXPECTED; pass it to
 	show_progress().
	(show_progress): New argument EXPECTED; use it to display
 	percentages.

	* init.c (setval): Ditto.

	* http.c (gethttp): Ditto.
	(http_loop): Ditto.

	* ftp.c (getftp): Ditto.
	(ftp_loop_internal): Ditto.

	* ftp-ls.c (ftp_parse_unix_ls): Use abort() instead of assert(0).

	* sysdep.h (CLOSE): Simplify; use DEBUGP.

	* netrc.c (search_netrc): Use alloca().

	* init.c (defaults): Initialize no_flush.

	* log.c (vlogmsg): Don't flush if no_flush.

	* options.h (struct options): New variable no_flush.

	* main.c (main): Don't play games with buffering.

	* log.c (vlogmsg): Flush the output after every message.

1998-01-31  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (parse_line): Ditto.

	* url.c (get_urls_html): Ditto.

	* main.c (main): Don't cast to unsigned char.

	* init.c (run_wgetrc): Don't cast to unsigned char.
	(parse_line): Accept char instead of unsigned char.

	* html.c (htmlfindurl): Use char instead of unsigned char.

	* all: Use them.

	* sysdep.h: Add wrappers to ctype macros to make them
 	eight-bit-clean:

1998-01-30  Hrvoje Niksic  <hniksic@srce.hr>

	* html.c (htmlfindurl): Download <img lowsrc=...>

	* main.c (main): Ignore SIGPIPE.

	* connect.c (select_fd): New argument WRITEP.
	(iwrite): Call select_fd().

1997-02-27  Fila Kolodny <fila@ibi.com>

	* ftp.c (ftp_retrieve_list): If retrieving symlink and the proper
 	one already exists, just skip it.

1998-01-30  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (gethttp): Cosmetic changes.

	* http.c (check_end): Allow `+D...' instead of `GMT'.
	From Fabrizio Pollastri <pollastri@cstv.to.cnr.it>.

	* url.c (process_ftp_type): New function.
	(parseurl): Use it.

	* connect.c (iwrite): Allow writing in a few chunks.
	(bindport): Made SRV static, so addr can point to it.
	(select_fd): Removed HPUX kludge.

	* host.c (free_hlist): Incorporated into clean_hosts().

1998-01-29  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (hlist): Made static.
	(search_address): Cosmetic change.

1998-01-29  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget v1.5-b1 is released.

	* http.c (hgetlen): Use sizeof() to get the header length.
	(hgetrange): Ditto.
	(hgettype): Ditto.
	(hgetlocation): Ditto.
	(hgetmodified): Ditto.
	(haccepts_none): Ditto.

	* main.c (main): Updated `--version' and `--help' output, as per
 	Francois Pinard's suggestions.

	* main.c: Include locale.h; call setlocale(), bindtextdomain() and 
	textdomain().

	* config.h.in: Define stubs for I18N3.

	* wget.h: Include libintl.h.

1998-01-28  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (mkstruct): Check for opt.cut_dirs.
	(mkstruct): alloca()-te more, xmalloc() less.

	* utils.c (load_file): Check for ferror().

	* url.c (get_urls_file): Close only the files we opened.
	(get_urls_html): Ditto.
	(count_slashes): New function.

	* http.h: Removed.

	* http.c (gethttp): Respect username and password provided by
	proxy URL.
	(base64_encode_line): Write into an existing buffer instead of
	malloc-ing a new one.
	(struct http_stat): Moved from http.h

	* retr.c (retrieve_url): Free SUF.

	* all: Removed lots of unnecessary .h dependencies.

	* html.c (global_state): Made static.

	* utils.h (ALLOCA_ARRAY): New macro.

	* main.c (main): New option `--cut-dirs'.

	* url.c (construct): Use alloca() for T.

	* utils.c (mkdirhier): Use STRDUP_ALLOCA.

	* host.c (_host_t): Moved from host.h.
	(struct host): Renamed from _host_t.
	(store_hostaddress): Use STRDUP_ALLOCA for INET_S.
	(realhost): Ditto.

	* host.h: Don't include url.h.

	* ftp.c (LIST_FILENAME): Moved from ftp.h.

	* init.c (DEFAULT_FTP_ACCT): Moved from ftp.h.

	* main.c (main): Enable log if the output goes to a TTY.

	* connect.h: Removed unused constant `BACKLOG'.

	* config.h.in: Check for isatty().

	* Makefile.in (LINK): Use CFLAGS when linking.

1998-01-27  Hrvoje Niksic  <hniksic@srce.hr>

	* mswindows.c (ws_hangup): Use redirect_output().

	* main.c (redirect_output_signal): New function; use
 	redirect_output().

	* log.c (redirect_output): New function, based on hangup(), which
	is deleted.

	* log.c (vlogmsg): New function.

	* wget.h (DEBUGP): Use debug_logmsg().

	* main.c (hangup): Use it.

	* log.c (log_dump): New function.

	* utils.h (DO_REALLOC): Use `long' for various sizes.

	* http.c (hskip_lws): Use `while', for clarity.
	(HTTP_DYNAMIC_LINE_BUFFER): New constant.
	(fetch_next_header): Use it instead of DYNAMIC_LINE_BUFFER.

	* ftp-basic.c (FTP_DYNAMIC_LINE_BUFFER): New constant.
	(ftp_response): Use it instead of DYNAMIC_LINE_BUFFER.

	* utils.c (DYNAMIC_LINE_BUFFER): Moved from utils.c.
	(LEGIBLE_SEPARATOR): Ditto.
	(FILE_BUFFER_SIZE): Ditto.

	* retr.c (BUFFER_SIZE): Moved from retr.h.

	* log.c: New file.
	(logmsg): Moved from utils.c.
	(debug_logmsg): New function.

	* mswindows.h: Include it here.

	* init.c: Ditto.

	* utils.c: Don't include <windows.h>.

1998-01-25  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (ftp_getaddress): Ditto.

	* main.c (main): Use it.

	* utils.h (STRDUP_ALLOCA): New macro.

	* init.c: Prepend `wget: ' to error messages printed on stderr.

	* utils.c (mkdirhier): Renamed from mymkdir.
	(touch): Renamed from my_touch.
	(pwd_cuserid): Renamed from my_cuserid().

1998-01-24  Andy Eskilsson  <andy.eskilsson@telelogic.se>

	* utils.c (accdir): Process wildcards.
	(proclist): New function.
	(accdir): Use it to avoid code repetition.

1998-01-24  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (parse_robots): Respect opt.useragent; use alloca().

	* http.c (gethttp): Construct useragent accordingly.

	* version.c: Changed version string to numbers-only.

	* main.c (print_help): List all the options.

	* mswindows.c (windows_main_junk): Initialize argv0 here.

1998-01-24  Karl Heuer  <kwzh@gnu.org>

	* netrc.c (search_netrc): Initialize `l' only after processing
 	netrc.

	* main.c (main): Don't trap SIGHUP if it's being ignored.

1998-01-24  Hrvoje Niksic  <hniksic@srce.hr>

	* all: Use logmsg().

	* utils.c (time_str): Moved from retr.c.
	(logmsg): New function.
	(logmsg_noflush): Ditto.

	* rbuf.c: New file, moved buf_* functions here.

	* ftp.c (ftp_expected_bytes): Moved from ftp-basic.c.

	* ftp-basic.c (ftp_rest): Use prnum().

	* ftp-basic.c: Ditto.

	* ftp.c: Use the new reading functions and macros.

	* retr.c (buf_initialize): New function.
	(buf_initialized_p): Ditto.
	(buf_uninitialize): Ditto.
	(buf_fd): Ditto.

	* http.c (fetch_next_header): Use the BUF_READCHAR macro for
 	efficiency.
	(gethttp): Use alloca() where appropriate.

	* retr.c (buf_readchar): Use it.
	(buf_peek): Use rstreams.

	* retr.h (BUF_READCHAR): New macro.

	* init.c (home_dir): Rewritten for clarity.
	(init_path): Ditto.

	* mswindows.c (ws_backgnd): Made static.
	(read_registry): Ditto.
	(ws_cleanup): Ditto.
	(ws_handler): Ditto.

1998-01-23  Hrvoje Niksic  <hniksic@srce.hr>

	* alloca.c: New file.

	* Makefile.in (ALLOCA): Define.

	* mswindows.c (ws_help): Constify.
	(ws_help): Use alloca.

	* mswindows.c: Reformat.

	* all: Added _(...) annotations for I18N snarfing and translation.

	* host.c (ftp_getaddress): Nuke SYSINFO.
	(ftp_getaddress): Don't use getdomainname().
	(ftp_getaddress): Use uname(), where available.

	* http.c (gethttp): Protect a stray fprintf().

	* init.c (settime): New function.
	(setval): Treat WAIT specially, allowing suffixes like `m' for
	minutes, etc.

1998-01-21  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (get_urls_html): Use alloca() for TEMP.

1998-01-21  Jordan Mendelson  <jordy@wserv.com>

	* url.c (rotate_backups): New function.

	* http.c (gethttp): Ditto.

	* ftp.c (getftp): Rotate backups.

1997-12-18  Hrvoje Niksic  <hniksic@srce.hr>

	* all: Renamed nmalloc(), nrealloc() and nstrdup() to xmalloc(),
 	xrealloc() and xstrdup().  Use the new functions.

	* url.c (decode_string): Made static.
	(has_proto): Ditto.
	(parse_dir): Ditto.
	(parse_uname): Ditto.
	(mkstruct): Ditto.
	(construct): Ditto.
	(construct_relative): Ditto.

	* retr.c (show_progress): Made static.

	* recur.c (robots_url): Made static.
	(retrieve_robots): Ditto.
	(parse_robots): Ditto.
	(robots_match): Ditto.

	* main.h: Removed.

	* main.c (printhelp): Made static.
	(hangup): Ditto.

	* init.c (comind): Made static.
	(defaults): Ditto.
	(init_path): Ditto.
	(run_wgetrc): Ditto.
	(onoff): Ditto.
	(setonoff): Ditto.
	(setnum): Ditto.
	(myatoi): Ditto.
	(getperms): Ditto.
	(setbytes): Ditto.

	* http.c (fetch_next_header): Made static.
	(hparsestatline): Ditto.
	(hskip_lws): Ditto.
	(hgetlen): Ditto.
	(hgetrange): Ditto.
	(hgettype): Ditto.
	(hgetlocation): Ditto.
	(hgetmodified): Ditto.
	(haccepts_none): Ditto.
	(gethttp): Ditto.
	(base64_encode_line): Ditto.
	(mktime_from_utc): Ditto.
	(http_atotm): Ditto.

	* html.c (idmatch): Made static.

	* host.c (search_host): Made static.
	(search_address): Ditto.
	(free_hlist): Ditto.

	* ftp.c (getftp): Made static.
	(ftp_loop_internal): Ditto.
	(ftp_get_listing): Ditto.
	(ftp_retrieve_list): Ditto.
	(ftp_retrieve_dirs): Ditto.
	(ftp_retrieve_glob): Ditto.
	(freefileinfo): Ditto.
	(delelement): Ditto.

	* ftp-ls.c (symperms): Made static.
	(ftp_parse_unix_ls): Ditto.

	* connect.c (select_fd): Made static.

	* utils.c (xmalloc): Renamed from nmalloc.
	(xrealloc): Renamed from nrealloc.
	(xstrdup): Renamed from nstrdup.

	* getopt.c (exchange): Use alloca.

	* mswindows.c (mycuserid): Use strncpy.

	* New files mswindows.c, mswindows.h, sysdep.h.  winjunk.c,
	systhings.h, windecl.h and winjunk.h removed.

	* mswindows.c (sleep): New function.

	* utils.c: Include <windows.h> under Windows.

1997-06-12  Darko Budor  <dbudor@zesoi.fer.hr>

	* url.h (URL_UNSAFE): Change default under Windows.

	* retr.c (retrieve_from_file): Respect opt.delete_after.

	* main.c (main): Call ws_help on Windows.

	* winjunk.c (windows_main_junk): New function.

	* main.c (main): Junk-process argv[0].

	* http.c (mktime_from_utc): Return -1 if mktime failed.

	* http.c (http_loop): Ditto.

	* ftp.c (ftp_loop_internal): Change title on Windows when using a
	new URL.

	* winjunk.c (getdomainname): Lots of functions.

1997-06-12  Hrvoje Niksic  <hniksic@srce.hr>

	* cmpt.c (strptime_internal): Handle years more correctly for
 	`%y'.

1997-06-09  Mike Thomas <mthomas@reality.ctron.com>

	* http.c (gethttp): Allocate enough space for
	`Proxy-Authorization' header.

1997-05-10  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Wget/1.4.5 is released.

1997-05-10  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (get_contents): Check return value of fwrite more
	carefully.

1997-03-30  Andreas Schwab  <schwab@issan.informatik.uni-dortmund.de>

	* cmpt.c (strptime_internal) [case 'Y']: Always subtract 1900 from
	year, regardless of century.

1997-03-30  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (isfile): Use `lstat' instead of `stat'.

1997-03-29  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (numdigit): Use explicit test.

1997-03-21  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): Always use `url_filename' to get u->local.

1997-03-20  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c: Recognize https.

1997-03-13  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (recursive_retrieve): Lowercase just the host name.

1997-03-09  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (get_urls_file): Use the correct test.
	(get_urls_html): Ditto.

1997-03-07  Hrvoje Niksic  <hniksic@srce.hr>

	* connect.c: Reverted addrlen to int.

	* init.c (parse_line): Check for -1 instead of NONE.

	* version.c: Changed version to 1.4.5.

1997-02-17  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c: New option netrc.
	(initialize): Don't parse .netrc.

	* cmpt.c (recursive): Return rp.
	(strptime_internal): Match the long strings first, the abbreviated
	second.

1997-02-16  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (check_end): New function.
	(http_atotm): Use it.
 
1997-02-13  gilles Cedoc  <gilles@cedocar.fr>

	* http.c (gethttp): Use them.

	* init.c: New options proxy_user and proxy_passwd.

1997-02-14  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_retrieve_list): Create links even if not relative.

1997-02-10  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (recursive_retrieve): Lowercase the host name, if the
 	URL is not "optimized".

	* host.c (realhost): Return l->hostname, even if it matches with
 	host.

1997-02-10  Marin Purgar  <pmc@asgard.hr>

	* connect.c: Make addrlen size_t instead of int.
	(conaddr): Ditto.

1997-02-09  Gregor Hoffleit  <flight@mathi.uni-heidelberg.DE>

	* systhings.h: Define S_ISLNK on NeXT too.

1997-02-09  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4.3.

	* url.c: Futher update to list of protostrings.
	(skip_proto): Skip `//' correctly for FTP and HTTP.

	* url.c (get_urls_html): Handle bogus `http:' things a little
 	different.

	* main.c (main): Removed `follow-ftp' from `f'.
	(main): Dumped the `prefix-files' and `file-prefix' options and
 	features; old and bogus.
	(main): Exit on failed setval() in `-e'.

	* http.c (fetch_next_header): Use it to detect header continuation
 	correctly.

	* retr.c (buf_peek): New function.

1997-02-08  Hrvoje Niksic  <hniksic@srce.hr>

	* wget.h: Include time.h and stuff.

1997-02-08  Roger Beeman  <beeman@cisco.com>

	* ftp.c: Include <time.h>

1997-02-07  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (findurl): Would read over buffer limits.

1997-02-06  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp-ls.c (ftp_parse_unix_ls): Allow spaces in file names.

1997-02-05  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_atotm): Initialize tm.is_dst.

1997-02-02  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (gethttp): Don't print the number of retrieved headers.

	* main.c (main): New option `--no-clobber', alias for `-nc'.

	* url.c: Recognize `https://'.

1997-02-01  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (herrmsg): Don't use h_errno.

1997-01-30  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (accept_domain): Use it.

	* main.c (main): New option `--exclude-domains'.

	* retr.c (retrieve_url): Use it.
	(retrieve_url): Bail out when an URL is redirecting to itself.

	* url.c (url_equal): New function.

1997-01-29  Hrvoje Niksic  <hniksic@srce.hr>

	* connect.c: Include arpa/inet.h instead of arpa/nameser.h.

	* http.c (mk_utc_time): New function.
	(http_atotm): Use it; handle time zones correctly.

1997-01-28  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c: Ditto.

	* ftp-basic.c: Use it instead of WRITE.

	* connect.c (iwrite): New function.

1997-01-27  Hrvoje Niksic  <hniksic@srce.hr>

	* cmpt.c (mktime): New function.

	* netrc.c: Include <sys/types.h>.

	* main.c (main): Wouldn't recognize --spider.

	* retr.c (rate): Use `B', `KB' and `MB'.
	(reset_timer,elapsed_time): Moved from utils.c.

	* ftp.c (ftp_retrieve_list): Ditto.

	* http.c (http_loop): Don't touch the file if opt.dfp.

1997-01-24  Hrvoje Niksic  <hniksic@srce.hr>

	* cmpt.c: New file.

	* ftp.c (ftp_retrieve_glob): New argument semantics.
	(ftp_retrieve_dirs): Use it.
	(ftp_loop): Ditto.

	* html.c (htmlfindurl): Recognize `'' as the quote char.

1997-01-23  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_loop_internal): Use it.

	* utils.c (remove_link): New function.

1997-01-22  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (retrieve_url): Require STRICT redirection URL.

	* url.c (parseurl): New argument STRICT.

	* http.c (hparsestatline): Be a little-bit less strict about
 	status line format.

1997-01-21  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (gethttp): Use it.

	* main.c (main): Don't use '<digit>' as options.

	* init.c: New option ignore_length.

	* http.c (gethttp): Ditto.
	(http_loop): Check for redirection without Location:.
	(gethttp): Don't print Length unless RETROKF.

	* ftp.c (getftp): Use it.

	* url.c (mkalldirs): New function.

	* utils.c (mymkdir): Don't check for existing non-directory.

	* url.c (mkstruct): Don't create the directory.

1997-01-20  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (setval): Removed NO_RECURSION checks.

1997-01-19  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4.3-pre2.

	* recur.c (recursive_retrieve): Bypass host checking only if URL
 	is ftp AND parent URL is not ftp.

	* ftp-basic.c (ftp_request): Print out Turtle Power.

	* ftp.c (ftp_loop): Call ftp_retrieve_glob with 0 if there's no
 	wildcard.
	(ftp_retrieve_glob): Call ftp_loop_internal even on empty list, if
 	not glob.

	* http.c (gethttp): Be a little bit smarter about status codes.

	* recur.c (recursive_retrieve): Always reset opt.recursive when
 	dealing with FTP.

1997-01-18  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (retrieve_url): New variable location_changed; use it for
 	tests instead of mynewloc.
	(retrieve_url): Allow heuristic adding of html.

	* url.c (url_filename): Don't use the `%' in Windows file names.

	* http.c (http_loop): Always time-stamp the local file.

	* http.c (http_loop): Ditto.

	* ftp.c (ftp_retrieve_list): Use it.

	* utils.c (my_touch): New function.

	* ftp.c (ftp_retrieve_list): Use #ifdef HAVE_STRUCT_UTIMBUF
 	instead of #ifndef NeXT.

	* utils.c (strptime): New version, by Ulrich Drepper.

1997-01-17  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (haccepts_none): Renamed from `haccepts_bytes'.
	(gethttp): If haccepts_none(), disable ACCEPTRANGES.
	(http_loop): Would remove ACCEPTRANGES.

	* ftp.c (getftp): Call ftp_list with NULL.

1997-01-15  Hrvoje Niksic  <hniksic@srce.hr>

	* html.c (ftp_index): Don't print minutes and seconds if we don't
 	know them; beautify the output.

	* ftp.c (getftp): Don't close the socket on FTPNSFOD.

1997-01-14  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (strptime): New function.
	(strptime): Don't use get_alt_number.
	(strptime): Don't use locale.
	(match_string): Made it a function.

1997-01-12  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_atotm): New function.
	(http_loop): Use it.

	* atotm.c: Removed from the distribution.

	* http.c (base64_encode_line): Rewrite.

1997-01-09  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Use ftp_expected_bytes; print size.

	* ftp-basic.c (ftp_response): Use ftp_last_respline.
	(ftp_expected_bytes): New function.

	* ftp.c (getftp): Print the unauthoritative file length.

	* ftp-ls.c: Renamed from ftp-unix.c.
	(ftp_parse_ls): Moved from ftp.c.
	(ftp_parse_unix_ls): Recognize seconds in time spec.
	(ftp_parse_unix_ls): Recognize year-less dates of the previous
 	year.

1997-01-08  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp-basic.c: Don't declare errno if #defined.

	* host.c (ftp_getaddress): Check for sysinfo legally.

1997-01-08  Darko Budor  <dbudor@diana.zems.fer.hr>

	* connect.c (iread): Use READ.

1996-12-23  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c: Recognize finger, rlogin, tn3270, mid and cid as valid
 	schemes.

1996-12-22  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (ftp_getaddress): Allow `.' in hostname.

1996-12-26  Darko Budor <dbudor@zems.fer.hr>

	* wget.h: READ and WRITE macros for use instead of read and write
	on sockets, grep READ *.c, grep WRITE *.c

	* wsstartup.c: new file - startup for winsock

	* wsstartup.h: new file

	* win32decl.h: new file - fixup for <errno.h> and winsock trouble

	* configure.bat: Configure utility for MSVC

	* src/Makefile.ms,config.h.ms: new files for use with MSVC 4.x

1996-12-22  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4.3-pre.

	* utils.c (prnum): Accept long.
	(legible): Use prnum().

	* connect.c (make_connection): Accept port as short.
	(bindport): Ditto.

	* http.c (gethttp): Use search_netrc.

1996-12-21  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Use search_netrc.

	* netrc.c (free_netrc): New function.

	* init.c (home_dir): New function.

	* url.c (convert_links): Allow REL2ABS changes.

1996-12-21  Gordon Matzigkeit  <gord@gnu.ai.mit.edu>

	* netrc.c: New file.
	(parse_netrc, maybe_add_to_list): New functions.

1996-12-17  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (retrieve_url): Reset opt.recursion before calling
 	ftp_loop if it is reached through newloc.

	* init.c (run_wgetrc): Print the wgetrc path too, when reporting
 	error; don't use "Syntax error", since we don't know if it is
 	really a syntax error.

1996-12-16  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (acceptable): Extract the filename part of the path.

	* recur.c (recursive_retrieve): Call acceptable() with the right
 	argument; would bug out on wildcards.

	* init.c (parse_line): Likewise.

	* html.c (htmlfindurl): Cast to char * when calling stuff.

1996-12-15  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Use ftp_pasv.

	* ftp-basic.c (ftp_request): Accept NULL value.
	(ftp_pasv): New function.

	* options.h (struct options): Add passive FTP option.

1996-12-15  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (parseurl): Debug output.

	* utils.c (path_simplify): New one, adapted from bash's
 	canonicalize_pathname().

1996-12-14  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Don't discard the buffer.

	* retr.c (get_contents): New parameter nobuf.

1996-12-13  Shawn McHorse  <riffraff@txdirect.net>

	* html.c (htmlfindurl): Recognize <meta contents="d; URL=...".

	* init.c (setval): Strip the trailing slashes on CVECDIR.

1996-12-13  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c: Make excludes and includes under CVECDIR instead of
 	CVEC.

1996-12-13  Shawn McHorse  <riffraff@txdirect.net>

	* url.c (get_urls_html): Skip "http:".

1996-12-13  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (strcasecmp): From glibc.
	(strncasecmp): Also.
	(strstr): Also.

	* url.c: Added javascript: to the list of URLs prefixes.

1996-12-12  Shawn McHorse  <riffraff@txdirect.net>

	* recur.c (retrieve_robots): Print the warning message only if
 	verbose.

1996-12-12  Gregor Hoffleit  <flight@mathi.uni-heidelberg.DE>

	* ftp.c (ftp_retrieve_list): Use NeXT old utime interface.

1996-12-12  Hrvoje Niksic  <hniksic@srce.hr>

	* systhings.h: New file.

	* ../configure.in: Check for utime.h

	* ftp.c: Check whether we have unistd.h.

1996-11-27  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (recursive_retrieve): Send the canonical URL as referer.
	(recursive_retrieve): Call get_urls_html with the canonical URL.

1996-12-13  Kaveh R. Ghazi  <ghazi@caip.rutgers.edu>

	* (configure.in, config.h.in, src/Makefile.in, src/*.[ch]): Add
 	ansi2knr support for compilers which don't support ANSI style
 	function prototypes and signatures.

	* (aclocal.m4, src/ansi2knr.c, src/ansi2knr.1): New files.

1996-11-26  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c: Use it; Recognize paths ending with "." and ".." as
 	directories.
	(url_filename): Append .n whenever file exists and could be a
 	directory.

	* url.h (ISDDOT): New macro.

	* init.c (parse_line): Use unsigned char.

	* url.c (get_urls_html): Cast to unsigned char * when calling
 	htmlfindurl.

	* html.c (htmlfindurl): Use unsigned char.

	* version.c: Changed version to 1.4.3.

1996-11-25  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4.2.

	* ftp.c (getftp): Simplified assertion.
	(ftp_loop_internal): Remove symlink before downloading.
	(ftp_retrieve_list): Unlink the symlink name before attempting to
 	create a symlink!

	* options.h (struct options): Renamed print_server_response to
 	server_response.

	* ftp.c (rel_constr): Removed.
	(ftp_retrieve_list): Don't use it.
	(ftp_retrieve_list): Use opt.retr_symlinks.

1996-11-24  Hrvoje Niksic  <hniksic@srce.hr>

	* main.c (main): New option retr_symlinks.

	* url.c (convert_links): Print verbose message.

1996-11-24  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): Reset newloc in the beginning of function;
 	would cause FMR in retrieve_url.

1996-11-23  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (convert_all_links): Find the URL of each HTML document,
 	and feed it to get_urls_html; would bug out.
	(convert_all_links): Check for l2 instead of dl; removed dl.

	* url.c (convert_links): Don't refer to freed newname.

	* recur.c (recursive_retrieve): Add this_url to urls_downloaded.

	* main.c (main): Print the OS_TYPE in the debug output, too.

	* recur.c (recursive_retrieve): Check for opt.delete_after.

	* main.c (main): New option delete-after.

	* init.c (setval): Cleaned up.

1996-11-21  Hrvoje Niksic  <hniksic@srce.hr>

	* Makefile.in (wget): Make `wget' the default target.

	* ftp.c (ftp_loop_internal): Move noclobber checking out of the
 	loop.
	(ftp_retrieve_list): Warn about non-matching sizes.

	* http.c (http_loop): Made -nc non-dependent on opt.recursive.

	* init.c (setnum): Renamed from setnuminf; New argument flags.
	(setval): Use it.

	* main.c (main): Sorted the options.
	(main): New option --wait.

1996-11-21  Shawn McHorse  <riffraff@txdirect.net>

	* html.c (htmlfindurl): Reset s->in_quote after getting out of
 	quotes.

1996-11-20  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Changed version to 1.4.2.

1996-11-20  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4.1.

	* html.c (html_quote_string): New function.
	(ftp_index): Use it.
	(htmlfindurl): A more gentle ending debug message.

	* ftp.c (ftp_loop): Check for opt.htmlify.

	* init.c: New command htmlify.

	* ftp.c (getftp): Nicer error messages, with `'-encapsulated
 	strings.
	(ftp_loop): Print size of index.html.

	* init.c (setval): Implement "styles".

	* main.c (main): New option dotstyle.

1996-11-19  Hrvoje Niksic  <hniksic@srce.hr>

        * ftp.c (getftp): Close the master socket in case of errors, after
        bindport().

        * connect.c (bindport): Initialize msock to -1.

        * ftp.c (getftp): Initialize dtsock to -1.

        * connect.c (closeport): Don't close sock if sock == -1.

1996-11-18  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (setnuminf): Nuked default value -- just leave unchanged.
	(setval): Don't send default values.
	(defaults): Use DEFAULT_TIMEOUT -- aaargh.

	* options.h (struct options): Use long for dot_bytes.

	* init.c (setquota): Renamed to setbytes.
	(setval): Use setbytes on DOTBYTES.

1996-11-17  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Initialize con->dltime.

	* recur.c (recursive_retrieve): Use same_host instead of
 	try_robots; simply load robots_txt whenever the host is changed.
	(recursive_retrieve): Free forbidden before calling parse_robots.

1996-11-16  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (show_progress): Use them.

	* options.h (struct options): New options dot_bytes, dots_on_line
 	and dot_spacing.

1996-11-16  Mark Boyns  <boyns@sdsu.edu>

	* recur.c (recursive_retrieve): Retrieve directories regardless of
 	acc/rej rules; check for empty u->file.

1996-11-14  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (setval): Use it.

	* utils.c (merge_vecs): New function.

	* init.c (setval): Reset the list-type functions when encountering
 	"".

1996-11-14  Shawn McHorse  <riffraff@txdirect.net>

	* recur.c (recursive_retrieve): Use base_url instead of this_url
 	for no_parent.

1996-11-14  Shawn McHorse  <riffraff@txdirect.net>

	* html.c (htmlfindurl): Reset s->in_quote after exiting the quote.

1996-11-13  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c (sepstring): Rewrote; don't use strtok.

	* recur.c (recursive_retrieve): Enter assorted this_url to slist
 	when running the first time.
	(retrieve_robots): Warn to ignore errors when robots are loaded.

	* utils.c (load_file): Moved from url.c.

	* http.c: Made static variables const too in h* functions.

	* main.c (main): Renamed --continue-ftp to --continue.

	* recur.c (recursive_retrieve): Use it.

	* utils.c (frontcmp): New function.

	* url.c (accdir): New function.

	* html.c (htmlfindurl): Recognize <area href=...>.

	* ftp.c (ftp_retrieve_dirs): Implemented opt.includes.

	* init.c (setval): Free the existing opt.excludes and
 	opt.includes, if available.

	* main.c (main): New option -I.

1996-11-12  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_retrieve_glob): Do not weed out directories.

	* version.c: Changed version to 1.4.1.

1996-11-11  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4.0.

1996-11-10  Hrvoje Niksic  <hniksic@srce.hr>

	* main.c (main): Free com and val after parse_line.
	(printhelp): Reorder the listing.

	* http.c: More robust header parsing.

	* http.c: Allow any number of spaces, or no spaces, precede ':'.
	(hskip_lws): New function.
	(haccepts_bytes): New function.
	(gethttp): Use it.

	* init.c (setval): Check header sanity.
	(setval): Allow resetting of headers.

1996-11-10  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): Don't use has_wildcards.

	* http.c (gethttp): Free all_headers -- would leak.

	* recur.c (recursive_retrieve): Initialize depth to 1 instead of
 	0 -- this fixes a long-standing bug in -rl.

1996-11-09  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c: Use -1 as "impossible" value for con->fd.

	* url.h (URL_SEPARATOR): Don't treat `*' and `+' as separators.

	* init.c (parse_line): Use isalpha.

	* ftp-unix.c: Use HAVE_UNISTD_H.

	* mtch.c (has_wildcards): Don't match \.

	* http.c (http_loop): Warn on HTTP wildcard usage.

1996-11-08  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (url_filename): Do not create numbered suffixes if
 	opt.noclobber -- would bug out on -nc.

1996-11-07  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (parse_robots): Don't chuck out the commands without
 	arguments (`Disallow:<empty>' didn't work).
	(parse_robots): Compare versions lowercase.
	(parse_robots): Match on base_version, not version_string!
	(parse_robots): Handle comments properly.
	(parse_robots): Match versions in a sane way.

	* init.c: Print nicer error messages.

	* version.c: Changed version to 1.4.0.

1996-11-06  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4.0-test2.

	* init.c (run_wgetrc): Close fp.

	* ftp.c (ftp_retrieve_dirs): Allocate the correct length for
 	u->dir.

1996-11-06  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c (setquota): Allow inf as quota specification.

1996-11-05  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_retrieve_dirs): Return QUOTEXC if quota exceeded.
	(ftp_retrieve_glob): Return QUOTEXC on quota exceeded.

	* main.c (main): Check for quota by comparison with downloaded
 	stuff, not from status.

	* connect.c (select_fd): Should compile on HPUX without warnings now.

	* ftp.c (ftp_get_listing): Check whether ftp_loop_internal
 	returned RETROK.

1996-11-04  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_retrieve_glob): Print the pattern nicely.
	(getftp): Return FTPRETRINT on control connection error.

	* html.c (htmlfindurl): Recognize <embed src=...> and
	<bgsound src=...>.
	(ftp_index): Handle username and password correctly.

	* main.c (main): Made `-np' a synonim for --no-parent.

1996-11-02  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_loop): Check for opt.ftp_glob too before calling
 	ftp_retrieve_glob.

	* version.c: Changed version to 1.4.0-test2.

1996-11-02  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4.0-test1.

	* url.c (str_url): Don't use sprintf when creating %2F-prefixed
 	directory.
	(convert_links): Removed definition of make_backup.

	* http.h: Removed definition of MAX_ERROR_LENGTH.

	* host.c (ftp_getaddress): Check for "(none)" domains.

	* ftp.c (ftp_retrieve_dirs): Docfix.

	* http.c (gethttp): Use ou->referer instead of u->referer.

	* retr.c (retrieve_url): Reset u to avoid freeing pointers twice;
 	this was known to cause coredumps on Linux.

	* html.c (ftp_index): Cast the argument to local_time to time_t *.

1996-11-01  Hrvoje Niksic  <hniksic@srce.hr>

	* connect.c (select_fd): Use exceptfds -- once and for all.

	* retr.c (retrieve_from_file): Free filename after
 	recursive_retrieve.
	(retrieve_from_file): Send RFIRST_TIME to recursive_retrieve on
 	first-time retrieval.
	(retrieve_from_file): Return uerr_t; new argument, count.
	(retrieve_from_file): Break on QUOTEXC.

	* init.c (setquota): Fixed a bug that caused rejection of
 	non-postfixed values..

1996-10-30  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Changed name to wget.

	* connect.c (iread): Smarter use of select.
	(select_fd): Set errno on timeout.  If not timeout, return 1
 	instead of 0.

1996-10-29  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_loop_internal): Don't use con->cmd before
 	establishing it.

1996-10-26  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (gethttp): Send correct referer when using proxy.
	(gethttp): Use struct urlinfo ou to access the relevant data; send
 	correct authorization in all cases.

	* host.c (same_host): Use skip_uname to skip username and
 	password.

	* url.c (skip_uname): New function.
	(parseurl): Use it.

	* host.c (same_host): Do not assume HTTP -- same_host should now
 	be totally foolproof.

	* url.c (skip_proto): New function.
	(parse_uname): Use it.

	* http.c (gethttp): Create local user and passwd from what is
 	given.

	* url.c (parseurl): Check for HTTP username and password too.

1996-10-25  Hrvoje Niksic  <hniksic@srce.hr>

	* config.h.in: Removed #define gethostbyname R...

1996-10-22  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Changed version to 1.4.0-test1.

1996-10-21  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b29.

	* recur.c (recursive_retrieve): Check for no_parent.

	* init.c (setval): Option update.

	* main.c (main): New option no-parent.

	* options.h (struct options): New variable no_parent.

	* recur.c (recursive_retrieve): Only files are checked for
 	opt.accepts and opt.rejects.
	(recursive_retrieve): Check directories for opt.excludes.
	(recursive_retrieve): Make the dir absolute when checking
 	opt.excludes.

	* html.c (htmlfindurl): Recognize <applet code=...> and <script
 	src=...>

1996-10-18  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (getftp): Do not line-break assert entries at all.
	(ftp_retrieve_dirs): docfix.

	* connect.c (select_fd): Use fd + 1 as nfds.

	* version.c: Changed version to 1.4b29.

1996-10-18  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b28.

	* ftp.c (ftp_loop_internal): Check whether f->size == len and
 	don't continue the loop if it is.
	(ftp_get_listing): Remove list_filename on unsuccesful loop.

1996-10-17  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_loop_internal): Use strcpy to initialize tmp.
	(getftp): Do not use multiline assert.

	* http.c (hparsestatline): Use mjr and mnr instead of major and
 	minor, which don't compile on Ultrix.
	(http_loop): Use strcpy() to initialize tmp.

	* all: Geturl -> Fetch

1996-10-17  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (parse_robots): Fixed an off-by-one bug when looking for
 	':'.

	* html.c (htmlfindurl): Fixed several possible off-by-one bugs by
 	moving `bufsize &&' to the beginning of each check in for-loops.

	* recur.c (parse_robots): Close fp on exit.

	* url.c (mymkdir): Check for each directory before creating.

1996-10-16  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Changed version to 1.4b28.

1996-10-16  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b27.

	* init.c (parse_line): Use isspace.
	(parse_line): Free *com on all errors.

	* ftp.c (ftp_loop): Change FTPOK to RETROK before exiting.
	(delelement): Use next instead of f->next and prev instead of
 	f->prev.
	(delelement): Free the members of the deleted element.

	* http.c (http_loop): Do not return RETROK on code != 20x.

	* init.c (cleanup): Free opt.user_header.
	(cleanup): Free opt.domains.

	* url.c (freelists): Moved to cleanup().

	* http.c (hparsestatline): Docfix.

	* main.c (main): Return with error status on unsuccesful
 	retrieval.

	* init.c (setval): Do not remove listing when mirroring.

	* url.c (url_filename): Use opt.fileprefix.

	* ftp.c (ftp_get_listing): Use url_filename to get filename for
 	.listing.

	* main.c (main): New option: -rn.

1996-10-15  Hrvoje Niksic  <hniksic@srce.hr>

	* Makefile.in (RM): Added RM = rm -f.

	* host.c (clean_hosts): New function.
	(free_hlist): Just free the list, no reset.

	* version.c: Changed version to 1.4b27.

1996-10-13  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b26.

	* retr.c (retrieve_from_file): If call get_urls_html with
 	opt.spider to make it silent in spider mode.

	* url.c (str_url): Use CLEANDUP instead of URL_CLEANSE.

	* url.h (CLEANDUP): New macro.

	* http.c (gethttp): Fixed a bug that freed location only when it
 	was NULL.

	* retr.c (retrieve_url): Free url if it will not be stored,
 	i.e. newloc is NULL.

	* html.c (htmlfindurl): Handle exiting from quotes correctly; the
 	old version would bug out on <a href="x#a"href="y">.

	* html.h (state_t): New member in_quote.

	* html.c (htmlfindurl): Free s->attr at the beginning of
 	attr-loop.

	* recur.c (recursive_retrieve): Recognize RCLEANUP.
	(tried_robots): Make hosts a global variable.
	(recursive_retrieve): Free constr after URL host optimization.
	(tried_robots): Free urlinfo before exiting.

	* utils.c (free_slist): New function.

	* recur.c (recursive_retrieve): Use flags to add cleanup
 	possibility.

	* main.c (main): Free filename after recursive_retrieve.

	* http.c (gethttp): Store successful responses too.

1996-10-12  Hrvoje Niksic  <hniksic@srce.hr>

	* all: Constified the whole source.  This required some minor
 	changes in many functions in url.c, possibly introducing bugs -- I
 	hope not.

	* ftp-basic.c: Removed last_respline.

	* http.c (gethttp): Free type.

	* host.c (same_host): Free real1 and real2.

	* main.c (main): New option --spider.

	* retr.c (get_contents): Don't reset errno.

	* main.c (main): Sorted the options.

	* connect.c (iread): Set errno to ETIMEDOUT only if it was left
 	uninitialized by select().

	* http.c (http_loop): Print the time when the connection is
 	closed.
	(gethttp): Debug-print the HTTP request.

1996-10-11  Hrvoje Niksic  <hniksic@srce.hr>

	* connect.c (iread): Do not try reading after timeout.

	* main.c (main): Would bug out on -T.

	* connect.c (select_fd): Do not use exceptfds.
	(iread): Set ETIMEDOUT on select_fd <= 0.

	* version.c: Changed version to 1.4b26.

1996-10-10  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b25.

	* ftp-unix.c (ftp_parse_unix_ls): Ignore lines without file name
 	or link name.

	* http.c (gethttp): Add errcode to struct hstat.
	(http_loop): Use it.

	* url.c (no_proxy_match): Simplify using char** for no_proxy.

	* options.h (struct options): Make opt.no_proxy a vector.

	* utils.c (sepstring): Use !*s instead of !strlen(s).

	* init.c (setval): Set opt.maxreclevel to 0 on --mirror.
	(getperms): Use ISODIGIT instead of isdigit.

	* ftp.c (getftp): Print time.

	* main.c (main): Use legible output of downloaded quantity.

	* ftp.c (getftp): Use elapsed_time().
	(ftp_loop_internal): Use rate().

	* http.c (http_loop): Add download ratio output; Use rate().

	* utils.c (rate): New function.

1996-10-09  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): Use timer.

	* ftp.c: Split to ftp-basic.c and ftp.c

	* utils.c (reset_timer): New function.
	(elapsed_time): New function.

	* retr.c (show_progress): Make bytes_in_line and offs long; should
 	work on 16-bit machines.

1996-10-08  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (in_acclist): New argument backward.

	* ftp.c (ftp_retrieve_glob): Use acceptable() to determine whether
 	a file should be retrieved according to suffix.
	(ftp_get_listing): Check the return value of unlink; Do not call
 	ftp_retrieve_dirs if depth reached maxreclevel.
	(ftp_retrieve_dirs): Check whether the directory is in
 	exclude-list.

	* main.c (main): Print the version number at the beginning of
 	DEBUG output.
	(main): Use strrchr when creating exec_name.

	* ftp.c (ftp_retrieve_glob): Do not close control connection.

	* version.c: Changed version to 1.4b25.

1996-10-07  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b24.

	* Makefile.in: Rewrite.

	* ftp.c (ftp_loop_internal): Likewise.

	* retr.c (time_str): Check for failed time().

	* html.c (htmlfindurl): Recognize <fig src> and <overlay src> from
 	HTML3.0.

	* retr.c (time_str): Return time_t *.

	* connect.c (bindport): Close msock on unsuccesful bind.
	(bindport): The same for getsockname and listen.

	* retr.c (retrieve_url): Allow any number of retries on
	proxy.

	* http.c (gethttp): Do not treat errno == 0 as timeout.
	(http_loop): Likewise.
	(http_loop): Cosmetic changes.

	* connect.c (iread): Set errno to ETIMEDOUT in case of timeout.

	* retr.c (get_contents): Reset errno.

	* ftp.c (getftp): Minor fixes.

1996-10-06  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c: Do not use backups.

	* geturl.1 (WARNING): Warn that man-page could be obsolete.

	* getopt.c (getopt_long): Moved to getopt.c

	* geturl.texi: Enhanced.

	* main.c (main): Use it.

	* recur.c (convert_all_links): New function.

	* utils.c (add_slist): New argument flags.

	* recur.c (recursive_retrieve): Update a list of downloaded URLs.
	(parse_robots): Do not chuck out empty value fields.
	(parse_robots): Make yourself welcome on empty Disallow.

	* version.c: Changed version to 1.4b24.

1996-10-06  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b23.

	* ftp.c (ftp_loop_internal): Get the time after getftp.

	* Makefile.in (install.info): New target.
	(install): Use it.

	* http.c (http_loop): Fix output when doing -O.

1996-10-05  Hrvoje Niksic  <hniksic@srce.hr>

	* geturl.texi: New file.

	* main.c (main): Do not print the warnings and download summary if
 	opt.quiet is set.

	* version.c: Changed version to 1.4b23.

1996-10-05  Hrvoje Niksic  <hniksic@srce.hr>

	* "Released" 1.4b22.

	* atotm.c (atotm): Use True and False instead of TRUE and FALSE,
 	to avoid redefinition warnings.

	* host.c (store_hostaddress): Use memcpy() to copy the address
 	returned by inet_addr.

	* version.c: Changed version to 1.4b22.

1996-10-04  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b21.

	* ftp-unix.c (ftp_parse_ls): Renamed to ftp_parse_unix_ls.

	* ftp.c (ftp_port): Use conaddr.
	(getftp): Print the file length.
	(ftp_retrieve_list): Check the stamps of plain files only.

	* connect.c (closeport): Do not call shutdown().
	(conaddr): New function.

	* html.c (ftp_index): Made it dfp-aware.

	* init.c (cleanup): New name of freemem. Close opt.dfp.

	* ftp.c (getftp): Use opt.dfp if it is set.

	* ftp-unix.c (ftp_parse_ls): Recognize time in h:mm format.

	* ftp.c (ftp_retrieve_dirs): Fixed a bug that caused incorrect
 	CWDs to be sent with recursive FTP retrievals.

1996-10-03  Hrvoje Niksic  <hniksic@srce.hr>

	* recur.c (parse_robots): Made it more compliant with "official"
 	specifications.

	* http.c: New function.

	* ftp-unix.c (ftp_parse_ls): Added better debug output.

	* ftp.c (getftp): Print out the LIST in case of
 	opt.print_server_response.

	* version.c: Changed version to 1.4b21.

1996-10-01  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b20.

	* README: Update.

	* http.c (gethttp): Preset lengths of various headers instead of
 	calculating them dynamically.
	(gethttp): Check for 206 partial contents.

1996-09-30  Hrvoje Niksic  <hniksic@srce.hr>

	* configure.in: Set SYSTEM_GETURLRC to $libdir/geturlrc

	* http.c (gethttp): Send the port number in the Host: header.

1996-09-29  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (gethttp): Send host: header.
	(gethttp): Add the possibility of user-defined headers.
	(gethttp): Move decision about pragma: no-cache to http_loop,
 	where it belongs.
	(gethttp): Pass a struct instead of enormous argument list.
	(http_loop): Use a new, fancier display format.
	(ftp_loop): Likewise.

	* main.c: (hangup): Turn off buffering of the new log file.

	* install-sh: Likewise.

	* config.sub: Replace with the one in autoconf-2.10

	* geturl.1: Update.

	* init.c: New options httpuser and httppasswd.

	* http.c: (base64_encode_line): New function.
	(gethttp): Send authentication.

	* connect.c (make_connection): Use store_hostaddress.

1996-09-28  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (store_hostaddress): New function.

	* NEWS: Update.

	* http.c (hgetrange): New function.
	(gethttp): Use ranges.

	* utils.c (numdigit): Accept long instead of int.

	* http.c (http_loop): Add restart capabilities.

	* ftp.c (ftp_retrieve_glob): Fixed a bug that could cause matchres
 	being used uninitialized.
	(ftp_retrieve_list): Similar fix.

	* host.c (add_hlist): Fixed a bug that could cause cmp being used
 	uninitialized.

	* url.c (construct_relative): New function.

	* recur.c (recursive_retrieve): Use it.

	* retr.c (convert_links): New function.

1996-09-27  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (free_urlpos): New function.

	* recur.c (recursive_retrieve): Adapt.

	* url.c (get_urls_html): Return a linked list instead of a vector.

	* url.c (get_urls_file): Return a linked list instead of a vector.

	* geturl.1: Update.

	* http.c (gethttp): Implement it.

	* init.c (setval): New option: SAVEHEADERS

	* ftp.c (ftp_loop_internal): Do not set restval if listing is to
 	be retrieved. Lack of this test caused bugs when the connection
 	was lost during listing.

	* retr.c (retrieve_url): Fixed a bug that caused
 	coredumps. *newloc is now reset by default.
	(retrieve_url): Lift the twenty-tries limit on proxies.

	* version.c: Changed version to 1.4b20.

1996-09-20  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b19.

1996-09-19  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_loop_internal): Renamed from ftp_1fl_loop.
	(getftp): Changed prototype to accept ccon *.

1996-09-17  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_retrieve_list): Fixed a bug that caused setting
 	incorrect values to files pointed to by symbolic links.
	(ftp_1fl_loop): Do not count listings among the downloaded URL-s.

1996-09-16  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (mkstruct): Do not prepend "./" in front of a pathname.

	* main.c (main): New option: --user-agent.

	* geturl.1: Ditto.

	* init.h: Ditto.

	* init.c (setval): Ditto.

	* main.c (main): Rename "server-headers" to "server-response".

	* ftp-unix.c (ftp_parse_ls): Check for asterisks at the end of
 	executables in 'ls -F' listings.

1996-09-15  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (parseurl): Remove realloc() and sprintf().
	(str_url): Get rid of sprintf().

	* recur.c (recursive_retrieve): Enable FTP recursion through proxy
 	servers.

	* url.h (URL_CLEANSE): Made it else-resistant.
	(USE_PROXY): New macro.

1996-09-14  Hrvoje Niksic  <hniksic@srce.hr>

	* NEWS: Update.

	* version.c: Changed version to 1.4b19.

1996-09-14  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b18.

	* url.c: Made it reallocate space exponentially.

1996-09-14  Drazen Kacar  <dave@fly.cc.fer.hr>

	* html.c (htmlfindurl): Added <frame src> and <iframe src> among
 	the list of stuff to fetch.

1996-09-13  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (get_urls_html): Fixed a bug that caused SIGSEGV's with
 	-Fi.

	* html.c (htmlfindurl): Rewrite.

	* http.c (gethttp): Use opt.proxy_cache.

	* main.c (main): Added --cache option.

	* ftp.c (ftp_response): Print server response if opt.print_server
 	response is set.
	(getftp): Print newlines after each request if the server response
 	is to be printed.
	(ftp_response): Copy the last response line to last_respline.

	* http.c (gethttp): Add Pragma: nocache for retried
 	proxy-retrievals.

	* ftp.c (getftp): Use it.

	* retr.c (buf_discard): New function.

	* ftp.c (ftp_response): Use buf_readchar().
	(getftp): Flush the control connection buffer before calling
 	get_contents().

	* retr.c (buf_readchar): New function.
	(buf_flush): New function.
	(get_contents): Use buf_readchar() instead of read(x, x, 1).
	(get_contents): Use buf_flush.

1996-09-12  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c: Incorporate changes to ftp_response.

	* ftp.c (ftp_response): Allocate the server response dynamically,
 	as in read_whole_line and fetch_next_header.

	* utils.c (read_whole_line): Fixed a bug that prevented reading
 	the last line if it is not \n-terminated. Also fixed a possible
 	memory overflow.

	* http.c (fetch_next_header): Return malloc-ed string as large as
 	needed.
	(gethttp): Use new fetch_next_header.

1996-09-12  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (hgetlen): Compute the header length the first time only.
	(hgettype): Ditto.
	(hgetlocation): Ditto.
	(hgetmodified): Ditto.

1996-09-11  Hrvoje Niksic  <hniksic@srce.hr>

	* sample.geturlrc: Update.

1996-09-10  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): Ditto.

	* ftp.c (getftp): Open the output file as binary.

	* version.c: Changed version to 1.4b18.

1996-09-10  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b17.

	* ftp-unix.c (ftp_parse_ls): If unable to open file, return NULL
 	instead of failed assertion.

1996-09-09  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_get_listing): Add a numbered suffix to LIST_FILENAME
 	if a file of that name already exists.

1996-09-05  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_1fl_loop): Handler FTPPORTERR and FOPENERR correctly.

	* config.h.in: Define gethostbyname as Rgethostbyname when using
 	Socks.

	* configure.in: Check for -lresolv if using Socks.

	* version.c: Changed version to 1.4b17.

1996-07-15  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b16.

	* http.c (gethttp): More intelligent check for first line of HTTP
 	response.
	(gethttp): Would bug out on time-stamping.

	* version.c: Changed version to 1.4b16.

1996-07-11  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Released 1.4b15.

	* http.c (http_loop): Print \n after the loop entry, not before.

	* url.c (url_filename): Use ISDOT.

	* url.h (ISDOT): New macro.

	* recur.c (recursive_retrieve): Change only opt.recursive for
 	following FTP.

1996-07-11  Antonio Rosella <antonio.rosella@agip.it>

	* socks/geturl.cgi: Fixed version No.

	* socks/download-netscape.html: Ditto.

	* socks/download.html: Changed socks.html to download.html.

1996-07-11  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (url_filename): Check for opt.dirstruct instead for
 	opt.recursive && opt.dirstruct.

	* init.c (defaults): Ditto.
	(defaults): Reset dirstruct by default.
	(setval): Set opt.dirstruct whenever setting recursive.

	* init.h: Removed FORCEDIRHIER.

	* INSTALL: Added -L to socks-description.

	* version.c: Changed version to 1.4b15.

1996-07-10  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b14.

	* geturl.1: Update AUTHOR to include Rosella as contributor.

	* NEWS: Update.

	* socks/geturl.cgi: Simplified command creation, nuked <blink>.

	* socks/geturl.cgi: Wrap nutscape extensions within if $netscape.
	(cal_time): Fix == to eq.

	* socks/geturl.cgi: GPL-ized with permission of A. Rosella.

	* geturl.1 (hostname): Moved URL CONVENTIONS to the beginning.

	* Makefile.in: Use @VERSION@.

	* configure.in: Check version from version.c.

	* socks/geturl.cgi: Changed /pub/bin/perl to /usr/bin/perl.

	* socks/download.html: Created from download-netscape.html, made
 	HTML-2.0 compliant.

	* recur.c (recursive_retrieve): Set opt.force_dir_hier when
 	following FTP links from recursions.

1996-07-09  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (mymkdir): Fixed a bug that prevented mymkdir() to create
 	absolute directories correctly.

	* version.c: Changed version to 1.4b14.

1996-07-09  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b13.

	* url.c (make_backup): New function.

	* http.c (http_loop): Make a backup copy of the local file (using
 	rename(2)) before opening it.

	* main.c (main): Added --backups.

	* host.c (ftp_getaddress): Bail out on failed mycuserid().
	(ftp_getaddress): Check for leading dot on MY_DOMAIN.
	(ftp_getaddress): Check for empty, null or (null) domain.

	* url.c (get_urls_html): If this_url is NULL, the base must have a
 	protocol.
	(parseurl): Use has_proto.

	* retr.c (retrieve_url): Warn when proxy is used with more than 20
 	retries.

	* url.c (mkstruct): Create the directory (calling mymkdir()) only
 	if it is not already there.
	(has_proto): New function.
	(get_urls_html): Eliminate the remaining call to findurl -- use
 	has_proto.

	* geturl.1: Ditto.

	* main.c: Change -X to -x.

	* url.c (url_filename): Simplify creation of filename if
 	prefix_files is set.
	(url_filename): Simplify everything. And I do mean *everything*.
	(mkstruct): Add dir_prefix before hostname.
	(path_simplify): Fixed a bug that caused writing outside the path
 	string in case of "." and ".." path strings.

1996-07-06  Hrvoje Niksic  <hniksic@srce.hr>

	* init.c: Added --mirror.

	* main.c (main): Added -X to force saving of directory hierarchy.

	* ftp.c (ftp_retrieve_list): Added recursion depth counter.
	(ftp_retrieve_list): Check whether quota is exceeded.

	* url.c (get_urls_html): Skip leading blanks for absolute URIs.

	* http.c (gethttp): Use referer if present.

	* recur.c (recursive_retrieve): Set u->referer before calling
 	retrieve_url.

	* url.c (newurl): Use memset to nullify the struct members.
	(freeurl): Free the referer field too.

	* url.h: Added referer to urlinfo.

	* geturl.1: Updated the manual to document some of the new features.

	* utils.c (numdigit): Moved from url.c.

	* README: Rewritten.

	* config.h.in: Add the support for socks.

	* configure.in: Add the support for socks.

	* url.c (url_filename): If the dir_prefix is ".", work with just
 	the file name.
	(url_filename): Do not look for .n extensions if timestamping if
 	turned on.

	* retr.c (show_progress): Skip the over-abundant restval data, and
 	print the rest of it with ',' instead of '.'.

1996-07-05  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (show_progress): Changed second arg. to long (as it
 	should be).
	(show_progress): Moved to retr.c.
	(get_contents): Moved to retr.c.

	* version.c: Change version to 1.4b13.

1996-07-05  Hrvoje Lacko <hlacko@fly.cc.fer.hr>

	* url.c (in_acclist): Would return after the first suffix.

1996-07-04  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: "Released" 1.4b12.

	* url.c (path_simplify): More kludgifications.
	(get_urls_html): Use new parameters for htmlfindurl.

	* html.c: Removed memorizing "parser states", since the new
 	organization does not require them.

	* init.c (run_geturlrc): Use read_whole_line.

	* ftp-unix.c (ftp_parse_ls): Use read_whole_line.

	* recur.c (parse_robots): Use read_whole_line.

	* utils.c (read_whole_line): New function.

	* recur.c (tried_robots): Use add_slist/in_slist, *much* cleaner.

	* host.c (ngethostbyname): Call inet_addr just once. Yet to be
 	tested on OSF and Ultrix.
	(add_hlist): New function.
	(free_hlist): New function.
	(search_host): New function.
	(search_address): New function.
	(realhost): Use search_host, search_address and add_hlist.
	(same_host): Replaced realloc() with strdupdelim(), made
 	case-insensitive, fixed a memory leak.

	* html.c (ftp_index): Fixed tm_min and tm_sec to be tm_hour and
 	tm_min, like intended.

	* version.c: Change user agent information to
 	Geturl/version.

1996-07-03  Hrvoje Niksic  <hniksic@srce.hr>

	* utils.c: Renamed nmalloc.c to utils.c, .h likewise.

	* url.c (acceptable): Always accept directories.

	* ftp-unix.c (ftp_parse_ls): Support brain-damaged "ls -F"-loving
 	servers by stripping trailing @ from symlinks and trailing / from
 	directories.

	* ftp.c (ftp_loop): Debugged the "enhanced" heuristics. :-)

	* url.c (skip_url): Use toupper instead of UCASE.

	* host.c (sufmatch): Made it case-insensitive.

	* url.c (match_backwards_or_pattern): Fixed i == -1 to j == -1.
	(match_backwards): New function, instead of
 	match_backwards_or_pattern.

	* recur.c (recursive_retrieve): Increased performance by
 	introducing inl, which reduces number of calls to in_slist to only
 	one.

	* ftp.c (ftp_loop): Enhanced the heuristics that decides which
 	routine to use.

	* main.c (printhelp): Removed the warranty stuff.

1996-07-02  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (add_slist): Simplify.
	(match_backwards_or_pattern): New function.
	(in_acclist): Use match_backwards_or_pattern.
	(matches): Remove.

1996-06-30  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (ftp_loop): Call ftp_index on empty file names, if not
 	recursive.

	* html.c (ftp_index): Fixed to work. Beautified the output.

	* ftp.c (ftp_retrieve_glob): Another argument to control whether
 	globbing is to be used.
	(ftp_retrieve_list): Compare the time-stamps of local and remote
 	files to determine whether to download.

1996-06-29  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (rel_constr): New function.

	* retr.c (retrieve_from_file): Check for text/html before
 	retrieving recursively.

	* main.c (main): Check whether the file is HTML before going into
 	recursive HTML retrieving.

	* ftp.c (ftp_retrieve_list): Manage directories.
	(ftp_retrieve_glob): Pass all the file-types to ftp_retrieve_list.
	(ftp_1fl_loop): Fixed a bug that caused con->com to be incorrectly
 	initialized, causing bugchecks in getftp to fail.

	* configure.in: Check for symlink.

	* ftp.c (ftp_retrieve_list): Added support for symlinks.

	* version.c: "Released" 1.4b10.

	* atotm.c (atotm): Redeclared as time_t.

	* init.c: New variable "timestamping".

	* main.c (main): New option 'N'.

	* http.c (hgetlocation): Case-insensitive match.
	(hgetmodified): New function.
	(http_loop): Implement time-stamping.

1996-06-28  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: Changed version to 1.4b10

	* atotm.c: New file, from phttpd.

	* options.h (struct options): New parameter timestamping.

	* version.c: 1.4b9 "released".

	* recur.c (recursive_retrieve): Used linked list (ulist) for
 	faster storing of URLs.

	* url.c (get_urls_html): Removed the old kludge with comparing the
 	outputs of htmlfindurl and findurl.
	(get_urls_html): Added better protocol support here.
	(create_hash): Removed, as well as add_hash and in_hash.
	(addslist): New function.
	(in_slist): ditto

	* version.c: Released 1.4b8, changed version to b9.

1996-06-27  Hrvoje Niksic  <hniksic@srce.hr>

	* ftp.c (freefileinfo): New function.
	(delelement): New function.

	* everywhere: GPL!

	* ftp.c (ftp_loop): Use ccon.
	(ftp_retrieve_glob): Likewise.

	* ftp.h: Define ccon, to define status of control connection.

	* ftp.c (ftp_get_listing): New function.
	(ftp_retrieve_more): New function.
	(ftp_retrieve_glob): New function.

1996-06-25  Hrvoje Niksic  <hniksic@srce.hr>

	* configure.in: Removed the search for cuserid().

	* init.c (getmode): Renamed to getperms.

1996-06-24  Hrvoje Niksic  <hniksic@srce.hr>

	* version.c: New version.

	* main.c (hangup): New function, that handles hangup. Hangup
        signal now causes geturl to stop writing on stdout, and to write
        to a log file.

	* ftp.c (getftp): "Released" 1.4b7.

	* html.c (htmlfindurl): Ignore everything inside <head>...</head>.
	(ftp_index): Use fileinfo/urlinfo.

	* ftp-unix.c (ftp_parse_ls): New function.
	(symperms): New function.

	* ftp.c (ftp_1fl_loop): New function, to handle 1-file loops.

	* retr.c (retrieve_url): Added FTP support.

1996-06-23  Hrvoje Niksic  <hniksic@srce.hr>

	* geturl.h: Removed NOTFTP2HTML enum.
	Added DO_LOGIN, DO_CWD and DO_LIST. LIST_ONLY is obsolete.

	* ftp.c (getftp): Resynched with urlinfo.
	(getftp): Removed HMTL-ization of index.html from getftp.

	* version.c: 1.4b6 "released".

	* options.h (options): New struct, to keep options in.

	* http.c (http_loop,gethttp): Synched with proxy.

	* retr.c (retrieve_url): Implemented proxy retrieval.

	* main.c (main): Use retrieve_from_file.

1996-06-22  Hrvoje Niksic  <hniksic@srce.hr>

	* retr.c (retrieve_from_file): New function.

	* url.c (parseurl): Modified to return URLOK if all OK. Protocol
        can be found in u->proto.

	* ftp.c (ftp_response): Fixed to accept multi-line responses as
        per RFC 959.

	* recr.c (recursive_retrieve): Take newloc from retrieve_url.

	* url.c (mymkdir): Removed the file of the same name, if one
        exists.
	(isfile): New function.
	(mkstruct): Fixed the '/' glitches.
	(path_simplify): Hacked to treat something/.. correctly.

1996-06-21  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (gethttp): Close the socket after error in headers.
	(http_loop): HEOF no longer a fatal header.

	* loop.c (retrieve_url): When dt is NULL, do not modify it. This
        simplifies the syntax of calling retrieve_url.

	* recr.c (recursive_retrieve): Modified to use get_urls_html.

	* url.c (get_urls_file): New function.
	(get_urls_html): New function.

	* recr.c (recursive_retrieve): Patched up to conform to the
        standards.

	* http.c (gethttp): Synched with the rest...
	(gethttp): Treat only CONREFUSED specially, with connection
	errors.

	* init.c,geturl.1,http.c (http_loop): Removed kill_error.

1996-06-20  Hrvoje Niksic  <hniksic@srce.hr>

	* http.c (http_loop): New function.

	* loop.c: Removed *lots* of stuff from retrieve_url.

	* url.c (parseurl): Changed to work with urlinfo. Integrated
        username finding and path parsing.
	(newurl): New function.
	(freeurl): New function.
	(mkstruct): Removed the old bogosities, made it urlinfo-compliant.
	(url_filename): Likewise.
	(path_simplify): Accept relative paths too.
	(opt_url): Made urlinfo-compliant, removed bogosities.
	(path_simplify): Expanded to accept relative paths.
	(str_url): A replacement for hide_url
	(decode_string): Fixed a bug that caused malfunctioning when
	encountering an illegal %.. combination.
	(opt_url): Removed the argument. Dot-optimizations are now default.

	* nmalloc.c (strdupdelim): New function.

	* url.h: Added the urlinfo structure

1996-06-19  Hrvoje Niksic  <hniksic@srce.hr>

	* url.c (hide_url): Thrown out the protocol assertion. Do not
        change the URL if the protocol if not recognized.
	(findurl): Put continue instead of break.

1996-06-18  Hrvoje Niksic  <hniksic@srce.hr>

	* sample.geturlrc: Changed the defaults to be commented out and
        harmless (previous defaults caused pains if copied to
        ~/.geturlrc).

	* http.c (gethttp): Print the HTTP request in debug mode.

	* connect.c (iread): Added EINTR check loop to select-ing
        too. EINTR is now correctly handled with select().

	* TODO: new file

1996-05-07  Hrvoje Niksic  <hniksic@srce.hr>

	* host.c (same_host): Made the function a little bit more
        intelligent regarding diversified URL syntaxes.

	* url.c (skip_url): Spaces are now skipped after URL:

	* Released 1.3.1 with the patch to prevent crashing when sending
        NULL to robot* functions and the patch to compile "out of the box"
        on AIX.

	* recr.c (recursive_retrieve): Added checking whether this_url is
	NULL when calling the robot functions.

	* ChangeLog: New file.
