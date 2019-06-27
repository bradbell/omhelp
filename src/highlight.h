# ifndef HIGHLIGHT_INCLUDED
# define HIGHLIGHT_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif

// BEGIN PROTOTYPE
extern char* highlight(
	const char* input_text_cstr     ,
	const char* input_lang_cstr     ,
	const char* output_lang_cstr    ,
	int         indent              ,
	int         tabsize
);
extern char* file_ext2lang(const char* file_ext_cstr);
// END PROTOTYPE
# ifdef __cplusplus
}
# endif
# endif
