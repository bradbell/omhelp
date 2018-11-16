/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2018 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

/*
$begin relative$$
$spell
	Javascript
	js
	src
$$

$section Automatic Generated Links Relative to Current Section$$

$head Syntax$$
$codei%void RelativeFrame(SectionInfo *%This%)
%$$
$codei%void RelativeTable(SectionInfo *%This%)
%$$

$head Purpose$$
Creates the automatically generated links
(during the second pass), such as previous, next, up,
that are relative to the section $icode This$$.

$head RelativeFrame$$
This creates the file $icode%tag%_links.%ext%$$ containing the links.
where $icode tag$$ is equal to $icode%This%->tagLower%$$ and
$icode ext$$ is equal to $icode%Internal2Out("OutputExtension")%$$.

$head RelativeTable$$
This creates a table, in the current output file, containing the links.
It also creates the Javascript file
$codei%
	_%This->tagLower%_%ext%.js
%$$
and assumes that the $codei%<head>%...%</head>%$$ for the current
output file contains the command
$codei%
<script type='text/javascript' language='JavaScript' src='%tag%_%ext%.js'>
%$$
where $icode tag$$ is $icode%This->tagLower%$$ and
$icode ext$$ is $code Internal2Out("OutputExtension")$$
with out the leading "." character.

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
# include <string.h>
# include <ctype.h>

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
# include "strjoin.h"
# include "automatic.h"
# include "output.h"
# include "Internal2Out.h"
# include "url.h"
# include "href.h"
# include "AutoTag.h"
# include "convert.h"

static void OutputOption(const char *name)
{	// should option name be preformatted ?
	int pre = 0;

	OutputString("<option>");
	ConvertOutputString(name, pre);
	OutputString("</option>\n");

	return;
}


static void WriteJavascriptString(FILE *fp, const char *s)
{	char single_quote = '\'';
	char back_slash   = '\\';
	fputc(single_quote, fp);
	while( *s != '\0' )
	{	if( *s == single_quote )
			fputc(back_slash, fp);
		fputc(*s++, fp);
	}
	fputc(single_quote, fp);
}

void RelativeFrame(SectionInfo *This)
{	SectionInfo    *F;
	SectionInfo    *S;
	SectionInfo    *Up[MAX_DEPTH];
	CrossReference *C;
	char           Space[1000];
	int            nspace = 2;
	int            i;
	int            j;
	int            depth;
	int            index;
	int            number;
	int            titled;
	char           *stylecmd;
	char           *head;
	char           *text;

	enum navigateType nav_type;
	const char    *label;

	// preformat output labels ?
	int              pre = 0;

	assert( 1000 > nspace * MAX_DEPTH );

	stylecmd = StyleCommand(This);
	BeginLinks(This->tag, "column", ImageLink(), ImageFile(), stylecmd);
	FreeMem(stylecmd);

	// =================================================================
	titled = 0;
	number = This->navigate.number;
	for(index = 0; index < number; index++)
	{
		// simple case where using label explicitly
		label    = This->navigate.item[index].label;

		// check for case where using cross reference tag for _up_i
		if( strcmp(label, "_jump_table") != 0 && label[0] == '_' )
		{	assert( strncmp(label, "_up_", 4) == 0 );
			assert( strlen(label) == 5 );
			assert( isdigit((int) label[4]) );
			i = atoi(label + 4);
			F = This;
			while(i--)
			{	if( F != NULL )
					F = F->parent;
			}
			if( F != NULL )
				label = F->tag;
			else	label = NULL;
		}

		// simple case where using this section
		nav_type = This->navigate.item[index].nav_type;
		F        = This;

		// check for case where links are relative to parent
		switch( nav_type )
		{	case DOWN_UP_0_nav:
			i = 0;
			break;
			case DOWN_UP_1_nav:
			i = 1;
			break;
			case DOWN_UP_2_nav:
			i = 2;
			break;
			case DOWN_UP_3_nav:
			i = 3;
			break;
			case DOWN_UP_4_nav:
			i = 4;
			break;
			case DOWN_UP_5_nav:
			i = 5;
			break;
			case DOWN_UP_6_nav:
			i = 6;
			break;
			case DOWN_UP_7_nav:
			i = 7;
			break;
			case DOWN_UP_8_nav:
			i = 8;
			break;
			case DOWN_UP_9_nav:
			i = 9;
			break;

			default:
			i = -1;
			break;
		}
		if( i != -1 )
		{	while(i--)
			{	if( F != NULL )
					F = F->parent;
			}
		}

	// undo one level of indentation (need the space)
	if( F != NULL && label != NULL ) switch( nav_type )
	{
		// Contents ------------------------------------------------
		case CONTENT_nav:
		if( titled )
		{	OutputString("<hr");
			OutputString(Internal2Out("SelfTerminateCmd"));
		}
		titled = 0;
		HrefOutputPass2(CONTENTS_TAG, "", "false", "");
		ConvertOutputString(label, pre);
		HrefEnd("\n");
		OutputString("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");
		break;

		// Previous ------------------------------------------------
		case PREV_nav:
		if( titled )
		{	OutputString("<hr");
			OutputString(Internal2Out("SelfTerminateCmd"));
		}
		titled = 0;
		S = SectionReadPrevious(F);
		if( S == NULL )
			ConvertOutputString(label, pre);
		else
		{	HrefOutputPass2(S->tag, "", "false", "");
			ConvertOutputString(label, pre);
			HrefEnd("\n");
		}
		OutputString("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");
		break;

		// Next -----------------------------------------------------
		case NEXT_nav:
		if( titled )
		{	OutputString("<hr");
			OutputString(Internal2Out("SelfTerminateCmd"));
		}
		titled = 0;
		S = SectionReadNext(F);
		if( S == NULL )
			ConvertOutputString(label, pre);
		else
		{	HrefOutputPass2(S->tag, "", "false", "");
			ConvertOutputString(label, pre);
			HrefEnd("\n");
		}
		OutputString("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");
		break;

		// Top -----------------------------------------------------
		case TOP_nav:
		if( titled )
		{	OutputString("<hr");
			OutputString(Internal2Out("SelfTerminateCmd"));
		}
		S = F;
		while( S->parent != NULL )
			S = S->parent;
		titled = 0;
		assert( S != NULL );
		HrefOutputPass2(S->tag, "", "false", "");
		ConvertOutputString(label, pre);
		HrefEnd("\n");
		OutputString("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");
		break;

		// Up ------------------------------------------------------
		case UP_nav:
		TitleLinks(label);
		titled        = 1;
		depth         = 1;
		Up[depth-1]   = F;
		while( Up[depth-1]->parent != NULL )
		{	if( depth >= MAX_DEPTH ) fatalomh(
				"Omhelp tree has over ",
				int2str(MAX_DEPTH),
				" branches from its root to a leaf",
				NULL
			);
			Up[depth] =  Up[depth-1]->parent;
			depth++;
		}

		i = depth;
		while( i > 0 )
		{	i--;
			for(j = 0; j < nspace * (depth - i); j++)
				Space[j] = ' ';
			Space[j] = '\0';

			S    = Up[i];
			text = strjoin(Space, S->tag);
			AddLink(text, S->tag, "");
			FreeMem(text);
		}
		break;

		// Siblings ------------------------------------------------
		case SIBLING_nav:
		TitleLinks(label);
		titled     = 1;
		S          = F;
		while( S->previous != NULL )
			S = S->previous;

		if( S->next != NULL )
		{
			while( S != NULL )
			{	if( ! IsAutomaticSection(S) )
					AddLink(S->tag, S->tag, "");
				S = S->next;
			}
		}
		break;

		// Down ---------------------------------------------------
		case DOWN_nav:
		case DOWN_UP_0_nav:
		case DOWN_UP_1_nav:
		case DOWN_UP_2_nav:
		case DOWN_UP_3_nav:
		case DOWN_UP_4_nav:
		case DOWN_UP_5_nav:
		case DOWN_UP_6_nav:
		case DOWN_UP_7_nav:
		case DOWN_UP_8_nav:
		case DOWN_UP_9_nav:
		TitleLinks(label);
		titled = 1;
		if( F->children != NULL )
		{
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
		break;

		// Current --------------------------------------------------
		case CURRENT_nav:
		// If label == _jump_table, the links to the heading and sub-headings
		// for this section are placed in a jump table above the section title.
		if( strcmp(label, "_jump_table") == 0 )
			break;

		TitleLinks(label);
		titled = 1;
		C = FindCrossReference(F->tag, "");
		assert( C != NULL );
		C = NextCrossReference(C);

		head = "";
		while( C != NULL )
		{	assert( C->head != NULL );

			i = 0;
			while( (head[i] != '0')
			     & (C->head[i] != '0')
			     & (head[i] == C->head[i])
			) i++;

			if( C->head[i] == '.' )
			{
				text = strjoin("    ", C->head + i);
				AddLink(text, C->tag, C->head);
				FreeMem(text);
			}
			else
			{	AddLink(C->head, C->tag, C->head);
				head = C->head;
			}
			C = NextCrossReference(C);
		}
		break;

		default:
		break;
	}
	}
	// =================================================================

	EndLinks();

}
void RelativeTable(SectionInfo *This)
{
	SectionInfo     *F;
	SectionInfo     *S;
	SectionInfo     *Up[MAX_DEPTH];
	char            *list_name[MAX_NAVIGATE];
	char            *name;
	char            *url;
	FILE            *javascript_fp;
	const char      *image_link = ImageLink();
	const char      *image_file = ImageFile();
	const char      *format;
	const char      *head;
	const char      *ext;
	const char      *label;
	char            *tmp;
	int              number;
	int              index;
	int              i;
	int              depth;
	CrossReference  *C;
	enum navigateType nav_type;

	// preformat output labels ?
	int              pre = 0;

	// output extension with out leading dot
	ext = Internal2Out("OutputExtension");
	assert( *ext == '.' );
	ext++;

	// Open the Javascript file for these drop down links.
	name = StrCat(
		__FILE__,
		__LINE__,
		"_",
		This->tagLower,
		"_",
		ext,
		".js",
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
	if( image_link != NULL )
	{	OutputString("<td>\n");
		if( image_link[0] != '\0' )
		{	FormatOutput(
				"<a href=\"%s\" target=\"_top\">", image_link
			);
			FormatOutput(
				"<img border=\"0\" src=\"%s\"", image_file
			);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("</a>\n");
		}
		else
		{	FormatOutput(
				"<img border=\"0\" src=\"%s\"", image_file
			);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("\n");
		}
		OutputString("</td>\n");
	}

	// =================================================================
	//
	// number of relative navigation types for this section
	number = This->navigate.number;
	assert( number <= MAX_NAVIGATE );
	//
	// is there CURRENT_nav type for this section
	for(index = 0; index < number; index++)
	{	char digit[] = { '0', '\0' };

		// simple case where using label explicitly
		label    = This->navigate.item[index].label;

		// check for case where using cross reference tag for _up_i
		if( strcmp(label, "_jump_table") != 0 && label[0] == '_' )
		{	assert( strncmp(label, "_up_", 4) == 0 );
			assert( strlen(label) == 5 );
			assert( isdigit((int) label[4]) );
			i = atoi(label + 4);
			F = This;
			while(i--)
			{	if( F != NULL )
					F = F->parent;
			}
			if( F != NULL )
				label = F->tag;
			else	label = NULL;
		}

		// simple case where using this section
		nav_type = This->navigate.item[index].nav_type;
		F        = This;

		// check for case where links are relative to parent
		switch( nav_type )
		{	case DOWN_UP_0_nav:
			i = 0;
			break;
			case DOWN_UP_1_nav:
			i = 1;
			break;
			case DOWN_UP_2_nav:
			i = 2;
			break;
			case DOWN_UP_3_nav:
			i = 3;
			break;
			case DOWN_UP_4_nav:
			i = 4;
			break;
			case DOWN_UP_5_nav:
			i = 5;
			break;
			case DOWN_UP_6_nav:
			i = 6;
			break;
			case DOWN_UP_7_nav:
			i = 7;
			break;
			case DOWN_UP_8_nav:
			i = 8;
			break;
			case DOWN_UP_9_nav:
			i = 9;
			break;

			default:
			i = -1;
			break;
		}
		if( i != -1 )
		{	digit[0] = (char) ('0' + i);
			while(i--)
			{	if( F != NULL )
					F = F->parent;
			}
		}
	// ---------------------------------------------
	// undo one level of indentation (need the space)
	// ---------------------------------------------
	if( F == NULL || label == NULL )
		list_name[index] = NULL;
	else switch( nav_type )
	{
		// Contents -----------------------------------------------
		case CONTENT_nav:
		list_name[index] = NULL;
		OutputString("<td>\n");
		HrefOutputPass2(CONTENTS_TAG, "", "false", "");
		ConvertOutputString(label, pre);
		HrefEnd("\n");
		OutputString("</td>\n");
		break;

		// Previous -------------------------------------------------
		case PREV_nav:
		list_name[index] = NULL;
		OutputString("<td>");
		S = SectionReadPrevious(F);
		if( S == NULL )
		ConvertOutputString(label, pre);
		else
		{	HrefOutputPass2(S->tag, "", "false", "");
			ConvertOutputString(label, pre);
			HrefEnd("\n");
		}
		OutputString("</td>");
		break;

		// Next ------------------------------------------------------
		case NEXT_nav:
		list_name[index] = NULL;
		OutputString("<td>");
		S = SectionReadNext(F);
		if( S == NULL )
			ConvertOutputString(label, pre);
		else
		{	HrefOutputPass2(S->tag, "", "false", "");
			ConvertOutputString(label, pre);
			HrefEnd("\n");
		}
		OutputString("</td>");
		break;

		// Top -----------------------------------------------------
		case TOP_nav:
		list_name[index] = NULL;
		OutputString("<td>");
		S = F;
		while( S->parent != NULL )
			S = S->parent;
		assert( S != NULL );
		HrefOutputPass2(S->tag, "", "false", "");
		ConvertOutputString(label, pre);
		HrefEnd("\n");
		OutputString("</td>");
		break;

		// Up -------------------------------------------------------
		case UP_nav:
		list_name[index] = strjoin("up", digit);
		depth       = 1;
		Up[depth-1] = F;
		while( Up[depth-1]->parent != NULL )
		{	if( depth >= MAX_DEPTH ) fatalomh(
				"Omhelp tree has over ",
				int2str(MAX_DEPTH),
				" branches from its root to a leaf",
				NULL
			);
			Up[depth] =  Up[depth-1]->parent;
			depth++;
		}
		OutputString("<td>\n");
		FormatOutput(
			"<select onchange='choose_%s(this)'>\n",
			list_name[index]
		);
		tmp = strjoin(label, "->");
		OutputOption(tmp);
		FreeMem(tmp);
		fprintf(javascript_fp, "var list_%s = [\n", list_name[index]);
		i = depth;
		while( i > 0 )
		{	i--;
			S = Up[i];
			OutputOption(S->tag);
			url = Url(S->tag, "", "false");
			WriteJavascriptString(javascript_fp, url);
			FreeMem(url);
			if( i > 0 )
				fprintf(javascript_fp, ",\n");
			else	fprintf(javascript_fp, "\n];\n");
		}
		OutputString("</select>\n</td>\n");
		break;

		// Sibling ---------------------------------------------------
		case SIBLING_nav:
		list_name[index] = strjoin("sibling", digit);
		OutputString("<td>\n");
		FormatOutput(
			"<select onchange='choose_%s(this)'>\n",
			list_name[index]
		);
		tmp = strjoin(label, "->");
		OutputOption(tmp);
		FreeMem(tmp);
		fprintf(javascript_fp, "var list_%s = [\n", list_name[index]);
		S = F;
		while(S->previous != NULL )
			S = S->previous;
		while( IsAutomaticSection(S) )
			S = S->next;
		while(S != NULL)
		{	OutputOption(S->tag);
			url = Url(S->tag, "", "false");
			WriteJavascriptString(javascript_fp, url);
			FreeMem(url);
			S = S->next;
			while( S != NULL && IsAutomaticSection(S) )
				S = S->next;
			if( S != NULL )
				fprintf(javascript_fp, ",\n");
			else	fprintf(javascript_fp, "\n];\n");
		}
		OutputString("</select>\n</td>\n");
		break;

		// Down ------------------------------------------------------
		case DOWN_nav:
		case DOWN_UP_0_nav:
		case DOWN_UP_1_nav:
		case DOWN_UP_2_nav:
		case DOWN_UP_3_nav:
		case DOWN_UP_4_nav:
		case DOWN_UP_5_nav:
		case DOWN_UP_6_nav:
		case DOWN_UP_7_nav:
		case DOWN_UP_8_nav:
		case DOWN_UP_9_nav:
		list_name[index] = strjoin("down", digit);
		S = F->children;
		if( S == NULL )
		{	OutputString("<td>");
			ConvertOutputString(label, pre);
			OutputString("</td>\n");
		}
		else
		{	OutputString("<td>\n");
			FormatOutput(
				"<select onchange='choose_%s(this)'>\n",
				list_name[index]
			);
			tmp = strjoin(label, "->");
			OutputOption(tmp);
			FreeMem(tmp);
			fprintf(javascript_fp,
				"var list_%s = [\n", list_name[index]
			);
			while(S->previous != NULL )
				S = S->previous;
			while( IsAutomaticSection(S) )
				S = S->next;
			while(S != NULL)
			{	OutputOption(S->tag);
				url = Url(S->tag, "", "false");
				WriteJavascriptString(javascript_fp, url);
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
		break;

		// Across ----------------------------------------------------
		case ACROSS_nav:
		list_name[index] = strjoin("across", digit);
		OutputString("<td>\n");
		FormatOutput(
			"<select onchange='choose_%s(this)'>\n",
			list_name[index]
		);
		tmp = strjoin(label, "->");
		OutputOption(tmp);
		FreeMem(tmp);
		fprintf(javascript_fp, "var list_%s = [\n", list_name[index]);
		i = 0;
		while( AutomaticTag(i) != NULL )
		{	const char *tag = AutomaticTag(i);
			while( *tag == '_' )
				tag++;
			OutputOption(tag);
			url = Url(AutomaticTag(i), "", "false");
			WriteJavascriptString(javascript_fp, url);
			FreeMem(url);
			i++;
			if( AutomaticTag(i) != NULL )
				fprintf(javascript_fp, ",\n");
			else	fprintf(javascript_fp, "\n];\n");
		}
		OutputString("</select>\n</td>\n");
		break;

		// Current ---------------------------------------------------
		case CURRENT_nav:
		// If label == _jump_table, the links to the heading and sub-headings
		// for this section are placed in a jump table above the section title.
		list_name[index] = NULL;
		if( strcmp(label, "_jump_table") == 0 )
			break;
		//
		list_name[index] = strjoin("current", digit);
		C = FindCrossReference(F->tag, "");
		assert( C != NULL );
		C = NextCrossReference(C);

		head = "";
		if( C == NULL )
		{	OutputString("<td>");
			ConvertOutputString(label, pre);
			OutputString("</td>\n");
		}
		else
		{	OutputString("<td>\n");
			FormatOutput(
				"<select onchange='choose_%s(this)'>\n",
				list_name[index]
			);
			tmp = strjoin(label, "->");
			OutputOption(tmp);
			FreeMem(tmp);
			fprintf(javascript_fp,
				"var list_%s = [\n", list_name[index]
			);

			while( C != NULL )
			{	assert( C->head != NULL );

				i = 0;
				while(
					(head[i] != '0')
					& (C->head[i] != '0')
					& (head[i] == C->head[i])
				) i++;

				if( C->head[i] == '.' )
					name = strjoin("---.", C->head + i);
				else
				{	name = str_alloc(C->head);
					head = C->head;
				}
				OutputOption(name);
				FreeMem(name);
				//
				url = Url(C->tag, C->head, "false");
				WriteJavascriptString(javascript_fp, url);
				FreeMem(url);
				C = NextCrossReference(C);
				if( C != NULL )
					fprintf(javascript_fp, ",\n");
				else	fprintf(javascript_fp, "\n];\n");
			}
			OutputString("</select>\n</td>\n");
		}
		break;

		// invalid case
		case INVALID_nav:
		assert(0);
		break;

	}
	}
	// =================================================================

	// End table that contains the relative links
	OutputString("</tr></table><br");
	OutputString(Internal2Out("SelfTerminateCmd"));
	OutputString("\n");

	// End javascript file
	format =
	"function choose_%s(item)\n"
	"{	var index          = item.selectedIndex;\n"
	"	item.selectedIndex = 0;\n"
	"	if(index > 0)\n"
	"		document.location = list_%s[index-1];\n"
	"}\n";
	for(index = 0; index < number; index++)
	{	if( list_name[index] != NULL )
		{	fprintf(javascript_fp,
				format, list_name[index], list_name[index]
			);
		}
		FreeMem(list_name[index]);
	}
	fclose(javascript_fp);

}
