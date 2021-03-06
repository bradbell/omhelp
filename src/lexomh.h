# ifndef LEXOMH_INCLUDED
# define LEXOMH_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern char GetCommandKeyCharacter(void);
extern void SetCommandKeyCharacter(char c);
extern char *TokenCode2String(int code);

# ifdef __cplusplus
}
# endif
# endif
