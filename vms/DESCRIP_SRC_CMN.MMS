#                                               26 September 2009.  SMS.
#
#    Wget 1.12 for VMS - MMS (or MMK) Common Source Description File.
#

# This description file is included by other description files.  It is
# not intended to be used alone.  Verify proper inclusion.

.IFDEF INCL_DESCRIP_SRC
.ELSE
$$$$ THIS DESCRIPTION FILE IS NOT INTENDED TO BE USED THIS WAY.
.ENDIF # INCL_DESCRIP_SRC


# Define MMK architecture macros when using MMS.

.IFDEF __MMK__                  # __MMK__
.ELSE                           # __MMK__
ALPHA_X_ALPHA = 1
IA64_X_IA64 = 1
VAX_X_VAX = 1
.IFDEF $(MMS$ARCH_NAME)_X_ALPHA     # $(MMS$ARCH_NAME)_X_ALPHA
__ALPHA__ = 1
.ENDIF                              # $(MMS$ARCH_NAME)_X_ALPHA
.IFDEF $(MMS$ARCH_NAME)_X_IA64      # $(MMS$ARCH_NAME)_X_IA64
__IA64__ = 1
.ENDIF                              # $(MMS$ARCH_NAME)_X_IA64
.IFDEF $(MMS$ARCH_NAME)_X_VAX       # $(MMS$ARCH_NAME)_X_VAX
__VAX__ = 1
.ENDIF                              # $(MMS$ARCH_NAME)_X_VAX
.ENDIF                          # __MMK__ [else]

# Analyze architecture-related and option macros.

.IFDEF __ALPHA__                # __ALPHA__
DESTM = ALPHA
.ELSE                           # __ALPHA__
.IFDEF __IA64__                     # __IA64__
DESTM = IA64
.ELSE                               # __IA64__
.IFDEF __VAX__                          # __VAX__
DESTM = VAX
.ELSE                                   # __VAX__
DESTM = UNK
UNK_DEST = 1
.ENDIF                                  # __VAX__ [else]
.ENDIF                              # __IA64__ [else]
.ENDIF                          # __ALPHA__ [else]

.IFDEF LARGE                    # LARGE
.IFDEF __VAX__                      # __VAX__
DESTL =
LARGE_VAX = 1
.ELSE                               # __VAX__
DESTL = L
.ENDIF                              # __VAX__ [else]
.ELSE                           # LARGE
DESTL =
.ENDIF                          # LARGE [else]

DEST = $(DESTM)$(DESTL)

# DASHD options.

.IFDEF DASHD                    # DASHD
CDEFS_DASHD = , "ENABLE_DEBUG"
.ELSE                           # DASHD
CDEFS_DASHD =
.ENDIF                          # DASHD [else]

# DBG options.

.IFDEF DBG                      # DBG
CFLAGS_DBG = /debug /nooptimize
LINKFLAGS_DBG = /debug /traceback
.ELSE                           # DBG
CFLAGS_DBG =
LINKFLAGS_DBG = /notraceback
.ENDIF                          # DBG [else]

# Large-file options.

.IFDEF LARGE                    # LARGE
CDEFS_LARGE = , "_LARGEFILE"
.ELSE                           # LARGE
CDEFS_LARGE =
.ENDIF                          # LARGE [else]

.IFDEF HPSSL                    # HPSSL
CDEFS_SSL = , "HAVE_SSL", "ENABLE_NTLM"
SSL_LINK_OPT = , [-.VMS]WGET_SSL_HP.OPT /OPTIONS
.IFDEF OSSL                         # OSSL
HPSSL_OSSL = 1
.ENDIF                              # OSSL
.ELSE                           # HPSSL
.IFDEF OSSL                         # OSSL
CDEFS_SSL = , "HAVE_LIBSSL", "ENABLE_NTLM"
SSL_LINK_OPT = , [-.VMS]WGET_SSL_O.OPT /OPTIONS
.ELSE                               # OSSL
CDEFS_SSL =
SSL_LINK_OPT =
.ENDIF                              # OSSL [else]
.ENDIF                          # HPSSL [else]

