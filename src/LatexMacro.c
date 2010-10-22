/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2010 Bradley M. Bell

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

$section Return Curerent Expansion for All Active Latex Macros$$

$head Syntax$$
$code char* LatexMacroExpandInput()$$

$head Details$$
If the previous two characters came from file input instead of a macro
expansion, the return value of $code LatexMacroExpandInput$$ is $code NULL$$.
Otherwise,
each macro expansion is identified by the macro name, and its 
expansion value,
up to the current point in the expansion (where input is currently 
being taken from).
If the current input point corresponds to a macro,
then the expansion of that macro is included.

$head Memory Allocation$$
The return value is memory that was allocated with $cref AllocMem$$
and should be freed using the routine $cref/FreeMem/AllocMem/FreeMem/$$
(or used for a fatal error message).

$head Input File$$
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
------------------------------------------------------------------------\
$begin LatexMacroPopFullyExpandedInput$$

$section Remove Fully Expanded Latex Macros and Fee Corresponding Memory$$

The fully expanded latex macros's are kept around for one extra 
input character.
This help error message when an error is detected at the end of a macro.
In the case where there are no more latex commands after the end
of the last macro in the OMhelp input, there can be 
$cref AllocMem$$ left over for this purpose that must be freed
before checking for memory leaks.
This function will free that memory.

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

# define MAX_DEFINE   1000 // maximum number of latex macros defined
# define MAX_LENGTH   500  // maximum lenght of a macro
# define MAX_EXPAND   30   // will be increased when recursion is completed

// Data Only Used In This File ==============================================

// line number and file where user input occurs
int   UserLine  = 0; 
char *UserFile  = NULL;

// actual users input and index of next input character
static char   *UserInput = NULL;
static int    UserIndex = 0;

// was previous user input character the beginning of an escape sequence
static int  UserEscape = 0;

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


// Information for one macro expansion
typedef struct macro_expansion {
	Definition *macro; // definition for this macro in the macro Define array
	int    text_index; // index of the next character in this expansion 
	char*        text; // current macro expansion 
} MacroExpansion;

// number of macros currently expanded
static int NumExpandInput = 0;

// Expansion for each of the macros
// For i > 0, ExpandInput[i] comes from a macro in ExpandInput[i-1]
// For i == 0, ExpandInput[i] comes from a macro in current input file.
static MacroExpansion ExpandInput[MAX_EXPAND]; 

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

// skip user space 
static char SkipUserWhite()
{	char ch;

	ch = UserGetCh();
	while( isspace((int) ch) )
		ch = UserGetCh();

	return ch;
}

