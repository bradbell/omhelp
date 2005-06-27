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
$begin FunRef$$
$spell
	Href
	tmp
$$

$section Function Reference Utilities$$
$index InsertFunRef$$
$index FunRefPass1$$

$table
$bold Syntax$$
$cend $syntax%InsertInFunRef(%tag%, %title%)%$$ $rend
$cend $syntax%FunRefPass1(%section%)%$$
$tend

$fend 20$$

$head Description$$
These routines manage the function reference table.
$syntax%

%tag%
%$$
The '\0' terminated character vector $italic tag$$ is the cross reference
tag for this function reference entry. 
This value will appear in alphabetic order in the function reference section.
$syntax%

%title%
%$$
The '\0' terminated character vector $italic title$$ is
text that will next to the corresponding value of $italic tag$$ 
in the function reference section.
$syntax%

%section%
%$$
The is a pointer to the $xref/SectionInfo/$$ record that
corresponds to the function reference section.
$syntax%

InsertInFunRef(%tag%, %title%)
%$$
This call inserts an entry in the function reference table.
These entries are accumulated until a call is made to 
$code FunRefPass1$$.
$syntax%

FunRefPass1(%section%)
%$$
This call creates the pass one version of the
function reference section in the file with root name 
$syntax//section/->tag/$$
and extension $code .tmp$$.
It is a Pass1 version because
the cross references use the HrefOutputPass1 format.
In addition, for the $italic letter$$
between $code A$$ and $code Z$$ that has function reference entries
starting with that letter: 
there a heading for that letter together with a
$syntax%
	<a name="%letter%"></a>
%$$
reference that points to the position of that letter in the function reference.
In addition, it is added to the list of cross references to this section.
$syntax%

FunRefFree()
%$$
The $code InsertInFunRef$$ routine uses 
$xref/AllocMem/$$ to store information that is used by
$code FunRefPass1$$.
The routine $code FunRefFree$$ frees all this temporary memory.


$end
*/

# include <string.h>
# include <assert.h>
# include <ctype.h>

# include "cross.h"
# include "funref.h"
# include "allocmem.h"
# include "str_alloc.h"
# include "output.h"
# include "href.h"
# include "convert.h"
# include "section.h"
# include "main.h"
# include "str_cat.h"
# include "Internal2Out.h"

# ifndef WIN32
# define stricmp strcasecmp 
# endif


// current function reference entries
typedef struct  funRefEntry {
	char                 *tag;
	char               *title;
	struct funRefEntry  *next;
} FunRefEntry;

FunRefEntry *FunRef = NULL;



void InsertInFunRef(char *tag, char *title)
{
	FunRefEntry *E, *L, *N;

	// put new entry at front of list
	E         = (FunRefEntry *) AllocMem(1, sizeof(FunRefEntry));
	E->next   = FunRef;
	E->tag    = str_alloc(tag);
	E->title  = str_alloc(title);
	
	// move E to proper place in index 
	if( FunRef == NULL )
		FunRef = E;
	else if( stricmp(tag, FunRef->tag) < 0 )
		FunRef = E;
	else
	{	L  = FunRef;
		N  = FunRef->next; 
		while( N != NULL && stricmp(tag, N->tag) >= 0 ) 
		{	L = N;
		    	N = N->next;
		}
		L->next = E;
		E->next = N;
	}
	return;
}

void FunRefPass1(SectionInfo *section)
{	
	char    *filename;
	char         *tag;
	char       *title;

	char    letter[2];

	char      heading;
	char           ch;

	FunRefEntry *Current;
	
	// open output file
	filename = str_cat(section->tag, ".tmp");
	PushOutput(filename);
	FreeMem(filename);

	// title for this section
	OutputString("<center><b><big><big>");
	if( PrintableOmhelp() )
	{
		char *printid;
		printid = SectionNumber(section);
		assert( printid[0] != '\0' );
		FormatOutput("<a name=\"%s\">", printid);
		OutputString(printid);
		OutputString(": ");
		OutputString(section->title);
		OutputString("</a>\n");
		FreeMem(printid);
	}
	else	OutputString(section->title);
	OutputString("</big></big></b></center>\n");

	OutputString("<table>\n");
	OutputString("<tr valign=\"top\"><td>\n");

	heading = 'A';
	Current = FunRef;
	while( Current != NULL )
	{	
		tag     = Current->tag;
		title   = Current->title;

		ch      = toupper(tag[0]);
		while( ch > heading && heading <= 'Z' )
			heading++;
		if( ch == heading && heading <= 'Z' )
		{	letter[0] = heading;
			letter[1] = '\0';
			FormatOutput("\n<b><big><a name=\"%s\">", letter);
			FormatOutput("%s</a></big></b>", letter);
			OutputString(" </td><td> ");
			OutputString(" </td></tr><tr valign=\"top\"><td>\n");
			DefineCrossReference(
				section->tag, letter, "", 1, letter);
			heading++;
		}
		
		//  output the cross reference tag
		HrefOutputPass1(tag, "", "false", "");
		OutputString(tag);
		HrefEnd("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));

		// terminate this column
		OutputString(" </td><td> ");

		// output the title
		ConvertOutputString(title, 0);

		// terminate the row
		OutputString(" </td></tr><tr valign=\"top\"><td>\n");

		// next function reference entry
		Current  = Current->next;
		
	}

	OutputString("</td></tr></table>\n");
	PopOutput();
}

void FunRefFree()
{	FunRefEntry *Next;

	while( FunRef != NULL )
	{	Next = FunRef->next;
	
		// free memory for this entry
		FreeMem(FunRef->tag);
		FreeMem(FunRef->title);
		FreeMem(FunRef);

		FunRef = Next;
	}
	return;
}
