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
$begin AutomaticAppendSection$$

$mindex add automatic section tree$$
$section Add an Automatically Generated Section to Section Tree$$

$table
$bold Syntax$$
$cnext
$syntax/AutomaticAppendSection(/parent/, /tag/, /title/, /letterHeadings/)/$$
$tend

$fend 20$$

$head Description$$
This call adds a section to the section tree.

$head parent$$
The argument $italic parent$$
$xref/SectionInfo//SectionInfo/$$ pointer
that specifies the parent of the section being added.
This cannot be NULL, but $syntax//parent/->children/$$
can be NULL.
The style of the parent section is copied into the new section.

$head tag$$
The argument $italic tag$$ is a $code '\0'$$
terminated character vector that specifies the cross reference
tag for the section that is appended.
A $xref/CrossReference//cross reference/$$ is defined pointing to this section
with tag equal to $italic tag$$ and
heading equal to the empty string.

$head title$$
The argument $italic title$$ is a $code '\0'$$
terminated character vector that specifies the
$xref/SectionInfo//section title/$$
for the section that is added to the tree.

$head letterHeadings$$
The argument $italic letterHeadings$$ is either zero or one.
If it is one, for each capital letter in the alphabet,
a cross references
is defined with tag equal to $italic tag$$,
heading equal to the letter,
frame equal to 1,
and file equal to the empty string.
Thus it is assumed that frame one of the corresponding section
will contain a heading for each capital letter in the alphabet.

$end
==============================================================================
$begin IsAutomaticSection$$

$section Determine if a Section is Automatically Generated$$

$table
$bold Syntax$$
$cnext $syntax/IsAutomaticSection(/section/)/$$
$tend

$fend 20$$

$head Description$$
Returns one, if $italic section/$$ is one of the sections generated
by a previous call to $xref/AutomaticAppendSection/$$,
and returns zero otherwise.


$head section$$
The argument $italic section$$ is a
$xref/SectionInfo//SectionInfo/$$ pointer.
The value $italic section$$ or $syntax//section/->tag/$$ can be NULL,
in which case zero is returned.

$end
==============================================================================
$begin AutomaticTag$$

$section Get List of Automatically Generated Sections$$

$table
$bold Syntax$$
$cnext $syntax/AutomaticTag(/i/)/$$
$tend

$fend 20$$

$head Description$$
Returns a $code '\0'$$ character vector pointing to
the $italic tag$$ for the $math% i+1 %$$ call to $code AutomaticAppendSection$$.
If $italic i$$ is greater than or equal to the number of calls to
$code AutomaticAppendSection$$, $code AutomaticTag$$ returns NULL.

$end
==============================================================================
*/

# include <string.h>
# include <assert.h>

# include "automatic.h"
# include "section.h"
# include "str_alloc.h"
# include "cross.h"
# include "head.h"
# include "strjoin.h"
# include "allocmem.h"

# define MAX_AUTOMATIC 6
# define MAX_LENGTH    100

static char Tag[MAX_AUTOMATIC][MAX_LENGTH];
static int  Number = 0;

int IsAutomaticSection(SectionInfo *section)
{	int i;
	if( section == NULL )
		return 0;
	if( section->tag == NULL )
		return 0;
	for(i = 0; i < Number; i++ )
		if( strcmp(section->tag, Tag[i]) == 0 )
			return 1;
	return 0;
}
const char *AutomaticTag(int i)
{	if( i < Number )
		return Tag[i];
	else	return NULL;
}


void AutomaticAppendSection(
	SectionInfo *parent,
	const char *tag,
	const char *title,
	int letterHeadings)
{
	SectionInfo    *T;
	SectionInfo    *S;
	CrossReference *C;
	char           *inputfile = NULL;
	char           *sectionid;
	char           *printid;

	// add this entry to list of automatically generated sections
	assert( strlen(tag) < MAX_LENGTH );
	assert( Number < MAX_AUTOMATIC );
	strcpy( Tag[Number], tag );
	Number++;


	// find the end of the list at second level
	assert( parent != NULL );

	// find top of the section tree
	T = parent;
	while( T->parent != NULL )
		T = T->parent;

	if( parent->children == NULL )
	{	parent->children = SectionInfoNew(T, inputfile);
		S                     = parent->children;
	}
	else
	{
		S = parent->children;
		while(S->next != NULL)
			S = S->next;

		// create a new section at end of list at top level
		S->next           = SectionInfoNew(T, inputfile);
		S->next->previous = S;
		S                 = S->next;
	}

	// use default style values for this section
	SectionDefaultStyle(S, parent);

	// fill in parent for this section
	S->parent = parent;

	// fill in fields for this file
	SectionSetTag(S, tag);
	S->title    = str_alloc(title);

	// add to list of cross references
	sectionid = SectionNumber(S);
	C         = DefineCrossReference(tag, "", "", 0, sectionid);
	assert( C != NULL );

	// Add automatic headings for index and function reference
	if( letterHeadings )
	{

		char head[2];
		char ch;

		InitializeHeading();

		head[1] = '\0';
		ch   = 'A';
		while( ch <= 'Z' )
		{	head[0] = ch;
			SetHeading(head);
			printid = strjoin(sectionid, HeadingAndSubPrintId() );
			DefineCrossReference(tag, head, "", 1, printid);
			++ch;
			FreeMem(printid);
		}
		InitializeHeading();
	}


	FreeMem(sectionid);
}
