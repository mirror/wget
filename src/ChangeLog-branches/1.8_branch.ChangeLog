2002-05-28  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8.2 is released.

2002-02-11  Christian Lackas <delta@lackas.net>

	* Recurive downloading for https fixed.

2002-05-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (bar_set_params): Fall back to dot progress if the
	terminal type is "emacs".

2002-05-24  Hack Kampbjorn  <wget@hack.kampbjorn.com>

	* url.c (mkstruct) [WINDOWS || __CYGWIN__]: Use `_' to separate domain
	from port number in filename instead of `:'.

2002-05-24  Ian Abbott  <abbotti@mev.co.uk>

	* url.c (mkstruct) [WINDOWS || __CYGWIN__]: Replace query character
	`?' with `@'.
	(compose_file_name) [WINDOWS || __CYGWIN__]: Ditto.

2002-04-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (struct progress_implementation): Use PARAMS when
	declaring the parameters of *create, *update, *finish, and
	*set_params.

	* netrc.c: Ditto.

	* http.c: Reformat some function definitions so that ansi2knr can
	read them.

	* hash.c (struct hash_table): Use the PARAMS macro around
	parameters in the declaration of hash_function and test_function.
	(prime_size): Spell 2580823717UL and 3355070839UL as (unsigned
	long)0x99d43ea5 and (unsigned long)0xc7fa5177 respectively, so
	that pre-ANSI compilers can read them.
	(find_mapping): Use PARAMS when declaring EQUALS.
	(hash_table_put): Ditto.

	* ftp.h: Wrap the parameters of ftp_index declaration in PARAMS.

	* cookies.c (cookie_new): Use (unsigned long)0 instead of 0UL,
	which was unsupported by pre-ANSI compilers.

	From Nelson H. F. Beebe <beebe@math.utah.edu>, for the most part.

2002-04-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (bar_create): If INITIAL is larger than TOTAL, fix
	TOTAL.
	(bar_finish): Likewise.

2002-02-19  Andreas Damm  <andreas-sourceforge@radab.org>

	* wget.h (DO_REALLOC_FROM_ALLOCA): Multiply with sizeof(type) when
	calling xmalloc and memcpy.

2002-01-07  Ian Abbott <abbotti@mev.co.uk>

	* url.c (uri_merge_1): Deal with "net path" relative URL (one that
	starts with "//").

2002-01-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (parse_uname): URL-decode *USER and *PASSWD.

2002-02-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (retrieve_tree): Handle the case when start_url doesn't
	parse.

2002-01-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* netrc.c (parse_netrc): Skip leading whitespace before testing
	whether the line is empty.  Empty lines still contain the line
	terminator.

2002-01-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Invalidate SOCK if get_contents encountered an
	error.

2002-04-16  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): If Content-Type is not given, assume
	text/html.

2002-02-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-url.c (tag_handle_meta): Don't crash on <meta
	http-equiv=refresh> where content is missing.

2002-01-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* headers.c (header_get): Strip trailing whitespace from the
	header.

2002-01-15  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen_sslfunc.c (ssl_iread): Call select on the file descriptor
	only if no data is pending in SSL buffers.
	From tony@bluetail.com.

2001-12-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8.1 is released.

2001-12-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8.1-pre3 is released.

2001-12-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (retrieve_tree): Enqueue the canonical representation of
	start_url, so that the test against dl_url_file_map works.

2001-12-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* log.c (logputs): Check for requested verbosity before printing
	anything.

2001-12-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-url.c (tag_handle_link): Treat the "shortcut icon" link as
	inline.

2001-12-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (retrieve_tree): Make a copy of file obtained from
	dl_url_file_map because the code calls xfree(file) later.

2001-12-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (register_html): Maintain a hash table of HTML files
	along with the list.  Disallow duplicates.
	(retrieve_tree): Use downloaded_html_set to check whether the file
	found in dl_url_file_map is an HTML file, and descend into it if
	so.
	(convert_all_links): Don't guard against duplicates in
	downloaded_html_list, since they are no longer possible.

2001-12-18  Ian Abbott  <abbotti@mev.co.uk>

	* recur.c (retrieve_tree): Pass on referring URL when retrieving
	recursed URL.

2001-12-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8.1-pre2 is released.

2001-12-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (sleep_between_retrievals): Simplify indentation.

2001-12-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen_sslfunc.c (ssl_init_prng): Use random_number to get a byte
	of "randomness" at a time.
	(ssl_init_prng): Don't seed the PRNG; random_number will do that.

	* retr.c (sleep_between_retrievals): Use it.  Make sure that the
	random amount averages in opt.wait.
	(sleep_between_retrievals): Don't seed the PRNG; random_number
	will do that.

	* utils.c (random_number): New function.

2001-12-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (path_simplify): Move here from utils.c, and make static.

2001-12-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c (wgetrc_file_name): Print correct message when loading
	getenv("WGETRC") fails.

2001-12-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (register_download): Don't abort when one URL references
	two different files.

2001-12-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Check for conn->scheme, not u->scheme, before
	calling ssl_iwrite.

2001-12-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8.1-pre1 is released.

2001-12-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* res.c (matches): Fix broken URL in the docstring.

2001-12-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-url.c (tag_url_attributes): Mark <embed href=...> as
	external.

2001-12-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (get_urls_file): Cosmetic changes.

2001-12-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-url.c (append_one_url): Resurrect warning when unable to
	resolve a relative link.

2001-12-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-url.c (collect_tags_mapper): Break into several functions.
	(tag_url_attributes): Collect <embed href=...>.

2001-12-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* host.c: New type ipv4_address.  Use it consistently instead of
	`unsigned char[4]' and `unsigned char *'.
	(pretty_print_address): Accept a `const void *', to require even
	less casting.

2001-12-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp-ls.c (ftp_parse_vms_ls): Fix obvious memory leaks.

2001-12-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (main): Initialize progress after fork_to_background, so
	that it knows when to use dots.

	* mswindows.c (ws_hangup): Call log_request_redirect_output.

	* utils.c (fork_to_background): Print the PID of the child
	process.

	* log.c (log_request_redirect_output): Set a flag that output
	redirection has been requested.  Doing anything else in a signal
	handler is unsafe.
	(check_redirect_output): New function: check whether redirection
	has been requested and, if so, call redirect_output().
	(logputs): Call check_redirect_output.
	(logprintf): Ditto.
	(debug_logprintf): Ditto.
	(redirect_output): Print clearer messages.

	* main.c (redirect_output_signal): Don't call
	redirect_output_signal directly.  Instead, call
	log_request_redirect_output.

	* utils.c (memfatal): Ditto.

	* progress.c (display_image): Use it.

	* log.c (log_set_save_context): New function: allow the caller to
	turn off saving log context lines.

2001-12-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* host.c (address_list_set_faulty): Uncomment a sanity check.

2001-12-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (long_to_string): Return a pointer after where the
	number ends.
	(long_to_string): Rename to number_to_string.

2001-12-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (path_simplify): Correctly handle the unlikely case that
	b starts out as path + 1.

2001-12-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (path_simplify): Rewrite, with better comments, and
	without the use of strcpy to move overlapping blocks.

2001-12-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c (cmd_spec_progress): Resurrect.  Check whether VAL is a
	valid progress type before setting it.

2001-12-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (main): Remove stray debugging message.

2001-12-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (create_image): Fix ETA padding when hours are prined.

2001-12-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8 is released.

2001-12-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (reencode_string): Declare static.

	* res.c (registered_specs): Declare static.

	* progress.c (current_impl_locked): Declare static.

	* log.c (flush_log_p): Declare static.
	(needs_flushing): Ditto.

	* http.c (digest_authentication_encode): Declare static.

	* html-url.c (init_interesting): Declare static.

	* host.c (host_name_addresses_map): Declare static.

	* cookies.c (find_matching_chains): Declare static.

	* ftp-ls.c (ftp_parse_vms_ls): Warn about the memory leak
	indicated by lint.

	* utils.c (path_simplify): Remove unused variable STUB_CHAR.

	* host.c (address_list_set_faulty): Document that INDEX is
	currently unused.

	* url.c (rewrite_shorthand_url): Remove unused variable PATH.

2001-12-08  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8-pre2 is released.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (progress_handle_sigwinch): Set up the signal again.

	* utils.c: Include <sys/termios.h>, where Solaris defines
	TIOCGWINSZ.

	* progress.c (bar_create): Don't use the last column on the screen.
	(create_image): Pad ETA to constant size.  Pad SIZE to nine digits
	only until it exceeded them.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8-pre1 is released.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (progress_create): Make sure that, when the output is
	redirected, the progress implementation gets changed to the
	fallback one.
	(bar_set_params): Set current_impl_locked to 1 when "force" is
	specified.
	(progress_create): Don't change the progress implementation if
	current_impl_locked is non-zero.

	* main.c (redirect_output_signal): Call
	progress_schedule_redirect.

	* progress.c (progress_schedule_redirect): New function.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* log.c (logvprintf): Restructure to allow being called multiple
	times.
	(logprintf): Call logvprintf in a loop.
	(debug_logprintf): Ditto.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen_sslfunc.c (ssl_init_prng): Allow the user to disable EGD by
	setting egd_file it to empty string.

	* main.c (main): Change the option name from --sslegdsock to
	--egd-file.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen_sslfunc.c (ssl_init_prng): Make the printed message
	translatable.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (scheme_disable): New function.

	* main.c (main): Call ssl_init_prng from here rather than from
	init_ssl, so that it has a chance to disable support for https
	before a URL has been resolved.

	* gen_sslfunc.c (ssl_init_prng): Seed with rand() if all else
	failed.
	(ssl_init_prng): Disable support for https if seeding the PRNG
	fails.

2001-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (read_whole_line): Handle lines beginning with \0.

2001-12-05  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (convert_all_links): Guard against duplicates in
	downloaded_html_files.
	(register_download): Don't invalidate similar-looking URLs.
	(match_except_index): New function.

2001-12-05  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (path_simplify): Document with test cases.

2001-12-04  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen_sslfunc.c: Ditto.

	* rbuf.c: Include <string.h>.

2001-12-04  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (retrieve_tree): Check whether the URL was already
	downloaded before downloading it again.
	(descend_child_p): Renamed to download_child_p.
	(register_download): When one URL is downloaded to a file already
	"owned" by another URL, delete all references that map any URL to
	that file.
	(register_delete_file): New function.
	(retrieve_tree): Use it after deleting a file.

	* url.c (url_parse): Re-canonicalize the URL also if the path is
	empty, so that e.g. "http://www.server.com" ->
	"http://www.server.com/".
	(lowercase_str): Use ISUPPER instead of !ISLOWER.

	* retr.c (retrieve_url): Use the canonical URL form when calling
	register_download().

2001-12-04  Ian Abbott <abbotti@mev.co.uk>

	* snprintf.c (dopr): Use `unsigned int' as the second argument to
	va_arg when casting to `unsigned short' is intended.

2001-12-04  Herold Heiko  <Heiko.Herold@previnet.it>

	* gen_sslfunc.c: on windows provide ssl crypto random 
	  initialization through RAND_screen(); could possibly
	  be not enough for strong ssl communication (see the 
	  relevant manual page from the openssl package).

2001-12-04  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (local_quote_string): Reenable quoting of question marks,
	but only when `--html-extension' is used.

