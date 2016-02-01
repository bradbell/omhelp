/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         omhparse
#define yylex           omhlex
#define yyerror         omherror
#define yydebug         omhdebug
#define yynerrs         omhnerrs

#define yylval          omhlval
#define yychar          omhchar

/* Copy the first part of user declarations.  */
#line 7 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:339  */

/*

Tag2Title(tag)
Returns a pointer to a character vector containing the title
for the section with the specified cross reference tag,
where ~tag is a '\0' terminated character row vector.
If there is no section with the specificed
cross reference tag, NULL is returned.
*/

# include "output_text.h"
# include "color_switch.h"
# include "Color.h"
# include "InitParser.h"
# include "Tag2Title.h"

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <assert.h>
# include <time.h>

# include "FrameSet.h"
# include "HtmlHead.h"
# include "relative.h"
# include "style.h"
# include "LatexMacro.h"
# include "content.h"
# include "AutomaticLink.h"
# include "omhparse.h"
# include "allocmem.h"
# include "strjoin.h"
# include "str_alloc.h"
# include "input.h"
# include "output.h"
# include "spell.h"
# include "copyfile.h"
# include "fatalerr.h"
# include "execute.h"
# include "pending.h"
# include "math.h"
# include "convert.h"
# include "SplitText.h"
# include "section.h"
# include "children.h"
# include "search.h"
# include "highlight.h"
# include "hilite.h"
# include "href.h"
# include "index.h"
# include "funref.h"
# include "cross.h"
# include "StrLowCase.h"
# include "StrLowAlloc.h"
# include "PatternMatch.h"
# include "DirSep.h"
# include "main.h"
# include "head.h"
# include "automatic.h"
# include "StrRemove.h"
# include "ClipWhiteSpace.h"
# include "UniformWhiteSpace.h"
# include "Internal2Out.h"
# include "int2str.h"
# include "LatexLexPut.h"
# include "texparse.h"
# include "lexomh.h"
# include "AutoTag.h"
# include "math_jax.h"

# ifndef WIN32
# define stricmp strcasecmp
# endif


# include "OmhStype.h"
# define YYSTYPE OmhStype
# define YYDEBUG 1

# define TAB_SIZE           5
# define MAX_TAG            100
# define MAX_WORD           100
# define MAX_LIST_LEVEL     10
# define MAX_AUTOMATIC      10
# define MAX_DEPTH          100


// define in main.c
extern int  DebugOmhelp;

// ***************** Section State ***************************

// frame counter in current section
static int iFrame;

// maximum frame referenced for the current section
static int MaxFrame;
static int MaxFrameLine;
static char *MaxFrameFile = NULL;

// track pending tables
static int  TableLevel    = 0;

// track pending lists
static int  ListLevel     = 0;
static int  ListOrdered[MAX_LIST_LEVEL];

// current table alingment
static char *HorizontalAlign;
static char *VerticalAlign;

// current character that gets converted to '$'
static char Dollar;

// current character that gets converted to RESISTERED_TRADE_MARK_CHARACTER
static char Rmark;

// current character that gets converted to COPYRIGHT_CHARACTER
static char Cmark;

// current character that gets converted to a space
static char Wspace;

// current program comment character
static char NewlineCh;

// current tab size during root seciton (constant after)
static int TabSizeRoot = TAB_SIZE;

// current escape character
static char Escape;
static char EscapeRoot = '\\';

// current automatic mindex commands
static int MindexSection;
static int MindexHead;
static int MindexSubhead;

// the automaitc mindex sections for root section
static int MindexSectionRoot = 0;
static int MindexHeadRoot    = 0;
static int MindexSubheadRoot = 0;

// current code font color
static char *CodeColor   = NULL;
static char *ErrorColor  = NULL;
static char *HiliteColor = NULL;

// flag that indicates spell checking is on
static int CheckSpell   = 1;

// ************************* Other Static Data  ************************

// words ignored by automatic indexing
static const char* AutomaticIndexIgnore =
	" a an and as at by for in of or to";

// Was previous output a heading
static int PreviousOutputWasHeading = 0;
int PreviousOmhelpOutputWasHeading()
{	return PreviousOutputWasHeading; }

// track pending execute command
static int ExecuteLine   = 0;
static char *ExecuteFile = NULL;


// track pending italic commands
static int ItalicCount = 0;

// count of section and end commands in this file
static int BeginCount;
static int EndCount;

// are we currently reading an include file
static char *IncludeFrom = NULL;
static int   IncludeLine = 0;

static int   RootHasChildren       = 0;
static SectionInfo *SectionTree    = NULL;
static SectionInfo *CurrentSection = NULL;

// Text being matched by MatchOrOutput which assumes that the first character
// ("<" in this case) appears no where else in any of the text. Thus
// one match cannot startup while another is running.
enum MatchType {
	NO_match,           // corresponds to the value 0
	HREF_match,
	CONTENTS_match,
	EXECUTE_match,
	FEND_match,
	TITLE_match,
	TREF_match,
	RREF_match,
	ENDHREF_match,
	CHILDREN_match,
	CHILDTABLE_match,
	ACCENT_match
};

static char *MatchText[]  = {
	"<HREF=\"",
	"<CONTENTS>",
	"<EXECUTE=\"",
	"<FEND>",
	"<TITLE=\"",
	"<TREF=\"",
	"<RREF=\"",
	"</HREF>",
	"<CHILDREN>",
	"<CHILDTABLE>",
	"<ACCENT="
};
static int   MatchLen[]   = {7, 10, 10, 6,  8, 7, 7, 7, 10, 12, 8};
static int   MatchState[] = {0, 0,  0,  0, 0,  0, 0, 0, 0,  0,  0, 0};
static int   MatchNumber  = sizeof(MatchText) / sizeof(MatchText[0]);

// ***************** Static Functions ************************

static void fatal_not_2_dollar_or_text(int code_cmd1, int line1, int code_cmd2)
{	fatalomh(
		"Error in the ",
		TokenCode2String(code_cmd1),
		" command that begins in line ",
		int2str(line1),
		".\nThis command is not terminated by $$ before ",
		TokenCode2String( code_cmd2 ),
		" appears.",
		NULL
	);
}

static int WhiteSpace(char *s)
{	int c;

	c = *s++;
	while( c != '\0' )
	{	if( ! isspace((int) c) )
			return 0;
		c = *s++;
	}
	return 1;
}


static void OutPre(int line, const char *s)
{	output_text(line,s,1,'\0',CheckSpell,ErrorColor); }




static void PushOmhInput(SectionInfo *S)
{	SectionInfo *P;

	int  nparent;

	// number of parents for this file
	nparent  = 0;
	P        = S->parent;
	while(P != NULL )
	{	nparent++;
		P = P->parent;
	}

	// set next input file and index nparent spaces when
	// printing its name on standard output
	InputPush(S->root, S->ext, nparent);

	BeginCount = 0;
	EndCount     = 0;
}

static void PushTmpOutput(const char *root)
{	char *file;
	file = strjoin(root, ".tmp");
	PushOutput(file);
	FreeMem(file);
}

static char MatchBuffer[10];
static int  MatchIndex = 0;
static int MatchOrOutput(int ch)
{	int    i;
	int    j;
	int    state;
	int    match;
	char   *text;

	match = 0;
	for(i = 0; i < MatchNumber; i++)
	{	text  = MatchText[i];
		state = MatchState[i];
		if( text[state] == ch )
		{	MatchState[i]++;
			if( MatchState[i] == MatchLen[i] )
			{	for(j = 0; j < MatchNumber; j++)
					MatchState[j] = 0;
				MatchIndex = 0;
				return i + 1;
			}
			match = 1;
		}
		else	MatchState[i] = 0;
	}
	if( match )
	{	assert(MatchIndex < 100);
		MatchBuffer[MatchIndex++] = ch;
		return 0;
	}
	for(i = 0; i < MatchIndex; i++)
		OutputChar(MatchBuffer[i]);
	MatchIndex = 0;

	if( ch != EOF )
		OutputChar((char) ch);

	return 0;
}


static void SecondPass(SectionInfo *F)
{
	char *tagLower;
	char *NameTmp;
	FILE *fpTmp;
	int  ch;
	int  match;

	// initialize to not defined
	int   lastCrossReferenceDefined = 0;

	// following buffer must be enough larger than MAX_TAG
	char buffer[200];


	assert( RootHasChildren || F == SectionTree );

	while( F != NULL )
	{	int         HtmlOnly;
		const char *FrameOneExt;

		// only use HTML format for frame one of these sections
		HtmlOnly =  (strcmp(F->tag, SEARCH_TAG) == 0)
		         || (strcmp(F->tag, CONTENTS_TAG) == 0);
		if( HtmlOnly )
			FrameOneExt = Internal2Out("HtmlOnlyExtension");
		else	FrameOneExt = Internal2Out("OutputExtension");

		// lower case version of tag
		tagLower = F->tagLower;

		// input file
		NameTmp = strjoin(F->tag, ".tmp");
		DirSep(NameTmp);
		StrLowCase(NameTmp);

		fpTmp   = fopen(NameTmp, "r");
		if( fpTmp == NULL ) fatalerr(
			"OMhelp created the temporary file\n",
			NameTmp,
			"\nbut that file is no longer available for reading.",
			NULL
		);
		if( PrintableOmhelp() )
		{	OutputString("\n<hr");
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("\n");
		}
		else if( NoFrame() )
		{	// new output file for this section
			sprintf(buffer,
				"%s%s",
				tagLower,
				FrameOneExt
			);
			PushOutput(buffer);

			if( HtmlOnly )
				OutputString("<html>\n");
			else	OutputString(Internal2Out("StartOutputFile"));
			OutputHtmlHead(F);
			OutputString("<body>\n");

			// relative links are in this file
			if( RootHasChildren )
				RelativeTable(F);
		}
		else
		{
			if( RootHasChildren )
				RelativeFrame(F);
			OutputFrameSet(F, FrameOneExt, RootHasChildren);

			// initialize user side frame index
			iFrame = 1;

			// create first output file
			sprintf(buffer,
				"%s_frame%d%s",
				tagLower,
				iFrame,
				FrameOneExt
			);
			PushOutput(buffer);

			if( HtmlOnly )
			{
				OutputString("<html>\n");
				OutputHtmlHead(F);
				OutputString("<body>\n");
				AutomaticLink(RootHasChildren, F);
			}
			else
			{
				OutputString(Internal2Out("StartOutputFile"));
				OutputHtmlHead(F);
				OutputString("<body>\n");
				AutomaticLink(RootHasChildren, F);
			}
		}

		// read until end of file
		ch    = getc(fpTmp);
		while( ch != EOF )
		{	// output checking for special sequences
			match = MatchOrOutput(ch);

			// check for an accent over a vowel
			if( match == ACCENT_match )
			{	// convert to proper accent
				buffer[0] = getc(fpTmp);
				buffer[1] = '\0';
				FormatOutput("&%sacute;", buffer);
				ch = getc(fpTmp);
				assert( ch == '>' );
			}

			// check for a cross reference
			if( match == HREF_match )
			{
				char *tag;
				int npound   = 0;
				int itag     = 0;
				int ipound[4];
				int defined;

				char *head;
				char *external;
				char *displayframe;
				char *display_printid;

				CrossReference *C = NULL;

				tag = AllocMem(1000, sizeof(char));

				// get the full pass1 cross reference
				ch = getc(fpTmp);
				while( ch != '"' )
				{	if( ch == '#' )
					{	assert( npound < 4 );
						ipound[npound++] = itag;
					}
					tag[itag++] = ch;
					ch = getc(fpTmp);
					assert(itag < 1000);
				}

				// remove the matching >
				ch = getc(fpTmp);
				assert( ch == '>' );

				assert( npound == 4 );
				assert( ipound[0] > 0);
				assert( ipound[0] < ipound[1] );
				assert( ipound[1] < ipound[2] );
				assert( ipound[2] < ipound[3] );
				assert( ipound[3] < itag);

				tag[ipound[0]] = '\0';
				tag[ipound[1]] = '\0';
				tag[ipound[2]] = '\0';
				tag[ipound[3]] = '\0';
				tag[itag]      = '\0';

				head            = tag + ipound[0] + 1;
				external        = tag + ipound[1] + 1;
				displayframe    = tag + ipound[2] + 1;
				display_printid = tag + ipound[3] + 1;

				defined = strcmp(external, "true") == 0;
				if( ! defined )
				{
					// check the cross reference
					C = FindCrossReference(tag, head);
					assert(C != NULL);

					defined = C->defined;
				}
				lastCrossReferenceDefined = defined;
				if( defined
				&& PrintableOmhelp()
				&& strcmp(external, "true") != 0 )
				{
					HrefPrintablePass2(
						C->printid,
						display_printid
					);
				}
				else if( defined )
				{	HrefOutputPass2(
						tag,
						head,
						external,
						displayframe
					);
				}
				else
				{	int matchtmp;
					// remove the cross reference

					// put cross reference text in red
					if( PostWarnings() )
					OutputString("<u><font color=\"red\">");

					// read and output until find </HREF>
					matchtmp = NO_match;
					while( matchtmp != ENDHREF_match )
					{	ch       = getc(fpTmp);
						matchtmp = MatchOrOutput(ch);
					}

					// terminate red underlines font
					if( PostWarnings() )
					OutputString("</font></u>\n");
				}

				FreeMem(tag);
			}

			// check for table of contents
			if( match == CHILDTABLE_match )
			{	TableChildren(F, PrintableOmhelp() );
			}
			if( match == CONTENTS_match )
			{	ListChildren(F, PrintableOmhelp() );
			}
			if( match == CHILDREN_match )
			{	// do nothing
			}

			// check for execute reference
			if( match == EXECUTE_match )
			{	char *execute;
				char *lower;

				int i = 0;

				execute = AllocMem(1000, sizeof(char));
				ch = getc(fpTmp);

				while( ch != '"' )
				{	execute[i++] = ch;
					ch = getc(fpTmp);
					assert(i < 1000);
				}
				execute[i] = '\0';
				lower = StrLowAlloc(execute);

				// remove the matching >
				ch = getc(fpTmp);
				assert( ch == '>' );

				// note the color for cross reference
				// that referrs to an execute
				FormatOutput(
					"<a href=\"%s\" target=\"_top\">",
					lower
				);
				OutputString("<font color=\"green\">");
				FormatOutput("%s</font></a>", execute);

				FreeMem(lower);
				FreeMem(execute);
			}

			// check for end of frame
			if( match == FEND_match )
			{
				assert( ! PrintableOmhelp() );
				assert( ! NoFrame() );

				OutputString("\n</body>\n</html>\n");
				PopOutput();

				iFrame++;
				sprintf(
					buffer,
					"%s_frame%d%s",
					tagLower,
					iFrame,
					Internal2Out("OutputExtension")
				);
				PushOutput(buffer);

				OutputString(Internal2Out("StartOutputFile"));
				OutputHtmlHead(F);
				OutputString("<body>\n");

				// Automatic links to this section and frame
				AutomaticLink(0, F);
			}

			if( match == TREF_match ||
			    match == RREF_match ||
			    match == TITLE_match
			)
			{	char           *tag;
				int            itag;
				CrossReference *C;

				// copy tag from file
				tag  = AllocMem(1000, sizeof(char));
				itag = 0;
				ch   = getc(fpTmp);
				while( ch != '"' )
				{	tag[itag++] = ch;
					ch          = getc(fpTmp);
					assert(itag < 1000);
				}
				tag[itag] = '\0';

				// remove the matching >
				ch   = getc(fpTmp);
				assert(ch == '>');


				// check the cross reference
				C = FindCrossReference(tag, "");
				assert(C != NULL);

				if(! C->defined)
				{	// underline tag in red
					if( PostWarnings() )
					OutputString("<u><font color=\"red\">");

					ConvertOutputString(tag, 0);

					if( PostWarnings() )
					OutputString("</font></u>\n");
				}
				else if( match == TITLE_match )
				{	// get the corresponding title
					const char *title = Tag2Title(tag);
					assert(title != NULL);
					ConvertOutputString(title, 0);
				}
				else
				{	// get the corresponding title
					const char *title = Tag2Title(tag);
					assert(title != NULL);

					if( PrintableOmhelp() )
						HrefPrintablePass2(
							C->printid, "true");
					else	HrefOutputPass2(
							tag, "", "false", "");

					// If RREF, make cross reference
					// a row in a table
					if( match == RREF_match )
					{	ConvertOutputString(tag, 0);
						HrefEnd("");
						OutputString("</td><td>\n");
						ConvertOutputString(
							title, 0);
						OutputString(
						"</td></tr>\n<tr><td>\n");
					}
					else
					{
						ConvertOutputString(
							title, 0);
						HrefEnd("");
					}
				}
				FreeMem(tag);
			}
			if(match == ENDHREF_match && lastCrossReferenceDefined)
			{
				HrefEnd("");
			}

			// get next character
			ch = getc(fpTmp);
		}


		// flush output and reset state to zero
		MatchOrOutput(EOF);
		if( ! PrintableOmhelp() )
		{	OutputString("\n</body>\n</html>\n");
			PopOutput();
		}

		// close this input file
		fclose(fpTmp);

		// delete the temporary file
		remove(NameTmp);

		// free allocation for this section
		FreeMem(NameTmp);

		// now children
		if( RootHasChildren )
			SecondPass(F->children);
		else
		{	assert( F->children != NULL );
			assert( strcmp(F->children->tag, CONTENTS_TAG) == 0 );
			assert( F->next     == NULL );
		}

		// now siblings
		F = F->next;

	}
	return;
}

