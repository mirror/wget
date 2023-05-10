/*
 *    VMS supplement for "wget".
 *
 *======================================================================
 *
 *       vms_init()
 *
 *    On non-VAX systems, uses LIB$INITIALIZE to set a collection of C
 *    RTL features without using the DECC$* logical name method.
 *
 *----------------------------------------------------------------------
 *
 *       vms_arch()
 *
 *    Returns (run-time) VMS architecture string.
 *
 *----------------------------------------------------------------------
 *
 *       vms_basename()
 *
 *    Returns the basename from a VMS file spec.
 *
 *----------------------------------------------------------------------
 *
 *       vms_getpass().
 *
 *    VMS-specific substitute for GNU getpass().
 *
 *----------------------------------------------------------------------
 *
 *       vms_ver()
 *
 *    Returns (run-time) VMS version string.
 *
 *----------------------------------------------------------------------
 *
 *       set_ods5_dest()
 *
 *    Sets a global flag ("ods5_dest") according to the file system type
 *    of the destination device.
 *
 *----------------------------------------------------------------------
 *
 *       ods_conform()
 *
 *   Simplifies a fancy URL-derived file name into an ODS2- or
 *   ODS5-compatible file name.
 *
 *----------------------------------------------------------------------
 *
 *       utime()
 *
 *    VMS C RTL before V7.3 lacks utime().  In V7.3, utime() sets only
 *    the modified (revised) date, not the created date of a file.
 *
 *    UNIX "ls -l" reports the modified time.  VMS "DIRECTORY /DATE"
 *    reports the creation time.  Reconciling these in FTP DIR reports
 *    is non-trivial.
 *
 *    UNIX utime() sets revision and access times.  VMS does not always
 *    maintain access times, so this utime() replacement sets the
 *    creation and revision times to the specified revision (or
 *    creation?) time.  Any access time is ignored.
 *
 *----------------------------------------------------------------------
 *
 *       getpwuid()
 *
 *    VMS C RTL before V7.0 lacks getpwuid().
 *
 *----------------------------------------------------------------------
 *
 */

#include "vms.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unixlib.h>

#include <atrdef.h>
#include <descrip.h>
#include <dcdef.h>
#include <dvidef.h>
#include <fibdef.h>
#include <iodef.h>
#include <rms.h>
#include <stsdef.h>
#include <syidef.h>
#include <ttdef.h>
#include <lib$routines.h>
#include <starlet.h>

/* Use <iosbdef.h> if available.  Otherwise declare IOSB here. */

#if !defined( __VAX) && (__CRTL_VER >= 70000000)
#include <iosbdef.h>
#else /* __CRTL_VER >= 70000000 */
typedef struct _iosb {
        unsigned short int iosb$w_status; /* Final I/O status   */
        unsigned short int iosb$w_bcnt; /* 16-bit byte count    */
        unsigned int iosb$l_dev_depend; /* 32-bit dev dependent */
    } IOSB;
#endif /* !defined( __VAX) && (__CRTL_VER >= 70000000) */

/* Ugly work-around for bad type in VAX <atrdef.h>. */

#ifdef __VAX
#define UWA (unsigned int)
#else /* def __VAX */
#define UWA
#endif /* def __VAX */

#include "config.h"
#include "wget.h"
#include "utils.h"


/* Define macros for use with either NAM or NAML. */

#ifdef NAML$C_MAXRSS            /* NAML is available.  Use it. */

#  define NAM_STRUCT NAML

#  define FAB_OR_NAML( fab, nam) nam
#  define FAB_OR_NAML_FNA naml$l_long_filename
#  define FAB_OR_NAML_FNS naml$l_long_filename_size

#  define CC_RMS_NAM cc$rms_naml
#  define FAB_NAM fab$l_naml
#  define NAM_ESA naml$l_long_expand
#  define NAM_ESL naml$l_long_expand_size
#  define NAM_ESS naml$l_long_expand_alloc
#  define NAM_RSA naml$l_long_result
#  define NAM_RSL naml$l_long_result_size
#  define NAM_RSS naml$l_long_result_alloc
#  define NAM_MAXRSS NAML$C_MAXRSS
#  define NAM_NOP naml$b_nop
#  define NAM_M_SYNCHK NAML$M_SYNCHK
#  define NAM_B_NAME naml$l_long_name_size
#  define NAM_L_NAME naml$l_long_name

#else /* def NAML$C_MAXRSS */   /* NAML is not available.  Use NAM. */

#  define NAM_STRUCT NAM

#  define FAB_OR_NAML( fab, nam) fab
#  define FAB_OR_NAML_FNA fab$l_fna
#  define FAB_OR_NAML_FNS fab$b_fns

#  define CC_RMS_NAM cc$rms_nam
#  define FAB_NAM fab$l_nam
#  define NAM_ESA nam$l_esa
#  define NAM_ESL nam$b_esl
#  define NAM_ESS nam$b_ess
#  define NAM_RSA nam$l_rsa
#  define NAM_RSL nam$b_rsl
#  define NAM_RSS nam$b_rss
#  define NAM_MAXRSS NAM$C_MAXRSS
#  define NAM_NOP nam$b_nop
#  define NAM_M_SYNCHK NAM$M_SYNCHK
#  define NAM_B_NAME nam$b_name
#  define NAM_L_NAME nam$l_name

#endif /* def NAML$C_MAXRSS */

/*--------------------------------------------------------------------*/

/* Global storage. */

/*    Flag for an ODS5 destination directory. */

int ods5_dest = -1;

/*    Flag to sense if vms_init() was called. */

int vms_init_done = -1;

/*--------------------------------------------------------------------*/

#if !defined( __VAX) && (__CRTL_VER >= 70301000)

/* vms_init()

      Uses LIB$INITIALIZE to set a collection of C RTL features without
      requiring the user to define the corresponding logical names.
*/

/* Structure to hold a DECC$* feature name and its desired value. */

typedef struct
   {
   char *name;
   int value;
   } decc_feat_t;

/* Array of DECC$* feature names and their desired values. */

decc_feat_t decc_feat_array[] = {
   /* Preserve command-line case with SET PROCESS/PARSE_STYLE=EXTENDED */
 { "DECC$ARGV_PARSE_STYLE", 1 },
   /* Preserve case for file names on ODS5 disks. */
 { "DECC$EFS_CASE_PRESERVE", 1 },
   /* Enable multiple dots (and most characters) in ODS5 file names,
      while preserving VMS-ness of ";version". */
 { "DECC$EFS_CHARSET", 1 },
   /* List terminator. */
 { (char *)NULL, 0 } };

/* LIB$INITIALIZE initialization function. */

static void vms_init( void)
{
int feat_index;
int feat_value;
int feat_value_max;
int feat_value_min;
int i;
int sts;

/* Set the global flag to indicate that LIB$INITIALIZE worked. */

vms_init_done = 1;

/* Loop through all items in the decc_feat_array[]. */

for (i = 0; decc_feat_array[ i].name != NULL; i++)
   {
   /* Get the feature index. */
   feat_index = decc$feature_get_index( decc_feat_array[ i].name);
   if (feat_index >= 0)
      {
      /* Valid item.  Collect its properties. */
      feat_value = decc$feature_get_value( feat_index, 1);
      feat_value_min = decc$feature_get_value( feat_index, 2);
      feat_value_max = decc$feature_get_value( feat_index, 3);

      if ((decc_feat_array[ i].value >= feat_value_min) &&
       (decc_feat_array[ i].value <= feat_value_max))
         {
         /* Valid value.  Set it if necessary. */
         if (feat_value != decc_feat_array[ i].value)
            {
            sts = decc$feature_set_value( feat_index,
             1,
             decc_feat_array[ i].value);
            }
         }
      else
         {
         /* Invalid DECC feature value. */
         printf( " INVALID DECC FEATURE VALUE, %d: %d <= %s <= %d.\n",
          feat_value,
          feat_value_min, decc_feat_array[ i].name, feat_value_max);
         }
      }
   else
      {
      /* Invalid DECC feature name. */
      printf( " UNKNOWN DECC FEATURE: %s.\n", decc_feat_array[ i].name);
      }
   }
}

/* Get "vms_init()" into a valid, loaded LIB$INITIALIZE PSECT. */

#pragma nostandard

/* Establish the LIB$INITIALIZE PSECTs, with proper alignment and
   other attributes.  Note that "nopic" is significant only on VAX.
*/
#pragma extern_model save

#pragma extern_model strict_refdef "LIB$INITIALIZE" 2, nopic, nowrt
void (*const x_vms_init)() = vms_init;

#pragma extern_model strict_refdef "LIB$INITIALIZ" 2, nopic, nowrt
const int spare[ 8] = { 0 };

#pragma extern_model restore

/* Fake reference to ensure loading the LIB$INITIALIZE PSECT. */

#pragma extern_model save
int lib$initialize(void);
#pragma extern_model strict_refdef
int dmy_lib$initialize = (int) lib$initialize;
#pragma extern_model restore

#pragma standard

#endif /* !defined( __VAX) && (__CRTL_VER >= 70301000) */

/*--------------------------------------------------------------------*/

/* vms_arch()

      Returns (run-time) VMS architecture string.
*/

char *vms_arch( void)
{
#define ARCH_SIZE 15

static int sts = 0;
static char arch[ ARCH_SIZE+ 1] = "VAX";        /* Only VAX could fail. */
unsigned short arch_len;

struct dsc$descriptor_s arch_descr =
 { ARCH_SIZE, DSC$K_DTYPE_T, DSC$K_CLASS_S, arch };

if (sts == 0)
   {
   sts = lib$getsyi( &SYI$_ARCH_NAME, 0, &arch_descr, &arch_len, 0, 0);
   if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
      {
      arch[ arch_len] = '\0';

      /* Trim trailing spaces. */
      while ((arch_len > 0) && (arch[ arch_len- 1] == ' '))
         {
         arch[ --arch_len] = '\0';
         }
      }
   }
return arch;
}

