@ echo off
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
rem BEGIN USER CHANGES
rem You can choose a different value for the OMhelp installation sub-directory
set install_sub_dir=OMhelp
rem
rem You can choose a different directory for OMhelp to change to after setup
set after_setup_dir=c:\cygwin\home\Brad
rem END USER CHANGES
rem -------------------------------------------------------------------------
echo Your choice for the OMhelp installation directory is:
echo c:\Program Files\%install_sub_dir%
echo .
echo Your choice of directory after setup is
echo %after_setup_dir%
echo .
echo Press Ctrl-C to stop or
pause
rem -------------------------------------------------------------------------
rem Delete the old copy of the installation directory 
if not exist "c:\Program Files\%install_sub_dir%" goto create_setup
echo First remove or rename the old install directory; for example, execute 
echo the del command, respond y to prompts, then execute the rmdir command:
echo del /P /S "c:\Program Files\%install_sub_dir%"
echo rmdir "c:\Program Files\%install_sub_dir%"
goto quit
rem -------------------------------------------------------------------------
:create_setup
rem Create the batch file to set the OMhelp environment in a command window
rem Avoid trailing spaces at the end of batch commands
echo @ echo off>                                           OMhelp\setup.bat
echo rem Set OMhelp environment variable>>                 OMhelp\setup.bat
echo set omhelp_dir=c:\Program Files\%install_sub_dir%>>   OMhelp\setup.bat
echo rem>>                                                 OMhelp\setup.bat
echo rem Add OMhelp installation director to the path>>    OMhelp\setup.bat
echo set path=%path%;c:\Program Files\%install_sub_dir%;>> OMhelp\setup.bat
echo rem>>                                                 OMhelp\setup.bat
echo rem Change into user's directory>>                    OMhelp\setup.bat
echo cd "%after_setup_dir%">>                              OMhelp\setup.bat
rem -------------------------------------------------------------------------
rem Create the installation directory
mkdir "c:\Program Files\%install_sub_dir%"
rem -------------------------------------------------------------------------
rem Copy the OMhelp data files to the install directory
copy /b OMhelp\* "c:\Program Files\%install_sub_dir%"
rem -------------------------------------------------------------------------
rem Copy the OMhelp Dos executable file to the install directory
echo OMhelp\omhelp.exe
copy /b src\src.exe "c:\Program Files\%install_sub_dir%\omhelp.exe"
rem -------------------------------------------------------------------------
:quit
@ echo on
