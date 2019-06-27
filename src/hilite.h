# ifndef HILITE_INCLUDED
# define HILITE_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif



void hilite_pattern(
	int         line      ,
	int         n_pattern ,
	char       *patterns
);
void hilite_command(
	int         line      ,
	int         n_command ,
	char       *commands
);
void hilite_seq(
	int         line      ,
	int         n_pair    ,
	char       *pairs
);
void hilite_set_default(void);
void hilite_get_default(void);
void hilite_out(
	const char *command        ,
	int         line           ,
	int         check_spell    ,
	const char *error_color    ,
	const char *hilite_color   ,
	int         pre            ,
	char       *text
);

# ifdef __cplusplus
}
# endif
# endif
