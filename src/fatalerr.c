/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin fatalerr_dev$$
$spell
	fatalerr
	fatalomh
	fataltex
	OMhelp
	myfile
$$

$section Fatal Error Handler$$

$index error, terminating execution on$$
$index terminating, execution on error$$
$index execution, terminating on error$$
$index fatal, error$$

$head Syntax$$
$codei%fatalerr(char *%s1%, %...%)
%$$
$codei%fatalomh(char *%s1%, %...%)
%$$
$codei%fataltex(char *%s1%, %...%)%$$


$head Message$$
The arguments
$codei%
	%s1%, %...%
%$$
The last argument is a $code NULL$$
and all the other arguments are
'\0' terminated character vectors.
We refer to the string that consists
of all the arguments in order,
with not extra formatting between them, as the $icode Message$$.

$head File$$
We refer to the value of $code InputName()$$ as the $icode File$$.

$head fatalerr$$
$index fatalerr$$
If $icode File$$ is "NONE", the line of text
$codep
	OMhelp Error:
$$
is printed on standard output followed by the $icode Message$$.
Otherwise
$codei/
	OMhelp Error: in file /File/:
/$$
is printed on standard output followed by the $icode Message$$.

$head fatalomh$$
$index fatalomh$$
The $icode File$$ must not be "NONE"; i.e., there must
be a current input file.
The text
$codei/
	OMhelp Error: in file /File/:
/$$
is printed on standard output followed by the $icode Message$$.
After $icode Message$$, and starting with a new line,
a line number is reported.
This is where the next input token (after the error) would start; i.e.,
the current value of $cref/InputLine()/InputLine_dev/$$.
$pre

$$
All occurrences of the character $code @$$ in the error message
are converted to the current
$cref/command key character/CommandKeyCharacter_dev/$$ before being output.

$head fataltex$$
$index fataltex$$
The $icode File$$ must not be "NONE"; i.e., there must
be a current input file.
The text
$codei/
	OMhelp Error: Latex in file /File/:
/$$
is printed on standard output followed by the $icode Message$$.
Extra information is printed after $icode Message$$,
and starting with a new line.
This extra information includes the most recent input tokens
to the Latex parser and the line number where they started.
If the current input tokens are coming from a macro expansion,
the macro expansion is also included.

$end
---------------------------------------------------------------------------
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// declare the CommandKeyCharacter function
# include "lexomh.h"

// declaration of this function
# include "fatalerr.h"

// variable argument list as per Section B7 of the second edition of
// The C programming language by Kernighan and Ritchie
# include <stdarg.h>

// functions that keep track of input files
# include "input.h"

// functions that keep track of macro expansions
# include "LatexMacro.h"

// returns history of Latex input tokens
# include "LatexLexHistory.h"

// allocates memory
# include "allocmem.h"

// programming error assertions
# include <assert.h>

// optional printing of exit status
# include "trace_exit.h"

void fatalerr(const char *s1, ...)
{
	// next argument
	const char *s = s1;


	// pointer to the argument list
	va_list argList;

	// initialize the argument list
	va_start(argList, s1);

	// initialize error message
	if( strcmp(InputName(), "NONE") == 0 )
		printf( "\nOMhelp Error:\n");
	else	printf(
		"\nOMhelp Error: in file %s:\n",
		InputName()
	);


	// print the arguments
	while(s != NULL )
	{	printf("%s", s);
		s = va_arg(argList, const char *);
	}

	trace_exit(1);
}

void fatalomh(const char *s1, ...)
{
	// next argument
	const char *s = s1;

	// pointer to the argument list
	va_list argList;

	// initialize the argument list
	va_start(argList, s1);

	// initialize error message
	assert( strcmp(InputName(), "NONE") != 0 );
	if( strcmp(InputName(), "NONE") == 0 )
		printf("\nOMhelp input error with no current input file ?\n");
	else	printf(
		"\nOMhelp Error: in file %s:\n",
		InputName()
	);

	// print the arguments
	while(s != NULL )
	{	int i = 0;
		while( s[i] != '\0' )
		{	if( s[i] == '$' )
				putchar( GetCommandKeyCharacter() );
			else	putchar( s[i] );
			i++;
		}
		s = va_arg(argList, const char *);
	}

	// print input file identification
	if( strcmp(InputName(), "NONE") != 0 ) printf(
		"\nError occurred in or before line %d.\n",
		InputLine()
	);

	trace_exit(1);
}


# define MAX_NUMBER	10
# define MAX_LENGTH	100

void fataltex(const char *s1, ...)
{
	int    line[MAX_NUMBER];
	char *token[MAX_NUMBER];
	const char      *expand;

	int number;
	int  i;

	// next argument
	const char *s = s1;

	// pointer to the argument list
	va_list argList;

	// initialize the argument list
	va_start(argList, s1);


	// initialize error message
	assert( strcmp(LatexMacroInputFile(), "NONE") != 0 );
	if( strcmp(LatexMacroInputFile(), "NONE") == 0 )
		printf("\nLatex error with no current input file ?\n");
	else	printf(
		"\nOMhelp Latex Error at line %d in file\n%s\n",
		LatexMacroInputLine(),
		LatexMacroInputFile()
	);


	// print the arguments
	while(s != NULL )
	{	printf("%s", s);
		s = va_arg(argList, const char *);
	}

	// allocate memory for tex tokens
	for(i = 0; i < MAX_NUMBER; i++)
		token[i] = AllocMem(MAX_LENGTH, sizeof(char));

	number = LatexLexHistory(MAX_NUMBER, MAX_LENGTH, line, token);

	if( number > 1 )
		printf("\n\nPrevious Latex input tokens are\n");
	else if( number == 1 )
		printf("\nPrevious Latex input token is ");
	else	printf("\nError occurred in next token after $latex command.");
	for(i = 1; i <= number; i++)
	{	printf(" %s", token[number - i] );
		FreeMem( token[number - i] );
	}

	// print input file identification
	if( strcmp(InputName(), "NONE") != 0 )
	{	if( number > 1 ) printf(
			"\nThe first token occurred in line %d.\n",
			line[number - 1]
		);
		else if( number == 1 ) printf(
			"\nThis token occurred in line %d.\n",
			line[number - 1]
		);
		else	printf(
			"\nThe $latex command is in or before line %d.\n",
			InputLine()
		);
	}

	// check for an active macro expansions
	expand = LatexMacroExpandInput();
	if( expand != NULL ) printf("\n%s", expand);

	trace_exit(1);
}
