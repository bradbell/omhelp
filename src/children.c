/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin children$$
$spell
	printable
	printid
$$

$section List Children of a Section$$

$table
$bold Syntax$$
$cend $codei/ListChildren(/S/, /printable/)/$$ $rend
$cend $codei/TableChildren(/S/, /printable/)/$$
$tend

$head Description$$
Output (to current output file)
a list of HTML links to the sections that are children
of the specified section.
$codei/

ListChildren
/$$
Use the title for each child as the linking text.
$codei/

TableChildren
/$$
Use the
$cref/cross reference tag/CrossReference/Tag/$$ for each child
as the linking text.
Output the corresponding title next to the linking text.
$codei/

/S/
/$$
is an pointer to a
$cref/SectionInfo/SectionInfo/$$ record
that specifies which section children
are being listed for cross reference linking.
$codei/

/printable/
/$$
is an integer either equal to zero or one.
If it is zero, no special action is taken.
If it is one, we are outputting a printable version of the web site.
In this case, the
$cref/printid/CrossReference/Printid/$$
corresponding to each child is included at the end of the
linking text.
In addition, the cross reference link is to the same file
and the NAME field $italic printid$$ within that file.

$end
*/
# include "children.h"

# include <assert.h>
# include <stdlib.h>
# include <string.h>

# include "section.h"
# include "cross.h"
# include "convert.h"
# include "output.h"
# include "StrCat.h"
# include "allocmem.h"
# include "Internal2Out.h"
# include "AutoTag.h"


static void OutputPre(char *text)
{
	while(*text != '\0')
		ConvertOutputCh(*text++, 1);
	return;
}

void TableChildren(SectionInfo *S, int printable)
{	int HtmlOnly;
	const char *ext;

	OutputString("<table>\n");

	// children
	S = S->children;
	while( S != NULL )
	{	assert( S->title != NULL );
		OutputString("<tr><td>");

		if( ! printable )
		{
			// only use HTML format for frame one of these sections
			HtmlOnly =  (strcmp(S->tag, SEARCH_TAG) == 0)
			         || (strcmp(S->tag, CONTENTS_TAG) == 0);
			if( HtmlOnly )
				ext = Internal2Out("HtmlOnlyExtension");
			else	ext = Internal2Out("OutputExtension");

			FormatOutput2("<a href=\"%s%s\" target=\"_top\">",
				S->tagLower,
				ext
			);
			OutputPre(S->tag);
		}
		else
		{
			CrossReference *C;

			C = FindCrossReference(S->tag, "");
			assert( C != NULL );

			FormatOutput("<a href=\"#%s\" target=\"_top\">",
				C->printid);

			OutputPre(S->tag);
			OutputPre(": ");
			OutputPre(C->printid);
		}

		OutputString("</a></td><td>");
		OutputPre(S->title);
		OutputString("</td></tr>");
		S = S->next;
	}
	OutputString("</table>");
	return;
}

void ListChildren(SectionInfo *S, int printable)
{	int HtmlOnly;
	const char *ext;

	// children
	OutputString("<div>");
	S = S->children;
	while( S != NULL )
	{	assert( S->title != NULL );

		if( ! printable )
		{
			// only use HTML format for frame one of these sections
			HtmlOnly =  (strcmp(S->tag, SEARCH_TAG) == 0)
			         || (strcmp(S->tag, CONTENTS_TAG) == 0);
			if( HtmlOnly )
				ext = Internal2Out("HtmlOnlyExtension");
			else	ext = Internal2Out("OutputExtension");

			FormatOutput2("<a href=\"%s%s\" target=\"_top\">",
				S->tagLower,
				ext
			);
			OutputPre(S->title);
		}
		else
		{
			CrossReference *C;

			C = FindCrossReference(S->tag, "");
			assert( C != NULL );

			FormatOutput("<a href=\"#%s\" target=\"_top\">",
				C->printid);
			OutputPre(C->printid);
			OutputPre(": ");

			OutputPre(S->title);
		}
		OutputString("</a>");
		ConvertForcedNewline(1);
		S = S->next;
	}
	OutputString("</div>");
	return;
}
