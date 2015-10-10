# ifndef OUTPUT_TEXT_INCLUDED
# define OUTPUT_TEXT_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

extern int output_text(
	int         line        ,
	const char *s           ,
	int         pre         ,
	char        skip        ,
	int         check_spell ,
	const char *error_color
);

# endif
