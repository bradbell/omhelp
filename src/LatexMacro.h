# ifndef LATEX_MACRO_INCLUDED
# define LATEX_MACRO_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif

/*
$begin LatexMacro$$

$section Implementation of Latex Macro Preprocessor$$

$contents/
	LatexMacro.c/$$

$end
*/

extern void        LatexMacroUserInput(int line, const char *input);
extern void        LatexMacroFree();
extern char        LatexMacroGetCh(void);
extern int         LatexMacroInputLine(void);
extern const char *LatexMacroInputFile(void);
extern const char *LatexMacroExpandInput(void);
extern int         LatexMacroExpandLine(void);
extern const char *LatexMacroExpandFile(void);
extern const char *LatexMacroExpandName(void);
extern void        LatexMacroKeep(void);

# ifdef __cplusplus
}
# endif
# endif
