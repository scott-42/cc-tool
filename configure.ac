dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(cc-tool, 0.16, george-u@yandex.com)

# AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE(cc-tool, 0.16)

AC_PROG_LIBTOOL
AC_PROG_CXX

BOOST_REQUIRE([1.34])

BOOST_FILESYSTEM([mt])
BOOST_PROGRAM_OPTIONS([mt])
BOOST_SYSTEM([mt])
BOOST_REGEX([mt])
BOOST_THREADS([mt])

PKG_CHECK_MODULES([DEPS], [libusb-1.0 >= 1.0.0])

AC_LANG_PUSH([C++])
AC_CHECK_HEADERS( \
		boost/regex.hpp \
		boost/foreach.hpp \
		boost/filesystem.hpp \
		boost/shared_ptr.hpp \
		boost/signals2.hpp \
		boost/crc.hpp \
		boost/algorithm/string.hpp,
		[],[AC_MSG_ERROR(You need the Boost libraries.)])
AC_LANG_POP([C++])

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT

