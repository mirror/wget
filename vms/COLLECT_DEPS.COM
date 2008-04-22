$!                                              12 April 2005.  SMS.
$!
$!    Collect all source file dependencies specified by P2,
$!    and add P3 prefix.
$!    Convert absolute dependencies to relative from P4.
$!    P1 = output file specification.
$!
$! MMS /EXTENDED_SYNTAX can't easily pass a macro invocation for P3, so
$! we remove any internal spaces which might have been added to prevent
$! immediate evaluation of a macro invocation.
$!
$ prefix = f$edit( p3, "COLLAPSE")
$!
$ dev_lose = f$parse( p4, , , "DEVICE", "SYNTAX_ONLY")
$ dir_lose = f$parse( p4, , , "DIRECTORY", "SYNTAX_ONLY")
$ suffix = ".VMS]"
$ suffix_loc = f$locate( suffix, dir_lose)
$ if (suffix_loc .lt f$length( dir_lose))
$ then
$    dev_dir_lose = dev_lose+ dir_lose- suffix
$ else
$    dev_dir_lose = dev_lose+ dir_lose- "]"
$ endif
$!
$!!! write sys$output " d_d_l: ""''dev_dir_lose'""."
$!
$! For portability, make the output file record format Stream_LF.
$!
$ create /fdl = sys$input 'p1'
RECORD
        Carriage_Control carriage_return
        Format stream_lf
$!
$ open /read /write /error = end_main deps_out 'p1'
$ on error then goto loop_main_end
$!
$! Include proper-inclusion-check preface.
$!
$ incl_macro = "INCL_"+ f$parse( p1, , , "NAME", "SYNTAX_ONLY")
$ write deps_out "#"
$ write deps_out "# Wget for VMS - MMS (or MMK) Source Dependency File."
$ write deps_out "#"
$ write deps_out ""
$ write deps_out -
   "# This description file is included by other description files.  It is"
$ write deps_out -
   "# not intended to be used alone.  Verify proper inclusion."
$ write deps_out ""
$ write deps_out ".IFDEF ''incl_macro'"
$ write deps_out ".ELSE"
$ write deps_out -
   "$$$$ THIS DESCRIPTION FILE IS NOT INTENDED TO BE USED THIS WAY."
$ write deps_out ".ENDIF"
$ write deps_out ""
$!
$! Actual dependencies from individual dependency files.
$!
$ loop_main_top:
$    file = f$search( p2)
$    if (file .eqs. "") then goto loop_main_end
$!
$    open /read /error = end_subs deps_in 'file'
$    loop_subs_top:
$       read /error = loop_subs_end deps_in line
$       line_reduced = f$edit( line, "COMPRESS, TRIM")
$       colon = f$locate( " : ", line_reduced)
$       if (colon .ge. f$length( line_reduced)) then goto loop_subs_top
$       d_d_l_loc = f$locate( dev_dir_lose, -
         f$extract( (colon+ 3), 1000, line_reduced))
$       if (d_d_l_loc .eq. 0)
$       then
$          front = f$extract( 0, (colon+ 3), line_reduced)
$          back = f$extract( (colon+ 3+ f$length( dev_dir_lose)), -
            1000, line_reduced)
$          line = front+ "[-"+ back
$          write deps_out "''prefix'"+ "''line'"
$       endif
$    goto loop_subs_top
$!
$    loop_subs_end:
$    close deps_in
$!
$ goto loop_main_top
$!
$ loop_main_end:
$ close deps_out
$!
$ end_main:
$!
