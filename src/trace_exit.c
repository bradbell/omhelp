/*
$begin trace_exit$$

$section Routine that Traces Exit Value on Standard Error$$

$table
$bold Syntax$$ $cnext $syntax%void trace_exit(int %status%)%$$
$tend

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
			"OMhelp exiting with status equal to %d.\n", status);
	exit(status);
}
