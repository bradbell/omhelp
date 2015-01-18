# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2015 Bradley M. Bell
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# ---------------------------------------------------------------------------
# Set the minimum required version of cmake for this project
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(omhelp_version      "20150117" )
SET(omhelp_description  "Language independent embedded code documentation")
SET(omhelp_url          "http://www.seanet.com/~bradbell/omhelp")
PROJECT(omhelp)
# ---------------------------------------------------------------------------
MACRO(command_line_arg variable_out default_in type_in description_in)
	IF( NOT ( ${type_in} STREQUAL "STRING" ) )
	IF( NOT ( ${type_in} STREQUAL "PATH" ) )
	IF( NOT ( ${type_in} STREQUAL "BOOL" ) )
		MESSAGE(FATAL_ERROR, "command_line_arg: bug in CMakeLists.txt")
	ENDIF( NOT ( ${type_in} STREQUAL "BOOL" ) )
	ENDIF( NOT ( ${type_in} STREQUAL "PATH" ) )
	ENDIF( NOT ( ${type_in} STREQUAL "STRING" ) )
	#
	SET(${variable_out} "${default_in}" CACHE ${type_in} "${description_in}")
	MESSAGE(STATUS "${variable_out} = \"${${variable_out}}\"")
ENDMACRO( command_line_arg )
SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(bindir ${CMAKE_CURRENT_BINARY_DIR})
# ---------------------------------------------------------------------------
# omhelp_prefix
command_line_arg(omhelp_prefix /usr PATH 
	"prefix for omhelp install"
)
# omhelp_datadir
command_line_arg(omhelp_datadir share STRING 
	"directory below prefix where cmake will install omhelp data files"
)
# ---------------------------------------------------------------------------
ADD_SUBDIRECTORY(src)
# ---------------------------------------------------------------------------
ENABLE_LANGUAGE( Fortran OPTIONAL )
IF( CMAKE_Fortran_COMPILER_WORKS )
	INCLUDE( FortranCInterface )
	IF( FortranCInterface_MODULE_FOUND )
		# 2DO: include just C examples when Fortran linking not available
		ADD_SUBDIRECTORY(omh/getstarted)
	ENDIF( FortranCInterface_MODULE_FOUND )
ENDIF( CMAKE_Fortran_COMPILER_WORKS )
# ---------------------------------------------------------------------------
INSTALL(
	PROGRAMS    ${bindir}/src/omhelp${CMAKE_EXECUTABLE_SUFFIX}
	DESTINATION ${omhelp_prefix}/bin
)
INSTALL(
	DIRECTORY   omhelp_data
	DESTINATION ${omhelp_prefix}/${omhelp_datadir}
)
