/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2008 Bradley M. Bell

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
--------------------------------------------------------------------------
$begin hilite_command$$

$section Set Commands for Automatic Highlighting and Cross Referencing$$

$head Syntax$$
$codei%int hilite_command(
	int         line        ,
	int        %n_pattern%  ,
	char       *%commands%
%$$

$head Purpose$$
Set commands for highlighting and automatic cross reference done by the
$code hilite_out$$ command.

$head line$$
Is the line number in the current OMhelp input file 
that is used for error reporting erros in the $code hilitepat$$ command.
A fatal error is reported if $icode n_command$$ is to large.
A fatal error is also reported
if one of the commands is not in the list of commands that can be highlighted
(currently only the $code codep$$ command can be highlighted).

$head n_command$$
Is the number of commands specified by the character vector
$icode commands$$.
If $icode n_command$$ is equal to zero, $icode commands$$ is not used.

$head commands$$
The first chatacter in $icode commands$$ is an $code '\0'$$.
For $icode i$$ between zero and $icode%n_command%-1%$$,
The $th i$$ command is the characters between the 
$th i-1$$ and $th i$$ occurance of $code '\0'$$ in $icode commands$$.
in $icode commands$$.
Thus there are $icode%n_command%+1%$$ occurances of $code '\0'$$ in
$icode commands$$.
$pre

$$
After a call to $code hlite_command$$,
the state of the vector $icode commands$$ is unspecified.

$end
--------------------------------------------------------------------------
$begin hilite_token$$

$section Set Tokens for Automatic Highlighting and Cross Referencing$$

$head Syntax$$
$codei%int hilite_token(
	int         line        ,
	int        %n_pair%     ,
	char      *%pairs%
%$$

$head Purpose$$
Set token, tag pairs for highlighting and automatic cross reference 
done by the $code hilite_out$$ command.

$head line$$
Is the line number in the current OMhelp input file that is used
for error reporting erros in the $code hilitecmd$$ command.
A fatal error is reported if $icode n_pair$$ is not an even number.
A fatal error is also reported if one of the tokens or tags is too large.

$head n_pair$$
Is the number of token, tag pairs specified by the character vector
$icode tokens$$.
If $icode n_pair$$ is equal to zero, $icode pairs$$ is not used.

$head pairs$$
The first character in $icode pairs$$ is a $code '\0'$$.
The first token goes from $icode%pairs%+1%$$ to the
second $code '\0'$$ in $icode pairs$$.
The first tag goes from the second $code '\0'$$
to the third $code '\0'$$.
$pre

$$
For $icode i$$ between two and $icode%n_pair%-1%$$,
The $th i$$ token goes from the character directly after 
the $code '\0'$$ terminating the $th i-1$$ tag 
to the $code '\0'$$ terminating the $th i$$ token.
The $th i$$ tag goes from the character following the 
$th i$$ token's $code '\0'$$ to the next $code '\0'$$.
$pre

$$
Thus there are $codei%2 * %n_pair% + 1%$$ terminating $code '\0'$$ characters
in $icode tokens$$.
$pre

$$
After a call to $code hlite_tokens$$,
the state of the vector $icode pairs$$ is unspecified.


$end
--------------------------------------------------------------------------
$begin hilite_out$$

$section Output Text with Automatic Highlighting and Cross Referencing$$

$head Syntax$$
$codei%void hilite_out(
	const char *%command%       ,
	int         %line%          ,
	int         %spell_check%   ,
	const char *%error_color%   ,
	const char *%hilite_color%  ,
	int         %pre%           , 
	char       *%text%          )%$$

$head Purpose$$
Outputs $icode text$$ with automatic highlightling and 
cross referencing as defined
by the previous call to $code hilite_command$$ and $code hilite_token$$.

$head command$$
is the current command. If it is in the current hilite command
list, automatic highlighting and cross referencing is done.
Otherwise the text is output without highlighting and cross referencing.

$head line$$
is the line number for spell check error reporting.

$head spell_check$$
If true, spell checking is done on the characters requested for output.
Otherwise it is not.

$head error_color$$
Is a $code '\0'$$ terminated character vector specifying
the color to use for spell check error reporting.

$head hilite_color$$
Is a $code '\0'$$ terminated character vector specifying
the color to use for highlighting.

$head pre$$
If $icode pre$$ is true, the output is preformatted.
Otherwise it is not.

$head text$$
Is a $code '\0'$$ terminated character vector containing
the text to be output.

$head matching$$
A pattern match starts directly after a character not with in limits
(or with the first character) 
and end just before another character not with in limits
(or the last character).
Pattern matches that are tokens
are output with the cross reference (and not spell checked).
All other text is output normally.

$end
---------------------------------------------------------------------------
$begin hilite_set_default$$

$section Set Default for hilite Commands and Tokens$$

$head Syntax$$
$icode hilite_set_default()$$

$head Purpose$$
The current settings by $cref hilite_command$$ and $cref hilite_token$$
are stored so that they can be recalled later.

$end
---------------------------------------------------------------------------
$begin hilite_get_default$$

$section Get Default for hilite Commands and Tokens$$

$head Syntax$$
$icode hilite_get_default()$$

$head Purpose$$
The values stored by the previous call to 
$code hilite_set_default$$ are restored as the current settings 
corresponding to $cref hilite_command$$ and $cref hilite_token$$.
If there was no previous call to $cref hilite_set_default$$,
the correspondign settings will not highlite or cross reference any commands.

$end
--------------------------------------------------------------------------
*/
# include <stddef.h>
# include <assert.h>
# include <string.h>
# include <ctype.h>

# include "fatalerr.h"
# include "int2str.h"
# include "output_text.h"
# include "output.h"
# include "href.h"
# include "hilite.h"
# include "ClipWhiteSpace.h"

# define MAX_TOKEN    200
# define MAX_NTOKEN   20
# define MAX_NCOMMAND 20
# define MAX_NPATTERN 20

// set by previous call to hilite_default
static int Ncommand_default = 0; 
static char Command_default[MAX_NTOKEN][MAX_TOKEN];

// set by previous call to hilite_default
static int  Ntoken_default = 0; 
static char Token_default[MAX_NTOKEN][MAX_TOKEN];
static char Tag_default[MAX_NTOKEN][MAX_TOKEN];

// set by previous call to hilite_command with root false
static int Ncommand = 0;
static char Command[MAX_NTOKEN][MAX_TOKEN];

// set by previous call to hilite_token with root false
static int  Ntoken = 0; 
static char Token[MAX_NTOKEN][MAX_TOKEN];
static char Tag[MAX_NTOKEN][MAX_TOKEN];

static void match_indices(const char *text, int *start, int *end)
{	int i   = *start;
	char ch = text[i++];

	// skip to first matching character
	while( (ch != '\0')  & (ch != '_') & (isalpha(ch) == 0) )
		ch = text[i++]; 
	--i;

	// check for no matching characters
	if( ch == '\0' )
	{	*start = i;
		*end   = i;
		return;
	}

	// index of the first matching character
	*start = i;

	while( (ch == '_') | (isalpha(ch) != 0 ) | (isdigit(ch) != 0) )
		ch = text[++i];

	*end = i;
	return;
}

void hilite_set_default(void)
{	int i;
	Ncommand_default = Ncommand;
	for(i = 0; i < Ncommand; i++)
		strcpy(Command_default[i], Command[i]);
	Ntoken_default = Ntoken;
	for(i = 0; i < Ntoken; i++)
	{	strcpy(Token_default[i], Token[i]);
		strcpy(Tag_default[i], Tag[i]);
	}
	return;
}

void hilite_get_default(void)
{	int i;
	Ncommand = Ncommand_default;
	for(i = 0; i < Ncommand; i++)
		strcpy(Command[i], Command_default[i]);
	Ntoken= Ntoken_default;
	for(i = 0; i < Ntoken; i++)
	{	strcpy(Token[i], Token_default[i]);
		strcpy(Tag[i], Tag_default[i]);
	}
	return;
}

void hilite_command(
	int         line      ,
	int         n_command ,
	char        *commands )
{	int i;
	char *command;
	assert( *commands == '\0' );

	if( n_command > MAX_NCOMMAND ) fatalomh(
		"Error in the hilitecmd command that begins in line ",
		int2str(line),
		".\nThere are to many commands in this command",
		NULL
	);
	Ncommand = n_command;
	command  = commands + 1;
	for(i = 0; i < n_command; i++)
	{	int len = strlen(command);
		int ok;
		ClipWhiteSpace(command);
		ok  = strcmp(command, "codep") == 0;
		ok |= strcmp(command, "verbatim") == 0;
		if( ! ok ) fatalomh(
			"Error in hilitecmd command that begins in line ",
			int2str(line),
			".\nThe command ",
			command,
			" is not valid in this context.",
			NULL
		);	
		assert( strlen(command) < MAX_TOKEN );
		strcpy(Command[i], command);
		command = command + len + 1;
	}
	return;
}

void hilite_token(
	int         line      ,
	int         n_pair    ,
	char        *pairs    )
{	int i;
	char *token;
	assert( *pairs == '\0' );

	if( n_pair > MAX_NTOKEN ) fatalomh(
		"Error in the hilitetok command that begins in line ",
		int2str(line),
		".\nThere are to many (token, tag) pairs in this command",
		NULL
	);
	Ntoken = n_pair;
	token  = pairs + 1;
	for(i = 0; i < n_pair; i++)
	{	int len   = strlen(token);
		char *tag = token + len + 1;
		int id, j;
		len       = strlen(tag);
		ClipWhiteSpace(token);
		ClipWhiteSpace(tag);
		if( strlen(token) > MAX_TOKEN - 1 ) fatalomh(
			"Error in the hilitetok command that begins in line ",
			int2str(line),
			".\nThe following token is to long\n",
			token,
			NULL
		);
		if( strlen(tag) > MAX_TOKEN - 1 ) fatalomh(
			"Error in the hilitetok command that begins in line ",
			int2str(line),
			".\nThe following tag is to long\n",
			tag,
			NULL
		);
		id = (isalpha(token[0]) != 0) | (token[0] != '_' );
		j  = strlen(token);
		while(--j)
		{	char ch = token[j];
			id &= (isalpha(ch)!=0) | (ch=='_') | (isdigit(ch)!=0);
		}

		if( ! id ) fatalomh(
			"Error in the hilitetok command that begins in line ",
			int2str(line),
			".\nThe following token is not an identifier\n",
			token,
			NULL
		);
		strncpy(Token[i], token, MAX_TOKEN);
		strncpy(Tag[i], tag, MAX_TOKEN);
		token = tag + len + 1;
	}
	return;
}


void hilite_out(
	const char *command        ,
	int         line           , 
	int         check_spell    , 
	const char *error_color    , 
	const char *hilite_color   ,
	int         pre            , 
	char       *text
)
{	int i, len, index, match, end;
	int  start = 0;
	char skip  = '\0';
	
	match = 0;
	for(i = 0; i < Ncommand; i++)
		match |= strcmp(command, Command[i]) == 0;
	if( ! match )
	{	output_text(line, text, pre, skip, check_spell, error_color);
		return;
	}

	len   = strlen(text);
	while( start < len )
	{	match_indices(text, &start, &end);

		// check for a token match
		char save = text[end];
		text[end] = '\0';
		index = -1;
		for(i = 0; i < Ntoken; i++)
			if( strcmp(text + start, Token[i]) == 0 )
				index = i;
		text[end] = save;

		if( index < 0 )
			start = end;
		else
		{	// output characters from start to end of token
			if( start > 0 )
			{	char save         = text[start];
				text[start]       = '\0';
				char skip         = '\0';
				output_text(line, text, pre, skip,
					check_spell, error_color
				);
				text[start]       = save;
			}
			if( Tag[index][0] == '\0' )
			{	OutputString("<font color=\"");
				OutputString(hilite_color);
				OutputString("\">");
			}
			else
			{	char *head         = "";
				char *external     = "false";
				char *displayframe = "";
				HrefOutputPass1(
					Tag[index]    ,
					head          ,
					external      ,
					displayframe
				);
			}
			output_text(line, Token[index], pre, skip, 
				check_spell, error_color
			); 
			if( Tag[index][0] == '\0' )
				OutputString("</font>");
			else	HrefEnd("");

			text  = text + end;
			len   = len - end;
			start = 0;
		}
	}
	output_text(line, text, pre, skip, check_spell, error_color);
	return;
}