2001-12-03  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8-beta3 is released.

2001-12-03  Hrvoje Niksic  <hniksic@arsdigita.com>

	* snprintf.c (dopr): Cast the result of va_arg to short int and
	short unsigned int where these types are expected to be used.

2001-12-03  Hrvoje Niksic  <hniksic@arsdigita.com>

	* snprintf.c (dopr): Replace `short int' and `unsigned short int'
	with `int' when using it as the second argument to `va_arg'.

2001-12-03  Hrvoje Niksic  <hniksic@arsdigita.com>

	* host.c (address_list_new_one): New function.
	(lookup_host): Use it.

2001-12-03  Andre Majorel  <amajorel@teaser.fr>

	* host.c (lookup_host): Don't initialize TMPSTORE directly because
	it's not legal C.

2001-12-03  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp-basic.c (ftp_port): Don't return HOSTERR if we fail getting
	the socket data.

	* ftp.c: Ditto.

	* http.c: No need to declare h_errno.

	* host.c: Declare h_errno.

2001-12-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (file_merge): If BASE doesn't contain a slash, just
	return a copy of FILE.

2001-12-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8-beta2 is released.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): When PWD fails, assume "/".

	* ftp-basic.c (ftp_syst): Fix indentation.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (get_urls_file): If opt.base_href is specified, merge each
	URL with the base.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (print_help): Don't document the removed `-nh'.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (url_full_path): Document better.

	* http.c (gethttp): Use the full path when creating digest
	authorization.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c (path_matches): Return 0 if PREFIX doesn't begin with
	'/'.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c (path_matches): FULL_PATH doesn't begin with '/', but
	PREFIX does.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c (check_domain_match): Reimplement to match Netscape's
	"preliminary specification" for cookies.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (replace_attr_refresh_hack): New function.
	(convert_links): Call replace_attr_refresh_hack for Refresh
	links.  It will add the "TMOUT; URL=" junk before the link.

	* html-url.c (collect_tags_mapper): Set ID to the ID of the
	"content" attribute, not "http-equiv".
	(collect_tags_mapper): Don't use OFFSET to hack the raw_* values;
	instead, store the information that this entry belongs to a
	"refresh" link.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.8-beta1 is released.

2001-12-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (retrieve_tree): Allow -p retrievals to exceed maximum
	depth by more than one.

2001-11-30  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): Don't allow more than 20 redirections.

2001-11-30  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (retrieve_tree): Skip the non-inline entries when
	enqueuing the children of a leaf HTML node in -p mode.
	(descend_url_p): Ignore opt.no_parent when in -p mode and UPOS is
	"inline".

	* html-url.c (get_urls_html): Don't accept dash_p_leaf_HTML.
	(collect_tags_mapper): When an entry is "inline", mark it as such.

	* recur.c (descend_url_p): Fix test when checking for
	acceptance/rejection rules.

2001-10-31 Daniel BODEA <dali@dali-designs.com>

	* netrc.c (search_netrc): When slack_default is 0, still look for
	an account with matching password, just not the "default account".
	HTTP Authorization using .netrc should now work as expected.

2001-11-30  T. Bharath  <TBharath@responsenetworks.com>

	* http.c (persistent_available_p): Call SHUTDOWN_SSL if
	test_socket_open fails.

2001-11-30  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (display_image): Just print one CR to reset the
	cursor position.

2001-11-30  Christian Fraenkel  <c.fraenkel@gmx.net>

	* init.c: New command `ssl_egd_sock'.

	* main.c (main): New option `--sslegdsock'.

	* gen_sslfunc.c (ssl_init_prng): Seed the RNG using EGD.

2001-11-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cmpt.c (memmove): Include a simple memmove implementation.

2001-11-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* headers: Guard against header files being included twice.

2001-11-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen-md5.c: Use unsigned char * as the buffer argument to
	gen_md5_update.

2001-11-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* connect.h: Declare select_fd.

2001-11-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (descend_url_p): When resolving no_parent, compare with
	start_url, not parent url.  Otherwise link from /a/b/ to /a/c/
	wouldn't be followed, although the download started from /a/.

2001-01-23  Herold Heiko  <Heiko.Herold@previnet.it>

	* config.h.ms, mswindows.h: defined HAVE_ISATTY, use _isatty for
	MS VC; somebody with Borland compiler please check and provide
	patch if possible;

	* cmpt.c: provided a usleep emulation.

2001-11-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* host.c (address_list_new): Initialize al->faulty.

2001-11-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_process_range): Accept the broken output of
	"JavaWebServer/1.1.1".

2001-11-28  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (dot_set_params): If PARAMS is unspecified, use
	dot_style, if available.

	* init.c: Ditto.

	* main.c (main): Resurect --dot-style.

	* progress.c (dot_finish): Print the quantity if we're left at the
	beginning of a row.

2001-11-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cmpt.c (random): Removed.

	* retr.c (sleep_between_retrievals): Use the more portable rand()
	instead of random().

