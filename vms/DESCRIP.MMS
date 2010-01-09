#                                               23 September 2009.  SMS.
#
#    Wget 1.12 for VMS - MMS (or MMK) Description File.
#
# Usage:
#
#    SET DEFAULT [.directory]   ! [.VMS] to build all products.
#    MMS /DESCRIPTION = [-.VMS] [/MACRO = (<see_below>)] target
#
# Optional macros:
#
#    CCOPTS=xxx     Compile with CC options xxx.  For example:
#                   "CCOPTS=/ARCH=HOST"
#
#    CDEFS_USER=xxx  Compile with C macro definition(s) xxx.
#
#    DASHD=1        Compile with "-d" option enabled.
#
#    DBG=1          Compile with /DEBUG /NOOPTIMIZE.
#                   Link with /DEBUG /TRACEBACK.
#                   (Default is /NOTRACEBACK.)
#
#    HPSSL=1        Enable HTTPS (and NTLM) support using HP SSL.
#
#    LARGE=1        Enable large-file (>2GB) support.  Non-VAX only.
#
#    LINKOPTS=xxx   Link with LINK options xxx.  For example:
#                   "LINKOPTS=/NOINFO"   
#
#    LIST=1         Compile with /LIST /SHOW = (ALL, NOMESSAGES).
#                   Link with /MAP /CROSS_REFERENCE /FULL.
#
#    ODS2DU=1       Look for multi-dot file names (like
#                   "[.lib]getopt^.in.h") using VMSTAR-compatible,
#                   dot-under, ODS2-conforming names (like
#                   "[.lib]getopt.in_h").  See also ODS2Z, below.
#
#    ODS2UD=1       Look for multi-dot file names (like
#                   "[.lib]getopt^.in.h") using [Un]Zip-compatible,
#                   under-dot ODS2-conforming names (like
#                    "[.lib]getopt_in.h").  Also use this macro if the
#                   source kit was extracted using VMSTAR with the
#                   /UNDERDOT ("-u") option.
#
#    OSSL=1         Enable HTTPS (and NTLM) support using OpenSSL.
#
#
# The default target, ALL, builds all the product executables.
#
# Other targets:
#
#    CLEAN      deletes architecture-specific files, but leaves any
#               individual source dependency files.
#
#    CLEAN_ALL  deletes all generated files, except the main (collected)
#               source dependency files.
#
#    CLEAN_EXE  deletes only the architecture-specific executables. 
#               Handy if all you wish to do is re-link the executables.
#
#    CLEAN_OLB  deletes only the architecture-specific object libraries. 
#
#    HELP       creates the HELP library, [.vms]WGET.HLB.
#
# Example commands:
#
# To build the conventional small-file product using the DEC/Compaq/HP C
# compiler (Note: DESCRIP.MMS is the default description file name.):
#
#    MMS
#
# To get the large-file executables (on a non-VAX system):
#
#    MMS /MACRO = (DASHD=1, LARGE=1)
#
# To delete the architecture-specific generated files for this system
# type:
#
#    MMS /MACRO = (LARGE=1) CLEAN       ! Large-file.
# or
#    MMS CLEAN                          ! Small-file.
#
# To build a complete small-file product for debug with compiler
# listings and link maps:
#
#    MMS CLEAN
#    MMS /MACRO = (DBG=1, LIST=1)
#
########################################################################

# Include primary product description file.

INCL_DESCRIP_SRC = 1
.INCLUDE descrip_src.mms

# Required command procedures.

CONFIG_EXTRACT_COM = [-.$(DIR_VMS)]CONFIG_EXTRACT.COM

# Generated header files.

#    Products.

LIB_GETOPT_H = $(DIR_LIB_DEST)GETOPT.H
SRC_CONFIG_H = $(DIR_SRC_DEST)CONFIG.H

#    Sources.

LIB_GETOPT_H_SRC_DD = [-.$(DIR_LIB)]getopt^.in.h
LIB_GETOPT_H_SRC_DU = [-.$(DIR_LIB)]getopt.in_h
LIB_GETOPT_H_SRC_UD = [-.$(DIR_LIB)]getopt_in.h

