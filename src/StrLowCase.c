/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin StrLowCase$$
$spell
	str
$$

$index StrLowCase$$
$cindex string lower case convert$$
$section Convert a String to Lower Case$$

$table
$bold Syntax$$ $cend
$syntax%char *%%StrLowCase(
	char *%s%
)%$$ $rend
$rend
$bold See Also$$ $cend $mref/StrLowAlloc/$$
$tend

$fend 25$$

$head Description$$
converts the
$code '\0'$$ terminated character vector specified by $italic s$$
to lower case.
The return value is equal to $italic s$$; i.e.,
the return value points to the beginning of the memory that has been changed.

$end
------------------------------------------------------------------------
*/

# include <ctype.h>

char *StrLowCase(char *s)
{	char *ch = s;
	while( *ch != '\0' )
	{	*ch = (char) tolower((int) *ch);
		ch++;
	}
	return s;
}
