dnl
dnl Check for `struct utimbuf'.
dnl

AC_DEFUN([WGET_STRUCT_UTIMBUF],
[AC_MSG_CHECKING([for struct utimbuf])
if test x"$ac_cv_header_utime_h" = xyes; then
  AC_EGREP_CPP([struct[ 	]+utimbuf],
    [#include <utime.h>],
    [AC_DEFINE(HAVE_STRUCT_UTIMBUF)
      AC_MSG_RESULT(yes)],
    AC_MSG_RESULT(no))
else
  AC_MSG_RESULT(no)
fi])


dnl Check for socklen_t.  The third argument of accept, getsockname,
dnl etc. is int * on some systems, but size_t * on others.  POSIX
dnl finally standardized on socklen_t, but older systems don't have
dnl it.  If socklen_t exists, we use it, else if accept() accepts
dnl size_t *, we use that, else we use int.

AC_DEFUN([WGET_SOCKLEN_T], [
  AC_MSG_CHECKING(for socklen_t)
  AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
socklen_t x;
],
    [], [AC_MSG_RESULT(yes)], [
      AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>
int accept (int, struct sockaddr *, size_t *);
],
      [], [
      AC_MSG_RESULT(size_t)
      AC_DEFINE(socklen_t, size_t)
    ], [
      AC_MSG_RESULT(int)
      AC_DEFINE(socklen_t, int)
    ])
  ])
])

dnl
dnl ansi2knr support: check whether C prototypes are available.
dnl

AC_DEFUN(AM_C_PROTOTYPES,
[AC_REQUIRE([AM_PROG_CC_STDC])
AC_BEFORE([$0], [AC_C_INLINE])
AC_MSG_CHECKING([for function prototypes])
if test "$am_cv_prog_cc_stdc" != no; then
  AC_MSG_RESULT(yes)
  AC_DEFINE(PROTOTYPES)
  U= ANSI2KNR=
else
  AC_MSG_RESULT(no)
  U=_ ANSI2KNR=./ansi2knr
  # Ensure some checks needed by ansi2knr itself.
  AC_HEADER_STDC
  AC_CHECK_HEADERS(string.h)
fi
AC_SUBST(U)dnl
AC_SUBST(ANSI2KNR)dnl
])


# serial 1

# @defmac AC_PROG_CC_STDC
# @maindex PROG_CC_STDC
# @ovindex CC
# If the C compiler in not in ANSI C mode by default, try to add an option
# to output variable @code{CC} to make it so.  This macro tries various
# options that select ANSI C on some system or another.  It considers the
# compiler to be in ANSI C mode if it defines @code{__STDC__} to 1 and
# handles function prototypes correctly.
#
# If you use this macro, you should check after calling it whether the C
# compiler has been set to accept ANSI C; if not, the shell variable
# @code{am_cv_prog_cc_stdc} is set to @samp{no}.  If you wrote your source
# code in ANSI C, you can make an un-ANSIfied copy of it by using the
# program @code{ansi2knr}, which comes with Ghostscript.
# @end defmac

AC_DEFUN(AM_PROG_CC_STDC,
[AC_REQUIRE([AC_PROG_CC])
AC_MSG_CHECKING([for ${CC-cc} option to accept ANSI C])
AC_CACHE_VAL(am_cv_prog_cc_stdc,
[am_cv_prog_cc_stdc=no
ac_save_CC="$CC"
# Don't try gcc -ansi; that turns off useful extensions and
# breaks some systems' header files.
# AIX			-qlanglvl=ansi
# Ultrix and OSF/1	-std1
# HP-UX			-Aa -D_HPUX_SOURCE
for ac_arg in "" -qlanglvl=ansi -std1 "-Aa -D_HPUX_SOURCE"
do
  CC="$ac_save_CC $ac_arg"
  AC_TRY_COMPILE(
[#if !defined(__STDC__)
choke me
#endif
/* DYNIX/ptx V4.1.3 can't compile sys/stat.h with -Xc -D__EXTENSIONS__. */
#ifdef _SEQUENT_
# include <sys/types.h>
# include <sys/stat.h>
#endif
], [
int test (int i, double x);
struct s1 {int (*f) (int a);};
struct s2 {int (*f) (double a);};],
[am_cv_prog_cc_stdc="$ac_arg"; break])
done
CC="$ac_save_CC"
])
AC_MSG_RESULT($am_cv_prog_cc_stdc)
case "x$am_cv_prog_cc_stdc" in
  x|xno) ;;
  *) CC="$CC $am_cv_prog_cc_stdc" ;;
esac
])


dnl ************************************************************
dnl START OF IPv6 AUTOCONFIGURATION SUPPORT MACROS
dnl ************************************************************

AC_DEFUN([TYPE_STRUCT_SOCKADDR_IN6],[
  ds6_have_sockaddr_in6=
  AC_CHECK_TYPES([struct sockaddr_in6],[
    ds6_have_sockaddr_in6=yes
  ],[
    ds6_have_sockaddr_in6=no
  ],[
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
  ])

  if test "X$ds6_have_sockaddr_in6" = "Xyes"; then :
    $1
  else :
    $2
  fi
])


AC_DEFUN([MEMBER_SIN6_SCOPE_ID],[
  AC_REQUIRE([TYPE_STRUCT_SOCKADDR_IN6])
  
  ds6_member_sin6_scope_id=
  if test "X$ds6_have_sockaddr_in6" = "Xyes"; then
    AC_CHECK_MEMBER([struct sockaddr_in6.sin6_scope_id],[
      ds6_member_sin6_scope_id=yes
    ],[
      ds6_member_sin6_scope_id=no
    ],[
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
    ])
  fi

  if test "X$ds6_member_sin6_scope_id" = "Xyes"; then
    AC_DEFINE([HAVE_SOCKADDR_IN6_SCOPE_ID], 1,
      [Define if struct sockaddr_in6 has the sin6_scope_id member])
    $1
  else :
    $2
  fi
])


AC_DEFUN([PROTO_INET6],[
  AC_CACHE_CHECK([for INET6 protocol support], [ds6_cv_proto_inet6],[
    AC_TRY_CPP([
#include <sys/types.h>
#include <sys/socket.h>

#ifndef PF_INET6
#error Missing PF_INET6
#endif
#ifndef AF_INET6
#error Mlssing AF_INET6
#endif
    ],[
      ds6_cv_proto_inet6=yes
    ],[
      ds6_cv_proto_inet6=no
    ])
  ])

  if test "X$ds6_cv_proto_inet6" = "Xyes"; then :
    $1
  else :
    $2
  fi
])


AC_DEFUN([GETADDRINFO_AI_ADDRCONFIG],[
  AC_CACHE_CHECK([if getaddrinfo supports AI_ADDRCONFIG],
    [ds6_cv_gai_ai_addrconfig],[
    AC_TRY_CPP([
#include <netdb.h>

#ifndef AI_ADDRCONFIG
#error Missing AI_ADDRCONFIG
#endif
    ],[
      ds6_cv_gai_ai_addrconfig=yes
    ],[
      ds6_cv_gai_ai_addrconfig=no
    ])
  ])

  if test "X$ds6_cv_gai_ai_addrconfig" = "Xyes"; then :
    $1
  else :
    $2
  fi
])


AC_DEFUN([GETADDRINFO_AI_ALL],[
  AC_CACHE_CHECK([if getaddrinfo supports AI_ALL],[ds6_cv_gai_ai_all],[
    AC_TRY_CPP([
#include <netdb.h>

#ifndef AI_ALL
#error Missing AI_ALL
#endif
    ],[
      ds6_cv_gai_ai_all=yes
    ],[
      ds6_cv_gai_ai_all=no
    ])
  ])

  if test "X$ds6_cv_gai_ai_all" = "Xyes"; then :
    $1
  else :
    $2
  fi
])


AC_DEFUN([GETADDRINFO_AI_V4MAPPED],[
  AC_CACHE_CHECK([if getaddrinfo supports AI_V4MAPPED],[ds6_cv_gai_ai_v4mapped],[
    AC_TRY_CPP([
#include <netdb.h>

#ifndef AI_V4MAPPED
#error Missing AI_V4MAPPED
#endif
    ],[
      ds6_cv_gai_ai_v4mapped=yes
    ],[
      ds6_cv_gai_ai_v4mapped=no
    ])
  ])

  if test "X$ds6_cv_gai_ai_v4mapped" = "Xyes"; then :
    $1
  else :
    $2
  fi
])

dnl ************************************************************
dnl END OF IPv6 AUTOCONFIGURATION SUPPORT MACROS
dnl ************************************************************

# This code originates from Ulrich Drepper's AM_WITH_NLS.

AC_DEFUN(WGET_WITH_NLS,
  [AC_MSG_CHECKING([whether NLS is requested])
    dnl Default is enabled NLS
    AC_ARG_ENABLE(nls,
      [  --disable-nls           do not use Native Language Support],
      HAVE_NLS=$enableval, HAVE_NLS=yes)
    AC_MSG_RESULT($HAVE_NLS)

    dnl If something goes wrong, we may still decide not to use NLS.
    dnl For this reason, defer AC_SUBST'ing HAVE_NLS until the very
    dnl last moment.

    if test x"$HAVE_NLS" = xyes; then
      AC_MSG_RESULT([language catalogs: $ALL_LINGUAS])
      AM_PATH_PROG_WITH_TEST(MSGFMT, msgfmt,
	[test -z "`$ac_dir/$ac_word -h 2>&1 | grep 'dv '`"], msgfmt)
      AM_PATH_PROG_WITH_TEST(XGETTEXT, xgettext,
	  [test -z "`$ac_dir/$ac_word -h 2>&1 | grep '(HELP)'`"], :)
      AC_SUBST(MSGFMT)
      AC_PATH_PROG(GMSGFMT, gmsgfmt, $MSGFMT)
      CATOBJEXT=.gmo
      INSTOBJEXT=.mo
      DATADIRNAME=share

      dnl Test whether we really found GNU xgettext.
      if test "$XGETTEXT" != ":"; then
	dnl If it is no GNU xgettext we define it as : so that the
	dnl Makefiles still can work.
	if $XGETTEXT --omit-header /dev/null 2> /dev/null; then
	  : ;
	else
	  AC_MSG_RESULT(
	    [found xgettext programs is not GNU xgettext; ignore it])
	  XGETTEXT=":"
	fi
      fi

      AC_CHECK_HEADERS(locale.h libintl.h)

      dnl Prefer gettext found in -lintl to the one in libc.
      dnl Otherwise it can happen that we include libintl.h from
      dnl /usr/local/lib, but fail to specify -lintl, which results in
      dnl link or run-time failures.  (Symptom: libintl_bindtextdomain
      dnl not found at link-time.)

      AC_CHECK_LIB(intl, gettext, [
        dnl gettext is in libintl; announce the fact manually.
        LIBS="-lintl $LIBS"
	AC_DEFINE(HAVE_GETTEXT)
      ], [
        AC_CHECK_FUNCS(gettext, [], [
          AC_MSG_RESULT([gettext not found; disabling NLS])
          HAVE_NLS=no
        ])
      ])

      dnl These rules are solely for the distribution goal.  While doing this
      dnl we only have to keep exactly one list of the available catalogs
      dnl in configure.in.
      for lang in $ALL_LINGUAS; do
	GMOFILES="$GMOFILES $lang.gmo"
	POFILES="$POFILES $lang.po"
      done
      dnl Construct list of names of catalog files to be constructed.
      for lang in $ALL_LINGUAS; do
        CATALOGS="$CATALOGS ${lang}${CATOBJEXT}"
      done

      dnl Make all variables we use known to autoconf.
      AC_SUBST(CATALOGS)
      AC_SUBST(CATOBJEXT)
      AC_SUBST(DATADIRNAME)
      AC_SUBST(GMOFILES)
      AC_SUBST(INSTOBJEXT)
      AC_SUBST(INTLLIBS)
      AC_SUBST(POFILES)
    fi
    AC_SUBST(HAVE_NLS)
    dnl Some independently maintained files, such as po/Makefile.in,
    dnl use `USE_NLS', so support it.
    USE_NLS=$HAVE_NLS
    AC_SUBST(USE_NLS)
    if test "x$HAVE_NLS" = xyes; then
      AC_DEFINE(HAVE_NLS)
    fi
  ])

