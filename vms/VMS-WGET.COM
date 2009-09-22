$!                                              16 November 2006.  SMS.
$!
$!    Attempt to build Wget 1.10 automatically, using MMK or MMS.
$!
$!    Usage:
$!
$!       @ wget_kit_device:[wget_kit_dir.VMS]VMS-WGET.COM -
$!          [DASHD] [DBG] [HPSSL|NOSSL] [LARGE] [LIST] [MMS] -
$!          [CLEAN] [CLEAN_ALL] [CLEAN_EXE] [HELP] [MULTINET]
$!
$!    To enable the "-d" (diagnostics) Wget command-line option, add
$! "DASHD" to the command line.
$!
$!    To enable large-file (>2GB) support (non-VAX systems), add "LARGE"
$! to the command line.
$!
$!    To build a debug executable, add "DBG" to the command line.
$!
$!    To get compiler listing files, add "LIST" to the command line.
$!
$!    This procedure prefers MMK to MMS.
$! To use MMS when both work, add "MMS" to the command line.
$!
$!    To prevent automatic detection and use of OpenSSL, add "NOSSL"
$! to the command line.  This procedure prefers a generic SSL kit to HP
$! SSL.  If the generic logical names OPENSSL and SSLLIB are defined,
$! they will be used instead of the HP SSL logical names SSL$INCLUDE
$! and SYS$SHARE.  To use HP SSL when these generic logical names are
$! defined, add "HPSSL" to the command line.
$!
$!    To build the "CLEAN" target (which deletes all object and
$! executable files for the current CPU type, add "CLEAN" to the command
$! line.  Similarly, the "CLEAN_ALL", "CLEAN_EXE" or "HELP" target may be
$! specified.  For details, see [.VMS]DESCRIP.MMS.
$!
$!    The source code contains some old Multinet-specific code which may
$! be useful for building the program with Multinet on old VMS versions
$! (probably VMS before V7.x).  With more modern VMS and Multinet, there
$! should be no need to use any of the old Multinet-specific code.  If
$! Multinet build problems occur, try adding "MULTINET" to the command
$! line.  The source code contains no special code for PathWay or
$! TCPware IP software (or for the DEC/Compaq/HP UCX or TCPIP software).
$!
$!
$!    Special usage for automatic dependency generation (MMS only):
$!
$!       @ wget_kit_device:[wget_kit_dir.VMS]VMS-WGET.COM -
$!          DEPS [DASHD] [HPSSL|NOSSL] [NOSKIP] [CLEAN|PURGE]
$!
$!    See the [.VMS]DESCRIP_MKDEPS.MMS description file for more
$! details.  Specifying the CLEAN target here deletes the dependency
$! files, not the usual objects and executables.
$!
$!    Note that by default, DESCRIP_MKDEPS.MMS will delete the
$! intermediate *.MMSD dependency files, leaving only the comprehensive
$! dependency file, DESCRIP_DEPS.MMS.  To preserve the intermediate
$! files, specify "NOSKIP".
$!
$!    Specifying the PURGE target here deletes the intermediate *.MMSD
$! dependency files, and purges the comprehensive dependency file,
$! DESCRIP_DEPS.MMS.
$!
$!----------------------------------------------------------------------
$!
$! Sense the current default directory.
$!
$ def_orig = f$environment( "DEFAULT")
$!
$! Arrange for clean-up.
$!
$ on error then goto clean_up
$ on control_y then goto clean_up
$!
$! Set default to the kit [.SRC] directory.
$!
$ proc = f$environment( "PROCEDURE")
$ proc_dev_dir = -
   f$parse( proc, , , "DEVICE")+ f$parse( proc, , , "DIRECTORY")
$ set default 'proc_dev_dir'
$ set default [-.src]
$!
$! Sense the VMS version.
$!
$ VMS_VERS = f$edit( f$getsyi( "version"), "trim")
$!
$!
$! Analyze the command-line parameters.
$!
$ CMD = ""
$ DASHD = ""
$ DBG = ""
$ DEPS = ""
$ HPSSL = ""
$ IP = ""
$ LARGE = ""
$ LIST = ""
$ NOSKIP = ""
$ NOSSL = ""
$ TARGET = ""
$!
$ I = 0
$ p_loop_top:
$!
$    I = I+ 1
$    P = P'I'
$    P = f$edit( P, "TRIM, UPCASE")
$!
$    if (P .eqs. "DASHD")
$    then
$       DASHD = "DASHD"
$    else
$       if (P .eqs. "DBG")
$       then
$          DBG = "DBG"
$       else
$          if (P .eqs. "DEPS")
$          then
$             DEPS = "DEPS"
$          else
$             if (P .eqs. "MMS")
$             then
$                CMD = "MMS"
$             else
$                if (P .eqs. "LARGE")
$                then
$                   LARGE = "LARGE"
$                else
$                   if (P .eqs. "LIST")
$                   then
$                      LIST = "LIST"
$                   else
$                      if (P .eqs. "MULTINET")
$                      then
$                         IP = "MULTINET"
$                      else
$                         if (P .eqs. "NOSKIP")
$                         then
$                            NOSKIP = "NOSKIP"
$                         else
$                            if (P .eqs. "NOSSL")
$                            then
$                               NOSSL = "NOSSL"
$                            else
$                               if (P .eqs. "HPSSL")
$                               then
$                                  HPSSL = "HPSSL"
$                               else
$                                  if (P .nes. "")
$                                  then
$                                     TARGET = P
$                                  else
$                                     goto p_loop_bottom
$                                  endif
$                               endif
$                            endif
$                         endif
$                      endif
$                   endif
$                endif
$             endif
$          endif
$       endif
$    endif
$!
$ goto p_loop_top
$ p_loop_bottom:
$!
$! Verify MMK, if not intending to use MMS.  DEPS rquires MMS.
$! Accept a (non-blank) foreign command symbol "MMK", or the presence of
$! MMK.EXE on DCL$PATH.
$!
$ if (DEPS .eqs. "")
$ then
$    if ((CMD .eqs. "") .and. (DEPS .eqs. ""))
$    then
$       CMD = "MMS"
$       M_ = f$type( MMK)
$       if (M_ .eqs. "")
$       then
$          if (f$search( "DCL$PATH:MMK.EXE") .nes. "") then CMD = "MMK"
$       else
$          if (f$edit( MMK, "TRIM") .nes. "") then CMD = "MMK"
$       endif
$    endif
$ endif
$!
$! Set MMK or MMS macros.
$!
$ MACROS = """""VMS_VERS=''VMS_VERS'"""""
$!
$ if (DASHD .nes. "")
$ then
$    MACROS = MACROS+ ", """"''DASHD'=1"""""
$ endif
$!
$ if (DBG .nes. "")
$ then
$    MACROS = MACROS+ ", """"''DBG'=1"""""
$ endif
$!
$ if (LARGE .nes. "")
$ then
$    MACROS = MACROS+ ", """"''LARGE'=1"""""
$ endif
$!
$ if (LIST .nes. "")
$ then
$    MACROS = MACROS+ ", """"''LIST'=1"""""
$ endif
$!
$ if (IP .nes. "")
$ then
$    MACROS = MACROS+ ", """"''IP'=1"""""
$ endif
$!
$ if (NOSKIP .nes. "")
$ then
$    MACROS = MACROS+ ", """"''NOSKIP'=1"""""
$ endif
$!
$ NEED_HP_OPENSSL = 0
$ if (NOSSL .eqs. "")
$ then
$    if (HPSSL .nes. "")
$    then
$       if (f$search( "ssl$include:ssl.h") .nes. "")
$       then
$          MACROS = MACROS+ ", """"HPSSL=1"""""
$       endif
$    else
$       if (f$search( "openssl:ssl.h") .nes. "")
$       then
$          if (f$trnlnm( "OPENSSL") .eqs. "SSL$INCLUDE:")
$          then
$             MACROS = MACROS+ ", """"HPSSL=1"""""
$          else
$             MACROS = MACROS+ ", """"SSL=1"""""
$          endif
$       else
$          if (f$search( "ssl$include:ssl.h") .nes. "")
$          then
$             NEED_HP_OPENSSL = 1
$             MACROS = MACROS+ ", """"HPSSL=1"""""
$          endif
$       endif
$    endif
$ endif
$!
$ if (MACROS .nes. "")
$ then
$    MACROS = "/MACRO = (''MACROS')"
$ endif
$!
$! Compose the MMK or MMS command with the appropriate options.
$!
$ if (DEPS .eqs. "")
$ then
$    X := 'CMD' /DESCRIPTION = [-.vms]descrip.mms 'MACROS' 'TARGET'
$ else
$    CMD = "MMS"
$    if (NOSKIP .eqs. "")
$    then
$       CMD = CMD+ " /SKIP_INTERMEDIATE"
$    endif
$    X := 'CMD' /EXTENDED_SYNTAX -
      /DESCRIPTION = [-.vms]descrip_mkdeps.mms 'MACROS' 'TARGET'
$ endif
$!
$! If using HP SSL, define the logical name OPENSSL.
$!
$ if (NEED_HP_OPENSSL)
$ then
$    define openssl ssl$include
$ endif
$!
$! If using any SSL, show the openssl definition.
$!
$ if (NOSSL .eqs. "")
$ then
$    lnm = f$trnlnm( "OPENSSL")
$    if (lnm .eqs. "")
$    then
$       lnm = "(none)"
$    endif
$    write sys$output "OPENSSL = "+ lnm
$ endif
$!
$! Show the MMK or MMS command.
$!
$ write sys$output X
$!
$! Run MMK or MMS with the appropriate options.
$!
$ 'X'
$!
$ clean_up:
$!
$! If using HP SSL, deassign the logical name OPENSSL.
$!
$ if (NEED_HP_OPENSSL)
$ then
$    deassign openssl
$ endif
$!
$! Restore the original default directory.
$!
$ set default 'def_orig'
$!