/*--------------------------------------------------------------------*/

/* vms_basename()
 *
 *    Extract the basename from a VMS file spec.
 */

char *vms_basename( char *file_spec)
{
    /* Static storage for NAM[L], and so on. */

    static struct NAM_STRUCT nam;
    static char exp_name[ NAM_MAXRSS+ 1];
    static char res_name[ NAM_MAXRSS+ 1];

    struct FAB fab;
    int status;

    /* Set up the FAB and NAM[L] blocks. */

    fab = cc$rms_fab;                   /* Initialize FAB. */
    nam = CC_RMS_NAM;                   /* Initialize NAM[L]. */

    fab.FAB_NAM = &nam;                 /* FAB -> NAM[L] */

#ifdef NAML$C_MAXRSS

    fab.fab$l_dna = (char *) -1;    /* Using NAML for default name. */
    fab.fab$l_fna = (char *) -1;    /* Using NAML for file name. */

#endif /* def NAML$C_MAXRSS */

    /* Arg name and length. */
    FAB_OR_NAML( fab, nam).FAB_OR_NAML_FNA = file_spec;
    FAB_OR_NAML( fab, nam).FAB_OR_NAML_FNS = strlen( file_spec);

    nam.NAM_ESA = exp_name;         /* Expanded name. */
    nam.NAM_ESS = NAM_MAXRSS;       /* Max length. */
    nam.NAM_RSA = res_name;         /* Resulting name. */
    nam.NAM_RSS = NAM_MAXRSS;       /* Max length. */

    nam.NAM_NOP = NAM_M_SYNCHK;     /* Syntax-only analysis. */

    /* Parse the file name. */
    status = sys$parse( &fab);      /* What could go wrong? */

    nam.NAM_L_NAME[ nam.NAM_B_NAME] = '\0';

    return nam.NAM_L_NAME;
}

/*--------------------------------------------------------------------*/

/* 2009-09-07 SMS.
 *
 *       vms_getpass().
 *
 *    VMS-specific substitute for GNU getpass().
 *
 *       Returns passpord in locally allocated string.
 */

/* Terminal characteristics buffer structure. */
typedef struct
{
    char class;
    char type;
    short page_width;
    int basic_chars;    /* (The high eight bits are page length.) */
    int extended_chars;
} term_chars_t;

/* Enable/disable terminal echo. */

int vms_set_term_echo( int able)
{
    int sts;
    int sts2;
    short term_chan;
    $DESCRIPTOR( term_dscr, "SYS$COMMAND");
    term_chars_t term_chars;
    static int initial_echo = -1;

    /* Open a channel to the terminal device. */
    sts = sys$assign( &term_dscr,       /* Terminal device name. */
                      &term_chan,       /* Channel. */
                      0,                /* Access mode. */
                      0);               /* Mailbox. */

    /* Return immediately on failure. */
    if ((sts& STS$M_SEVERITY) != STS$K_SUCCESS)
    {
        errno = EVMSERR;
        vaxc$errno = sts;
        return -1;
    }

    /* Get the current terminal characteristics (mode). */
    sts = sys$qiow( 0,                          /* Event flag. */
                    term_chan,                  /* Channel. */
                    IO$_SENSEMODE,              /* Function. */
                    0,                          /* IOSB. */
                    0,                          /* AST address. */
                    0,                          /* AST parameter. */
                    &term_chars,                /* P1 = Buffer address. */
                    sizeof term_chars,          /* P2 = Buffer size. */
                    0, 0, 0, 0);                /* P3-P6 not used. */

    if ((sts& STS$M_SEVERITY) != STS$K_SUCCESS)
    {
        errno = EVMSERR;
        vaxc$errno = sts;
    }
    else if (term_chars.class != DC$_TERM)
    {
        errno = ENOTTY;
    }
    else
    {
        /* Save the initial echo state, to allow proper restoration. */
        if (initial_echo < 0)
        {
            initial_echo = ((term_chars.basic_chars& TT$M_NOECHO) == 0);
        }

        if (able < 0)
        {
           if (initial_echo)
           {
               /* Was initially enabled. */
               able = 1;
           }
           else
           {
               /* Was initially disabled. */
               able = 0;
           }
        }

        if (able == 0)
        {
            /* Disable.  Set the no-echo bit. */
            term_chars.basic_chars |= TT$M_NOECHO;
        }
        else
        {
            /* Enable.  Clear the no-echo bit. */
            term_chars.basic_chars &= ~TT$M_NOECHO;
        }

        /* Set the terminal characteristics (mode). */
        sts = sys$qiow( 0,                      /* Event flag. */
                        term_chan,              /* Channel. */
                        IO$_SETMODE,            /* Function. */
                        0,                      /* IOSB. */
                        0,                      /* AST address. */
                        0,                      /* AST parameter. */
                        &term_chars,            /* P1 = Buffer address. */
                        sizeof term_chars,      /* P2 = Buffer size. */
                        0, 0, 0, 0);            /* P3-P6 not used. */

        if ((sts& STS$M_SEVERITY) != STS$K_SUCCESS)
        {
            errno = EVMSERR;
            vaxc$errno = sts;
        }
        else
        {
            /* All is well. */
            sts = 0;
        }
    }

    /* Close the channel to the terminal device. */
    sts2 = sys$dassgn( term_chan);              /* Channel. */
    if ((sts2& STS$M_SEVERITY) != STS$K_SUCCESS)
    {
        /* If all was not well, leave the old error codes as were. */
        if (sts == 0)
        {
            /* All was well, but DASSGN failed. */
            errno = EVMSERR;
            vaxc$errno = sts2;
            sts = sts2;
        }
    }
    return sts;
}

