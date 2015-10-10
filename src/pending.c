/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

# include "pending.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "input.h"
# include "int2str.h"
# include "allocmem.h"
# include "str_alloc.h"

# include "fatalerr.h"
/*

$begin pending$$
$spell
	Omh
	OMhelp
$$

$section Tracking Commands That Can Contain Other Commands Inside$$

$table
$bold Syntax$$ $cend
$syntax/PushPending(/line/, /name/)
PopPending(/line/, /name/)
NumberPending()
OmhPendingError(/line/, /input/)
TexPendingError(/msg/)/$$
$tend

$syntax/PushPending(/line/, /name/)
/$$
This signals the beginning of the specified command
where the integer $italic line$$ is the line number the command appears,
$xref/InputName//InputName()/$$ is the file,
and $italic name$$ is a '\0' terminate character vector
of at most
$codep */
// maximum number of characters in a command name
# define MAX_NAME 20
/* $$
minus one characters long.
$syntax/

PopPending(/line/, /name/)
/$$
This signals the end of the command specified by $italic name$$
(which occurred on line $italic line$$ of the file
$xref/InputName//InputName()/$$) .
It is assumed that commands will end on a last in first out basis.
If this is not the case, an error message is displayed saying that
command $italic name$$ terminated before the expected command.
$syntax/

NumberPending()
/$$
Returns the number of commands that have been pushed by
$code PushPending$$ but not popped by $code PopPending$$.
$syntax/

OmhPendingError(/line/, /input/)
/$$
The value returned by $code NumberPending$$ must be greater
than zero or else it is a programming error to call this routine.
The argument '\0' terminated character vector
$italic input$$ is the OMhelp (latex) input text before which
the pending commands should have been terminated.
The integer $italic line$$ is the line number where $italic input$$
appears.
An error message is printed identifying the command
on top of the stack (most recently pushed command)
that has not been terminated.
Then execution is terminated; i.e., this routine does not return.
$syntax/

TexPendingError(/msg/)
/$$
The value returned by $code NumberPending$$ must be greater
than zero or else it is a programming error to call this routine.
An error message is printed beginning with $italic msg$$
followed by a new line.
The lack of termination of the pending command on the top of the
stack is reported as a possible cause of the error.
Then execution is terminated; i.e., this routine does not return.
$end
-------------------------------------------------------------------------
*/
// maximum number of pending commands at one time
# define MAX_COMMAND     100

// file for each of the pending commands
static char *File[MAX_COMMAND];

// name of the currently pending commands
static char Name[MAX_COMMAND][MAX_NAME];

// input file line number corresponding to each pending command
static int  Line[MAX_COMMAND];

// number of pending commands
static int  Number;


void PushPending(int line, const char *name)
{
	if( Number >= MAX_COMMAND ) fatalerr(
		"More than ",
		int2str(MAX_COMMAND),
		" commands are currently active; i.e.,\n",
		"have not yet been terminated",
		NULL
	);
	assert( strlen(name) < MAX_NAME );

	File[Number] = str_alloc(InputName());
	strcpy(Name[Number], name);
	Line[Number] = line;
	Number++;
}
void PopPending(int line, const char *name)
{
	assert(Number >= 0);

	Number--;
	if(strcmp(name, Name[Number]) != 0) fatalerr(
		"A ",
		name,
		" command terminated at line ",
		int2str(line),
		"\nIt was expected that the ",
		Name[Number],
		" command in line ",
		int2str(Line[Number]),
		" of file\n",
		File[Number],
		" would terminate first",
		NULL
	);
	FreeMem(File[Number]);
}

int NumberPending()
{	return Number; }

void OmhPendingError(int line, const char *input)
{
	assert( Number > 0 );

	fatalomh(
		"At the input text \"",
		input,
		"\" in line ",
		int2str(line),
		"\nThe ",
		Name[Number-1],
		" command in line ",
		int2str(Line[Number-1]),
		" of file\n",
		File[Number-1],
		" was not terminated",
		NULL
	);
}
void TexPendingError(const char *msg)
{
	assert( Number > 0 );

	fataltex(
		msg,
		"\nA possible cause for this error is that the\n",
		Name[Number-1],
		" command in line ",
		int2str(Line[Number-1]),
		" of file\n",
		File[Number-1],
		" was not terminated.",
		NULL
	);
}
