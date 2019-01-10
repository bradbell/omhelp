# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2018 Bradley M. Bell
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
SET(omhelp_version "20190110")
SET(omhelp_description  "Language independent embedded code documentation")
SET(omhelp_url          "http://www.seanet.com/~bradbell/omhelp")
PROJECT(omhelp)
SET(topsrcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(topbindir ${CMAKE_CURRENT_BINARY_DIR})
# -----------------------------------------------------------------------------
# CHECK_CXX_SOURCE_COMPILES(source variable)
# Checks whether the code given in source will compile, link and run and
# return zero status. You can set
# CMAKE_REQUIRED_LIBRARIES, CMAKE_REQUIRED_FLAGS and CMAKE_REQUIRED_INCLUDES
# accordingly if additional libraries or compiler flags are required.
INCLUDE(CheckCXXSourceRuns)
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
SET(topbindir ${CMAKE_CURRENT_BINARY_DIR})
# ---------------------------------------------------------------------------
MACRO(set_library_info dir_out file_out library prefix)
	SET(${dir_out} NOTFOUND)
	SET(${file_out} NOTFOUND)
	FOREACH(extension "so" "a")
		FOREACH(dir "lib" "lib64")
			SET(value "${prefix}/${dir}/lib${library}.${extension}" )
			IF(EXISTS "${value}" )
				IF( NOT ${dir_out} )
					SET(${dir_out} "${prefix}/${dir}")
					SET(${file_out} "lib${library}.${extension}")
				ENDIF( NOT ${dir_out} )
			ENDIF(EXISTS "${value}" )
		ENDFOREACH(dir)
	ENDFOREACH(extension)
	IF( ${dir_out} )
		MESSAGE(STATUS "${library} dir  = ${${dir_out}}" )
		MESSAGE(STATUS "${library} file = ${${file_out}}" )
	ELSE( ${dir_out} )
		MESSAGE(STATUS "WARNING: Cannot find ${library} library files")
	ENDIF( ${dir_out} )
ENDMACRO( set_library_info )
# ---------------------------------------------------------------------------
# boost_regex_prefix
command_line_arg(boost_regex_prefix /usr PATH
	"prefix were the boost regex library was install"
)
set_library_info(
	boost_regex_dir boost_regex_file
	"boost_regex" ${boost_regex_prefix}
)
# ---------------------------------------------------------------------------
# source_highlight_prefix
command_line_arg(source_highlight_prefix /usr PATH
	"prefix where source-highlight was install"
)
set_library_info(
	source_highlight_dir source_highlight_file
	 "source-highlight" ${source_highlight_prefix}
)
# ---------------------------------------------------------------------------
# have_flex_and_bison
command_line_arg(have_flex_and_bison NOTFOUND BOOL
	"are the flex and bison programs available on the this system"
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
# omhelp_build_type
command_line_arg(omhelp_build_type NOTFOUND STRING
	"DEBUG (compile for debugging) or RELEASE (compile for speed)"
)
IF ( omhelp_build_type )
	STRING(TOUPPER "${omhelp_build_type}" CMAKE_BUILD_TYPE)
ELSE ( omhelp_build_type )
	SET(CMAKE_BUILD_TYPE "DEBUG")
ENDIF ( omhelp_build_type )
MESSAGE(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}" )
# ---------------------------------------------------------------------------
# source_highlight_01
#
LINK_DIRECTORIES( ${source_highlight_LIBRARY_DIR} )
IF( source_highlight_dir AND boost_regex_dir )
	SET(CMAKE_REQUIRED_INCLUDES "${source_highlight_prefix}/include" )
	SET(CMAKE_REQUIRED_LIBRARIES
		"${source_highlight_dir}/${source_highlight_file}"
		"${boost_regex_dir}/${boost_regex_file}"
	)
ELSEIF( source_highlight_dir AND boost_regex_dir )
	SET(CMAKE_REQUIRED_INCLUDES "")
	SET(CMAKD_REQUIRED_LIBRARIES "")
ENDIF( source_highlight_dir AND boost_regex_dir )
SET(CMAKE_REQUIRED_DEFINITIONS "")
SET(source_before "
# include <cassert>
# include <cstring>
# include <sstream>
# include \"srchilite/sourcehighlight.h\"
# include \"srchilite/langmap.h\"
int main(void)
{
	std::string input_string( \"extern highlight(const char* text);\" );
	std::stringstream input_sstream( input_string );
	std::stringstream output_sstream;
	//
	std::string input_lang(\"cpp.lang\");
	std::string output_lang(\"html.outlang\");
	//
	srchilite::SourceHighlight hiliter( output_lang );
	hiliter.highlight(input_sstream, output_sstream, input_lang);
	//
	// check some asserts that appear in omhelp.y
	char null_char  = static_cast<char>(0);
	std::string stmp = output_sstream.str();
	const char* ctmp = stmp.c_str();
	assert( strncmp(ctmp, \"<!--\", 4) == 0 );
	while( *ctmp != '>' && *ctmp != null_char )
		ctmp++;
	while( *ctmp != '<' && *ctmp != null_char )
		ctmp++;
	assert( strncmp(ctmp, \"<pre><tt>\", 9) == 0 );
	//
	return 0;
}"
)
STRING(
	REPLACE "DATADIR" "${source_highlight_prefix}/share/source-highlight"
	source_after "${source_before}"
)
CHECK_CXX_SOURCE_RUNS("${source_after}" source_highlight_result)
IF( source_highlight_result )
	SET(source_highlight_01 1)
ELSE( source_highlight_result )
	SET(source_highlight_01 0)
	MESSAGE(STATUS "WARNING: \$srcfile command NOT available with this omhelp")
ENDIF( source_highlight_result )
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
# ---------------------------------------------------------------------------
# Use CONFIGURE_FILE to modify inclusion of files
# that should only be included when $srcfile command is available:
IF( source_highlight_01 )
	SET(highlight_cpp      "highlight.cpp/"     )
	SET(src_omh        "srcfile.omh/"       )
	SET(srccode_omh        "srccode.omh/"       )
	SET(start_src_omh  "start_src.omh/" )
ELSE( source_highlight_01 )
	SET(src_omh        "no_srcfile.omh/"    )
	SET(srccode_omh        "no_srccode.omh/"    )
	SET(highlight_cpp      ""                   )
	SET(start_src_omh  ""                   )
ENDIF( source_highlight_01 )
CONFIGURE_FILE(
	src/omh/misc.omh.in               src/omh/misc.omh
)
CONFIGURE_FILE(
	omh/file.omh.in                   omh/file.omh
)
CONFIGURE_FILE(
	omh/getstarted/get_started.omh.in omh/getstarted/get_started.omh
)
# ---------------------------------------------------------------------------
