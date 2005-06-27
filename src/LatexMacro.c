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
/*
-----------------------------------------------------------------------------
$begin LatexMacroUserInput$$
$spell
	const
	ntoken
$$

$section Set Input Characters For Latex Macro Preprocessor$$

$table
$bold Syntax$$
$cend $syntax%void LatexMacroUserInput(int %line%, const char *%input%)%$$ 
$tend

$fend 20$$

$head Description$$
The Latex macro preprocessor reads its data from memory.
This call sets the input data to the '\0' terminated
character vector specified by $italic input$$.
The integer $italic line$$ specifies the line
number in the file $xref/InputName//InputName()/$$
where $italic input$$ started.

$head Memory Allocation$$
This call allocates memory using $xref/AllocMem/$$
and this memory is freed by $xref/LatexMacroFree/$$.

$end
-----------------------------------------------------------------------------
$begin LatexMacroFree$$
$spell
	Ch
$$

$table
$bold Syntax$$
$cend $syntax%void LatexMacroFree()%$$
$tend

$section Free Memory Allocated By Latex Macro Preprocessor$$

$head Description$$
This routine deletes all of the macros defined
since the previous call to
$xref LatexMacroKeep$$.
It also erases the information passed to the macro preprocessor
by the previous call to $xref LatexMacroUserInput$$.
$pre

$$
You can free all the macro memory using the sequence of calls
$syntax%
	LatexMacroFree();
	LatexMacroFree();
%$$
which should be called after you are done using the preprocessor;
i.e., any of the routines in the following list:
$xref LatexMacroUserInput$$,
$xref LatexMacroGetCh$$,
$xref LatexMacroInputLine$$,
$xref LatexMacroInputFile$$,
$xref LatexMacroExpandInput$$,
$xref LatexMacroExpandLine$$,
and
$xref LatexMacroExpandFile$$.


$end
-----------------------------------------------------------------------------
$begin LatexMacroGetCh$$
$spell
	Ch
$$

$section Get the Next Input Character With Latex Macro Expansion$$

$table
$bold Syntax$$
$cnext $syntax%char LatexMacroGetCh()%$$
$tend

$head Description$$
Gets the next character after the input specified by
$xref LatexMacroUserInput$$
has been run through the Latex macro preprocessor.

If there is no more input or
if no call has yet been made to $code LatexMacroUserInput$$,
the value '\001' is returned.


$end
-----------------------------------------------------------------------------
$begin LatexMacroInputLine$$

$section Determine the Current User Input Line Number$$

$table
$bold Syntax$$
$cnext $syntax%int LatexMacroInputLine()%$$
$tend

$head Description$$
Returns the line number corresponding to the next 
character returned by $xref LatexMacroGetCh$$ 
(not counting macro expansion).
This line number corresponds to the file specified 
by the previous call to $xref LatexMacroUserInput$$.

If no call has been made to $code LatexMacroUserInput$$,
the value zero is returned.

$end
-----------------------------------------------------------------------------
$begin LatexMacroInputFile$$
$spell
	const
$$

$section Determine the Current User Input File$$

$table
$bold Syntax$$
$cnext $syntax%const char *LatexMacroInputFile()%$$
$tend

$head Description$$
Returns the file name corresponding to the previous call to
$xref LatexMacroUserInput$$. 

If no call has been made to $code LatexMacroUserInput$$,
the value "NONE" is returned.

$end
-----------------------------------------------------------------------------
$begin LatexMacroExpandInput$$
$spell
	const
$$

$section Determine the Current Latex Macro Expansion$$

$table
$bold Syntax$$
$cnext $syntax%const char *LatexMacroExpandInput()%$$
$tend

$head Description$$
Returns the current macro expansion that corresponds to the next character
returned by $xref LatexMacroGetCh$$.

If the next character will come from user input instead of a macro
expansion, the return value of $code LatexMacroExpandInput$$ is $code NULL$$.


If no call has been made to $code LatexMacroUserInput$$,
the value $code NULL$$ is returned.
$end
-----------------------------------------------------------------------------
$begin LatexMacroExpandLine$$

$section Line Where the Currently Expanded Latex Macro is Defined$$

$table
$bold Syntax$$
$cnext $syntax%int LatexMacroExpandLine()%$$
$tend

$head Description$$
Returns the line number where the currently expanded macro is defined.
This is useful for error reporting.

$head Restrictions$$
It a programming  error to call this routine if the return value of 
$xref LatexMacroExpandInput$$ is $code NULL$$.

$end
-----------------------------------------------------------------------------
$begin LatexMacroExpandFile$$
$spell
	const
$$

$section File Where the Currently Expanded Latex Macro is Defined$$

$table
$bold Syntax$$
$cnext $syntax%const char *LatexMacroExpandFile()%$$
$tend

$head Description$$
Returns the file where the currently expanded macro is defined.
This is useful for error reporting.

$head Restrictions$$
It a programming  error to call this routine if the return value of 
$xref LatexMacroExpandInput$$ is $code NULL$$.

$end

-----------------------------------------------------------------------------
$begin LatexMacroExpandName$$
$spell
	const
$$

$section Name of the Currently Expanded Latex Macro$$

$table
$bold Syntax$$
$cnext $syntax%const char *LatexMacroExpandName()%$$
$tend

$head Description$$
Returns the name of the currently expanded macro.
This is useful for error reporting.

$head Restrictions$$
It a programming  error to call this routine if the return value of 
$xref LatexMacroExpandInput$$ is $code NULL$$.

$end

-----------------------------------------------------------------------------
$begin LatexMacroKeep$$

$mindex keep macro$$
$section Keep The Currently Defined Latex Macros$$

$table
$bold Syntax$$
$cnext $syntax%void LatexMacroKeep()%$$
$tend

$head Description$$
Macros are defined in order as they appear in the input stream.
Using $code LatexMacroKeep$$ enables
one to remove
the macro definitions that are local to a particular part
section.
This can be done by calling $code LatexMacroKeep$$ before
processing a section and $xref LatexMacroFree$$ after.

$end
*/

