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
$begin browser$$
$spell
	tmp
$$

$section Automatic Generation of Browser$$

$table
$bold Syntax$$
$cnext
$syntax%void BrowserPass1(SectionInfo *%browser%)%$$
$tend

$fend 20$$

$head Description$$
This routine outputs creates the file
$syntax//tag/.tmp/$$ and writes 
a pass one version of the table of
the browser sectionto that file.
The argument $italic browser$$ is the corresponding 
$xref/SectionInfo/$$ pointer corresponding to the browser section.
The value $italic tag$$ in the file name
is equal to $syntax//browser/->tag/$$.

$end

*/
# include "browser.h"

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <assert.h>

# include "Internal2Out.h"
# include "fatalerr.h"
# include "DirSep.h"
# include "str_alloc.h"
# include "copyfile.h"
# include "int2str.h"
# include "section.h"
# include "output.h"
# include "convert.h"
# include "allocmem.h"
# include "href.h"
# include "main.h"
# include "strjoin.h"

// ======================================================================
static char *Javascript =
"var Cookie            = document.cookie;\n"
"var Open              = '';\n"
"var SectionCount      = 000000;\n"
"var ImagesInitialized = false;\n"
"Children              = new Array();\n"
"Initialize();\n"
"\n"
"function Initialize()\n"
"{	var i;\n"
"\n"
"	if( Cookie.length == 10 + SectionCount )\n"
"		Open = Cookie.substring(9, 10 + SectionCount);\n"
"	else\n"
"	{	Open = '_T';\n"
"		for(i = 2; i <= SectionCount; i++)\n"
"			Open = Open + 'F';	\n"
"	}\n"
"	for (i = 1; i <= SectionCount; i++)\n"
"	{\n"
"		var child   = document.getElementById('children'+i);\n"
"		Children[i] = child;\n"
"		if( child != null )\n"
"		{	if( Open.charAt(i) == 'T' )\n"
"				child.style.display  = '';     // visible\n"
"			else	child.style.display  = 'none'; // invisible\n"
"		}\n"
"	}\n"
"}\n"
"function InitializeImages()\n"
"{	// would like to do this during initialization\n"
"	// but image variable seems to come out null then\n"
"\n"
"	for (i = 1; i <= SectionCount; i++)\n"
"	{\n"
"		if( Children[i] != null )\n"
"		{	var image   = document.images['folder'+i];\n"
"			if( Open.charAt(i) == 'T' )\n"
"				image.src  = '_open.gif';\n"
"			else	image.src  = '_close.gif';\n"
"		}\n"
"	}\n"
"	ImagesInitialized = true;\n"
"}\n"
"\n"
"// select a folder\n"
"function Select(index)\n"
"{\n"
"	if( ! ImagesInitialized )\n"
"		InitializeImages();\n"
"\n"
"	// cannot be null becasue is visible\n"
"	var child = Children[index];\n"
"	var image = document.images['folder'+index];\n"
"\n"
"	if( child.style.display == 'none' )\n"
"	{	image.src           = '_openblue.gif';\n"
"		child.style.display = '';\n"
"		Open = Open.substring(0, index) \n"
"		     + 'T' + Open.substring(index, SectionCount);\n"
"	}\n"
"	else\n"
"	{	image.src           = '_closeblue.gif';\n"
"		child.style.display = 'none';\n"
"		Open = Open.substring(0, index) \n"
"		     + 'F' + Open.substring(index, SectionCount);\n"
"	}\n"
"	document.cookie = 'contents=' + Open;\n"
"}\n"
"\n"
"// high light a folder\n"
"function MouseOver(index)\n"
"{\n"
"	if( ! ImagesInitialized )\n"
"		InitializeImages();\n"
"\n"
"	// cannot be null becasue is visible\n"
"	var child = Children[index];\n"
"	var image = document.images['folder'+index];\n"
"\n"
"	if( child.style.display == '' )\n"
"		image.src = '_openblue.gif';\n"
"	else	image.src = '_closeblue.gif';\n"
"}\n"
"\n"
"// remove high lighting\n"
"function MouseOut(index)\n"
"{\n"
"	if( ! ImagesInitialized )\n"
"		InitializeImages();\n"
"\n"
"	// cannot be null becasue is visible\n"
"	var child = Children[index];\n"
"	var image = document.images['folder'+index];\n"
"\n"
"	if( child.style.display == '' )\n"
"		image.src = '_open.gif';\n"
"	else	image.src = '_close.gif';\n"
"}\n"
;
// ======================================================================

static int SectionCount;