# User-specified options.

.IFDEF CDEFS_USER               # CDEFS_USER
CDEFS_USR = , $(CDEFS_USER)
.ELSE                           # CDEFS_USER
CDEFS_USR =
.ENDIF                          # CDEFS_USER [else]


# Specific DESCRIP_SRC.MMS defines:
#    CDEFS
#    CFLAGS_SPEC
#    CFLAGS_INCL

CDEFS_CMN = VMS $(CDEFS_DASHD) $(CDEFS_LARGE) $(CDEFS_SSL) $(CDEFS_USR)


# Absence of MMSDESCRIPTION_FILE.
.IFDEF MMSDESCRIPTION_FILE      # MMSDESCRIPTION_FILE
.ELSE                           # MMSDESCRIPTION_FILE
NO_MMSDESCRIPTION_FILE = 1
.ENDIF                          # MMSDESCRIPTION_FILE [else]


# Subsidiary directory names.  (Note: DEST must be defined first.)

DIR_LIB = LIB
DIR_LIB_DEST = [-.$(DIR_LIB).$(DEST)]
DIR_LIB_DEST_FILE = [-.$(DIR_LIB)]$(DEST).DIR;1

DIR_MD5 = MD5
DIR_MD5_DEST = [-.$(DIR_MD5).$(DEST)]
DIR_MD5_DEST_FILE = [-.$(DIR_MD5)]$(DEST).DIR;1

DIR_SRC = SRC
DIR_SRC_DEST = [-.$(DIR_SRC).$(DEST)]
DIR_SRC_DEST_FILE = [-.$(DIR_SRC)]$(DEST).DIR;1

DIR_VMS = VMS

# Object library names.

LIB_LIB = $(DIR_LIB_DEST)LIBLIB.OLB
LIB_MD5 = $(DIR_MD5_DEST)LIBMD5.OLB
LIB_SRC = $(DIR_SRC_DEST)LIBSRC.OLB

# DECC_VER object name.

DECC_VER_OBJ = $(DIR_SRC_DEST)DECC_VER.OBJ

# Executable names.

WGET_EXE = $(DIR_SRC_DEST)WGET.EXE
DECC_VER_EXE = $(DIR_SRC_DEST)DECC_VER.EXE

EXES = $(WGET_EXE) \
       $(DECC_VER_EXE)

# Help file names.

WGET_HLB = [-.$(DIR_VMS)]WGET.HLB
WGET_HLP = [-.$(DIR_VMS)]WGET.HLP


# Complain if warranted.  Otherwise, show destination directory.
# Make the destination directories, if necessary.
				
.IFDEF UNK_DEST                 # UNK_DEST
.FIRST
	@ write sys$output -
 "   Unknown system architecture."
.IFDEF __MMK__                      # __MMK__
	@ write sys$output -
 "   MMK on IA64?  Try adding ""/MACRO = __IA64__""."
.ELSE                               # __MMK__
	@ write sys$output -
 "   MMS too old?  Try adding ""/MACRO = MMS$ARCH_NAME=ALPHA"","
	@ write sys$output -
 "   or ""/MACRO = MMS$ARCH_NAME=IA64"", or ""/MACRO = MMS$ARCH_NAME=VAX"","
	@ write sys$output -
 "   as appropriate.  (Or try a newer version of MMS.)"
.ENDIF                              # __MMK__ [else]
	@ write sys$output ""
	I_WILL_DIE_NOW.  /$$$$INVALID$$$$
.ELSE                           # UNK_DEST
.IFDEF LARGE_VAX                    # LARGE_VAX
.FIRST
	@ write sys$output -
 "   Macro ""LARGE"" is invalid on VAX."
	@ write sys$output ""
	I_WILL_DIE_NOW.  /$$$$INVALID$$$$
.ELSE                               # LARGE_VAX
.IFDEF HPSSL_OSSL                       # HPSSL_OSSL
.FIRST
	@ write sys$output -
 "   Macro ""HPSSL"" is incompatible with macro ""OSSL""."
	@ write sys$output ""
	I_WILL_DIE_NOW.  /$$$$INVALID$$$$
