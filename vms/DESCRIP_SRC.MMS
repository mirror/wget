#                                               29 January 2008.  SMS.
#
#    Wget 1.11 for VMS - MMS (or MMK) Source Description File.
#

# This description file is included by other description files.  It is
# not intended to be used alone.  Verify proper inclusion.

.IFDEF INCL_DESCRIP_SRC
.ELSE
$$$$ THIS DESCRIPTION FILE IS NOT INTENDED TO BE USED THIS WAY.
.ENDIF


# Define MMK architecture macros when using MMS.

.IFDEF __MMK__                          # __MMK__
.ELSE                                   # __MMK__
ALPHA_X_ALPHA = 1
IA64_X_IA64 = 1
VAX_X_VAX = 1
.IFDEF $(MMS$ARCH_NAME)_X_ALPHA             # $(MMS$ARCH_NAME)_X_ALPHA
__ALPHA__ = 1
.ENDIF                                      # $(MMS$ARCH_NAME)_X_ALPHA
.IFDEF $(MMS$ARCH_NAME)_X_IA64              # $(MMS$ARCH_NAME)_X_IA64
__IA64__ = 1
.ENDIF                                      # $(MMS$ARCH_NAME)_X_IA64
.IFDEF $(MMS$ARCH_NAME)_X_VAX               # $(MMS$ARCH_NAME)_X_VAX
__VAX__ = 1
.ENDIF                                      # $(MMS$ARCH_NAME)_X_VAX
.ENDIF                                  # __MMK__

# Analyze architecture-related and option macros.

.IFDEF __ALPHA__                        # __ALPHA__
DECC = 1
.IFDEF LARGE                                # LARGE
DEST = ALPHAL
.ELSE                                       # LARGE
DEST = ALPHA
.ENDIF                                      # LARGE
.ELSE                                   # __ALPHA__
.IFDEF __IA64__                             # __IA64__
DECC = 1
.IFDEF LARGE                                    # LARGE
DEST = IA64L
.ELSE                                           # LARGE
DEST = IA64
.ENDIF                                          # LARGE
.ELSE                                       # __IA64__
.IFDEF __VAX__                                  # __VAX__
DEST = VAX
.ELSE                                           # __VAX__
DEST = UNK
UNK_DEST = 1
.ENDIF                                          # __VAX__
.ENDIF                                      # __IA64__
.ENDIF                                  # __ALPHA__

# Check for option problems.

.IFDEF __VAX__                          # __VAX__
.IFDEF LARGE                                # LARGE
LARGE_VAX = 1
.ENDIF                                      # LARGE
.ENDIF                                  # __VAX__

# Complain if warranted.  Otherwise, show destination directory.
# Make the destination directory, if necessary.

.IFDEF VMS_VERS                         # VMS_VERS
.IFDEF UNK_DEST                             # UNK_DEST
.FIRST
	@ write sys$output -
 "   Unknown system architecture."
.IFDEF __MMK__                                  # __MMK__
	@ write sys$output -
 "   MMK on IA64?  Try adding ""/MACRO = __IA64__""."
.ELSE                                           # __MMK__
	@ write sys$output -
 "   MMS too old?  Try adding ""/MACRO = MMS$ARCH_NAME=ALPHA"","
	@ write sys$output -
 "   or ""/MACRO = MMS$ARCH_NAME=IA64"", or ""/MACRO = MMS$ARCH_NAME=VAX"","
	@ write sys$output -
 "   as appropriate.  (Or try a newer version of MMS.)"
.ENDIF                                          # __MMK__
	@ write sys$output ""
	I_WILL_DIE_NOW.  /$$$$INVALID$$$$
.ELSE                                       # UNK_DEST
.IFDEF LARGE_VAX                                # LARGE_VAX
.FIRST
	@ write sys$output -
 "   Macro ""LARGE"" is invalid on VAX."
	@ write sys$output ""
	I_WILL_DIE_NOW.  /$$$$INVALID$$$$
.ELSE                                           # LARGE_VAX
.FIRST
	@ write sys$output ""
	@ write sys$output "   Destination: "
	@ write sys$output "   "+ -
	   f$extract( 0, (f$length( f$environment( "DEFAULT"))- 1), -
	   f$environment( "DEFAULT")) + ".$(DEST)]"
	@ write sys$output ""
	if (f$search( "$(DEST).DIR;1") .eqs. "") then -
	 create /directory [.$(DEST)]
.ENDIF                                          # LARGE_VAX
.ENDIF                                      # UNK_DEST
.ELSE                                   # VMS_VERS
.FIRST
	@ write sys$output -
 "   Use VMS-WGET.COM to define the required MMK or MMS macros."
	@ write sys$output -
 "   It will then run MMS (or MMK)."
	@ write sys$output ""
	I_WILL_DIE_NOW.  /$$$$INVALID$$$$
.ENDIF                                  # VMS_VERS

# UTIME prefix quirk.

.IFDEF __ALPHA__
UTNP = , __UTC_UTIME
.ENDIF

.IFDEF __IA64__
UTNP = , __UTC_UTIME
.ENDIF

# DEC C and LINK options.

# Main LINK options file.

MAIN_OPT = [-.VMS]wget.opt

