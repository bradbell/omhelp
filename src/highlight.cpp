/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

# if ! SOURCE_HIGHLIGHT_01
# include <cstddef>
extern "C" char* highlight(const char*, const char*, const char*, int, int)
{	return NULL; }
extern "C" char* file_ext2lang(const char*)
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
$begin highlight_dev$$
$spell
	tabsize
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
$srcfile%src/highlight.cpp%0
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

$head indent$$
This is the number of spaces to add to the input after each newline.
Except for the last newline when it is the last character in
$icode input_text_cstr$$.

$head tabsize$$
This is the number of columns between each of the tab stops,
with the first tab stop being at the indentation specified by
$icode indent$$. There is no specification for what happens
if there is a tab before the first newline.

$head Return Value$$
The return value is a highlighted version of the input source code in
either HTML or XHTML depending on the output language.
The return value memory is allocated using $mref/AllocMem_dev/$$
and should be freed using $cref/FreeMem/AllocMem_dev/FreeMem/$$.

$end
*/
// BEGIN HIGHLIGHT_PROTOTYPE
extern "C" char* highlight(
	const char* input_text_cstr    ,
	const char* input_lang_cstr    ,
	const char* output_lang_cstr   ,
	int         indent             ,
	int         tabsize
) // END HIGHLIGHT_PROTOTYPE
{	using std::string;

	// source-highlight data directory
	string data_dir = source_highlight_prefix();
	data_dir       += "/share/source-highlight";

	// shorter name for the input text
	const char* c_str = input_text_cstr;

	// check if there is a newline before the fist non-whitespace character,
	// after the last non-whitespace character,
	// and count the number of newline characters
	size_t n_newline    = 0;
	bool   before_first = true;
	bool   after_last   = false;
	bool   space;
	while( *c_str != '\0' )
	{	space = std::isspace(*c_str) != 0;
		if( n_newline == 0 )
			before_first &= space;
		after_last &= space;
		if( *c_str == '\n' )
		{	after_last = true;
			n_newline++;
		}
		c_str++;
	}
	// restore c_str
	c_str = input_text_cstr;

	// use paragraph (or inline) mode
	bool paragraph_mode = before_first && after_last && n_newline > 4;

	// Add indentation and convert tabs to spaces
	string input_text;
	int    column               = -1;
	bool   previous_was_newline = false;
	size_t i_newline            = 0;
	while( *c_str != '\0' )
	{	if( previous_was_newline )
		{	for(int i = 0; i < indent; i++)
				input_text.push_back(' ');
			column = indent;
		}
		if( *c_str == '\n' )
		{	previous_was_newline = true;
			i_newline++;
			if( paragraph_mode )
			{	if( i_newline != 1 && i_newline != n_newline )
					input_text.push_back(*c_str);
			}
			else
			{	input_text.push_back(*c_str);
			}
		}
		else
		{	previous_was_newline = false;
			if( *c_str == '\t' )
			{	input_text.push_back(' ');
				column++;
				while( column % tabsize )
				{	input_text.push_back(' ');
					column++;
				}
			}
			else
			{	input_text.push_back(*c_str);
				column++;
			}
		}
		c_str++;
	}

	// convert from string to string stream
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
	c_str = output_string.c_str();

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

	// now we set the preformat style
	const char* start_output_cstr;
	if( paragraph_mode )
		start_output_cstr = "<pre><tt>";
	else
		start_output_cstr = "<pre style='display:inline'><tt>";

	// return value
	char* ret = StrCat(
		__FILE__, __LINE__,  start_output_cstr, c_str, NULL
	);

	return ret;
}
/*
----------------------------------------------------------------------------
$begin file_ext2lang_dev$$
$spell
	cstr
	Mem
$$

$section Determine Source Code Language Corresponding to a File Extension$$

$head Prototype$$
$srccode%cpp% */
extern "C" char* file_ext2lang(const char* file_ext_cstr)
/* %$$

$head SOURCE_HIGHLIGHT_01$$
If $code SOURCE_HIGHLIGHT_01$$ is $code 0$$,
this routine returns $code NULL$$.
Otherwise it returns the compute language corresponding to the
specified file.

$head file_ext_cstr$$
This is the extension, without the period $code .$$ at the beginning,
for the file containing the source code.
Case does not matter because it is mapped to
lower case before checking.

$head Return Value$$
The return value is a $code source-highlight$$ input language.
It is allocated using $mref/AllocMem_dev/$$
and should be freed using $cref/FreeMem/AllocMem_dev/FreeMem/$$.
If the language could not be determined, the empty string is returned; i.e.,
it has one character and it is the $code '\0'$$ character.

$end
*/
{	using std::string;

	// file extension
	string file_ext( file_ext_cstr);

	// map to lower case
	for(size_t i = 0; i < file_ext.size(); ++i)
		file_ext[i] = std::tolower( file_ext[i] );

	// source-highlight data directory
	string data_dir = source_highlight_prefix();
	data_dir       += "/share/source-highlight";
	//
	srchilite::LangMap lang_map(data_dir, "lang.map");
	string lang = lang_map.getMappedFileName(file_ext);

	// return value
	char* ret = StrCat(__FILE__, __LINE__,  lang.c_str(), NULL);

	return ret;
}
# endif
