/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2016 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

# if ! SOURCE_HIGHLIGHT_01
# include <cstddef>
extern "C" char* highlight(const char*, const char*, const char*)
{	return NULL; }
extern "C" char* file2lang(const char*)
{	return NULL; }
# else

# include <sstream>
# include <cstring>
# include <cassert>
# include "srchilite/sourcehighlight.h"
# include "srchilite/langmap.h"

// used by omhelp to allocate and concatencate strings
extern "C" char* StrCat( const char *file, int line, ... );

// defined by main.c.in
extern "C" const char* source_highlight_prefix(void);
/*
-----------------------------------------------------------------------------
$begin highlight$$
$spell
	cstr
	lang
	outlang
	xhtml
	cpp
	html
	Mem
	newline
	preformatted
$$

$section Highlighting Source Code$$

$head Prototype$$
$srcfile%highlight.cpp%0
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

$head start_with_newline$$
This is either zero or one. If it is one,
then make sure that the first output character in the preformatted text,
that is not a space or tab, is a newline.

$head Return Value$$
The return value is a highlighted version of the input source code in
either HTML or XHTML depending on the output language.
The return value memory is allocated using $mref/AllocMem/$$
and should be freed using $cref/FreeMem/AllocMem/FreeMem/$$.

$end
*/
// BEGIN HIGHLIGHT_PROTOTYPE
extern "C" char* highlight(
	const char* input_text_cstr    ,
	const char* input_lang_cstr    ,
	const char* output_lang_cstr   ,
	int         start_with_newline
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

	// pointer to beginning of output string
	string output_string ( output_sstream.str() );
	const char* c_str = output_string.c_str();

	// check that string begins with <!--
	assert( std::strncmp(c_str, "<!--", 4) == 0 );

	// skip comment at beginning of string
	while( *c_str != '>' && *c_str != '\0' )
			c_str++;
	assert( std::strncmp(c_str - 2, "-->", 3) == 0 );

	// skip to start of pre command
	while( *c_str != '<' && *c_str != '\0' )
			c_str++;

	// check preformatted text command
	assert( std::strncmp(c_str, "<pre><tt>", 9) == 0 );
	c_str += 9;

	// Add display inline to command
	std::string start_output("<pre style='display:inline'><tt>");

	// check if we need to add a newline to he beginning
	if( start_with_newline )
	{	while( *c_str == ' ' || *c_str == '\t' )
			c_str++;
		if( *c_str != '\n' )
			start_output.push_back('\n');
	}

	// return value
	char* ret = StrCat(
		__FILE__, __LINE__,  start_output.c_str(), c_str, NULL
	);

	return ret;
}
/*
----------------------------------------------------------------------------
$begin file2lang$$
$spell
	cstr
	Mem
$$

$section Determine Language Corresponding to a Source Code File$$

$head Prototype$$
$srcfile%highlight.cpp%0
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
