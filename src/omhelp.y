/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2020 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
%{
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

# include "jump_table.h"
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
static int TabSizeRoot    = TAB_SIZE;
static int TabSizeCurrent = TAB_SIZE;

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
	ETITLE_match,
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
	ACCENT_match,
	NO_match,
	PARTIAL_match
};

static char *MatchText[]  = {
	"<ETITLE>",
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
static int   MatchLen[]   = {8, 7, 10, 10, 6,  8, 7, 7, 7, 10, 12, 8};
static int   MatchState[] = {0, 0,  0,  0, 0,  0, 0, 0, 0,  0,  0, 0};
static int   MatchNumber  = sizeof(MatchText) / sizeof(MatchText[0]);

// ************************ Static Functions *******************************
//
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
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
static void OutPre(int line, const char *s)
{	output_text(line,s,1,'\0',CheckSpell,ErrorColor); }
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
static void PushTmpOutput(const char *root)
{	char *file;
	file = strjoin(root, ".tmp");
	PushOutput(file);
	FreeMem(file);
}
// ----------------------------------------------------------------------------
static char MatchBuffer[10];
static int  MatchIndex = 0;
static enum MatchType MatchOrOutput(int ch)
{	int            i;
	int            j;
	int            state;
	char           *text;
	enum MatchType result;

	result = NO_match;
	for(i = 0; i < MatchNumber; i++)
	{	text  = MatchText[i];
		state = MatchState[i];
		if( text[state] == ch )
		{	MatchState[i]++;
			if( MatchState[i] == MatchLen[i] )
			{	for(j = 0; j < MatchNumber; j++)
					MatchState[j] = 0;
				MatchIndex = 0;
				result = (enum MatchType) i;
				return result;
			}
			result = PARTIAL_match;
		}
		else	MatchState[i] = 0;
	}
	if( result == PARTIAL_match )
	{	assert(MatchIndex < 100);
		MatchBuffer[MatchIndex++] = ch;
		return result;
	}
	assert( result == NO_match );
	//
	// output charages that have been waiting to see if a match
	for(i = 0; i < MatchIndex; i++)
		OutputChar(MatchBuffer[i]);
	MatchIndex = 0;
	//
	// output this character
	if( ch != EOF )
		OutputChar((char) ch);
	//
	return result;
}
// ----------------------------------------------------------------------------
static void SecondPass(SectionInfo *F)
{
	char *tagLower;
	char *NameTmp;
	FILE *fpTmp;
	int  ch;
	int  index;
	int  build_jump_table;
	enum MatchType  match;

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
		// -----------------------------------------------------------------
		// jump table
		build_jump_table = 0;
		for(index = 0; index < F->navigate.number; ++index)
		{	if( F->navigate.item[index].nav_type == CURRENT_nav )
			{	const char* label = F->navigate.item[index].label;
				if( strcmp(label, "_jump_table") == 0 )
					build_jump_table = 1;
			}
		}
		//
		// read until end of file
		ch    = getc(fpTmp);
		while( ch != EOF )
		{	// output checking for special sequences
			match = MatchOrOutput(ch);
			switch( match )
			{
				// ----------------------------------------------------------
				case ETITLE_match:
				// end of the tilte for this section
				if( build_jump_table )
				{	jump_table(F);
					// add extra space after jump table to account for call to
					// ConvertAddPrevious(1) after <ETITLE> in section code
					OutputString("\n<br");
					OutputString(Internal2Out("SelfTerminateCmd"));
				}
				break;

				// ----------------------------------------------------------
				case ACCENT_match:
				// an accent over a vowel, convert to proper accent
				buffer[0] = getc(fpTmp);
				buffer[1] = '\0';
				FormatOutput("&%sacute;", buffer);
				ch = getc(fpTmp);
				assert( ch == '>' );
				break;

				// ----------------------------------------------------------
				case HREF_match:
				// a cross reference
				{ // Begin HREF_match block
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
				} // End HREF_match block
				break;

				// ----------------------------------------------------------
				case CHILDTABLE_match:
				TableChildren(F, PrintableOmhelp() );
				break;

				// ----------------------------------------------------------
				case CONTENTS_match:
				ListChildren(F, PrintableOmhelp() );
				break;

				// ----------------------------------------------------------
				case CHILDREN_match:
				// do nothing
				break;

				// ----------------------------------------------------------
				case EXECUTE_match:
				{ // Begin EXECUTE_match block
				char *execute;
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
				} // End EXECUTE_match block
				break;

				// ----------------------------------------------------------
				case FEND_match:
				// for end of frame
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
				break;

				// ----------------------------------------------------------
				case TREF_match:
				case RREF_match:
				case TITLE_match:
				{ // Begin TREF_match, RREF_match, TITLE_match block
				char           *tag;
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
				} // End TREF_match, RREF_match, TITLE_match block
				break;

				// ----------------------------------------------------------
				case ENDHREF_match:
				if( lastCrossReferenceDefined )
					HrefEnd("");
				break;

				// ----------------------------------------------------------
				default:
				assert( match == NO_match || match == PARTIAL_match );
				break;
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
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
static void SkipBeforeFirstAndAfterLastNewline(
	int line, char *s, const char *cmd, const char *name
)
{	char *next;
	char *last;
	int count;

	next = s;
	count = 0;
	while( *next != '\0' )
	{	if( *next == '\n' )
			count++;
		next++;
	}
	if( count < 2 ) fatalomh(
		"In line number ",
		int2str(line),
		"\nThere must be at least two newlines in the ",
		name,
		" for a ",
		cmd,
		" command.\n",
		NULL
	);

	// last character in s
	last = next - 1;
	// first character in s
	next = s;

	/*
	skip to the first newline
	*/
	while( *next != '\n' && *next != '\0' )
		next++;
	assert( *next == '\n' );

	// find last character to include
	while( *last != '\n' )
		last--;

	// last must be past next
	assert( next < last );

	// skift the string pointed to by s
	while( next <= last )
		*s++ = *next++;

	// new termination point
	*s = '\0';
}
// --------------------------------------------------------------------------
static void srcfile(
	const char* command_name     ,
	int         line_number      ,
	int         newline_at_start ,
	const char* file_name        ,
	int         indent           ,
	const char* start            ,
	const char* stop             ,
	int         skip             )
{
	{	// will count how many matches for start pattern
		int  count = 0;

		// other local variables
		char *input_lang, *output_lang, *root, *ext, *data, *tmp;
		char ch, line_buffer[300];
		int  len, match, tabsize, column_index, column_max = 299;

		// split name for opening file and check extension
		// root and ext must be freed before returning
		InputSplitName(&root, &ext, file_name);

		// make sure file_name has an extension
		if( ext[0] == '\0' ) fatalomh(
			command_name,
			" command in line ",
			int2str(line_number),
			"\nThe file '",
			file_name,
			"'\ndoes not have a '.' followed by an extension",
			"\nso cannot determine its language.",
			NULL
		);
		// determine what language this file is in
		assert( ext[0] == '.' );
		input_lang = file_ext2lang( ext + 1 );
		if( input_lang == NULL ) fatalomh(
			command_name,
			" command in line ",
			int2str(line_number),
			"\nCannot use this command becasue the",
			"\nsource-highlight or boost_regex library is not avaiable.",
			NULL
		);
		if( input_lang[0] == '\0' )
		{	fatalomh(
				command_name,
				" command in line ",
				int2str(line_number),
				"\nCannot determine language for the file extension ",
				ext,
				NULL
			);
		}
		// initialize with input first character
		InputPush(root, ext, -1);
		ch       = InputGet();
		//
		// set start pattern
		len = PatternMatchLen(start, Escape);
		if( len == -1 )
		{	InputPop();
			fatalomh(
				command_name,
				" command in line ",
				int2str(line_number),
				"\nToo many characters in start pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				command_name,
				" command in line ",
				int2str(line_number),
				"\nThree decimal digits must follow the ",
				"escape character in the start pattern",
				NULL
			);
		}
		assert( len >= 0 );
		//
		// skip to the starting pattern
		if( len > 0 )
		{	match = 0;
			while( (! match)  & (ch != '\001') )
			{	match = PatternMatchCh(&ch);
				if( match && count < skip)
				{	++count;
					match = 0;
				}
				ch = InputGet();
			}
			if( ch == '\001' )
			{	InputPop();
				fatalomh(
					command_name,
					" command in line ",
					int2str(line_number),
					"\nCould not find the ",
					int2str(skip + 1),
					"-th copy of start pattern \"",
					start,
					"\"\nin file ",
					file_name,
					NULL
				);
			}
		}
		//
		// set stopping pattern
		len     = PatternMatchLen(stop, Escape);
		if( len == -1 )
		{	InputPop();
			fatalomh(
				command_name,
				" command in line ",
				int2str(line_number),
				"\nToo many characters in stop pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				command_name,
				" command in line ",
				int2str(line_number),
				"\nThree decimal digits must follow the ",
				"escape character in the stop pattern",
				NULL
			);
		}
		//
		// get the data
		match        = 0;
		column_index = 0;
		data         = NULL;
		while(ch != '\001' )
		{	if( len > 0 )
				match = PatternMatchCh(&ch);
			//
			// add this character to the output line buffer
			if( (ch != '\001') & (ch != '\0') )
			{	if( column_index >= column_max )
				{	line_buffer[column_index-1] = '\n';
					line_buffer[column_index]   = '\0';
					fatalomh(
						command_name,
						" command in line ",
						int2str(line_number),
						"\nin file ",
						file_name,
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
				{	int i = 0;
					while( line_buffer[i] == ' ' || line_buffer[i] == '\n' )
						i++;
					if( newline_at_start && line_buffer[i] != '\n' )
						data = strjoin( "\n", line_buffer );
					else
						data = str_alloc( line_buffer );
				}
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
		//
		// done with this input file
		InputPop();
		//
		// check for no data
		tmp = data;
		while( isspace(*tmp) )
			tmp++;
		if( *tmp == '\0' ) fatalomh(
			command_name,
			" command in line ",
			int2str(line_number),
			" of file ",
			file_name,
			"\nNo text between start and stop patterns.",
			"\nPerhaps you need to skip the first start pattern.",
			NULL
		);
		//
		// check for no match
		if( len > 0 && ! match ) fatalomh(
			command_name,
			" command in line ",
			int2str(line_number),
			"\nCould not find the stop pattern \"",
			stop,
			"\"\nin ",
			file_name,
			NULL
		);
		//
		// determine what language the output file is in
		if( strcmp( Internal2Out("OutputExtension"), ".htm") == 0 )
			output_lang = "html.outlang";
        else
            output_lang = "xhtml.outlang";
		//
		// number of newliness there will be at end of soruce
		tmp = data + strlen(data) - 1;
		while( isspace(*tmp) && data < tmp )
		{	if( *tmp == '\n' )
				ConvertAddPrevious(1);
			tmp--;
		}
		//
		// convert data to the output language with highlighting
		tabsize = TabSizeCurrent;
		tmp     = data;
		data = highlight(data, input_lang, output_lang, indent, tabsize);
		FreeMem(tmp);
		assert( data != NULL );
		tmp = data;
		//
		// output data
		while( *tmp != '\0' )
			OutputChar( *tmp++ );
		//
		FreeMem(input_lang);
		FreeMem(data);
		FreeMem(root);
		FreeMem(ext);
	}
}
// ************************ Global Functions **********************************
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
// ************************* End Preamble ************************************
%}

%token ACCENT_lex
%token AINDEX_lex
%token ALIGN_lex
%token BEGIN_lex
%token BGCOLOR_lex
%token BIG_lex
%token BOLD_lex
%token CEND_lex
%token CENTER_lex
%token CHILDREN_lex
%token CHILDTABLE_lex
%token CINDEX_lex
%token CMARK_lex
%token CNEXT_lex
%token CODE_lex
%token CODECOLOR_lex
%token CODEI_lex
%token CODEP_lex
%token COMMENT_lex
%token CONTENTS_lex
%token CREF_lex
%token DATE_lex
%token DOLLAR_lex
%token DOUBLE_DOLLAR_lex
%token END_lex
%token EOF_lex
%token ERRORCOLOR_lex
%token ESCAPE_lex
%token EXECUTE_lex
%token FEND_lex
%token FIXED_lex
%token HEAD_lex
%token HILITECMD_lex
%token HILITECOLOR_lex
%token HILITESEQ_lex
%token HREF_lex
%token ICODE_lex
%token ICON_lex
%token IMAGE_lex
%token INCLUDE_lex
%token INDEX_lex
%token ITALIC_lex
%token LATEX_lex
%token LEND_lex
%token LINKCOLOR_lex
%token LIST_lex
%token LNEXT_lex
%token MATH_lex
%token MINDEX_lex
%token MREF_lex
%token NAVIGATE_lex
%token NEWLINECH_lex
%token NOBREAK_lex
%token NOSPELL_lex
%token NUMBER_lex
%token PATH_lex
%token PRE_lex
%token REND_lex
%token RMARK_lex
%token RNEXT_lex
%token RREF_lex
%token SECTION_lex
%token SKIPNL_lex
%token SMALL_lex
%token SPELL_lex
%token SRCCODE_lex
%token SRCFILE_lex
%token SRCTHISFILE_lex
%token SUBHEAD_lex
%token SYNTAX_lex
%token TABLE_lex
%token TABSIZE_lex
%token TEND_lex
%token TEXT_lex
%token TEXTCOLOR_lex
%token TH_lex
%token TITLE_lex
%token TRACE_lex
%token TREF_lex
%token VERBATIM_lex
%token VISITCOLOR_lex
%token WSPACE_lex
%token XREF_lex

%%

start
	: init element_list DOUBLE_DOLLAR_lex
	{
		fatalomh(
			"Unexpected $$",
			NULL
		);
	}
	;

init
	:
	{	yydebug = 0;
	}
	;

element
	: accent
	| aindex
	| align
	| begin
	| bgcolor
	| big
	| bold
	| center
	| childlist
	| cmark
	| cnext
	| code
	| codecolor
	| codei
	| codep
	| comment
	| cref
	| date
	| dollar
	| end
	| eof
	| errorcolor
	| escape
	| execute
	| fend
	| fixed
	| head
	| hilitecmd
	| hilitecolor
	| hiliteseq
	| href
	| icode
	| image
	| include
	| index
	| italic
	| latex
	| lend
	| linkcolor
	| list
	| lnext
	| math
	| mref
	| nobreak
	| nospell
	| number
	| navigate
	| newlinech
	| path
	| pre
	| rmark
	| rnext
	| section
	| skipnl
	| small
	| spell
	| srccode
	| srcfile
	| srcthisfile
	| subhead
	| syntax
	| table
	| tabsize
	| tend
	| text
	{	assert( $1.str != NULL );

		if( PreviousOutputWasHeading )
		{
			char *s = $1.str;
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

		output_text($1.line,$1.str,0,'\0',CheckSpell,ErrorColor);
		FreeMem($1.str);

		$$.str  = NULL;
		$$.line = $1.line;
	}
	| textcolor
	| th
	| trace
	| rref
	| title
	| tref
	| verbatim
	| visitcolor
	| wspace
	| xref
	;

element_list
	: element
	{	assert( $1.str == NULL );
		$$ = $1;
	}
	| element_list element
	{	assert( $1.str == NULL );
		$$ = $1;
	}
	;

accent
	: ACCENT_lex
	{	char ch;

		// initlaize to avoid warning
		// (compiler does not know fatalomh does not return)
		char *code = NULL;

		assert( $1.str != NULL );
		assert( strlen($1.str) == 1 );

		ch = *($1.str);
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
			int2str( $1.line ),
			" is not a vowel.",
			NULL
			);
		}
		FormatOutput("&#%s;", code);

		FreeMem($1.str);
	}
	;

aindex
	: AINDEX_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| AINDEX_lex argument DOUBLE_DOLLAR_lex
	{	char *s;
		int i;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		s = StrCat(__FILE__, __LINE__, " ", $2.str, " ", NULL);

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
		FreeMem($2.str);

		$$ = $1;
	}
	;

align
	: ALIGN_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| ALIGN_lex argument DOUBLE_DOLLAR_lex
	{	char *s;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		s = $2.str;
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
			int2str($2.line),
			" is not one of following:\n",
			"left, center, right, top, middle, bottom",
			NULL
		);

		FreeMem($2.str);
	}
	;

argument
	: text
	{	assert( $1.str != NULL );
		ClipWhiteSpace($1.str);
		$$ = $1;
	}
	;

begin
	: BEGIN_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| BEGIN_lex argument DOUBLE_DOLLAR_lex
	{	char *tag;
		char *tag_lower;
		char *number = NULL;
		int i;
# ifndef NDEBUG
		CrossReference *C;
# endif

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( BeginCount != EndCount ) fatalomh(
			"The $begin command on line ",
			int2str($1.line),
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
				int2str($1.line),
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
		tag = $2.str;
		SectionSetTag(CurrentSection, tag);
		tag_lower = CurrentSection->tagLower;

		/*
		check for an invalid section tag
		*/
		if( strlen(tag) > MAX_TAG ) fatalomh(
			"In the $begin command on line ",
			int2str($1.line),
			"\nthe section tag is more than ",
			int2str(MAX_TAG),
			" characters long",
			NULL
		);
		if( strstr(tag_lower, "_frame") != NULL ) fatalomh(
			"In the $begin command on line ",
			int2str($1.line),
			"\nthe section tag contains the substring \"_frame\"",
			NULL
		);
		if( strstr(tag_lower, "_links") != NULL ) fatalomh(
			"In the $begin command on line ",
			int2str($1.line),
			"\nthe section tag contains the substring \"_links\"",
			NULL
		);
		if( strstr(tag_lower, "__") != NULL ) fatalomh(
			"In the $begin command on line ",
			int2str($1.line),
			"\nthe section tag contains the substring of two underbars \"__\"",
			NULL
		);
		if( tag_lower[0] == '_' ) fatalomh(
			"In the $begin command on line ",
			int2str($1.line),
			"\n\"_\" is the first character in the section tag",
			NULL
		);
		if( strcmp(tag_lower, "index") == 0 ) fatalomh(
			"In the $begin command on line ",
			int2str($1.line),
			"\nyou cannot use \"index\" as a section tag",
			"\nbecause \"index\" automatically links ",
			"to the starting file",
			NULL
		);
		for(i = 0; tag[i] != '\0'; ++i)
		if( isspace( tag[i] ) )	fatalomh(
			"In the $begin command on line ",
			int2str($1.line),
			"\nthe section tag contains white space characters",
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
		TabSizeCurrent = TabSizeRoot;

		// erase the current heading setting
		InitializeHeading();

		// erase the current special spelling list
		SpellingOkList("");

		// get the default settings for this section
		hilite_get_default();

		// ********************************************************

		// define cross reference point
		number = SectionNumber(CurrentSection);
# ifndef NDEBUG
		C =
# endif
		DefineCrossReference(tag, "", InputName(), 0, number);
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
		FreeMem($2.str);
		$$ = $1;
	}
	;

bgcolor
	: BGCOLOR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| BGCOLOR_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// only one $bgcolor per section
		if( CurrentSection->style.bgcolor != NULL ) fatalomh(
			"At $bgcolor comamnd in line ",
			int2str($1.line),
			"\nThere is more than one $bgcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.bgcolor = Color(
			$1.line, "$bgcolor", $2.str
		);

		FreeMem($2.str);
		$$ = $1;
	}
	;

big_begin
	: BIG_lex
	{	assert( $1.str == NULL );

		OutputString("<big>");
		PushPending($1.line, "$big");

		$$ = $1;
	}
	;

big
	: big_begin element_list DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );

		OutputString("</big>");
		PopPending($3.line, "$big");

		$$ = $1;
	}
	;


bold_begin
	: BOLD_lex
	{	assert( $1.str == NULL );

		OutputString("<b>");
		PushPending($1.line, "$bold");

		$$ = $1;
	}
	;

bold
	: bold_begin element_list DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );

		OutputString("</b>");
		PopPending($3.line, "$bold");

		$$ = $1;
	}
	;

codei
	: CODEI_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| CODEI_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		color_switch($2.str, "blue", "black", Escape,
			$1.line, "codei", CheckSpell, ErrorColor);

		FreeMem($2.str);
		$$ = $1;
	}
	;


cnext
	: cnext_cases
	{	assert( $1.str == NULL );

		if( TableLevel == 0 ) fatalomh(
			"$cnext or $cend command in line ",
			int2str($1.line),
			"\nis not between a $table command ",
			"and its corresponding $tend command",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		OutputString("</td>");
		FormatOutput("<td align='%s' ", HorizontalAlign);
		FormatOutput(" valign='%s'>\n", VerticalAlign);

		PopPending( $1.line, "$cnext");
		PushPending($1.line, "$cnext");

		$$ = $1;
	}
	;

cnext_cases
	: CEND_lex
	{	assert( $1.str == NULL );
		$$ = $1;
	}
	| CNEXT_lex
	{	assert( $1.str == NULL );
		$$ = $1;
	}
	;

center_begin
	: CENTER_lex
	{	assert( $1.str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		OutputString("<center>");
		PushPending($1.line, "$center");

		$$ = $1;
	}
	;

center:
	center_begin element_list DOUBLE_DOLLAR_lex
	{	assert( $2.str == NULL );
		assert( $3.str == NULL );

		OutputString("</center>");
		PopPending($3.line, "$center");

		// the end of centering starts a new line
		ConvertAddPrevious(1);

		$$ = $1;
	}
	;

contents
	: CONTENTS_lex
	{	assert( $1.str == NULL );

		$$.str  = str_alloc("$contents");
		$$.line = $1.line;
	}
	| CHILDTABLE_lex
	{	assert( $1.str == NULL );

		$$.str  = str_alloc("$childtable");
		$$.line = $1.line;
	}
	;

childhead
	: contents
	{
# ifndef NDEBUG
		CrossReference *C;
# endif
		char           *number  = NULL;
		char           *printid = NULL;
		char           *converted;

		assert( $1.str != NULL );

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

		output_text($1.line,"Contents",0,'\0',CheckSpell,ErrorColor);
		OutputString("</a></big></b>\n");
		ConvertForcedNewline(1);

		// defined cross reference point
# ifndef NDEBUG
		C =
# endif
		DefineCrossReference(
			CurrentSection->tag,
			HeadingAndSubHeading(),
			InputName(),
			iFrame,
			printid
		);
		assert( C != NULL);
		FreeMem(number);
		FreeMem(printid);

		$$ = $1;
	}
	;

childlist
	: children text DOUBLE_DOLLAR_lex
	{
		char       *p;
		char       *name;
		char       del;
		SectionInfo *F;
		SectionInfo *list;

		assert( $1.str != NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		F = CurrentSection->children;
		while( IsAutomaticSection(F) )
			F = F->next;
		if( F != NULL ) fatalomh(
			"Invalid ",
			$1.str,
			" command in line ",
			int2str($1.line),
			"\nThere was a previous ",
			"$contents, $children, or $childtable",
			"\ncommannd in this section",
			NULL
		);

		// delimiter is first character in text;
		del        = *($2.str);

		// last character in text
		p          = $2.str + strlen($2.str) - 1;
		if( *p != del ) fatalomh(
			"In delimiter sequence following ",
			$1.str,
			" command in line ",
			int2str($1.line),
			NULL
		);

		// add the files to the list in reverse order
		// because we add at the front of the list
		list       = NULL;
		while(p - 1 > $2.str)
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
				$1.str,
				" command in line ",
				int2str($1.line),
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

		if( strcmp($1.str, "$children") == 0 )
			OutputString("<CHILDREN>");
		else if( strcmp($1.str, "$contents") == 0 )
			OutputString("<CONTENTS>");
		else if( strcmp($1.str, "$childtable") == 0 )
			OutputString("<CHILDTABLE>");
		else	assert(0);


		FreeMem($1.str);
		FreeMem($2.str);

		$$.str  = NULL;
		$$.line = $1.line;
	}
	;

children
	: CHILDREN_lex
	{	assert( $1.str == NULL );

		RootHasChildren = 1;

		$$.str  = str_alloc("$children");
		$$.line = $1.line;
	}
	| childhead
	{	assert( $1.str != NULL );

		RootHasChildren = 1;

		$$ = $1;
	}
	;

cmindex : CINDEX_lex
	{	assert( $1.str == NULL );

		$$.str  = str_alloc("$cindex");
		$$.line = $1.line;
	}
	| MINDEX_lex
	{	assert( $1.str == NULL );

		$$.str  = str_alloc("$mindex");
		$$.line = $1.line;
	}
	| INDEX_lex
	{	assert( $1.str == NULL );

		$$.str  = str_alloc("$index");
		$$.line = $1.line;
	}
	;

cmark
	: CMARK_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| CMARK_lex argument DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		Cmark  = *($2.str);

		FreeMem($2.str);

		$$ = $1;
	}
	;

code_begin
	: CODE_lex
	{	assert( $1.str == NULL );

		OutputString("<code><font color=\"");
		OutputString(CodeColor);
		OutputString("\">");
		PushPending($1.line, "$code");

		$$ = $1;
	}
	;

code
	: code_begin element_list DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );

		OutputString("</font></code>");
		PopPending($3.line, "$code");

		$$ = $1;
	}
	;

codecolor
	: CODECOLOR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| CODECOLOR_lex text DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		FreeMem(CodeColor);
		CodeColor = Color($1.line, "$codecolor", $2.str);

		FreeMem($2.str);
		$$ = $1;
	}
	;