static char pw_buf[ PASS_MAX+ 1];

char *vms_getpass( const char *prompt)
{
    char *ret;
    int sts;
    FILE *sdc;

    ret = NULL;

    sdc = fopen( "SYS$COMMAND", "r");
    if (sdc != NULL)
    {
        sts = vms_set_term_echo( 0);
        if (sts == 0)
        {
            /* Read password string. */
            if (sts == 0)
            {
                fprintf( stdout, "%s", prompt);
                sts = fread( pw_buf, 1, PASS_MAX, sdc);
                if ((sts > 0) && (pw_buf[ sts- 1]) == '\n')
                {
                    pw_buf[ --sts] = '\0';
                }
                else
                {
                    pw_buf[ sts = '\0'];
                }
                ret = pw_buf;
            }
            sts = vms_set_term_echo( -1);
        }
        fclose( sdc);
    }
    return ret;
}

/*--------------------------------------------------------------------*/

/* vms_vers()

      Returns (run-time) VMS version string.
*/

char *vms_vers( void)
{
#define VERS_SIZE 8

static int sts = 0;
static char vers[ VERS_SIZE+ 1] = "";
unsigned short vers_len;

struct dsc$descriptor_s vers_descr =
 { VERS_SIZE, DSC$K_DTYPE_T, DSC$K_CLASS_S, vers };

if (sts == 0)
   {
   sts = lib$getsyi( &SYI$_VERSION, 0, &vers_descr, &vers_len, 0, 0);
   if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
   {
      vers[ vers_len] = '\0';

      /* Trim trailing spaces. */
      while ((vers_len > 0) && (vers[ vers_len- 1] == ' '))
         {
         vers[ --vers_len] = '\0';
         }
      }
   }
return vers;
}

/*--------------------------------------------------------------------*/

/* set_ods5_dest()

      Sets global "ods5_dest" according to the file system type of the
      argument: 0 for ODS2, 1 for ODS5.  (No change if other/unknown or
      failure.)

      Return value:  Status from sys$getdvi().
*/

int set_ods5_dest( char *path)
{
#ifdef DVI$C_ACP_F11V5

/* Should know about ODS5 file system.  Do actual check.
   (This should be non-VAX with __CRTL_VER >= 70200000.)
*/

struct dsc$descriptor_s dev_descr =
 { 0, DSC$K_DTYPE_T, DSC$K_CLASS_S, 0 };

int acp_code;
int sts;

/* Load path argument into device descriptor.
   Default to current default device.
*/
if (path == NULL)
   {
   dev_descr.dsc$a_pointer = "SYS$DISK";
   }
else
   {
   dev_descr.dsc$a_pointer = path;
   }
dev_descr.dsc$w_length = strlen( dev_descr.dsc$a_pointer);

/* Get file system type code.
   (Text results for this item code have been unreliable.)
*/
sts = lib$getdvi( &((int) DVI$_ACPTYPE),
                  0,
                  &dev_descr,
                  &acp_code,
                  0,
                  0);

if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
   {
   if (acp_code == DVI$C_ACP_F11V2)
      {
      ods5_dest = 0;
      }
   else if (acp_code == DVI$C_ACP_F11V5)
      {
      ods5_dest = 1;
      }
   }

return sts;

#else /* def DVI$C_ACP_F11V5 */

/* Too old for ODS5 file system.  Do nothing. */

return STS$K_SUCCESS;

#endif /* def DVI$C_ACP_F11V5 */
}

/*--------------------------------------------------------------------*/

/* ods2_conform()

   Replace ODS2-troublesome characters in the argument, overwriting the
   original string.  Replace "~" with "-", "@" with "$", and invalid
   dots and other characters with "_".  (Invalid dots are any in a
   directory name, and all but the last in a file name.)

   Return value: path.  (Someday this function could be written to leave
   the original string unchanged, and to return a freshly allocated
   string, possibly of a dfferent length.)

   2005-02-23 SMS.
   Changed to use char_prop[] look-up table, and to convert more invalid
   characters to "_".
*/

