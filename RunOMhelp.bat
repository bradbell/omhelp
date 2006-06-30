echo off
rem ---------------------------------------------------------------------------
rem OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell
rem 
rem This program is free software; you can redistribute it and/or
rem modify it under the terms of the GNU General Public License
rem as published by the Free Software Foundation; either version 2
rem of the License, or (at your option) any later version.
rem 
rem This program is distributed in the hope that it will be useful,
rem but WITHOUT ANY WARRANTY; without even the implied warranty of
rem MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
rem GNU General Public License for more details.
rem 
rem You should have received a copy of the GNU General Public License
rem along with this program; if not, write to the Free Software
rem Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
rem ---------------------------------------------------------------------------
rem
if "%1%" == "Dev" goto DEVELOPER
if "%1%" == "Doc" goto DOC
	echo usage: RunOMhelp target (where target is Doc or Dev)
	goto DONE
: DEVELOPER
	echo Building developer documentation
	if exist Dev del /Q Dev 
	if exist Dev rmdir Dev 
	mkdir Dev
	cd    Dev
	..\src\src.exe ..\src\omh\omhelp.omh > ..\OMhelp.Dev.log -noframe -debug -omhelp_dir ..\OMhelp
	cd ..
	goto ERRORCHECK
: DOC
	echo Building user documentation
	if exist Doc del /Q Doc 
	if exist Doc rmdir Doc 
	mkdir Doc
	cd    Doc
	..\src\src.exe ..\omh\overview.omh > ..\OMhelp.Doc.log -xml -debug -omhelp_dir ..\OMhelp
	..\src\src.exe ..\omh\overview.omh  -noframe -debug -omhelp_dir ..\OMhelp
	cd ..
: ERRORCHECK
find "OMhelp Warning:"       RunOMhelp.log
find "OMhelp Error:"         RunOMhelp.log
: DONE
