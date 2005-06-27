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
$begin content$$
$spell
	tmp
$$

$section Automatic Generation of Table of Contents$$

$table
$bold Syntax$$
$cnext
$syntax%void ContentPass1(SectionInfo *%content%)%$$
$tend

$fend 20$$

$head Description$$
This routine outputs creates the file
$syntax//tag/.tmp/$$ and writes 
a pass one version of the table of
contents to that file.
The argument $italic content$$ is the corresponding 
$xref/SectionInfo/$$ pointer corresponding to the table of contents.
The value $italic tag$$ in the file name
is equal to $syntax//content/->tag/$$.


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
# include "str_cat.h"

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
		{	if( isspace(title[i]) )
			{	title[j++] = ' ';
				i++;
				while( isspace(title[i]) )
					i++;
			}
			else	title[j++] = title[i++];
		}
		title[j] = '\0';
		ConvertOutputString(title, 0);
		FreeMem(title);

		// include short version of title; i.e., tag in linking text
		OutputString(": ");
		HrefOutputPass1(F->tag, "", "false", "");
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
	file = str_cat(content->tag, ".tmp");
	PushOutput(file);
	FreeMem(file);

	// Determine the root of the section tree
	Root = content;
	while( Root->parent != NULL )
		Root = Root->parent;
	assert( Root->next == NULL && Root->previous == NULL );

	
	// title for this section
	OutputString("<center><b><big><big>\n");

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