static
char *ods2_conform( char *path)
{
char *p;
char *prd;
char *prs;
char *prv;
unsigned char uchr;
unsigned char prop;

/* Locate the last slash. */
prs = rindex( path, '/');
if (prs == NULL)
   {
   prs = path;
   }

/* Locate the last dot after the last slash. */
prd = rindex( prs, '.');
if (prd == NULL)
   {
   prd = prs;
   }

/* Locate the version (after the last slash and dot). */
for (prv = prs+ strlen( prs) ; (--prv > prs) && isdigit( *prv); );
if ((*prv != ';') || (*(prv- 1) == '^'))
   {
   prv = prs+ strlen( prs);
   }

for (p = path ; p < prv; p++)
   {
   prop = char_prop[ uchr = *p];
   if ((prop& 4))
      {                                 /* Dot. */
      if (p < prd)
         {                              /* Before last dot in name. */
         *p = '_';                      /* Convert to "_". */
         }
      }
   else if ((prop& (32+ 16)) == 0)
      {                                 /* ODS2-invalid. */
      if (uchr == '~')
         {
         *p = '-';                      /* Convert to "-". */
         }
      else if (uchr == '@')
         {
         *p = '$';                      /* Convert to "$". */
         }
      else if (uchr != '/')             /* Leave "/" as-is. */
         {
         *p = '_';                      /* Convert to "_". */
         }
      }
   }
return path;
}

/*--------------------------------------------------------------------*/

/* ods_conform()

   Replace troublesome characters for the destination file system (ODS2
   or ODS5) with more legal characters.

   For ODS5, this is simply "?" -> "!" and "*" -> "#".

   For ODS2, see ods2_conform().

   Return value: path.  (Someday this function could be written to leave
   the original string unchanged, and to return a freshly allocated
   string, possibly of a dfferent length.)
*/

char *ods_conform( char *path)
{
char *p;

/* Replacements for invalid (printing) ODS5 characters. */
#define ODS5_QUESTION '!'
#define ODS5_ASTERISK '#'

if (ods5_dest <= 0)
   {
   /* Return ODS2-conformant file name. */
   return ods2_conform( path);
   }
else
   {
   /* Return ODS5-conformant file name.  ("?" -> "!", "*" -> "#".) */
   for (p = path; *p != '\0'; p++)
      {
      if (*p == '?')
         {
         *p = ODS5_QUESTION;
         }
      else if (*p == '*')
         {
         *p = ODS5_ASTERISK;
         }
      }
   return path;
   }
}

/*--------------------------------------------------------------------*/

/* Wget-private utime() code. */

/* Use long name (NAML) structure only where available.
   (This should be non-VAX with __CRTL_VER >= 70200000.)
*/

#ifdef NAML$C_BID

/* Use long name (NAML) structure. */

#define FAB$L_NAMX fab$l_naml
#define NAMX NAML
#define NAMX$C_MAXRSS NAML$C_MAXRSS
#define NAMX$B_DEV naml$l_long_dev_size
#define NAMX$L_DEV naml$l_long_dev
#define NAMX$L_ESA naml$l_long_expand
#define NAMX$B_ESL naml$l_long_expand_size
#define NAMX$B_ESS naml$l_long_expand_alloc
#define NAMX$W_FID naml$w_fid
#define NAMX$L_RSA naml$l_long_result
#define NAMX$B_RSL naml$l_long_result_size
#define NAMX$B_RSS naml$l_long_result_alloc
#define CC$RMS_NAMX cc$rms_naml

#else /* def NAML$C_BID */

/* Use short name (NAM) structure. */

#define FAB$L_NAMX fab$l_nam
#define NAMX NAM
#define NAMX$C_MAXRSS NAM$C_MAXRSS
#define NAMX$B_DEV nam$b_dev
#define NAMX$L_DEV nam$l_dev
#define NAMX$L_ESA nam$l_esa
#define NAMX$B_ESL nam$b_esl
#define NAMX$B_ESS nam$b_ess
#define NAMX$W_FID nam$w_fid
#define NAMX$L_RSA nam$l_rsa
#define NAMX$B_RSL nam$b_rsl
#define NAMX$B_RSS nam$b_rss
#define CC$RMS_NAMX cc$rms_nam

#endif /* def NAML$C_BID */

/*--------------------------------------------------------------------*/

/* Wget-private utime() code. */

/* Action routine for decc$to_vms(), in utime(). */

char *vms_path;

int set_vms_name( char *name, int type)
{
   vms_path = strdup(name);
   return 1;
}

/*--------------------------------------------------------------------*/

/* utime() replacement. */