2001-11-27  Ian Abbott <abbotti@mev.co.uk>

	* retr.c (retrieve_from_file): Initialize `new_file' to NULL to
	prevent seg fault.

2001-11-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* connect.c (connect_to_many): Use address_list_set_faulty to
	prevent the faulty address from being reused.

	* host.c (address_list_set_faulty): New function.
	(address_list_get_bounds): New function, instead of
	address_list_count.

2001-11-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (convert_links): Don't translate %d-%d.

	* main.c (print_help): Remove stray HAVE_RANDOM code.

2001-11-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): Improve output after sending PASV.  Don't
	attempt to "look up" the IP address we already know; call
	connect_to_one directly.

2001-11-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c: Change the default progress implementation to "bar".

2001-11-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (bar_create): Print two newlines.

2001-11-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cmpt.c (random): New function, a simple-minded replacement for
	random() on systems that don't have it.

2001-11-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* config.h.in: Put a HAVE_USLEEP stub.

	* cmpt.c (usleep): Replacement implementation of usleep using
	select.

	* init.c: New option init_rate.

	* main.c (main): New option --limit-rate.

	* retr.c (limit_bandwidth): New function.
	(get_contents): Call it to limit the bandwidth used when
	downloading.

	* progress.c (dot_update): Would print the wrong download speed on
	rows other than the first one when the download was continued.
	(dot_finish): Ditto.

2001-11-26  Ian Abbott <abbotti@mev.co.uk>

	* http.c (gethttp): fix undeclared variable 'err' when compiled
	with HAVE_SSL.

2001-11-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c: Don't allocate new timers; use the timing data
	propagated from the caller.

	* retr.c (get_contents): Allocate and use a timer.

2001-11-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (last_host_ip): Made into an address_list.
	(invalidate_persistent): Release pc_last_host_ip.
	(register_persistent): Use lookup_host.
	(persistent_available_p): Check for equality of hosts using
	address_list_match_all.  Call address_list_release.
	(http_cleanup): New function.

	* ftp.c (getftp): Use lookup_host and connect_to_many.

	* http.c (gethttp): Use lookup_host and connect_to_many.

	* connect.c (make_connection): Removed.
	(connect_to_one): New function.
	(connect_to_many): Ditto.
	(set_connection_host_name): Ditto.

	* host.c (lookup_host): New function; new return type.
	(address_list_new): New function.
	(address_list_count): Ditto.
	(address_list_copy_one): Ditto.
	(address_list_delete): Ditto.
	(address_list_release): Ditto.
	(pretty_print_address): Ditto.

2001-11-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (retrieve_tree): In case of followed redirection,
	blacklist the pre-redirection URL.

2001-11-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (descend_redirect_p): New function.
	(retrieve_tree): Make sure redirections are not blindly followed.

2001-11-04  Alan Eldridge  <alane@geeksrus.net>

	* config.h.in: added HAVE_RANDOM.

	* options.h: added random_wait to struct options.

	* main.c (print_help [HAVE_RANDOM], main): added arg parsing, help
	for --random-wait.

	* retr.c (sleep_between_retrievals) [HAVE_RANDOM]: added
	implementation of random wait times.

	* init.c (commands): added "randomwait" keyword.

2001-11-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (descend_url_p): Be more conservative with blacklisting
	URLs.
	(convert_all_links): Print how many files have been converted, and
	how long it took.

	* progress.c (create_image): Place the number of downloaded bytes
	right after the progress bar.

	* utils.c (suffix): Return a pointer into the string.

2001-11-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (convert_links): Handle CO_NULLIFY_BASE.

	* recur.c (retrieve_tree): Ignore download-ignorable children.
	(convert_all_links): Specify CO_NULLIFY_BASE when link_base_p.

	* html-url.c (handle_link): Return the newly created urlpos.
	(collect_tags_mapper): When dealing with BASE, store the base
	reference and mark it as download-ignorable.

2001-11-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (convert_links): Attempt to quote '?' as "%3F" when
	linking to local files.  Given up on the attempt, as it breaks
	local browsing.

2001-11-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (private_initialize): Removed.
	(main): Don't call private_initialize.

	* http.c: Call lookup_host.

	* host.c (host_init): Removed.
	(add_host_to_cache): Initialize host_name_address_map here, on
	demand.
	(ngethostbyname): Commented out.

	* connect.c (make_connection): Remove dead code; use lookup_host.

	* host.c (store_hostaddress): Renamed to lookup_host and reversed
	the args.
	Removed host_address_name_map and host_slave_master_map.

2001-11-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (dot_create): Align the "[ skipping ... ]" string
	with the dots.

	* retr.c (rate): Split into two functions: calc_rate and
	retr_rate.

	* progress.c (create_image): Draw a dummy progress bar even when
	total size is unknown.
	(display_image): Place the text cursor at the end of the "image".

2001-11-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (reencode_string): Use unsigned char, not char --
	otherwise the hex digits come out wrong for 8-bit chars such as
	nbsp.
	(lowercase_str): New function.
	(url_parse): Canonicalize u->url if needed.
	(get_urls_file): Parse each URL, and return only the valid ones.
	(free_urlpos): Call url_free.
	(mkstruct): Add :port if the port is non-standard.
	(mkstruct): Append the query string to the file name, if any.
	(urlpath_length): Use strpbrk_or_eos.
	(uri_merge_1): Handle the cases where LINK is an empty string,
	where LINK consists only of query, and where LINK consists only of
	fragment.
	(convert_links): Count and report both kinds of conversion.
	(downloaded_file): Use a hash table, not a list.
	(downloaded_files_free): Free the hash table.

	* retr.c (retrieve_from_file): Ditto.

	* main.c (main): Call either retrieve_url or retrieve_tree
	for each URL, not both.

	* retr.c (register_all_redirections): New function.
	(register_redirections_mapper): Ditto.
	(retrieve_url): Register the redirections.
	(retrieve_url): Make the string "Error parsing proxy ..." 
	translatable.

	* res.c (add_path): Strip leading slash from robots.txt paths so
	that the path representations are "compatible".
	(free_specs): Free each individual path, too.
	(res_cleanup): New function.
	(cleanup_hash_table_mapper): Ditto.

	* recur.c (url_queue_new): New function.
	(url_queue_delete): Ditto.
	(url_enqueue): Ditto.
	(url_dequeue): Ditto.
	(retrieve_tree): New function, replacement for recursive_retrieve.
	(descend_url_p): New function.
	(register_redirection): New function.

	* progress.c (create_image): Cosmetic changes.

	* init.c (cleanup): Do all those complex cleanups only if
	DEBUG_MALLOC is defined.

	* main.c: Removed --simple-check and the corresponding
	simple_host_check in init.c.

	* html-url.c (handle_link): Parse the URL here, and propagate the
	parsed URL to the caller, who would otherwise have to parse it
	again.

	* host.c (xstrdup_lower): Moved to utils.c.
	(realhost): Removed.
	(same_host): Ditto.

2001-11-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (path_simplify): Preserver the (non-)existence of
	leading slash.  Return non-zero if changes were made.

2001-11-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (bar_update): Don't modify bp->total_length if it is
	zero.

2001-11-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): When the redirection URL doesn't parse,
	print the correct error message rather than "UNKNOWN".

2001-11-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (bar_finish): If the timer didn't record any time
	since the download beginning, fake 1ms.

2001-11-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (recursive_retrieve): Fix typo.

2001-11-23  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (create_image): Don't translate "%ld ".

2001-11-23  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (bar_set_params): Allow the user to force the use of
	the bar.

2001-11-23  Lemble Gregory  <gregory.lemble@st.com>

	* gen_sslfunc.c (ssl_init_prng): New function; seed the SSL RNG.

2001-11-23  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c: Renamed dp_* functions to dot_* for greater clarity
	and consistency with bar_*.
	(print_download_speed): Get rid of the unneeded '@' character.
	(create_image): Fix download rate geometry.

	* progress.c (print_elapsed): Remove spurious space.
	(print_elapsed): Renamed to print_download_speed, since that's
	what it does.

2001-11-23  Hrvoje Niksic  <hniksic@arsdigita.com>

	* progress.c (bar_update): If the downloaded amount becomes larger
	than the expected amount, adjust the expected amount accordingly.

2001-11-23  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (determine_screen_width): New function.

	* main.c (main): New option `--progress=TYPE'.
	(main): Implement compatibility with the old option `--dot-style'.

	* init.c: Removed cmd_spec_dotstyle -- that logic is now in
	dp_set_params.
	(cmd_spec_progress): New function.

	* retr.c (get_contents): Use the progress_* functions instead of
	the old show_progress().
	(show_progress): Removed.
	(rate): Print "xxxx.xx K/s" instead of "KB/s".  Ditto for MB/s,
	etc.

	* progress.c (set_progress_implementation): New function.
	(valid_progress_implementation_p): Ditto.
	(progress_create): Ditto.
	(progress_update): Ditto.
	(progress_finish): Ditto.
	(dp_create): Ditto.
	(dp_update): Ditto.
	(dp_finish): Ditto.
	(dp_set_params): Ditto.
	(print_elapsed): Ditto.

2001-11-22  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (show_progress): Use it.

	* log.c (log_set_flush): New function.

2001-11-22  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (path_simplify): Don't remove trailing slashes.

	* ftp.c (ftp_get_listing): Use it.

	* utils.c (file_merge): New function.

	* url.c (opt_url): Removed.

	* recur.c (recursive_retrieve): Inline "opt_url" logic.

	* main.c (main): Use xfree(), not free().

	* url.c (rewrite_url_maybe): Renamed to rewrite_shorthand_url.

	* ftp.c (ccon): Move `ccon' typedef here, since it's only used
	internally.

	* config.h.in: Include a stub for HAVE_STRPBRK.

	* cmpt.c (strpbrk): Include a replacement for systems without
	strpbrk().

	* ftp.c: Use url_set_dir and url_set_file when modifying the URL.

	* url.c (url_set_dir): New function.
	(url_set_file): Ditto.

	* ftp-basic.c (ftp_process_type): Process FTP type here; the URL
	parser makes the URL "params" available, so we can do that in this
	function.

	* retr.c: Ditto.

	* ftp.c: Ditto; pass the local file information in `ccon'.

	* http.c: Get rid of the ugly kludge that had URL being replaced
	with the proxy URL when proxy retrieval was requested.  Use a
	separate parameter to http_loop and gethttp for the proxy URL.

	* http.c: Changed to reflect the fact that local file, proxy, and
	referer information are no longer stored in struct url.  The local
	file information is passed in `struct hstat' now.

	* url.c: Reworked URL parsing to be more regular.  Reencode the
	URL using reencode_string.
	Removed non-URL-related information from struct url.  This
	includes fields `proxy', `local', and `referer'.

