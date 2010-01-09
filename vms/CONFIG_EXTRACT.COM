$!                                              22 September 2009.  SMS.
$!
$!    Extract the AC_INIT strings from the "configure.ac" file.
$!
$!    P1 = input file spec.
$!    P2, P3, P4 = logical names to be defined with the extracted text.
$!
$! We're expecting to extract the bracketed text from the "[text]"
$! tokens from a block of text like:
$!
$!       AC_INIT([wget],
$!               [1.12-devel],
$!               [bug-wget@gnu.org])
$!
$! That is, starting with "AC_INIT", and ending with ")".
$!
$ file_in_open = 0
$ ac_init = ""
$!
$ on error then goto tidy
$!
$ open /error = tidy /read file_in 'p1'
$ file_in_open = 1
$ state = 0                     ! Looking for "AC_INIT".
$!
$ loop_read:
$!
$    read /error = tidy file_in line
$    line_len = f$length( line)
$    if (state .eq. 0)
$    then
$        if (f$locate( "AC_INIT", line) .lt line_len)
$        then
$           ac_init = line
$           state = 1           ! Looking for ")".
$        endif
$    else
$        if (f$locate( ")", line) .lt line_len)
$        then
$           state = 2           ! Found ")".  (Done.)
$        endif
$        ac_init = ac_init+ line
$    endif
$!
$ if (state .ne. 2) then goto loop_read
$!
$ t1 = f$element( 0, "]", f$element( 1, "[", ac_init))
$ t2 = f$element( 0, "]", f$element( 2, "[", ac_init))
$ t3 = f$element( 0, "]", f$element( 3, "[", ac_init))
$!
$ if (p2 .nes. "")
$ then
$    define 'p2' "''t1'"
$ else
$    write sys$output " 1: >''t1'<"
$ endif
$!
$ if (p3 .nes. "")
$ then
$    define 'p3' "''t2'"
$ else
$    write sys$output " 2: >''t2'<"
$ endif
$!
$ if (p4 .nes. "")
$ then
$    define 'p4' "''t3'"
$ else
$    write sys$output " 3: >''t3'<"
$ endif
$!
$ tidy:
$ if (file_in_open)
$ then
$    close file_in
$ endif