int utime( const char *path, const struct utimbuf *times)
{
time_t utc_unsigned;

int chan, i;
int sts, sts2;

unsigned short int vms_num_vec_time[ 7];
static unsigned int vms_abs_time[ 2];
struct tm *tms;
struct _iosb iosb_q;

/* QIOW item list used to set creation and revision dates. */

struct atrdef ut_atr[ 3] = {
 {sizeof( vms_abs_time), ATR$C_CREDATE, UWA vms_abs_time},
 {sizeof( vms_abs_time), ATR$C_REVDATE, UWA vms_abs_time},
 {0,0,0}};

/* Various RMS structures used for file access. */

struct FAB ut_fab = cc$rms_fab;
struct RAB ut_rab = cc$rms_rab;
struct NAMX ut_namx = CC$RMS_NAMX;
static struct fibdef ut_fib;

/* Device and file name buffers and their descriptors. */

static char dev_namx[ NAMX$C_MAXRSS+ 1];
char esa_namx[ NAMX$C_MAXRSS+ 1];
char rsa_namx[ NAMX$C_MAXRSS+ 1];

struct dsc$descriptor dev_dsc =
 {0, DSC$K_DTYPE_T, DSC$K_CLASS_S, dev_namx};

struct dsc$descriptor fib_dsc =
 {sizeof( ut_fib), DSC$K_DTYPE_T, DSC$K_CLASS_S, (char *) &ut_fib};

/* "wget" provides a UNIX-like path name.  With "-O", a user may provide
   a VMS-like path name.  If a slash is found in the name, assume that
   it's UNIX-like, and convert it to VMS form.  Otherwise, use it as-is.
*/

if (strchr( path, '/') != NULL)
   {
   sts = decc$to_vms( path, set_vms_name, 0, 0);
   path = vms_path;
   }

/* Install the VMS file specification into the FAB. */

ut_fab.fab$l_fna = (char *) path;
ut_fab.fab$b_fns = (unsigned char) strlen( path);

ut_fab.fab$l_dna = "";
ut_fab.fab$b_dns = 0;

/* Point the FAB to the NAMX. */

ut_fab.FAB$L_NAMX = &ut_namx;

/* Install the name buffers into the NAM. */

ut_namx.NAMX$L_ESA = esa_namx;
ut_namx.NAMX$B_ESL = 0;
ut_namx.NAMX$B_ESS = sizeof( esa_namx)- 1;

ut_namx.NAMX$L_RSA = rsa_namx;
ut_namx.NAMX$B_RSL = 0;
ut_namx.NAMX$B_RSS = sizeof( rsa_namx)- 1;

/* Convert the modification time (UTC time_t) to local "tm" time. */

tms = localtime( &(times-> modtime));

/* Move (translate) "tm" structure local time to VMS vector time. */

if (tms != NULL)
   {
   vms_num_vec_time[ 0] = tms-> tm_year+ 1900;
   vms_num_vec_time[ 1] = tms-> tm_mon+ 1;
   vms_num_vec_time[ 2] = tms-> tm_mday;
   vms_num_vec_time[ 3] = tms-> tm_hour;
   vms_num_vec_time[ 4] = tms-> tm_min;
   vms_num_vec_time[ 5] = tms-> tm_sec;
   vms_num_vec_time[ 6] = 0;  /* centiseconds */

/* Convert VMS vector time to VMS absolute time (quadword). */

   sts = lib$cvt_vectim( vms_num_vec_time, vms_abs_time);

   if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
      {
/* Parse the file specification. */

      sts = sys$parse( &ut_fab, 0, 0);

      if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
         {
/* Locate the file. (Gets the FID.) */

         sts = sys$search( &ut_fab, 0, 0);

         if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
            {
/* Form the device name descriptor. */

            dev_dsc.dsc$w_length = ut_namx.NAMX$B_DEV;
            dev_dsc.dsc$a_pointer = (char *) ut_namx.NAMX$L_DEV;

/* Assign a channel to the disk device. */

            sts = sys$assign( &dev_dsc, &chan, 0, 0);

            if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
               {
/* Move the FID (and not the DID) into the FIB. */

               memset( (void *) &ut_fib, 0, sizeof( ut_fib));

               for (i = 0; i < 3; i++)
                  {
                  ut_fib.fib$w_fid[ i] = ut_namx.NAMX$W_FID[ i];
                  ut_fib.fib$w_did[ i] = 0;
                  }

/* Prevent this QIOW from setting the revision time to now. */

               ut_fib.fib$l_acctl = FIB$M_NORECORD;

/* Set the file dates. */

               sts = sys$qiow( 0,
                               chan,
                               IO$_MODIFY,
                               &iosb_q,
                               0,
                               0,
                               &fib_dsc,
                               0,
                               0,
                               0,
                               ut_atr,
                               0);

               if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
                  {
                   sts = iosb_q.iosb$w_status;
                  }
               sts2 = sys$dassgn( chan);

               if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
                  {
                  sts = sts2;
                  }
               }
            }
         }
      }
   }

/* Convert successful VMS status to zero = success status.
   If failure, set errno and vaxc$errno, and return -1 = failure status.
*/

if ((sts& STS$M_SEVERITY) == STS$K_SUCCESS)
   {
   sts = 0;
   }
else
   {
   errno = EVMSERR;
   vaxc$errno = sts;
   sts = -1;
   }

return sts;
}

