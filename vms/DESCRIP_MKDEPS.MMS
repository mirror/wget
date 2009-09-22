#                                               28 January 2008.  SMS.
#
#    Wget 1.11 for VMS - MMS Dependency Description File.
#
#    MMS /EXTENDED_SYNTAX description file to generate a C source
#    dependencies file.  Unsightly errors result when /EXTENDED_SYNTAX
#    is not specified.  Typical usage (from the [...src] directory):
#
#    $ @ [-.VMS]VMS-WGET.COM DEPS [DASHD] [HPSSL|NOSSL] [NOSKIP] [CLEAN|PURGE]
#
# This description file uses this command procedure:
#
#    [-.VMS]COLLECT_DEPS.COM
#
# MMK users without MMS will be unable to generate the dependencies file
# using this description file, however there should be one supplied in
# the kit.  If this file has been deleted, users in this predicament
# will need to recover it from the original distribution kit.
#
# Note:  This dependency generation scheme assumes that the dependencies
# do not depend on host architecture type or other such variables.
# Therefore, no "#include" directive in the C source itself should be
# conditional on such variables.
#
# Note:  For no apparent reason, Wget code uses "system include"
# brackets (<>) for "config.h", so /MMS_DEPENDENCIES =
# NOSYSTEM_INCLUDE_FILES is useless here.  Thus, we rely on
# COLLECT_DEPS.COM to filter out the system includes from the
# dependencies.
#

# Required command procedures.

COMS = [-.VMS]COLLECT_DEPS.COM

# Include the source file lists (among other data).

INCL_DESCRIP_SRC = 1
.INCLUDE [-.VMS]descrip_src.mms

# The ultimate product, a comprehensive dependency list.

DEPS_FILE = [-.VMS]descrip_deps.mms

# Detect valid qualifier and/or macro options.

.IF $(FINDSTRING Skip, $(MMSQUALIFIERS)) .eq Skip
DELETE_MMSD = 1
.ELSIF NOSKIP
PURGE_MMSD = 1
.ELSE
UNK_MMSD = 1
.ENDIF

# Dependency suffixes and rules.
#
# .FIRST is assumed to be used already, so the MMS qualifier/macro check
# is included in each rule (one way or another).

.SUFFIXES_BEFORE .C .MMSD

.C.MMSD :
.IF UNK_MMSD
	@ write sys$output -
 "   /SKIP_INTERMEDIATES is expected on the MMS command line."
	@ write sys$output -
 "   For normal behavior (delete .MMSD files), specify ""/SKIP""."
	@ write sys$output -
 "   To retain the .MMSD files, specify ""/MACRO = NOSKIP=1""."
	@ exit %x00000004
.ENDIF
	$(CC) /NOOBJECT -
	 /define = ($(CDEFINES)) -
	 $(CFLAGS_INCL) -
	 $(CFLAGS_LIST) -
	 $(CFLAGS_PREFIX) -
	 $(MMS$SOURCE) -
	 /MMS_DEPENDENCIES = (FILE = $(MMS$TARGET))

# List of MMS dependency files.
# [.$(DEST)]XXX.obj -> XXX

MODS_SRC = $(FILTER-OUT *], $(PATSUBST *]*.obj, *] *, $(OBJS_SRC)))
MODS_VMS = $(FILTER-OUT *], $(PATSUBST *]*.obj, *] [-.vms]*, $(OBJS_VMS)))

MODS = $(MODS_SRC) $(MODS_VMS)

# Complete list of C object dependency file names.
# XXX -> XXX.mmsd

DEPS = $(FOREACH NAME, $(MODS), $(NAME).mmsd)

# Default target is the comprehensive dependency list.

$(DEPS_FILE) : $(CONFIG_H) $(DEPS) $(COMS)
.IF UNK_MMSD
	@ write sys$output -
 "   /SKIP_INTERMEDIATES is expected on the MMS command line."
	@ write sys$output -
 "   For normal behavior (delete individual .MMSD files), specify ""/SKIP""."
	@ write sys$output -
 "   To retain the individual .MMSD files, specify ""/MACRO = NOSKIP=1""."
	@ exit %x00000004
.ENDIF
#
#       Note that the space in P3, which prevents immediate macro
#       expansion, is removed by COLLECT_DEPS.COM.
#
        @[-.VMS]collect_deps.com -
         "$(MMS$TARGET)" "[-...]*.mmsd" "[.$ (DEST)]" -
	 $(MMSDESCRIPTION_FILE)
        @ write sys$output -
         "Created a new dependency file: $(MMS$TARGET)"
.IF DELETE_MMSD
	@ write sys$output -
         "Deleting intermediate .MMSD files..."
	if (f$search( "*.mmsd;*") .nes. "") then -
	 delete /log *.mmsd;*
	if (f$search( "[-.vms]*.mmsd;*") .nes. "") then -
	 delete /log [-.vms]*.mmsd;*
.ELSE
	@ write sys$output -
         "Purging intermediate .MMSD files..."
	purge /log *.mmsd, [-.vms]*.mmsd
.ENDIF

# CLEAN target.

CLEAN :
	if (f$search( "$(CONFIG_H)") .nes. "") then -
	 delete /log $(CONFIG_H);*
	if (f$search( "*.mmsd;*") .nes. "") then -
	 delete /log *.mmsd;*
	if (f$search( "[-.vms]*.mmsd;*") .nes. "") then -
	 delete /log [-.vms]*.mmsd;*
	if (f$search( "$(DEPS_FILE);*") .nes. "") then -
	 delete /log $(DEPS_FILE);*

# PURGE target.

PURGE :
	if (f$search( "$(CONFIG_H);-1") .nes. "") then -
	 purge /log $(CONFIG_H)
	if (f$search( "*.mmsd;*") .nes. "") then -
	 delete /log *.mmsd;*
	if (f$search( "[-.vms]*.mmsd;*") .nes. "") then -
	 delete /log [-.vms]*.mmsd;*
	if (f$search( "$(DEPS_FILE);-1") .nes. "") then -
	 purge /log $(DEPS_FILE)


# Include CONFIG.H dependency and rule.

INCL_CONFIG_SRC = 1
.INCLUDE [-.VMS]descrip_config.mms

