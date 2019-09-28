# ifndef EXECUTE_INCLUDED
# define EXECUTE_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


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
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$ error.

$comment
Only include execute.c because routines in that file refer
back to here for the list of all routines in that file
$$

$childtable%
	src/execute.c%$$


$end

*/

# ifdef __cplusplus
}
# endif
# endif
