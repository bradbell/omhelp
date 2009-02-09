/*--------------------------------------------------------------------
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
$codei%void hilite_command(
	int        %line%       ,
	int        %n_pattern%  ,
	char       *%commands%
%$$

$head Purpose$$
Set commands for highlighting and automatic cross reference done by the
$code hilite_out$$ command.

$head line$$
Is the line number in the current OMhelp input file 
that is used for error reporting erros in the $code hilitecmd$$ command.
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

$section 
Set Patterns and Tags for Automatic Highlighting and Cross Referencing$$

$head Syntax$$
$codei%void hilite_token(
	int        %line%     ,
	int        %n_arg%    ,
	char      *%args%
%$$

$head Purpose$$
Set patterns and tags for highlighting and automatic cross reference 
done by the $code hilite_out$$ command.

$head line$$
Is the line number in the current OMhelp input file that is used
for error reporting erros in the $code hilitecmd$$ command.
A fatal error is reported if $icode n_arg$$ is not 
a multiple of four.
A fatal error is also reported if one of the patterns or tags is too large.

$head n_arg$$
Is the number of arguments specified by the character vector
$icode args$$.

$head args$$
For $icode%j%=1,%...%n_arg%/4%$$:
$pre

$$
$icode before_j$$ is the characters between 
$codei%4*%j% - 3%$$ and the $codei%4*%j% - 2%$$ 
terminating $code '\0'$$ in $icode args$$. 
$pre

$$
$icode token_j$$ is the characters between 
$codei%4*%j% - 2%$$ and the $codei%4*%j% - 1%$$ 
terminating $code '\0'$$ in $icode args$$. 
$pre

$$
$icode after_j$$ is the characters between 
$codei%4*%j% - 1%$$ and the $codei%4*%j%$$ 
terminating $code '\0'$$ in $icode args$$. 
$pre

$$
$icode tag_j$$ is the characters between 
$codei%4*%j%$$ and the $codei%4*%j% + 1%$$ 
terminating $code '\0'$$ in $icode args$$. 
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

$end
---------------------------------------------------------------------------
$begin hilite_set_default$$

$section Set Default for hilite Commands and Tokens$$

$head Syntax$$
$icode hilite_set_default()$$

$head Purpose$$
The current settings by 
$cref hilite_command$$ and $cref hilite_token$$
are stored so that they can be recalled later.

$end
---------------------------------------------------------------------------
$begin hilite_get_default$$

$section Get Default for hilite Commands and Tokens$$

$head Syntax$$
$icode hilite_get_default()$$

$head Purpose$$
The values stored by the previous call to 
$code hilite_set_default$$ are restored as the current settings corresponding 
$cref hilite_command$$ and $cref hilite_token$$.
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
# include "allocmem.h"


# define MAX_ERROR    200
# define MAX_TOKEN    200
# define MAX_NTOKEN   20
# define MAX_NCOMMAND 20
# define MAX_NPATTERN 20

// set by previous call to hilite_default
static int  Ncommand_default = 0; 
static char Command_default[MAX_NTOKEN][MAX_TOKEN];

static int  Npattern_default = 0; 
static int  Nbefore_default[MAX_NTOKEN];
static int  Ntoken_default [MAX_NTOKEN];
static int  Nafter_default [MAX_NTOKEN];
static char Pattern_default[MAX_NTOKEN][MAX_TOKEN];
static char Tag_default    [MAX_NTOKEN][MAX_TOKEN];

// set by previous call to hilite_command
static int  Ncommand = 0;
static char Command[MAX_NTOKEN][MAX_TOKEN];

// set by previous call to hilite_token
static int  Npattern = 0; 
static int  Nbefore[MAX_NTOKEN];
static int  Ntoken [MAX_NTOKEN];
static int  Nafter [MAX_NTOKEN];
static char Pattern[MAX_NTOKEN][MAX_TOKEN];
static char Tag    [MAX_NTOKEN][MAX_TOKEN];


static int match_pattern(const char *text, int start)
{	int i, j, k, agree;
	const char *pattern;
	for(i = 0; i < Npattern; i++)
	{	j       = 0;
		k       = start;
		pattern = Pattern[i];
		agree   = (pattern[j] != '\0') & (text[k] != '\0');
		while( agree )
		{	if( isspace(pattern[j]) )
			{	// white space matches the beginning and end
				// of the input text
				agree  = isspace( text[k] ) > 0;
				agree |= k == 0;
				agree |= text[k] == '\0';
				if( agree )
				{	while( isspace(text[k]) )
						k++;
					while( isspace(pattern[j]) )
						j++;
				}
			}
			else if( pattern[j] == '\0' )
				agree = 0;
			else 	agree = pattern[j++] == text[k++];
		}
		if( pattern[j] == '\0' )
			return i;
	}
	return -1;
}


static int count_before(const char *text, int start, int index)
{	int j, k, agree;
	const char *before = Pattern[index];
	j       = 0;
	k       = 0;
	while( j < Nbefore[index] )
	{	if( isspace(before[j]) )
		{	while( isspace(text[k + start]) )
				k++;
			while( isspace(before[j]) )
				j++;
		}
		else
		{	assert( before[j] == text[k + start] );
			j++;
			k++;
		}
	}
	if( j >= Nbefore[index] )
		return k;
	return -1;
}


void hilite_set_default(void)
{	int i;
	Ncommand_default = Ncommand;
	for(i = 0; i < Ncommand; i++)
		strcpy(Command_default[i], Command[i]);

	Npattern_default = Npattern;
	for(i = 0; i < Npattern; i++)
	{	Nbefore_default[i] = Nbefore[i];
		Ntoken_default[i]  = Ntoken[i];
		Nafter_default[i]  = Nafter[i];
		strcpy(Pattern_default[i], Pattern[i]);
		strcpy(Tag_default[i], Tag[i]);
	}
	return;
}

void hilite_get_default(void)
{	int i;
	Ncommand = Ncommand_default;
	for(i = 0; i < Ncommand; i++)
		strcpy(Command[i], Command_default[i]);
	Npattern = Npattern_default;
	for(i = 0; i < Npattern; i++)
	{	Nbefore[i] = Nbefore_default[i];
		Ntoken[i]  = Ntoken_default[i];
		Nafter[i]  = Nafter_default[i];
		strcpy(Pattern[i], Pattern_default[i]);
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
	int         n_arg     ,
	char        *args     )
{	int i;
	char *before, *token, *after, *tag;
	assert( *args == '\0' );

	if( n_arg / 4 > MAX_NTOKEN ) fatalomh(
		"Error in the hilitetok command that begins in line ",
		int2str(line),
		".\nToo many (before, token, after, tag) groups",
		NULL
	);
	if( n_arg % 4 != 0 ) fatalomh(
		"Error in the hilitetok command that begins in line ",
		int2str(line),
		".\nThe number of arguments is not a multiple of four",
		NULL
	);
	Npattern = n_arg / 4;
	for(i = 0; i < Npattern; i++)
	{	int j, k;
		before    = args + 1;
		token     = before + strlen(before) + 1;
		after     = token + strlen(token) + 1;
		tag       = after + strlen(after) + 1;
		args      = tag + strlen(tag);
		//
		ClipWhiteSpace(token);
		ClipWhiteSpace(tag);
		//
		Nbefore[i] = token - before - 1;
		Ntoken[i]  = strlen(token);
		Nafter[i]  = tag - after - 1;
		//
		if( tag - before > MAX_TOKEN - 1 ) fatalomh(
			"Error in the hilitetok command that begins in line ",
			int2str(line),
			".\nThe following pattern is to long\n",
			before, token, after,
			NULL
		);
		if( strlen(tag) > MAX_TOKEN - 1 ) fatalomh(
			"Error in the hilitetok command that begins in line ",
			int2str(line),
			".\nThe following tag is to long\n",
			tag,
			NULL
		);
		// copy entire pattern into one buffer
		k = 0;
		for(j = 0; j < Nbefore[i]; j++)
			Pattern[i][k++] = before[j];
		for(j = 0; j < Ntoken[i]; j++)
			Pattern[i][k++] = token[j];
		for(j = 0; j < Nafter[i]; j++)
			Pattern[i][k++] = after[j];
		Pattern[i][k] = '\0';
		assert( k < MAX_TOKEN );

		strncpy(Tag[i], tag, MAX_TOKEN);
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
{	int i, len, index, flag, done;
	int  start = 0;
	char skip  = '\0';
	
	flag = 0;
	for(i = 0; i < Ncommand; i++)
		flag |= strcmp(command, Command[i]) == 0;
	if( ! flag )
	{	output_text(line, text, pre, skip, check_spell, error_color);
		return;
	}

	len   = strlen(text);
	done  = 0;
	while( start < len )
	{	index = match_pattern(text, start);

		if( index >= 0 )
		{	char save;
			int  token  = start + count_before(text, start, index);
			int  after  = token + Ntoken[index];
			assert( done <= start );
			// output characters before token
			if( start > 0 )
			{	char skip         = '\0';
				save              = text[token];
				text[token]       = '\0';
				output_text(line, text + done, pre, skip,
					check_spell, error_color
				);
				text[token]       = save;
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
			save        = text[after];
			text[after] = '\0';
			output_text(line, text + token, pre, skip, 
				check_spell, error_color
			); 
			text[after] = save;

			if( Tag[index][0] == '\0' )
				OutputString("</font>");
			else	HrefEnd("");

			done = start = after;
		}
		else	start++;
		assert( start <= len );
	}
	output_text(line, text + done, pre, skip, check_spell, error_color);
	return;
}
