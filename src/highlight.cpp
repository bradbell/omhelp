/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2016 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin highlight$$
$spell
	cstr
	lang
	outlang
	xhtml
	cpp
	html
	Mem
$$

$section Highlighting Source Code$$

$head Prototype$$
$src%highlight.cpp%0
	%// BEGIN HIGHLIGHT_PROTOTYPE%// END HIGHLIGHT_PROTOTYPE%1%$$

$head SOURCE_HIGHLIGHT_01$$
If $code SOURCE_HIGHLIGHT_01$$ is $code 0$$,
this routine returns $code NULL$$.
Otherwise it returns a highlighted version of source code.

$head input_text_cstr$$
This is the source code that we are highlighting.

$head input_lang_cstr$$
This is the language corresponding to the source code; e.g.,
$code "cpp.lang"$$; see
$href%http://www.gnu.org/software/src-highlite/source-highlight.html#Supported-languages%supported languages%$$.

$head output_lang_cstr$$
This is the output language and must be either
$code "html.outlang"$$ or $code "xhtml.outlang"$$.

$head Return Value$$
The return value is a highlighted version of the input source code in
either HTML or XHTML depending on the output language.
The return value memory is allocated using $mref/AllocMem/$$
and should be freed using $cref/FreeMem/AllocMem/FreeMem/$$.

$end
*/

# include <sstream>
# include "srchilite/sourcehighlight.h"
# include "srchilite/langmap.h"

// used by omhelp to allocate and concatencate strings
extern "C" char* StrCat( const char *file, int line, ... );

// defined by main.c.in
extern "C" const char* source_highlight_prefix(void);

# if ! SOURCE_HIGHLIGHT_01
extern "C" char* highlight(const char*, const char*, const char*)
{	return NULL; }
# else
// BEGIN HIGHLIGHT_PROTOTYPE
extern "C" char* highlight(
	const char* input_text_cstr  ,
	const char* input_lang_cstr  ,
	const char* output_lang_cstr
) // END HIGHLIGHT_PROTOTYPE
{	using std::string;

	// source-highlight data directory
	string data_dir = source_highlight_prefix();
	data_dir       += "/share/source-highlight";

	// input string stream
	string input_text( input_text_cstr );
	std::stringstream input_sstream( input_text );

	// ctor
	string output_lang( output_lang_cstr );
	srchilite::SourceHighlight hiliter( output_lang );

	// source-highlight data directory
	hiliter.setDataDir(data_dir);

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
# endif
/*
----------------------------------------------------------------------------
$begin file2lang$$
$spell
	cstr
	Mem
$$

$section Determine Language Corresponding to a Source Code File$$

$head Prototype$$
$src%highlight.cpp%0
	%// BEGIN FILE2LANG_PROTOTYPE%// END FILE2LANG_PROTOTYPE%1%$$

$head SOURCE_HIGHLIGHT_01$$
If $code SOURCE_HIGHLIGHT_01$$ is $code 0$$,
this routine returns $code NULL$$.
Otherwise it returns the compute language corresponding to the
specified file.

$head file_name_cstr$$
This is the name of the file containing the compute language
source code.

$head Return Value$$
The return value is a $code source-highlight$$ input language.
It is allocated using $mref/AllocMem/$$
and should be freed using $cref/FreeMem/AllocMem/FreeMem/$$.

$end
*/

# if ! SOURCE_HIGHLIGHT_01
extern "C" char* file2lang(const char*)
{	return NULL; }
# else
// BEGIN FILE2LANG_PROTOTYPE
extern "C" char* file2lang(const char* file_name_cstr)
// END FILE2LANG_PROTOTYPE
{	using std::string;

	// source-highlight data directory
	string data_dir = source_highlight_prefix();
	data_dir       += "/share/source-highlight";

	srchilite::LangMap lang_map(data_dir, "lang.map");
	string file_name( file_name_cstr);
	string lang = lang_map.getMappedFileNameFromFileName(file_name);

	// return value
	char* ret = StrCat(__FILE__, __LINE__,  lang.c_str(), NULL);

	return ret;
}
# endif
