/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin content_dev$$
$spell
	tmp
$$

$section Automatic Generation of Table of Contents$$

$head Syntax$$
$codei%void ContentPass1(SectionInfo *%content%)%$$


$head Description$$
This routine outputs creates the file
$icode/tag/.tmp/$$ and writes
a pass one version of the table of
contents to that file.
The argument $icode content$$ is the corresponding
$cref SectionInfo_dev$$ pointer corresponding to the table of contents.
The value $icode tag$$ in the file name
is equal to $icode/content/->tag/$$.


$end

*/
# include "content.h"

# include <ctype.h>
# include <string.h>
# include <assert.h>

# include "browser.h"
# include "section.h"
# include "output.h"
# include "str_alloc.h"
# include "convert.h"
# include "allocmem.h"
# include "href.h"
# include "main.h"
# include "strjoin.h"

static void NextContent(SectionInfo *F, int level)
{	int i, j;
	char *title;

	while( F != NULL )
	{
		// new line, indentation, and description
		OutputString("\n");
		for(i = 0; i < 4 * level; i++)
			OutputString(" ");

		// output section title (convert white space)
		title = str_alloc(F->title);
		i = j = 0;
		while(title[i] != '\0')
		{	if( isspace((int) title[i]) )
			{	title[j++] = ' ';
				i++;
				while( isspace((int) title[i]) )
					i++;
			}
			else	title[j++] = title[i++];
		}
		title[j] = '\0';
		ConvertOutputString(title, 0);
		FreeMem(title);

		// include short version of title; i.e., tag in linking text
		OutputString(": ");
		HrefOutputPass1(F->tag, "", "false", "", "true");
		ConvertOutputString(F->tag, 0);
		HrefEnd("");

		// table of contents for children
		NextContent(F->children, level + 1);

		// table of contents for siblings
		F = F->next;
	}
	return;
}

void ContentPass1(SectionInfo *content)
{	SectionInfo *Root;
	char *file;
	char *number;

	assert( content != NULL );

	if( ! PrintableOmhelp() )
	{	BrowserPass1( content );
		return;
	}


	// Open the Pass One output file for this section
	file = strjoin(content->tag, ".tmp");
	PushOutput(file);
	FreeMem(file);

	// Determine the root of the section tree
	Root = content;
	while( Root->parent != NULL )
		Root = Root->parent;
	assert( Root->next == NULL && Root->previous == NULL );


	// title for this section
	OutputString("<center><b><big><big>\n");

	// mark the end of the title for this section
	OutputString("<ETITLE>");

	// Add the section number to the title
	number = SectionNumber(content);
	OutputString(number);
	OutputString(": ");
	FreeMem(number);

	OutputString(content->title);
	OutputString("</big></big></b></center>\n");

	// The table of contents is preformatted text
	OutputString("\n<pre>");
	NextContent(Root, 0);
	OutputString("\n</pre>");

	PopOutput();
}