static void Appendices()
{	// appendices used only if root has children

	int     letterheadings;

	CheckSpell = 0;

	letterheadings = 0;
	AutomaticAppendSection(
		SectionTree,
		REFERENCE_TAG,
		"Alphabetic Listing of Cross Reference Tags",
		letterheadings
	);
	FunRefPass1( SectionFind(SectionTree, REFERENCE_TAG) );

	AutomaticAppendSection(
		SectionTree,
		INDEX_TAG,
		"Keyword Index",
		letterheadings
	);
	IndexPass1(  SectionFind(SectionTree, INDEX_TAG)     );

	if( ! PrintableOmhelp() )
	{	// insert the search utility in the section tree
		// but close the search file later so happens even if
		// root has no children
		char *searchTitle;
		if( SiteName() != NULL )
			searchTitle = strjoin("Search ", SiteName());
		else	searchTitle = str_alloc("Search This Web Site");
		AutomaticAppendSection(
			SectionTree,
			SEARCH_TAG,
			searchTitle,
			letterheadings
		);
		FreeMem(searchTitle);

	}
	if( DebugOmhelp )
	{	AutomaticAppendSection(
			SectionTree,
			EXTERNAL_TAG,
			"External Internet References",
			letterheadings
		);
		HrefOutputList(
			SectionFind(SectionTree, EXTERNAL_TAG)
		);
	}

	ContentPass1( SectionFind(SectionTree, CONTENTS_TAG) );
}

static void FinishUp()
{	char *root_file_name = NULL;
	FILE *fp = NULL;

# if 0
	// free memory corresponding to patterns
	hilite_pattern(0, 0, "");
	hilite_set_default();
# endif


	// done with xml macros defined at the Root level
	LatexMacroFree();
	LatexMacroFree();

	// done with htm macros defined at the Root level
	const char* macro_cmd  = "clear";
	const char* latex_cmds = NULL;
	math_jax(macro_cmd, latex_cmds);

	// must close search file even if root has no children
	CloseSearchFile( ! RootHasChildren );

	// Separate trace information from error message during second pass
	printf("\nBegin Second Pass\n");

	if( ! PrintableOmhelp() )
	{	SecondPass(SectionTree);

		// file corresponding to the root section
		root_file_name = strjoin(
			SectionTree->tagLower,
			Internal2Out("OutputExtension")
		);

	}
	else
	{	// file corresponding to the root section
		root_file_name = strjoin(
			PRINTABLE_TAG,
			Internal2Out("OutputExtension")
		);
		PushOutput(root_file_name);
		OutputString(Internal2Out("StartOutputFile"));
		OutputString("\n");

		// just title: no keywords or style for printable version
		OutputString("<head><title>");
		ConvertOutputString(SectionTree->title, 0);
		OutputString("</title></head>\n");

		OutputString("<body>\n");

		SecondPass(SectionTree);

		OutputString("\n</body>\n</html>\n");
		PopOutput();
	}
	// create index.html as a link to the root file
	fp = fopen("index.html", "w");
	assert( fp != NULL );
	fprintf(fp, "<html><head><script>\n");
	fprintf(fp, "\twindow.location.href=\"%s\";\n", root_file_name);
	fprintf(fp, "</script></head></html>\n");
	fclose(fp);
	FreeMem(root_file_name);

	FunRefFree();
	IndexFreeMem();

	SectionFreeTree(SectionTree);

	InputFree();

	FreeCrossReference();

	FreeSpelling(DebugOmhelp);

	ExecuteFree();

	HrefFreeMemory();

	copyfileFreeMemory();

}

static void SkipCodep(int line, char *s)
{	char *next;
	char *last;

	next = s;
	last  = s + strlen(s) - 1;

	/*
	skip to the first newline
	*/
	while( *next != '\n' && *next != '\0' )
		next++;
	if( *next != '\n' ) fatalomh(
		"A new line was expected ",
		"after the $codep command in line ",
		int2str(line),
		NULL
	);

	// find last character to include
	while( *last != '\n' )
		last--;

	// could not have gone past newline found by next pointer
	assert( next <= last );

	if( next == last ) fatalomh(
		"The output for $codep Text$$ comes after the first\n",
		"newline in Text and before the last.\n",
		"The output specified by the $codep command in line ",
		int2str(line),
		" is empty",
		NULL
	);


	// skift the string pointed to by s
	while( next <= last )
		*s++ = *next++;

	// new termination point
	*s = '\0';
}

/**********************************************************************/

char newline_ch(void)
{	return NewlineCh; }

const char *Tag2Title(const char *tag)
{	SectionInfo *F;
	F = SectionFind(SectionTree, tag);
	if( F == NULL )
		return NULL;
	else	return F->title;
}

void InitParser(const char *StartingInputFile)
{	char *s;
	char *LocalDirectory;
	char *searchTitle;
	int letterheadings;

	// initialize LocalName to avoid warning
	// (compiler does not know fatalerr will not return)
	char *LocalName = NULL;

	// extract the directory and name rom StartingInputFile
	LocalDirectory = str_alloc(StartingInputFile);
	s              = LocalDirectory + strlen(LocalDirectory);
	while( s > LocalDirectory && *s != '/' && *s != '\\' )
		s--;
	if( *s == '/' || *s == '\\' )
	{	LocalName = str_alloc(s + 1);
		*(s+1) = '\0';
	}
	else	fatalerr(
		"The starting input file specification\n",
		"does not contain a directory name.\n",
		"If you must run OMhelp in the directory\n",
		"where the starting input file is located,\n",
		"place .\\ in front of the file name",
		NULL
	);


	InputInit(LocalDirectory);

	assert(SectionTree == NULL);

	// starting of section tree
	SectionTree    = SectionInfoNew(NULL, LocalName);
	CurrentSection = SectionTree;

	// Table of Contents is first child of starting section
	letterheadings = 0;
	AutomaticAppendSection(
		SectionTree,
		CONTENTS_TAG,
		"Table of Contents",
		letterheadings
	);
	assert( SectionTree->children != NULL );
	assert( strcmp(SectionTree->children->tag, CONTENTS_TAG) == 0 );

	PushOmhInput(CurrentSection);

	if( SiteName() != NULL )
		searchTitle = strjoin("Search ", SiteName());
	else	searchTitle = str_alloc("Search This Web Site");
	OpenSearchFile(SEARCH_TAG, searchTitle);
	FreeMem(searchTitle);

	FreeMem(LocalDirectory);
	FreeMem(LocalName);
}


#line 1066 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "omhelp.h".  */
#ifndef YY_OMH_HOME_BRADBELL_OMHELP_GIT_SRC_OMHELP_H_INCLUDED
# define YY_OMH_HOME_BRADBELL_OMHELP_GIT_SRC_OMHELP_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int omhdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ACCENT_lex = 258,
    AINDEX_lex = 259,
    ALIGN_lex = 260,
    BEGIN_lex = 261,
    BGCOLOR_lex = 262,
    BIG_lex = 263,
    BOLD_lex = 264,
    CEND_lex = 265,
    CENTER_lex = 266,
    CHILDREN_lex = 267,
    CHILDTABLE_lex = 268,
    CINDEX_lex = 269,
    CMARK_lex = 270,
    CNEXT_lex = 271,
    CODE_lex = 272,
    CODECOLOR_lex = 273,
    CODEI_lex = 274,
    CODEP_lex = 275,
    COMMENT_lex = 276,
    CONTENTS_lex = 277,
    CREF_lex = 278,
    DATE_lex = 279,
    DOLLAR_lex = 280,
    DOUBLE_DOLLAR_lex = 281,
    END_lex = 282,
    EOF_lex = 283,
    ERRORCOLOR_lex = 284,
    ESCAPE_lex = 285,
    EXECUTE_lex = 286,
    FEND_lex = 287,
    FIXED_lex = 288,
    HEAD_lex = 289,
    HILITECMD_lex = 290,
    HILITECOLOR_lex = 291,
    HILITESEQ_lex = 292,
    HREF_lex = 293,
    ICODE_lex = 294,
    ICON_lex = 295,
    IMAGE_lex = 296,
    INCLUDE_lex = 297,
    INDEX_lex = 298,
    ITALIC_lex = 299,
    LATEX_lex = 300,
    LEND_lex = 301,
    LINKCOLOR_lex = 302,
    LIST_lex = 303,
    LNEXT_lex = 304,
    MATH_lex = 305,
    MINDEX_lex = 306,
    MREF_lex = 307,
    NAVIGATE_lex = 308,
    NEWLINECH_lex = 309,
    NOBREAK_lex = 310,
    NOSPELL_lex = 311,
    NUMBER_lex = 312,
    PATH_lex = 313,
    PRE_lex = 314,
    REND_lex = 315,
    RMARK_lex = 316,
    RNEXT_lex = 317,
    RREF_lex = 318,
    SECTION_lex = 319,
    SKIPNL_lex = 320,
    SMALL_lex = 321,
    SPELL_lex = 322,
    SRC_lex = 323,
    SUBHEAD_lex = 324,
    SYNTAX_lex = 325,
    TABLE_lex = 326,
    TABSIZE_lex = 327,
    TEND_lex = 328,
    TEXT_lex = 329,
    TEXTCOLOR_lex = 330,
    TH_lex = 331,
    TITLE_lex = 332,
    TRACE_lex = 333,
    TREF_lex = 334,
    VERBATIM_lex = 335,
    VISITCOLOR_lex = 336,
    WSPACE_lex = 337,
    XREF_lex = 338
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE omhlval;

int omhparse (void);

#endif /* !YY_OMH_HOME_BRADBELL_OMHELP_GIT_SRC_OMHELP_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 1201 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3246

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  97
/* YYNRULES -- Number of rules.  */
#define YYNRULES  304
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  453

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1084,  1084,  1095,  1100,  1101,  1102,  1103,  1104,  1105,
    1106,  1107,  1108,  1109,  1110,  1111,  1112,  1113,  1114,  1115,
    1116,  1117,  1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,
    1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,
    1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,
    1146,  1147,  1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,
    1156,  1157,  1158,  1159,  1160,  1161,  1162,  1189,  1190,  1191,
    1192,  1193,  1194,  1195,  1196,  1197,  1198,  1202,  1206,  1213,
    1288,  1291,  1323,  1326,  1359,  1367,  1370,  1564,  1567,  1593,
    1604,  1618,  1629,  1642,  1645,  1666,  1690,  1694,  1701,  1716,
    1731,  1737,  1746,  1815,  1924,  1932,  1941,  1947,  1953,  1962,
    1965,  1979,  1992,  2005,  2008,  2023,  2026,  2084,  2087,  2099,
    2102,  2234,  2271,  2274,  2288,  2391,  2516,  2519,  2533,  2536,
    2554,  2557,  2600,  2603,  2674,  2685,  2698,  2701,  2819,  2822,
    2832,  2835,  2850,  2853,  2862,  2865,  2982,  2985,  3005,  3012,
    3022,  3185,  3188,  3246,  3350,  3362,  3377,  3378,  3379,  3380,
    3381,  3382,  3383,  3384,  3385,  3386,  3387,  3388,  3389,  3390,
    3391,  3392,  3393,  3394,  3395,  3396,  3397,  3398,  3399,  3400,
    3401,  3402,  3403,  3404,  3405,  3406,  3407,  3408,  3409,  3410,
    3411,  3412,  3413,  3414,  3415,  3416,  3417,  3418,  3419,  3420,
    3421,  3422,  3423,  3424,  3425,  3426,  3427,  3428,  3429,  3430,
    3431,  3432,  3433,  3434,  3435,  3436,  3437,  3438,  3439,  3440,
    3441,  3442,  3443,  3444,  3445,  3446,  3447,  3448,  3449,  3450,
    3451,  3457,  3460,  3523,  3545,  3548,  3574,  3577,  3646,  3665,
    3668,  3708,  3711,  3785,  3788,  3804,  3807,  3829,  3832,  3850,
    3861,  3874,  3875,  3876,  3877,  3881,  3884,  3903,  3942,  3945,
    3983,  4014,  4021,  4031,  4034,  4048,  4051,  4091,  4094,  4188,
    4191,  4203,  4214,  4228,  4231,  4247,  4250,  4562,  4565,  4689,
    4692,  4761,  4784,  4787,  4822,  4847,  4855,  4915,  4918,  4944,
    4947,  4972,  4975,  4988,  4991,  5020,  5023,  5066,  5069,  5323,
    5326,  5351,  5354,  5369,  5372
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ACCENT_lex", "AINDEX_lex", "ALIGN_lex",
  "BEGIN_lex", "BGCOLOR_lex", "BIG_lex", "BOLD_lex", "CEND_lex",
  "CENTER_lex", "CHILDREN_lex", "CHILDTABLE_lex", "CINDEX_lex",
  "CMARK_lex", "CNEXT_lex", "CODE_lex", "CODECOLOR_lex", "CODEI_lex",
  "CODEP_lex", "COMMENT_lex", "CONTENTS_lex", "CREF_lex", "DATE_lex",
  "DOLLAR_lex", "DOUBLE_DOLLAR_lex", "END_lex", "EOF_lex",
  "ERRORCOLOR_lex", "ESCAPE_lex", "EXECUTE_lex", "FEND_lex", "FIXED_lex",
  "HEAD_lex", "HILITECMD_lex", "HILITECOLOR_lex", "HILITESEQ_lex",
  "HREF_lex", "ICODE_lex", "ICON_lex", "IMAGE_lex", "INCLUDE_lex",
  "INDEX_lex", "ITALIC_lex", "LATEX_lex", "LEND_lex", "LINKCOLOR_lex",
  "LIST_lex", "LNEXT_lex", "MATH_lex", "MINDEX_lex", "MREF_lex",
  "NAVIGATE_lex", "NEWLINECH_lex", "NOBREAK_lex", "NOSPELL_lex",
  "NUMBER_lex", "PATH_lex", "PRE_lex", "REND_lex", "RMARK_lex",
  "RNEXT_lex", "RREF_lex", "SECTION_lex", "SKIPNL_lex", "SMALL_lex",
  "SPELL_lex", "SRC_lex", "SUBHEAD_lex", "SYNTAX_lex", "TABLE_lex",
  "TABSIZE_lex", "TEND_lex", "TEXT_lex", "TEXTCOLOR_lex", "TH_lex",
  "TITLE_lex", "TRACE_lex", "TREF_lex", "VERBATIM_lex", "VISITCOLOR_lex",
  "WSPACE_lex", "XREF_lex", "$accept", "start", "init", "element",
  "element_list", "accent", "aindex", "align", "argument", "begin",
  "bgcolor", "big_begin", "big", "bold_begin", "bold", "codei", "cnext",
  "cnext_cases", "center_begin", "center", "contents", "childhead",
  "childlist", "children", "cmindex", "cmark", "code_begin", "code",
  "codecolor", "codep", "comment", "cref", "date", "dollar", "end", "eof",
  "errorcolor", "escape", "execute", "fend", "fixed_begin", "fixed",
  "head", "hilitecmd", "hilitecolor", "hiliteseq", "href", "icode",
  "image_begin", "image", "include", "index", "italic_begin", "italic",
  "keyword", "latex", "lend", "linkcolor", "list", "lnext", "math", "mref",
  "navigate", "newlinech", "nobreak", "nospell_begin", "nospell",
  "not_2_dollar_or_text", "number", "path", "pre", "rnext", "rnext_cases",
  "rmark", "rref", "section", "skipnl", "small_begin", "small", "spell",
  "src", "subhead", "syntax", "table", "tabsize", "tend", "text",
  "text_raw", "textcolor", "th", "trace", "title", "tref", "verbatim",
  "visitcolor", "wspace", "xref", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338
};
# endif

