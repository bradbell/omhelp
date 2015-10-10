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
$beign PatternMatch$$

$section Routines for Finding a Pattern Match in A Text Sequence$$

$table
$bold Syntax$$ $cnext
$syntax%int PatternMatchLen(const char *%p%, char %escape%)%$$
$rnext $cnext
$syntax%int PatternMatchCh(char *%ch%)%$$
$tend

$fend 25$$

$head PatternMatchLen$$
This function initializes the $code PatternMatchCh$$ function
for matching the pattern defined by the '\0' terminated character
row vector $italic p$$.
The return value of $code PatternMatchLen$$ is the number of characters,
not counting the '\0', in the pattern to be matched.
If the length is to long, $code PatternMatchLen$$ returns minus one.
If the character $italic escape$$ is not present in pattern,
the return value of $code PatternMatchLen$$
will be the length of the string contained in $italic p$$.
$pre

$$
If the character $italic escape$$ is present in $italic p$$, it specifies
the beginning of an escape sequence. In this case the next three characters
after the escape character specify the ascii code for a single
character to be used in the pattern matching.
(If there are not three decimal digits following the escape character,
$code PatternMatchLen$$ returns with the value minus two.)


$head PatternMatchCh$$
Returns one if the input value of
$syntax%*%ch%$$
completes a pattern match,
and zero others.
If the input value of
$syntax%*%ch%$$
completes a pattern match,
then the previous $italic len$$ character were
$syntax%
	%p%[0], %p%[1], ..., %p%[%len%-1]
%$$
where $italic len$$
is the value returned by the previous call to $code PatternMatchLen$$
and $syntax%%p%[%len%-1] corresponds to the input value of
$syntax%*%ch%$$
The output value of
$syntax%*%ch%$$
is the input value of
$syntax%*%ch%$$
$italic len$$ previous calls ago.
This enables one to delay use of
$syntax%*%ch%$$
until one is sure that it will not be included in the pattern match.
(If there are not $italic len$$ calls since the previous call to
$code PatternMatchLen$$,
the output value of
$syntax%*%ch%$$
is '\0'.)

$end

*/

# include <string.h>
# include <assert.h>
# include <stdlib.h>

# include "PatternMatch.h"

# define PatternMatchMax 100

// pattern to count
static char Pattern[PatternMatchMax];

// number of counts relative to next
static int  Count[PatternMatchMax];

// history of previous input characters
static int History[PatternMatchMax];

// number of characters in the pattern
static int  Len;

// index corresponding to next character
static int  Next;

int PatternMatchLen(const char *p, char escape)
{	int i, j, k, len;
	char number[4];

	len = strlen(p);

	i = 0;
	j = 0;
	while(i < len )
	{
		if( j >= PatternMatchMax )
			return -1;

		Count[j]   = 0;
		History[j] = '\0';
		if( p[i] != escape )
			Pattern[j] = p[i];
		else
		{	if( i + 3 >= len )
				return -2;
			for(k = 0; k < 3; k++)
			{	number[k] = p[++i];
				if( number[k] < '0' || '9' < number[k] )
					return -2;
			}
			number[3]  = '\0';
			Pattern[j] = (char) atoi(number);
		}
		++i;
		++j;
	}
	Next = 0;

	Len = j;
	return Len;
}

int PatternMatchCh(char *ch)
{
	char match;
	int  retflag;

	int i, j;
	i     = Len;
	j     = Next;
	match = *ch;
	while(i)
	{	i--;
		Count[j] += match == Pattern[i];
		j = (j + 1) % Len;
	}
	//
	retflag     = Count[Next] == Len;
	Count[Next] = 0;
	//
	*ch           = History[Next];
	History[Next] = match;
	//
	Next        = (Next + 1) % Len;

	return retflag;
}
