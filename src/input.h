# ifndef INPUT_INCLUDED
# define INPUT_INCLUDED

/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
------------------------------------------------------------------------ */

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
extern const int InputLine(
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
