# ifndef FUNREF_INCLUDED
# define FUNREF_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

# include "section.h"

extern void InsertInFunRef(
	char *tag,
	char *title
);
extern void FunRefPass1(SectionInfo *section);

extern void FunRefFree(void);

# endif