codep
	: CODEP_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| CODEP_lex text DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// $2 is called text in documentation
		SkipBeforeFirstAndAfterLastNewline(
			$2.line, $2.str, "$codep", "text"
		);

		if( ExecuteFile != NULL )
		{	char *text;
			int len;

			FreeMem(ExecuteFile);
			ExecuteFile = NULL;

			text = str_alloc($2.str);
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
				$2.line,
				CheckSpell,
				ErrorColor,
				HiliteColor,
				pre,
				$2.str
			);
		}
		OutputString("</pre></font></code>\n");

		FreeMem($2.str);

		$$ = $1;
	}
	;

comment
	: COMMENT_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| COMMENT_lex TEXT_lex DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		FreeMem($2.str);

		$$ = $1;
	}
	;

cref
	: CREF_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| CREF_lex text DOUBLE_DOLLAR_lex
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

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}


		// split text into tokens
		ntoken = SplitText($1.line, "$cref", $2.str);
		if( ntoken > 4 ) fatalomh(
			"At $cref command in line ",
			int2str($1.line),
			"\nMore than 5 delimiters in $cref command",
			NULL
		);

		// text for reference
		text = $2.str + 1;
		tag  = text + strlen(text) + 1;
		UniformWhiteSpace(text);
		if( text[0] == '\0' ) fatalomh(
			"At $cref command in line ",
			int2str($1.line),
			"\nthe text portion is only white space",
			NULL
		);

		// tag
		if( ntoken >= 2 )
		{	head = tag + strlen(tag) + 1;
			UniformWhiteSpace(tag);
			if( tag[0] == '\0' ) fatalomh(
				"At $cref command in line ",
				int2str($1.line),
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
				int2str($1.line),
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
				int2str($1.line),
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

		OutPre($2.line, text);
		HrefEnd("\n");

		// search for this cross reference
		C = FindCrossReference(tag, head);
		if( C == NULL )
			C = CreateCrossReference(tag, head, InputName());
		assert( C != NULL );

		// restore spell checking to initial setting
		CheckSpell = checkspell;

		FreeMem($2.str);

		$$ = $1;
	}
	;

date
	: DATE_lex
	{	time_t     time_t_time;
		struct tm     *tm_time;
		char        *char_time;
		char          date[13];
		int                  i;

		assert( $1.str == NULL );

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

		$$ = $1;
	}
	;


dollar
	: DOLLAR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| DOLLAR_lex argument DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		Dollar = *($2.str);

		FreeMem($2.str);

		$$ = $1;
	}
	;

