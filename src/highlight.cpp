/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin highlight.cpp$$

$section Highlighting Source Code$$

$head Prototype$$
$source%highlight.h%// BEGIN PROTOTYPE%// END PROTOTYPE%$$


$end
*/

# include <sstream>
# include "srchilite/sourcehighlight.h"
# include "srchilite/langmap.h"

# define DATADIR "/usr/share/source-highlight"

// used by omhelp to allocate and concatencate strings
extern "C" char* StrCat( const char *file, int line, ... );

extern "C" char* highlight(
	const char* input_text_cstr  ,
	const char* input_lang_cstr  ,
	const char* output_lang_cstr )
{	using std::string;

	// input string stream
	string input_text( input_text_cstr );
	std::stringstream input_sstream( input_text );

	// ctor
	string output_lang( output_lang_cstr );
	srchilite::SourceHighlight hiliter( output_lang );

	// source-highlight data directory
	hiliter.setDataDir(DATADIR);

	// output stream
	std::stringstream output_sstream;

	// convert from the input to output string stream
	string input_lang( input_lang_cstr );
	hiliter.highlight(input_sstream, output_sstream, input_lang);

	// return value
	char* ret = StrCat(
		__FILE__, __LINE__,  output_sstream.str().c_str(), NULL
	);

	return ret;
}

extern "C" char* file2lang(const char* file_name_cstr)
{
	srchilite::LangMap lang_map(DATADIR, "lang.map");
	std::string file_name( file_name_cstr);
	std::string lang = lang_map.getMappedFileNameFromFileName(file_name);

	// return value
	char* ret = StrCat(__FILE__, __LINE__,  lang.c_str(), NULL);

	return ret;
}
