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
$begin ClipWhiteSpace$$

$section Clip Leading and Trailing White Space$$

$table
$bold Syntax$$
$cend $syntax%void ClipWhiteSpace(char *%s%)%$$ 
$tend

$fend 20$$

$head Description$$
Leading and trailing white space characters are removed from
the '\0' terminated character vector $italic s$$.
$pre

$$
If $italic s$$ is empty; i.e.,
the first character in $italic s$$ is '\0',
no write is attempted to the memory pointed to by $italic s$$.


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
	while( isspace(s[i]) )
		i++;

	// copy to end of string
	j = 0;
	while( s[i] != '\0' )
		s[j++] = s[i++];

	// terminate
	s[j] = '\0';

	while( j > 0 && isspace( s[j-1] ) )
	{	--j;
		s[j] = '\0';
	}
}
