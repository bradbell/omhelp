# ifndef OMHPARSE_INCLUDED
# define OMHPARSE_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern int omhparse(void);
extern int omhlex(void);
extern void omherror(char msg[]);

# ifdef __cplusplus
}
# endif
# endif