/*--------------------------------------------------------------------*/

/* 2005-04-14 SMS.
 *
 *       vms_init_diag().
 *
 *    Get Wget debug option value.
 */

int vms_init_diag( void)
{
#ifdef ENABLE_DEBUG
return (opt.debug > 0);
#else /* def ENABLE_DEBUG */
return 0;
#endif /* def ENABLE_DEBUG */
}

/*--------------------------------------------------------------------*/

/* 2004-11-23 SMS.
 *
 *       get_rms_defaults().
 *
 *    Get user-specified values from (DCL) SET RMS_DEFAULT.  FAB/RAB
 *    items of particular interest are:
 *
 *       fab$w_deq         default extension quantity (blocks) (write).
 *       rab$b_mbc         multi-block count.
 *       rab$b_mbf         multi-buffer count (used with rah and wbh).
 */

/* Default RMS parameter values. */

#define RMS_DEQ_DEFAULT 16384   /* About 1/4 the max (65535 blocks). */
#define RMS_MBC_DEFAULT 127     /* The max, */
#define RMS_MBF_DEFAULT 2       /* Enough to enable rah and wbh. */

/* GETJPI item descriptor structure. */
typedef struct
    {
    short buf_len;
    short itm_cod;
    void *buf;
    int *ret_len;
    } jpi_item_t;

/* Durable storage */

static int rms_defaults_known = 0;

/* JPI item buffers. */
static unsigned short rms_ext;
static char rms_mbc;
static unsigned char rms_mbf;

/* Active RMS item values. */
unsigned short rms_ext_active;
char rms_mbc_active;
unsigned char rms_mbf_active;

/* GETJPI item lengths. */
static int rms_ext_len;         /* Should come back 2. */
static int rms_mbc_len;         /* Should come back 1. */
static int rms_mbf_len;         /* Should come back 1. */

/* Desperation attempts to define unknown macros.  Probably doomed.
 * If these get used, expect sys$getjpiw() to return %x00000014 =
 * %SYSTEM-F-BADPARAM, bad parameter value.
 * They keep compilers with old header files quiet, though.
 */
#ifndef JPI$_RMS_EXTEND_SIZE
#  define JPI$_RMS_EXTEND_SIZE 542
#endif /* ndef JPI$_RMS_EXTEND_SIZE */

#ifndef JPI$_RMS_DFMBC
#  define JPI$_RMS_DFMBC 535
#endif /* ndef JPI$_RMS_DFMBC */

#ifndef JPI$_RMS_DFMBFSDK
#  define JPI$_RMS_DFMBFSDK 536
#endif /* ndef JPI$_RMS_DFMBFSDK */

/* GETJPI item descriptor set. */

struct
    {
    jpi_item_t rms_ext_itm;
    jpi_item_t rms_mbc_itm;
    jpi_item_t rms_mbf_itm;
    int term;
    } jpi_itm_lst =
     { { 2, JPI$_RMS_EXTEND_SIZE, &rms_ext, &rms_ext_len },
       { 1, JPI$_RMS_DFMBC, &rms_mbc, &rms_mbc_len },
       { 1, JPI$_RMS_DFMBFSDK, &rms_mbf, &rms_mbf_len },
       0
     };

int get_rms_defaults()
{
int sts;

/* Get process RMS_DEFAULT values. */

sts = sys$getjpiw( 0, 0, 0, &jpi_itm_lst, 0, 0, 0);
if ((sts& STS$M_SEVERITY) != STS$M_SUCCESS)
    {
    /* Failed.  Don't try again. */
    rms_defaults_known = -1;
    }
else
    {
    /* Fine, but don't come back. */
    rms_defaults_known = 1;
    }

/* Limit the active values according to the RMS_DEFAULT values. */

if (rms_defaults_known > 0)
    {
    /* Set the default values. */

    rms_ext_active = RMS_DEQ_DEFAULT;
    rms_mbc_active = RMS_MBC_DEFAULT;
    rms_mbf_active = RMS_MBF_DEFAULT;

    /* Default extend quantity.  Use the user value, if set. */
    if (rms_ext > 0)
        {
        rms_ext_active = rms_ext;
        }

    /* Default multi-block count.  Use the user value, if set. */
    if (rms_mbc > 0)
        {
        rms_mbc_active = rms_mbc;
        }

    /* Default multi-buffer count.  Use the user value, if set. */
    if (rms_mbf > 0)
        {
        rms_mbf_active = rms_mbf;
        }
    }

if (vms_init_diag() > 0)
    {
    fprintf( stderr,
     "Get RMS defaults.  getjpi sts = %%x%08x.\n",
     sts);

    if (rms_defaults_known > 0)
        {
        fprintf( stderr,
         "               Default: deq = %6d, mbc = %3d, mbf = %3d.\n",
         rms_ext, rms_mbc, rms_mbf);
        }
    }
return sts;
}

