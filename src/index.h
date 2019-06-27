# ifndef INDEX_INCLUDED
# define INDEX_INCLUDED
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

extern void InsertInIndex(
	const char *key,
	const char *tag,
	const char *head,
	const char escape
);
extern void MultipleIntoIndex(
	const char *key,
	const char *tag,
	const char *head,
	const char escape,
	const char *ignore
);
extern void CycleIntoIndex(
	const char *key,
	const char *tag,
	const char *head,
	const char escape
);
extern void IndexPass1(SectionInfo *section);
extern void IndexFreeMem(void);

# ifdef __cplusplus
}
# endif
# endif
