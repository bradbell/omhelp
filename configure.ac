dnl /* ------------------------------------------------------------------------
dnl OMhelp: Source Code -> Help Files: Copyright *(C) 1998-2005 Bradley M. Bell
dnl 
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl 
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
dnl .--------------------------------------------------------------------------
dnl Process this file with autoconf to produce a configure script

dnl        package   version           bug-report
AC_INIT(OMhelp, 08-04-12, bradbell@seanet.com)

dnl --------------------------------------------------------------------------

dnl The director where vim data is stored
AC_MSG_CHECKING( [VIMRUNTIME] )
AC_SUBST(VIMRUNTIME)
AM_CONDITIONAL(OMhelp_VIMRUNTIME, test "$VIMRUNTIME" != "" )
if test "$VIMRUNTIME" != "" ; then
	AC_MSG_RESULT( [$VIMRUNTIME] )
else
	AC_MSG_RESULT( [no] )
fi

dnl Set the default install prefix to the installers home directory
AC_PREFIX_DEFAULT(${HOME})

dnl Run any macros required for proper operations of generated Makefiles
dnl nostdinc: Do not define standard include directories in generated Makefiles
AM_INIT_AUTOMAKE(nostdinc)

dnl No default setting for compiler flags
AC_SUBST(CXXFLAGS, "")

dnl Have configure check source directory 
AC_CONFIG_SRCDIR(src/UniformWhiteSpace.c)

dnl Use config.h instead of make file command line arugments
AC_CONFIG_HEADER(src/config.h) 

dnl AC_PROG_CC([compiler-search-list]) outputs CC as C compiler to use
AC_PROG_CC

dnl AC_PROG_F77([complier-search-list]) outputs F77 as Fortran compiler to use
AC_PROG_F77
dnl AC_PROG_CP outputs CPP as command to run C preprocessor
AC_PROG_CPP

dnl Macros for linking fortran to C
AC_F77_WRAPPERS

dnl AC_CONFIG_FILES(file-list) for each file in the list, configure will 
dnl read file.in, do its substitutions, and create file
AC_CONFIG_FILES([ 
	Makefile
	src/Makefile
	omh/getstarted/makefile
])

dnl create all the requested output files
AC_OUTPUT