end
	: END_lex
	{	assert( $1.str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// make sure there was a section command
		if( CurrentSection->title == NULL ) fatalomh(
			"There was no $section command\n",
			"between the $end command on line ",
			int2str($1.line),
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
			OmhPendingError($1.line, "$end");

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

		$$ = $1;
	}
	;


eof
	: EOF_lex
	{	// end of an input file

		SectionInfo *S;
		int          done;

		// initialize I to avoid warning
		// (compiler does not know it will be reset before used)
		SectionInfo *I = NULL;

		assert( $1.str != NULL );

		if( IncludeFrom != NULL )
		{	// not much to do in include file case
			InputPop();

			FreeMem(IncludeFrom);
			IncludeFrom = NULL;

			// no need for the previous command key character
			FreeMem($1.str);
			$1.str = NULL;
		}
		else
		{
		// not include file case ***********************************

		if( BeginCount == 0 ) fatalomh(
			"No ",
			$1.str,
			"begin commands in current input file",
			NULL
		);

		// lexomh ignores all commands until $begin is found
		assert( BeginCount >= EndCount );

		if( BeginCount > EndCount ) fatalomh(
			"There are more ",
			$1.str,
			"begin than ",
			$1.str,
			"end commmands\n",
			"in the current input file",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		// done with the previous command key character
		FreeMem($1.str);
		$1.str = NULL;

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

		$$ = $1;
	}
	;

errorcolor
	: ERRORCOLOR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| ERRORCOLOR_lex text DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		FreeMem(ErrorColor);
		ErrorColor = Color($1.line, "$errorcolor", $2.str);

		FreeMem($2.str);
		$$ = $1;
	}
	;

escape
	: ESCAPE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| ESCAPE_lex argument DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		Escape = *($2.str);

		if( CurrentSection->parent == NULL )
			EscapeRoot = Escape;

		FreeMem($2.str);

		$$ = $1;
	}
	;


execute
	: EXECUTE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| EXECUTE_lex argument DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

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
			int2str($1.line),
			" of file ",
			InputName(),
			NULL
		);

		// file name for error reporting
		ExecuteFile = str_alloc(InputName());
		ExecuteLine = $1.line;

		// file name to write to
		assert( CurrentSection->tag != NULL );
		ExecuteSetFile($2.str, CurrentSection->tag);

		// insert link to execute
		FormatOutput("<EXECUTE=\"%s\">", $2.str);

		FreeMem($2.str);

		$$ = $1;
	}
	;