static void NextSection(SectionInfo *F, int level)
{	int i;

	char *number;
	char *title;
	
	while( F != NULL )
	{	SectionCount++;

		// ascii version of number for this section
		number = int2str(SectionCount);

		// start a new line and indent for this section
		FormatOutput("\n<br%s",
			Internal2Out("SelfTerminateCmd")
		);
		for(i = 0; i < 4 * level; i++) 
			ConvertOutputCh(' ', 1);

		title = NULL;
		if( F->children == NULL )
		{	// simple case of no children 
			HrefOutputPass1(F->tag, "", "false", "");

			// use title as linking text
			title = ConvertInternalString(F->title);
			OutputString(title);
			HrefEnd("\n");
		}
		else
		{	// folder selection opens view of this section
			FormatOutput(
				"<a onclick='Select(%s)'\n", 
				number
			);
			FormatOutput(
				"\tonmouseover='MouseOver(%s)'\n", 
				number
			);
			FormatOutput(
				"\tonmouseout='MouseOut(%s)'\n>", 
				number
			);
			FormatOutput(
				"<img src='_close.gif' name='folder%s'"
				" align='middle' />\n",
				number
			);

			// use title to describe this folder 
			// and make it part of the selectable section
			title = ConvertInternalString(F->title);
			FormatOutput("<u>%s</u>", title);

			// terminate folder selection
			OutputString("</a>\n");

			// identifier for children of this section
			FormatOutput(
				"\n<span id='children%s'>", 
				number
			);

			// begin the view of this section
			FormatOutput("\n<br%s",
				Internal2Out("SelfTerminateCmd")
			);

			// link to this section is first option in view
			for(i = 0; i < 4 * level; i++) 
				ConvertOutputCh(' ', 1);
			HrefOutputPass1(F->tag, "", "false", "");
			OutputString(title);
			HrefEnd("\n");

			// link to children follow (and are indented further)
			NextSection(F->children, level + 1);
			
			OutputString("</span>\n");

		}

		FreeMem(title);
		FreeMem(number);
		
		// next sibling of this section
		F = F->next;
	}
	return;
}

static void CopyImage(const char *dir, char *name)
{	char *file;

	file = StrCat(
		__FILE__,
		__LINE__,
		dir,
		name,
		NULL
	);
	copyfile(name, file);
	FreeMem(file);
}

void BrowserPass1(SectionInfo *browser)
{	FILE *Fp;
	SectionInfo *Root;
	char *file;
	char *tmp;
	char *s;
	char *number;
	int  i;
	const char *omhDir;

	assert( browser != NULL );
	assert( SectionCount == 0 );
	assert( ! PrintableOmhelp() );

	// directory where Omhelp is installed
	omhDir = OmhDir();
	assert( omhDir != NULL );

	CopyImage(omhDir, "_close.gif");
	CopyImage(omhDir, "_open.gif");
	CopyImage(omhDir, "_closeblue.gif");
	CopyImage(omhDir, "_openblue.gif");


	// Open the Pass One output file for this section
	file = strjoin(browser->tag, ".tmp");
	PushOutput(file);
	FreeMem(file);

	// Determine the root of the section tree
	Root = browser;
	while( Root->parent != NULL )
		Root = Root->parent;
	assert( Root->next == NULL && Root->previous == NULL );

	// title for this section
	OutputString("<center><b><big><big>\n");
	OutputString(browser->title);
	OutputString("\n</big></big></b></center>\n");
	
	// Start with the root of the tree
	SectionCount = 0;
	NextSection(Root, 0);

	// load Javascript at end of file so getElementById works
	FormatOutput(
		"<script type='text/javascript' src='%s.js'></script>\n",
		browser->tag
	);
	PopOutput();

	// Open the Pass One output file for this section
	file = strjoin(browser->tag, ".js");
	DirSep(file);
	Fp = fopen(file, "w");
	if( Fp == NULL )
		fatalerr("Cannot create a new ", file, " file\n", NULL);
	FreeMem(file);

	// replace 000000 with actual number of sections
	tmp = str_alloc(Javascript);
	s   = strstr(tmp, "000000");
	assert( s != NULL );
	for(i = 0; i < 6; i++)
		s[i] = ' ';

	assert(SectionCount <= 999999 );
	number = int2str(SectionCount);
	i = strlen(number);
	while(i)
	{	i--;
		s[i] = number[i];
	}
	fprintf(Fp, "%s", tmp);

	FreeMem(number);
	FreeMem(tmp);
	
	fclose(Fp);
}