2001-11-22  Jochen Hein  <jochen@jochen.org>

	* main.c (main): Split the copyright notice for easier
	translation.

2001-08-21  Dave Turner <dct25@hermes.cam.ac.uk>

	* ftp-basic.c (ftp_size): New function to send non-standard SIZE
	  command to server to request file size.
	* ftp.h (ftp_size): Export it.
	* ftp.c (getftp): Use new ftp_size function if restoring
	  transfer of a file with unknown size.

2001-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (parseurl): Don't depend on the now-obsolete TYPE.

2001-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (getproxy): Handle URL shorthands.

2001-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c: Remove --wait / --waitretry backwards compatibility
	code.
	
2001-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (main): Use it.

	* url.c (rewrite_url_maybe): New function.

2001-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c: Clean up handling of URL schemes.

2001-05-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c: Get rid of `protostrings'.
	(skip_proto): Don't use protostrings.
	(has_proto): Ditto.

2001-11-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* Makefile.in: Conditionally compile getopt.o.

2001-11-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* md5.h: Renamed to gnu-md5.h.

	* md5.c: Renamed to gnu-md5.c.

	* http.c: Ditto.

	* ftp-opie.c: Use the new macros.

	* sysdep.h: Define md5-related macros.

	* config.h.in: Define HAVE_SOLARIS_MD5 or HAVE_BUILTIN_MD5
	depending on which md5 implementation is used.

2001-11-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* res.c (res_register_specs): Initialize OLD and HP_OLD to appease
	the compiler.

2001-11-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Print the whole response line when printing
	headers is requested.

2001-05-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* res.c: New file.  Implement all RES-related code here.

2001-11-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.7.1 is released.

2001-11-16  Hrvoje Niksic  <hniksic@arsdigita.com>

	* headers.c (header_extract_number): Ignore trailing whitespace.

2001-08-24  Ian Abbott  <abbotti@mev.co.uk>

	* html-url.c (collect_tags_mapper): Fix bug converting links
	with -k option for tags with multiple link attributes by
	handling links in the order they appear.

2001-08-15  Ian Abbott  <abbotti@mev.co.uk>

	* ftp.c (ftp_loop_internal): Avoid a potential buffer overflow in
	  the call to the 'rate' function by moving it past the error
	  checking for the 'getftp' function return value.

2001-11-16  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-parse.c (advance_declaration): Use 0x22 instead of '"' or
	'\"'.  Different compilers' assert macros are broken in different
	ways.

2001-09-29  Christian Fraenkel  <c.fraenkel@gmx.net>

	* http.c (gethttp): print debug output for errors occuring during
	the ssl handshake.

2001-11-16  Chris Seawood  <cls@seawood.org>

	* init.c: Ditto.

	* host.c: Ditto.

	* connect.c: Ditto.

	* sysdep.h: Support compilation under BEOS.

2001-06-08  Edward J. Sabol  <sabol@alderaan.gsfc.nasa.gov>

	* url.c (url_equal): Fix a memory leak when parseurl returns an
	error on the second URL. Also, since url_equal is not used at the
	moment, do not compile it.

	* url.h: Ditto for the prototype of url_equal.

2001-11-16  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-parse.c (map_html_tags): Support XML-style empty tags.

2001-06-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* wget.h (DO_REALLOC_FROM_ALLOCA): Check for do_realloc_newsize in
	loop condition because we're no longer setting SIZEVAR here.

2001-06-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* wget.h (DO_REALLOC_FROM_ALLOCA): Set SIZEVAR after the memcpy()
	call because it needs the old value.

2001-06-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c (ATTR_NAME_CHAR): Allow almost any character to be in
	an attribute name.

2001-06-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (url_filename): Make sure that slashes that sneak in to
	u->file via query string get protected.
	(file_name_protect_query_string): New function.

2001-06-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (recursive_retrieve): Also check undesirable_urls with
	canonicalized URL.

2001-06-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Search `.netrc' with real host, not the proxy
	one.

2001-06-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* sysdep.h (MAP_FAILED): Provide MAP_FAILED for systems that don't
	define it.

2001-06-09  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftp.h: Provide correct prototype for ftp_parse_ls().

2001-06-04  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.7 is released.

2001-06-03  Karl Eichwalder  <ke@suse.de>

	* ftp-ls.c (ftp_parse_ls): Fix typo.

2001-05-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* all: Update copyright information.

2001-05-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Indicate that the continued download failed
	for *this* file.

2001-05-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Wget 1.7-pre1 is released.

2001-05-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Updated version to 1.7-pre1.

2001-05-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen_sslfunc.c: Don't include <sys/time.h> directly.

2001-05-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Use real URL data for cookies, not the proxy
	stuff.

2001-05-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (print_help): Document `--no-http-keep-alive'.

	* utils.c (numdigit): Handle negative numbers *correctly*.

	* hash.c (make_nocase_string_hash_table): Use term "nocase" rather
	than the confusing "unsigned".

	* utils.c (string_set_contains): Renamed from string_set_exists.

	* hash.c (hash_table_contains): Renamed from hash_table_exists.

	* cookies.c: Move case-insensitive hash tables to hash.c.

2001-05-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Before concluding that the file is already
	fully retrieved, make sure that the file existed and `Range' was
	actually requested.

2001-05-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c (eliminate_dups): New function.
	(build_cookies_request): Use it.
	(build_cookies_request): Set chain_store_size after reallocating
	all_chains.
	(check_domain_match): Annotated for easier future debugging.
	(store_cookie): In the debug message, print whether the cookie is
	permanent.

2001-05-08  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): Reset no_truncate before deciding whether to
	set it.
	(gethttp): Further clarify "-c conflicts with existing file" error
	message, based on input from Herold Heiko.

2001-05-07  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): If restval is set, set no_truncate to 1
	unconditionally.

2001-05-02  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftp-ls.c (ftp_parse_winnt_ls): Assure months are being correctly
	converted. Pointed out by <Stefan.Weil@de.heidelberg.com>.
	(ftp_parse_vms_ls): Ditto.

2001-04-30  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c (cmd_address): Zero SIN before using it; apparently
	needed on *BSD.

2001-04-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_loop_internal): Don't set NO_TRUNCATE if the file is
	empty.

2001-04-29  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (main): Make `--cookies' respect its argument.

2001-04-28  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (main): Removed undocumented option `--email-address'.

	* netrc.c: Use the latest read_whole_line.

	* init.c (defaults): Set opt.ftp_pass to "-wget@".

	* mswindows.c (pwd_cuserid): Ditto.

	* utils.c (pwd_cuserid): Removed.

	* host.c (ftp_getaddress): Removed.

2001-04-28  Hrvoje Niksic  <hniksic@arsdigita.com>

	(http_loop): Allocate space for filename_plus_orig_suffix with
	alloca; this is more efficient and removes the need to free it
	before each and every return.