/*--------------------------------------------------------------------*/

/* 2004-11-23 SMS.
 *
 *       acc_cb(), access callback function for DEC C [f]open().
 *
 *    Set some RMS FAB/RAB items, with consideration of user-specified
 * values from (DCL) SET RMS_DEFAULT.  Items of particular interest are:
 *
 *       fab$w_deq         default extension quantity (blocks).
 *       rab$b_mbc         multi-block count.
 *       rab$b_mbf         multi-buffer count (used with rah and wbh).
 *
 *    See also the FOP* macros in OSDEP.H.  Currently, no notice is
 * taken of the caller-ID value, but options could be set differently
 * for read versus write access.  (I assume that specifying fab$w_deq,
 * for example, for a read-only file has no ill effects.)
 */

/* acc_cb() */

int acc_cb( int *id_arg, struct FAB *fab, struct RAB *rab)
{
int sts;

/* Get process RMS_DEFAULT values, if not already done. */
if (rms_defaults_known == 0)
    {
    get_rms_defaults();
    }

/* If RMS_DEFAULT (and adjusted active) values are available, then set
 * the FAB/RAB parameters.  If RMS_DEFAULT values are not available,
 * suffer with the default parameters.
 */
if (rms_defaults_known > 0)
    {
    /* Set the FAB/RAB parameters accordingly. */
    fab-> fab$w_deq = rms_ext_active;
    rab-> rab$b_mbc = rms_mbc_active;
    rab-> rab$b_mbf = rms_mbf_active;

    /* Truncate at EOF on close, as we'll probably over-extend. */
    fab-> fab$v_tef = 1;

    /* If using multiple buffers, enable read-ahead and write-behind. */
    if (rms_mbf_active > 1)
        {
        rab-> rab$v_rah = 1;
        rab-> rab$v_wbh = 1;
        }

    if (vms_init_diag() > 0)
        {
        fprintf( stderr,
         "Open callback.  ID = %d, deq = %6d, mbc = %3d, mbf = %3d.\n",
         *id_arg, fab-> fab$w_deq, rab-> rab$b_mbc, rab-> rab$b_mbf);
        }
    }

/* Declare success. */
return 0;
}

/*--------------------------------------------------------------------*/

/* Added J.Lauret 05-Dec-1999 . Copied from Mosaic distribution */

/*
 * Here is a replacement for getpwuid for VMS.  It returns pointers
 * to userid (*pw_name) and owner (*pw_gecos) only.  Other fields
 * may be added later.
 * Note that sys$getuai returns owner as a counted string.
 */

#if __CRTL_VER < 70000000

#include <uaidef.h>

static struct passwd vms_passwd;
static char vms_userid[16];
static char vms_owner[40];

struct passwd *getpwuid()
{
struct  dsc$descriptor_s
{
  unsigned short  dsc$w_length;
  unsigned char   dsc$b_dtype;
  unsigned char   dsc$b_class;
  char            *dsc$a_pointer;
} user_desc = {0, DSC$K_DTYPE_T, DSC$K_CLASS_S, NULL};

  char *t_userid, owner[40];
  int status, length;
  struct {
    short buffer_length;
    short item_code;
    int buffer_address;
    int return_length_address;
    int terminator;
  } itmlst;

#ifdef __GNUC__
  (int)t_userid = cuserid((char *) NULL);
#else
  t_userid = cuserid((char *) NULL);
#endif /* GNU C is strange, GEC */
  user_desc.dsc$w_length       = strlen(t_userid);
  user_desc.dsc$a_pointer      = t_userid;
  itmlst.buffer_length         = sizeof(owner);
  itmlst.item_code             = UAI$_OWNER;
  itmlst.buffer_address        = (int)owner;
  itmlst.return_length_address = (int)&length;
  itmlst.terminator            = 0;
  status = sys$getuai(0, 0, &user_desc, &itmlst, 0, 0, 0);
  if ((stats& STS$M_SEVERITY) == STS$K_SUCCESS) {
    length = (int)owner[0];
    owner[length+1] = '\0';
    strcpy(vms_userid, t_userid);
    strcpy(vms_owner, &owner[1]);
  } else {
    vms_userid[0] = '\0';
    vms_owner[0] = '\0';
  }
  vms_passwd.pw_name = vms_userid;
  vms_passwd.pw_gecos = vms_owner;
  return (&vms_passwd);
}

/* Approximate localtime_r as best we can in its absence.  */
struct tm *
localtime_r (t, tp)
     const time_t *t;
     struct tm *tp;
{
  struct tm *l = localtime (t);
  if (! l)
    return 0;
  *tp = *l;
  return tp;
}

#endif  /* __CRTL_VER < 70000000 */

/*--------------------------------------------------------------------*/

/*
 * "version.c" information.
 */

const char *compilation_string = NULL;
const char *link_string = NULL;
const char *version_string = VERSION;

/*--------------------------------------------------------------------*/
