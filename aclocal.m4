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
AC_MSG_CHECKING(for ${CC-cc} option to accept ANSI C)
AC_CACHE_VAL(am_cv_prog_cc_stdc,
[am_cv_prog_cc_stdc=no
ac_save_CC="$CC"
# Don't try gcc -ansi; that turns off useful extensions and
# breaks some systems' header files.
# AIX			-qlanglvl=ansi
# Ultrix and OSF/1	-std1
# HP-UX			-Aa -D_HPUX_SOURCE
# SVR4			-Xc -D__EXTENSIONS__
for ac_arg in "" -qlanglvl=ansi -std1 "-Aa -D_HPUX_SOURCE" "-Xc -D__EXTENSIONS__"
do
  CC="$ac_save_CC $ac_arg"
  AC_TRY_COMPILE(
[#if !defined(__STDC__) || __STDC__ != 1
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

AC_DEFUN(WGET_STRUCT_UTIMBUF,
[AC_MSG_CHECKING(for struct utimbuf)
if test x"$ac_cv_header_utime_h" = xyes; then
  AC_EGREP_CPP([struct[ 	]+utimbuf],
    [#include <utime.h>],
    [AC_DEFINE(HAVE_STRUCT_UTIMBUF)
      AC_MSG_RESULT(yes)],
    AC_MSG_RESULT(no))
else
  AC_MSG_RESULT(no)
fi])


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
      AC_MSG_RESULT("language catalogs: $ALL_LINGUAS")
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

      AC_CHECK_FUNCS(gettext, [], [
	AC_CHECK_LIB(intl, gettext, [
          dnl gettext is in libintl; announce the fact manually.
          LIBS="-lintl $LIBS"
	  AC_DEFINE(HAVE_GETTEXT)
        ], [
	  AC_MSG_RESULT(
	    [gettext not found; disabling NLS])
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
  [srcdir=$ac_given_srcdir # Advanced autoconf hackery
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