.IFDEF ODS2DU                   # ODS2DU
LIB_GETOPT_H_SRC = $(LIB_GETOPT_H_SRC_DU)
.ELSE                           # ODS2DU
.IFDEF ODS2UD                       # ODS2UD
LIB_GETOPT_H_SRC = $(LIB_GETOPT_H_SRC_UD)
.ELSE                               # ODS2UD
LIB_GETOPT_H_SRC = $(LIB_GETOPT_H_SRC_DD)
.ENDIF                              # ODS2UD [else]
.ENDIF                          # ODS2DU [else]
SRC_CONFIG_H_SRC = [-.$(DIR_VMS)]CONFIG.H_VMS


# TARGETS.

# Default subsidiary targets.

# Build LIB object library (default target).

.IFDEF TARGET_LIB               # TARGET_LIB

SUBSIDIARY = 1

LIBLIB : $(LIB_LIB)
	@ write sys$output ""
	@ write sys$output "   LIBLIB done."
	@ write sys$output ""

$(LIB_LIB) : $(LIB_LIB)($(MODS_OBJS_LIB_LIB))
	@ write sys$output "$(MMS$TARGET) updated."

.ENDIF                          # TARGET_LIB


# Build MD5 object library (default target).

.IFDEF TARGET_MD5               # TARGET_MD5

SUBSIDIARY = 1

LIBMD5 : $(LIB_MD5)
	@ write sys$output ""
	@ write sys$output "   LIBMD5 done."
	@ write sys$output ""

$(LIB_MD5) : $(LIB_MD5)($(MODS_OBJS_LIB_MD5))
	@ write sys$output "$(MMS$TARGET) updated."

# Special rules for MD5.C on VAX where Compaq C V6.4-005
# (like, probably, other versions) loops with /optimize = disjoint.

.IFDEF __VAX__                      # __VAX__

[.$(DEST)]MD5.OBJ : MD5.C
	@ write sys$output "***************************************"
	@ write sys$output "* Note: Exceptional rule in use here: *"
	@ write sys$output "***************************************"
	$(CC) $(CFLAGS) /optimize = nodisjoint /define = ($(CDEFS)) -
	 $(MMS$SOURCE)

.ENDIF                              # __VAX__

.ENDIF                          # TARGET_MD5


# Build Wget executable or SRC object library (default target).

.IFDEF TARGET_SRC               # TARGET_SRC

SUBSIDIARY = 1

EXES : $(EXES)
	@ write sys$output ""
	@ write sys$output "   Wget done."
	@ write sys$output ""

$(LIB_SRC) : $(LIB_SRC)($(MODS_OBJS_LIB_SRC))
	@ write sys$output "$(MMS$TARGET) updated."

$(WGET_EXE) : $(LIB_MD5) $(LIB_LIB) $(LIB_SRC)
	$(LINK) $(LINKFLAGS) -
	 $(LIB_SRC) /library /include = (main), -
	 $(LIB_LIB) /library, -
	 $(LIB_MD5) /library -
	 $(SSL_LINK_OPT)
	 $(LFLAGS_ARCH)

$(DECC_VER_EXE) : $(DECC_VER_OBJ)
	$(LINK) $(LINKFLAGS) -
	 $(DECC_VER_OBJ) -
	 $(LFLAGS_ARCH)

$(DECC_VER_OBJ) : [-.$(DIR_SRC)]DECC_VER.C

.ENDIF                          # TARGET_SRC


# Default global target.

ALL : $(EXES)
	@ show time
	@ write sys$output ""
	@ write sys$output "   ALL done."
	@ write sys$output ""

# Global rules for executables and object libraries.

.IFDEF TARGET_LIB               # TARGET_LIB
.ELSE                           # TARGET_LIB

