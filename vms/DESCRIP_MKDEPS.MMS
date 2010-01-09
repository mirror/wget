#                                               23 September 2009.  SMS.
#
#    Wget 1.12 for VMS - MMS Dependency Description File.
#
#    MMS /EXTENDED_SYNTAX description file to generate a C source
#    dependencies file.  Unsightly errors result when /EXTENDED_SYNTAX
#    is not specified.  Typical usage:
#
#    $ MMS /EXTEND /DESCRIP = [-.VMS]DESCRIP_MKDEPS.MMS /SKIP
#
#    which discards individual source dependency files, or:
#
#    $ MMS /EXTEND /DESCRIP = [-.VMS]DESCRIP_MKDEPS.MMS /MACRO = NOSKIP=1
#
#    which retains them.  Retaining them can save time when doing code
#    development.
#
#
# The default target is the comprehensive source dependency file,
# $(DEPS_FILE) = "DESCRIP_DEPS.MMS".
#
# Other targets:
#
#    CLEAN      deletes the individual source dependency files,
#               *.MMSD;*, but leaves the comprehensive source dependency
#               file.
#
#    CLEAN_ALL  deletes all source dependency files, including the
#               individual *.MMSD;* files and the comprehensive file,
#               DESCRIP_DEPS.MMS.*.
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
# This description file uses this command procedure:
#
#    [-.VMS]COLLECT_DEPS.COM
#

# Include the source file lists (among other data).

INCL_DESCRIP_SRC = 1
.INCLUDE DESCRIP_SRC.MMS

# Required command procedures.

COLLECT_DEPS = [-.$(DIR_VMS)]COLLECT_DEPS.COM

COMS = $(COLLECT_DEPS)

# The ultimate individual product, a comprehensive dependency list.

DEPS_FILE = DESCRIP_DEPS.MMS

# Detect valid qualifier and/or macro options.

.IF $(FINDSTRING Skip, $(MMSQUALIFIERS)) .eq Skip
DELETE_MMSD = 1
.ELSIF NOSKIP
PURGE_MMSD = 1
.ELSE # [complex]
UNK_MMSD = 1
.ENDIF # [else, complex]

# Dependency suffixes and rules.
#
# .FIRST is assumed to be used already, so the MMS qualifier/macro check
# is included in each rule (one way or another).

.SUFFIXES_BEFORE .C .MMSD

.C.MMSD :
.IF UNK_MMSD                    # UNK_MMSD
	@ write sys$output -
 "   /SKIP_INTERMEDIATES is expected on the MMS command line."
	@ write sys$output -
 "   For normal behavior (delete .MMSD files), specify ""/SKIP""."
	@ write sys$output -
 "   To retain the .MMSD files, specify ""/MACRO = NOSKIP=1""."
	@ exit %x00000004
.ENDIF                          # UNK_MMSD
	$(CC) $(CFLAGS_ARCH) $(CFLAGS_INCL) $(CFLAGS_SPEC) -
	 /define = ($(CDEFS)) $(MMS$SOURCE) -
	 /NOLIST /NOOBJECT  /MMS_DEPENDENCIES = (FILE = $(MMS$TARGET))

# List of MMS dependency files.

# In case it's not obvious...
# To extract module name lists from object library module=object lists:
# 1.  Transform "module=[.dest]name.OBJ" into "module=[.dest] name".
# 2.  For a subdirectory, add "[.subdir]".
# 3.  Delete "*]" words.

# Complete list of C object dependency file names.


#    LIB.
				
.IFDEF MODS_OBJS_LIB_LIB        # MODS_OBJS_LIB_LIB

SUBSIDIARY = 1

MODS_LIB_LIB = $(FILTER-OUT *], \
 $(PATSUBST *]*.OBJ, *] *, $(MODS_OBJS_LIB_LIB)))

DEPS = $(FOREACH NAME, $(MODS_LIB_LIB), $(NAME).MMSD)

.ENDIF                          # MODS_OBJS_LIB_LIB


#    MD5.
				
.IFDEF MODS_OBJS_LIB_MD5        # MODS_OBJS_LIB_MD5

SUBSIDIARY = 1

MODS_LIB_MD5 = $(FILTER-OUT *], \
 $(PATSUBST *]*.OBJ, *] *, $(MODS_OBJS_LIB_MD5)))

DEPS = $(FOREACH NAME, $(MODS_LIB_MD5), $(NAME).MMSD)

.ENDIF                          # MODS_OBJS_LIB_MD5


#    SRC.
				