.ELSE                                   # HPSSL_OSSL
.IFDEF NO_MMSDESCRIPTION_FILE               # NO_MMSDESCRIPTION_FILE
.FIRST
	@ write sys$output -
 "   Macro ""MMSDESCRIPTION_FILE"" is not defined as required."
	@ write sys$output -
 "   MMK, or MMS too old?  Try adding:"
	@ write sys$output -
 "   ""/MACRO = MMSDESCRIPTION_FILE=dev:[dir]description_file"","
	@ write sys$output -
 "   as appropriate, where ""dev:[dir]description_file"" is the full path"
	@ write sys$output -
 "   to the MMS/MMK description file being used (typically ""DESCRIP.MMS"")."
	@ write sys$output ""
	I_WILL_DIE_NOW.  /$$$$INVALID$$$$
.ELSE                                       # NO_MMSDESCRIPTION_FILE
.FIRST
	@ show time
	@ write sys$output "   Destination: [.$(DEST)]"
	@ write sys$output ""
	@ ! Define ODS2 symbols (close enough to MMS macros) according
	@ ! to the actual "getopt.in.h" name.
	@ if (f$search( "$(LIB_GETOPT_H_SRC_DU)") .nes. "") then -
	   ODS2DU = 1
	@ if (f$search( "$(LIB_GETOPT_H_SRC_UD)") .nes. "") then -
	   ODS2UD = 1
	@ if (f$type( ODS2DU) .nes. "") then -
	   write sys$output -
	    "   (Expecting ODS2 dot-under names for multi-dot file names.)"
	@ if (f$type( ODS2UD).nes. "") then -
	   write sys$output -
	    "   (Expecting ODS2 under-dot names for multi-dot file names.)"
	@ if ((f$type( ODS2DU) .nes. "") .or. -
	   (f$type( ODS2UD) .nes. "")) then -
	   write sys$output ""
.IFDEF ALL_DEST_DIRS_NEEDED                     # ALL_DEST_DIRS_NEEDED
	@ ! Create all destination directories first.
	if (f$search( "[-.$(DIR_LIB)]$(DEST).DIR;1") .eqs. "") then -
	 create /directory [-.$(DIR_LIB).$(DEST)]
	if (f$search( "[-.$(DIR_MD5)]$(DEST).DIR;1") .eqs. "") then -
	 create /directory [-.$(DIR_MD5).$(DEST)]
	if (f$search( "[-.$(DIR_SRC)]$(DEST).DIR;1") .eqs. "") then -
	 create /directory [-.$(DIR_SRC).$(DEST)]
.ELSE                                           # ALL_DEST_DIRS_NEEDED
	@ ! Create this specific destination directory first.
	if (f$search( "$(DEST).DIR;1") .eqs. "") then -
	 create /directory [.$(DEST)]
.ENDIF                                          # ALL_DEST_DIRS_NEEDED [else]
.ENDIF                                      # NO_MMSDESCRIPTION_FILE [else]
.ENDIF                                  # HPSSL_OSSL [else]
.ENDIF                              # LARGE_VAX [else]
.ENDIF                          # UNK_DEST [else]

# UTIME prefix quirk.

.IFDEF __ALPHA__
UTNP = , __UTC_UTIME
.ENDIF

.IFDEF __IA64__
UTNP = , __UTC_UTIME
.ENDIF

# Architecture-specific CC and LINK flags.

.IFDEF __VAX__                  # __VAX__
CFLAGS_ARCH = /decc
.ELSE                           # __VAX__
CFLAGS_ARCH = /float = ieee_float
.ENDIF                          # __VAX__ [else]

LFLAGS_ARCH =

# LIST options.

.IFDEF LIST                     # LIST
# Note: Before DEC C V6.0, "/show = [no]messages" will cause trouble.
CFLAGS_LIST = /list = $*.LIS /show = (all, nomessages)
LINKFLAGS_LIST = /map = $*.MAP /cross_reference /full
.ELSE                           # LIST
CFLAGS_LIST =
LINKFLAGS_LIST =
.ENDIF                          # LIST [else]

