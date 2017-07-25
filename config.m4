dnl $Id$
dnl config.m4 for extension mystem

PHP_ARG_WITH(mystem, for mystem support,
Make sure that the comment is aligned:
[  --with-mystem             Include mystem support])

if test "$PHP_MYSTEM" != "no"; then

  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)

  if ! test -x $PKG_CONFIG; then
    AC_MSG_ERROR([pkg-config is required])
  fi

  AC_MSG_CHECKING([for libicu using pkg-config])
  if ! $PKG_CONFIG --exists icu-uc; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([libicu not found])
  fi
  AC_MSG_RESULT([found])

  PHP_ICU_LIBS=`$PKG_CONFIG icu-uc --libs`
  PHP_ICU_INCS=`$PKG_CONFIG icu-uc --cflags`

  PHP_EVAL_LIBLINE($PHP_ICU_LIBS, MYSTEM_SHARED_LIBADD)
  PHP_EVAL_INCLINE($PHP_ICU_INCS)

  SEARCH_PATH="./lib /usr/local/lib64 /usr/lib64"
  SEARCH_FOR="libmystem_c_binding.so"
  AC_MSG_CHECKING([for mystem files in default path])
  for i in $SEARCH_PATH ; do
    if test -r $i/$SEARCH_FOR; then
      MYSTEM_DIR=$i
      AC_MSG_RESULT(found in $i)
    fi
  done

  if test -z "$MYSTEM_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please install the mystem_c_binding library])
  fi

  LIBNAME=mystem_c_binding
  LIBSYMBOL=MystemAnalyze

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MYSTEM_DIR, MYSTEM_SHARED_LIBADD)
    AC_DEFINE(HAVE_MYSTEMLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong mystem lib version or lib not found])
  ],[
    -L$MYSTEM_DIR -lm
  ])

  PHP_REQUIRE_CXX()
  PHP_SUBST(MYSTEM_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mystem, mystem.cpp, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
