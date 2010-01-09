/*
 *    Various VMS-specific items.
 *
 *    Includes:
 *
 *  Emergency replacement for <utime.h> for VMS CRTL before V7.3.
 *
 *  Emergency replacement for <pwd.h> for VMS CRTL before V7.0.
 *
 *  Emergency substitution of stat() for lstat() for VAX and VMS CRTL
 *  before V7.3-1.
 *
 *  Prototypes for VMS-specific functions:
 *     acc_cb()
 *     utime() (CRTL < V7.3)
 *     ods_conform()
 *     set_ods5_dest()
 *     vms_arch()
 *     vms_basename()
 *     vms_vers()
 *
 *  Global storage:
 *     ods5_dest
 */

#ifndef __VMS_H_INCLUDED
#define __VMS_H_INCLUDED

/* Emergency replacement for <utime.h> for VMS before V7.3. */

#if __CRTL_VER < 70300000

#include <types.h>

/* The "utimbuf" structure is used by "utime()". */
struct utimbuf {
        time_t actime;          /* access time */
        time_t modtime;         /* modification time */
};

/* Function prototypes for utime(), */

int utime( const char *path, const struct utimbuf *times);

#else /* __CRTL_VER < 70300000 */

#include <utime.h>

#endif /* __CRTL_VER < 70300000 */


/* Emergency substitution of stat() for lstat() for VAX and VMS CRTL
   before V7.3-1.
*/
#if defined(__VAX) || __CRTL_VER < 70301000

#define lstat( __p1, __p2) stat( __p1, __p2)

#endif /* defined(__VAX) || __CRTL_VER < 70301000 */


/* Global storage. */

/*    VMS destination file system type.  < 0: unset/unknown
                                         = 0: ODS2
                                         > 0: ODS5
*/

extern int ods5_dest;


/* Function prototypes. */

extern int acc_cb();

char *ods_conform( char *path);

int set_ods5_dest( char *path);

char *vms_arch( void);

char *vms_basename( char *file_spec);

char *vms_vers( void);

/* Emergency replacement for <pwd.h> (for VMS CRTL before V7.0). */

/* Declare "passwd" structure, if needed. */

#ifndef HAVE_PWD_H

struct passwd {
        char    *pw_name;
        char    *pw_passwd;
        int     pw_uid;
        int     pw_gid;
        short   pw_salt;
        int     pw_encrypt;
        char    *pw_age;
        char    *pw_comment;
        char    *pw_gecos;
        char    *pw_dir;
        char    *pw_shell;
};

struct passwd *getpwuid();

#endif /* HAVE_PWD_H */

#endif /* __VMS_H_INCLUDED */