### To enable the "-d" command-line debug option, add "ENABLE_DEBUG", as
### shown (or in CONFIG.H[_VMS]).

.IFDEF DASHD
BASE_CDEFINES = "HAVE_CONFIG_H", "SYSTEM_WGETRC=""SYSTEM_WGETRC""", \
 "ENABLE_DEBUG"
.ELSE
BASE_CDEFINES = "HAVE_CONFIG_H", "SYSTEM_WGETRC=""SYSTEM_WGETRC"""
.ENDIF

.IFDEF MULTINET
IP_CDEFINES = , "MULTINET"
IP_OPT = [-.VMS]wget_multinet.opt
IP_LINK_OPT = , $(IP_OPT) /OPTIONS
.ENDIF

.IFDEF DBG
CFLAGS_DBG = /debug /nooptimize
LINKFLAGS_DBG = /debug
.ENDIF

.IFDEF LIST
CFLAGS_LIST = /list = [.$(DEST)] /show = (all, nomessages)
LINKFLAGS_LIST = /map = [.$(DEST)] /cross_reference /full
.ENDIF

.IFDEF LARGE
LARGE_CDEFINES = , "_LARGEFILE"
.ENDIF

.IFDEF HPSSL                            # HPSSL
SSL_CDEFINES = , "HAVE_SSL", "ENABLE_NTLM"
SSL_LINK_OPT = , [-.VMS]WGET_SSL_HP.OPT /OPTIONS
.ELSE                                   # HPSSL
.IFDEF SSL                                  # SSL
SSL_CDEFINES = , "HAVE_SSL", "ENABLE_NTLM"
SSL_LINK_OPT = , [-.VMS]WGET_SSL.OPT /OPTIONS
.ELSE                                       # SSL
SSL_CDEFINES =
SSL_LINK_OPT = 
.ENDIF                                      # SSL
.ENDIF                                  # HPSSL

VER_CDEFINES = , "OS_TYPE=""VMS $(VMS_VERS)"""

CDEFINES = $(BASE_CDEFINES) $(IP_CDEFINES) $(LARGE_CDEFINES) \
 $(SSL_CDEFINES) $(VER_CDEFINES)

CFLAGS_INCL = /include = ([], [-.vms])

CFLAGS_PREFIX = /prefix = (all, except = \
 (getopt, optarg, opterr, optind, optopt, utime $(UTNP)))

CFLAGS = \
 $(CFLAGS_DBG) $(CFLAGS_LIST) \
 /define = ($(CDEFINES)) \
 $(CFLAGS_INCL) \
 $(CFLAGS_PREFIX) \
 /object = $(MMS$TARGET)
 
LINKFLAGS = $(LINKFLAGS_DBG) $(LINKFLAGS_LIST) \
 /executable = $(MMS$TARGET)

# Object files.

OBJS_NOSSL_SRC = \
 [.$(DEST)]cmpt.obj \
 [.$(DEST)]connect.obj \
 [.$(DEST)]convert.obj \
 [.$(DEST)]cookies.obj \
 [.$(DEST)]ftp.obj \
 [.$(DEST)]ftp-basic.obj \
 [.$(DEST)]ftp-ls.obj \
 [.$(DEST)]ftp-opie.obj \
 [.$(DEST)]gen-md5.obj \
 [.$(DEST)]getopt.obj \
 [.$(DEST)]gnu-md5.obj \
 [.$(DEST)]hash.obj \
 [.$(DEST)]host.obj \
 [.$(DEST)]html-parse.obj \
 [.$(DEST)]html-url.obj \
 [.$(DEST)]http.obj \
 [.$(DEST)]init.obj \
 [.$(DEST)]log.obj \
 [.$(DEST)]main.obj \
 [.$(DEST)]netrc.obj \
 [.$(DEST)]progress.obj \
 [.$(DEST)]ptimer.obj \
 [.$(DEST)]recur.obj \
 [.$(DEST)]res.obj \
 [.$(DEST)]retr.obj \
 [.$(DEST)]safe-ctype.obj \
 [.$(DEST)]snprintf.obj \
 [.$(DEST)]spider.obj \
 [.$(DEST)]url.obj \
 [.$(DEST)]utils.obj \
 [.$(DEST)]xmalloc.obj

OBJS_NOSSL_VMS = \
 [.$(DEST)]vms.obj

OBJS_NOSSL = $(OBJS_NOSSL_SRC) $(OBJS_NOSSL_VMS)

.IFDEF HPSSL                            # HPSSL
OBJS_SSL = \
 [.$(DEST)]http-ntlm.obj \
 [.$(DEST)]openssl.obj
.ELSE                                   # HPSSL
.IFDEF SSL                                  # SSL
OBJS_SSL = \
 [.$(DEST)]http-ntlm.obj \
 [.$(DEST)]openssl.obj
.ELSE                                       # SSL
OBJS_SSL =
.ENDIF                                      # SSL
.ENDIF                                  # HPSSL

OBJS = $(OBJS_NOSSL) $(OBJS_SSL)

OBJS_SRC = $(OBJS_NOSSL_SRC) $(OBJS_SSL)
OBJS_VMS = $(OBJS_NOSSL_VMS)

# Configuration header file.

CONFIG_H = [-.SRC]config.h

