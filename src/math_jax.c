/*
$begin math_jax$$
$spell
$$

$section Output MathJax Commands$$

$head Syntax$$
$codei%math_jax(const char* %macro_cmd%, const char* %latex_cmds%)%$$

$head Purpose$$
If the output file is
$cref/htm/Internal2Out/Internal2OutSet/htm/$$,
this routine outputs the latex commands so they will be processed by
MathJax.

$head latex_cmds$$
Is the latex commands. These are all math mode comamnds except for possibly
beginning with $code \[$$ and ending with $code \]$$.
If the latex commands begin and end this way, the math commands
are displayed in Latex display mode.
Otherwise they are displayed in inline mode.

$head macro_cmd$$
This argument must be one of the following:
$code add$$, $code output$$, $code ignore$$, $code clear$$.

$subhead add$$
The
$cref/latex macros/LatexMacro/$$ defined in $icode latex_cmds$$
are added to those that are held for future use.
In this case, $icode latex_cmds$$ must not be $code NULL$$.

$subhead ignore$$
The currently held latex macros are ignored.
In this case, $icode latex_cmds$$ must not be $code NULL$$.

$subhead output$$
The currently held latex macros are
output in MathJax in inline mode.
In this case, $icode latex_cmds$$ should be $code NULL$$.

$subhead clear$$
The currently held
$cref/latex macros/LatexMacro/$$ are cleared; i.e., upon return,
the set of held macros is empty.
This has the side effect of freeing the corresponding memory.
In this case, $icode latex_cmds$$ should be $code NULL$$.

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

static char* next_in_newcommand(char* s, const char* valid)
{	s++;
	while( isspace(*s) )
		s++;
	if( strchr(valid, *s) == NULL ) fatalomh(
		"syntax error in \\newcommand in latex mode",
		NULL
	);
	return s;
}

void math_jax(const char* macro_cmd, const char* latex_cmds)
{	static char *held_macros = NULL;

	bool add      = strcmp(macro_cmd, "add") == 0;
	bool output   = strcmp(macro_cmd, "output") == 0;
	bool ignore   = strcmp(macro_cmd, "ignore") == 0;
	bool clear    = strcmp(macro_cmd, "clear") == 0;
	assert( add || output || ignore || clear );
	//
	if( clear )
	{	assert( latex_cmds == NULL );
		FreeMem( held_macros );
		held_macros = NULL;
		return;
	}
	if( output )
	{	assert( latex_cmds == NULL );
		if( held_macros == NULL )
			return;
		OutputString( Internal2Out("math_jax_begin_inline") );
		OutputString(held_macros);
		OutputString( Internal2Out("math_jax_end_inline") );
		return;
	}
	assert( latex_cmds != NULL );

	// separate copy of latex_cmds
	char* latex_tmp = str_alloc(latex_cmds);

	// skip leading white space
	char* start = latex_tmp;
	while( isspace(*start) )
		start++;

	// skip trailing white space
	char* end = start;
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
	FreeMem(latex_tmp);
	if( add )
	{	// start over with a fresh copy
		latex_tmp = str_alloc(latex_cmds);

		// re-copy deleting comments
		const char* s_cmds = latex_cmds;
		char*       s_tmp  = latex_tmp;
		bool        escape = false;
		while( *s_cmds != '\0' )
		{	if( *s_cmds == '%' && ! escape )
			{	// skip comment
				while( *s_cmds != '\n' && *s_cmds != '\0' )
					s_cmds++;
			}
			else
			{	if( *s_cmds == '\\' )
					escape = ! escape;
				*s_tmp++ = *s_cmds++;
			}
		}
		// search for macros commands
		start       = latex_tmp;
		int n_newcommand = strlen("\\newcommand");
		while( *start != '\0' )
		{	if( strncmp(start, "\\newcommand", n_newcommand) != 0 )
				start++;
			else
			{	end = start + n_newcommand - 1;
				end = next_in_newcommand(end, "{");
				end = next_in_newcommand(end, "\\");
				while( *end != '}' && *end != '\0' )
					end++;
				if( *end != '}' ) fatalomh(
					"syntax error in \\newcommand in latex mode",
					NULL
				);
				end = next_in_newcommand(end, "[{");
				if( *end == '[' )
				{	while( *end != ']' && *end != '\0' )
						end++;
					if( *end != ']' ) fatalomh(
						"syntax error in \\newcommand in latex mode",
						NULL
					);
					end = next_in_newcommand(end, "{");
				}
				int level = 1;
				end++;
				while( level > 0 && *end != '\0' )
				{	if( *end == '{' )
						level++;
					if( *end == '}' )
						level--;
					end++;
				}
				char save_ch = *end;
				*end = '\0';
				if( held_macros == NULL )
					held_macros = str_alloc(start);
				else
				{	s_tmp       = held_macros;
					held_macros = StrCat(
						__FILE__,
						__LINE__,
						held_macros,
						"\n",
						start,
						NULL
					);
					FreeMem(s_tmp);
				}
				*end = save_ch;
				start = end;
			}
		}
		FreeMem(latex_tmp);
	}
	return;
}
