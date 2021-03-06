/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
=============================================================================
$begin Url_dev$$
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
$codei%char *Url(
	const char *%tag% ,
	const char *%head%,
	const char *%external%
)%$$

$head Purpose$$
Maps the internal represent of a link to a web address
(relative to the directory where this web site is stored).

$head Convention$$
All the arguments are all
$code '\0'$$ terminated character vectors.

$head tag$$
If $icode external$$ is equal to $code true$$,
$icode tag$$ is the web address corresponding this link.
Otherwise,
$icode tag$$ is the cross reference tag for the section
corresponding to this link.

$head head$$
This argument specifies the heading
(with in the file) corresponding to the link.
If the link is to the entire section, head is equal to the empty string; i.e.
$codei%
	%head%[0] == '\0'
%$$

$head external$$
This argument should be equal to $code true$$ or $code false$$.
See $icode tag$$ above for purpose of this argument.

$head Restrictions$$
This function should only be called during the second pass,
when all the cross references have been defined.
The argument $icode tag$$ must satisfy the following conditions:
$codei%
	assert( %tag%[0] != '\0' );
	assert( ! isspace((int) %tag%[0]) );
%$$

$head Memory$$
The return value is allocated using $cref AllocMem_dev$$
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
# include "strjoin.h"
# include "StrCat.h"
# include "allocmem.h"
# include "Internal2Out.h"
# include "convert.h"
# include "main.h"
# include "AutoTag.h"

char *Url(const char *tag, const char *head, const char *external)
{	char number[200];
	char *taglower;
	char *url;
	char *converted;
	int  i;
	int  HtmlOnly;
	const char *ext;

	// initialize to avoid compiler warning
	// (will be reset before used)
	CrossReference *C = NULL;

	assert( *tag != '\0' );
	assert( ! isspace((int) *tag) );

	assert( strcmp(external, "true") == 0 ||
	        strcmp(external, "false") == 0
	);

	if( strcmp(external, "false") == 0 )
	{	C = FindCrossReference(tag, head);
		assert( C != NULL );
		assert( C->defined );
	}

	// links must be in lower case (see discussion in PushOutput)
	taglower = str_alloc(tag);
	for(i = 0; taglower[i] != '\0'; i++)
		taglower[i] = tolower((int) taglower[i]);

	// check for case where only use htm for extension
	HtmlOnly =  (strcmp(tag, SEARCH_TAG) == 0)
		|| (strcmp(tag, CONTENTS_TAG) == 0);
	// HtmlOnly = HtmlOnly & ( NoFrame() | (head[0] != '\0') );
	if( HtmlOnly )
		ext = Internal2Out("HtmlOnlyExtension");
	else	ext = Internal2Out("OutputExtension");

	// set url
	if( head[0] == '\0' )
	{	if( strcmp(external, "true") == 0 )
			url = str_alloc(tag);
		else	url = strjoin(
				taglower,
				ext
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
		else if( NoFrame() )
		{	url = StrCat(
				__FILE__,
				__LINE__,
				taglower,
				ext,
				"#",
				converted,
				NULL
			);
		}
		else
		{	assert( C != NULL );
			sprintf(number, "%d", C->frame);
			url = StrCat(
				__FILE__,
				__LINE__,
				taglower,
				"_frame",
				number,
				ext,
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
