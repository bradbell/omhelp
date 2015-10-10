/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
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