fend
	: FEND_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| FEND_lex argument DOUBLE_DOLLAR_lex
	{
		int above;
		int below;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// check there are no pending commands
		if( NumberPending() > 0 )
			OmhPendingError($1.line, "$fend");

		if( ! (PrintableOmhelp() | NoFrame() ) )
		{
			if( iFrame >= MAX_FRAME ) fatalomh(
				"\nThere are more than ",
				int2str(MAX_FRAME),
				" frames requested for this section\n",
				"OMhelp Cannot satisfy the $fend request in ",
				"line ",
				int2str($1.line),
				NULL
			);

			above   = atoi($2.str);
			if( above < 5 ) fatalomh(
				"In the $fend command in line ",
				int2str($1.line),
				"\nthe requested frame size ",
				"is less than 5 percent\n",
				NULL
			);

			below = CurrentSection->Frame[iFrame - 1] - above;
			if( below < 5 ) fatalomh(
				"At the $fend command in line ",
				int2str($1.line),
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
		FreeMem($2.str);

		$$ = $1;
	}
	;

fixed_begin
	: FIXED_lex
	{	assert( $1.str == NULL );

		OutputString("<code>");
		PushPending($1.line, "$fixed");

		$$ = $1;
	}
	;

fixed
	: fixed_begin element_list DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );

		OutputString("</code>");
		PopPending($3.line, "$fixed");

		$$ = $1;
	}
	;

