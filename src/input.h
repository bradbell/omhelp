# ifndef INPUT_INCLUDED
# define INPUT_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

extern void  InputAddPath(
	const char *path,
	const char *ext
);
extern void  InputFree(
	void
);
extern char  InputGet(
	void
);
extern int InputLine(
	void
);
extern void InputInit(
	const char *directory
);
extern const char *InputName(
	void
);
extern void  InputPush(
	const char *root,
	const char *ext,
	const int nspace
);
extern void  InputPop(
	void
);
extern const char *InputSearch(
	const char *root,
	const char *ext
);
extern void  InputSplitName(
	char **proot,
	char **pext,
	const char *filename
);

/*
$begin input$$
$escape #$$

$cindex set input path #and read file$$

$section Setting Input Paths and Reading Input Files$$

$head Description$$
The functions listed below manage the reading of input files.

$head Memory Allocation$$
When you are finished using the routines listed below,
the routine $mref/InputFree/$$ should be called.
This will free hidden memory allocated for these routines
and avoid a
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$ error.

$comment
Only include include.c because routines in that file refer
back to here for the list of all routines in that file
$$

$childtable/
	input.c/$$

$end
*/

# endif