dnl Generate list of files to be processed by xgettext which will
dnl be included in po/Makefile.
dnl
dnl This is not strictly an Autoconf macro, because it is run from
dnl within `config.status' rather than from within configure.  This
dnl is why special rules must be applied for it.
AC_DEFUN(WGET_PROCESS_PO,
  [
   dnl I wonder what the following several lines do...
   if test "x$srcdir" != "x."; then
     if test "x`echo $srcdir | sed 's@/.*@@'`" = "x"; then
       posrcprefix="$srcdir/"
     else
       posrcprefix="../$srcdir/"
     fi
   else
     posrcprefix="../"
   fi
   rm -f po/POTFILES
   dnl Use `echo' rather than AC_MSG_RESULT, because this is run from
   dnl `config.status'.
   echo "generating po/POTFILES from $srcdir/po/POTFILES.in"
   sed -e "/^#/d" -e "/^\$/d" -e "s,.*,	$posrcprefix& \\\\,"  \
       -e "\$s/\(.*\) \\\\/\1/" \
        < $srcdir/po/POTFILES.in > po/POTFILES
   echo "creating po/Makefile"
   sed -e "/POTFILES =/r po/POTFILES" po/Makefile.in > po/Makefile
  ])

# Search path for a program which passes the given test.
# Ulrich Drepper <drepper@cygnus.com>, 1996.
#
# This file may be copied and used freely without restrictions.  It
# can be used in projects which are not available under the GNU Public
# License but which still want to provide support for the GNU gettext
# functionality.  Please note that the actual code is *not* freely
# available.

# serial 1

dnl AM_PATH_PROG_WITH_TEST(VARIABLE, PROG-TO-CHECK-FOR,
dnl   TEST-PERFORMED-ON-FOUND_PROGRAM [, VALUE-IF-NOT-FOUND [, PATH]])
AC_DEFUN(AM_PATH_PROG_WITH_TEST,
[# Extract the first word of "$2", so it can be a program name with args.
set dummy $2; ac_word=[$]2
AC_MSG_CHECKING([for $ac_word])
AC_CACHE_VAL(ac_cv_path_$1,
[case "[$]$1" in
  /*)
  ac_cv_path_$1="[$]$1" # Let the user override the test with a path.
  ;;
  *)
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in ifelse([$5], , $PATH, [$5]); do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/$ac_word; then
      if [$3]; then
	ac_cv_path_$1="$ac_dir/$ac_word"
	break
      fi
    fi
  done
  IFS="$ac_save_ifs"
dnl If no 4th arg is given, leave the cache variable unset,
dnl so AC_PATH_PROGS will keep looking.
ifelse([$4], , , [  test -z "[$]ac_cv_path_$1" && ac_cv_path_$1="$4"
])dnl
  ;;
esac])dnl
$1="$ac_cv_path_$1"
if test -n "[$]$1"; then
  AC_MSG_RESULT([$]$1)
else
  AC_MSG_RESULT(no)
fi
AC_SUBST($1)dnl
])

# Include libtool code.

builtin(include, libtool.m4)dnl
