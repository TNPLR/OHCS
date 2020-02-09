#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ohcs], [2.3])

AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_AUX_DIR([tools/])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lboost_system':
AC_CHECK_LIB([boost_system], [main])
# FIXME: Replace `main' with a function in `-lgmp':
AC_CHECK_LIB([gmp], [main])
# FIXME: Replace `main' with a function in `-lgmpxx':
AC_CHECK_LIB([gmpxx], [main])
# FIXME: Replace `main' with a function in `-lncurses':
AC_CHECK_LIB([ncurses], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])
# FIXME: Replace `main' with a function in `-lrt':
AC_CHECK_LIB([rt], [main])
# FIXME: Replace `main' with a function in `-ltinfo':
AC_CHECK_LIB([tinfo], [main])

# Checks for header files.
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
