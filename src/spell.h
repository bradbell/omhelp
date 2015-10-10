# ifndef SPELL_INCLUDED
# define SPELL_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

extern void InitSpelling(const char *dir);
extern void SpellingOkList(const char *special);
extern const char *SpellingError(const char *text, int *nOut);
extern void FreeSpelling(int debug);

# endif