// skip latex space 
static char SkipLatexWhite()
{	char ch;
	extern char LatexMacroGetCh(void);

	ch = LatexMacroGetCh();
	while( isspace((int) ch) )
		ch = LatexMacroGetCh();

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
	while( isalpha((int) ch) )
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
	macro->iarg = (int *) AllocMem(count, sizeof(int));
	macro->text = (char **) AllocMem(count+1, sizeof(char *));
	macro->text[count] = NULL;
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
	// check for case where no characters follow the last replacement number
	if( macro->text[count] == NULL )
		macro->text[count] = str_alloc("");

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
	int                  i, j, k;
	char              *tmp, *expansion;
	int              count, startLine;

	char arg[9][MAX_LENGTH];
	extern char LatexMacroGetCh(void);

	macro       = Define + index;
	startLine   = UserLine;
	for(i = 0; i < macro->narg; i++)
	{	assert( i < 9 );
		// place this macro argument in arg

		ch    = SkipLatexWhite();
		if( ch != '{' ) fataltex(
			"In expansion of macro \\",
			macro->name,
			"\nExpected the character '{' before argument number ",
			int2str(i + 1),
			NULL
		);
		count = 1;
		j     = 0;
		while( count > 0 )
		{	ch = LatexMacroGetCh();
			if( ch == '{' )
				count++;
			if( ch == '}' )
				count--;

			if( j >= MAX_LENGTH-1 ) fataltex(
				"In expansion of macro \\",
				macro->name,
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

	expansion = str_alloc( macro->text[0] );
	for(j = 0; j < macro->nrep; j++)
	{	// macro argument for this replacement
		i = macro->iarg[j] - 1;
	
		tmp         = expansion;
		expansion   = StrCat(
			__FILE__,
			__LINE__,
			tmp,
			arg[i],
			macro->text[j+1],
			NULL
		);
		FreeMem(tmp);
	}

	// later change this assert to a fatal error message about recursion
	// is too deep
	if( NumExpandInput >= MAX_EXPAND ) fataltex(
		"Too many macros currently expanded, cannot expand macro \\",
		macro->name,
		NULL
	);
	k                         = NumExpandInput;
	ExpandInput[k].macro      = macro;
	ExpandInput[k].text       = expansion;
	ExpandInput[k].text_index = 0;
	NumExpandInput++;
	return;
}

static char *MacroExpansionMessage(void)
{	int   i, j;
	char ch;
	char *this = NULL, *all = NULL, *tmp = NULL;

	for(i = 0; i < NumExpandInput; i++)
	{	
		j  = ExpandInput[i].text_index;
		ch = ExpandInput[i].text[j];
		ExpandInput[i].text[j] = '\0';
		tmp  = int2str(ExpandInput[i].macro->line);
		this = StrCat(
			__FILE__,
			__LINE__,
			"The macro \"",
			ExpandInput[i].macro->name,
			"\" is defined at line ",
			tmp,
			" of ",
			ExpandInput[i].macro->file,
			"\nIt's current expansion is:\n\t",
			ExpandInput[i].text,
			"\n",
			NULL
		);
		FreeMem(tmp);
		ExpandInput[i].text[j] = ch;
		//
		if(i == 0 )
			all = this;
		else
		{	tmp = StrCat(
				__FILE__,
				__LINE__,
				all,
				this,
				NULL
			);
			FreeMem(all);
			FreeMem(this);
			all = tmp;
		}
	}  

	return all;
}

// Functions Used External From This File ===============================

void LatexMacroPopFullyExpandedInput(void)
{	int i, j;
	char ch;

	i  = NumExpandInput;
	ch = '\0';
	while( (i > 0) & (ch == '\0') )
	{	i--;
		j  = ExpandInput[i].text_index;
		assert( (unsigned int) j <= strlen(ExpandInput[i].text) );
		ch = ExpandInput[i].text[j];
		if( ch == '\0' )
		{	FreeMem(ExpandInput[i].text);
			NumExpandInput--;
		}
	}

}

void LatexMacroUserInput(int line, const char *input)
{	
	// start of new input, free old expansions
	LatexMacroPopFullyExpandedInput();

	// this is temporary until have multiple macros
	assert( NumExpandInput == 0 );

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
{	static int count_not_from_macro = 0;
	static int previous_backslash   = 0;
	char ch;
	int  startIndex;
	char token[MAX_LENGTH];
	int  i, j, k, ell;

	if( count_not_from_macro > 0 )
		LatexMacroPopFullyExpandedInput();

	i  = NumExpandInput;
	ch = '\0';
	while( (i > 0) & (ch == '\0') )
	{	i--;
		j  = ExpandInput[i].text_index;
		assert( (unsigned int) j <= strlen(ExpandInput[i].text) );
		ch = ExpandInput[i].text[j];

		// skip comments
		if( ch == '%' )
		{	ch = ExpandInput[i].text[++j];
			while( (ch != '\n') & (ch != '\0') )
				ch = ExpandInput[i].text[++j];

			// done with characters we have skipped
			ExpandInput[i].text_index = j;
		}

		if( ch != '\0' )
		{	// this is a usable macro character
			count_not_from_macro = 0;
			// advanced macro index to next character
			ExpandInput[i].text_index = j+1;
		}

		if( (ch == '\\') & (! previous_backslash) )
		{	// check for a recursive macro

			// get token corresponding to a possible macro
			k   = ExpandInput[i].text_index;
			ch  = ExpandInput[i].text[k];
			ell = 0;
			while( isalpha((int) ch) )
			{	if( ell < MAX_LENGTH )
					token[ell++] = ch;
				ch  = ExpandInput[i].text[++k];
			}

			// terminate the token
			if( ell < MAX_LENGTH )
				token[ell] = '\0';
			else	token[MAX_LENGTH-1] = '\0';

			// newcommand inside of macro not legal
			if( strcmp(token, "newcommand") == 0 ) fataltex(
				"\\newcommand occurs inside of a macro"
			);

			// see if it is a macro
			ell = BinarySearch(DefineName, Ndefine, token);

			// check if we have a new macro inside of this macro expansion
			if( ell < Ndefine )
			{	// advance input for this macro past new macro 
				ExpandInput[i].text_index = k;
				
				// increase expansion level and have i point to new macro
				i = NumExpandInput;
				ExpandLatexMacro(DefineIndex[ell]);
				assert( NumExpandInput == i + 1 );

				// get first character from new macro expansion
				previous_backslash = 0;
				ch = LatexMacroGetCh();
			}
			else	
			{	// this backslash does not start a macro so
				// terminate this while loop
				previous_backslash = 1;
				ch                 = '\\';
			}
		}
	} 

	if( ch == '\0' )
	{	ch = UserGetCh();
		count_not_from_macro++;

		if( UserEscape )
		{	startIndex = UserIndex;

			ch         = UserGetCh();
			i          = 0;
			while( isalpha((int) ch) )
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
	previous_backslash = (ch == '\\');

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

	return MacroExpansionMessage();
}

int LatexMacroExpandLine()
{	assert( NumExpandInput > 0 );

	return ExpandInput[0].macro->line;
}	

const char *LatexMacroExpandFile()
{	assert( NumExpandInput > 0 );

	return ExpandInput[0].macro->file;
}	

const char *LatexMacroExpandName()
{	assert( NumExpandInput > 0 );

	return ExpandInput[0].macro->name;
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
