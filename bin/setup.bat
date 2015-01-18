ECHO off
REM ---------------------------------------------------------------------------
REM OMhelp: Language Independent Embedded Documentation
REM           Copyright (C) 1998-2015 Bradley M. Bell
REM OMhelp is distributed under the terms of the
REM             GNU General Public License Version 2.
REM ---------------------------------------------------------------------------
REM BEGIN USER CHANGES
ECHO These parameters must be changed so they correspond to your system.
ECHO You will at least need to change bradbell to your user name.
ECHO on
SET zip_prefix=C:\Program Files\7-Zip
SET cmake_prefix=C:\Program Files (x86)\CMake
SET gnu_prefix=C:\GnuWin32
SET VC_dir=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC
REM
SET omhelp_prefix=C:\cygwin\home\bradbell
SET omhelp_version=20150117
ECHO off
REM END USER CHANGES
ECHO --------------------------------------------------------------------------
SET PATH=%gnu_prefix%/bin;%PATH%
CALL "%VC_dir%\vcvarsall.bat" x86
REM ---------------------------------------------------------------------------
SET web_page=https://github.com/bradbell/omhelp/archive
wget --no-check-certificate %web_page%/%omhelp_version%.zip^
	-O omhelp-%omhelp_version%.zip
ECHO --------------------------------------------------------------------------
"%zip_prefix%\7z" x omhelp-%omhelp_version%.zip
ECHO --------------------------------------------------------------------------
CD omhelp-%omhelp_version%
MKDIR build
CD build
"%cmake_prefix%\bin\cmake"^
	-G "NMake Makefiles"^
	-D omhelp_prefix="%omhelp_prefix%"^
	..
ECHO --------------------------------------------------------------------------
nmake install
ECHO bin/setup.bat: OK
