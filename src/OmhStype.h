# ifndef OMH_STYPE_INCLUDED
# define OMH_STYPE_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


typedef struct omhstype
{	int  code;
	int  line;
	char *str;
} OmhStype;

# ifdef __cplusplus
}
# endif
# endif
