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
$begin relative$$
$spell
	Javascript
	js
	src
$$

$section Automatic Generated Links Relative to Current Section$$

$head Syntax$$
$syntax%void RelativeFrame(SectionInfo *%F%)
%$$
$syntax%void RelativeTable(SectionInfo *%F%)
%$$

$head Purpose$$
Creates the automatically generated links
(during the second pass), such as previous, next, up,
that are relative to the section $italic F$$.

$head RelativeFrame$$
This creates the file $syntax%%tag%_links.%ext%$$ containing the links.
where $italic tag$$ is equal to $syntax%%F%->tagLower%$$ and
$italic ext$$ is equal to $syntax%%Internal2Out("OutputExtension")%$$. 

$head RelativeTable$$
This creates a table, in the current output file, containing the links.
It also creates the Javascript file $syntax%%F->tagLower%.js%$$ and 
assumes that the $syntax%<head>%...%</head>%$$ for the current 
output file contains the command
$syntax%
	<script type='text/javascript' language='JavaScript' src='%tag%.js'>
%$$
where $italic tag$$ is $syntax%%F->tagLower%$$.

$contents%
	links.c
%$$

$end
--------------------------------------------------------------------------
*/

# define MAX_DEPTH          100

# include <assert.h>
# include <stdlib.h>

# include "relative.h"
# include "links.h"
# include "section.h"
# include "cross.h"
# include "style.h"
# include "main.h"
# include "allocmem.h"
# include "fatalerr.h"
# include "int2str.h"
# include "str_cat.h"
# include "automatic.h"

void RelativeFrame(SectionInfo *F)
{	SectionInfo    *S;
	SectionInfo    *List[MAX_DEPTH];
	CrossReference *C;
	char           Space[1000];
	int            nspace = 2;
	int            i;
	int            j;
	int            depth;
	char           *stylecmd;
	char           *head;
	char           *text;

	assert( 1000 > nspace * MAX_DEPTH ); 

	stylecmd = StyleCommand(F);
	BeginLinks(F->tag, "column", IconLink(), IconFile(), stylecmd);
	FreeMem(stylecmd);

	// start with location of this section in the tree
	depth       = 0;
	List[depth] = F;
	while( List[depth]->parent != NULL )
	{	if( depth >= MAX_DEPTH ) fatalomh(
			"Omhelp tree has over ",
			int2str(MAX_DEPTH),
			" branches from its root to a leaf",
			NULL
		);
		List[depth + 1] =  List[depth]->parent;
		depth++;
	}
	
	i = depth;
	while( i >= 0 )
	{
		for(j = 0; j < nspace * (depth - i); j++)
			Space[j] = ' ';
		Space[j] = '\0';

		S    = List[i];
		text = str_cat(Space, S->tag);
		AddLink(text, S->tag, "");
		FreeMem(text);

		i--;
	}	

	// siblings
	S          = F;
	while( S->previous != NULL )
		S = S->previous;

	if( S->next != NULL )
	{
		TitleLinks("Siblings");
		while( S != NULL )
		{	if( ! IsAutomaticSection(S) )
			{
				if( S != F )
					AddLink(S->tag, S->tag, "");
				else	AddLink(S->tag,     "", "");
			}
			S = S->next;
		}	
	}

	// children
	if( F->children != NULL )
	{
		TitleLinks("Children");
		S   = F->children;

		while( S != NULL )
		{	if( ! IsAutomaticSection(S) )
			{	if( S != F )
					AddLink(S->tag, S->tag, "");
				else	AddLink(S->tag,     "", "");
			}
			S = S->next;
		}	
	}

	// headings
	C = FindCrossReference(F->tag, "");
	assert( C != NULL );
	C = NextCrossReference(C);

	head = "";
	if( C != NULL )
	{
		TitleLinks("Headings");

		while( C != NULL )
		{	assert( C->head != NULL );

			i = 0;
			while( (head[i] != '0') 
			     & (C->head[i] != '0')
			     & (head[i] == C->head[i]) 
			) i++;

			if( C->head[i] == '.' )
			{
				text = str_cat("    ", C->head + i);
				AddLink(text, C->tag, C->head);
				FreeMem(text);
			}
			else
			{	AddLink(C->head, C->tag, C->head);
				head = C->head;
			}
			C = NextCrossReference(C);
		}
	}

	EndLinks();

}