#define YYPACT_NINF -86

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-86)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -86,     6,   904,   -86,   -86,   -69,   -69,   -69,   -69,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -69,   -86,   -86,   -69,
     -69,   -69,   -67,   -86,   -69,   -86,   -69,   -86,   -86,   -69,
     -69,   -69,   -69,   -86,   -69,   -69,   -69,   -69,   -69,   -69,
     -86,   -86,   -69,   -86,   -86,   -69,   -86,   -69,   -69,   -86,
     -69,   -86,   -69,   -69,   -69,   -69,   -86,   -18,   -69,   -69,
     -86,   -69,   -86,   -69,   -69,   -69,   -86,   -69,   -69,   -69,
     -69,   -86,   -69,   -86,   -86,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -86,   175,   -86,   -86,   -86,   -86,
     -86,   904,   -86,   904,   -86,   -86,   -86,   -86,   904,   -86,
     -86,   -86,   -86,   -69,   -69,   -86,   904,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     904,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -69,   -86,
     -86,   -86,   904,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   904,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   904,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -17,  3091,   -16,  3091,   -15,
    3091,   985,   -13,  3091,  1066,  1147,  1228,   -12,  3091,  1309,
      -7,  3091,  1390,    -5,  3091,    -3,  3091,    -2,  3091,     3,
    3091,  1471,  1552,  1633,  1714,  1795,    10,  3091,  1876,  1957,
      11,  3091,  2038,  2119,  2200,    13,  3091,  2281,   -86,  3091,
      14,  2362,    16,  3091,    19,  3091,    21,  3091,    26,  3091,
    2443,  2524,    32,  3091,  2605,    36,  3091,  2686,    41,  3091,
      43,  3091,  2767,    44,  3091,  2848,  2929,    54,  3091,  3010,
     -86,   -86,   256,   337,   418,    57,    58,   499,   580,    59,
     661,   742,   823,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     0,     1,    79,     0,     0,     0,     0,    89,
      91,    96,    98,   104,   101,   106,     0,    97,   111,     0,
       0,     0,     0,   100,     0,   121,     0,   124,   125,     0,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
     148,   149,     0,   108,   154,     0,   233,     0,     0,   238,
       0,   107,     0,     0,     0,     0,   249,     0,     0,     0,
     261,     0,   262,     0,     0,     0,   271,     0,     0,     0,
       0,   281,     0,   284,   286,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    77,     0,     4,     5,     6,     7,
       8,     0,     9,     0,    10,    17,    14,    95,     0,    11,
     102,   105,    12,     0,     0,    13,     0,    15,    16,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
       0,    29,    30,    31,    32,    33,    34,    35,     0,    36,
      37,    38,     0,    39,    40,    41,    42,    43,    44,    45,
      46,    50,    51,    47,     0,    48,    49,    52,    53,    55,
     260,    54,    70,    56,    57,     0,    58,    59,    60,    61,
      62,    63,    64,    65,    66,   285,    67,    68,    69,    71,
      72,    73,    74,    75,    76,     0,    84,     0,    84,     0,
      84,     0,     0,    84,     0,     0,     0,   286,     0,     0,
       0,    84,     0,     0,    84,     0,    84,     0,    84,     0,
      84,     0,     0,     0,     0,     0,     0,    84,     0,     0,
       0,    84,     0,     0,     0,     0,    84,     0,   256,     0,
       0,     0,     0,    84,     0,    84,     0,    84,     0,    84,
       0,     0,     0,    84,     0,     0,    84,     0,     0,    84,
       0,    84,     0,     0,    84,     0,     0,     0,    84,     0,
       2,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,   252,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   253,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   254,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   251,    80,    83,    82,    86,    85,    88,    87,
     110,   109,   114,   113,    94,    93,   116,   115,   118,   117,
     120,   119,   123,   122,   127,   126,   129,   128,   131,   130,
     133,   132,   137,   136,   139,   138,   141,   140,   143,   142,
     145,   144,   147,   146,   152,   151,   232,   231,   235,   234,
     237,   236,   240,   239,   242,   241,   244,   243,   246,   245,
     248,   247,   255,   257,   259,   258,   264,   263,   266,   265,
     268,   267,   270,   269,   274,   273,   276,   275,   278,   277,
     280,   279,   283,   282,   288,   287,   290,   289,   294,   293,
     292,   291,   296,   295,   298,   297,   300,   299,   302,   301,
     304,   303,    90,    92,    99,   103,   153,   112,   135,   150,
     155,   250,   272
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -86,   -86,   -86,   -85,     5,   -86,   -86,   -86,    75,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,  2997,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,    -4,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    84,    85,    86,    87,    88,   175,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   342,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   343,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     251,   176,   178,   180,   181,    74,     3,   187,   218,   263,
     344,   346,   183,   350,   358,   184,   185,   186,   188,   362,
     189,   366,   191,   368,   370,   192,   194,   196,   198,   372,
     200,   201,   202,   203,   204,   205,   384,   390,   207,   398,
     403,   208,   406,   209,   211,   408,   212,   410,   213,   214,
     216,   217,   412,   219,   220,   221,    74,   223,   418,   225,
     227,   229,   422,   230,   231,   233,   234,   426,   236,   428,
     432,   237,   239,   241,   242,   244,   245,   246,   248,   249,
     438,   177,   179,   445,   446,   449,     0,     0,     0,     0,
       0,   182,     0,     0,     0,     0,   252,     0,   253,   255,
     256,   190,     0,   254,     0,   193,   195,   197,     0,   199,
       0,   257,     0,     0,     0,     0,     0,   206,     0,     0,
       0,     0,     0,   210,   259,   258,     0,     0,     0,   215,
       0,     0,     0,     0,     0,     0,   222,   260,   224,   226,
     228,     0,     0,     0,   232,     0,     0,   235,     0,   261,
       0,   238,   240,     0,   243,     0,     0,   247,     0,     0,
     262,     0,     0,     0,     0,     0,     0,   251,   251,   251,
       0,     0,   251,   251,     0,   251,   251,   251,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,   250,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,   442,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,   443,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,   444,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,   447,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,   448,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,   450,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,   451,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,   452,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   348,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,     0,   328,   329,   330,   331,   332,     0,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   352,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,     0,   328,   329,   330,   331,   332,
       0,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   354,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,     0,   328,   329,   330,   331,
     332,     0,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   356,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,     0,   328,   329,   330,
     331,   332,     0,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   360,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,     0,   328,   329,
     330,   331,   332,     0,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   364,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,     0,   328,
     329,   330,   331,   332,     0,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   374,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,     0,
     328,   329,   330,   331,   332,     0,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   376,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
       0,   328,   329,   330,   331,   332,     0,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   378,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,     0,   328,   329,   330,   331,   332,     0,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     380,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,     0,   328,   329,   330,   331,   332,     0,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   382,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,     0,   328,   329,   330,   331,   332,     0,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   386,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,     0,   328,   329,   330,   331,   332,
       0,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   388,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,     0,   328,   329,   330,   331,
     332,     0,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   392,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,     0,   328,   329,   330,
     331,   332,     0,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   394,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,     0,   328,   329,
     330,   331,   332,     0,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   396,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,     0,   328,
     329,   330,   331,   332,     0,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   400,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,     0,
     328,   329,   330,   331,   332,     0,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   404,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
       0,   328,   329,   330,   331,   332,     0,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   414,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,     0,   328,   329,   330,   331,   332,     0,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     416,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,     0,   328,   329,   330,   331,   332,     0,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   420,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,     0,   328,   329,   330,   331,   332,     0,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   424,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,     0,   328,   329,   330,   331,   332,
       0,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   430,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,     0,   328,   329,   330,   331,
     332,     0,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   434,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,     0,   328,   329,   330,
     331,   332,     0,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   436,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,     0,   328,   329,
     330,   331,   332,     0,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   440,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,     0,   328,
     329,   330,   331,   332,     0,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,     0,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,     0,
     328,   329,   330,   331,   332,     0,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   345,     0,   347,   349,     0,
     351,   353,   355,   357,     0,   359,   361,     0,   363,   365,
       0,   367,     0,   369,     0,   371,     0,   373,   375,   377,
     379,   381,   383,     0,   385,   387,   389,     0,   391,   393,
     395,   397,     0,   399,   401,     0,   402,     0,   405,     0,
     407,     0,   409,     0,   411,     0,   413,   415,   417,     0,
     419,   421,     0,   423,   425,     0,   427,     0,   429,   431,
       0,   433,   435,   437,     0,   439,   441
};

static const yytype_int16 yycheck[] =
{
      85,     5,     6,     7,     8,    74,     0,    74,    26,    26,
      26,    26,    16,    26,    26,    19,    20,    21,    22,    26,
      24,    26,    26,    26,    26,    29,    30,    31,    32,    26,
      34,    35,    36,    37,    38,    39,    26,    26,    42,    26,
      26,    45,    26,    47,    48,    26,    50,    26,    52,    53,
      54,    55,    26,    57,    58,    59,    74,    61,    26,    63,
      64,    65,    26,    67,    68,    69,    70,    26,    72,    26,
      26,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      26,     6,     7,    26,    26,    26,    -1,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    -1,    91,    -1,    93,   103,
     104,    26,    -1,    98,    -1,    30,    31,    32,    -1,    34,
      -1,   106,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    48,   128,   120,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    61,   132,    63,    64,
      65,    -1,    -1,    -1,    69,    -1,    -1,    72,    -1,   144,
      -1,    76,    77,    -1,    79,    -1,    -1,    82,    -1,    -1,
     155,    -1,    -1,    -1,    -1,    -1,    -1,   252,   253,   254,
      -1,    -1,   257,   258,    -1,   260,   261,   262,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    69,    70,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    69,    70,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      69,    70,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    69,    70,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    69,    70,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    69,    70,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      69,    70,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    69,    70,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    69,    70,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    69,    70,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    69,    70,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      69,    70,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,   178,    -1,   180,   181,    -1,
     183,   184,   185,   186,    -1,   188,   189,    -1,   191,   192,
      -1,   194,    -1,   196,    -1,   198,    -1,   200,   201,   202,
     203,   204,   205,    -1,   207,   208,   209,    -1,   211,   212,
     213,   214,    -1,   216,   217,    -1,   219,    -1,   221,    -1,
     223,    -1,   225,    -1,   227,    -1,   229,   230,   231,    -1,
     233,   234,    -1,   236,   237,    -1,   239,    -1,   241,   242,
      -1,   244,   245,   246,    -1,   248,   249
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    85,    86,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    87,    88,    89,    90,    91,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,    92,   170,    92,   170,    92,
     170,   170,    92,   170,   170,   170,   170,    74,   170,   170,
      92,   170,   170,    92,   170,    92,   170,    92,   170,    92,
     170,   170,   170,   170,   170,   170,    92,   170,   170,   170,
      92,   170,   170,   170,   170,    92,   170,   170,    26,   170,
     170,   170,    92,   170,    92,   170,    92,   170,    92,   170,
     170,   170,    92,   170,   170,    92,   170,   170,    92,   170,
      92,   170,   170,    92,   170,   170,   170,    92,   170,   170,
      26,    87,    88,    88,    88,   170,   170,    88,    88,   170,
      88,    88,    88,    26,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    69,    70,
      71,    72,    73,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   138,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,   151,    26,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,   151,    26,   151,    26,   151,    26,   151,
      26,   151,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    88,    89,
      90,    90,    91,    91,    92,    93,    93,    94,    94,    95,
      96,    97,    98,    99,    99,   100,   101,   101,   102,   103,
     104,   104,   105,   106,   107,   107,   108,   108,   108,   109,
     109,   110,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   117,   117,   118,   119,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   125,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   132,   132,
     133,   134,   134,   135,   136,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   139,   139,   140,   141,   141,   142,   142,   143,   144,
     144,   145,   145,   146,   146,   147,   147,   148,   148,   149,
     150,   151,   151,   151,   151,   152,   152,   153,   154,   154,
     155,   156,   156,   157,   157,   158,   158,   159,   159,   160,
     160,   161,   162,   163,   163,   164,   164,   165,   165,   166,
     166,   167,   168,   168,   169,   170,   171,   172,   172,   173,
     173,   174,   174,   175,   175,   176,   176,   177,   177,   178,
     178,   179,   179,   180,   180
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     1,     3,     3,     3,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     3,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     1,     1,     1,     1,     3,     2,     3,     3,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 1085 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		fatalomh(
			"Unexpected $$",
			NULL
		);
	}
#line 3209 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 3:
#line 1095 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	yydebug = 0;
	}
#line 3216 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1163 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );

		if( PreviousOutputWasHeading )
		{
			char *s = (yyvsp[0]).str;
			char ch = *s++;

			while( isspace((int) ch) )
				ch = *s++;

			if( ! ch == '\0' )
			{	// if text is not all white space, need
				// an extra new line after previous heading
				ConvertForcedNewline(1);

				PreviousOutputWasHeading = 0;
			}
			// otherwise suspend judgement on the extra new line
		}

		output_text((yyvsp[0]).line,(yyvsp[0]).str,0,'\0',CheckSpell,ErrorColor);
		FreeMem((yyvsp[0]).str);

		(yyval).str  = NULL;
		(yyval).line = (yyvsp[0]).line;
	}
#line 3247 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1203 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		(yyval) = (yyvsp[0]);
	}
#line 3255 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1207 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str == NULL );
		(yyval) = (yyvsp[-1]);
	}
#line 3263 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1214 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char ch;

		// initlaize to avoid warning
		// (compiler does not know fatalomh does not return)
		char *code = NULL;

		assert( (yyvsp[0]).str != NULL );
		assert( strlen((yyvsp[0]).str) == 1 );

		ch = *((yyvsp[0]).str);
		switch(ch)
		{	case 'A':
			code = "193";
			break;

			case 'E':
			code = "201";
			break;

			case 'I':
			code = "205";
			break;

			case 'O':
			code = "211";
			break;

			case 'U':
			code = "218";
			break;

			case 'Y':
			code = "221";
			break;

			case 'a':
			code = "225";
			break;

			case 'e':
			code = "233";
			break;

			case 'i':
			code = "237";
			break;

			case 'o':
			code = "243";
			break;

			case 'u':
			code = "250";
			break;

			case 'y':
			code = "253";
			break;

			default:
			fatalomh(
			"The character following a $' command in line ",
			int2str( (yyvsp[0]).line ),
			" is not a vowel.",
			NULL
			);
		}
		FormatOutput("&#%s;", code);

		FreeMem((yyvsp[0]).str);
	}
#line 3339 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1289 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 3346 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1292 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *s;
		int i;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		s = StrCat(__FILE__, __LINE__, " ", (yyvsp[-1]).str, " ", NULL);

		for(i = 0; s[i] != '\0'; i++)
			if( isspace((int) s[i]) )
				s[i] = ' ';

		MindexSection = strstr(s, " section ") != NULL;
		MindexHead    = strstr(s, " head ")    != NULL;
		MindexSubhead = strstr(s, " subhead ") != NULL;

		if( CurrentSection->parent == NULL )
		{	MindexSectionRoot = MindexSection;
			MindexHeadRoot    = MindexHead;
			MindexSubheadRoot = MindexSubhead;
		}

		FreeMem(s);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 3379 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1324 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 3386 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1327 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *s;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		s = (yyvsp[-1]).str;
		if( strcmp(s, "left") == 0 )
			HorizontalAlign = "left";
		else if( strcmp(s, "center") == 0 )
			HorizontalAlign = "center";
		else if( strcmp(s, "right") == 0 )
			HorizontalAlign = "right";
		else if( strcmp(s, "top") == 0 )
			VerticalAlign = "top";
		else if( strcmp(s, "middle") == 0 )
			VerticalAlign = "middle";
		else if( strcmp(s, "bottom") == 0 )
			VerticalAlign = "bottom";
		else fatalomh(
			"The $align command argument in line ",
			int2str((yyvsp[-1]).line),
			" is not one of following:\n",
			"left, center, right, top, middle, bottom",
			NULL
		);

		FreeMem((yyvsp[-1]).str);
	}
#line 3420 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1360 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		ClipWhiteSpace((yyvsp[0]).str);
		(yyval) = (yyvsp[0]);
	}
