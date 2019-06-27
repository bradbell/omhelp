# ifndef COLOR_SWITCH_INCLUDED
# define COLOR_SWITCH_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern void color_switch(
	char       *text            ,
	const char *first_color     ,
	const char *second_color    ,
	char        escape          ,
	int         line            ,
	const char *cmd             ,
	int         check_spell     ,
	const char *error_color
);

# ifdef __cplusplus
}
# endif
# endif