# include "BinarySearch.h"
# include "input.h"
# include "allocmem.h"
# include "str_alloc.h"
# include "int2str.h"
# include "fatalerr.h"

# include <string.h>
# include <assert.h>
# include <ctype.h>

// Prerocessor Definitions  =================================================

# define MAX_DEFINE   1000
# define MAX_LENGTH   500

// Data Only Used In This File ==============================================

// line number and file where user input occurs
int   UserLine  = 0; 
char *UserFile  = NULL;

// actual users input and index of next input character
static char   *UserInput = NULL;
static int    UserIndex = 0;

// was previous user input character the beginning of an escape sequence
static int  UserEscape = 0;

// current macro expansion
static int  ExpandDefine;     
static int  ExpandIndex  = 0;
static char *ExpandInput  = NULL;

// number of macros defined so far (must be <= MAX_DEFINE
static int Ndefine = 0;

// definition of a macro
typedef struct definition {
	char *file;  // file that the macro definition appears in
	int   line;  // line that the macro definition starts in
	char *name;  // name of the macro
	int   narg;  // number of arguments that the macro has
	int   nrep;  // number of argument replacements macro has
	char **text; // text that is placed around each of the replacements
	int  *iarg;  // arguments that is placed between text 

} Definition;

// set of macro defintions so far
static Definition Define[MAX_DEFINE];

// alphabetic order of the macros; i.e. , for i = 1 , ..., Ndefine-1
// DefineName[i] = Define[DefineIndex[i]].name
// DefineName[i] > Name[i-1]  
static const char *DefineName[MAX_DEFINE];
static int         DefineIndex[MAX_DEFINE];

// currently kept macros
static int Nkeep = 0;
static const char *KeepName[MAX_DEFINE];
static int         KeepIndex[MAX_DEFINE];

// Functions Only Used In This File =======================================

// get next user character
static char UserGetCh()
{	char ch;

	if( UserInput == NULL )
		return '\001';

	assert( ( (unsigned int) UserIndex ) <= strlen(UserInput) );
	ch = UserInput[UserIndex];

	// skip comments
	if( (ch == '%') & (! UserEscape) )
	{	while( (ch != '\n') & (ch != '\0') )
		{	++UserIndex;
			ch = UserInput[UserIndex];
		}
	}

	if( ch == '\0' )
		return '\001';

	if( ch == '\n' )
		++UserLine;

	if( UserEscape )
		UserEscape = 0;
	else	UserEscape = ch == '\\';

	++UserIndex;
	return ch;
}

// skip white space 
static char SkipUserWhite()
{	char ch;

	ch = UserGetCh();
	while( isspace(ch) )
		ch = UserGetCh();

	return ch;
}

// check length of macro definition
static void CheckDefineLength(int startLine, int startIndex)
{	if( UserIndex - startIndex >= MAX_LENGTH - 1 ) fataltex(
		"In the macro definition that starts ",
		"with the \\newcommand\nin line ",
		int2str(startLine),
		"\nDefinition is over ",
		int2str(MAX_LENGTH-1),
		" characters long.",
		"\nPerhaps a '}' is missing.",
		NULL
	);
	return;
}

