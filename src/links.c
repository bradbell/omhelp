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
$begin links$$
$spell
	tagfrom
	crossheading
	const
	taglower
	underbars
	stylecmd
$$
$cindex automatic relative link$$
$index BeginLinks$$
$index TitleLinks$$
$index AddLink$$
$index EndLinks$$


$section Managing Frame Containing the Links Relative To A Section$$

$table
$bold Syntax$$
$cend 
$syntax/BeginLinks(/tagfrom/, /direction/, /image_link/, /image_file/, /stylecmd/)/$$ $rend
$cend $syntax/TitleLinks(/title/)/$$ $rend
$cend $syntax/AddLink(/tag/, /head/, /text/)/$$  $rend
$cend $syntax/EndLinks()/$$
$tend

$fend 25$$

$head Description$$
The routines in this file manage
the HTML file that contains the automatically generated
cross reference links that are relative to a section. 
$pre

$$
All of the arguments
$italic tagfrom$$,
$italic direction$$,
$italic image_link$$,
$italic image_file$$,
$italic title$$,
$italic tag$$,
$italic crossheading$$,
and
$italic text$$,
are all '\0' terminated vectors of type $code const char*$$.
One exception to this rule is that $italic image_link$$
and $italic image_file$$ may be $code NULL$$.
$syntax/

BeginLinks(/tagfrom/, /direction/, /image_link/, /image_file/, /stylecmd/)
/$$
The opens a new output file named $syntax//taglower/_links./ext/$$ 
where $italic taglower$$ is a lower case version of $italic tagfrom$$
and $italic ext$$ is the output file extension specified by 
$xref/Internal2Out/$$.
This file will contain a set of links for navigating from 
specified section.
The argument $italic tagfrom$$ contains
the a cross reference tag for the section where the links will appear.
The argument $italic direction$$
is either $code "row"$$ or $code "column"$$ depending
on if the links are to be in a frame displayed
as a row or column of the overall window.
$pre

$$
The argument $italic image_link$$ specifies the web address that the 
image file $italic image_file$$ is to be linked to.
If $italic image_link$$ is $code NULL$$, the image does not appear
and $italic image_file$$ is not used.
Otherwise, $italic image_file$$ cannot be $code NULL$$.
If $syntax//image_link/[0] == '\0'/$$, 
the image is output, but it is not linked to any web address. 
$pre

$$
The argument $italic stylecmd$$ is a $code '\0'$$ terminated character
vector that specifies the exact form of the style commands 
to use at the beginning of this file.
(This enables the inclusion of style information such as background color.)
$pre

$$
It is assumed that the routine $code EndLinks$$
will be called some time after $code BeginLinks$$ and before
another call to $code BeginLinks$$.
$syntax/

TitleLinks(/title/)
/$$
It is assumed that we are between a call to $code BeginLinks$$
and the corresponding call to $code EndLinks$$.
This call to $code TitleLinks$$
separates links from the previous title and 
writes a title for the set of links that follow.
$syntax/

AddLink(/text/, /tag/, /crossheading/, /frame/)
/$$
It is assumed that we are between a call to $code BeginLinks$$
and the corresponding call to $code EndLinks$$.
If $syntax//crossheading/[0]/$$ is not '\0',
it is assumed that $syntax//tag/[0]/$$ is not '\0'.
$pre

$$
If $syntax//tag/[0]/$$ is '\0',
$italic text$$ is output as straight text without a link.
$pre

$$
If neither of the cases above hold,
It is assumed that $italic tag$$ and $italic crossheading$$.
specify a valid $xref/CrossReference//cross reference/$$.
In this case
$italic text$$ is linked to the
$xref/glossary/Cross Reference Heading/cross reference heading/$$
specified by $italic crossheading$$
with in the section specified by $italic tag$$.
$pre

$$
Leading underbars in $italic text$$ are not included in the output.
Leading spaces are output as non-breaking spaces and can 
be used to indent the linking text.
If $syntax//crossheading/[0]/$$ == '\0', 
the link replaces the entire window.
$syntax/

