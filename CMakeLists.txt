# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2016 Bradley M. Bell
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
SET(omhelp_version      "20151014" )
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
SET(topsrcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(topbindir ${CMAKE_CURRENT_BINARY_DIR})
# ---------------------------------------------------------------------------
MACRO(set_library_dir variable library prefix)
	SET(${variable} NOTFOUND)
	FOREACH(dir "lib" "lib64")
		MESSAGE(STATUS "Checking for ${library} in ${prefix}/${dir}")
		FILE(GLOB temp "${prefix}/${dir}/lib${library}.*" )
		IF( temp )
			SET(${variable} ${prefix}/${dir} )
		ENDIF( temp )
	ENDFOREACH(dir)
	IF( ${variable} )
		MESSAGE(STATUS "${variable} = ${${variable}}")
	ELSE( ${variable} )
		MESSAGE(FATAL_ERROR "Cannot find ${library} library files")
	ENDIF( ${variable} )
ENDMACRO( set_library_dir )
# ---------------------------------------------------------------------------
# boost_regex_prefix
command_line_arg(boost_regex_prefix /usr PATH
	"prefix were the boost regex library was install"
)
set_library_dir(
	boost_regex_LIBRARY_DIR "boost_regex" ${boost_regex_prefix}
)
# ---------------------------------------------------------------------------
# source_highlight_prefix
command_line_arg(source_highlight_prefix /usr PATH
	"prefix where source-highlight was install"
)
set_library_dir(
	source_highlight_LIBRARY_DIR "source-highlight" ${source_highlight_prefix}
)
# ---------------------------------------------------------------------------
# omhelp_prefix
command_line_arg(omhelp_prefix /usr PATH
	"prefix for omhelp install"
)
# ---------------------------------------------------------------------------
# omhelp_datadir
command_line_arg(omhelp_datadir share STRING
	"directory below omhelp prefix where omhelp data files are installed"
)
# ---------------------------------------------------------------------------
# omhelp_c_flags
command_line_arg(omhelp_c_flags NOTFOUND STRING
	"extra flags used to compile omhelp souce (besided debug and release flags)"
)
IF( omhelp_c_flags )
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${omhelp_c_flags}")
ENDIF( omhelp_c_flags )
# ---------------------------------------------------------------------------
# have_flex_and_bison
command_line_arg(have_flex_and_bison NOTFOUND BOOL
	"are the flex and bison programs available on the this system"
)
# ---------------------------------------------------------------------------
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(omh/getstarted)
# ---------------------------------------------------------------------------
INSTALL(
	PROGRAMS    ${topbindir}/src/omhelp${CMAKE_EXECUTABLE_SUFFIX}
	DESTINATION ${omhelp_prefix}/bin
)
INSTALL(
	DIRECTORY   omhelp_data
	DESTINATION ${omhelp_prefix}/${omhelp_datadir}
)
