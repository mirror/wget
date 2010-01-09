#
# Wget for VMS - MMS (or MMK) Source Dependency File.
#

# This description file is included by other description files.  It is
# not intended to be used alone.  Verify proper inclusion.

.IFDEF INCL_DESCRIP_DEPS
.ELSE
$$$$ THIS DESCRIPTION FILE IS NOT INTENDED TO BE USED THIS WAY.
.ENDIF

[.$(DEST)]MD5.OBJ : [-.MD5]MD5.C
[.$(DEST)]MD5.OBJ : [-.SRC.$(DEST)]CONFIG.H
[.$(DEST)]MD5.OBJ : [-.MD5]MD5.H
[.$(DEST)]MD5.OBJ : [-.VMS]STDINT.H