head
	: HEAD_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| HEAD_lex argument DOUBLE_DOLLAR_lex
	{
# ifndef NDEBUG
		CrossReference *C;
# endif
		char           *noEscape;
		char           *converted;
		char           *number = NULL;
		char           *printid = NULL;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		if( TableLevel > 0 ) fatalomh(
			"The $head command in line ",
			int2str($1.line),
			" is inside a table; i.e.,\n",
			"between a $table and the corresponding $tend",
			NULL
		);
		// make sure no # characters in heading
		if( strchr($2.str, '#') != NULL ) fatalomh(
			"$head command in line ",
			int2str($1.line),
			" has heading\n",
			$2.str,
			"\nThe character '#' is not allowed in headings",
			NULL
		);

		// version of heading without escape characters
		noEscape = str_alloc($2.str);
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

		output_text($2.line,noEscape,0,'\0',CheckSpell,ErrorColor);
		OutputString("</a></big></b>\n");

		// defined cross reference point
# ifndef NDEBUG
		C =
# endif
		DefineCrossReference(
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
		{	char *lower = StrLowAlloc($2.str);

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
		FreeMem($2.str);

		$$ = $1;

		PreviousOutputWasHeading = 1;
	}
	;


hilitecmd
	: HILITECMD_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| HILITECMD_lex text DOUBLE_DOLLAR_lex
	{	int n_command;
		n_command = SplitText($1.line, "hilitecmd", $2.str);
		hilite_command($1.line, n_command, $2.str);

		FreeMem($2.str);
	}
	;

hilitecolor
	: HILITECOLOR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| HILITECOLOR_lex text DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		FreeMem(HiliteColor);
		HiliteColor = Color($1.line, "$hilitecolor", $2.str);

		FreeMem($2.str);
		$$ = $1;
	}
	;


hiliteseq
	: HILITESEQ_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| HILITESEQ_lex text DOUBLE_DOLLAR_lex
	{	int n_token;
		n_token = SplitText($1.line, "hiliteseq", $2.str);
		hilite_seq($1.line, n_token, $2.str);

		FreeMem($2.str);
	}
	;
href
	: HREF_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| HREF_lex text DOUBLE_DOLLAR_lex
	{	char *url;
		char *frame;
		char *link;
		char *tag;
		char *heading;

		int checkspell;
		int ntoken;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// initial state of spell checker
		checkspell = CheckSpell;

		// split text into tokens
		ntoken = SplitText($1.line, "$href", $2.str);
		if( ntoken > 3 ) fatalomh(
			"In the $href command in line ",
			int2str($1.line),
			"\nTo many delimiters in the delimiter sequence",
			NULL
		);

		// internet address for reference
		url = $2.str + 1;

		// make sure url is not empty
		if( WhiteSpace(url) ) fatalomh(
			"In the $href command in line ",
			int2str($1.line),
			"\nOnly white space between first 2 delimiters",
			NULL
		);

		// make sure not using back slashes in address
		// because they do not work when displaying on Unix
		if( strchr(url, '\\') != NULL ) fatalomh(
			"In the $href command in line ",
			int2str($1.line),
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
			int2str($1.line),
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
			if( strchr(heading, '#') != NULL ) fatalomh(
				"In the $href command in line ",
				int2str($1.line),
				"\nlinking text has more than one '#' character",
				"\nPerhaps missing $newlinech #$$ at top of this section",
				NULL
			);
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
			OutPre($2.line, url);
		else	OutPre($2.line, link);
		HrefEnd("\n");

		if( ntoken >= 2 && PrintableOmhelp() )
		{	OutputString(" (");
			output_text($2.line,url,0,'\0',CheckSpell,ErrorColor);
			OutputString(") ");
		}

		CheckSpell = checkspell;
		FreeMem(tag);
		FreeMem($2.str);

		$$ = $1;
	}
	;

icode
	: ICODE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| ICODE_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		color_switch($2.str, "black", "blue", Escape,
			$1.line, "icode", CheckSpell, ErrorColor);

		FreeMem($2.str);
		$$ = $1;
	}
	;

image_begin
	: ICON_lex
	{	assert( $1.str == NULL );

		$$.str  = str_alloc("$icon");
		$$.line = $1.line;

	}
	| IMAGE_lex
	{	assert( $1.str == NULL );

		$$.str  = str_alloc("$image");
		$$.line = $1.line;
	}
	;


image
	: image_begin text DOUBLE_DOLLAR_lex
	{

		char *root;
		char *ext;
		char *name;
		char *fullname;

		char *localname;

		int  i;

		assert( $1.str != NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// split text into tokens
		int ntoken = SplitText($1.line, $1.str, $2.str);
		if( ntoken > 2 ) fatalomh(
			$1.str,
			" command in line ",
			int2str($1.line),
			"\nMore than 3 delimiters in command",
			NULL
		);

		// first token
		char* file_in  = $2.str + 1;
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
			$1.str,
			" at line ",
			int2str($1.line),
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
				$1.str,
				" at line ",
				int2str($1.line),
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
				$1.str,
				" at line ",
				int2str($1.line),
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


		if( strcmp( $1.str, "$icon" ) == 0 )
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
		else if( strcmp( $1.str, "$image" ) == 0 )
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

		FreeMem($1.str);
		FreeMem($2.str);
		FreeMem(localname);

		$$.str  = NULL;
		$$.line = $1.line;
	}
	;

include
	: INCLUDE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| INCLUDE_lex argument DOUBLE_DOLLAR_lex
	{	char  *root;
		char  *ext;
		char  cmd_key_char;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( IncludeFrom != NULL ) fatalomh(
			"Cannot use $include command on line ",
			int2str($1.line),
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
		IncludeLine = $1.line;

		root = str_alloc($2.str);

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

		FreeMem($2.str);

		$$ = $1;
	}
	;


index
	: cmindex text DOUBLE_DOLLAR_lex
	{	char *text = $2.str;
		int line   = $1.line;


		assert( $1.str != NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// add keywords to search for this section
		SearchKeywords(text, Escape, "");

		// check for seplling error
		if( CheckSpell )
		{
			const char *s = $2.str;
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
		if( strcmp($1.str, "$index") == 0 ) InsertInIndex(
			text,
			CurrentSection->tag,
			HeadingAndSubHeading(),
			Escape
		);
		else if( strcmp($1.str, "$cindex") == 0 ) CycleIntoIndex(
			text,
			CurrentSection->tag,
			HeadingAndSubHeading(),
			Escape
		);
		else if( strcmp($1.str, "$mindex") == 0 ) MultipleIntoIndex(
			text,
			CurrentSection->tag,
			HeadingAndSubHeading(),
			Escape,
			""
		);
		else	assert(0);

		FreeMem($1.str);
		FreeMem($2.str);

		$$.str  = NULL;
		$$.line = $1.line;
	}
	;

italic_begin
	: ITALIC_lex
	{	assert( $1.str == NULL );

		OutputString("<i>");
		PushPending($1.line, "$italic");
		ItalicCount++;

		$$ = $1;
	}
	;

italic
	: italic_begin element_list DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );

		OutputString("</i>");
		PopPending($3.line, "$italic");
		ItalicCount--;

		$$ = $1;
	}
	;

keyword
	: AINDEX_lex
	| ALIGN_lex
	| BEGIN_lex
	| BGCOLOR_lex
	| BIG_lex
	| BOLD_lex
	| CEND_lex
	| CENTER_lex
	| CHILDREN_lex
	| CHILDTABLE_lex
	| CINDEX_lex
	| CMARK_lex
	| CNEXT_lex
	| CODE_lex
	| CODECOLOR_lex
	| CODEI_lex
	| CODEP_lex
	| COMMENT_lex
	| CONTENTS_lex
	| CREF_lex
	| DATE_lex
	| DOLLAR_lex
	| END_lex
	| ERRORCOLOR_lex
	| ESCAPE_lex
	| EXECUTE_lex
	| FEND_lex
	| FIXED_lex
	| HEAD_lex
	| HILITECMD_lex
	| HILITECOLOR_lex
	| HILITESEQ_lex
	| HREF_lex
	| ICODE_lex
	| ICON_lex
	| IMAGE_lex
	| INCLUDE_lex
	| INDEX_lex
	| ITALIC_lex
	| LATEX_lex
	| LEND_lex
	| LINKCOLOR_lex
	| LIST_lex
	| LNEXT_lex
	| MATH_lex
	| MINDEX_lex
	| MREF_lex
	| NAVIGATE_lex
	| NEWLINECH_lex
	| NOBREAK_lex
	| NOSPELL_lex
	| PATH_lex
	| PRE_lex
	| REND_lex
	| RMARK_lex
	| RNEXT_lex
	| RREF_lex
	| SECTION_lex
	| SKIPNL_lex
	| SMALL_lex
	| SPELL_lex
	| SUBHEAD_lex
	| SYNTAX_lex
	| TABLE_lex
	| TABSIZE_lex
	| TEND_lex
	| TEXTCOLOR_lex
	| TH_lex
	| TITLE_lex
	| TRACE_lex
	| TREF_lex
	| VERBATIM_lex
	| VISITCOLOR_lex
	| WSPACE_lex
	| XREF_lex
	{	$$ = $1;
	}
	;

latex
	: LATEX_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| LATEX_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( strcmp(".xml", Internal2Out("OutputExtension") ) == 0 )
		{	int BlockDisplay;

			LatexLexPut($2.line, $2.str);
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
			{	char *s = $2.str;
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
			const char* latex_cmds = $2.str;
			math_jax(macro_cmd, latex_cmds);

			CheckSpell = checkspell;
		}

		FreeMem($2.str);

		$$ = $1;
	}
	;


lend
	: LEND_lex
	{	assert( $1.str == NULL );

		if( ListLevel <= 0 ) fatalomh(
			"There is no matching $list command preceeding\n",
			"the $lend command in line ",
			int2str($1.line),
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		ListLevel--;
		if( ListOrdered[ListLevel] )
			OutputString("</li></ol>\n");
		else	OutputString("</li></ul>\n");

		PopPending($1.line, "$list");
		$$ = $1;
	}
	;

linkcolor
	: LINKCOLOR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| LINKCOLOR_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// only one $linkcolor per section
		if( CurrentSection->style.linkcolor != NULL ) fatalomh(
			"At $linkcolor comamnd in line ",
			int2str($1.line),
			"\nThere is more than one $linkcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.linkcolor = Color(
			$1.line, "$linkcolor", $2.str
		);

		FreeMem($2.str);
		$$ = $1;
	}
	;

list
	: LIST_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| LIST_lex argument DOUBLE_DOLLAR_lex
	{	// initalize cmd to avoid warning
		// (compiler does not know fatalerr will not return)
		char *cmd = NULL;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );


		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		if( ListLevel == MAX_LIST_LEVEL ) fatalomh(
			"At $list command in line ",
			int2str($1.line),
			"\nMore than ",
			int2str(MAX_LIST_LEVEL),
			" levels of nested lists requested",
			NULL
		);

		ListOrdered[ListLevel]= 1;

		if( strcmp($2.str, "disk") == 0 )
		{	cmd  = "<ul type=\"disk\"><li>";
			ListOrdered[ListLevel] = 0;
		}
		else if( strcmp($2.str, "circle") == 0 )
		{	cmd  = "<ul type=\"circle\"><li>";
			ListOrdered[ListLevel] = 0;
		}
		else if( strcmp($2.str, "square") == 0 )
		{	cmd  = "<ul type=\"square\"><li>";
			ListOrdered[ListLevel] = 0;
		}
		else if( strcmp($2.str, "number") == 0 )
			cmd  = "<ol type=\"1\"><li>";
		else if( strcmp($2.str, "alpha") == 0 )
			cmd  = "<ol type=\"a\"><li>";
		else if( strcmp($2.str, "Alpha") == 0 )
			cmd  = "<ol type=\"A\"><li>";
		else if( strcmp($2.str, "roman") == 0 )
			cmd  = "<ol type=\"i\"><li>";
		else if( strcmp($2.str, "Roman") == 0 )
			cmd  = "<ol type=\"I\"><li>";
		else fatalomh(
			"At $list command in line ",
			int2str($1.line),
			"\n",
			$2.str,
			" is not a valid marker for a $list command",
			NULL
		);

		ListLevel++;

		OutputString(cmd);

		FreeMem($2.str);

		PushPending($1.line, "$list");

		$$ = $1;
	}
	;

lnext
	: LNEXT_lex
	{	assert( $1.str == NULL );

		if( ListLevel == 0 ) fatalomh(
			"The $lnext command in line ",
			int2str($1.line),
			"\nis not inside of a list; i.e.,\n",
			"not between a $list and the corresponding $lend",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		OutputString("</li><li>\n");

		$$ = $1;
	}
	;

math
	: MATH_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| MATH_lex text DOUBLE_DOLLAR_lex
	{	int   ntoken;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// split text into tokens
		ntoken = SplitText($1.line, "$math", $2.str);


		// if output begins with a preformatted new line
		// do not need an extra one to for previous heading
		if( PreviousOutputWasHeading )
		{	char *s = $2.str + 1;
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

		OutputMath(ntoken, $2.str + 1, Escape, ItalicCount > 0);

		FreeMem($2.str);

		$$ = $1;
	}

	;

mref
	: MREF_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| MREF_lex text DOUBLE_DOLLAR_lex
	{	char *tag;
		char *next;
		CrossReference *C;
		int nref;
		int checkspell;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// suspend spell checking
		checkspell = CheckSpell;
		CheckSpell = 0;

		// split text into tokens
		nref = SplitText($1.line, "$mref", $2.str);

		// tag for reference
		tag = $2.str + 1;

		// output the cross reference jump
		while(nref--)
		{	// get next pointer before cliping white space
			next = strlen(tag) + tag + 1;

			// convert to unifrom white space format
			UniformWhiteSpace(tag);

			// make sure take is not empty
			if( tag[0] == '\0' ) fatalomh(
				"At $mref command in line ",
				int2str($1.line),
				"only white space between two delimiters ",
				"following $mref command",
				NULL
			);

			// output the cross reference
			OutputString(" ");
			HrefOutputPass1(tag, "", "false", "", "true");
			OutPre($2.line, tag);
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

		FreeMem($2.str);

		$$ = $1;
	}
	;


navigate
	: NAVIGATE_lex text not_2_dollar_or_text
	{       fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
        }
	| NAVIGATE_lex text DOUBLE_DOLLAR_lex
	{	int ntoken;

		// split text into tokens
		ntoken = SplitText($1.line, "$navigate", $2.str);

		// set the current navigation sequence
		SectionNavigate(CurrentSection, ntoken, $2.str + 1, $1.line);

		// done with the delimiter sequence
		FreeMem($2.str);
	}
	;


newlinech
	: NEWLINECH_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| NEWLINECH_lex argument DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( strlen($2.str)  > 1 ) fatalomh(
			"More that one character is specified by the\n",
			"$newlinech comamnd in line ",
			int2str($1.line),
			NULL
		);

		NewlineCh = *($2.str);

		FreeMem($2.str);

		$$ = $1;
	}
	;

nobreak
	: NOBREAK_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| NOBREAK_lex text DOUBLE_DOLLAR_lex
	{	int pre = 0;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		OutputString("<span style='white-space: nowrap'>");
		output_text($2.line,$2.str,pre,'\0',CheckSpell,ErrorColor);
		OutputString("</span>\n");

		FreeMem($2.str);

		$$ = $1;
	}
	;

nospell_begin
	: NOSPELL_lex
	{	assert( $1.str == NULL );

		CheckSpell = 0;
		PushPending($1.line, "$nospell");

		$$ = $1;
	}
	;

nospell
	: nospell_begin element_list DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );

		CheckSpell = 1;
		PopPending($3.line, "$nospell");

		$$ = $1;
	}
	;

not_2_dollar_or_text
	: keyword
	| ACCENT_lex
	| EOF_lex
	| NUMBER_lex
	;

number
	: NUMBER_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| NUMBER_lex DOUBLE_DOLLAR_lex
	{	assert( $1.str != NULL );
		assert( $2.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		OutputMath(1, $1.str, '\0', ItalicCount > 0);

		FreeMem($1.str);

		$$.str  = NULL;
		$$.line = $1.line;
	}
	;

path
	: PATH_lex text DOUBLE_DOLLAR_lex
	{
		char *path;
		char *ext;
		int ntoken;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// only use path command at root level
		if( CurrentSection == SectionTree )
		{
			// split text into tokens
			ntoken = SplitText($1.line, "$path", $2.str);
			if( ntoken != 2 ) fatalomh(
				"At $path comamnd in line ",
				int2str($1.line),
				"\n$path command expects three delimiters",
				NULL
			);

			// path token
			path = $2.str + 1;

			// extension token
			ext  = path + strlen(path) + 1;

			InputAddPath(path, ext);
		}


		FreeMem($2.str);

		$$ = $1;
	}
	;

pre
	: PRE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| PRE_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// if output begins with a preformatted new line
		// do not need an extra one to for previous heading
		if( PreviousOutputWasHeading )
		{	char *s = $2.str;
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
		OutPre($2.line, $2.str);
		OutputString("</code>");

		FreeMem($2.str);

		$$ = $1;
	}
	;

rnext:
	rnext_cases
	{	assert( $1.str != NULL );

		if( TableLevel == 0 ) fatalomh(
			"The ",
			$1.str,
			" command in line ",
			int2str($1.line),
			"\nis not inside of a table; i.e.,\n",
			"not between a $table and the corresponding $tend",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		OutputString("</td></tr><tr>");
		FormatOutput("<td align='%s' ", HorizontalAlign);
		FormatOutput(" valign='%s'>\n", VerticalAlign);

		PopPending( $1.line, "$cnext");
		PopPending( $1.line, "$rnext");
		PushPending($1.line, "$rnext");
		PushPending($1.line, "$cnext");

		FreeMem($1.str);

		$$.str   = NULL;
		$$.line  = $1.line;
	}
	;

rnext_cases
	: REND_lex
	{	assert( $1.str == NULL );
		assert( PreviousOutputWasHeading == 0 );

		$$.str = str_alloc("$rend");
		$$.line = $1.line;
	}
	| RNEXT_lex
	{	assert( $1.str == NULL );
		assert( PreviousOutputWasHeading == 0 );

		$$.str = str_alloc("$rnext");
		$$.line = $1.line;
	}
	;

rmark
	: RMARK_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| RMARK_lex argument DOUBLE_DOLLAR_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		Rmark  = *($2.str);

		FreeMem($2.str);

		$$ = $1;
	}
	;

rref
	: RREF_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| RREF_lex argument DOUBLE_DOLLAR_lex
	{	char *tag;
		CrossReference *C;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// this command must be inside of a table
		if( TableLevel == 0 ) fatalomh(
			"The $rref command in line ",
			int2str($1.line),
			"\nis not inside of a table; i.e.,\n",
			"not between a $table and the corresponding $tend",
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		// cross reference tag
		tag = $2.str;

		// convert to uniform white space format
		UniformWhiteSpace(tag);

		// output the cross reference
		FormatOutput("<RREF=\"%s\">", tag);

		// search for this cross reference
		C = FindCrossReference(tag, "");
		if( C == NULL )
			C = CreateCrossReference(tag, "", InputName());
		assert( C != NULL );

		FreeMem($2.str);

		$$ = $1;
	}
	;

section
	: SECTION_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SECTION_lex argument DOUBLE_DOLLAR_lex
	{	char *noEscape;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// I guess some one might put a paragraph heading
		// for an empty paragraph directly before the section title
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// remember the title
		if( CurrentSection->title != NULL ) fatalomh(
			"At $section command in line ",
			int2str($1.line),
			"\nMore than one $section command between\n",
			"the $begin and $end for the current section",
			NULL
		);

		// version of title without escape characters
		noEscape = str_alloc($2.str);
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
				output_text($2.line,noEscape,0,'\0',
					CheckSpell,ErrorColor);
				OutputString("</a>\n");
			}
			else	output_text($2.line,noEscape,0,'\0',
					CheckSpell,ErrorColor);

			FreeMem(printid);
		}
		else	output_text($2.line,noEscape,0,'\0',
					CheckSpell,ErrorColor);
		OutputString("</big></big></b></center>\n");

		// mark the end of the title for this section
		OutputString("<ETITLE>");

		// the end of centering starts a new line
		ConvertAddPrevious(1);

		if( MindexSection )
		{	char *lower = StrLowAlloc($2.str);

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
		FreeMem($2.str);

		$$ = $1;
	}
	;

skipnl
	: SKIPNL_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SKIPNL_lex argument DOUBLE_DOLLAR_lex
	{	fatalomh(
			"At $skipnl in line ",
			int2str($1.line),
			"\nThe $skipnl command has been removed from\n",
			"the OMhelp language",
			NULL
		);
	}
	;

small_begin
	: SMALL_lex
	{	assert( $1.str == NULL );

		OutputString("<small>");
		PushPending($1.line, "$small");

		$$ = $1;
	}
	;

small
	: small_begin element_list DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );

		OutputString("</small>");
		PopPending($3.line, "$small");

		$$ = $1;
	}
	;

spell
	: SPELL_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SPELL_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( $2.str[0] != '\0' )
			SpellingOkList($2.str);

		FreeMem($2.str);

		$$ = $1;
	}
	;
