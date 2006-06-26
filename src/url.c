/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell

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
/*
=============================================================================
$begin Url$$
$spell
	isspace
	Mem
	Url
	href
	const
$$
$index Url, href$$
$index href, Url$$

$section Map Link Representation to a URL$$

$head Syntax$$
$syntax%char *Url(
	const char *%tag% , 
	const char *%head%,
	const char *%head%
)%$$ 

$head Purpose$$
Maps the internal represent of a link to a web address
(relative to the directory where this web site is stored).

$head Convention$$
All the arguments are all
$code '\0'$$ terminated character vectors.

$head tag$$
If $italic external$$ is equal to $code true$$,
$italic tag$$ is the web address corresponding this link.
Otherwise,
$italic tag$$ is the cross reference tag for the section
corresponding to this link.

$head head$$
This argument specifies the heading 
(with in the file) corresponding to the link.
If the link is to the entire section, head is equal to the empty string; i.e.
$syntax%
	%head%[0] == '\0'
%$$

$head external$$
This argument should be equal to $code true$$ or $code false$$.
See $italic tag$$ above for purpose of this argument.

$head Restrictions$$
This function should only be called during the second pass,
when all the cross references have been defined.
The argument $italic tag$$ must satisfy the following conditions:
$syntax%
	assert( %tag%[0] != '\0' );
	assert( ! isspace(%tag%[0]) );
%$$

$head Memory$$
The return value is allocated using $xref/AllocMem/$$
and should be freed using $code FreeMem$$

$end
------------------------------------------------------------------------------
*/

# include <stdio.h>
# include <assert.h>
# include <string.h>
# include <ctype.h>

# include "url.h"
# include "cross.h"
# include "str_alloc.h"
# include "str_cat.h"
# include "StrCat.h"
# include "allocmem.h"
# include "Internal2Out.h"
# include "convert.h"

char *Url(const char *tag, const char *head, const char *external)
{	char number[200];
	char *taglower;
	char *url;
	char *converted;
	int  i;

	// initialize to avoid compiler warning
	// (will be reset before used)
	CrossReference *C = NULL;
	
	assert( *tag != '\0' );
	assert( ! isspace(*tag) );

	assert( strcmp(external, "true") == 0 || 
	        strcmp(external, "false") == 0 
	);

	if( strcmp(external, "false") == 0 )
	{
		C = FindCrossReference(tag, head);
		assert( C != NULL );
		assert( C->defined );
	}

	// links must be in lower case (see discussion in PushOutput)
	taglower = str_alloc(tag);
	for(i = 0; taglower[i] != '\0'; i++)
		taglower[i] = tolower(taglower[i]);


	// set url
	if( head[0] == '\0' )
	{	if( strcmp(external, "true") == 0 )
			url = str_alloc(tag);
		else	url = str_cat(
				taglower, 
				Internal2Out("OutputExtension")
		);
	}
	else
	{	// XHTML cannot have certain character, such as <, here
		// This is an unspecified kludge to fix this
		converted = ConvertInternalString(head);	

		if( strcmp(external, "true") == 0 )
			url = StrCat(
				__FILE__, 
				__LINE__, 
				tag, 
				"#", 
				converted,
				NULL
		);
		else
		{	assert( C != NULL );
			sprintf(number, "%d", C->frame);
			url = StrCat(
				__FILE__, 
				__LINE__, 
				taglower, 
				"_frame", 
				number, 
				Internal2Out("OutputExtension"),
				"#",
				converted,
				NULL
			);
		}	

		FreeMem(converted);
	}
	FreeMem(taglower);

	return url;
}
