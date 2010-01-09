#                                               23 September 2009.  SMS.
#
#    Wget 1.12 for VMS - MMS (or MMK) Source Description File.
#

# Default target identifier.

TARGET_SRC = 1

# Common source description file.

.INCLUDE [-.VMS]DESCRIP_SRC_CMN.MMS

# C compiler defines.

CDEFS_SPEC =

CDEFS = $(CDEFS_CMN) $(CDEFS_SPEC)

# Other C compiler options.

CFLAGS_INCL = /include = ([], [.$(DEST)], \
 [-.$(DIR_LIB)], [-.$(DIR_LIB).$(DEST)], [-.$(DIR_MD5)], [-.$(DIR_VMS)])

CFLAGS_SPEC = /prefix_library_entries = \
 (all_entries, except = (utime $(UTNP)))

# Define CFLAGS and LINKFLAGS.

.INCLUDE [-.VMS]DESCRIP_SRC_FLAGS.MMS

# Object library modules.

.INCLUDE DESCRIP_MODS.MMS