/*
{ \<name> } { <text[0]> }
{ \<name> } [ <narg> ] { <text[0]> #<number> <text[1]> #<number> ... }
*/
static void DefineLatexMacro()
{
	Definition *macro;
	char       ch;
	char       buffer[MAX_LENGTH];
	char       token[MAX_LENGTH];
	int        i;
	int        j;
	int        count;
	int        startLine;
	int        startIndex;
	int        match;
	int        escape;

	// starting line number for this macro definition
	startLine  = UserLine;

	// starting character index for this macro definition
	startIndex = UserIndex;

	// macro we are defining
	macro = Define + Ndefine;

	// file and line for this macro definition
	macro->file = str_alloc(UserFile);
	macro->line = UserLine;

	/*
	Determine macro->name
	*/
	ch = SkipUserWhite();
	CheckDefineLength(startLine, startIndex);

	if( ch != '{' ) fataltex(
		"In the macro definition that starts ",
		"with the \\newcommand\nin line ",
		int2str(startLine),
		"\nExpected '{' and then '\\' to follow \\newcommand.",
		NULL
	);

	ch = SkipUserWhite();
	CheckDefineLength(startLine, startIndex);

	if( ch != '\\' ) fataltex(
		"In the macro definition that starts ",
		"with the \\newcommand\nin line ",
		int2str(startLine),
		"\nExpected '{' and then '\\' to follow \\newcommand.",
		NULL
	);
	i  = 0;
	ch = UserGetCh();
	while( isalpha(ch) )
	{	token[i] = ch;
		i++;

		ch      = UserGetCh();
		CheckDefineLength(startLine, startIndex);
	}
	token[i] = '\0';
	macro->name = str_alloc(token);
	if( strcmp(token, "newcommand") == 0 ) fataltex(
		"In the macro definition that starts ",
		"with the \\newcommand\nin line ",
		int2str(startLine),
		"\nAttempt to define a macro named newcommand.",
		NULL
	);

	if( ch != '}' ) fataltex(
		"In the macro definition that starts ",
		"with the \\newcommand\nin line ",
		int2str(startLine),
		"\nExpected '}' to follow \\",
		macro->name,
		NULL
	);

	/*
	Determine macro->narg
	*/
	ch = SkipUserWhite();
	CheckDefineLength(startLine, startIndex);
	if( ch == '[' )
	{	// determine the number of arguments
		macro->narg = 0;
		ch          = SkipUserWhite();
		CheckDefineLength(startLine, startIndex);
		while ( ch != ']' )
		{	if( (ch < '0') | ('9' < ch) ) fataltex(
				"In the macro definition that starts ",
				"with the \\newcommand\nin line ",
				int2str(startLine),
				"\nInvalid syntax for the number of arguments",
				NULL
			);
			macro->narg = macro->narg * 10 + (ch - '0');

			ch = SkipUserWhite();
			CheckDefineLength(startLine, startIndex);
		}
		if( (macro->narg < 1) | (macro->narg > 9) ) fataltex(
			"In the macro definition that starts ",
			"with the \\newcommand\nin line ",
			int2str(startLine),
			"\nThe number of arguments ",
			int2str(macro->narg),
			"\nis not between 0 and 9.",
			NULL
		);
		ch = SkipUserWhite();
		CheckDefineLength(startLine, startIndex);

		if( ch != '{' ) fataltex(
			"In the macro definition that starts ",
			"with the \\newcommand\nin line ",
			int2str(startLine),
			"\nThe character '{' should follow the character ']'\n",
			"that terminates the specificaiton of the number of\n",
			"arguments.",
			NULL
		);
	}
	else if ( ch == '{' )
	{	// there are no arguments to this macro
		macro->narg = 0;
	}
	else fataltex(
		"In the macro definition that starts ",
		"with the \\newcommand\nin line ",
		int2str(startLine),
		"\nThe definition of the macro ",
		macro->name,
		"\ndoes not start with the '[' or '{' character.",
		NULL
	);

	assert( ch == '{' );
	/*
	store the rest of the macro definition characters in buffer
	*/
	i     = 0;    // index in the buffer
	count = 1;    // number of left braces minus number of right braces
	while( count > 0 )
	{	ch        = UserGetCh();
		if( ch == '\001' ) fataltex(
			"In definition of the macro that starts in line ",
			int2str(startLine),
			"\nof the file ",
			UserFile,
			"\nThere is a '{' with out a matching '}'",
			NULL
		);

		if(ch == '{')
			++count;
		if(ch == '}')
			--count;

		if( count > 0 )
		{	CheckDefineLength(startLine, startIndex);

			buffer[i] = ch;
			i++;
		}
	}
	buffer[i] = '\0';

	// count the number of # characters in the macro definition
	i      = 0;
	count  = 0;
	escape = 0;
	while( buffer[i] != '\0' )
	{	if( escape )
			escape = 0;
		else if(buffer[i] == '#')
			++count;

		escape   = (buffer[i] == '\\');

		i++;
	}

	/*
	Determine value of the macro->text and macro->iarg arrays
	*/
	macro->nrep = count;
	macro->text = (char **) AllocMem(count+1, sizeof(char *));
	macro->iarg = (int *) AllocMem(count, sizeof(int));
	i      = 0;
	count  = 0;
	escape = 0;
	while( buffer[i] != '\0' )
	{	
		// determine macro->text[count]
		j = 0;
		while( (escape | (buffer[i] != '#')) & (buffer[i] != '\0') )
		{	token[j] = buffer[i];
			escape   = (buffer[i] == '\\');
			j++;
			i++;
		}
		token[j] = '\0';

		assert( count < macro->nrep + 1);
		macro->text[count] = str_alloc(token);

		// determine macro->iarg[count]
		if( buffer[i] == '#' )
		{	++i;
			ch = buffer[i];
			j  = 0;
			while( ('0' <= ch ) & (ch <= '9') ) 
			{	j = j * 10 + (ch - '0');
				++i;
				ch = buffer[i];
			}
			if( (j < 1) | (macro->narg < j) ) fataltex(
				"In definition of the macro that starts ",
				"in line ",
				int2str(startLine),
				"\nof the file ",
				UserFile,
				"\nThe macro argument number ",
				int2str(j),
				"\nis not with in the specified limits.",
				NULL
			);
			assert( count < macro->nrep );
			macro->iarg[count] = j;

			count++;
		}
	}
	assert( count == macro->nrep );

	// determine the position of the new macro in the ordered list
	i     = 0;
	match = Ndefine;
	while(i < Ndefine )
	{	if(strcmp(macro->name, DefineName[i]) <= 0)
		{	match = i;
			i     = Ndefine;
		}
		else	++i;
	}
	if( match < Ndefine )
	{	if( strcmp(macro->name, DefineName[match]) == 0 ) fataltex(
			"In the macro definition that starts\n",
			"with the \\newcommand in line ",
			int2str(startLine),
			"\nA macro named \\",
			macro->name,
			" was perviously defined\n",
			"in line ",
			int2str( Define[DefineIndex[i]].line ),
			" of the file ",
			Define[DefineIndex[i]].file,
			NULL
		);
	}

	// place the new macro in the ordered list
	i = Ndefine;
	while( i > match )
	{	DefineIndex[i] = DefineIndex[i-1];
		DefineName[i]  = DefineName[i-1];
		--i;
	}
	DefineIndex[match] = Ndefine;
	DefineName[match]  = macro->name;

	++Ndefine;

	return;
}