srccode
	: SRCCODE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SRCCODE_lex text DOUBLE_DOLLAR_lex
	{	int ntoken;
		char *ext, *source, *input_lang, *output_lang, *data, *tmp;
		int   indent, tabsize;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		// split delimiter sequence into tokens
		ntoken = SplitText($1.line, "$srccode", $2.str);
		if( ntoken != 2 ) fatalomh(
			"At $srccode command in line ",
			int2str($1.line),
			"\nExpected 3 delimiters in the $srccode command",
			NULL
		);

		// get the file extension token
		ext  = $2.str + 1;

		// get the source token
		source  = ext + strlen(ext) + 1;

		// check the input language
		input_lang  = file_ext2lang(ext);
		if( input_lang == NULL ) fatalomh(
			"At $srccode command in line ",
			int2str($1.line),
			"\nCannot use the $srccode command becasue the",
			"\nsource-highlight or boost_regex library is not avaiable.",
			NULL
		);
		if( input_lang[0] == '\0' )
		{	fatalomh(
				"At $srccode command in line ",
				int2str($1.line),
				"\nCannot determine language for the file extension ",
				ext,
				NULL
			);
		}

		// determine what language the output file is in
		if( strcmp( Internal2Out("OutputExtension"), ".htm") == 0 )
			output_lang = "html.outlang";
        else
            output_lang = "xhtml.outlang";

		// skip characters before first and after last newline in source
		SkipBeforeFirstAndAfterLastNewline(
			$2.line, source, "$srccode", "source"
		);

		// number of newliness there will be at end of soruce
		tmp = source + strlen(source) - 1;
		while( isspace(*tmp) && source < tmp )
		{	if( *tmp == '\n' )
				ConvertAddPrevious(1);
			tmp--;
		}

		// do not indent any more that the input specifies
		indent = 0;

		// space between tab columns
		tabsize = TabSizeCurrent;

		// convert source to the output language with highlighting
		data = highlight(source, input_lang, output_lang, indent, tabsize);

		// output the data
		tmp    = data;
		while( *tmp != '\0' )
			OutputChar( *tmp++ );

		FreeMem(input_lang);
		FreeMem(data);
		FreeMem($2.str);

		$$ = $1;
	}
	;

