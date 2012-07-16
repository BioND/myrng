AC_PREREQ([2.61])
AC_INIT([myrng], [1.5])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([1.11 -Wall -Werror silent-rules subdir-objects])
LT_PREREQ([2.2])
LT_INIT([disable-static])

AC_CONFIG_MACRO_DIR([m4])

AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_TRY_DOXYGEN

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([floor pow sqrt])

# Sanity check
AC_CONFIG_SRCDIR([myrng/myrng.h])

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

# Output files
AC_CONFIG_FILES([Makefile
                myrngWELL.pc
                myrngMT.pc
                Doxyfile])

dnl AC_CONFIG_HEADERS([config.h])

AC_OUTPUT
