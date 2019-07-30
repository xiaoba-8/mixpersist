#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([include/mix/database/db_errno.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([mixdb], 1.0)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_MKDIR_P

# Checks for libraries.
AC_CHECK_LIB([mysqlcppconn])
AC_CHECK_LIB([occi])

# Checks for header files.
AC_CHECK_HEADERS([netdb.h stddef.h stdint.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_PROG_LIBTOOL

# Checks for library functions.
AC_FUNC_MKTIME
AC_CHECK_FUNCS([gethostbyname gethostname gettimeofday localtime_r memset tzset])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 libex/Makefile
                 libex/mysql/Makefile
                 libex/oracle/Makefile
                 src/Makefile])
AC_OUTPUT
