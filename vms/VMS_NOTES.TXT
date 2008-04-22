                                                29 January 2008.  SMS.

                       Wget 1.11 for VMS (1.11a)
                       =========================

------------------------------------------------------------------------

      Disclaimer
      ----------

   No claims of any sort are made herein.  The main Wget developers seem
indifferent to this effort.  Any suggestions for improving the code in
the VMS-specific sections are welcome, but low expectations are more
realistic than high ones.

------------------------------------------------------------------------

      Description
      -----------

   This note accompanies a quick VMS port of Wget version 1.10.2, a GNU
free network utility to retrieve files from the World Wide Web using
HTTP and FTP.  The most obvious features seem to work, but many have not
been tested.

   Built and tested (slightly) in these environments:

OpenVMS Alpha V7.3-2, HP C V7.3-009, TCPIP V5.4 - ECO 6

OpenVMS IA64 V8.3, HP C V7.3-018, TCPIP V5.6.

OpenVMS VAX V7.3, Compaq C V6.4-005, TCPIP V5.1.

------------------------------------------------------------------------

      News
      ----

   Version 1.11a (PRELIMINARY)  2008-01-30
   ---------------------------------------

- General code update to Wget 1.11.

- Changed to avoid trying "LIST -a" for a VMS FTP server.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.10.2c  2006-11-16
   ----------------------------

- Changed the code which determines the FTP server type to avoid an
  ACCVIO if no text was returned in response to a "SYST" inquiry.

- Fixed a command-line parsing problem with the "--ftp-stmlf" option.

- Fixed an unclosed comment (again?) in FTP-LS.C which could have caused
  problems with ODS5 extended file names.

- Changed VMS-WGET.COM to assume that nothing special is now required
  for use with the MultiNet IP package.  For obsolete VMS and/or
  MultiNet versions where the old MultiNet-specific changes are still
  needed, specify "MULTINET" on the VMS-WGET.COM command line.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.10.2b  2004-12-15
   ----------------------------

- Changed the "-V" version report to include some host type information.

- Changed the I/O scheme on VMS for progress dots to avoid spurious
  newline characters when output is directed to a file.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.10.2a  2004-10-13
   ----------------------------

- General code update to Wget 1.10.2.

- Many legitimate FTP CWD operations on a VMS FTP server failed.  The
  typical symptom was "No such directory `perfectly/vaild/directory'."

- FTP CWD operations on a VMS FTP server now end with a "CWD []".  For
  an FTP URL like "ftp://host/a/b/c/d.e" (and contrary to the RFC), Wget
  uses a UNIX-like directory specification in its CWD command, here,
  "CWD a/b/c".  This was observed to switch a TCPware FTP server
  (V5.6-2) into its UNIX emulation mode.  Because Wget checks the system
  type only once at the beginning of a session, the associated change in
  directory listing format confused the program.  The typical symptom
  was "No such file `-rwx---r-x'."  The added "CWD []" command resets
  the TCPware server to VMS mode, and should be harmless on other VMS
  FTP servers. 

- VMS-WGET.COM now finds MMK when it's on DCL$PATH as well as when a
  foreign command symbol "MMK" is defined.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.10.1a  2004-09-09
   ---------------------------

- General code update to Wget 1.10.1.

- VMS-specific files are now in the new [.VMS] directory.

- Changes to VMS-WGET.COM:
   - New command-line option, LARGE, enables large-file support on
     non-VAX systems.
   - VMS-WGET.COM may now be run from any default directory, not only
     [.SRC].

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.9.1e  2005-09-09
   --------------------------

- The default User-Agent string on VMS now includes the host
  architecture and VMS version.  For example, "Wget/1.9.1e (VMS Alpha
  V7.3-2)".