#line 3429 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1368 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 3436 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1371 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *tag;
		char *tag_lower;
		char *number = NULL;
		CrossReference *C;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( BeginCount != EndCount ) fatalomh(
			"The $begin command on line ",
			int2str((yyvsp[-2]).line),
			"\noccurs before the previous $begin ",
			"was terminated by a $end",
			NULL
		);
		BeginCount++;

		assert( PreviousOutputWasHeading == 0 );

		// check if there is already a section in this file
		// if so, start a new sibling of current section
		if( CurrentSection->tag != NULL )
		{	// note that this operation changes the value of
			// SectionNumber(CurrentSection->next) which has
			// not yet been used.
			SectionInfo *F;
			if( CurrentSection == SectionTree ) fatalomh(
				"The $begin command in line ",
				int2str((yyvsp[-2]).line),
				" is the second one in the starting file\n",
				"There can only be one section at the root ",
				"of the web site tree.",
				NULL
			);
			F = SectionInfoNew(SectionTree, InputName());

			// links for this section
			F->next           = CurrentSection->next;
			F->previous       = CurrentSection;
			F->parent         = CurrentSection->parent;

			// this section comes after the current one
			CurrentSection->next = F;

			// this section comes before the next one
			if( F->next != NULL )
				F->next->previous = F;

			// make this the current section
			CurrentSection       = F;
		}

		// set the current section tag (and lower case version)
		tag = (yyvsp[-1]).str;
		SectionSetTag(CurrentSection, tag);
		tag_lower = CurrentSection->tagLower;

		/*
		check for an invalid section tag
		*/
		if( strlen(tag) > MAX_TAG ) fatalomh(
			"In the $begin command on line ",
			int2str((yyvsp[-2]).line),
			"\nthe section tag is more than ",
			int2str(MAX_TAG),
			" characters long",
			NULL
		);
		if( strstr(tag_lower, "_frame") != NULL ) fatalomh(
			"In the $begin command on line ",
			int2str((yyvsp[-2]).line),
			"\nthe section tag contains the substring \"_frame\"",
			NULL
		);
		if( strstr(tag_lower, "_links") != NULL ) fatalomh(
			"In the $begin command on line ",
			int2str((yyvsp[-2]).line),
			"\nthe section tag contains the substring \"_links\"",
			NULL
		);
		if( tag_lower[0] == '_' ) fatalomh(
			"In the $begin command on line ",
			int2str((yyvsp[-2]).line),
			"\n\"_\" is the first character in the section tag",
			NULL
		);
		if( strcmp(tag_lower, "index") == 0 ) fatalomh(
			"In the $begin command on line ",
			int2str((yyvsp[-2]).line),
			"\nyou cannot use \"index\" as a section tag",
			"\nbecause \"index\" automatically links ",
			"to the starting file",
			NULL
		);

		// start a new output file
		PushTmpOutput(CurrentSection->tag);

		// start new section in search cross reference list
		SearchBegin(tag);

		// ******* Section State (default values) *****************

		// frame for the current section
		iFrame   = 1;

		// Maximum frame referenced for the current section
		MaxFrame     = 0;
		MaxFrameLine = 0;
		assert( MaxFrameFile == NULL );  // set at previous end

		// Initialize Table and List levels
		assert( TableLevel == 0 );       // checked at previous end
		assert( ListLevel  == 0 );

		// erase current alignments
		HorizontalAlign = "left";
		VerticalAlign   = "top";

		// erase the current Dollar command
		Dollar = '\0';

		// erase the current Rmark command
		Rmark = '\0';

		// erase the current copyright character
		Cmark = '\0';

		// erase the current white space character
		Wspace = '\0';

		// erase the current program comment character
		NewlineCh = '\0';

		// reset the current escape character
		Escape = EscapeRoot;

		// reset the automatic mindex command connections
		MindexSection = MindexSectionRoot;
		MindexHead    = MindexHeadRoot;
		MindexSubhead = MindexSubheadRoot;

		// reset the current color settings
		assert( ErrorColor   == NULL );    // set at previous end
		assert( CodeColor    == NULL );
		assert( HiliteColor  == NULL );
		CodeColor   = str_alloc("blue");
		ErrorColor  = str_alloc("red");
		HiliteColor = str_alloc("purple");

		// initial state of spell checker
		assert( CheckSpell == 1);


		// reset the current number of characters between tab columns
		ConvertSetTabSize(TabSizeRoot);

		// erase the current heading setting
		InitializeHeading();

		// erase the current special spelling list
		SpellingOkList("");

		// get the default settings for this section
		hilite_get_default();

		// ********************************************************

		// define cross reference point
		number = SectionNumber(CurrentSection);
		C      = DefineCrossReference(tag, "", InputName(), 0, number);
		FreeMem(number);

		assert( C != NULL );

		// output root level macros for math_jax use in this section
		if( strcmp(".htm", Internal2Out("OutputExtension") ) == 0 )
		{	const char* macro_cmd  = "output";
			const char* latex_cmds = NULL;
			math_jax(macro_cmd, latex_cmds);
		}

		// print program progress
		printf(" %s:", tag);

		// cleanup
		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 3631 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1565 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 3638 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1568 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// only one $bgcolor per section
		if( CurrentSection->style.bgcolor != NULL ) fatalomh(
			"At $bgcolor comamnd in line ",
			int2str((yyvsp[-2]).line),
			"\nThere is more than one $bgcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.bgcolor = Color(
			(yyvsp[-2]).line, "$bgcolor", (yyvsp[-1]).str
		);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 3665 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1594 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		OutputString("<big>");
		PushPending((yyvsp[0]).line, "$big");

		(yyval) = (yyvsp[0]);
	}
#line 3677 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1605 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("</big>");
		PopPending((yyvsp[0]).line, "$big");

		(yyval) = (yyvsp[-2]);
	}
#line 3691 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1619 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		OutputString("<b>");
		PushPending((yyvsp[0]).line, "$bold");

		(yyval) = (yyvsp[0]);
	}
#line 3703 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1630 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("</b>");
		PopPending((yyvsp[0]).line, "$bold");

		(yyval) = (yyvsp[-2]);
	}
#line 3717 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1643 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 3724 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1646 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		color_switch((yyvsp[-1]).str, "blue", "black", Escape,
			(yyvsp[-2]).line, "codei", CheckSpell, ErrorColor);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 3745 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1667 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		if( TableLevel == 0 ) fatalomh(
			"$cnext or $cend command in line ",
			int2str((yyvsp[0]).line),
			"\nis not between a $table command ",
			"and its corresponding $tend command",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		OutputString("</td>");
		FormatOutput("<td align='%s' ", HorizontalAlign);
		FormatOutput(" valign='%s'>\n", VerticalAlign);

		PopPending( (yyvsp[0]).line, "$cnext");
		PushPending((yyvsp[0]).line, "$cnext");

		(yyval) = (yyvsp[0]);
	}
#line 3770 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1691 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		(yyval) = (yyvsp[0]);
	}
#line 3778 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1695 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		(yyval) = (yyvsp[0]);
	}
#line 3786 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1702 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		OutputString("<center>");
		PushPending((yyvsp[0]).line, "$center");

		(yyval) = (yyvsp[0]);
	}
#line 3802 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1717 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("</center>");
		PopPending((yyvsp[0]).line, "$center");

		// the end of centering starts a new line
		ConvertAddPrevious(1);

		(yyval) = (yyvsp[-2]);
	}
#line 3818 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1732 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		(yyval).str  = str_alloc("$contents");
		(yyval).line = (yyvsp[0]).line;
	}
#line 3828 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1738 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		(yyval).str  = str_alloc("$childtable");
		(yyval).line = (yyvsp[0]).line;
	}
#line 3838 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1747 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		CrossReference *C;
		char           *number  = NULL;
		char           *printid = NULL;
		char           *converted;

		assert( (yyvsp[0]).str != NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// set the current heading
		SetHeading("Contents");

		if( ConvertPreviousNewline() < 2 )
			ConvertForcedNewline(2 - ConvertPreviousNewline() );

		number  = SectionNumber(CurrentSection);
		assert( *( HeadingAndSubPrintId() ) == '.' );

		if( number[0] == '\0' )
			printid = strjoin(number, HeadingAndSubPrintId()+1);
		else	printid = strjoin(number, HeadingAndSubPrintId());

		OutputString("<b><big>");
		if( PrintableOmhelp() )
		{	FormatOutput2(
				"<a name=\"%s\" id=\"%s\">",
				printid,
				printid
			);
			OutputString(printid);
			OutputString(": ");
		}
		else
		{	converted = ConvertInternalString(
				HeadingAndSubHeading()
			);
			FormatOutput2(
				"<a name=\"%s\" id=\"%s\">",
				converted,
				converted
			);
			FreeMem(converted);
		}

		output_text((yyvsp[0]).line,"Contents",0,'\0',CheckSpell,ErrorColor);
		OutputString("</a></big></b>\n");
		ConvertForcedNewline(1);

		// defined cross reference point
		C = DefineCrossReference(
			CurrentSection->tag,
			HeadingAndSubHeading(),
			InputName(),
			iFrame,
			printid
		);
		assert( C != NULL);
		FreeMem(number);
		FreeMem(printid);

		(yyval) = (yyvsp[0]);
	}
#line 3908 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1816 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		char       *p;
		char       *name;
		char       del;
		SectionInfo *F;
		SectionInfo *list;

		assert( (yyvsp[-2]).str != NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		F = CurrentSection->children;
		while( IsAutomaticSection(F) )
			F = F->next;
		if( F != NULL ) fatalomh(
			"Invalid ",
			(yyvsp[-2]).str,
			" command in line ",
			int2str((yyvsp[-2]).line),
			"\nThere was a previous ",
			"$contents, $children, or $childtable",
			"\ncommannd in this section",
			NULL
		);

		// delimiter is first character in text;
		del        = *((yyvsp[-1]).str);

		// last character in text
		p          = (yyvsp[-1]).str + strlen((yyvsp[-1]).str) - 1;
		if( *p != del ) fatalomh(
			"In delimiter sequence following ",
			(yyvsp[-2]).str,
			" command in line ",
			int2str((yyvsp[-2]).line),
			NULL
		);

		// add the files to the list in reverse order
		// because we add at the front of the list
		list       = NULL;
		while(p - 1 > (yyvsp[-1]).str)
		{	// end of this file name
			*p = '\0';

			// find begining of this file name
			while( *p != del ) p--;

			// skip white space
			name = p + 1;
			while( isspace((int) *name) ) name++;

			// make sure name is not empty
			if( *name == '\0' ) fatalomh(
				"There is only white space between two\n",
				"of the delimiters in the\n",
				(yyvsp[-2]).str,
				" command in line ",
				int2str((yyvsp[-2]).line),
				NULL
			);

			// add to the file list
			F = SectionInfoNew(SectionTree, name);

			// if the file does not exist, generate error
			// message when it is specified and not later
			InputSearch(F->root, F->ext);

			// link it up at the front of the list of children
			F->next = list;
			if( list != NULL )
				list->previous  = F;
			F->parent   = CurrentSection;
			list = F;
		}

		// link this list to parent
		if( CurrentSection->children == NULL )
			CurrentSection->children = list;
		else
		{	F = CurrentSection->children;
			assert( IsAutomaticSection(F) );

			while( F->next != NULL )
				F = F->next;
			F->next        = list;
			list->previous = F;
		}

		if( strcmp((yyvsp[-2]).str, "$children") == 0 )
			OutputString("<CHILDREN>");
		else if( strcmp((yyvsp[-2]).str, "$contents") == 0 )
			OutputString("<CONTENTS>");
		else if( strcmp((yyvsp[-2]).str, "$childtable") == 0 )
			OutputString("<CHILDTABLE>");
		else	assert(0);


		FreeMem((yyvsp[-2]).str);
		FreeMem((yyvsp[-1]).str);

		(yyval).str  = NULL;
		(yyval).line = (yyvsp[-2]).line;
	}
#line 4018 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1925 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		RootHasChildren = 1;

		(yyval).str  = str_alloc("$children");
		(yyval).line = (yyvsp[0]).line;
	}
#line 4030 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1933 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );

		RootHasChildren = 1;

		(yyval) = (yyvsp[0]);
	}
#line 4041 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1942 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		(yyval).str  = str_alloc("$cindex");
		(yyval).line = (yyvsp[0]).line;
	}
#line 4051 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1948 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		(yyval).str  = str_alloc("$mindex");
		(yyval).line = (yyvsp[0]).line;
	}
#line 4061 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1954 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		(yyval).str  = str_alloc("$index");
		(yyval).line = (yyvsp[0]).line;
	}
#line 4071 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1963 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4078 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1966 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		Cmark  = *((yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4093 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1980 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		OutputString("<code><font color=\"");
		OutputString(CodeColor);
		OutputString("\">");
		PushPending((yyvsp[0]).line, "$code");

		(yyval) = (yyvsp[0]);
	}
#line 4107 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1993 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("</font></code>");
		PopPending((yyvsp[0]).line, "$code");

		(yyval) = (yyvsp[-2]);
	}
#line 4121 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 113:
#line 2006 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4128 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 114:
#line 2009 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		FreeMem(CodeColor);
		CodeColor = Color((yyvsp[-2]).line, "$codecolor", (yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 4143 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 115:
#line 2024 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4150 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 116:
#line 2027 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		SkipCodep((yyvsp[-1]).line, (yyvsp[-1]).str);

		if( ExecuteFile != NULL )
		{	char *text;
			int len;

			FreeMem(ExecuteFile);
			ExecuteFile = NULL;

			text = str_alloc((yyvsp[-1]).str);
			len  = strlen(text);

			assert( len > 1 );
			assert( text[0] == '\n' );
			assert( text[len-1] == '\n' );
			assert( ExecuteNextFile() != NULL );

			text[len-1] = '\0';
			ExecuteWriteFile(text + 1);

			FreeMem(text);
		}

		OutputString("<code><font color='");
		OutputString(CodeColor);
		// need space after > so first newline is not ignored; see
		// https://bugzilla.mozilla.org/show_bug.cgi?id=476324
		OutputString("'><pre style='display:inline'> ");
		// already in preformat mode, pre is false in call
		{	int pre  = 2;
			hilite_out(
				"codep",
				(yyvsp[-1]).line,
				CheckSpell,
				ErrorColor,
				HiliteColor,
				pre,
				(yyvsp[-1]).str
			);
		}
		OutputString("</pre></font></code>\n");

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4209 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 117:
#line 2085 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4216 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 118:
#line 2088 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4229 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 119:
#line 2100 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4236 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 120:
#line 2103 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *text;
		char *tag;
		char *head;
		char *subhead;
		char *frame;
		char *external;
		CrossReference *C;

		int checkspell;
		int ntoken;
		int i, j;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}


		// split text into tokens
		ntoken = SplitText((yyvsp[-2]).line, "$cref", (yyvsp[-1]).str);
		if( ntoken > 4 ) fatalomh(
			"At $cref command in line ",
			int2str((yyvsp[-2]).line),
			"\nMore than 5 delimiters in $cref command",
			NULL
		);

		// text for reference
		text = (yyvsp[-1]).str + 1;
		tag  = text + strlen(text) + 1;
		UniformWhiteSpace(text);
		if( text[0] == '\0' ) fatalomh(
			"At $cref command in line ",
			int2str((yyvsp[-2]).line),
			"\nthe text portion is only white space",
			NULL
		);

		// tag
		if( ntoken >= 2 )
		{	head = tag + strlen(tag) + 1;
			UniformWhiteSpace(tag);
			if( tag[0] == '\0' ) fatalomh(
				"At $cref command in line ",
				int2str((yyvsp[-2]).line),
				"\nthe tag portion is only white space",
				NULL
			);
		}
		else
		{	head = ""; // avoid unitialized warning
			tag = text;
		}

		// head
		if( ntoken >= 3 )
		{	subhead = head + strlen(head) + 1;
			UniformWhiteSpace(head);
			if( head[0] == '\0' ) fatalomh(
				"At $cref command in line ",
				int2str((yyvsp[-2]).line),
				"\nthe head portion is only white space",
				NULL
			);
		}
		else
		{	subhead = ""; // avoid unitialized warning
			head    = "";
		}

		// subhead
		if( ntoken >= 4 )
		{	UniformWhiteSpace(subhead);
			if( subhead[0] == '\0' ) fatalomh(
				"At $cref command in line ",
				int2str((yyvsp[-2]).line),
				"\nthe subhead portion is only white space",
				NULL
			);
		}
		else	subhead = "";

		// target frame (part of xref) has been deprecricated.
		frame = "";

		// this is not an external reference
		external = "false";

		// attach the subheading to the heading
		if( subhead[0] != '\0' )
		{	assert( subhead >=  head + strlen(head) + 1);
			i         = strlen(head);
			j         = 0;
			head[i++] = '.';
			while( subhead[j] != '\0' )
				head[i++] = subhead[j++];
			head[i] = '\0';
		}

		// output the cross reference jump without spell checking
		checkspell = CheckSpell;
		CheckSpell = 0;
		HrefOutputPass1(tag, head, external, frame, "true");

		// output other information with spell checking
		if( ntoken >= 2 )
			CheckSpell = checkspell;

		OutPre((yyvsp[-1]).line, text);
		HrefEnd("\n");

		// search for this cross reference
		C = FindCrossReference(tag, head);
		if( C == NULL )
			C = CreateCrossReference(tag, head, InputName());
		assert( C != NULL );

		// restore spell checking to initial setting
		CheckSpell = checkspell;

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4369 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 121:
#line 2235 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	time_t     time_t_time;
		struct tm     *tm_time;
		char        *char_time;
		char          date[13];
		int                  i;

		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		time(&time_t_time);
		tm_time = localtime( &time_t_time );
		char_time = asctime( tm_time);

		// month space day (3 + 1 + 2 characters)
		for(i = 0; i < 6; i++)
			date[i] = char_time[i + 4];

		// comma space year end
		date[6] = ',';
		date[7] = ' ';
		for(i = 0; i < 4; i++)
			date[i + 8] = char_time[i + 20];
		date[12] = '\0';

		OutputString(date);

		(yyval) = (yyvsp[0]);
	}