/*
{ <arg[1]> } { <arg[2]> } ... { <arg[Define[index].narg]> }
*/
void ExpandLatexMacro(int index)
{	Definition      *macro;
	char                ch;
	int                  i;
	int                  j;
	char              *tmp;
	int              count;
	int          startLine;

	char arg[9][MAX_LENGTH];

	assert( ExpandInput == NULL );

	ExpandDefine = index;
	ExpandIndex  = 0;
	macro        = Define + index;

	startLine   = UserLine;
	for(i = 0; i < macro->narg; i++)
	{	assert( i < 9 );
		// place this macro argument in arg

		ch    = SkipUserWhite();
		if( ch != '{' ) fataltex(
			"In the macro expansion that starts ",
			"with the \\",
			macro->name,
			"\nin in line ",
			int2str(startLine),
			"\nwhich is defined in line ",
			int2str(macro->line),
			" of the file ",
			macro->file,
			"\nExpected the character '{' before argument number ",
			int2str(i + 1),
			NULL
		);
		count = 1;
		j     = 0;
		while( count > 0 )
		{	ch = UserGetCh();
			if( ch == '{' )
				count++;
			if( ch == '}' )
				count--;

			if( j >= MAX_LENGTH-1 ) fataltex(
				"In the macro expansion that starts ",
				"with the \\",
				macro->name,
				"\nin in line ",
				int2str(startLine),
				"\nwhich is defined in line ",
				int2str(macro->line),
				" of the file ",
				macro->file,
				"\nArgument number ",
				int2str(i + 1),
				" is to long\n",
				"Perhaps a '}' is missing.",
				NULL
			);
			if( count > 0 )
			{	arg[i][j] = ch;
				++j;
			}
		}
		arg[i][j] = '\0';
	}

	ExpandInput = str_alloc( macro->text[0] );
	for(j = 0; j < macro->nrep; j++)
	{	// macro argument for this replacement
		i = macro->iarg[j] - 1;
	
		tmp         = ExpandInput;
		ExpandInput = StrCat(
			__FILE__,
			__LINE__,
			tmp,
			arg[i],
			macro->text[j+1],
			NULL
		);
		FreeMem(tmp);
	}
	return;
}

