# ifndef AUTOMATIC_INCLUDED
# define AUTOMATIC_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

# include "section.h"

extern int IsAutomaticSection(SectionInfo *section);
extern const char *AutomaticTag(int i);

extern void AutomaticAppendSection(
	SectionInfo *parent,
	const char *tag,
	const char *title,
	int letterheadings
);

# endif