#line 4406 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 122:
#line 2272 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4413 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 123:
#line 2275 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		Dollar = *((yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4428 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 124:
#line 2289 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// make sure there was a section command
		if( CurrentSection->title == NULL ) fatalomh(
			"There was no $section command\n",
			"between the $end command on line ",
			int2str((yyvsp[0]).line),
			" and the previous $begin command",
			NULL
		);

		// make sure maximum frame referenced was valid
		assert( MaxFrame <= iFrame || MaxFrameFile != NULL );
		if( MaxFrame > iFrame ) fatalomh(
			"Frame number ",
			int2str(MaxFrame),
			" does not exist in the current section\n",
			"This frame is referenced in $xref command in line ",
			int2str(MaxFrameLine),
			"\nof file ",
			MaxFrameFile,
			NULL
		);

		// make sure any execute has been written
		if( ExecuteFile != NULL ) fatalomh(
			"No $codep command follows the $execute command\n",
			"in line ",
			int2str(ExecuteLine),
			" of file ",
			ExecuteFile,
			NULL
		);

		// if this is the root section, copy its hilite settings
		if( CurrentSection == SectionTree )
			hilite_set_default();

		// check there are no pending commands
		if( NumberPending() > 0 )
			OmhPendingError((yyvsp[0]).line, "$end");

		// the check above should have asserted the following
		assert( TableLevel == 0);
		assert( ListLevel  == 0);

		// copy default style from starting file to values not set
		if( CurrentSection == SectionTree )
		{	SectionInfo *Contents = CurrentSection->children;
			assert(Contents != NULL );
			SectionDefaultStyle(Contents, SectionTree);

			// xml only: keep macros defined in the root section
			LatexMacroKeep();
		}
		else
		{	SectionDefaultStyle(CurrentSection, SectionTree);

			// xml only: remove the macros defined in this section
			LatexMacroFree();
			LatexMacroKeep();
		}

		// get the keywords for this section
		assert( CurrentSection->keywords == NULL );
		CurrentSection->keywords = SearchGetKeywords();

		// terminate search keys for current section
		SearchEnd();

		// output name of current input file
		if( DebugOmhelp ) FormatOutput2(
			"\n<hr%sInput File: %s\n",
			Internal2Out("SelfTerminateCmd"),
			InputName()
		);

		// keep track of how many end commands
		EndCount++;

		FreeMem( MaxFrameFile );
		FreeMem( ErrorColor   );
		FreeMem( CodeColor    );
		FreeMem( HiliteColor  );

		MaxFrameFile = NULL;
		ErrorColor   = NULL;
		CodeColor    = NULL;
		HiliteColor  = NULL;

		PopOutput();

		(yyval) = (yyvsp[0]);
	}
#line 4531 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 125:
#line 2392 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	// end of an input file

		SectionInfo *S;
		int          done;

		// initialize I to avoid warning
		// (compiler does not know it will be reset before used)
		SectionInfo *I = NULL;

		assert( (yyvsp[0]).str != NULL );

		if( IncludeFrom != NULL )
		{	// not much to do in include file case
			InputPop();

			FreeMem(IncludeFrom);
			IncludeFrom = NULL;

			// no need for the previous command key character
			FreeMem((yyvsp[0]).str);
			(yyvsp[0]).str = NULL;
		}
		else
		{
		// not include file case ***********************************

		if( BeginCount == 0 ) fatalomh(
			"No ",
			(yyvsp[0]).str,
			"begin commands in current input file",
			NULL
		);

		// lexomh ignores all commands until $begin is found
		assert( BeginCount >= EndCount );

		if( BeginCount > EndCount ) fatalomh(
			"There are more ",
			(yyvsp[0]).str,
			"begin than ",
			(yyvsp[0]).str,
			"end commmands\n",
			"in the current input file",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		// done with the previous command key character
		FreeMem((yyvsp[0]).str);
		(yyvsp[0]).str = NULL;

		// done with this input file
		InputPop();

		// pointers relative to current file
		S = CurrentSection;

		// back up at this level because one input file can have
		// multiple sections in it
		while( S->previous != NULL )
			S = S->previous;

		// check for an unread input file  (skip automatic sections)
		done = 1;
		while( done && S != NULL )
		{
			// check children first
			I    = S->children;
			while( IsAutomaticSection(I) )
				I = I->next;
			done = I == NULL || I->tag != NULL;

			// check siblings next
			if( done )
			{	I    = S->next;
				while( IsAutomaticSection(I) )
					I = I->next;
				done = I == NULL || I->tag != NULL;
			}

			if( done )
			{
				if( S->next != NULL )
				{	// move forward at current level
					// undoing the back up above
					S = S->next;
				}
				else
				{	// completed this entire level
					S = S->parent;
					assert( S == NULL ||
						SectionTagNotDefined(
							S->children
						) == NULL
					);
				}
			}
		}

		// erase the current heading setting
		InitializeHeading();

		if( I != NULL )
		{	// start reading next file
			PushOmhInput(I);
			CurrentSection = I;

		}
		else
		{
			if( RootHasChildren )
				Appendices();
			FinishUp();
			return(1);
		}

		// end of not include file case *****************************
		}

		(yyval) = (yyvsp[0]);
	}
#line 4657 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 126:
#line 2517 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4664 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 127:
#line 2520 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		FreeMem(ErrorColor);
		ErrorColor = Color((yyvsp[-2]).line, "$errorcolor", (yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 4679 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 128:
#line 2534 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4686 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 129:
#line 2537 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		Escape = *((yyvsp[-1]).str);

		if( CurrentSection->parent == NULL )
			EscapeRoot = Escape;

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4704 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 130:
#line 2555 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4711 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 131:
#line 2558 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// check for already set
		if( ExecuteFile !=  NULL ) fatalomh(
			"There is no $codep command between the\n",
			"$execute command in line ",
			int2str(ExecuteLine),
			" of file ",
			ExecuteFile,
			"\nand the $execute command in line ",
			int2str((yyvsp[-2]).line),
			" of file ",
			InputName(),
			NULL
		);

		// file name for error reporting
		ExecuteFile = str_alloc(InputName());
		ExecuteLine = (yyvsp[-2]).line;

		// file name to write to
		assert( CurrentSection->tag != NULL );
		ExecuteSetFile((yyvsp[-1]).str, CurrentSection->tag);

		// insert link to execute
		FormatOutput("<EXECUTE=\"%s\">", (yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4754 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 132:
#line 2601 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4761 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 133:
#line 2604 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		int above;
		int below;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// check there are no pending commands
		if( NumberPending() > 0 )
			OmhPendingError((yyvsp[-2]).line, "$fend");

		if( ! (PrintableOmhelp() | NoFrame() ) )
		{
			if( iFrame >= MAX_FRAME ) fatalomh(
				"\nThere are more than ",
				int2str(MAX_FRAME),
				" frames requested for this section\n",
				"OMhelp Cannot satisfy the $fend request in ",
				"line ",
				int2str((yyvsp[-2]).line),
				NULL
			);

			above   = atoi((yyvsp[-1]).str);
			if( above < 5 ) fatalomh(
				"In the $fend command in line ",
				int2str((yyvsp[-2]).line),
				"\nthe requested frame size ",
				"is less than 5 percent\n",
				NULL
			);

			below = CurrentSection->Frame[iFrame - 1] - above;
			if( below < 5 ) fatalomh(
				"At the $fend command in line ",
				int2str((yyvsp[-2]).line),
				"\nThe sum of the frame sizes in this ",
				"$fend command and in the previous\n",
				"$fend commands in this section ",
				"is greater than 95 percent",
				NULL
			);

			CurrentSection->Frame[iFrame - 1] = above;
			CurrentSection->Frame[iFrame]     = below;
			CurrentSection->nFrame = iFrame   = iFrame + 1;

			OutputString("\n<FEND>\n");

			// a new frame separates as well as two newlines
			ConvertAddPrevious(2);


		}
		else
		{	// use two newlines to separate in printable version
			ConvertForcedNewline( 2 - ConvertPreviousNewline() );
		}
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 4833 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 134:
#line 2675 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		OutputString("<code>");
		PushPending((yyvsp[0]).line, "$fixed");

		(yyval) = (yyvsp[0]);
	}
#line 4845 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 135:
#line 2686 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("</code>");
		PopPending((yyvsp[0]).line, "$fixed");

		(yyval) = (yyvsp[-2]);
	}
#line 4859 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 136:
#line 2699 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4866 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 137:
#line 2702 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		CrossReference *C;
		char           *noEscape;
		char           *converted;
		char           *number = NULL;
		char           *printid = NULL;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		if( TableLevel > 0 ) fatalomh(
			"The $head command in line ",
			int2str((yyvsp[-2]).line),
			" is inside a table; i.e.,\n",
			"between a $table and the corresponding $tend",
			NULL
		);
		// make sure no # characters in heading
		if( strchr((yyvsp[-1]).str, '#') != NULL ) fatalomh(
			"$head command in line ",
			int2str((yyvsp[-2]).line),
			" has heading\n",
			(yyvsp[-1]).str,
			"\nThe character '#' is not allowed in headings",
			NULL
		);

		// version of heading without escape characters
		noEscape = str_alloc((yyvsp[-1]).str);
		if( MindexHead )
			StrRemove(noEscape, Escape);

		// convert to unifrom white space format
		UniformWhiteSpace(noEscape);

		if( ConvertPreviousNewline() < 2 )
			ConvertForcedNewline(2 - ConvertPreviousNewline() );

		// set corresponding current heading
		SetHeading(noEscape);

		number  = SectionNumber(CurrentSection);
		assert( *( HeadingAndSubPrintId() ) == '.' );
		if( number[0] == '\0' )
			printid = strjoin(number, HeadingAndSubPrintId()+1);
		else	printid = strjoin(number, HeadingAndSubPrintId() );

		OutputString("<b><big>");
		if( PrintableOmhelp() )
		{	FormatOutput2(
				"<a name=\"%s\" id=\"%s\">",
				printid,
				printid
			);
			OutputString(printid);
			OutputString(": ");
		}
		else
		{	converted = ConvertInternalString(
				HeadingAndSubHeading()
			);
			FormatOutput2(
				"<a name=\"%s\" id=\"%s\">",
				converted,
				converted
			);
			FreeMem(converted);
		}

		output_text((yyvsp[-1]).line,noEscape,0,'\0',CheckSpell,ErrorColor);
		OutputString("</a></big></b>\n");

		// defined cross reference point
		C = DefineCrossReference(
			CurrentSection->tag,
			HeadingAndSubHeading(),
			InputName(),
			iFrame,
			printid
		);
		assert( C != NULL );
		FreeMem(number);
		FreeMem(printid);

		if( MindexHead )
		{	char *lower = StrLowAlloc((yyvsp[-1]).str);

			// add keywords to search for this section
			SearchKeywords(lower, Escape, AutomaticIndexIgnore);

			MultipleIntoIndex(
				lower,
				CurrentSection->tag,
				HeadingAndSubHeading(),
				Escape,
				AutomaticIndexIgnore
			);

			FreeMem(lower);
		}

		FreeMem(noEscape);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);

		PreviousOutputWasHeading = 1;
	}
#line 4984 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 138:
#line 2820 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 4991 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 139:
#line 2823 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	int n_command;
		n_command = SplitText((yyvsp[-2]).line, "hilitecmd", (yyvsp[-1]).str);
		hilite_command((yyvsp[-2]).line, n_command, (yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);
	}
#line 5002 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 140:
#line 2833 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5009 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 141:
#line 2836 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		FreeMem(HiliteColor);
		HiliteColor = Color((yyvsp[-2]).line, "$hilitecolor", (yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 5024 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 142:
#line 2851 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5031 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 143:
#line 2854 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	int n_token;
		n_token = SplitText((yyvsp[-2]).line, "hiliteseq", (yyvsp[-1]).str);
		hilite_seq((yyvsp[-2]).line, n_token, (yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);
	}
#line 5042 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 144:
#line 2863 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5049 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 145:
#line 2866 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *url;
		char *frame;
		char *link;
		char *tag;
		char *heading;

		int checkspell;
		int ntoken;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// initial state of spell checker
		checkspell = CheckSpell;

		// split text into tokens
		ntoken = SplitText((yyvsp[-2]).line, "$href", (yyvsp[-1]).str);
		if( ntoken > 3 ) fatalomh(
			"In the $href command in line ",
			int2str((yyvsp[-2]).line),
			"\nTo many delimiters in the delimiter sequence",
			NULL
		);

		// internet address for reference
		url = (yyvsp[-1]).str + 1;

		// make sure url is not empty
		if( WhiteSpace(url) ) fatalomh(
			"In the $href command in line ",
			int2str((yyvsp[-2]).line),
			"\nOnly white space between first 2 delimiters",
			NULL
		);

		// make sure not using back slashes in address
		// because they do not work when displaying on Unix
		if( strchr(url, '\\') != NULL ) fatalomh(
			"In the $href command in line ",
			int2str((yyvsp[-2]).line),
			"\nMust use \"/\" in place of \"\\\" in uri",
			NULL
		);

		// linking text for reference
		if( ntoken < 2 )
			link = "";
		else
		{	link = url + strlen(url) + 1;
			if( WhiteSpace(link) ) fatalomh(
			"In the $href command in line ",
			int2str((yyvsp[-2]).line),
			"\nlinking text specified as empty",
			NULL
			);
		}

		// displaying frame for the reference
		if( ntoken < 3 || PrintableOmhelp() )
			frame = "";
		else	frame = link + strlen(link) + 1;

		// clip leading and trailing white space in all arugments
		ClipWhiteSpace(url);
		if( ntoken >= 2 )
			ClipWhiteSpace(link);
		if( ntoken >= 3 && (! PrintableOmhelp() ) )
			ClipWhiteSpace(frame);


		// Split the URL to a file and anchor in that file
		tag     = str_alloc(url);
		heading = strchr(tag, '#');
		if( heading != NULL )
		{	*heading = '\0';
			heading++;
		}
		else	heading = "\0";


		// output the internet reference
		CheckSpell = 0;
		HrefOutputPass1(tag, heading, "true", frame, "true");
		HrefAddList(
			CurrentSection->tag,
			HeadingAndSubHeading(),
			tag,
			heading
		);

		if( ntoken < 2 )
			OutPre((yyvsp[-1]).line, url);
		else	OutPre((yyvsp[-1]).line, link);
		HrefEnd("\n");

		if( ntoken >= 2 && PrintableOmhelp() )
		{	OutputString(" (");
			output_text((yyvsp[-1]).line,url,0,'\0',CheckSpell,ErrorColor);
			OutputString(") ");
		}

		CheckSpell = checkspell;
		FreeMem(tag);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 5167 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 146:
#line 2983 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5174 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 147:
#line 2986 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		color_switch((yyvsp[-1]).str, "black", "blue", Escape,
			(yyvsp[-2]).line, "icode", CheckSpell, ErrorColor);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 5195 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 148:
#line 3006 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		(yyval).str  = str_alloc("$icon");
		(yyval).line = (yyvsp[0]).line;

	}
#line 5206 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 149:
#line 3013 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		(yyval).str  = str_alloc("$image");
		(yyval).line = (yyvsp[0]).line;
	}
