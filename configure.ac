#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([dcc], [0.5], [dzchen@stanford.edu])
AC_CONFIG_SRCDIR([src/utility.cc])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX

# Checks for libraries.
AC_CHECK_LIB([m], [log])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h stddef.h getopt.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strtol])
AC_CHECK_FUNCS([strdup])

AC_CONFIG_FILES(
[
  Makefile
  src/Makefile
  tests/Makefile
  tests/codegen/Makefile
])

AC_OUTPUT
