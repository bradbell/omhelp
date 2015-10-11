/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin trace_exit$$
$spell
	OMhelp
$$

$section Routine that Traces Exit Value on Standard Error$$

$head Syntax$$ $codei%void trace_exit(int %status%)%$$


$head Purpose$$
At a global level (for the entire OMhelp program)
the exit status can be optionally traced by using this routine to call exit.
After deciding if tracing or not, exit is called with the specified
status.


$end
*/
# include "trace_exit.h"
# include <stdio.h>
# include <stdlib.h>
void trace_exit(int status)
{
	if( status != 0 ) fprintf(stdout,
			"\nOMhelp exiting with status equal to %d.\n", status);
	exit(status);
}
