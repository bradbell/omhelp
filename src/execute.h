# ifndef EXECUTE_INCLUDED
# define EXECUTE_INCLUDED

// BEGIN SHORT COPYRIGHT
/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2004 Bradley M. Bell

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
// END SHORT COPYRIGHT

extern char *ExecuteNextFile(
	void
);
extern void  ExecuteSetFile(
	const char *name, 
	const char *tag
);
extern void  ExecuteWriteFile(
	const char *text
);
extern void  ExecuteFree(
	void
);

/*
$begin execute$$
$spell
	OMhelp
$$

$cindex execute command file$$
$section Managing Execute Command Files$$

$head Description$$
The functions listed below manage the creation
and writing of files created by the OMhelp $code execute$$ command.

$head Memory Allocation$$
When you are finished using the routines listed below,
the routine $mref/ExecuteFree/$$ should be called.
This will free hidden memory allocated for these routines
and avoid a 
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$ error.

$comment
Only include execute.c because routines in that file refer
back to here for the list of all routines in that file
$$

$childtable/
	execute.c/$$


$end

*/

# endif
