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

$head Syntax$$
$codei%void StrRemove(char *%str%, char %ch%)%$$


$head Description$$
All the characters in $icode str$$ that are equal to $icode ch$$
are removed where $icode str$$ is a '\0' terminated
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
