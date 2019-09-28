/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin ClipWhiteSpace_dev$$

$section Clip Leading and Trailing White Space$$

$head Syntax$$
$codei%void ClipWhiteSpace(char *%s%)%$$


$head Description$$
Leading and trailing white space characters are removed from
the '\0' terminated character vector $icode s$$.
$pre

$$
If $icode s$$ is empty; i.e.,
the first character in $icode s$$ is '\0',
no write is attempted to the memory pointed to by $icode s$$.


$end
*/

# include <ctype.h>

void ClipWhiteSpace(char *s)
{	int i;
	int j;

	if( *s == '\0' )
		return;

	// skip leading white space
	i = 0;
	while( isspace((int) s[i]) )
		i++;

	// copy to end of string
	j = 0;
	while( s[i] != '\0' )
		s[j++] = s[i++];

	// terminate
	s[j] = '\0';

	while( j > 0 && isspace((int) s[j-1] ) )
	{	--j;
		s[j] = '\0';
	}
}
