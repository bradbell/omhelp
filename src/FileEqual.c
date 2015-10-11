/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
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
$cnext $codei%int FileEqual(const char *%name1%, const char *%name2%)%$$
$tend

$head Description$$
System dependent check if the file corresponding to
$icode name1$$ is equal to the file correspond to $icode name2$$
where $icode name1$$ and $icode name2$$ are $code '\0'$$ terminated
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