2001-04-28  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Return RETRUNNEEDED when the retrieval is
	unneeded because the file is already there and fully downloaded,
	and -c is specified.
	(http_loop): Handle RETRUNNEEDED.

	* wget.h (uerr_t): New value RETRUNNEEDED.

	* http.c (http_loop): Set no_truncate for files that both exist
	and are non-empty.
	(gethttp): Consider the download finished when restval >= contlen,
	not only when restval==contlen.
	(gethttp): Handle redirection before giving up due to -c.
	(gethttp): Clarify error message which explains that -c will not
	truncate the file.
	(gethttp): When returning CONTNOTSUPPORTED, don't forget to free
	the stuff that needs freeing and release the socket.

2001-04-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (print_help): Wget booleans accept "off", not "no".

2001-04-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): If allow_cache is zero, always disable
	caching, not only when retrieving through proxy.

	* init.c: Ditto.

	* options.h (struct options): Rename proxy_cache to allow_cache.

2001-04-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (mktime_from_utc): Improve documentation.
	(http_atotm): Put format strings into a separate array.

2001-04-27  Hrvoje Niksic  <hniksic@arsdigita.com>

	* safe-ctype.h: Instead of throwing #error when isalpha is
	defined, redefine it to something that will throw a compile-time
	error if actually *used*.  Do the same for the rest of the
	standard C macros.

2001-04-26  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (getproxy): Ignore empty proxy vars.

2001-04-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): Would load cookies every time.

	* cookies.c (load_cookies): Handle cookies whose values contain
	embedded spaces.

2001-04-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c: Define each DIGITS_* in one line.

2001-04-25  Roger L. Beeman  <beeman@cisco.com>

	* http.c (http_atotm): Initialize t.tm_isdst to 0.
	(mktime_from_utc): Prevent mktime() from having discontinuities at
	DST transition points.

2001-04-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-url.c (get_urls_html): Fix documentation.

2001-04-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (UNSAFE_CHAR): Reimplement using a static table.
	(url_init): Removed.
	(init_unsafe_char_table): Removed.

2001-04-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* snprintf.c (dopr): Replace ISDIGIT with '0' <= ch && ch <= '9'.

2001-04-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c: Document timer functions.

	* retr.c (rate): Use it.
	(rate): Print in GB/s if transfer rate exceeds 1 GB/s.

	* utils.c (wtimer_granularity): New function.

2001-04-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (show_progress): Ditto.

	* ftp.c (getftp): Ditto.

	* http.c (gethttp): Use new timer functions.

	* utils.c (wtimer_allocate): New function.
	(wtimer_new): Ditto.
	(wtimer_delete): Ditto.
	(wtimer_reset): Ditto.
	(wtimer_elapsed): Ditto.

2001-04-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (long_to_string): New, faster version.  Favors smaller
	numbers; much of the calculation is now done at compile-time.

2001-04-24  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (numdigit): Handle negative numbers.

2001-04-23  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (show_progress): Print the download rate even when the
	percentages are not available.

2001-04-21  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): Adjust expected_bytes if the length is
	authoritative.

2001-04-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c: Don't declare `construct'.

	* hash.c (grow_hash_table): Speed up rehashing; inline storing of
	mappings to new locations.
	(hash_table_new): Make resize_threshold a field in the hash table,
	so we don't have to recalculate it in each hash_table_put.
	(grow_hash_table): Update resize_threshold.
	(MAX): Remove unused macro.
	(prime_size): Made static.

2001-04-14  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): Call uri_merge, not url_concat.

	* html-url.c (collect_tags_mapper): Call uri_merge, not
	url_concat.

	* url.c (mkstruct): Use encode_string instead of xstrdup followed
	by URL_CLEANSE.
	(path_simplify_with_kludge): Deleted.
	(contains_unsafe): Deleted.
	(construct): Renamed to uri_merge_1.
	(url_concat): Renamed to uri_merge.

2001-04-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (str_url): Use encode_string instead of the unnecessary
	CLEANDUP.
	(encode_string_maybe): New function, returns input string if no
	encoding is needed.
	(encode_string): Call encode_string_maybe to do the dirty work,
	xstrdup if no work needed.

2001-04-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* wget.h (XDIGIT_TO_xchar): Define here.

	* url.c (decode_string): Use new name.
	(encode_string): Ditto.

	* http.c (XDIGIT_TO_xchar): Rename HEXD2asc to XDIGIT_TO_xchar.
	(dump_hash): Use new name.

	* wget.h: Rename ASC2HEXD and HEXD2ASC to XCHAR_TO_XDIGIT and
	XDIGIT_TO_XCHAR respectively.

2001-04-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c: Include cookies.h.

	* cookies.h: Declare cookies_cleanup.

	* cookies.c (check_domain_match): Remove unused variable.
	(save_cookies): Remove extraneous argument from debug statement.

	* host.c (same_host): Don't call skip_url.

	* url.c (skip_url): Removed.  Removed its calls from various
	functions in url.c.

2001-04-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c (unsigned_string_hash): Use the new code in
	string_hash as reference.

	* hash.c (hash_table_map): Allow deletion and change of the
	element processed by MAPFUN.
	(string_hash): Use the function from glib.

2001-04-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* config.h.in: Include #undef stub.

	* hash.c (hash_table_remove): Rewrite to actually clear deleted
	entries instead of just marking them as deleted.

2001-04-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* hash.h: Declare hash_table_get_pair and hash_table_count.

2001-04-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c: Declare http_atotm.

2001-04-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp-ls.c (ftp_parse_unix_ls): Use octal constants for
	permissions.  A compiler that doesn't accept octal constants is
	seriously broken and shouldn't be used -- octal constants were
	present in K&R C!

2001-01-20  Karl Eichwalder  <ke@suse.de>

	* Makefile.in: Provide and use DESTDIR according to the Coding
	Standards.

2001-04-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp-ls.c (ftp_parse_vms_ls): Make seconds optional in time
	specification.

2001-04-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (parseurl): Don't strip trailing slash when u->dir is "/"
	because that strips the *leading* slash, thus forcing relative
	FTP retrieval.

2001-04-10  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftp.c (getftp): Convert initial FTP directory from VMS to UNIX
	notation for VMS servers. 
	(ftp_retrieve_dirs): Do not prepend '/' to f->name when
	odir is an empty string.

2001-04-10  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftp-ls.c (ftp_parse_winnt_ls): Made the fix for AM/PM more
	effective. Suggested by Edward J. Sabol.

2001-04-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* cookies.c (build_cookies_request): Use and sort cookies from all
	matching domains.
	(build_cookies_request): Check for duplicates before generating
	the `Cookies' header.

	* main.c (main): Don't load cookies here.
	(main): Make loadcookies and savecookies call the correct command.

	* http.c (http_loop): Load cookies on-demand.

2001-04-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Fix indentation of SSL ifdef.

2001-04-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_retrieve_dirs): Don't forcibly prepend "/" to u->dir;
	that hack is no longer necessary.
	(getftp): Prepend initial directory to *non*-absolute u->dir's.

2001-04-09  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c (cmd_file): New function.
	(enable_tilde_expansion): New variable.
	(run_wgetrc): Use it.
	(cmd_file): Use it.

2001-04-08  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c: Include cookie-related options.

	* main.c (main): Include cookie-specific options.
	(main): Load cookies before download is finished.
	(main): Save cookies when done.

	* http.c (gethttp): Process the `Set-Cookie' header.
	(gethttp): Include cookies in the response.

	* cookies.c: New file.

2001-04-08  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (datetime_str): New function.

2001-04-08  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftp-ls.c (ftp_parse_winnt_ls): The AM/PM change did assume
	12:01PM == 00:01, which was obviously wrong. Taken care of this
	anomaly.

	* ChangeLog: Removed an excess conflict marker. Reformatted the
	entry by Philipp Thomas from 2001-03-09.

	* ftp-ls.c (ftp_parse_winnt_ls): Ensure that adjusted PM hours lay
	between 0 and 23. Elminate unused variable `sec'.

2001-04-08  Hrvoje Niksic  <hniksic@arsdigita.com>

	* hash.c (hash_table_count): New function.

2001-04-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (read_file): Cast MAP_FAILED to char *.  Enforced by
	Digital Unix cc.

2001-04-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* config.h.in: Oops, do the namespace tweaks only on systems we
	know about.

2001-04-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* hash.c: Include <string.h>.

2001-04-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* config.h.in: Define "compilation environment" options that work
	under Linux and Solaris.  To be reviewed on other OS'es.

2001-04-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Prepend literal newline with `\n\'.

