#                                               28 January 2008.  SMS.
#
#    Wget 1.11 for VMS - MMS (or MMK) Config Description File.
#

# This description file is included by other description files.  It is
# not intended to be used alone.  Verify proper inclusion.

.IFDEF INCL_CONFIG_SRC
.ELSE
$$$$ THIS DESCRIPTION FILE IS NOT INTENDED TO BE USED THIS WAY.
.ENDIF


# Use the VMS "config.h".

$(CONFIG_H) : [-.vms]config.h_vms
	backup /log /new_version [-.vms]config.h_vms;0 $(CONFIG_H)

