# ifndef TEX_STYPE_INCLUDED
# define TEX_STYPE_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

typedef struct texstype
{	int  line;
	int  data;
	char *str;
	struct texstype *next;
	struct texstype *extra;
} TexStype;

# endif