srcfile
	: SRCFILE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SRCFILE_lex text DOUBLE_DOLLAR_lex
	{	// command parameters
		char *filename, *start, *stop, *token;
		int  skip, indent;

		// local variables
		int  ntoken;
		int  newline_at_start;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		ntoken = SplitText($1.line, "$srcfile", $2.str);
		if( ntoken < 1 ) fatalomh(
			"$srcfile command in line ",
			int2str($1.line),
			"\nExpected at least 2 delimiters in command",
			NULL
		);
		if( ntoken == 3 ) fatalomh(
			"$srcfile command in line ",
			int2str($1.line),
			"\nMust also specify stop when start is present",
			NULL
		);
		if( ntoken > 6 ) fatalomh(
			"$srcfile command in line ",
			int2str($1.line),
			"\nExpected at most 6 delimiters in $srcfile command",
			NULL
		);

		// filename
		filename = $2.str + 1;

		// indent
		if( ntoken < 2 )
			indent = 0;
		else
		{	token  = filename + strlen(filename) + 1;
			indent = atoi(token);
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

		// if start is not present, start with a newline for beginning of file
		// if previous output was a heading, start with a newline
		newline_at_start = ntoken < 3 && ConvertPreviousNewline() < 1;
		newline_at_start = newline_at_start || PreviousOutputWasHeading;
		//
		srcfile(
			"$srcfile",
			$1.line,
			newline_at_start,
			filename,
			indent,
			start,
			stop,
			skip
		);
		//
		// no longer need flag for previous heading
		PreviousOutputWasHeading = 0;


		FreeMem($2.str);
		$$ = $1;
	}
	;

srcthisfile
	: SRCTHISFILE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SRCTHISFILE_lex text DOUBLE_DOLLAR_lex
	{	// command parameters
		char *start, *stop, *token;
		int  skip, indent;

		// local variables
		int  ntoken;
		int  newline_at_start;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		ntoken = SplitText($1.line, "$srcfile", $2.str);
		if( ntoken < 1 ) fatalomh(
			"$srcthisfile command in line ",
			int2str($1.line),
			"\nExpected at least 2 delimiters in command",
			NULL
		);
		if( ntoken == 2 ) fatalomh(
			"$srcthisfile command in line ",
			int2str($1.line),
			"\nMust also specify stop when start is present",
			NULL
		);
		if( ntoken > 5 ) fatalomh(
			"$srcthisfile command in line ",
			int2str($1.line),
			"\nExpected at most 5 delimiters in $srcfile command",
			NULL
		);
		// delimiter != '\0'
		assert( $2.str[0] != '\0' );

		// indent
		token  = $2.str + 1;
		indent = atoi(token);

		// start
		if( ntoken < 2 )
			start = "";
		else
			start = token + strlen(token) + 1;

		// stop
		if( ntoken < 3 )
			stop = "";
		else
			stop = start + strlen(start) + 1;

		// skip
		if( ntoken < 4 )
			skip = 0;
		else
		{	token = stop + strlen(stop) + 1;
			skip = atoi(token);
		}

		// if start is not present, start with a newline for beginning of file
		// if previous output was a heading, start with a newline
		newline_at_start = ntoken < 3 && ConvertPreviousNewline() < 1;
		newline_at_start = newline_at_start || PreviousOutputWasHeading;
		//
		srcfile(
			"$srcthisfile",
			$1.line,
			newline_at_start,
			InputName(),
			indent,
			start,
			stop,
			skip
		);
		//
		// no longer need flag for previous heading
		PreviousOutputWasHeading = 0;


		FreeMem($2.str);
		$$ = $1;
	}
	;

subhead
	: SUBHEAD_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SUBHEAD_lex argument DOUBLE_DOLLAR_lex
	{
# ifndef NDEBUG
		CrossReference *C;
# endif
		char           *number = NULL;
		char           *printid = NULL;
		char           *noEscape;
		char           *converted;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( TableLevel > 0 ) fatalomh(
			"The $subhead command in line ",
			int2str($1.line),
			" is inside a table; i.e.,\n",
			"between a $table and the corresponding $tend",
			NULL
		);

		// make sure no # characters in subheading
		if( strchr($2.str, '#') != NULL ) fatalomh(
			"$head command in line ",
			int2str($1.line),
			" has heading\n",
			$2.str,
			"\nThe character '#' is not allowed in headings",
			NULL
		);

		// make sure no # characters in heading
		if( strchr($2.str, '#') != NULL ) fatalomh(
			"$subhead command in line ",
			int2str($1.line),
			" has subheading\n",
			$2.str,
			"\nThe character '#' is not allowed in headings",
			NULL
		);

		if( ConvertPreviousNewline() < 2 )
			ConvertForcedNewline(2 - ConvertPreviousNewline() );

		// version of heading without escape characters
		noEscape = str_alloc($2.str);
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

		OutputString("<big>");
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

		output_text($2.line,noEscape,0,'\0',CheckSpell,ErrorColor);
		OutputString("</a></big>\n");

		// defined cross reference point
# ifndef NDEBUG
		C =
# endif
		DefineCrossReference(
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
		{	char *lower = StrLowAlloc($2.str);

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
		FreeMem($2.str);

		$$ = $1;

		PreviousOutputWasHeading = 1;
	}
	;

syntax
	: SYNTAX_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| SYNTAX_lex text DOUBLE_DOLLAR_lex
	{	char *token;
		char *next;
		int  count;
		int  ntoken;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// split text into tokens
		ntoken = SplitText($1.line, "$syntax", $2.str);

		// first token
		token = $2.str + 1;

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
				output_text($2.line,token,1,'\0',
					CheckSpell,ErrorColor);
				OutputString("</i>");
			}
			else
			{	// code font
				OutputString("<code><font color=\"");
				OutputString(CodeColor);
				OutputString("\">");
				output_text($2.line,token,1,'\0',
					CheckSpell,ErrorColor);
				OutputString("</font></code>");
			}
			count++;
			token = next;
		}

		FreeMem($2.str);

		$$ = $1;
	}
	;

table
	: TABLE_lex
	{	assert( $1.str == NULL );

		// do not need extra new line after previous heading
		if( PreviousOutputWasHeading )
			PreviousOutputWasHeading = 0;

		TableLevel++;

		OutputString("<table><tr>");
		FormatOutput("<td align='%s' ", HorizontalAlign);
		FormatOutput(" valign='%s'>\n", VerticalAlign);

		PushPending($1.line, "$table");
		PushPending($1.line, "$rnext");
		PushPending($1.line, "$cnext");


		$$ = $1;
	}
	;

tabsize
	: TABSIZE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| TABSIZE_lex argument DOUBLE_DOLLAR_lex
	{	int size;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		size = atoi($2.str);
		if( size >= 100 ) fatalomh(
			"In $tabsize command in line ",
			int2str($1.line),
			"\nnumber of columns is greater than 99",
			NULL
		);
		if( size < 0 ) fatalomh(
			"In $tabsize command in line ",
			int2str($1.line),
			"\nnumber of columns is less than zero",
			NULL
		);
		if( size == 0 )
			size = TAB_SIZE;

		ConvertSetTabSize(size);
		TabSizeCurrent = size;
		//
		if( CurrentSection->parent == NULL )
			TabSizeRoot = size;

		FreeMem($2.str);

		$$ = $1;
	}
	;


tend
	: TEND_lex
	{	assert( $1.str == NULL );

		if( TableLevel <= 0 ) fatalomh(
			"There is no matching $table command preceeding\n",
			"the $tend command in line ",
			int2str($1.line),
			NULL
		);
		assert( PreviousOutputWasHeading == 0 );

		TableLevel--;
		OutputString("</td></tr>\n</table>\n");

		// tables had an automatic new line after them
		// (avoid adding more than once when tables are nested)
		if( TableLevel == 0 )
			ConvertAddPrevious(1);

		PopPending($1.line, "$cnext");
		PopPending($1.line, "$rnext");
		PopPending($1.line, "$table");
	}
	;
text
	: text_raw
	{	assert ( $1.str != NULL );

		$$ = $1;
	}
	;

text_raw
	: TEXT_lex
	{	int line = $1.line;
		char *p = $1.str;
		char *q = $1.str;

		assert( $1.str != NULL );
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

		$$ = $1;
	};

textcolor
	: TEXTCOLOR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| TEXTCOLOR_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// only one $textcolor per section
		if( CurrentSection->style.textcolor != NULL ) fatalomh(
			"At $textcolor comamnd in line ",
			int2str($1.line),
			"\nThere is more than one $textcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.textcolor = Color(
			$1.line, "$textcolor", $2.str
		);

		FreeMem($2.str);
		$$ = $1;
	}
	;

