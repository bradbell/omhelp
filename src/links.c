/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin links_dev$$
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

$head Syntax$$
$codei/BeginLinks(/tagfrom/, /direction/, /image_link/, /image_file/, /stylecmd/)/$$
$codei/TitleLinks(/title/)/$$
$codei/AddLink(/tag/, /head/, /text/)/$$
$codei/EndLinks()/$$


$head Description$$
The routines in this file manage
the HTML file that contains the automatically generated
cross reference links that are relative to a section.
$pre

$$
All of the arguments
$icode tagfrom$$,
$icode direction$$,
$icode image_link$$,
$icode image_file$$,
$icode title$$,
$icode tag$$,
$icode crossheading$$,
and
$icode text$$,
are all '\0' terminated vectors of type $code const char*$$.
One exception to this rule is that $icode image_link$$
and $icode image_file$$ may be $code NULL$$.
$codei/

BeginLinks(/tagfrom/, /direction/, /image_link/, /image_file/, /stylecmd/)
/$$
The opens a new output file named $icode/taglower/_links./ext/$$
where $icode taglower$$ is a lower case version of $icode tagfrom$$
and $icode ext$$ is the output file extension specified by
$cref Internal2Out_dev$$.
This file will contain a set of links for navigating from
specified section.
The argument $icode tagfrom$$ contains
the a cross reference tag for the section where the links will appear.
The argument $icode direction$$
is either $code "row"$$ or $code "column"$$ depending
on if the links are to be in a frame displayed
as a row or column of the overall window.
$pre

$$
The argument $icode image_link$$ specifies the web address that the
image file $icode image_file$$ is to be linked to.
If $icode image_link$$ is $code NULL$$, the image does not appear
and $icode image_file$$ is not used.
Otherwise, $icode image_file$$ cannot be $code NULL$$.
If $icode/image_link/[0] == '\0'/$$,
the image is output, but it is not linked to any web address.
$pre

$$
The argument $icode stylecmd$$ is a $code '\0'$$ terminated character
vector that specifies the exact form of the style commands
to use at the beginning of this file.
(This enables the inclusion of style information such as background color.)
$pre

$$
It is assumed that the routine $code EndLinks$$
will be called some time after $code BeginLinks$$ and before
another call to $code BeginLinks$$.
$codei/

TitleLinks(/title/)
/$$
It is assumed that we are between a call to $code BeginLinks$$
and the corresponding call to $code EndLinks$$.
This call to $code TitleLinks$$
separates links from the previous title and
writes a title for the set of links that follow.
$codei/

AddLink(/text/, /tag/, /crossheading/, /frame/)
/$$
It is assumed that we are between a call to $code BeginLinks$$
and the corresponding call to $code EndLinks$$.
If $icode/crossheading/[0]/$$ is not '\0',
it is assumed that $icode/tag/[0]/$$ is not '\0'.
$pre

$$
If $icode/tag/[0]/$$ is '\0',
$icode text$$ is output as straight text without a link.
$pre

$$
If neither of the cases above hold,
It is assumed that $icode tag$$ and $icode crossheading$$.
specify a valid $cref/cross reference/CrossReference_dev/$$.
In this case
$icode text$$ is linked to the
$cref/cross reference heading/glossary_dev/Cross Reference Heading/$$
specified by $icode crossheading$$
with in the section specified by $icode tag$$.
$pre

$$
Leading underbars in $icode text$$ are not included in the output.
Leading spaces are output as non-breaking spaces and can
be used to indent the linking text.
If $icode/crossheading/[0]/$$ == '\0',
the link replaces the entire window.
$codei/

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