2001-04-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* sysdep.h: Don't define VERY_LONG_FORMAT.

	* utils.c (very_long_to_string): New function.
	(legible_very_long): Use it; don't use VERY_LONG_FORMAT.

2001-04-04  Christian Fraenkel  <christian.fraenkel@gmx.net>

	* url.c (parse_uname): Would run past the end of the string if the
	username was present, but the URL did not contain a slash, e.g.
	http://foo:bar@myhost.

2001-04-03  KOJIMA Hajime  <kjm@rins.ryukoku.ac.jp>

	* http.c (http_atotm): Use %A instead of %a to match full
	weekday.  (On most systems there is no difference.)

2001-04-03  Paul Bludov  <paul@ozero.net>

	* mswindows.c (sleep): Use SleepEx() instead of Sleep().
	(ws_changetitle): Use alloca() instead of malloc() to avoid memory
	leak.
	(ws_mypath): Use GetModuleFileName instead of argv[0].
	(ws_startup): Use data.wVersion for comparison.

2001-04-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): Ditto.

	* ftp.c (ftp_loop_internal): Made the check whether to continue
	retrieval `-O'-friendly.

2001-04-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* netrc.c (parse_netrc): Don't trim the line endings explicitly;
	they will be handled as whitespace.
	(parse_netrc): Correctly handle lines that end with whitespace.

2001-04-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): New variable global_download_count used
	to identify first retrieval.

	* ftp.c (getftp): Ditto.

	* http.c (gethttp): Rewind opt.dfp only on first retrieval.

2001-04-02  Hrvoje Niksic  <hniksic@arsdigita.com>

	* init.c (cmd_address): Heap-allocate the address that gets stored
	to CLOSURE.  Old code would simply assign an address on the stack.

2001-04-01  Nicolas Lichtmaier <nick@debian.org>

	* ftp.c (ftp_get_listing): Propagate error status.
	(ftp_retrieve_glob): Use it.
	(ftp_loop): Ditto.

2001-04-01  Nicolas Lichtmaier <nick@debian.org>

	* main.c (main): Add -C to the string that is the third arg to
	getopt_long().

2001-04-01  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): Don't start the download from scratch if `-c'
	was specified, but the file is already fully downloaded.

	* http.c (gethttp): Don't truncate a pre-existing file if `-c' was
	specified and the server doesn't support continued download.
	(gethttp): Don't start the download from scratch if `-c' was
	specified, but the file is already fully downloaded.

2001-03-31  Hrvoje Niksic  <hniksic@arsdigita.com>

	(recursive_retrieve): Don't clear the hash tables at this point at
	all; it interferes with the normal operation of register_download.

2001-03-31  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (recursive_retrieve): Clear the hash tables only when
	they are defined.

2001-03-31  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Make sure the socket is closed with
	CLOSE_INVALIDATE before we have drained the body.

2001-03-31  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (retrieve_url): Call register_download() for downloaded
	files and register_html() for downloaded HTML files.

	* recur.c (register_download): New function; register here that a
	file has been downloaded, rather than in recursive_retrieve().
	(register_html): New function; enqueue the location of HTML files
	here rather than in recursive_retrieve().

2001-03-31  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (print_help): Use multiple fputs instead of a single ugly
	printf().
	(main): Consistently assign numbers >128 to options without a
	corresponding character.

2001-03-09  Philipp Thomas  <pthomas@suse.de>

	* safe-ctype.h: New file. Locale independent ctype.h replacement
	taken from libiberty.

	* safe-ctype.c: New file. Tables for above.

	* Makefile.in: Add safe-ctype$o to OBJS.  Add dependencies for
	safe-ctype$o.

	* cmpt.c: Remove include of ctype.h. Use ISSPACE instead of
	isspace.

	* ftp-basic.c: Don't include ctype.h.

	* ftp-ls.c: Likewise.

	* ftp.c: Likewise.

	* headers.c: Likewise.

	* host.c: Likewise.

	* html-parse.c: Likewise.

	* html-url.c: Likewise.

	* http.c: Likewise.

	* init.c: Likewise.

	* main.c: Likewise. Set LC_CTYPE along with LC_MESSAGES.

	* netrc.c: Likewise.

	* recur.c: Likewise.

	* retr.c: Likewise.

	* snprintf.c: Replace ctype.h with safe-ctype.h. Use ISDIGIT
	instead of isdigit.

	* sysdep.h: Remove defines of ctype macros as they aren't needed
	for safe-ctype-h.

	* url.c: Don't include ctype.h.

	* utils.c: Likewise.

	* wget.h: Include safe-ctype.h.

2001-03-27  Dan Harkless  <wget@harkless.org>

	* Makefile.in: Moved top_builddir out of "User configuration
	section" of top Makefile and analogous spot in this one.

2001-03-17  Dan Harkless  <wget@harkless.org>

	* Makefile.in: Include @SSL_INCLUDES@ substition in INCLUDES.
	Define top_builddir.  Link wget with libtool so the user doesn't
	have to supply a bunch of custom environment variables to 
	correctly link with the OpenSSL shared libraries.

2001-03-06  Hack Kampbjorn  <hack@hackdata.com>

	* http.c (gethttp): skip :port in host header if it is the
	DEFAULT_HTTPS_PORT when using SSL.

	* url.c: move the #define of DEFAULT_HTTP_PORT, DEFAULT_FTP_PORT
	and DEFAULT_HTTPS_PORT to the header file so it can be use in the
	rest of the code. 
	* url.h: Ditto

2001-03-01  Jonas Jensen  <bones@huleboer.dk>

	* retr.c (show_progress): Correctly calculate the number of bytes
	in the first line of the download that have been actually
	downloaded in this run.

2001-02-23  Dan Harkless  <wget@harkless.org>

	* main.c (print_help): --help documentation for -N said it would
 	re-download files if they had the _same_ timestamp on server.
	(print_help): -nr belongs in "FTP options" section of --help
	output, not "Recursive retrieval" section.  Alphabetized FTP
	options by long option name.

2001-02-16  Dan Harkless  <wget@harkless.org>

	* init.c (commands): Hack Kampbjørn <hack@hackdata.com> discovered
 	that "httpsproxy" had been inserted into commands[] out of
 	alphabetical order, causing "BUG: unknown command `httpuser'".

2001-02-13  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftp-ls.c (ftp_parse_ls): Added support of ST_MACOS (Unix-like
	listing without correct permissons).

	* ftp.h (stype): Added ST_MACOS to identify the NetPresenz MacOS
	FTP server. 

	* ftp.c (ftp_retrieve_list): New mirroring logic: A remote file
	shall be donwloaded only when it's newer than the local copy or
	when it has the same timeestamp but its size is different. ST_VMS
	and ST_MACOS as special cases that lie about file size. 

	* ftp-ls.c (ftp_parse_ls): Support for ST_MACOS.

	* Makefile.in: Removed dependency on ftpparse library due to unclear
	copyright issues and absence of any feedback to our queries. 

	* ftp-ls.c: Removed dependency on ftpparse library due to unclear
	copyright issues and absence of any feedback to our queries.   
	(ftp_parse_ls): Added a warning message when remote server system
	does not seem to be suported by wget. 
	(ftp_parse_vms_ls): New function for parsing VMS ftp
	server listing output.
	(clean_line): New function responsible for removing
	end-of-line characters from FTP listing texts.

	* ftp.c (getftp): Global variables pwd and host_type are now
	member of the ccon structure under names ccon.id and ccon.rs. 

	* ftp.h (struct ccon): Added formed global variables from ftp.c,
	enum stype rs (remote system identification) and char *id (initial
	working directory), as suggested by Hrvoje.

	* url.c (parse_uname): Added support for passwords containing '@'
	characters.
	(skip_uname): Ditto.

2001-02-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_loop): Reset con.

2001-01-06  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* url.c (parse_uname): Added support for passwords containing '@'
	characters.
	(skip_uname): Ditto.

2001-02-11  Hack Kampbjørn  <hack@hackdata.com>

	* url.c (parseurl): Debug-print u->ftp_type.

2001-02-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_loop_internal): Disable padding.
	(getftp): Ditto.

	* http.c (http_loop): Disable padding.

	* retr.c (show_progress): Use it to enable padding.

	* retr.c (rate): Optional parameter PAD for padding the rate.

2001-02-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (show_progress): Make sure that the last output line
	includes progress.