th
	: TH_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| TH_lex argument DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// output the index in italic followed by "-th"
		OutputString("<code><i>");
		output_text($2.line,$2.str,0,'\0',CheckSpell,ErrorColor);
		OutputString("</i></code>");
		OutputString("-th");

		FreeMem($2.str);

		$$ = $1;
	}

	;

trace
	: TRACE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| TRACE_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		printf("%s", $2.str);
		FreeMem($2.str);

		$$ = $1;
	}
	;
title
	: TITLE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| TITLE_lex argument DOUBLE_DOLLAR_lex
	{	char *tag = $2.str;
		CrossReference *C;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

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

		FreeMem($2.str);

		$$ = $1;
	}
	;

tref
	: TREF_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| TREF_lex argument DOUBLE_DOLLAR_lex
	{	char *tag;
		CrossReference *C;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

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
		tag = $2.str;

		// convert to uniform white space format
		UniformWhiteSpace(tag);

		// output the cross reference
		FormatOutput("<TREF=\"%s\">", tag);

		// search for this cross reference
		C = FindCrossReference(tag, "");
		if( C == NULL )
			C = CreateCrossReference(tag, "", InputName());
		assert( C != NULL );

		FreeMem($2.str);

		$$ = $1;
	}
	;


verbatim
	: VERBATIM_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| VERBATIM_lex text DOUBLE_DOLLAR_lex
	{	char *root, *ext, *filename, *start, *stop;
		char ch, previous;
		int  skip, ntoken, indent, match, len;
		int  i;
		char line_buffer[300];
		int  line_max = 299;
		int  line_index;

		// initialize token to avoid warning
		// (compiler does not know fatalerr will not return)
		char *token = NULL;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		ntoken = SplitText($1.line, "$verbatim", $2.str);
		if( 5 < ntoken ) fatalomh(
			"At $verbatim command in line ",
			int2str($1.line),
			"\nMore than 6 delimiters in $verbatim command",
			NULL
		);

		filename = $2.str + 1;
		if( ntoken < 2 )
			indent = 0;
		else
		{	token = filename + strlen(filename) + 1;
			indent = atoi(token);
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
				int2str($1.line),
				"\nToo many characters in start pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				"At $verbatim command in line ",
				int2str($1.line),
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
					int2str($1.line),
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
				int2str($1.line),
				"\nToo many characters in stop pattern",
				NULL
			);
		}
		if( len == -2 )
		{	InputPop();
			fatalomh(
				"At $verbatim command in line ",
				int2str($1.line),
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
			{	for(i = 0; i < indent; i++)
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
					int2str($1.line),
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
					$2.line,
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
			int2str($1.line),
			"\nCould not find the stop pattern \"",
			stop,
			"\"\nin the file ",
			filename,
			NULL
		);

		FreeMem(root);
		FreeMem(ext);
		FreeMem($2.str);

		$$ = $1;
	}
	;

visitcolor
	: VISITCOLOR_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| VISITCOLOR_lex text DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		// only one $visitcolor per section
		if( CurrentSection->style.visitcolor != NULL ) fatalomh(
			"At $visitcolor comamnd in line ",
			int2str($1.line),
			"\nThere is more than one $visitcolor command ",
			"in this section.",
			NULL
		);


		CurrentSection->style.visitcolor = Color(
			$1.line, "$visitcolor", $2.str
		);

		FreeMem($2.str);
		$$ = $1;
	}
	;
wspace
	: WSPACE_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| WSPACE_lex argument DOUBLE_DOLLAR_lex
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		Wspace = *($2.str);

		FreeMem($2.str);

		$$ = $1;
	}
	;

xref
	: XREF_lex text not_2_dollar_or_text
	{	fatal_not_2_dollar_or_text($1.code, $1.line, $3.code);
	}
	| XREF_lex text DOUBLE_DOLLAR_lex
	{	char *tag;
		char *head;
		char *subhead;
		char *link;
		char *frame;
		CrossReference *C;

		int checkspell;
		int ntoken;
		int i, j;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );

		if( PreviousOutputWasHeading )
		{	ConvertForcedNewline(1);
			PreviousOutputWasHeading = 0;
		}

		// initial state of spell checker
		checkspell = CheckSpell;

		// split text into tokens
		ntoken = SplitText($1.line, "$xref", $2.str);
		if( ntoken > 5 ) fatalomh(
			"At $xref command in line ",
			int2str($1.line),
			"\nMore than 6 delimiters in $xref command",
			NULL
		);

		// tag for reference
		tag = $2.str + 1;

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
			int2str($1.line),
			"\nOnly white space between first 2 delimiters",
			NULL
		);


		// check the frame specification
		if( ntoken >= 4  )
		{
			if( frame[0] == '\0' ) fatalomh(
				"At $xref command in line ",
				int2str($1.line),
				"\nFrame number in $xref command is empty; ",
				"i.e., just white space.",
				NULL
			);

			i     = atoi(frame);
			if( i < 1 ) fatalomh(
				"At $xref command in line ",
				int2str($1.line),
				"\nFrame number in $xref command is ",
				"less than 1",
				NULL
			);

			if( i > MaxFrame )
			{	FreeMem( MaxFrameFile );
				MaxFrame = i;
				MaxFrameLine = $1.line;
				MaxFrameFile = str_alloc(InputName());
			}

			if( head[0] == '\0' ) fatalomh(
				"At $xref command in line ",
				int2str($1.line),
				"\nCannot have an empty heading",
				"\nwhen a particular frame is specified.",
				NULL
			);
		}

		// if subheading is specified, check that heading is not empty
		if( subhead[0] != '\0' && head[0] == '\0' ) fatalomh(
			"At $xref command in line ",
			int2str($1.line),
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

		OutPre($2.line, link);
		HrefEnd("\n");

		// search for this cross reference
		C = FindCrossReference(tag, head);
		if( C == NULL )
			C = CreateCrossReference(tag, head, InputName());
		assert( C != NULL );

		// restore spell checking to initial setting
		CheckSpell = checkspell;

		FreeMem($2.str);

		$$ = $1;
	}
	;
%%
