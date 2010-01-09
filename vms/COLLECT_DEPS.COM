$!                                              5 December 2006.  SMS.
$!
$! Common VMS accessory procedure.
$!
$!    For the product named by P1,
$!    P2 = output file specification.
$!    Collect all source file dependencies specified by P3,
$!    and add P4 prefix to the object file.
$!    Convert absolute dependencies to relative from one level above P5,
$!    and add P6 prefix (typically a rooted logical name with ":[").
$!    Convert "[.P7]" to "[.P4]" in dependencies.
$!
$! MMS /EXTENDED_SYNTAX can't easily pass a macro invocation for P4, so
$! we remove any internal spaces which might have been added to prevent
$! immediate evaluation of such a macro invocation.
$!
$ prefix = f$edit( p4, "COLLAPSE")
$ here = f$environment( "DEFAULT")
$ dev_lose = f$edit( f$parse( p5, , , "DEVICE", "SYNTAX_ONLY"), "UPCASE")
$ dir_lose = f$edit( f$parse( p5, , , "DIRECTORY", "SYNTAX_ONLY"), "UPCASE")
$ set default 'dev_lose''dir_lose'
$ set default [-]
$ dev_dir_lose = f$environment( "DEFAULT")- "]"
$!
$ p6_last = f$extract( (f$length( p6)- 1), 1, p6)
$!
$ dest = ""
$ if (p7 .nes. "")
$ then
$    dest = ".''p7']"
$ endif
$!
$ set default 'here'
$!
$! For portability, make the output file record format Stream_LF.
$!
$ create /fdl = sys$input 'p2'
RECORD
        Carriage_Control carriage_return
        Format stream_lf
$!
$ open /read /write /error = end_main deps_out 'p2'
$ on error then goto loop_main_end
$!
$! Include proper-inclusion-check preface.
$!
$ incl_macro = "INCL_"+ f$parse( p2, , , "NAME", "SYNTAX_ONLY")
$ write deps_out "#"
$ write deps_out "# ''p1' - MMS (or MMK) Source Dependency File."
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
$    file = f$search( p3)
$    if (file .eqs. "") then goto loop_main_end
$!
$    open /read /error = end_subs deps_in 'file'
$    loop_subs_top:
$       read /error = loop_subs_end deps_in line
$       line_reduced = f$edit( line, "COMPRESS, TRIM, UPCASE")
$       colon = f$locate( " : ", line_reduced)
$       if (colon .ge. f$length( line_reduced)) then goto loop_subs_top
$       d_d_l_loc = f$locate( dev_dir_lose, -
         f$extract( (colon+ 3), 1000, line_reduced))
$       if (d_d_l_loc .eq. 0)
$       then
$          front = f$extract( 0, (colon+ 3), line_reduced)
$          back = f$extract( (colon+ 3+ f$length( dev_dir_lose)+ 1), -
            1000, line_reduced)
$!
$!         If specified, replace final ".P7]" with part of P4.
$!
$!         This allows a system-specific subdirectory name on a
$!         dependency file to be replaced with an MMS macro, for
$!         example, ".ALPHA]" with ".$(DEST)]".
$!
$          if (dest .nes. "")
$          then
$             dest_dot_loc = f$locate( dest, back)
$             if (dest_dot_loc .lt. f$length( back))
$             then
$                back = f$extract( 0, dest_dot_loc, back)+ -
                  f$extract( 1, 1000, prefix)+ -
                  f$extract( (dest_dot_loc+ f$length( dest)), 1000, back)
$             endif
$          endif
$!
$!         Replace null subdirectory with "000000".
$!
$          if (f$length( back) .gt. 0)
$          then
$             mid = p6
$          else
$             mid = "000000]"
$          endif
$!
$          line = front+ mid+ back
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
