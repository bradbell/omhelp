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
$begin UniformWhiteSpace$$

$section Unify Different White Space Versions of Same Information$$

$table
$bold Syntax$$
$cend $syntax%void UniformWhiteSpace(char *%s%)%$$ 
$tend

$fend 20$$

$head Description$$
For some applications, one or more white space characters
just represents a delimiter between different tokens in a string.
This routine converts the string $italic s$$ so that leading
and trailing white space is deleted and so that
each token in the string is separated by just one space ' ' character.

$head s$$
The input and output contents of $italic s$$ is a '\0' 
terminated character string.
If $italic s$$ is empty; i.e.,
the first character in $italic s$$ is '\0',
no write is attempted to the memory pointed to by $italic s$$.


$end
*/

# include <stdio.h>
# include <assert.h>
# include <ctype.h>

void UniformWhiteSpace(char *s)
{	int i = 0;  // index of next character in input value of string
	int j = 0;  // index of next character in output value of string
	int k;      // temporary index

	if( s[i] == '\0' )
		return;

	// skip leading white space in front of string
	while( isspace(s[i]) )
		i++;

	// convert multiple white space to one space
	while( s[i] != '\0' )
	{	assert( ! isspace(s[i]) ); 	

		// copy this token from input to output 
		while( (s[i] != '\0') & (! isspace(s[i]) ) )
			s[j++] = s[i++];

		// find end of white space following this token
		k = i;
		while( isspace(s[i]) )
			i++;

		if( s[i] != '\0' )
		{	assert( i > k );
			assert( ! isspace(s[i]) );

			// another token follows so place a space between 
			assert( i > j );
			s[j++] = ' ';
		}
	}

	// terminate the output string value
	s[j] = '\0';

	return;
}
