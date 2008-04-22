#                                               29 January 2008.  SMS.
#
#    MMS or MMK description file for Wget 1.11.
#
# The default target, EXE, builds the architecture-specific Wget
# executable (and the DECC_VER.EXE diagnostic executable).
#
# Other targets:
#
#    HELP       [.VMS]WGET.HLB help library.
#
#    CLEAN      deletes architecture-specific files, but leaves any
#               individual source dependency files and the help library.
#
#    CLEAN_ALL  deletes all generated files, except the main (collected)
#               source dependency file.
#
#    CLEAN_EXE  deletes only the architecture-specific executable. 
#               Handy if all you wish to do is re-link the executable.
#

# Include the source file lists (among other data).

INCL_DESCRIP_SRC = 1
.INCLUDE [-.VMS]descrip_src.mms

# DECC_VER diagnostic program.
DECC_VER_OBJ = [.$(DEST)]DECC_VER.OBJ

# Executables.

WGET_EXE = [.$(DEST)]WGET.EXE
DECC_VER_EXE = [.$(DEST)]DECC_VER.EXE

EXE = $(WGET_EXE) $(DECC_VER_EXE)

# HELP library and source file.

HLB = [-.VMS]WGET.HLB
HLP = [-.VMS]WGET.HLP

# Link the executables (default target).

EXE : $(EXE)
	@ write sys$output ""
	@ write sys$output "   ""$<"" is ready."
	@ write sys$output ""

$(WGET_EXE) : $(OBJS) $(MAIN_OPT) $(IP_OPT)
	define /user_mode odir [.$(DEST)]
	$(LINK) $(LINKFLAGS) $(MAIN_OPT) /options $(IP_LINK_OPT) -
	 $(SSL_LINK_OPT)

$(DECC_VER_OBJ) : [-.VMS]DECC_VER.C

$(DECC_VER_EXE) : $(DECC_VER_OBJ)
	$(LINK) $(LINKFLAGS) $(MMS$SOURCE)

# Create the HELP library (HELP target).

HELP : $(HLB)
	@ write sys$output ""
	@ write sys$output "   ""$<"" is ready."
	@ write sys$output ""

$(HLB) : $(HLP)
	LIBRARY /CREATE /HELP $@ $<

# CLEAN target.  Delete the [.$(DEST)] directory and everything in it.

CLEAN :
	if (f$search( "[.$(DEST)]*.*") .nes. "") then -
	 delete [.$(DEST)]*.*;*
	if (f$search( "$(DEST).dir") .nes. "") then -
	 set protection = w:d $(DEST).dir;*
	if (f$search( "$(DEST).dir") .nes. "") then -
	 delete $(DEST).dir;*

# CLEAN_ALL target.  Delete:
#    The [.$(DEST)] directories and everything in them.
#    All help-related derived files,
#    CONFIG.H.
#    All individual C dependency files.
# Also mention:
#    Comprehensive dependency file.

CLEAN_ALL :
	if (f$search( "[.ALPHA*]*.*") .nes. "") then -
	 delete [.ALPHA*]*.*;*
	if (f$search( "ALPHA*.dir", 1) .nes. "") then -
	 set protection = w:d ALPHA*.dir;*
	if (f$search( "ALPHA*.dir", 2) .nes. "") then -
	 delete ALPHA*.dir;*
	if (f$search( "[.IA64*]*.*") .nes. "") then -
	 delete [.IA64*]*.*;*
	if (f$search( "IA64*.dir", 1) .nes. "") then -
	 set protection = w:d IA64*.dir;*
	if (f$search( "IA64*.dir", 2) .nes. "") then -
	 delete IA64*.dir;*
	if (f$search( "[.VAX*]*.*") .nes. "") then -
	 delete [.VAX*]*.*;*
	if (f$search( "VAX*.dir", 1) .nes. "") then -
	 set protection = w:d VAX*.dir;*
	if (f$search( "VAX*.dir", 2) .nes. "") then -
	 delete VAX*.dir;*
	if (f$search( "$(CONFIG_H)") .nes. "") then -
	 delete /log /noconfirm $(CONFIG_H);*
	if (f$search( "$(HLB)") .nes. "") then -
	 delete /log /noconfirm $(HLB);*
	if (f$search( "*.MMSD") .nes. "") then -
	 delete *.MMSD;*
	@ write sys$output ""
	@ write sys$output "Note:  This procedure will not"
	@ write sys$output "   DELETE [.VMS]DESCRIP_DEPS.MMS;*"
	@ write sys$output -
 "You may choose to, but a recent version of MMS (V3.5 or newer?) is"
	@ write sys$output -
 "needed to regenerate it.  (It may also be recovered from the original"
	@ write sys$output -
 "distribution kit.)  See [.VMS]DESCRIP_MKDEPS.MMS for instructions on"
	@ write sys$output -
 "generating [.VMS]DESCRIP_DEPS.MMS."
	@ write sys$output ""

# CLEAN_EXE target.  Delete the executable in [.$(DEST)].

CLEAN_EXE :
	if (f$search( "[.$(DEST)]*.exe") .nes. "") then -
	 delete [.$(DEST)]*.exe;*

# Include CONFIG.H dependency and rule.

INCL_CONFIG_SRC = 1
.INCLUDE [-.VMS]descrip_config.mms

# Include generated source dependencies.

INCL_DESCRIP_DEPS = 1
.INCLUDE [-.VMS]descrip_deps.mms

