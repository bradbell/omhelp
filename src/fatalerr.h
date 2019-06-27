# ifndef FATALERR_INCLUDED
# define FATALERR_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern void fatalerr(const char *s1, ...);
extern void fatalomh(const char *s1, ...);
extern void fataltex(const char *s1, ...);

# ifdef __cplusplus
}
# endif
# endif