// Functions Used External From This File ===============================

void LatexMacroUserInput(int line, const char *input)
{	
	assert( ExpandInput == NULL );

	FreeMem(UserFile);
	UserFile  = str_alloc(InputName());

	FreeMem(UserInput);
	UserInput = str_alloc(input);


	UserLine  = line;
	UserIndex = 0;

	return;
}

void LatexMacroFree()
{	Definition *macro;
	int i;

	while( Ndefine > Nkeep )
	{	--Ndefine;

		macro = Define + Ndefine;
		FreeMem(macro->file);
		FreeMem(macro->name);
		FreeMem(macro->iarg);
		for(i = 0; i <= macro->nrep; i++)
			FreeMem(macro->text[i]);
		FreeMem(macro->text);

	}

	FreeMem(UserInput);
		UserInput = NULL;

	FreeMem(UserFile);
		UserFile  = NULL;

	i = Nkeep;
	while(i)
	{	--i;
	
		DefineName[i]  = KeepName[i];
		DefineIndex[i] = KeepIndex[i];
	}

	Nkeep = 0;

	return;
}

// get next combination of user input and macro expansion
char LatexMacroGetCh()
{	char ch;
	int  startIndex;
	char token[MAX_LENGTH];
	int  i;

	if( UserFile == NULL )
		return '\001';

	if( ExpandInput != NULL )
	{	if( ExpandInput[ExpandIndex] == '\0' )
		{	FreeMem(ExpandInput);
			ExpandInput = NULL;
		}
	}

	if( ExpandInput != NULL )
	{	assert( (unsigned int) ExpandIndex < strlen(ExpandInput) );
		ch = ExpandInput[ExpandIndex++];
	}
	else
	{	ch = UserGetCh();

		if( UserEscape )
		{	startIndex = UserIndex;

			ch         = UserGetCh();
			i          = 0;
			while( isalpha(ch) )
			{	if( i < MAX_LENGTH )
					token[i++] = ch;
				ch        = UserGetCh();
			}
			// undo get of character that was not a letter 
			if( ch != '\001' )
				--UserIndex;

			// terminame the token
			if( i < MAX_LENGTH )
				token[i] = '\0';
			else	token[MAX_LENGTH-1] = '\0';

			// see if it is a macro
			i = BinarySearch(DefineName, Ndefine, token);

			if( i < Ndefine )
			{	ExpandLatexMacro(DefineIndex[i]);
				ch = LatexMacroGetCh();
			}
			else if( strcmp(token, "newcommand") == 0 )
			{	DefineLatexMacro();
				ch = UserGetCh();
			}
			else
			{	UserIndex = startIndex;
				ch = '\\';
				UserEscape = 1;
			}
		}		
	}

	return ch;
}

int LatexMacroInputLine()
{	if( UserFile == NULL )
		return 0;

	return UserLine; 
}

const char *LatexMacroInputFile()
{	if( UserFile == NULL )
		return "NONE";

	return UserFile; 
}

const char *LatexMacroExpandInput()
{	if( UserFile == NULL )
		return NULL;

	return ExpandInput; 
}

int LatexMacroExpandLine()
{	assert( ExpandInput != NULL );

	return Define[ExpandDefine].line;
}	

const char *LatexMacroExpandFile()
{	assert( ExpandInput != NULL );

	return Define[ExpandDefine].file;
}	

const char *LatexMacroExpandName()
{	assert( ExpandInput != NULL );

	return Define[ExpandDefine].name;
}	

void LatexMacroKeep()
{	int i;

	Nkeep = Ndefine;
	i     = Nkeep;
	while(i)
	{	--i;
		KeepName[i] = DefineName[i];
		KeepIndex[i] = DefineIndex[i];
	}

	
	return;
}
