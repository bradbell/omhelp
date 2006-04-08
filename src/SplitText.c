/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell

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

$begin SplitText$$
$spell 
	int
	substrings
	cmd
	fatalomh
	OMhelp
$$

$section Splitting Text At Each Delimiter$$

$table
$bold Syntax$$ $cend $syntax%int SplitText(
	char *%line%, 
	char *%cmd%, 
	char *%text%
)%$$
$tend

$fend 25$$

$head Description$$
The '\0' terminated character vector $italic text$$ contains
a delimiter sequence that is to be split into tokens
by the actions specified below (in the specified order).

$list number$$
If the first character in $italic text$$ is a letter,
an error message is printed and this routine does not return.
$lnext
If the first character in $italic text$$ is a 
white space character, $code SplitText$$
changes it to a '\0' character and
returns the value one (for one token).
$lnext
If the length of $italic text$$ is less than two characters
(not counting '\0'), an error message is printed
and this routine does not return.
$lnext
The first character in $italic text$$ is the delimiter character.
If it is not equal to the last character in $italic text$$
an error message is printed and this routine does not return.
$lnext
If the first and last characters of $italic text$$ are equal,
the return value of $code SplitText$$ is
the number of tokens; i.e.,
the number of delimiter characters minus one.
Each occurrence of the delimiter character in $italic text$$
is changed to a '\0' character. 
This splits $italic text$$ into tokens.
$lend

$head Errors$$
All the routines documented above use 
$xref/fatalerr//fatalomh/$$ to report error messages; i.e.,
they assume that there is an open input file and
that we are currently parsing OMhelp input.
The error messages listed above identify
$italic line$$ as the line number in the input file
and $italic cmd$$ as the command where the error occurred
in a delimiter sequence.
$end
*/

# include <assert.h>
# include <string.h>
# include <ctype.h>

# include "SplitText.h"
# include "fatalerr.h"
# include "int2str.h"
# include "StrCat.h"
# include "str_alloc.h"


static char *char2str(int ch)
{	char str[4];
	char *ascii;
	char *ret;
	if( 32 < ch && ch < 127 )
	{	if( ch == '\'' )
			return str_alloc("(single quote)");
		else if( ch == '\"' )
			return str_alloc("(double quote)");
		str[0] = str[2] = '\'';
		str[1] = ch;
		str[3] = '\0';
		return str_alloc(str);
	}
	ret = StrCat(
		__FILE__,
		__LINE__,
		"(ascii code ",
		int2str(ch),
		")",
		NULL
	);
	return ret;
}

int SplitText(int line, const char *cmd, char *text)
{	char del;
	int  ndel;
	int  len;
	int  i;

	// length of text
	len     = strlen(text);
	if( len < 2 ) fatalomh(
		"In the ",
		cmd,
		" command in line ",
		int2str(line),
		"\nThe delimiter sequence has less than two characters",
		NULL
	);

	// delimiter
	del     = *text;

	// check if sequence begins with white space
	if( isspace(del) )
	{	text[0] = '\0';
		return 1;
	}

	// check last character
	if( text[len - 1] != del ) fatalomh(
		"In the ",
		cmd,
		" command in line ",
		int2str(line),
		":\nThe first character of the delimiter sequence ",
		char2str(del),
		",\nis not the same as the last character ",
		char2str(text[len-1]),
		".",
		NULL
	);

	ndel = 0;
	for(i = 0; i < len;  i++)
	{	// convert to delimiter to '\0'
		if( text[i] == del )
		{	text[i] = '\0';
			ndel++;
		}
	}
	assert(ndel > 1);

	// return number of substrings found
	return ndel - 1;
}
