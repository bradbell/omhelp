echo off
rem ---------------------------------------------------------------------------
rem OMhelp: Source Code -> Help Files: Copyright (C) 1998-2005 Bradley M. Bell
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
if "%1%" == "Developer" goto DEVELOPER
if "%1%" == "Doc" goto DOC
	echo usage: RunOMhelp target (where target is Doc or Developer)
	goto DONE
: DEVELOPER
	echo Building developer documentation
	if exist Developer del /Q Developer 
	if exist Developer rmdir Developer 
	mkdir Developer
	cd    Developer
	..\src\omhelp ..\src\omh\omhelp.omh > ..\RunOMhelp.log -debug -omhelp_dir ..\OMhelp
	cd ..
	goto ERRORCHECK
: DOC
	echo Building user documentation
	if exist Doc del /Q Doc 
	if exist Doc rmdir Doc 
	mkdir Doc
	cd    Doc
	..\src\omhelp ..\omh\overview.omh > ..\RunOMhelp.log -xml -debug -omhelp_dir ..\OMhelp
	..\src\omhelp ..\omh\overview.omh  -debug -omhelp_dir ..\OMhelp
	cd ..
: ERRORCHECK
find "Latex error"                 RunOMhelp.log
find "Spelling error:"             RunOMhelp.log
find "Cross reference error"       RunOMhelp.log
find "OMhelp error in file"        RunOMhelp.log
find "Error occurred in or before" RunOMhelp.log
find "Cross reference destination defined at line" RunOMhelp.log
: DONE
