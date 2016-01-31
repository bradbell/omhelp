# ifndef HIGHLIGHT_INCLUDED
# define HIGHLIGHT_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

// BEGIN PROTOTYPE
extern char* highlight(
	const char* input_text_cstr  ,
	const char* input_lang_cstr  ,
	const char* output_lang_cstr
);
extern char* file2lang(const char* file_name_cstr);
// END PROTOTYPE

# endif

