# ifndef TEXPARSE_INCLUDED
# define TEXPARSE_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern int texparse(void);
extern int texlex(void);
extern void texerror(char msg[]);

# ifdef __cplusplus
}
# endif
# endif
