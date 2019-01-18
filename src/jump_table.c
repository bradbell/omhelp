/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2018 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin jump_table$$
$spell
$$

$section Pass Two Output of Jump Table for a Section$$

$head Syntax$$
$codei%jump_table(%Current%)%$$

$head Prototype$$
$srcfile%jump_table.c%
	0%// BEGIN_PROTOTYPE%// END_PROTOTYPE%1
%$$


$head Description$$
Output (to current output file)
the jump table for the current section.

$head Current$$
is the current section.

$end
*/
# include <stdlib.h>
# include <assert.h>
# include "jump_table.h"
# include "cross.h"
# include "strjoin.h"
# include "str_alloc.h"
# include "output.h"
# include "href.h"
# include "Internal2Out.h"
# include "convert.h"

// BEGIN_PROTOTYPE
void jump_table(SectionInfo *Current)
// END_PROTOTYPE
{
	// Create a jump table at the top to each heading in this page
	CrossReference  *C;
	const char      *head;
	int              i;
	//
	// cross reference for tag for this section
	C    = FindCrossReference(Current->tag, "");
	assert( C != NULL );
	//
	// first heading for this sections
	C    = NextCrossReference(C);
	head = "";
	//
	// Foreach heading.subheading cross reference in this section
	while(C != NULL )
	{	assert( C->head != NULL );

		// skip to start of this heading or subheading
		i = 0;
		while( (C->head[i] != '\0') & (head[i] == C->head[i]) )
			i++;
		//
		// linking text for this heading
		char *link_text;
		if( C->head[i] == '.' )
		{	// this is a subheading, linking text is only the sub-heading
			link_text = C->head + i + 1;
		}
		else
		{	// this is a heading
			head      = C->head;
			link_text = C->head;
		}

		// Each link is on a new line
		OutputString("\n<br");
		OutputString(Internal2Out("SelfTerminateCmd"));

		// indent the sub-hreading 5 non-breaking spaces
		if( link_text != C->head )
			OutputString("&#160;&#160;&#160;&#160;&#160;");

		// output the cross reference
		const char* external     = "false";
		const char* displayframe = "";
		HrefOutputPass2(C->tag, C->head, external, displayframe);

		// output linking text
		ConvertOutputString(link_text, 1);

		// end the cross reference
		HrefEnd("");

		// next cross reference
		C = NextCrossReference(C);
	}
}
