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
	{	*ch = tolower(*ch);
		ch++;
	}
	return s;
}
