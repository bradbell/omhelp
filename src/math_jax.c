/*
$begin math_jax$$
$spell
$$

$section Output MathJax Commands$$

$head Syntax$$
$codei%math_jax(const char* latex_commands)%$$

$head Purpose$$
If the output file is
$cref/htm/Internal2Out/Internal2OutSet/htm/$$,
this routine outputs the latex commands so they will be processed by
MathJax.

$latex_commands$$
Is the latex commands. These are all math mode comamnds except for possibly
beginning with $code \[$$ and ending with $code \]$$.
If the latex commands begin and end this way, the math commands
are displayed in Latex display mode.
Otherwise they are displayed in inline mode.

$end
*/
# include <ctype.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "math_jax.h"
# include "str_alloc.h"
# include "fatalerr.h"
# include "output.h"
# include "Internal2Out.h"
# include "allocmem.h"
void math_jax(const char* latex_commands)
{
	// separate copy of latex_commands
	char *commands = str_alloc(latex_commands);

	// skip leading white space
	char *start = commands;
	while( isspace(*start) )
		start++;

	// skip trailing white space
	char *end = start;
	while( *end != '\0' )
		end++;
	while( start < end && isspace(*(end-1)) )
		end--;
	*end = '\0';

	// determine if begins with \[
	bool display_mode = strncmp(start, "\\[", 2) == 0;
	if( display_mode )
	{	assert( start <= end-2 );
		if( ! strncmp(end-2, "\\]", 2) == 0 )
		{	fatalomh(
			"$latex command begins with \\[ but does not end with \\]",
			NULL
			);
		}
		start      = start + 2;
		*(end - 2) = '\0';
		OutputString( Internal2Out("math_jax_begin_display") );
		OutputString(start);
		OutputString( Internal2Out("math_jax_end_display") );
	}
	else
	{	OutputString( Internal2Out("math_jax_begin_inline") );
		OutputString(start);
		OutputString( Internal2Out("math_jax_end_inline") );
	}
	FreeMem(commands);
	return;
}
