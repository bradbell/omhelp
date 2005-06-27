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
$begin Color$$
$spell
	Mem
	cmd
	delseq
	fatalomh
	OMhelp
$$

$section Extract Color Style From Delimiter Sequence$$

$table
$bold Syntax$$ 
$cend $syntax%char *Color(
	char *%line%, 
	char *%cmd%, 
	char *%delseq%
)%$$
$tend

$head Description$$
The argument $italic delseq$$ is
a '\0' terminated character vector.
If it does not agree with the specifications below,
an error message that identifies the
contains a delimiter sequence that specifies a color.

$head Specifications$$
If it contains one token, the token (not counting surrounding white space)
is one of the
color names specified below.
Otherwise,
each token is a positive integer between 0 and 255
that specifies the RGB value for the color.
The return value 
of $code Color$$ 
is a '\0' terminate character vector containing a valid
for a color style.
It is allocated using $xref/AllocMem/$$ and should be freed
using $xref/AllocMem/FreeMem/FreeMem/$$ when it is no longer needed.


$head Color Names$$
The valid color names are case insensitive and are listed below:
$table
$pre     $$ 
	$cnext Black    $cnext Green  $rnext
	$cnext Silver   $cnext Lime   $rnext
	$cnext Gray     $cnext Olive  $rnext
	$cnext White    $cnext Yellow $rnext
	$cnext Maroon   $cnext Navy   $rnext
	$cnext Red      $cnext Blue   $rnext
	$cnext Purple   $cnext Teal   $rnext
	$cnext Fuchsia  $cnext Aqua
$tend


$head Errors$$
It $italic delseq$$ does not meet the specifications above,
$xref/fatalerr//fatalomh/$$ is used to report error messages; i.e.,
it is assumed that there is an open input file and
that we are currently parsing OMhelp input.
The error messages listed above identify
$italic line$$ as the line number in the input file
and $italic cmd$$ as the command where the error occurred
in a delimiter sequence.

$end 
-----------------------------------------------------------------------------
*/

# include "Color.h"
# include "SplitText.h"
# include "ClipWhiteSpace.h"
# include "str_alloc.h"
# include "fatalerr.h"
# include "StrCat.h"
# include "int2str.h"

# include <assert.h>
# include <string.h>

# ifndef WIN32
# define stricmp strcasecmp 
# endif

static int IsUnsignedInteger(const char *text, int lower, int upper)
{	int flag;
	int value;

	flag = (*text != '\0');

	value  = atoi(text);
	flag  &= lower <= value && value <= upper;
	
	while( *text != '\0' )
	{	flag &= ( '0' <= *text) & (*text <= '9');
		++text;
	}

	return flag;
}

char *Color(int line, const char *cmd, char *delseq)
{
	char *token[3];
	char *str;
	char *color;
	int ntoken;
	int i;
	int ok;
	char *primary[] = {
		"red",
		"green",
		"blue"
	};
	char *name[] = {
		"black",
		"green",
		"silver",
		"lime",
		"gray",
		"olive",
		"white",
		"yellow",
		"maroon",
		"navy",
		"red",
		"blue",
		"purple",
		"teal",
		"fuchsia",
		"aqua"
	};
	int nname = sizeof(name) / sizeof(name[0]);

	assert( delseq != NULL );

	
	ntoken = SplitText(line, cmd, delseq);
	str    = delseq + 1;

	// case where color is specified by name
	if( ntoken == 1 )
	{	ClipWhiteSpace(str);
		for(i = 0; i < nname; i++)
		{	if( stricmp(str, name[i]) == 0 )
				return str_alloc(str);
		}
		fatalomh(
			"At ",
			cmd,
			" command lin line ",
			int2str(line),
			"\n",
			str,
			" is not a valid color name",
			NULL
		);
	}
	

	if( ntoken != 3 ) fatalomh(
		"At ",
		cmd,
		" comamnd in line ",
		int2str(line),
		"\nEither one or three tokens expected in delimiter sequence.",
		NULL
	);


	// case where color is specified by RGB values
	for(i = 0; i < ntoken; i++)
	{	token[i] = str;
		str = str + strlen(str) + 1;

		ClipWhiteSpace(token[i]);

		ok = IsUnsignedInteger(token[i], 0, 255);

		if( ! ok ) fatalomh(
			"At ",
			cmd,
			" comamnd in line ",
			int2str(line),
			"\nThe RGB code for ",
			primary[i],
			" is not an unsigned integer\n",
			"between 0 and 255",
			NULL
		);
	}

	color = StrCat(
		__FILE__,
		__LINE__,
		"rgb(",
		token[0],
		", ",
		token[1],
		", ",
		token[2],
		")",
		NULL
	);

	return color;
}