#line 5216 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 150:
#line 3023 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {

		char *root;
		char *ext;
		char *name;
		char *fullname;

		char *localname;

		int  i;

		assert( (yyvsp[-2]).str != NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// split text into tokens
		int ntoken = SplitText((yyvsp[-2]).line, (yyvsp[-2]).str, (yyvsp[-1]).str);
		if( ntoken > 2 ) fatalomh(
			(yyvsp[-2]).str,
			" command in line ",
			int2str((yyvsp[-2]).line),
			"\nMore than 3 delimiters in command",
			NULL
		);

		// first token
		char* file_in  = (yyvsp[-1]).str + 1;
		char* file_out = NULL;
		if( ntoken == 2 )
		{	file_out = file_in + strlen(file_in) + 1;
			ClipWhiteSpace(file_out);
		}
		ClipWhiteSpace(file_in);


		// determine root and extension
		InputSplitName(&root, &ext, file_in);

		// check for case of default extension
		if( ext[0] == '\0' )
		{	FreeMem(ext);
			ext = str_alloc(".gif");
		}
		else if( stricmp( ext, Internal2Out("OutputExtension") ) == 0 )
		fatalomh(
			"The file ",
			file_in,
			" following command ",
			(yyvsp[-2]).str,
			" at line ",
			int2str((yyvsp[-2]).line),
			"\nuses ",
			Internal2Out("OutputExtension"),
			" for its file extension",
			NULL
		);


		// file name including extension
		name     = strjoin(root, ext);
		fullname = strjoin( InputSearch(root, ext) , name);

		const char* file = NULL;
		if( file_out != NULL )
			file = file_out;
		else	file = fullname;

		// determine the local file name
		i = strlen(file) - 1;
		while( i > 0 && file[i] != '\\' && file[i] != '/' )
			i--;

		if( file_out != NULL )
		{	if( i > 0 ) fatalomh(
				"The file ",
				file_out,
				" in command ",
				(yyvsp[-2]).str,
				" at line ",
				int2str((yyvsp[-2]).line),
				"\nuses either the / or \\ character",
				NULL
			);
			file = file_out;
			i = strlen(ext);
			int j = strlen(file_out);
			int ok = 1;
			while(i--)
			{	j--;
				ok = ok && (file_out[j] == ext[i]);
			}
			if( ! ok ) fatalomh(
				"In command ",
				(yyvsp[-2]).str,
				" at line ",
				int2str((yyvsp[-2]).line),
				"\nFile extensions do not match between\n",
				file_in,
				"\n",
				file_out,
				NULL
			);

		}
		else
		{	if( i > 0 )
				file = fullname + i + 1;
			else	file = fullname;
		}
		localname = StrLowAlloc(file);
		copyfile(localname, fullname);

		FreeMem(fullname);
		FreeMem(name);
		FreeMem(ext);
		FreeMem(root);


		if( strcmp( (yyvsp[-2]).str, "$icon" ) == 0 )
		{

			if( PreviousOutputWasHeading )
			{	ConvertForcedNewline(1);
				PreviousOutputWasHeading = 0;
			}

			FormatOutput2(
				"<img src=\"%s\" valign=\"top\"%s\n",
				localname,
				Internal2Out("SelfTerminateCmd")
			);
		}
		else if( strcmp( (yyvsp[-2]).str, "$image" ) == 0 )
		{

			// do not need extra new line after previous heading
			if( PreviousOutputWasHeading )
				PreviousOutputWasHeading = 0;

			OutputString("<center>");
			FormatOutput2(
				"<img src=\"%s\"%s\n",
				localname,
				Internal2Out("SelfTerminateCmd")
			);
			OutputString("</center>");

			// the end of centering starts a new line
			ConvertAddPrevious(1);
		}
		else	assert(0);

		FreeMem((yyvsp[-2]).str);
		FreeMem((yyvsp[-1]).str);
		FreeMem(localname);

		(yyval).str  = NULL;
		(yyval).line = (yyvsp[-2]).line;
	}
#line 5380 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 151:
#line 3186 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5387 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 152:
#line 3189 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char  *root;
		char  *ext;
		char  cmd_key_char;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( IncludeFrom != NULL ) fatalomh(
			"Cannot use $include command on line ",
			int2str((yyvsp[-2]).line),
			" because\n",
			InputName(),
			" was included by $include \n",
			"in line ",
			int2str(IncludeLine),
			" of ",
			IncludeFrom,
			NULL
		);
		IncludeFrom = str_alloc(InputName());
		IncludeLine = (yyvsp[-2]).line;

		root = str_alloc((yyvsp[-1]).str);

		// determine the start of the extension
		ext = root + strlen(root) - 1;
		while( (ext > root) & (*ext != '.') )
			ext--;

		// separate root and extension
		if( ext > root )
		{	*ext++ = '\0';
			ext    = strjoin(".", ext);
		}
		else	ext    = str_alloc("");

		// remember the command key character in the original file
		cmd_key_char = GetCommandKeyCharacter();

		// set input file
		InputPush(root, ext, -1);

		// keep the same command key character in the included file
		SetCommandKeyCharacter(cmd_key_char);

		FreeMem(ext);
		FreeMem(root);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 5445 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 153:
#line 3247 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *text = (yyvsp[-1]).str;
		int line   = (yyvsp[-2]).line;


		assert( (yyvsp[-2]).str != NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// add keywords to search for this section
		SearchKeywords(text, Escape, "");

		// check for seplling error
		if( CheckSpell )
		{
			const char *s = (yyvsp[-1]).str;
			int i, j;
			int nchar;
			const char* next_error = SpellingError(s, &nchar);

			i = 0;
			j = 0;
			while( next_error != NULL )
			{	i = next_error - s;

				// advance line counter to spelling error
				while( j < i )
				{	line += (s[j] == '\n');
					j++;
				}


				// begin standard output version of error
				printf(
					"\nOMhelp Warning: spelling "
					"in line %d of file %s: ",
					line,
					InputName()
				);

				// begin browser version of error
				if( ConvertPreviousNewline() == 0 )
					ConvertForcedNewline(1);
				OutputString("<font color=\"");
				OutputString(ErrorColor);
				OutputString("\">");

				assert( nchar > 0 );
				while( nchar-- )
				{	if( isspace((int) s[i]) )
					{	printf(" ");
						ConvertOutputCh(' ', 0);
					}
					else
					{	printf("%c", s[i]);
						ConvertOutputCh(s[i], 0);
					}
					i++;
				}

				// end standard output version of error
				printf("\n");

				// end browser version of error
				OutputString("</font>");
				ConvertForcedNewline(1);

				// search for next error
				next_error = SpellingError(s + i, &nchar);
			}
		}


		// new entry
		if( strcmp((yyvsp[-2]).str, "$index") == 0 ) InsertInIndex(
			text,
			CurrentSection->tag,
			HeadingAndSubHeading(),
			Escape
		);
		else if( strcmp((yyvsp[-2]).str, "$cindex") == 0 ) CycleIntoIndex(
			text,
			CurrentSection->tag,
			HeadingAndSubHeading(),
			Escape
		);
		else if( strcmp((yyvsp[-2]).str, "$mindex") == 0 ) MultipleIntoIndex(
			text,
			CurrentSection->tag,
			HeadingAndSubHeading(),
			Escape,
			""
		);
		else	assert(0);

		FreeMem((yyvsp[-2]).str);
		FreeMem((yyvsp[-1]).str);

		(yyval).str  = NULL;
		(yyval).line = (yyvsp[-2]).line;
	}
#line 5550 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 154:
#line 3351 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		OutputString("<i>");
		PushPending((yyvsp[0]).line, "$italic");
		ItalicCount++;

		(yyval) = (yyvsp[0]);
	}
#line 5563 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 155:
#line 3363 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("</i>");
		PopPending((yyvsp[0]).line, "$italic");
		ItalicCount--;

		(yyval) = (yyvsp[-2]);
	}
#line 5579 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 230:
#line 3452 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]);
	}
#line 5586 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 231:
#line 3458 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5593 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 232:
#line 3461 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( strcmp(".xml", Internal2Out("OutputExtension") ) == 0 )
		{	int BlockDisplay;

			LatexLexPut((yyvsp[-1]).line, (yyvsp[-1]).str);
			BlockDisplay = texparse();

			ConvertAddPrevious( - ConvertPreviousNewline() );
			if( BlockDisplay )
				ConvertAddPrevious(1);

			// note texparse uses PreviousOmhelpOutputWasHeading()
			PreviousOutputWasHeading = 0;
		}
		else
		{	int checkspell = CheckSpell;
			CheckSpell     = 0;

			assert( strcmp(".htm",
				Internal2Out("OutputExtension") ) == 0 );


			// if output begins with a preformatted new line
			// do not need an extra one to for previous heading
			if( PreviousOutputWasHeading )
			{	char *s = (yyvsp[-1]).str;
				char ch = *s++;

				int newline = 0;

				while( isspace((int) ch) )
				{	newline = newline || (ch == '\n');
					ch = *s++;
				}

				if( ! newline )
					ConvertForcedNewline(1);

				PreviousOutputWasHeading = 0;
			}
			// html: only add macros defined in the root section
			const char* macro_cmd  = "ignore";
			if( CurrentSection == SectionTree )
				macro_cmd = "add";
			const char* latex_cmds = (yyvsp[-1]).str;
			math_jax(macro_cmd, latex_cmds);

			CheckSpell = checkspell;
		}

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 5656 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 233:
#line 3524 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		if( ListLevel <= 0 ) fatalomh(
			"There is no matching $list command preceeding\n",
			"the $lend command in line ",
			int2str((yyvsp[0]).line),
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		ListLevel--;
		if( ListOrdered[ListLevel] )
			OutputString("</li></ol>\n");
		else	OutputString("</li></ul>\n");

		PopPending((yyvsp[0]).line, "$list");
		(yyval) = (yyvsp[0]);
	}
#line 5679 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 234:
#line 3546 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5686 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 235:
#line 3549 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// only one $linkcolor per section
		if( CurrentSection->style.linkcolor != NULL ) fatalomh(
			"At $linkcolor comamnd in line ",
			int2str((yyvsp[-2]).line),
			"\nThere is more than one $linkcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.linkcolor = Color(
			(yyvsp[-2]).line, "$linkcolor", (yyvsp[-1]).str
		);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 5713 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 236:
#line 3575 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5720 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 237:
#line 3578 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	// initalize cmd to avoid warning
		// (compiler does not know fatalerr will not return)
		char *cmd = NULL;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );


		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		if( ListLevel == MAX_LIST_LEVEL ) fatalomh(
			"At $list command in line ",
			int2str((yyvsp[-2]).line),
			"\nMore than ",
			int2str(MAX_LIST_LEVEL),
			" levels of nested lists requested",
			NULL
		);

		ListOrdered[ListLevel]= 1;

		if( strcmp((yyvsp[-1]).str, "disk") == 0 )
		{	cmd  = "<ul type=\"disk\"><li>";
			ListOrdered[ListLevel] = 0;
		}
		else if( strcmp((yyvsp[-1]).str, "circle") == 0 )
		{	cmd  = "<ul type=\"circle\"><li>";
			ListOrdered[ListLevel] = 0;
		}
		else if( strcmp((yyvsp[-1]).str, "square") == 0 )
		{	cmd  = "<ul type=\"square\"><li>";
			ListOrdered[ListLevel] = 0;
		}
		else if( strcmp((yyvsp[-1]).str, "number") == 0 )
			cmd  = "<ol type=\"1\"><li>";
		else if( strcmp((yyvsp[-1]).str, "alpha") == 0 )
			cmd  = "<ol type=\"a\"><li>";
		else if( strcmp((yyvsp[-1]).str, "Alpha") == 0 )
			cmd  = "<ol type=\"A\"><li>";
		else if( strcmp((yyvsp[-1]).str, "roman") == 0 )
			cmd  = "<ol type=\"i\"><li>";
		else if( strcmp((yyvsp[-1]).str, "Roman") == 0 )
			cmd  = "<ol type=\"I\"><li>";
		else fatalomh(
			"At $list command in line ",
			int2str((yyvsp[-2]).line),
			"\n",
			(yyvsp[-1]).str,
			" is not a valid marker for a $list command",
			NULL
		);

		ListLevel++;

		OutputString(cmd);

		FreeMem((yyvsp[-1]).str);

		PushPending((yyvsp[-2]).line, "$list");

		(yyval) = (yyvsp[-2]);
	}
#line 5790 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 238:
#line 3647 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		if( ListLevel == 0 ) fatalomh(
			"The $lnext command in line ",
			int2str((yyvsp[0]).line),
			"\nis not inside of a list; i.e.,\n",
			"not between a $list and the corresponding $lend",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		OutputString("</li><li>\n");

		(yyval) = (yyvsp[0]);
	}
#line 5810 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 239:
#line 3666 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5817 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 240:
#line 3669 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	int   ntoken;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// split text into tokens
		ntoken = SplitText((yyvsp[-2]).line, "$math", (yyvsp[-1]).str);


		// if output begins with a preformatted new line
		// do not need an extra one to for previous heading
		if( PreviousOutputWasHeading )
		{	char *s = (yyvsp[-1]).str + 1;
			char ch = *s++;

			int newline = 0;

			while( isspace((int) ch) )
			{	newline = newline || (ch == '\n');
				ch = *s++;
			}

			if( ! newline )
				ConvertForcedNewline(1);

			PreviousOutputWasHeading = 0;
		}

		OutputMath(ntoken, (yyvsp[-1]).str + 1, Escape, ItalicCount > 0);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 5857 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 241:
#line 3709 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5864 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 242:
#line 3712 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *tag;
		char *next;
		CrossReference *C;
		int nref;
		int checkspell;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// suspend spell checking
		checkspell = CheckSpell;
		CheckSpell = 0;

		// split text into tokens
		nref = SplitText((yyvsp[-2]).line, "$mref", (yyvsp[-1]).str);

		// tag for reference
		tag = (yyvsp[-1]).str + 1;

		// output the cross reference jump
		while(nref--)
		{	// get next pointer before cliping white space
			next = strlen(tag) + tag + 1;

			// convert to unifrom white space format
			UniformWhiteSpace(tag);

			// make sure take is not empty
			if( tag[0] == '\0' ) fatalomh(
				"At $mref command in line ",
				int2str((yyvsp[-2]).line),
				"only white space between two delimiters ",
				"following $mref command",
				NULL
			);

			// output the cross reference
			OutputString(" ");
			HrefOutputPass1(tag, "", "false", "", "true");
			OutPre((yyvsp[-1]).line, tag);
			HrefEnd("\n");

			// search for this cross reference
			C = FindCrossReference(tag, "");
			if( C == NULL )
				C = CreateCrossReference(tag, "", InputName());
			assert( C != NULL );

			// next cross reference
			tag = next;

			// separator between entries
			if( nref >= 1)
				OutputString(", ");
		}

		// restore spell checking to original state
		CheckSpell = checkspell;

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 5938 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 243:
#line 3786 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {       fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
        }
#line 5945 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 244:
#line 3789 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	int ntoken;

		// split text into tokens
		ntoken = SplitText((yyvsp[-2]).line, "$navigate", (yyvsp[-1]).str);

		// set the current navigation sequence
		SectionNavigate(CurrentSection, ntoken, (yyvsp[-1]).str + 1, (yyvsp[-2]).line);

		// done with the delimiter sequence
		FreeMem((yyvsp[-1]).str);
	}
#line 5961 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 245:
#line 3805 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5968 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 246:
#line 3808 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( strlen((yyvsp[-1]).str)  > 1 ) fatalomh(
			"More that one character is specified by the\n",
			"$newlinech comamnd in line ",
			int2str((yyvsp[-2]).line),
			NULL
		);

		NewlineCh = *((yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 5991 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 247:
#line 3830 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 5998 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 248:
#line 3833 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	int pre = 0;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("<span style='white-space: nowrap'>");
		output_text((yyvsp[-1]).line,(yyvsp[-1]).str,pre,'\0',CheckSpell,ErrorColor);
		OutputString("</span>\n");

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6017 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 249:
#line 3851 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		CheckSpell = 0;
		PushPending((yyvsp[0]).line, "$nospell");

		(yyval) = (yyvsp[0]);
	}
#line 6029 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 250:
#line 3862 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		CheckSpell = 1;
		PopPending((yyvsp[0]).line, "$nospell");

		(yyval) = (yyvsp[-2]);
	}
#line 6043 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 255:
#line 3882 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6050 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 256:
#line 3885 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		OutputMath(1, (yyvsp[-1]).str, '\0', ItalicCount > 0);

		FreeMem((yyvsp[-1]).str);

		(yyval).str  = NULL;
		(yyval).line = (yyvsp[-1]).line;
	}
#line 6070 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 257:
#line 3904 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		char *path;
		char *ext;
		int ntoken;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// only use path command at root level
		if( CurrentSection == SectionTree )
		{
			// split text into tokens
			ntoken = SplitText((yyvsp[-2]).line, "$path", (yyvsp[-1]).str);
			if( ntoken != 2 ) fatalomh(
				"At $path comamnd in line ",
				int2str((yyvsp[-2]).line),
				"\n$path command expects three delimiters",
				NULL
			);

			// path token
			path = (yyvsp[-1]).str + 1;

			// extension token
			ext  = path + strlen(path) + 1;

			InputAddPath(path, ext);
		}


		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6110 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 258:
