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
# include <stdio.h>

# include "str_alloc.h"
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
# include "output.h"
# include "Internal2Out.h"
# include "Url.h"
# include "href.h"


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
void RelativeTable(SectionInfo *F)
{
	SectionInfo     *S;
	char            *name;
	char            *url;
	FILE            *javascript_fp;
	const char      *icon_link = IconLink();
	const char      *icon_file = IconFile();
	const char      *script;
	const char      *head;
	int              i;
	CrossReference  *C;

	// The HTML code &#62; is used for the greater than symbol

	// Open the Javascript file for these drop down links.
	name = StrCat(
		__FILE__,
		__LINE__,
		F->tagLower,
		"_link.js",
		NULL
	);
	javascript_fp = fopen(name, "w");
	if( javascript_fp == NULL ) fatalerr(
		"Can not create the output file ",
		name,
		NULL
	);
	FreeMem(name);

	// -----------------------------------------------------------------
	// Begin table that contains the links in a single row
	OutputString("<table><tr>\n");

	// Icon --------------------------------------------------------- 
	if( icon_link != NULL )
	{	OutputString("<td>\n");
		if( icon_link[0] != '\0' )
		{	FormatOutput(
				"<a href=\"%s\" target=\"_top\">", icon_link
			);
			FormatOutput(
				"<img border=\"0\" src=\"%s\"", icon_file
			);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("</a>\n");
		}
		else
		{	FormatOutput(
				"<img border=\"0\" src=\"%s\"", icon_file
			);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("\n");
		}
		OutputString("</td>\n");
	}

	// Up ------------------------------------------------------------
	OutputString("<td>\n");
	OutputString(
		"<select onchange='choose_up(this.selectedIndex)'>\n"
	); 
	OutputString("<option>Up -&#62;</option>\n");
	fprintf(javascript_fp, "var list_up = [\n");
	S = F;
	while(S != NULL)
	{	FormatOutput( "<option>%s</option>\n", S->tag);
		url = Url(S->tag, "", "false");
		fprintf(javascript_fp, "'%s'", url);
		FreeMem(url);
		S = S->parent;
		if( S != NULL )
			fprintf(javascript_fp, ",\n");
		else	fprintf(javascript_fp, "\n];\n");
	}	
	OutputString("</select>\n</td>\n"); 

	// Sibling -------------------------------------------------------
	OutputString("<td>\n");
	OutputString(
		"<select onchange='choose_sibling(this.selectedIndex)'>\n"
	); 
	OutputString("<option>Sibling -&#62;</option>\n");
	fprintf(javascript_fp, "var list_sibling = [\n");
	S = F;
	while(S->previous != NULL )
		S = S->previous;
	while( IsAutomaticSection(S) )
		S = S->next;
	while(S != NULL)
	{	FormatOutput( "<option>%s</option>\n", S->tag);
		url = Url(S->tag, "", "false");
		fprintf(javascript_fp, "'%s'", url);
		FreeMem(url);
		S = S->next;
		while( S != NULL && IsAutomaticSection(S) )
			S = S->next;
		if( S != NULL )
			fprintf(javascript_fp, ",\n");
		else	fprintf(javascript_fp, "\n];\n");
	}	
	OutputString("</select>\n</td>\n"); 

	// Down ---------------------------------------------------------
	S = F->children;
	if( S != NULL )
	{	OutputString("<td>\n");
		OutputString(
		"<select onchange='choose_down(this.selectedIndex)'>\n"
		); 
		OutputString("<option>Down -&#62;</option>\n");
		fprintf(javascript_fp, "var list_down = [\n");
		while(S->previous != NULL )
			S = S->previous;
		while( IsAutomaticSection(S) )
			S = S->next;
		while(S != NULL)
		{	FormatOutput( "<option>%s</option>\n", S->tag);
			url = Url(S->tag, "", "false");
			fprintf(javascript_fp, "'%s'", url);
			FreeMem(url);
			S = S->next;
			while( S != NULL && IsAutomaticSection(S) )
				S = S->next;
			if( S != NULL )
				fprintf(javascript_fp, ",\n");
			else	fprintf(javascript_fp, "\n];\n");
		}
		OutputString("</select>\n</td>\n"); 
	}	

	// Across ---------------------------------------------------------
	OutputString("<td>\n");
	OutputString(
		"<select onchange='choose_across(this.selectedIndex)'>\n"
	); 
	OutputString("<option>Across -&#62;</option>\n");
	fprintf(javascript_fp, "var list_across = [\n");
	i = 0;
	while( AutomaticTag(i) != NULL )
	{	const char *tag = AutomaticTag(i);
		while( *tag == '_' )
			tag++;
		FormatOutput( "<option>%s</option>\n", tag);
		url = Url(AutomaticTag(i), "", "false");
		fprintf(javascript_fp, "'%s'", url);
		FreeMem(url);
		i++;
		if( AutomaticTag(i) != NULL )
			fprintf(javascript_fp, ",\n");
		else	fprintf(javascript_fp, "\n];\n");
	}
	OutputString("</select>\n</td>\n"); 

	// Previous and Next ---------------------------------------------
	OutputString("<td>\n");
	OutputString("<table><tr><td>\n");
	S = SectionReadPrevious(F);
	if( S == NULL )
		OutputString("prev");
	else
	{	HrefOutputPass2(S->tag, "", "false", "");
		OutputString("prev");
		HrefEnd("\n");
	}
	OutputString("</td><td>");
	S = SectionReadNext(F);
	if( S == NULL )
		OutputString("next");
	else
	{	HrefOutputPass2(S->tag, "", "false", "");
		OutputString("next");
		HrefEnd("\n");
	}
	OutputString("</td></tr></table>\n");
	OutputString("</td>");

	// Current ----------------------------------------------------------
	C = FindCrossReference(F->tag, "");
	assert( C != NULL );
	C = NextCrossReference(C);

	head = "";
	if( C != NULL )
	{	OutputString("<td>\n");
		OutputString(
		"<select onchange='choose_current(this.selectedIndex)'>\n"
		); 
		OutputString("<option>Current -&#62;</option>\n");
		fprintf(javascript_fp, "var list_current = [\n");

		while( C != NULL )
		{	assert( C->head != NULL );

			i = 0;
			while( (head[i] != '0') 
			     & (C->head[i] != '0')
			     & (head[i] == C->head[i]) 
			) i++;

			if( C->head[i] == '.' )
				name = str_cat("---.", C->head + i);
			else
			{	name = str_alloc(C->head);
				head = C->head;
			}
			FormatOutput( "<option>%s</option>\n", name);
			FreeMem(name);
			//
			url = Url(C->tag, C->head, "false");
			fprintf(javascript_fp, "'%s'", url);
			FreeMem(url);
			C = NextCrossReference(C);
			if( C != NULL )
				fprintf(javascript_fp, ",\n");
			else	fprintf(javascript_fp, "\n];\n");
		}
		OutputString("</select>\n</td>\n"); 
	}

	// -----------------------------------------------------------------
	// End table that contains the links
	OutputString("</tr></table><br");
	OutputString(Internal2Out("SelfTerminateCmd"));
	OutputString("\n");

	// End javascript file
	script =
	"function choose_up(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_up[index-1];\n"
	"}\n"
	"function choose_sibling(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_sibling[index-1];\n"
	"}\n"
	"function choose_down(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_down[index-1];\n"
	"}\n"
	"function choose_across(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_across[index-1];\n"
	"}\n"
	"function choose_current(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_current[index-1];\n"
	"}\n"
	;
	fprintf(javascript_fp, script);
	fclose(javascript_fp);
}