.IFDEF MODS_OBJS_LIB_SRC        # MODS_OBJS_LIB_SRC

SUBSIDIARY = 1

MODS_LIB_SRC = $(FILTER-OUT *], \
 $(PATSUBST *]*.OBJ, *] *, $(MODS_OBJS_LIB_SRC)))

DEPS = $(FOREACH NAME, $(MODS_LIB_SRC), $(NAME).MMSD)

.ENDIF                          # MODS_OBJS_LIB_SRC


# Rules and actions depend on circumstances, main or subsidiary.

.IFDEF SUBSIDIARY               # SUBSIDIARY

# Default target is the comprehensive dependency list.

$(DEPS_FILE) : $(DEPS) $(COMS)
.IF UNK_MMSD                        # UNK_MMSD
	@ write sys$output -
 "   /SKIP_INTERMEDIATES is expected on the MMS command line."
	@ write sys$output -
 "   For normal behavior (delete individual .MMSD files), specify ""/SKIP""."
	@ write sys$output -
 "   To retain the individual .MMSD files, specify ""/MACRO = NOSKIP=1""."
	@ exit %x00000004
.ENDIF                              # UNK_MMSD
#
#       Note that the space in P3, which prevents immediate macro
#       expansion, is removed by COLLECT_DEPS.COM.
#
	@$(COLLECT_DEPS) "Wget for VMS" "$(MMS$TARGET)" -
	 "[...]*.MMSD" "[.$ (DEST)]" $(MMSDESCRIPTION_FILE) -
	 "[-." $(DEST)
	@ write sys$output -
	 "Created a new dependency file: $(MMS$TARGET)"
.IF DELETE_MMSD                     # DELETE_MMSD
	@ write sys$output -
	 "Deleting intermediate .MMSD files..."
	if (f$search( "[...]*.MMSD") .nes. "") then -
	 delete /log [...]*.MMSD;*
.ELSE                               # DELETE_MMSD
	@ write sys$output -
	 "Purging intermediate .MMSD files..."
	if (f$search( "[...]*.MMSD") .nes. "") then -
	 purge /keep = 2 /log [...]*.MMSD
.ENDIF                              # DELETE_MMSD [else]

# CLEAN target.  Delete the individual C dependency files.

CLEAN :
	if (f$search( "[...]*.MMSD") .nes. "") then -
	 delete [...]*.MMSD;*

# CLEAN_ALL target.  Delete:
#    The individual C dependency files.
#    The collected source dependency file.

CLEAN_ALL :
	if (f$search( "[...]*.MMSD") .nes. "") then -
	 delete [...]*.MMSD;*
	if (f$search( "DESCRIP_DEPS.MMS") .nes. "") then -
	 delete DESCRIP_DEPS.MMS;*

.ELSE                           # SUBSIDIARY

#
# Main target is the specified target, everywhere.
#
# Note that the first actions use the normal description file to create
# some generated header files, before they are referenced.
#
# Generated headers must not be generated for any of the CLEAN* targets,
# because the CLEAN* actions may remove the required
# [.INC]DESCRIP_DEPS.MMS file.  The trick/mess here using "TARGET_xxx"
# does the job.
#
TARGET_CLEAN = X
TARGET_CLEAN_ALL = X
TARGET_CLEAN_EXE = X
TARGET_CLEAN_OLB = X

.IFDEF TARGET_$(MMSTARGETS)         # TARGET_xxx
.ELSE                               # TARGET_xxx
MAKE_GENERATED_HEADERS = X
.ENDIF                              # TARGET_xxx [else]

ALL, CLEAN, CLEAN_ALL, CLEAN_EXE, CLEAN_OLB :
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	show default
	@ write sys$output ""
	$(MMS) /description = [-.VMS]DESCRIP.MMS $(MMSQUALIFIERS) -
	 GENERATED_HEADERS
	set default [-.$(DIR_LIB)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 $(MMSTARGETS)
.IFDEF MAKE_GENERATED_HEADERS       # MAKE_GENERATED_HEADERS
	$(MMS) /description = [-.VMS]DESCRIP.MMS $(MMSQUALIFIERS) -
	 $(MMSTARGETS)
.ENDIF                              # MAKE_GENERATED_HEADERS
	set default [-.$(DIR_LIB)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 $(MMSTARGETS)
	set default [-.$(DIR_MD5)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 $(MMSTARGETS)
	set default [-.$(DIR_SRC)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 $(MMSTARGETS)

.ENDIF                          # SUBSIDIARY [else]

