# Author: Alexander Rykovanov 2009
#
#
# Distributed under the GNU LGPL License
# (See accompanying file LICENSE or copy at 
# http://www.gnu.org/licenses/lgpl.html)
#

AC_INIT([opcuamappings], [0.2.0], [rykovanov.as@gmail.com])
AC_CONFIG_AUX_DIR([.])
AC_CONFIG_SRCDIR([src/binary_stream.cpp])
AM_INIT_AUTOMAKE([-Wall -Werror])

CXXFLAGS="-O0 -g -Wall -std=c++0x"

AC_PROG_CXX
AM_PROG_AR
AC_PROG_LIBTOOL

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])


AC_ARG_WITH([gtest], 
            [AS_HELP_STRING([--with-gtest=DIR], [defines path to gtest root directory])],
            [ 
              AC_SUBST([GTEST_LIB], [-Wl,--whole-archive,$with_gtest/lib/.libs/libgtest.a,--no-whole-archive])
              AC_SUBST([GTEST_MAIN_LIB], [-Wl,--whole-archive,$with_gtest/lib/.libs/libgtest_main.a,--no-whole-archive])
              AC_SUBST([GTEST_INCLUDES], [-I$with_gtest/include])
              AC_MSG_NOTICE([Gtest path: $GTEST_INCLUDES]) 
            ], 
            [ 
              AC_SUBST([GTEST_LIB], [-lgtest])
              AC_SUBST([GTEST_MAIN_LIB], [-lgtest_main])
            ])

AC_ARG_ENABLE([gcov],
              [AS_HELP_STRING([--enable-gcov],[Enable support of coverage analize with gcov.])],
              [
                AC_SUBST([GCOV_FLAGS], ["-fprofile-arcs -ftest-coverage"])
                AC_SUBST([GCOV_LIBS], [-lgcov])
                AC_MSG_NOTICE([Enabled support of code coverage analize.]) 
              ],
              [
              ])

AC_SUBST([RELEASE_DATE], [$(date -R)])

#check headers
AC_CHECK_HEADERS([unistd.h])


#################################################################
AC_CONFIG_FILES([Makefile libopcuabinary.pc debian/changelog])

AC_OUTPUT

