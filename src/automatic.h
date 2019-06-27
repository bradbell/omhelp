# ifndef AUTOMATIC_INCLUDED
# define AUTOMATIC_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


# include "section.h"

extern int IsAutomaticSection(SectionInfo *section);
extern const char *AutomaticTag(int i);

extern void AutomaticAppendSection(
	SectionInfo *parent,
	const char *tag,
	const char *title,
	int letterheadings
);

# ifdef __cplusplus
}
# endif
# endif