$(LIB_LIB) :
	dev_dir = f$environment( "DEFAULT")
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	set default [-.$(DIR_LIB)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 $(LIB_LIB)
	set default 'dev_dir'
	show default
	@ write sys$output ""

.ENDIF                          # TARGET_LIB [else]

.IFDEF TARGET_MD5               # TARGET_MD5
.ELSE                           # TARGET_MD5

$(LIB_MD5) :
	dev_dir = f$environment( "DEFAULT")
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	set default [-.$(DIR_MD5)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 $(LIB_MD5)
	set default 'dev_dir'
	show default
	@ write sys$output ""

.ENDIF                          # TARGET_MD5 [else]

.IFDEF TARGET_SRC               # TARGET_SRC
.ELSE                           # TARGET_SRC

$(LIB_SRC) :
	dev_dir = f$environment( "DEFAULT")
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	set default [-.$(DIR_SRC)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 $(LIB_SRC)
	set default 'dev_dir'
	show default
	@ write sys$output ""

$(WGET_EXE) :
        set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
        set default [-.$(DIR_SRC)]
        show default
        @ write sys$output ""
        $(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
         $(WGET_EXE)

$(DECC_VER_EXE) :
        set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
        set default [-.$(DIR_SRC)]
        show default
        @ write sys$output ""
        $(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
         $(DECC_VER_EXE)

.ENDIF                          # TARGET_SRC [else]



# CLEAN target.  Delete the [.$(DEST)] directory and everything in it.

.IFDEF SUBSIDIARY               # SUBSIDIARY

CLEAN :
	if (f$search( "[.$(DEST)]*.*") .nes. "") then -
	 delete [.$(DEST)]*.*;*
	if (f$search( "$(DEST).dir", 1) .nes. "") then -
	 set protection = w:d $(DEST).dir;*
	if (f$search( "$(DEST).dir", 2) .nes. "") then -
	 delete $(DEST).dir;*

# CLEAN_ALL target.  Delete:
#    The [...$(DEST)] directories and everything in them.
#    All individual C dependency files.
# Also mention:
#    Comprehensive dependency file.

CLEAN_ALL :
	@ write sys$output "   SUBS - CLEAN_ALL"
	show default
	@ write sys$output ""
	if (f$search( "[...ALPHA*]*.*") .nes. "") then -
	 delete [...ALPHA*]*.*;*
	if (f$search( "[...]ALPHA*.dir", 1) .nes. "") then -
	 set protection = w:d [...]ALPHA*.dir;*
	if (f$search( "[...]ALPHA*.dir", 2) .nes. "") then -
	 delete [...]ALPHA*.dir;*
	if (f$search( "[...IA64*]*.*") .nes. "") then -
	 delete [...IA64*]*.*;*
	if (f$search( "[...]IA64*.dir", 1) .nes. "") then -
	 set protection = w:d [...]IA64*.dir;*
	if (f$search( "[...]IA64*.dir", 2) .nes. "") then -
	 delete [...]IA64*.dir;*
	if (f$search( "[...VAX*]*.*") .nes. "") then -
	 delete [...VAX*]*.*;*
	if (f$search( "[...]VAX*.dir", 1) .nes. "") then -
	 set protection = w:d [...]VAX*.dir;*
	if (f$search( "[...]VAX*.dir", 2) .nes. "") then -
	 delete [...]VAX*.dir;*
	if (f$search( "[...]*.MMSD") .nes. "") then -
	 delete [...]*.MMSD;*
	@ write sys$output ""
	@ write sys$output "Note:  This procedure will not"
	@ write sys$output "   DELETE DESCRIP_DEPS.MMS;*"
	@ write sys$output -
 "You may choose to, but a recent version of MMS (V3.5 or newer?) is"
	@ write sys$output -
 "needed to regenerate it.  (It may also be recovered from the original"
	@ write sys$output -
 "distribution kit.)  See DESCRIP_MKDEPS.MMS for instructions on"
	@ write sys$output -
 "generating DESCRIP_DEPS.MMS."
	@ write sys$output ""

# CLEAN_EXE target.  Delete the executables in [.$(DEST)].

CLEAN_EXE :
	if (f$search( "[.$(DEST)]*.EXE") .nes. "") then -
	 delete [.$(DEST)]*.EXE;*

# CLEAN_OLB target.  Delete the object libraries in [.$(DEST)].

CLEAN_OLB :
	if (f$search( "[.$(DEST)]*.OLB") .nes. "") then -
	 delete [.$(DEST)]*.OLB;*

.ELSE                           # SUBSIDIARY

.IFDEF MMSTARGETS                   # MMSTARGETS

#
# MMS (or MMK) with the MMSTARGETS macro needs only one real CLEAN rule.
#

CLEAN, CLEAN_ALL, CLEAN_EXE, CLEAN_OLB :
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
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

.ELSE                               # MMSTARGETS

#
# MMK without the MMSTARGETS macro needs more rules.
#

CLEAN :
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	set default [-.$(DIR_LIB)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN
	set default [-.$(DIR_MD5)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN
	set default [-.$(DIR_SRC)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN

CLEAN_ALL :
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	set default [-.$(DIR_LIB)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_ALL
	set default [-.$(DIR_MD5)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_ALL
	set default [-.$(DIR_SRC)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_ALL

CLEAN_EXE :
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	set default [-.$(DIR_LIB)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_EXE
	set default [-.$(DIR_MD5)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_EXE
	set default [-.$(DIR_SRC)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_EXE

CLEAN_OLB :
	set default 'f$parse( "$(MMSDESCRIPTION_FILE)", , , "DIRECTORY")'
	set default [-.$(DIR_LIB)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_OLB
	set default [-.$(DIR_MD5)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_OLB
	set default [-.$(DIR_SRC)]
	show default
	@ write sys$output ""
	$(MMS) /description = $(MMSDESCRIPTION_FILE) $(MMSQUALIFIERS) -
	 CLEAN_OLB

.ENDIF                              # MMSTARGETS [else]

.ENDIF                          # SUBSIDIARY

DEFAULT :
	@ write sys$output "No target, specified or default."

HELP : $(WGET_HLB)
	@ write sys$output ""
	@ write sys$output "   ""$<"" is ready."
	@ write sys$output ""

$(WGET_HLB) : $(WGET_HLP)
	LIBRARY /CREATE /HELP $(MMS$TARGET) $(MMS$SOURCE)

# Default C compile rule.

.C.OBJ :
	$(CC) $(CFLAGS) /define = ($(CDEFS)) $(MMS$SOURCE)


# Generated header files.

GENERATED_HEADERS : $(LIB_GETOPT_H) $(SRC_CONFIG_H)
	@ write sys$output "$(MMS$TARGET) updated."

# Simply copy "lib/getopt.in.h".

$(LIB_GETOPT_H) : $(LIB_GETOPT_H_SRC)
	copy $(LIB_GETOPT_H_SRC) $(MMS$TARGET)

# Copy "vms/config.h_vms", and append:
#    Wget version, and other information extracted from "configure.ac",
#    Current OS ("VMS"), host architecture, and OS version.

$(SRC_CONFIG_H) : $(SRC_CONFIG_H_SRC) $(CONFIG_EXTRACT_COM)
	@ @$(CONFIG_EXTRACT_COM) [-]CONFIGURE.AC wget_name wget_vers wget_email
	@ copy $(SRC_CONFIG_H_SRC) $(MMS$TARGET)
	@ open /append config_h $(MMS$TARGET)
	@ write config_h ""
	@ write config_h "/* Data extracted from ""configure.ac"": */"
	@ write config_h ""
	@ write config_h "#define PACKAGE "+ -
	 """''f$trnlnm( "wget_name")'"""
	@ write config_h "#define PACKAGE_BUGREPORT "+ -
	 """''f$trnlnm( "wget_email")'"""
	@ write config_h "#define PACKAGE_NAME "+ -
	 """''f$trnlnm( "wget_name")'"""
	@ write config_h "#define PACKAGE_STRING "+ -
	 """''f$trnlnm( "wget_name")' ''f$trnlnm( "wget_vers")'"""
	@ write config_h "#define PACKAGE_TARNAME "+ -
	 """''f$trnlnm( "wget_name")'"""
	@ write config_h "#define PACKAGE_VERSION "+ -
	 """''f$trnlnm( "wget_vers")'"""
	@ write config_h "#define VERSION "+ -
	 """''f$trnlnm( "wget_vers")'"""
	@ write config_h ""
	@ write config_h "/* Build-time info: */"
	@ write config_h ""
	@ if (f$getsyi( "hw_model") .lt. 1024) then arch_name = "VAX"
	@ if (f$getsyi( "hw_model") .ge. 1024) then -
	 arch_name = f$getsyi( "arch_name")
	@ write config_h "#define OS_TYPE "+ -
	 """VMS ''arch_name' ''f$edit( f$getsyi( ""version""), ""trim"")'"""
	@ write config_h ""
	@ close config_h

# Include generated source dependencies.

.IFDEF SUBSIDIARY               # SUBSIDIARY

INCL_DESCRIP_DEPS = 1

.INCLUDE descrip_deps.mms

.ENDIF                          # SUBSIDIARY

