/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin UniformWhiteSpace_dev$$

$section Unify Different White Space Versions of Same Information$$

$head Syntax$$
$codei%void UniformWhiteSpace(char *%s%)%$$


$head Description$$
For some applications, one or more white space characters
just represents a delimiter between different tokens in a string.
This routine converts the string $icode s$$ so that leading
and trailing white space is deleted and so that
each token in the string is separated by just one space ' ' character.

$head s$$
The input and output contents of $icode s$$ is a '\0'
terminated character string.
If $icode s$$ is empty; i.e.,
the first character in $icode s$$ is '\0',
no write is attempted to the memory pointed to by $icode s$$.


$end
*/

# include <stdio.h>
# include <assert.h>
# include <ctype.h>

void UniformWhiteSpace(char *s)
{	int i = 0;  // index of next character in input value of string
	int j = 0;  // index of next character in output value of string
# ifndef NDEBUG
	int k;      // temporary index
# endif

	if( s[i] == '\0' )
		return;

	// skip leading white space in front of string
	while( isspace((int) s[i]) )
		i++;

	// convert multiple white space to one space
	while( s[i] != '\0' )
	{	assert( ! isspace((int) s[i]) );

		// copy this token from input to output
		while( (s[i] != '\0') & (! isspace((int) s[i]) ) )
			s[j++] = s[i++];

		// find end of white space following this token
# ifndef NDEBUG
		k = i;
# endif
		while( isspace((int) s[i]) )
			i++;

		if( s[i] != '\0' )
		{	assert( i > k );
			assert( ! isspace((int) s[i]) );

			// another token follows so place a space between
			assert( i > j );
			s[j++] = ' ';
		}
	}

	// terminate the output string value
	s[j] = '\0';

	return;
}
