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
$begin StrRemove$$
$spell
	str
	ch
$$

$section Remove Copies of A Certain Character From A String$$

$table
$bold Syntax$$
$cend $syntax%void StrRemove(char *%str%, char %ch%)%$$
$tend

$fend 20$$

$head Description$$
All the characters in $italic str$$ that are equal to $italic ch$$
are removed where $italic str$$ is a '\0' terminated
character vector


$end
*/

# include "StrRemove.h"

void StrRemove(char *str, char ch)
{
	char *sin   = str;
	char *sout = str;

	while( *sin != '\0' )
	{	if( *sin != ch )
			*sout++ = *sin;
		sin++;
	}
	*sout = '\0';
}