EndLinks()
/$$
Completes and closes the file that was open by the
previous call to $code BeginLinks$$.
Every call to $code BeginLinks$$ must
have a corresponding call to $code EndLinks$$.

$end
*/

# include <string.h>
# include <stdio.h>
# include <ctype.h>

# include "output.h"
# include "href.h"
# include "strjoin.h"
# include "str_alloc.h"
# include "allocmem.h"
# include <assert.h>
# include "convert.h"
# include "cross.h"
# include "Internal2Out.h"

# include "links.h"

static int LinksOpen = 0;
static int Column    = 0;
static char *TagLower  = NULL;

void TitleLinks(const char *title)
{
	assert( LinksOpen );

	OutputString("<hr");
	OutputString(Internal2Out("SelfTerminateCmd"));
	OutputString("\n<b>");
	OutputString(title);
	OutputString("</b><br");
	OutputString(Internal2Out("SelfTerminateCmd"));
	OutputString("\n");
}

void AddLink(
	const char *text,
	const char *tag, 
	const char *crossheading
)
{	int link;

	while( *text == '_' || *text == ' ' )
	{	if( *text == ' ' )
			ConvertOutputCh(' ', 1);
		text++;
	}

	assert( LinksOpen );
	assert( crossheading[0] == 0 || tag[0] != 0  );
	assert( text[0] != 0 );

	link = tag[0] != '\0';

	if( link )
	{	CrossReference *C;
		char Frame[10];

		assert( tag[0] != 0 );
		C = FindCrossReference(tag, crossheading);
		assert( C != NULL );

		if( C->frame == 0 )
			Frame[0] = '\0';
		else	sprintf(Frame, "%d", C->frame);
		HrefOutputPass2(tag, crossheading, "false", Frame);
	}

	// preformatted output with special character conversion
	ConvertOutputString(text, 1);

	if( link )
		HrefEnd("");

	if( Column )
	{	OutputString("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");
	}
	else	// output two non-breaking spaces
		OutputString("&#160;&#160;\n");
}

void BeginLinks(
	const char *tagfrom,
	const char *direction,
	const char *image_link,
	const char *image_file,
	const char *stylecmd
)
{	char *file;
	int i;

	assert( tagfrom[0] != 0 );
	assert( ! LinksOpen );
	LinksOpen = 1;

	Column = strcmp(direction, "column") == 0;
	assert( Column || strcmp(direction, "row") == 0 );

	TagLower = str_alloc(tagfrom);
	i = 0;
	while( TagLower[i] != '\0' )
	{	TagLower[i] = tolower((int) TagLower[i] );
		++i;
	}

	file = StrCat(
		__FILE__,
		__LINE__,
		TagLower, 
		"_links",
		Internal2Out("OutputExtension"),
		NULL
	);
	PushOutput(file);
	FreeMem(file);


	OutputString(Internal2Out("StartOutputFile"));
	OutputString("<head>");
	OutputString(stylecmd);
	OutputString("</head><body>\n");

	if( image_link != NULL )
	{	
		if( image_link[0] != '\0' )
		{
			FormatOutput(
				"<a href=\"%s\" target=\"_top\">", image_link);
			FormatOutput(
				"<img border=\"0\" src=\"%s\"", image_file);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("</a>\n");
		}
		else
		{
			FormatOutput(
				"<img border=\"0\" src=\"%s\"", image_file);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("\n");
		}

		if( Column )
		{	OutputString("<br");
			OutputString(Internal2Out("SelfTerminateCmd"));
		}
		else	// output two non-breaking spaces
			OutputString("&#160;&#160;");
	}

	return;
}

void EndLinks()
{
	assert( LinksOpen );
	LinksOpen = 0;

	OutputString("</body>\n</html>\n");
	
	PopOutput();
	FreeMem(TagLower);
	TagLower = NULL;
}