#line 3943 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6117 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 259:
#line 3946 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// if output begins with a preformatted new line
		// do not need an extra one to for previous heading
		if( PreviousOutputWasHeading )
		{	char *s = (yyvsp[-1]).str;
			char ch = *s++;

			int newline = 0;

			while( isspace((int) ch) )
			{	newline = newline || (ch == '\n');
				ch = *s++;
			}

			if( ! newline )
				ConvertForcedNewline(1);

			PreviousOutputWasHeading = 0;
		}

		// do not put any white space before or after $pre command
		// to aid in text placement on page
		OutputString("<code>");
		OutPre((yyvsp[-1]).line, (yyvsp[-1]).str);
		OutputString("</code>");

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6156 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 260:
#line 3984 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );

		if( TableLevel == 0 ) fatalomh(
			"The ",
			(yyvsp[0]).str,
			" command in line ",
			int2str((yyvsp[0]).line),
			"\nis not inside of a table; i.e.,\n",
			"not between a $table and the corresponding $tend",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		OutputString("</td></tr><tr>");
		FormatOutput("<td align='%s' ", HorizontalAlign);
		FormatOutput(" valign='%s'>\n", VerticalAlign);

		PopPending( (yyvsp[0]).line, "$cnext");
		PopPending( (yyvsp[0]).line, "$rnext");
		PushPending((yyvsp[0]).line, "$rnext");
		PushPending((yyvsp[0]).line, "$cnext");

		FreeMem((yyvsp[0]).str);

		(yyval).str   = NULL;
		(yyval).line  = (yyvsp[0]).line;
	}
#line 6188 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 261:
#line 4015 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( PreviousOutputWasHeading == 0 );

		(yyval).str = str_alloc("$rend");
		(yyval).line = (yyvsp[0]).line;
	}
#line 6199 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 262:
#line 4022 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( PreviousOutputWasHeading == 0 );

		(yyval).str = str_alloc("$rnext");
		(yyval).line = (yyvsp[0]).line;
	}
#line 6210 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 263:
#line 4032 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6217 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 264:
#line 4035 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		Rmark  = *((yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6232 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 265:
#line 4049 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6239 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 266:
#line 4052 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *tag;
		CrossReference *C;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// this command must be inside of a table
		if( TableLevel == 0 ) fatalomh(
			"The $rref command in line ",
			int2str((yyvsp[-2]).line),
			"\nis not inside of a table; i.e.,\n",
			"not between a $table and the corresponding $tend",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		// cross reference tag
		tag = (yyvsp[-1]).str;

		// convert to uniform white space format
		UniformWhiteSpace(tag);

		// output the cross reference
		FormatOutput("<RREF=\"%s\">", tag);

		// search for this cross reference
		C = FindCrossReference(tag, "");
		if( C == NULL )
			C = CreateCrossReference(tag, "", InputName());
		assert( C != NULL );

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6280 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 267:
#line 4092 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6287 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 268:
#line 4095 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *noEscape;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// I guess some one might put a paragraph heading
		// for an empty paragraph directly before the section title
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// remember the title
		if( CurrentSection->title != NULL ) fatalomh(
			"At $section command in line ",
			int2str((yyvsp[-2]).line),
			"\nMore than one $section command between\n",
			"the $begin and $end for the current section",
			NULL
		);

		// version of title without escape characters
		noEscape = str_alloc((yyvsp[-1]).str);
		if( MindexSection )
			StrRemove(noEscape, Escape);
		CurrentSection->title = str_alloc(noEscape);

		// title for this topic
		SearchTitle(noEscape);

		// erase the current heading setting
		InitializeHeading();

		// add to function reference
		InsertInFunRef(CurrentSection->tag, noEscape);


		// title for this section
		OutputString("<center><b><big><big>");
		if( PrintableOmhelp() )
		{
			char *printid;
			printid = SectionNumber(CurrentSection);

			if( printid[0] != '\0' )
			{
				FormatOutput2(
					"<a name=\"%s\" id=\"%s\">",
					printid,
					printid
				);
				OutputString(printid);
				OutputString(": ");
				output_text((yyvsp[-1]).line,noEscape,0,'\0',
					CheckSpell,ErrorColor);
				OutputString("</a>\n");
			}
			else	output_text((yyvsp[-1]).line,noEscape,0,'\0',
					CheckSpell,ErrorColor);

			FreeMem(printid);
		}
		else	output_text((yyvsp[-1]).line,noEscape,0,'\0',
					CheckSpell,ErrorColor);
		OutputString("</big></big></b></center>\n");

		// the end of centering starts a new line
		ConvertAddPrevious(1);

		if( MindexSection )
		{	char *lower = StrLowAlloc((yyvsp[-1]).str);

			// add keywords to search for this section
			SearchKeywords(lower, Escape, AutomaticIndexIgnore);

			MultipleIntoIndex(
				lower,
				CurrentSection->tag,
				HeadingAndSubHeading(),
				Escape,
				AutomaticIndexIgnore
			);

			FreeMem(lower);
		}

		FreeMem(noEscape);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6382 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 269:
#line 4189 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6389 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 270:
#line 4192 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatalomh(
			"At $skipnl in line ",
			int2str((yyvsp[-2]).line),
			"\nThe $skipnl command has been removed from\n",
			"the OMhelp language",
			NULL
		);
	}
#line 6402 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 271:
#line 4204 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		OutputString("<small>");
		PushPending((yyvsp[0]).line, "$small");

		(yyval) = (yyvsp[0]);
	}
#line 6414 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 272:
#line 4215 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		OutputString("</small>");
		PopPending((yyvsp[0]).line, "$small");

		(yyval) = (yyvsp[-2]);
	}
#line 6429 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 273:
#line 4229 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6436 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 274:
#line 4232 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( (yyvsp[-1]).str[0] != '\0' )
			SpellingOkList((yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6453 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 275:
#line 4248 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6460 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 276:
#line 4251 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	// command parameters
		char *filename;
		int  nspace;
		char *start;
		char *stop;
		char *token;
		int  skip;

		// local variables
		char *input_lang;
		char *output_lang;
		char *root;
		char *ext;
		char ch;
		char delimiter;
		int  ntoken;
		int  match;
		int  len;
		int  i;
		char line_buffer[300];
		int  column_max = 299;
		int  column_index;
		//
		char *data;
		char *tmp;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		delimiter = (yyvsp[-1]).str[0];
		ntoken = SplitText((yyvsp[-2]).line, "$src", (yyvsp[-1]).str);
		if( ntoken < 1 ) fatalomh(
			"At $src command in line ",
			int2str((yyvsp[-2]).line),
			"\nExpected at least 2 delimiters in $src command",
			NULL
		);
		if( ntoken == 3 ) fatalomh(
			"At $src command in line ",
			int2str((yyvsp[-2]).line),
			"\nMust also specify stop when start is present",
			NULL
		);
		if( ntoken > 6 ) fatalomh(
			"At $src command in line ",
			int2str((yyvsp[-2]).line),
			"\nExpected at most 6 delimiters in $src command",
			NULL
		);
		assert( delimiter != '\0' );

		// filename
		filename = (yyvsp[-1]).str + 1;

		// nspace
		if( ntoken < 2 )
			nspace = 0;
		else
		{	token  = filename + strlen(filename) + 1;
			nspace = atoi(token);
		}

		// start
		if( ntoken < 3 )
			start = "";
		else
			start = token + strlen(token) + 1;

		// stop
		if( ntoken < 4 )
			stop = "";
		else
			stop = start + strlen(start) + 1;

		// skip
		if( ntoken < 5 )
			skip = 0;
		else
		{	token = stop + strlen(stop) + 1;
			skip = atoi(token);
		}

		// clean up input file name
		ClipWhiteSpace(filename);

		// determine what language this file is in
		input_lang = file2lang(filename);
		if( input_lang[0] == '\0' )
		{	fatalomh(
				"At $src command in line ",
				int2str((yyvsp[-2]).line),
				"\nCannot determine language for the file\n",
				filename,
				NULL
			);
		}

		// start reading file
		InputSplitName(&root, &ext, filename);
		InputPush(root, ext, -1);

		// initialize with input first character
		ch       = InputGet();

		// set start pattern
		len = PatternMatchLen(start, Escape);
		if( len == -1 )
		{	InputPop();
			fatalomh(
				"At $src command in line ",
				int2str((yyvsp[-2]).line),
				"\nToo many characters in start pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				"At $src command in line ",
				int2str((yyvsp[-2]).line),
				"\nThree decimal digits must follow the ",
				"escape character in the start pattern",
				NULL
			);
		}
		assert( len >= 0 );

		// skip to the starting pattern
		if( len > 0 )
		{
			match = 0;
			while( (! match)  & (ch != '\001') )
			{	match = PatternMatchCh(&ch);
				if( match && skip > 0 )
				{	--skip;
					match = 0;
				}
				ch = InputGet();
			}

			if( ch == '\001' )
			{	InputPop();
				fatalomh(
					"At $src command in line ",
					int2str((yyvsp[-2]).line),
					"\nCould not find the start pattern \"",
					start,
					"\"\nin the file ",
					filename,
					NULL
				);
			}
		}

		// set stopping pattern
		len     = PatternMatchLen(stop, Escape);
		if( len == -1 )
		{	InputPop();
			fatalomh(
				"At $src command in line ",
				int2str((yyvsp[-2]).line),
				"\nToo many characters in stop pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				"At $src command in line ",
				int2str((yyvsp[-2]).line),
				"\nThree decimal digits must follow the ",
				"escape character in the stop pattern",
				NULL
			);
		}

		// get the data
		match        = 0;
		column_index = 0;
		data         = NULL;
		while(ch != '\001' )
		{
			if( len > 0 )
				match = PatternMatchCh(&ch);

			// indent when previous character is a newline
			if( column_index == 0 )
			{	for(i = 0; i < nspace; i++)
					line_buffer[column_index++] = ' ';
			}

			// add this character to the output line buffer
			if( (ch != '\001') & (ch != '\0') )
			{	if( column_index >= column_max )
				{	line_buffer[column_index-1] = '\n';
					line_buffer[column_index]   = '\0';
					fatalomh(
						"At $src command in line ",
						int2str((yyvsp[-2]).line),
						"\nIn the file ",
						filename,
						"\nThe following input line ",
						"is too long",
						line_buffer,
						NULL
					);
				}
				line_buffer[column_index++] = ch;
			}
			if( (ch == '\001') | (ch == '\n') | match )
			{	line_buffer[column_index] = '\0';
				if( data == NULL )
					data = str_alloc( line_buffer );
				else
				{	tmp   = data;
					data  = strjoin(data, line_buffer);
					FreeMem(tmp);
				}
			}
			// check for stopping at ch
			if( match )
				ch = '\001';
			// check for starting a newline
			if( ch == '\n' )
				column_index = 0;
			//
			if( ch != '\001' )
				ch = InputGet();
		}

		// done with this input file
		InputPop();

		// check for no data
		tmp = data;
		while( isspace(*tmp) || *tmp == delimiter )
			tmp++;
		if( *tmp == '\0' ) fatalomh(
			"At $src command in line ",
			int2str((yyvsp[-2]).line),
			" of file ",
			filename,
			"\nNo text between start and stop patterns.",
			"\nPerhaps need to skip start pattern in $src command.",
			NULL
		);

		// check for no match
		if( len > 0 && ! match ) fatalomh(
			"At $src command in line ",
			int2str((yyvsp[-2]).line),
			"\nCould not find the stop pattern \"",
			stop,
			"\"\nin the file ",
			filename,
			NULL
		);
		// if start is not present, add a newline for beginning of file
		if( ntoken < 3 )
		{	if( ConvertPreviousNewline() < 1 )
			{	ConvertForcedNewline(1);
				PreviousOutputWasHeading = 0;
			}
		}
		// if previous output was a heading, add a newline at beginning
		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// determine what language the output file is in
		if( strcmp( Internal2Out("OutputExtension"), ".htm") == 0 )
			output_lang = "html.outlang";
        else
            output_lang = "xhtml.outlang";

		// convert data to the output language with highlighting
		tmp = data;
		data = highlight(data, input_lang, output_lang);
		FreeMem(tmp);

		// skip comment header at beginning
		assert( strncmp(data, "<!--", 4) == 0 );
		tmp = data;
		while( *tmp != '>' && *tmp != '\0')
			tmp++;
		assert( strncmp(tmp-2, "-->", 3) == 0 );

		// skip newline at beginning of preformatted text
		while( *tmp != '<' && *tmp != '\0')
			tmp++;
		assert( strncmp(tmp, "<pre>", 5) == 0 );
		OutputString("<pre style='display:inline'>");
		tmp += 5;

		// output rest of data
		while( *tmp != '\0' )
			OutputChar((char) *tmp++);

		FreeMem(input_lang);
		FreeMem(data);
		FreeMem(root);
		FreeMem(ext);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6773 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 277:
#line 4563 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6780 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 278:
#line 4566 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		CrossReference *C;
		char           *number = NULL;
		char           *printid = NULL;
		char           *noEscape;
		char           *converted;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( TableLevel > 0 ) fatalomh(
			"The $subhead command in line ",
			int2str((yyvsp[-2]).line),
			" is inside a table; i.e.,\n",
			"between a $table and the corresponding $tend",
			NULL
		);

		// make sure no # characters in subheading
		if( strchr((yyvsp[-1]).str, '#') != NULL ) fatalomh(
			"$head command in line ",
			int2str((yyvsp[-2]).line),
			" has heading\n",
			(yyvsp[-1]).str,
			"\nThe character '#' is not allowed in headings",
			NULL
		);

		// make sure no # characters in heading
		if( strchr((yyvsp[-1]).str, '#') != NULL ) fatalomh(
			"$subhead command in line ",
			int2str((yyvsp[-2]).line),
			" has subheading\n",
			(yyvsp[-1]).str,
			"\nThe character '#' is not allowed in headings",
			NULL
		);

		if( ConvertPreviousNewline() < 2 )
			ConvertForcedNewline(2 - ConvertPreviousNewline() );

		// version of heading without escape characters
		noEscape = str_alloc((yyvsp[-1]).str);
		if( MindexSubhead )
			StrRemove(noEscape, Escape);

		// convert to unifrom white space format
		UniformWhiteSpace(noEscape);

		// set corresponding current heading
		SetSubHeading(noEscape);

		number  = SectionNumber(CurrentSection);
		assert( *( HeadingAndSubPrintId() ) == '.' );
		if( number[0] == '\0' )
			printid = strjoin(number, HeadingAndSubPrintId()+1);
		else	printid = strjoin(number, HeadingAndSubPrintId() );

		OutputString("<b>");
		if( PrintableOmhelp() )
		{	FormatOutput2(
				"<a name=\"%s\" id=\"%s\">",
				printid,
				printid
			);
			OutputString(printid);
			OutputString(": ");
		}
		else
		{	converted = ConvertInternalString(
				HeadingAndSubHeading()
			);
			FormatOutput2(
				"<a name=\"%s\" id=\"%s\">",
				converted,
				converted
			);
			FreeMem(converted);
		}

		output_text((yyvsp[-1]).line,noEscape,0,'\0',CheckSpell,ErrorColor);
		OutputString("</a></b>\n");

		// defined cross reference point
		C = DefineCrossReference(
			CurrentSection->tag,
			HeadingAndSubHeading(),
			InputName(),
			iFrame,
			printid
		);
		assert( C != NULL );
		FreeMem(number);
		FreeMem(printid);

		if( MindexSubhead )
		{	char *lower = StrLowAlloc((yyvsp[-1]).str);

			// add keywords to search for this section
			SearchKeywords(lower, Escape, AutomaticIndexIgnore);

			MultipleIntoIndex(
				lower,
				CurrentSection->tag,
				HeadingAndSubHeading(),
				Escape,
				AutomaticIndexIgnore
			);

			FreeMem(lower);
		}

		FreeMem(noEscape);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);

		PreviousOutputWasHeading = 1;
	}
#line 6905 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 279:
#line 4690 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 6912 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 280:
#line 4693 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *token;
		char *next;
		int  count;
		int  ntoken;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// split text into tokens
		ntoken = SplitText((yyvsp[-2]).line, "$syntax", (yyvsp[-1]).str);

		// first token
		token = (yyvsp[-1]).str + 1;

		// initialize delimter count flag
		count  = 1;

		// if output begins with a preformatted new line
		// do not need an extra one to for previous heading
		if( PreviousOutputWasHeading )
		{	char *s = token;
			char ch = *s++;

			int newline = 0;

			while( isspace((int) ch) )
			{	newline = newline || (ch == '\n');
				ch = *s++;
			}

			if( ! newline )
				ConvertForcedNewline(1);

			PreviousOutputWasHeading = 0;
		}


		// for each token
		while( ntoken-- )
		{	next = token + strlen(token) + 1;
			if( count % 2 == 0 )
			{	OutputString("<i>");
				ClipWhiteSpace(token);
				output_text((yyvsp[-1]).line,token,1,'\0',
					CheckSpell,ErrorColor);
				OutputString("</i>");
			}
			else
			{	// code font
				OutputString("<code><font color=\"");
				OutputString(CodeColor);
				OutputString("\">");
				output_text((yyvsp[-1]).line,token,1,'\0',
					CheckSpell,ErrorColor);
				OutputString("</font></code>");
			}
			count++;
			token = next;
		}

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 6982 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 281:
#line 4762 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		TableLevel++;

		OutputString("<table><tr>");
		FormatOutput("<td align='%s' ", HorizontalAlign);
		FormatOutput(" valign='%s'>\n", VerticalAlign);

		PushPending((yyvsp[0]).line, "$table");
		PushPending((yyvsp[0]).line, "$rnext");
		PushPending((yyvsp[0]).line, "$cnext");


		(yyval) = (yyvsp[0]);
	}
