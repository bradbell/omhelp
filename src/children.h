# ifndef CHILDREN_INCLUDED
# define CHILDREN_INCLUDED
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

extern void ListChildren(SectionInfo *S, int printable);
extern void TableChildren(SectionInfo *S, int printable);

# ifdef __cplusplus
}
# endif
# endif
