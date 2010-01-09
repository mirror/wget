#                                               15 September 2009.  SMS.
#
#    Wget 1.12 for VMS - MMS (or MMK) Object Module List File.
#

# This description file is included by other description files.  It is
# not intended to be used alone.  Verify proper inclusion.

.IFDEF INCL_DESCRIP_SRC
.ELSE
$$$$ THIS DESCRIPTION FILE IS NOT INTENDED TO BE USED THIS WAY.
.ENDIF

# Object library modules.

MODS_OBJS_LIB_LIB = \
 C-CTYPE=[.$(DEST)]C-CTYPE.OBJ \
 ERROR=[.$(DEST)]ERROR.OBJ \
 EXITFAIL=[.$(DEST)]EXITFAIL.OBJ \
 GETOPT=[.$(DEST)]GETOPT.OBJ \
 GETOPT1=[.$(DEST)]GETOPT1.OBJ \
 QUOTE=[.$(DEST)]QUOTE.OBJ \
 QUOTEARG=[.$(DEST)]QUOTEARG.OBJ \
 XALLOC-DIE=[.$(DEST)]XALLOC-DIE.OBJ \
 XMALLOC=[.$(DEST)]XMALLOC.OBJ