#line 7006 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 282:
#line 4785 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7013 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 283:
#line 4788 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	int size;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		size = atoi((yyvsp[-1]).str);
		if( size >= 100 ) fatalomh(
			"In $tabsize command in line ",
			int2str((yyvsp[-2]).line),
			"\nnumber of columns is greater than 99",
			NULL
		);
		if( size < 0 ) fatalomh(
			"In $tabsize command in line ",
			int2str((yyvsp[-2]).line),
			"\nnumber of columns is less than zero",
			NULL
		);
		if( size == 0 )
			size = TAB_SIZE;

		ConvertSetTabSize(size);
		if( CurrentSection->parent == NULL )
			TabSizeRoot = size;

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7048 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 284:
#line 4823 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );

		if( TableLevel <= 0 ) fatalomh(
			"There is no matching $table command preceeding\n",
			"the $tend command in line ",
			int2str((yyvsp[0]).line),
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		TableLevel--;
		OutputString("</td></tr>\n</table>\n");

		// tables had an automatic new line after them
		// (avoid adding more than once when tables are nested)
		if( TableLevel == 0 )
			ConvertAddPrevious(1);

		PopPending((yyvsp[0]).line, "$cnext");
		PopPending((yyvsp[0]).line, "$rnext");
		PopPending((yyvsp[0]).line, "$table");
	}
#line 7075 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 285:
#line 4848 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	assert ( (yyvsp[0]).str != NULL );

		(yyval) = (yyvsp[0]);
	}
#line 7084 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 286:
#line 4856 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	int line = (yyvsp[0]).line;
		char *p = (yyvsp[0]).str;
		char *q = (yyvsp[0]).str;

		assert( (yyvsp[0]).str != NULL );
		assert( REGISTERED_TRADE_MARK_CHARACTER < 5 );
		assert( COPYRIGHT_CHARACTER < 5 );

		// convert special characters
		while(*p != '\0' )
		{
			// error cases
			if( *p < 5 ) fatalomh(
				"Line ",
				int2str(line),
				" contains a character with ascii code\n",
				int2str(*p),
				" which is less than 5.",
				NULL
			);

			// conversion cases
			if( *p == Dollar )
				*p = '$';
			if( *p == Rmark )
				*p = REGISTERED_TRADE_MARK_CHARACTER;
			if( *p == Cmark )
				*p = COPYRIGHT_CHARACTER;
			if( *p == Wspace )
				*p = ' ';

			if( *p == '\n' )
			{	// increment line counter
				line++;
				p++;
				q++;
				*p = *q;
				if( *p != '\0' && *p == NewlineCh )
				{	// skip program source comment char
					q++;
					*p = *q;
					// skip one space character (if present)
					if( *p == ' ' )
					{	q++;
						*p = *q;
					}
				}
			}
			else
			{	p++;
				q++;
				*p = *q;
			}
		}

		(yyval) = (yyvsp[0]);
	}
#line 7146 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 287:
#line 4916 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7153 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 288:
#line 4919 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// only one $textcolor per section
		if( CurrentSection->style.textcolor != NULL ) fatalomh(
			"At $textcolor comamnd in line ",
			int2str((yyvsp[-2]).line),
			"\nThere is more than one $textcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.textcolor = Color(
			(yyvsp[-2]).line, "$textcolor", (yyvsp[-1]).str
		);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 7180 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 289:
#line 4945 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7187 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 290:
#line 4948 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// output the index in italic followed by "-th"
		OutputString("<code><i>");
		output_text((yyvsp[-1]).line,(yyvsp[-1]).str,0,'\0',CheckSpell,ErrorColor);
		OutputString("</i></code>");
		OutputString("-th");

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7212 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 291:
#line 4973 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7219 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 292:
#line 4976 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		printf("%s", (yyvsp[-1]).str);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7234 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 293:
#line 4989 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7241 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 294:
#line 4992 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *tag = (yyvsp[-1]).str;
		CrossReference *C;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// output the cross reference
		FormatOutput("<TITLE=\"%s\">", tag);

		// search for this cross reference
		C = FindCrossReference(tag, "");
		if( C == NULL )
			C = CreateCrossReference(tag, "", InputName());
		assert( C != NULL );

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7271 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 295:
#line 5021 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7278 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 296:
#line 5024 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *tag;
		CrossReference *C;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	// place a new line after heading and before title
			ConvertForcedNewline(1);

			// there is no pass one output in title, so need
			// to cancel new line counter for previous newline
			ConvertAddPrevious(-1);

			// title is not a heading
			PreviousOutputWasHeading = 0;
		}

		// cross reference tag
		tag = (yyvsp[-1]).str;

		// convert to uniform white space format
		UniformWhiteSpace(tag);

		// output the cross reference
		FormatOutput("<TREF=\"%s\">", tag);

		// search for this cross reference
		C = FindCrossReference(tag, "");
		if( C == NULL )
			C = CreateCrossReference(tag, "", InputName());
		assert( C != NULL );

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7321 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 297:
#line 5067 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7328 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 298:
#line 5070 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *root;
		char *ext;
		char *filename;
		char *start;
		char *stop;
		char ch;
		char previous;
		int  skip;
		int  ntoken;
		int  nspace;
		int  match;
		int  len;
		int  i;
		char line_buffer[300];
		int  line_max = 299;
		int  line_index;

		// initialize token to avoid warning
		// (compiler does not know fatalerr will not return)
		char *token = NULL;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		ntoken = SplitText((yyvsp[-2]).line, "$verbatim", (yyvsp[-1]).str);
		if( 5 < ntoken ) fatalomh(
			"At $verbatim command in line ",
			int2str((yyvsp[-2]).line),
			"\nMore than 6 delimiters in $verbatim command",
			NULL
		);

		filename = (yyvsp[-1]).str + 1;
		if( ntoken < 2 )
			nspace = 0;
		else
		{	token = filename + strlen(filename) + 1;
			nspace = atoi(token);
		}
		if( ntoken < 3 )
			start = "\0";
		else	start = token + strlen(token) + 1;
		if( ntoken < 4 )
			stop  = "\0";
		else	stop  = start + strlen(start) + 1;
		if( ntoken < 5 )
			skip  = 0;
		else
		{	token = stop + strlen(stop) + 1;
			skip  = atoi(token);
		}

		ClipWhiteSpace(filename);
		InputSplitName(&root, &ext, filename);
		InputPush(root, ext, -1);

		// if start is not present, add a newline for beginning of file
		if( ntoken < 3 )
		{
			if( ConvertPreviousNewline() < 1 )
			{	ConvertForcedNewline(1);
				PreviousOutputWasHeading = 0;
			}

			previous = '\n';
		}
		else	previous = '\0';

		// if previous output was a heading, add a newline at beginning
		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// initialize with first character
		ch       = InputGet();

		// skip to starting point
		len = PatternMatchLen(start, Escape);
		if( len == -1 )
		{	InputPop();
			fatalomh(
				"At $verbatim command in line ",
				int2str((yyvsp[-2]).line),
				"\nToo many characters in start pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				"At $verbatim command in line ",
				int2str((yyvsp[-2]).line),
				"\nThree decimal digits must follow the ",
				"escape character in the start pattern",
				NULL
			);
		}
		assert( len >= 0 );
		if( len > 0 )
		{
			match = 0;
			while( (! match)  & (ch != '\001') )
			{	match = PatternMatchCh(&ch);
				if( match && skip > 0 )
				{	--skip;
					match = 0;
				}
				ch = InputGet();
			}

			if( ch == '\001' )
			{	InputPop();
				fatalomh(
					"At $verbatim command in line ",
					int2str((yyvsp[-2]).line),
					"\nCould not find the start pattern \"",
					start,
					"\"\nin the file ",
					filename,
					NULL
				);
			}
		}

		len     = PatternMatchLen(stop, Escape);
		if( len == -1 )
		{	InputPop();
			fatalomh(
				"At $verbatim command in line ",
				int2str((yyvsp[-2]).line),
				"\nToo many characters in stop pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				"At $verbatim command in line ",
				int2str((yyvsp[-2]).line),
				"\nThree decimal digits must follow the ",
				"escape character in the stop pattern",
				NULL
			);
		}

		// a standard compliant way to inhibit line breaks at
		// '-' in MS Internet Explorer (should not be necessary)
		OutputString("<pre style='display:inline'>");
		// if first character is a newline, add space before. See
		// https://bugzilla.mozilla.org/show_bug.cgi?id=476324
		if( ch == '\n' )
			OutputString(" ");
		// Add to column count in ConvertOuputCh so that Column > 0
		// and hence initial white space will be printed
		ConvertAddColumn(1);

		match = 0;
		line_index = 0;
		while(ch != '\001' )
		{
			if( len > 0 )
				match = PatternMatchCh(&ch);

			// indent when previous character is a newline
			if( (previous == '\n') & (ch != '\001' ) )
			{	for(i = 0; i < nspace; i++)
					ConvertOutputCh(' ', 0);
			}
			previous = ch;

			// add this character to the output line buffer
			if( (ch != '\001') & (ch != '\0') & (ch != '\n') )
			{	if( line_index >= line_max )
				{	line_buffer[line_max-1] = '\n';
					line_buffer[line_max]   = '\0';
					fatalomh(
					"At $verbatim command in line ",
					int2str((yyvsp[-2]).line),
					"\nIn the file ",
					filename,
					"\nThe following input line ",
					"is too long",
					line_buffer,
					NULL
					);
				}
				line_buffer[line_index++] = ch;
			}

			// check for stopping point after outputing ch
			if( match & (ch != '\n') )
				ch = '\001';

			// output line buffer when current character is newline
			// or the end of the input
			if( (ch == '\n') | (ch == '\001')  )
			{	int spell_check = 0;
				int pre = 0;
				assert( line_index < line_max );
				line_buffer[line_index] = '\0';
				hilite_out(
					"verbatim",
					(yyvsp[-1]).line,
					spell_check,
					ErrorColor,
					HiliteColor,
					pre,
					line_buffer
				);
				line_index = 0;
			}
			if( ch == '\n' )
				ConvertOutputCh(ch, 0);

			if( match )
				ch = '\001';

			if( ch != '\001' )
				ch = InputGet();
		}

		// stop preformatted output
		OutputString("</pre>");


		if( ntoken < 3  )
		{	if( ConvertPreviousNewline() < 1 )
				ConvertForcedNewline(1);
		}

		InputPop();

		if( len > 0 && ! match ) fatalomh(
			"At $verbatim command in line ",
			int2str((yyvsp[-2]).line),
			"\nCould not find the stop pattern \"",
			stop,
			"\"\nin the file ",
			filename,
			NULL
		);

		FreeMem(root);
		FreeMem(ext);
		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7583 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 299:
#line 5324 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7590 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 300:
#line 5327 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		// only one $visitcolor per section
		if( CurrentSection->style.visitcolor != NULL ) fatalomh(
			"At $visitcolor comamnd in line ",
			int2str((yyvsp[-2]).line),
			"\nThere is more than one $visitcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.visitcolor = Color(
			(yyvsp[-2]).line, "$visitcolor", (yyvsp[-1]).str
		);

		FreeMem((yyvsp[-1]).str);
		(yyval) = (yyvsp[-2]);
	}
#line 7617 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 301:
#line 5352 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7624 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 302:
#line 5355 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		Wspace = *((yyvsp[-1]).str);

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7640 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 303:
#line 5370 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	fatal_not_2_dollar_or_text((yyvsp[-2]).code, (yyvsp[-2]).line, (yyvsp[0]).code);
	}
#line 7647 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;

  case 304:
#line 5373 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1646  */
    {	char *tag;
		char *head;
		char *subhead;
		char *link;
		char *frame;
		CrossReference *C;

		int checkspell;
		int ntoken;
		int i, j;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// initial state of spell checker
		checkspell = CheckSpell;

		// split text into tokens
		ntoken = SplitText((yyvsp[-2]).line, "$xref", (yyvsp[-1]).str);
		if( ntoken > 5 ) fatalomh(
			"At $xref command in line ",
			int2str((yyvsp[-2]).line),
			"\nMore than 6 delimiters in $xref command",
			NULL
		);

		// tag for reference
		tag = (yyvsp[-1]).str + 1;

		// determine which arguments are present
		head    = "";
		subhead = "";
		link    = "";
		frame   = "";
		if( ntoken == 5 )
		{	head    = tag     + strlen(tag)     + 1;
			subhead = head    + strlen(head)    + 1;
			link    = subhead + strlen(subhead) + 1;
			frame   = link    + strlen(link)    + 1;
		}
		else if( ntoken > 1 )
		{	head = tag + strlen(tag) + 1;
			if( ntoken > 2 )
				link = head + strlen(head) + 1;
			if( ntoken > 3 )
				frame = link + strlen(link) + 1;
		}

		// convert to unifrom white space format
		UniformWhiteSpace(tag);
		UniformWhiteSpace(head);
		UniformWhiteSpace(subhead);
		UniformWhiteSpace(link);
		UniformWhiteSpace(frame);

		// make sure tag is not empty
		if( tag[0] == '\0' ) fatalomh(
			"At $xref command in line ",
			int2str((yyvsp[-2]).line),
			"\nOnly white space between first 2 delimiters",
			NULL
		);


		// check the frame specification
		if( ntoken >= 4  )
		{
			if( frame[0] == '\0' ) fatalomh(
				"At $xref command in line ",
				int2str((yyvsp[-2]).line),
				"\nFrame number in $xref command is empty; ",
				"i.e., just white space.",
				NULL
			);

			i     = atoi(frame);
			if( i < 1 ) fatalomh(
				"At $xref command in line ",
				int2str((yyvsp[-2]).line),
				"\nFrame number in $xref command is ",
				"less than 1",
				NULL
			);

			if( i > MaxFrame )
			{	FreeMem( MaxFrameFile );
				MaxFrame = i;
				MaxFrameLine = (yyvsp[-2]).line;
				MaxFrameFile = str_alloc(InputName());
			}

			if( head[0] == '\0' ) fatalomh(
				"At $xref command in line ",
				int2str((yyvsp[-2]).line),
				"\nCannot have an empty heading",
				"\nwhen a particular frame is specified.",
				NULL
			);
		}

		// if subheading is specified, check that heading is not empty
		if( subhead[0] != '\0' && head[0] == '\0' ) fatalomh(
			"At $xref command in line ",
			int2str((yyvsp[-2]).line),
			"\nCannot have an empty heading with ",
			"a non-empty subheading.",
			NULL
		);

		// attach the subheading to the heading
		if( subhead[0] != '\0' )
		{	i         = strlen(head);
			j         = 0;
			head[i++] = '.';
			while( subhead[j] != '\0' )
			{	assert( head + i < link - 1 );
				head[i++] = subhead[j++];
			}
			head[i] = '\0';
		}

		// if linking text is empty or not present
		// use the tag for the linking text
		if( link[0] == '\0' )
			link = tag;

		// if frame is not present and heading is not empty
		// change frame to 1
		if( ntoken < 4 && head[0] != '\0' )
			frame = "1";

		if( PrintableOmhelp() | NoFrame() )
		{	frame = "";
			MaxFrame = 0;
		}

		// output the cross reference jump without spell checking
		CheckSpell = 0;
		HrefOutputPass1(tag, head, "false", frame, "true");

		// do not check spelling on cross reference tags
		if( ntoken > 2 )
			CheckSpell = checkspell;

		OutPre((yyvsp[-1]).line, link);
		HrefEnd("\n");

		// search for this cross reference
		C = FindCrossReference(tag, head);
		if( C == NULL )
			C = CreateCrossReference(tag, head, InputName());
		assert( C != NULL );

		// restore spell checking to initial setting
		CheckSpell = checkspell;

		FreeMem((yyvsp[-1]).str);

		(yyval) = (yyvsp[-2]);
	}
#line 7818 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
    break;


#line 7822 "/home/bradbell/omhelp.git/src/omhelp.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 5540 "/home/bradbell/omhelp.git/src/omhelp.y" /* yacc.c:1906  */