2001-02-10  Jonas Jensen  <bones@huleboer.dk>

	* retr.c (show_progress): Print the download rate along with the
	percentages.
	Along with Anders Thorsby <anders@thorsby.dk>.

2001-02-10  Tim Mooney  <mooney@dogbert.cc.ndsu.NoDak.edu>

	* ftp.h: Rename enums `command' to `wget_ftp_command' and
	`fstatus' to `wget_ftp_status' because old names clash with Tru64
	net/if.h.

2001-02-08  Christian Fraenkel <christian.fraenkel@gmx.net>

        * gen_sslfunc.c: verify_callback is now static

        * gen_sslfunc.c (init_ssl): load certificate if specified

        * gen_sslfunc.c (ssl_printerr): new function

        * init.c: added new --sslcertfile and --sslcertkey switches

        * main.c: ditto

        * options.h: ditto

        * http.c (gethttp): abort when init_ssl fails

2001-01-23  Herold Heiko  <Heiko.Herold@previnet.it>

	* mswindows.h: Include <malloc.h>; it's needed for alloca().

2001-01-10  Dan Harkless  <wget@harkless.org>

	* url.c (str_url): Clarified this function's comment header after
	Hrvoje answered my question on the list as to when hide != 1.
	Also Hrvoje pointed out I need to use xstrdup() on the string literal.

2001-01-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* connect.c (bindport): Declare addrlen as int.  Diagnosed by
	Drazen Kacar <dave@arsdigita.com>.
	(conaddr): Ditto.

2001-01-09  Dan Harkless  <wget@harkless.org>

	* html-url.c: A bunch of fixup of `--page-requisites'-related
 	comments to reflect Hrvoje's changes to my code when transplanting
 	it into this new file, to fix spelling mistakes, to clarify, etc.

	* url.c (write_backup_file): Clarified a comment.
	(str_url): Henrik van Ginhoven pointed out on the list that we
	shouldn't give away the number of characters in the password by
	replacing each character with a 'x'.  Use "<password>" instead.

	* ftp.c (ftp_retrieve_dirs): The bug where recursion into FTP
 	directories didn't work if logging in put you in a directory other
 	than "/" is fixed now.  Removed the comment here warning of the bug.

	* main.c (print_help): --continue's description was misleading.
  	We don't "restart", we "resume".  Also, better to say
 	"partially-downloaded file" rather than just "existing file".

2001-01-06  Dan Harkless  <wget@harkless.org>

	* ChangeLog: The '[Not in 1.6 branch.]'s were decided not to be
	the best way to go about my aim.  Removed them in favor of:

	* ChangeLog-branches/1.6_branch.ChangeLog: New file.

2001-01-04  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (replace_attr): New function, to be used by both
	TO_COMPLETE and TO_RELATIVE case in convert_links.
	(find_fragment): New function for finding URL fragments.
	(replace_attr): Better handle the case where the original string
	is not quoted.  Use find_fragment.
	(convert_links): Use replace_attr().

2000-12-31  Dan Harkless  <wget@harkless.org>

	* ChangeLog: Since this flat file doesn't have multiple branches,
	looking at the dates would make you think that things went into
	1.6 that actually just went into the 1.7-dev branch.  Added "[Not
	in 1.6 branch.]" where appropriate to clarify.
	
2000-12-30  Dan Harkless  <wget@harkless.org>

	* ftp.c, http.c:  Applied Hack Kampbjørn <hack@hackdata.com>'s
	patch to deal with h_errno not being defined in netdb.h under Cygwin.

2000-12-18  Csaba Raduly  <csaba.raduly@sophos.com>

	* sysdep.h: Include <malloc.h> and <io.h> under Watcom.

2000-12-17  Igor Khristophorov  <igor@atdot.org>

	* http.c (check_end): Fix test for '+' or '-'.

2000-12-17  Hrvoje Niksic  <hniksic@arsdigita.com>

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

	* gen_sslfunc.c: Include <errno.h>.

	* ftp-basic.c: Don't attempt to declare errno or h_errno because
	they're not used.

	* main.c: Include <errno.h> because errno is used.

	* ftp.c: Ditto.

	* http.c: Include <netdb.h> for h_errno.

2000-12-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-parse.c (advance_declaration): MSVC assert() chokes on
	'\"'.  Use '"' instead.

2000-12-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (xfree_real): Removed.
	(xfree_debug): Just call free().

	* wget.h (xfree): Make it an alias for free.

2000-12-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): Furthermore, touch output_document only if
	it is known to be an existing regular file.

2000-12-11  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_retrieve_list): Ditto.

	* http.c (http_loop): Touch output_document if that is used for
	output.

2000-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c: Include gen_sslfunc.h after including Wget's headers.
	(persistent_available_p): Needed coma before `int ssl'.

2000-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_loop_internal): Ditto.

	* http.c (http_loop): Use it.

	* retr.c (sleep_between_retrievals): New function that handles the
	logic of opt.wait and opt.waitretry.

2000-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* rbuf.h: Implement only a single version of RBUF_READCHAR, using
	rbuf_read_bufferful when the buffer is depleted.

	* rbuf.c (rbuf_read_bufferful): New function.

2000-12-06  Hrvoje Niksic  <hniksic@arsdigita.com>

	* gen_sslfunc.h: Use ansi2knr style function declarations.

	* gen_sslfunc.c: Reformat according to the GNU coding standards.
	More should be done.

	* http.c (persistent_available_p): Place the cheap SSL test nearer
	the top of the function.
	(CLOSE_FINISH, CLOSE_INVALIDATE): Define only one version of each.

2000-12-05  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (init_unsafe_char_table): Reinstate space as an unsafe
	char.

2000-12-03  Christian Fraenkel <christian.fraenkel@gmx.net>

	* Makefile.in: added gen_sslfunc object
	* config.h.in: added HAVE_SSL define
	* connect.c: changed select_fd from static int to int
	* connect.h: ditto
	* gen_sslfunc.h: New file
	* gen_sslfunc.c: ditto
	* http.c: added HTTPS fuctionality
	* retrc.c: ditto
	* url.c: ditto
	* init.c: added opt.httpsproxy
	* options.h: ditto
	* rbuf.h: added alternate rbuf struct
	* wget.h: added CONSSLERR
	* rbuf.c: ditto

	* http.c: Added HTTPS fuctionality.

	* retrc.c: Ditto.

	* url.c: Ditto.

	* init.c: Added opt.httpsproxy.

	* options.h: Ditto.

	* rbuf.h: Added alternate rbuf struct.

	* wget.h: Added CONSSLERR.

	* rbuf.c: Ditto.

2000-11-30  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftp-ls.c (ftp_parse_unix_ls): Added second parameter
	"ignore_perms" to ignore file and directory permissions for
	Windows NT FTP server listings.
	(ftp_parse_winnt_ls): New function.
	(ftp_parse_ls): Parses UNIX and Windows NT listings
	separately. Simple heuristics for distinguishing between UNIX and
	MS-DOS-like FTP listing provided by Windows NT FTP service.

2000-11-18  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftpparse.c, ftpparse.h: New files.

	* ftp-ls.c (ftp_parse_ls): Use ftp_parse_unix_ls for UNIX servers
	only. Use ftp_parse_nonunix_ls otherwise.
	(ftp_parse_nonunix_ls): Stub to the ftpparse library handling all
	exotic FTP servers.

	* ftp.h (stype): New enum, distinguishes UNIX, VMS, and "other"
	FTP servers.

	* ftp.c: New static wariables host_type, pwd, and pwd_len. 
	(getftp): Support for VMS. Support for FTP servers that do not
	place you in the root directory after login.
	(ftp_retrieve_list): VMS is silent about the real file size, issue
	a more appropriate message.
	(ftp_get_listing): Pass host_type to ftp_parse_ls.

	* ftp-basic.c (ftp_pwd, ftp_syst): New functions.

2000-11-30  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

        * ftp-ls.c (ftp_parse_unix_ls): Added second parameter
        "ignore_perms" to ignore file and directory permissions for
        Windows NT FTP server listings.
        (ftp_parse_winnt_ls): New function.
        (ftp_parse_ls): Parses UNIX and Windows NT listings
        separately. Simple heuristics for distinguishing between UNIX
        and MS-DOS-like FTP listing provided by Windows NT FTP service.

2000-11-29  John Summerfield  <summer@OS2.ami.com.au>

	* netrc.c (parse_netrc): Get rid of line ending.