- Fixed a problem on VMS with an ODS5 destination file system when a
  URL-derived file name contained an invalid character ("?" or "*").  A
  typical complaint might look like:
     Cannot write to `www.foraddift.non/aspx/index.asp?sid=463e'
     (file specification syntax error).
  Now, "?" is converted to "!", and "*" to "#".

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

   Version 1.9.1d  2005-06-21
   --------------------------

- Replaced the remaining instances where ".orig" was appended to a file
  name.  Now (for VMS), "_orig" is used everywhere (except in the
  documentation).

- Disabled (for VMS) the code which appended ".nnn" (decimal "nnn") to
  an output file name to avoid overwriting an existing file.  The file
  name is now used unchanged, and VMS file versioning is expected to
  prevent overwriting.  (The multi-dot file names made this way caused
  I/O errors on ODS2 file systems.)

- Changed to do translation of CR-LF line endings to local line endings
  for ASCII FTP transfers.

- Changed (on VMS) to use fixed-512 format for binary FTP files.  Added
  the new "--ftp-stmlf" option ("ftpstmlf on" command) to let the user
  restore the old behavior, where Stream_LF was used for both ASCII and
  binary.

- Added (on VMS) a new open callback function which senses (where
  supported) the process RMS_DEFAULT values for file extend quantity
  (deq), multi-block count (mbc), and multi-buffer count (mbf), and sets
  the FAB/RAB parameters accordingly.  The default deq is now much
  larger than before (16384, was none), and the default mbc is now 127
  (was none), speeding creation of a large output file.  Explicitly set
  RMS_DEFAULT values override built-in defaults.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.9.1c  2004-12-15
   --------------------------

- Added https (SSL) support, changing DESCRIP.MMS and VMS-WGET.COM, and
  adding WGET_SSL.OPT and WGET_SSL_HP.OPT.  Limited testing was done on
  Alpha, using HP SSL V1.1-B and OpenSSL version 0.9.7e.  The build
  procedure automatically enables SSL support if it can find one of the
  SSL header files.  The details are explained in comments in
  VMS-WGET.COM, including its new command-line options, HPSSL and NOSSL.

- Changed CONNECT.C to fix some problems with MultiNet TCP/IP software.

   - A build problem related to header files (netdb.h) when compiled
     with MultiNet.  Typical symptom:

         %CC-E-REDEFSTRUCT, In this declaration, the struct "hostent" is
         redefined. at line number 178 in module NETDB of text library
         SYS$COMMON:[SYSLIB]DECC$RTLDEF.TLB;1

   - A run-time problem with an FTP URL. Typical symptom: 

         accept: bad address

- Changed FTP.C to fix various problems with time-stamping ("-N",
  "--timestamping") when using an FTP URL.  Some of the misbehavior was
  specific to a VMS FTP server, but not all.  The typical result was a
  file with the modification date (and, in some cases, the creation
  date) left at the date of the download, rather than set to match the
  date on the server.  Some misleading diagnostic messages also have
  been corrected.

- Changed FTP-LS.C to fix a typographical error (unclosed comment).

- Changed NETRC.C to fix a potential build problem on non-VMS systems.
  Adding some VMS-specific code introduced some improper statement
  ordering, which may generate complaints (or failure) with some C
  compilers.

- Changed VMS.C to fix a problem with the utime() function (supplied
  with Wget) when the user specified a non-UNIX file name with the Wget
  "-O" option.  Typical symptom: 

     utime(home_sms:[sms.wget]t.h): error 0

  As the message might suggest, the file date-time was not being set
  correctly.  With this fix, utime() should work with either a UNIX-like
  or VMS-like file specification, and it should also set errno properly
  when it fails, enabling a more informative error message.

- New MMS/MMK description files and associated command procedures enable
  automatic source dependency generation.  Changed: DESCRIP.MMS and
  VMS-WGET.COM.  New: DESCRIP_DEPS.MMS, DESCRIP_MKDEPS.MMS,
  DESCRIP_SRC.MMS, COLLECT_DEPS.COM, and MOD_DEP.COM.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.9.1b  2004-09-28
   --------------------------

- Changed CONFIG.H_VMS to fix a build problem with C RTL before VMS
  V7.3-1 with C Runtime ECO V3.0 on Alpha:
     %LINK-W-NUDFSYMS, 2 undefined symbols:
     %LINK-I-UDFSYM,         DECC$GXSNPRINTF
     %LINK-I-UDFSYM,         DECC$GXVSNPRINTF
     [...]

- Changed VMS.C:

   - Fixed a build problem with C RTL before V7.2:
        %CC-E-UNDECLARED, In this statement, "DVI$C_ACP_F11V5" is not
        declared. at line number 262 in file
        disk:[xxx.WGET-1_9_1A_VMS.SRC]VMS.C;1

   - Fixed a build problem with C RTL before VMS V7.3 with C Runtime ECO
     2 on Alpha: 
        %CC-I-IMPLICITFUNC, In this statement, the identifier
        "decc$feature_get_index" is implicitly declared as a function.
        at line number 155 in file disk:[xxx.WGET-1_9_1A_VMS.SRC]VMS.C;1

        %CC-I-IMPLICITFUNC, In this statement, the identifier
        "decc$feature_get_value" is implicitly declared as a function.
        at line number 159 in file disk:[xxx.WGET-1_9_1A_VMS.SRC]VMS.C;1

        %CC-I-IMPLICITFUNC, In this statement, the identifier
        "decc$feature_set_value" is implicitly declared as a function.
        at line number 169 in file disk:[xxx.WGET-1_9_1A_VMS.SRC]VMS.C;1

     and the related: 

        %LINK-W-NUDFSYMS, 3 undefined symbols:
        %LINK-I-UDFSYM,         DECC$FEATURE_GET_INDEX
        %LINK-I-UDFSYM,         DECC$FEATURE_GET_VALUE
        %LINK-I-UDFSYM,         DECC$FEATURE_SET_VALUE
        [...]

   - Fixed a build problem with Multinet involving use of both the
     Multinet-specific and generic netdb.h header files:

        %CC-E-REDEFSTRUCT, In this declaration, the struct "hostent" is
        redefined. at line number 178 in module NETDB of text library
        SYS$COMMON:[SYSLIB]DECC$RTLDEF.TLB;1

   - Fixed a typographical error (unclosed comment) which kept the C RTL
     feature DECC$EFS_CHARSET from being enabled as intended. This
     caused a run-time problem on non-VAX systems with some ODS5
     extended file specifications with multiple dots in file names,
     typically when "-m" ("--mirror"), "-O" ("--output-document"), or
     "-r" ("--recursive") was used: 

        hostname/test/a.B.c: file specification syntax error
     or
        test/a.B.c: non-translatable vms error code: 0x186D4
        rms-f-syn, file specification syntax error

   - Fixed a spurious diagnostic message when doing HTTP and
     complex FTP transfers: 

        utime().  sys$parse() = 00010001.

- Changed FTP.C to fix a variety of problems encountered when using a
  VMS FTP server.  These problems (not seen in Wget 1.5.3h) were caused
  mostly by inappropriate code added (in the main Wget development
  stream) to "help" deal with a VMS FTP server.  Removing this code and
  reforming the procedure used for getting to relative directories seems
  to have fixed the problems.  As before, a single-slash URL
  ("ftp://host/one/two/name.type") will be treated as specifying a
  relative directory ("one/two"), while a double-slash URL
  ("ftp://host//one/two/name.type") will be treated as specifying an
  absolute directory ("/one/two").  As usual, the VMS FTP server will
  attempt to puzzle out whether "/one/two" should really be interpreted
  as "one:[two]", but it's better equipped to do it than Wget is.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

   Version 1.9.1a  2004-04-28
   --------------------------

- Changes to VMS-WGET.COM since Wget 1.5.3h:

   - A separate LIST command-line option now controls compiler listing
     files.  The DBG option no longer implies compiler listing files. 
     The LIST option also generates a link map with cross-reference.

   - The DBG option may actually work now.

   - Added support for IA64 architecture.

- Changes to DESCRIP.MMS since Wget 1.5.3h:

   - Compiler listing files (.LIS) and link maps (.MAP) are now put into
     the system-specific directory with the corresponding object files
     (.OBJ), namely, [.SRC.ALPHA], [.SRC.IA64], or [.SRC.VAX]. 
     Previously, they were put into the source directory ([.SRC])
     itself.

   - CLEAN target now deletes any .LIS and .MAP files.

   - New HELP target creates a Wget help library.

   - The OS_TYPE macro is now defined, including the VMS version.

   - No more complaints like "%MMS-W-MBREDEFILL, Illegal attempt to
     redefine macro 'CFLAGS'" on old versions of MMS.

   - A separate LIST macro now controls compiler listing files.  The
     DBG macro no longer implies compiler listing files.

   - New support for IA64 architecture.

- Built-in initialization of some DECC$* run-time options on non-VAX
  systems.  Currently this behavior is compiled in, so any changes must
  be made in the VMS.C source file.  These changes have no effect on VAX
  (or older Alpha) systems where the OS and C run-time support is
  absent.

   - Command-line case preservation.  Wget for VMS enables the following
     DECC$* run-time option:
        DECC$ARGV_PARSE_STYLE
     With extended command parsing enabled ("SET PROCESS
     /PARSE_STYLE = EXTENDED"), command-line case is preserved.  This
     obviates quoting case-sensitive option switches, URLs, and other
     parameters.

   - Extended file names on ODS5 file systems.  Wget for VMS enables the
     following DECC$* run-time options:
        DECC$EFS_CASE_PRESERVE
        DECC$EFS_CHARSET
     Thus, if an ODS5 file system is used as the destination for
     downloaded files, multiple dots will be permitted and case will be
     preserved in file names.  If an ODS2 file system is used, the same
     character substitutions will be made as in Wget 1.5.3h, namely,
     "." -> "_" (where needed), "~" -> "-", and "@" -> "$".

------------------------------------------------------------------------

      Changes to Source Files
      -----------------------

   Files new for VMS (all in [.VMS]):

      COLLECT_DEPS.COM   Dependency collector for DESCRIP_MKDEPS.MMS.

      config.h_vms       VMS-specific CONFIG.H.

      decc_ver.c         Diagnostic program to provide build environment
                         information.

      DESCRIP.MMS        Main MMK or MMS description ("make") file.

      DESCRIP_CONFIG.MMS CONFIG.H description file.

      DESCRIP_DEPS.MMS   Source dependency description file.

      DESCRIP_MKDEPS.MMS Source dependency generator description file.

      DESCRIP_SRC.MMS    Source list description file.

      VMS-WGET.COM       DCL procedure to build the executable from the
                         source, using MMK or MMS (and DESCRIP*.MMS).

      vms.c              Various VMS-specific code: DEC C run-time
                         initialization, ODS2-ODS5 file system
                         detection, ODS2 file name adjustment, file open
                         callback function for better RMS parameters,
                         "utime()" replacement function, and for VMS
                         before V7.0, "getpwuid()" and "localtime_r()".

      vms.h              VMS-specific header file.  For VMS C RTL before
                         V7.3, replacement for <utime.h>.  For VMS C RTL
                         before V7.0, replacement for <pwd.h>. 
                         Declarations of replacement data
                         types/structures and function prototypes for
                         vms.c.

      vms_ip.h           IP software type-specific "#include"
                         directives.  Used by host.c.

      vms_name_fix.sh    UNIX shell script to restore file names after
                         storage on an ODS2 file system.

      VMS_NOTES.TXT      These notes.

      WGET.HLP           Simple help file.

      WGET.OPT           LINK options file.

      WGET_MULTINET.OPT  LINK options file supplement for Multinet.

      WGET_SSL.OPT       LINK options file supplement for OpenSSL.

      WGET_SSL_HP.OPT    LINK options file supplement for HP SSL.


   Files modified for VMS (all in [.SRC]):

      connect.c         Added code for VMS header files.

      convert.c         Changed to use "_orig" instead of ".orig" on VMS
                        as the file name suffix used for the "-K"
                        ("--backup-converted") option.

      ftp.c             Added code for VMS header files.
                        Changed to eliminate a spurious -debug message
                        ("Unrecognized permissions for <directory>").
                        Changed to eliminate spurious complaints when
                        recursive downloads hit an empty directory.
                        Changed to fix various problems dealing with a
                        VMS FTP server.
                        Changed to fix various problems with FTP and
                        time-stamping ("-N").
                        Changed to distinguish between ASCII and binary
                        FTP transfers for proper local line endings.
                        Added (for VMS) VMS-specific file open options.

      ftp.h             Added ftp_dele() function.  (See ftp-basic.c.)
                        Added an argument to ftp_list() for the FTP
                        server type.  (See ftp-basic.c.)

      ftp-basic.c       Added ftp_dele() function to accomodate a remote
                        delete-after-download option.
                        Changed ftp_list() to avoid trying "LIST -a" for
                        an VMS FTP server.

      ftp-ls.c          Changed to open the ".listing" file in text
                        mode, not binary.
                        Changed VMS FTP DIR-parsing code to tolerate
                        more variability (leading blank lines).
                        Added support for the environment variable
                        "WGET_TIMEZONE_DIFFERENTIAL" for file time
                        adjustment (as in Wget 1.5.3h for VMS).

      host.c            Added code for VMS header files.

      host.h            Added code for VMS header files.
      
      http.c            Added code for VMS header files.
                        Changed to use an OS-specific file name suffix,
                        "_orig" for VMS, rather than a hard-coded
                        ".orig".
                        Added (for VMS) VMS-specific file open options.
                        Added (for VMS) host type and OS version info to
                        the default User-Agent string.
                        Changed "ssl_connect()" to "ssl_connect_wget()"
                        to avoid conflict with "SSL_connect()".
                        Added a type cast to remove a
                        %CC-I-QUESTCOMPARE1 compiler complaint.

      init.c            Changed (on VMS) to use "SYS$LOGIN:.wgetrc" as
                        the name of the user-specific initialization
                        file (if "WGETRC" is not defined), and
                        "SYSTEM_WGETRC" (expected to be a logical name)
                        as the system-wide initialization file.
                        Changed to open ".wgetrc" in text mode, not
                        binary.
                        Added (for VMS) "--ftp-stmlf" option ("ftpstmlf
                        on" command to force Stream_LF format (instead
                        of fixed-512) for binary FTP output files.

      log.c             Changed the I/O scheme on VMS for progress dots
                        to avoid spurious newline characters when output
                        is directed to a file.

      main.c            Changed the program identification debug message
                        ("built on OS_TYPE" instead of "on OS_TYPE"),
                        and added host information to the "-V" version
                        report.
                        Changed to set ODS5 flag if the download
                        destination is on an ODS5 file system.
                        Added (for VMS) "--ftp-stmlf" option ("ftpstmlf
                        on" command to force Stream_LF format (instead
                        of fixed-512) for binary FTP output files.
                        Adjusted the help message for -K to say "_orig"
                        instead of ".orig".  (See convert.c.)

      netrc.c           Changed to use "SYS$LOGIN:.netrc" as the name of
                        the user name and password file on VMS.

      openssl.c         Changed "ssl_connect()" to "ssl_connect_wget()"
                        to avoid conflict with "SSL_connect()".

      options.h         Added (for VMS) "--ftp-stmlf" option ("ftpstmlf
                        on" command to force Stream_LF format (instead
                        of fixed-512) for binary FTP output files.

      retr.c            Changed to adjust CR-LF line endings in ASCII
                        FTP data to proper local line endings.
                        Changed to disable (for VMS) a useless fflush()
                        which was slowing file I/O.

      retr.h            Changed to accomodate changes for FTP to
                        distinguish between ASCII and binary FTP
                        transfers for proper local ASCII line endings.

      ssl.h             Changed "ssl_connect()" to "ssl_connect_wget()"
                        to avoid conflict with "SSL_connect()".

      url.c             Added code for VMS header files.
                        Added code to replace unacceptable dots (".")
                        (and other invalid characters) with underscores
                        ("_"), tildes ("~") with hyphens ("-"), and at
                        signs ("@") with dollar signs ("$"),
                        respectively, in URL-derived file specifications
                        on ODS2 file systems.

      utils.c           Added VMS-specific code to work around the lack
                        of "fork()".
                        Changed to assist ODS2 name reversion.
                        Added (for VMS) VMS-specific file open options.
                        Changed to use a macro, UNIQ_SEP, instead of a
                        hard-coded ".", as the separator character when
                        adding a decimal "nnn" suffix to a file name to
                        make it unique.  Not defining UNIQ_SEP, as on
                        VMS, now disables adding the suffix.  (See
                        WGET.H.)

      utils.h           Added a declaration of the character properties
                        look-up table for use in ftp-ls.c.

      version.h         Adapted from version.c.  Changed the version
                        string from "1.11" to "1.11a".

      wget.h            Added a definition of an OS-specific file name
                        suffix, ORIG_SFX ("_orig", for VMS), to be used
                        instead of a hard-coded ".orig".  (See
                        convert.c, http.c.)
                        Added a definition of an OS-specific separator
                        character, UNIQ_SEP, for the decimal "nnn"
                        version number appended to a file name to make
                        it unique.  (See utils.c.)
                        Fixed a defective typedef (affecting small-file
                        builds).

------------------------------------------------------------------------

      Home source URL
      ---------------

http://www.gnu.org/directory/wget.html
http://ftp.gnu.org/gnu/wget/
ftp://ftp.gnu.org/gnu/wget/

------------------------------------------------------------------------

      Instructions
      ------------

   Extract the files from the distribution kit.  The kit includes
objects and executables for Alpha, IA64, and VAX, in the corresponding
host-specific subdirectories.  These builds were done with options
(explained below) "DASHD", "LARGE" (except VAX), and "NOSSL".

   The command procedure VMS-WGET.COM attempts to determine the CPU
type, the IP package, and SSL availability.  It defines the appropriate
macros for MMK or MMS, and then builds the appropriate executable from
the source:

      SET DEFAULT [.WGET-1_10_2C_VMS.VMS]   ! For convenience.
      @ VMS-WGET CLEAN  ! Deletes all object, list, map, and executable
                        ! files for the current CPU type.
      @ VMS-WGET        ! Copies CONFIG.H_VMS to CONFIG.H, compiles the
                        ! source files, and links the executable,
                        ! WGET.EXE.
                        ! Add "DASHD" to this command line to enable the
                        ! Wget "-d" command-line option.
                        ! Add "DBG" to this command line to build a
                        ! debug executable.
                        ! Add "LARGE" to enable large-file support on
                        ! non-VAX systems.
                        ! Add "LIST" if compiler listing and link map
                        ! files are desired.
                        ! Add "MMS" to use MMS instead of MMK when both
                        ! are available.
                        ! Add "NOSSL" to inhibit use of any SSL package.
                        ! Add "HPSSL" to use the HP SSL package when
                        ! OpenSSL (the default choice) is also available.
      @ VMS-WGET HELP   ! Creates a help library.  (Optional.  See
                        ! below.)

   Set the symbol for the foreign command:

      WGET :== $ actual_device:[actual.directory]WGET.EXE

   A very basic VMS HELP file is supplied in [.DOC]WGET.HLP.  To be
used, it must be added to a HELP library, either an existing library or
one just for Wget.  As mentioned above, a new Wget help library may be
created using the command, "@ VMS-WGET HELP".

   When a new HELP library is created, a logical name "HLP$LIBRARY_n"
may be defined to allow the HELP utility to find it.  See "HELP HELP
/USERLIBRARY" for details.

   Try to read the original documentation to learn how to use Wget.  The
principal differences in this VMS adaptation are:

   "-b" ("background") has no effect.  (It uses "fork()".)

   Excess dots are replaced by underscores in URL-derived file
specifications on ODS2 file systems.  For example, on a UNIX system, the
URL "ftp://ftp.anywhere.org/x.y.z/a.b.c" could produce the local file
"ftp.anywhere.org/x.y.z/a.b.c".  With this VMS adaptation, the local
ODS2 file would be "[.FTP_ANYWHERE_ORG.X_Y_Z]A_B.C".  On an ODS5 file
system, the file would be [.ftp^.anywhere^.org.x^.y^.z]a^.b.c".

------------------------------------------------------------------------

   The accompanying source kit may suffer from storage on an ODS2 file
system, which does not preserve case or allow multiple dots in a file
name.  Building this kit should work on VMS, but it may be expected to
fail on other systems.  To use this kit on a non-VMS system, the files
may need to be renamed to restore their original mixed-case and/or
multi-dot names.  The UNIX shell script "vms_name_fix.sh" (or something
like it) should do the job.

------------------------------------------------------------------------

   Steven M. Schweda               (+1) 651-699-9818  (voice)
   382 South Warwick Street        sms@antinode.org
   Saint Paul  MN  55105-2547

