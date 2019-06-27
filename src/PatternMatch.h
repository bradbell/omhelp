# ifndef PATTERN_MATCH_INCLUDED
# define PATTERN_MATCH_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern int PatternMatchLen(const char *p, char escape);
extern int PatternMatchCh(char *ch);

# ifdef __cplusplus
}
# endif
# endif