2000-11-25  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (ftp_retrieve_list): Undo typo "fix" until resolution by
	Dan.

2000-11-24  Karl Eichwalder  <ke@suse.de>

	* main.c (print_help): Untabify.

2000-11-23  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (xrealloc_debug): Do the unregister/register thing only
	if the pointer has actually changed.
	(xmalloc_real): Declare `static' in DEBUG_MALLOC builds.
	(xfree_real): Ditto.
	(xrealloc_real): Ditto.
	(xstrdup_real): Ditto.

2000-11-22  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): ftp_getaddress() returns a malloc'ed copy of the
	string; no need to strdup() it.
	(getftp): Make pwd_len a local variable.
	(ftp_loop): Free PWD before returning.

	* init.c (cleanup): Free opt.ftp_pass only if it's non-NULL.

2000-11-22  Hrvoje Niksic  <hniksic@arsdigita.com>

	* all: Use xfree() instead of free.

	* utils.c (xfree): New function.

2000-11-21  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (convert_links): HTML-quote the converted string.

	* utils.c (html_quote_string): Move here from ftp-ls.c
	(html_quote_string): Make non-static; declare in utils.h.
	(html_quote_string): Convert SP to &#32;.

2000-11-21  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp.c (getftp): Reformat Jan's code according to GNU coding
	standards; remove (debugging?) printf's; use '\0' for the ASCII
	zero character.  Use alloca() instead of malloc() for
	inter-function temporary allocations.

2000-11-18  Jan Prikryl  <prikryl@cg.tuwien.ac.at>

	* ftpparse.c, ftpparse.h: New files.

	* ftp-ls.c (ftp_parse_ls): Use ftp_parse_unix_ls for UNIX servers
	only. Use ftp_parse_nonunix_ls otherwise.
	(ftp_parse_nonunix_ls): Stub to the ftpparse library handling all
	exotic FTP servers.

	* ftp.h (stype): New enum, distinguishes UNIX, VMS, and "other"
	FTP servers.

	* ftp.c: New static wariables host_type, pwd, and pwd_len. 
	(getftp): Support for VMS. Support for FTP servers that do not
	place you in the root directory after login.
	(ftp_retrieve_list): VMS is silent about the real file size, issue
	a more appropriate message.
	(ftp_get_listing): Pass host_type to ftp_parse_ls.

	* ftp-basic.c (ftp_pwd, ftp_syst): New functions.

2000-11-21  Hrvoje Niksic  <hniksic@arsdigita.com>

	* hash.c (hash_table_put): Don't overwrite deleted mappings.

2000-11-21  Hrvoje Niksic  <hniksic@arsdigita.com>

	* hash.c (find_mapping): New function.
	(hash_table_get): Use it.
	(hash_table_get_pair): Ditto.
	(hash_table_exists): Ditto.
	(hash_table_remove): Ditto.
	(hash_table_remove): Really delete the entry if the mapping
	following LOCATION is empty.

	* utils.c (string_set_add): Check whether the element has existed
	before.

	* hash.c (hash_table_get_pair): New function.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_process_type): Ignore trailing whitespace; use
	strdupdelim().

	* recur.c (recursive_retrieve): Use the new `convert' field.
	(convert_all_links): Ditto.
	(convert_all_links): Don't respect meta_disallow_follow.

	* html-url.c (handle_link): Fill out link_relative_p and
	link_complete_p.

	* url.h (struct _urlpos): Make elements more readable.

	* recur.c (recursive_retrieve): Call slist_prepend instead of
	slist_append.
	(convert_all_links): Call slist_nreverse before iterating through
	urls_html.

	* utils.c (slist_prepend): New function.
	(slist_nreverse): Ditto.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (check_end): Constify.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (http_loop): If username and password are known, try the
	`Basic' authentication scheme by default.

	* connect.h: Declare test_socket_open.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* version.c: Bump version from 1.5.3+dev to 1.7-dev.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Don't use the return value of sprintf().
	(gethttp): Inhibit keep-alive if opt.http_keep_alive is 0.

2000-11-20  Hrvoje Niksic  <hniksic@arsdigita.com>

	* recur.c (recursive_retrieve): Print the "so we don't load"
	debugging message only if we really don't load.

	* http.c (gethttp): Inhibit keep-alive if proxy is being used.
	(gethttp): Don't request keep-alive if keep-alive is inhibited.

2000-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (gethttp): Make the HTTP persistent connections more
	robust.

2000-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* retr.c (get_contents): If use_expected, make sure that the
	appropriate amount of data is being read.

	* http.c (gethttp): Check for both `Keep-Alive: ...' and
	`Connection: Keep-Alive'.

	* wget.h (DEBUGP): Call debug_logprintf only if opt.debug is
	turned on.

2000-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* http.c (connection_available_p): Use it.

	* connect.c (test_socket_open): New function.

	* http.c (gethttp): Support persistent connections.  Based on the
	ideas, and partly on code, by Sam Horrocks <sam@daemoninc.com>.
	(register_persistent): New function.
	(connection_available_p): Ditto.
	(invalidate_connection): Ditto.

2000-11-19  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (convert_links): Handle UREL2ABS case.

	* recur.c (recursive_retrieve): Instead of the list
	urls_downloaded, use hash tables dl_file_url_map and
	dl_url_file_map.
	(convert_all_links): Use them to retrieve data.

	* host.c (clean_hosts): Free the hash tables.

	* main.c (private_initialize): Call host_init().

	* host.c (store_hostaddress): Use a saner, hash table-based data
	model.
	(realhost): Ditto.
	(host_init): Initialize the hash tables.

2000-11-18  Hrvoje Niksic  <hniksic@arsdigita.com>

	* utils.c (slist_append): Eviscerate NOSORT.  Hash tables are now
	used for what the sorted slists used to be used for.
	(slist_contains): Don't rely on the list being sorted.
	(slist_append): Simplify the code.

	* recur.c (recursive_cleanup): Use free_string_set.

	* utils.c (string_set_add, string_set_exists, string_set_free):
	New functions for easier freeing of hash tables whose keys are
	strdup'ed strings.

	* recur.c (recursive_retrieve): Use the hash table functions for
	storing undesirable URLs.

	* hash.c: New file.

2000-11-17  Hrvoje Niksic  <hniksic@arsdigita.com>

	* main.c (private_initialize): Call url_init.
	(main): Call private_initialize.

	* url.c (unsafe_char_table): New table.
	(UNSAFE_CHAR): Use it.
	(init_unsafe_char_table): New function.
	(url_init): New function; call init_unsafe_char_table.

2000-11-16  Hrvoje Niksic  <hniksic@arsdigita.com>

	* mswindows.h: Define snprintf and vsnprintf to _snprintf and
	_vsnprintf respectively.

2000-11-15  Hrvoje Niksic  <hniksic@arsdigita.com>

	* config.h.in: Do the _XOPEN_SOURCE and _SVID_SOURCE things only
	on Linux.

2000-11-15  Hrvoje Niksic  <hniksic@arsdigita.com>

	* html-url.c (handle_link): Handle HTML fragment identifiers.

	* recur.c (recursive_retrieve): If norobot info is respected and
	the file is specified not to be followed by robots, respect that.

	* html-url.c (collect_tags_mapper): Handle <meta name=robots
	content=X>.  For us the important cases are where X is NONE or
	where X contains NOFOLLOW.
	(get_urls_html): Propagate that information to the caller.

2000-11-13  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (convert_links): Unlink the file we might be reading from
	before writing to it.
	(convert_links): Use alloca instead of malloc for
	filename_plus_orig_suffix.

2000-11-12  Hrvoje Niksic  <hniksic@arsdigita.com>

	* host.c (realhost): Add HOST to the list with quality==0 only if
	it wasn't already there.
	Based on analysis by Lu Guohan <feng@public.bjnet.edu.cn>.

2000-11-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* url.c (get_urls_file): Ditto.
	(convert_links): Ditto.

	* html-url.c (get_urls_html): Use read_file() instead of
	load_file().

	* utils.c (read_file): New function, instead of the old
	load_file().
	(read_file_free): Ditto.

	* url.c (findurl): Search only for the supported protocols.
	(convert_links): Use fwrite() when writing out a region of
	characters.

2000-11-10  Hrvoje Niksic  <hniksic@arsdigita.com>

	* ftp-ls.c: Move html_quote_string and ftp_index here.

	* url.c: Remove get_urls_html, since that's now in html-url.c.

	* html-url.c: New file.

	* html-parse.c: New file.

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
