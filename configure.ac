#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([ohcs], [3.0.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11
# Checks for programs.

# Checks for libraries.

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
# Checks for header files.
AC_CHECK_HEADERS([thread cstdlib cstring vector cstdio ctime iostream algorithm string sstream ncurses.h omp.h])
# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
