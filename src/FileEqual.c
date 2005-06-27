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
$begin FileEqual$$
$spell
	const
	backslash
$$

$section Check if Two File Names Correspond to The Same File$$
$index file, same name$$
$index name, same file$$
$index same, file name$$

$table
$bold Syntax$$
$cnext $syntax%int FileEqual(const char *%name1%, const char *%name2%)%$$
$tend

$fend 25$$

$head Description$$
System dependent check if the file corresponding to 
$italic name1$$ is equal to the file correspond to $italic name2$$
where $italic name1$$ and $italic name2$$ are $code '\0'$$ terminated
character vectors.
The backslash $code \$$ and forward slash $code /$$ 
are considered equal in this comparison.
In Windows, the comparison is not case sensitive, 
otherwise it is case sensitive.
$pre

$$
Other comparison checks, 
such as interpreting $code ..$$ as the parent directory, 
may be included in the future.

$end
*/

# include <stdio.h>
# include <ctype.h>

# ifdef WIN32
# include <io.h>
# endif

# include "FileEqual.h"


# define FORWARD_SLASH 47
# define BACK_SLASH    92

static int equal(int c1, int c2)
{	int s1 = c1 == FORWARD_SLASH || c1 == BACK_SLASH;
	int s2 = c2 == FORWARD_SLASH || c2 == BACK_SLASH;
	int flag;

	flag = s1 && s2;

	if( flag ) 
		return flag;

# ifdef WIN32
	c1 = tolower(c1);
	c2 = tolower(c2);
# endif

	return c1 == c2;
}	


int FileEqual(const char *name1, const char *name2)
{	int c1;
	int c2;
	int flag;
		
	c1 = *name1++;
	c2 = *name2++;
	while( c1 != '\0' && c2 != '\0' )
	{	flag = equal(c1, c2);
		if( ! flag )
			return flag;

		c1 = *name1++;
		c2 = *name2++;
	}
	return c1 == c2;
}
