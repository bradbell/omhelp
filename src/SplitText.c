/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
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

$head Syntax$$ $codei%int SplitText(
	int   %line%,
	char *%cmd%,
	char *%text%
)%$$


$head Description$$
The '\0' terminated character vector $icode text$$ contains
a delimiter sequence that is to be split into tokens
by the actions specified below (in the specified order).

$list number$$
If the first character in $icode text$$ is a letter,
an error message is printed and this routine does not return.
$lnext
If the first character in $icode text$$ is a
white space character, $code SplitText$$
changes it to a '\0' character and
returns the value one (for one token).
$lnext
If the length of $icode text$$ is less than two characters
(not counting '\0'), an error message is printed
and this routine does not return.
$lnext
The first character in $icode text$$ is the delimiter character.
If it is not equal to the last character in $icode text$$
an error message is printed and this routine does not return.
$lnext
If the first and last characters of $icode text$$ are equal,
the return value of $code SplitText$$ is
the number of tokens; i.e.,
the number of delimiter characters minus one.
Each occurrence of the delimiter character in $icode text$$
is changed to a '\0' character.
This splits $icode text$$ into tokens.
$lend

$head Errors$$
All the routines documented above use
$cref/fatalomh/fatalerr/$$ to report error messages; i.e.,
they assume that there is an open input file and
that we are currently parsing OMhelp input.
The error messages listed above identify
$icode line$$ as the line number in the input file
and $icode cmd$$ as the command where the error occurred
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
# include "newline_ch.h"


static char *char2str(int ch)
{	char str[4];
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
	if( isspace((int) del) )
	{	text[0] = '\0';
		return 1;
	}

	// check last character
	if( text[len - 1] != del )
	{	if( del != newline_ch() ) fatalomh(
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
		else	fatalomh(
			"In the ",
			cmd,
			" command in line ",
			int2str(line),
			":\nThe first character of the delimiter sequence ",
			char2str(del),
			",\nis not the same as the last character ",
			char2str(text[len-1]),
			".",
			"\nNote that the $newlinech character is also equal to",
			char2str(del),
			NULL
		);
	}

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
