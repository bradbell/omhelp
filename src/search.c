/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <assert.h>

# ifndef WIN32
# include <unistd.h>
# endif

# include "fatalerr.h"
# include "strjoin.h"
# include "allocmem.h"
# include "DirSep.h"
# include "StrLowAlloc.h"
# include "str_alloc.h"
# include "StrRemove.h"
# include "Internal2Out.h"


# include "search.h"

# define MAX_KEYWORD   2000
# define MAX_WORD      1000

static FILE *Fp                = NULL;
static char *FrameOneName      = NULL;
static char *JavascriptName    = NULL;
static int   SectionCount      = 0;
static int   SectionOpen       = 0;
static char *Title             = NULL;
static char *TitleLower        = NULL;
static char *Tag               = NULL;
static char *TagLower          = NULL;
static char *KeywordLower      = NULL;


static char  KeywordList[MAX_KEYWORD];

static void Output(const char *list, const char *terminate)
{	char last = '\0';
	char ch   = *list++;

	assert( Fp != NULL);

	if( ch == '\0' )
	{	fprintf(Fp, "%s", terminate);
		return;
	}

	last = ch;
	ch   = *list++;
	while( ch != '\0' )
	{
		if( ! ( isspace((int) ch) && isspace((int) last) ) )
		{
			if( isspace((int) last) )
				fputc(' ', Fp);
			else	fputc(last, Fp);

			// put backslash before single quote because this text
			// is inside of single quotes
			if( ch == '\'' )
				fputc('\\', Fp);
		}
		last = ch;
		ch   = *list++;
	}
	if( ! isspace((int) last) )
		fputc(last, Fp);
	fprintf(Fp, "%s", terminate);
	return;
}

static char *FrameOne =
"\n"
"<noscript><h1>\n"
"This search utility requires Javascript to be enabled\n"
"and Javascript is disabled in your browser.\n"
"</h1></noscript>\n"
"<h2>SiteTitle</h2>\n"
"<form name='search'>\n"
"<p><table>\n"
"	<tr><td>\n"
"		Enter keywords separated by spaces below\n"
"	</td><td>\n"
"		<input\n"
"			type='button'\n"
"			value='Goto'\n"
"			onclick='Goto()'\n"
"		/>\n"
"		Selection\n"
"	</td><tr><td>\n"
"		<input\n"
"			type='text'\n"
"			name='keywords'\n"
"			onkeydown='UpdateList(event)'\n"
"			size='50'\n"
"		></input>\n"
"	</td><td>\n"
"		<input\n"
"			type='text'\n"
"			name='selection'\n"
"			size='15'\n"
"		></input>\n"
"	</td></tr>\n"
"</table></p>\n"
"<p><table>\n"
"	<tr><td>\n"
"		Select from list of matching sections below \n"
"	</td><td>\n"
"		Section Tag\n"
"	</td></tr>\n"
"	<tr><td>\n"
"		<textarea\n"
"			name='title_list'\n"
"			rows='20'\n"
"			cols='70'\n"
"			onclick='Choose(this)'\n"
"			ondblclick='Goto()'\n"
"			onkeydown='CheckForReturn(event)'\n"
"		></textarea>\n"
"	</td><td>\n"
"		<textarea\n"
"			name='tag_list'\n"
"			rows='20'\n"
"			cols='20'\n"
"		></textarea>\n"
"	</td></tr>\n"
"</table></p>\n"
"</form>\n"
"<script type='text/javascript' src='_search.htm.js'>\n"
"</script>\n"
;
/*
MaxList  = Maximum number entries to display
Nstring  = number of characters in string
Nkeyword = number topics; i.e., number of keyword list
Row2Tag  = mapping form selection row to tag
*/

static char *Javascript =
"\n"
"var MaxList = 100;\n"
"var Nstring = -1;\n"
"var Nkeyword = Keyword.length;\n"
"var Row2Tag  = [];\n"
"Initialize();\n"
"\n"
"function Initialize()\n"
"{\n"
	// do a search for the empty string
"	UpdateList();\n"
	// set the cursor to the users input field
"	document.search.keywords.focus();\n"
"}\n"
"function UpdateList(event)\n"
"{\n"
	// check for return key
"	key = 0;\n"
"	if( window.event )\n"
		// IE
"		key = window.event.keyCode;\n"
"	else if( event )\n"
		// Firefox
"		key = event.which;\n"
"	if( key == 13 )\n"
"	{	Goto();\n"
"		return;\n"
"	}\n"
	// search string
"	var string  = document.search.keywords.value;\n"

	// No change ?
"	if( Nstring == string.length )\n"
"		return;\n"

	// remember for next time
"	Nstring     = string.length;\n"
"\n"
	// words in search string
"	var word    = string.match(/\\S+/g);\n"

	// number of words in search string
"	var nword   = 0;\n"
"	if(word != null )\n"
"		nword   = word.length;\n"
"\n"
	// map words to patterns
"	var pattern = new Array(nword);\n"
"	for(var j = 0; j < nword; j++)\n"
"		pattern[j] = new RegExp(word[j], 'i');\n"
"\n"
	// list of keyword lines that match
"	var nlist       = 0;\n"
"	var title_list  = '';\n"
"	var tag_list    = '';\n"
"	for(i = 0; (i < Nkeyword) && (nlist < MaxList) ; i++)\n"
"	{\n"
		// does this line match the search string
"		var match = true;\n"
"		for(j = 0; j < nword; j++)\n"
"		{	var flag = pattern[j].test(Keyword[i].tag);\n"
"			flag     = flag || pattern[j].test(Keyword[i].title);\n"
"			flag     = flag || pattern[j].test(Keyword[i].other);\n"
"			match    = match && flag;\n"
"		}\n"
"		if( match )\n"
"		{\n"
			// store first match as choice
"			var tag    = Keyword[i].tag;\n"
"			var title  = Keyword[i].title\n"
"			title      = title.split(/\\s+/);\n"
"			title      = title.join(' ');\n"
"			title_list = title_list + title + '\\n';\n"
"			tag_list   = tag_list + tag + '\\n'\n"
"			Row2Tag[nlist] = tag;\n"
"			nlist = nlist + 1;\n"
"		}\n"
"	}\n"
	// title_list
"	document.search.title_list.value = title_list;\n"
"	document.search.title_list.setAttribute('wrap', 'off');;\n"
"	document.search.title_list.readOnly = true;\n"
	// tag_list
"	document.search.tag_list.value = tag_list;\n"
"	document.search.tag_list.setAttribute('wrap', 'off');;\n"
"	document.search.tag_list.readOnly = true;\n"
"}\n"
"function Choose(textarea)\n"
"{	var start_select = textarea.value.substring(0, textarea.selectionStart);\n"
"	var start_pos    = Math.max(0, start_select.lastIndexOf('\\n') );\n"
"	var length       = textarea.value.length;\n"
"	var end_select   = \n"
"		textarea.value.substring(textarea.selectionEnd, length);\n"
"	var end_pos  = end_select.indexOf('\\n');\n"
"	end_pos      = textarea.selectionEnd + end_pos;\n"
	// highlight the selected line
"	textarea.selectionStart = start_pos;\n"
"	textarea.selectionEnd   = end_pos;\n"
	// get row number this selection corresponds to
"	var row = start_select.split('\\n').length - 1;\n"
"	var tag = Row2Tag[row];\n"
"	document.search.selection.value    = tag.toLowerCase();\n"
"	document.search.selection.readOnly = true;\n"
"	\n"
"	return true;\n"
"}\n"
"function Goto()\n"
"{\n"
"	parent.location = document.search.selection.value + '.htm';\n"
"}\n"
"function CheckForReturn()\n"
"{\n"
"	var key = event.which;\n"
"	if( key == 13 ) Goto();\n"
"}\n"
;

static void MakeKeywordList()
{
	char word[MAX_WORD];
	char *keywords = KeywordLower;
	char  ch       = *keywords++;
	int   n = 0;
	int   ok;
	int   i;
	int   j;

	assert(KeywordLower != NULL);

	KeywordList[n] = '\0';

	if( ch == '\0' )
		return;

	while( ch != '\0' )
	{	i = 0;
		while( ! ( ch == '\0' || isspace((int) ch) ) )
		{	if( i > MAX_WORD - 1 ) fatalomh(
				keywords,
				"\nis to long an index keyword",
				NULL
			);
			word[i++] = tolower((int) ch);
			ch        = *keywords++;
		}
		word[i]          = '\0';

		ok = strstr(KeywordList, word) == NULL;
		if(  TitleLower != NULL )
			ok = ok && strstr(TitleLower, word) == NULL;
		if( TagLower != NULL )
			ok = ok && strstr(TagLower, word)   == NULL;

		if( n + i >= MAX_KEYWORD ) fatalomh(
			"This section keyword list has too many characters",
			NULL
		);

		if( ok )
		{	for(j = 0; j < i; j++)
				KeywordList[n++] = word[j];
		}

		if( isspace((int) ch) )
			KeywordList[n++] = ch;

		while( isspace((int) ch) )
			ch  = *keywords++;

		KeywordList[n] = '\0';
	}
}

/*
------------------------------------------------------------------------------
$begin open_search_file$$
$spell
	tmp
$$

$section Opens File for Web Pages That Searches This Site$$

$head Syntax$$
$codei%OpenSearchFile(%fileTag%, %siteTitle%)%$$

$head Prototype$$
$srcfile%src/search.c%
	0%// BEGIN_OPEN_SEARCH_FILE%// END_OPEN_SEARCH_FILE%1
%$$

$head fileTag$$
The '\0' terminated character vector $icode fileTag$$
specifies the cross reference tag for the search utility.

$head siteTitle$$
The '\0' terminated character string $icode siteTitle$$
specifies the title for the automatically generated web page that
is a search utility for this web site.

$head Output$$
This call opens a new file called $icode%fileTag%.tmp%$$
in which the search information is written.
This will be a Pass One version of the web page that
can be used to search the web site being created.
It needs to be linked up as the proper frame of a page in the system
during Pass Two.
This routine must be called
before any of the other routines listed in $cref search_dev$$.

$end
*/
// BEGIN_OPEN_SEARCH_FILE
void OpenSearchFile(const char *fileTag, const char *siteTitle)
// END_OPEN_SEARCH_FILE
{
	char *frameOne;
	char *str;
	char *next;

	// open the pass one version of the browser search file
	assert( FrameOneName == NULL );
	FrameOneName = strjoin(fileTag, ".tmp");
	DirSep(FrameOneName);
	Fp = fopen(FrameOneName, "w");
	if( Fp == NULL )
		fatalomh("Cannot create a new ", FrameOneName, " file\n", NULL);

	// name of the javascript file
	JavascriptName = StrCat(
		__FILE__,
		__LINE__,
		fileTag,
		Internal2Out("OutputExtension"),
		".js",
		NULL
	);

	/*
	Write out the Browser search pass one file while replacing
	replacing _search.htm.js using the name of the javascript file
	*/

	// search for SiteTitle in frameOne
	frameOne = str_alloc(FrameOne);
	str      = frameOne;
	next     = strstr(str, "SiteTitle");
	assert( next != NULL );
	assert( strlen(next) > 9 );
	*next    = '\0';

	// replace SiteTitle in output
	fprintf(Fp, "%s", str);
	fprintf(Fp, "%s", siteTitle);

	// make sure only one SiteTitle in frameOne
	str = next + 9;
	assert( strstr(str, "SiteTitle") == NULL );

	// search for _search.htm.js in frameOne
	next     = strstr(str, "_search.htm.js");
	assert( next != NULL );
	assert( strlen( next ) > 14 );
	*next    = '\0';

	// replace _search.htm.js in output
	fprintf(Fp, "%s", str);
	fprintf(Fp, "%s", JavascriptName);

	// make sure only one _search.htm.js in frameOne
	str   = next + 14;
	assert( strstr(str, "_search.htm.js") == NULL );

	// output rest of frameOne
	fprintf(Fp, "%s", str);
	fclose(Fp);

	FreeMem(frameOne);

	// open the javascript file
	Fp = fopen(JavascriptName, "w");
	if( Fp == NULL ) fatalomh(
		"Cannot create a new ",
		JavascriptName,
		" file\n",
		NULL
	);

	// write copyright message
	fprintf(Fp,
		"// ------------------------------------------------------------ \n"
		"// Copyright (C) Bradley M. Bell 1998-2015, All rights reserved \n"
		"// ------------------------------------------------------------ \n"
	);
	// the keyword data starts with /^\[$/ and it ends
	// with /^\]$/ so it can be extracted easily with sed
	fprintf(Fp, "Keyword = \n[");

	// initialize section counter
	SectionCount = 0;

	return;
}
/*
-----------------------------------------------------------------------------
$begin search_begin$$
$spell
$$

$section Starts Search Information For Next Section$$

$head Syntax$$
$codei%SearchBegin(%tag%)%$$

$head Prototype$$
$srcfile%src/search.c%
	0%// BEGIN_SEARCH_BEGIN%// END_SEARCH_BEGIN%1
%$$

$head tag$$
This begins a the search information for a new section.
The '\0' terminated character vector $icode tag$$
specifies the cross reference tag for the current section.
It is assumed that $icode%tag%[0]%$$ is not equal to '\0'.
If multiple sequential white spaces characters
occur in $icode tag$$, a fatal error message
is generated and the program is terminated.

$head Tag$$
This is an allocated version of $icode tag$$.

$head TagLower$$
This is an allocated lower case version of $icode tag$$.

$head Keyword$$
This is an allocated empty string.

$head Current Section$$
The current section is defined as the one specified by the
previous call to $cref search_begin$$.
There is no current section after the corresponding call to
$cref search_end$$.

$end
*/
// BEGIN_SEARCH_BEGIN
void SearchBegin(const char *tag)
// END_SEARCH_BEGIN
{
	int   i;
	char ch;
	char last;

	assert( *tag != '\0' );
	assert( ! SectionOpen );
	assert( Tag == NULL );
	assert( TagLower == NULL );
	assert( Title == NULL );
	assert( TitleLower == NULL );
	assert( KeywordLower == NULL );
	SectionOpen = 1;

	Tag          = str_alloc(tag);
	TagLower     = StrLowAlloc(tag);
	KeywordLower = str_alloc(" ");

	// Tag for this line
	i    = 0;
	ch   = *tag++;
	last = '\0';
	while( ch != '\0' )
	{	if( isspace((int) ch) && isspace((int) last) ) fatalomh(
			"The cross reference tag \"",
			tag,
			"\"\n",
			"has multiple sequential white space characters\n",
			NULL
		);
		if( i >= MAX_WORD - 1 ) fatalomh(
			"The cross reference tag \"",
			tag,
			"\"\n",
			"has to many characters in it\n",
			NULL
		);
		last = ch;
		ch   = *tag++;
	}

}
/*
$begin search_title$$
$spell
$$

$section Sets Title For Current Section$$

$head Syntax$$
$codei%SearchTitle(%title%)%$$

$head Prototype$$
$srcfile%src/search.c%
	0%// BEGIN_SEARCH_TITLE%// END_SEARCH_TITLE%1
%$$

$head title$$
The '\0' terminated character vector $icode title$$ specifies the title
for the current section.

$head Title$$
This is an allocated version of $icode title$$.

$head TitleLower$$
This is an allocated lower case version of $icode title$$.

$end
*/
// BEGIN_SEARCH_TITLE
void SearchTitle(const char *title)
// END_SEARCH_TITLE
{
	assert( SectionOpen );
	assert( Title == NULL );
	assert( TitleLower == NULL );

	Title      = str_alloc(title);
	TitleLower = StrLowAlloc(title);
}
/*
-----------------------------------------------------------------------------
$begin search_keywords$$
$spell
$$

$section Sets Keywords For Current Section$$

$head Syntax$$
$codei%SearchKeywords(%keyword%, %escape%, %ignore%)%$$

$head Prototype$$
$srcfile%src/search.c%
	0%// BEGIN_SEARCH_KEYWORDS%// END_SEARCH_KEYWORDS%1
%$$

$head Current Section$$
see $cref/current section/search_begin/Current Section/$$.

$head keyword$$
is a '\0' terminated character vector
containing a list of keywords separated by white space
and commas.

$head escape$$
is the escape character for the list of keywords.
Words that begin with this character will not be included.

$head ignore$$
words that appear in $icode ignore$$, surrounded by spaces,
are not included.

$head KeywordLower$$
A lower case version of the accepted keywords, surrounded by spaces,
is placed here.

$end
*/

// BEGIN_SEARCH_KEYWORDS
void SearchKeywords(
	const char *keyword ,
	const char escape   ,
	const char* ignore  )
// END_SEARCH_KEYWORDS
{	char   ch;

	assert( ! isspace((int) escape) );
	assert( SectionOpen );

	ch    = *keyword++;
	while( ch != '\0' )
	{	int i;
		int ok;
		char word[MAX_WORD];

		// skip leading white space
		while( isspace((int) ch) )
			ch   = *keyword++;

		// get next word in keyword and surround by spaces
		i = 0;
		word[i++] = ' ';
		word[i++] = ch;
		if( ch != '\0' )
			ch = *keyword++;
		while(
			ch != '\0'
			&& ! isspace((int) ch)
			&&  ch != escape
		)
		{	if( i > MAX_WORD - 2 ) fatalomh(
				keyword,
				"\nis to long a keyword\n"
			);
			word[i++] = tolower((int) ch);
			ch        = *keyword++;
		}
		word[i++] = ' ';
		word[i]   = '\0';

		// do not include words that are escaped
		ok  = word[1] != escape;

		// do note include empty words
		if( ok )
		{	i = 0;
			while( word[i] == ' ' )
				i++;
			ok = word[i] != '\0';
		}

		// the comma is a special case
		if(word[1] == escape && word[2] == ',' )
		{	// special ok case
			ok = 1;

			// remove the escape
			StrRemove(word, escape);

			// remove other commas
			assert( word[1] == ',' );
			StrRemove(word + 2, ',' );
		}
		else if(ok)
		{	// remove all commas
			StrRemove(word, ',');
		}

		if( ok )
			ok = strstr(KeywordLower, word) == NULL;
		if( ok )
			ok = strstr(ignore, word) == NULL;

		if( ok )
		{	char *tmp = KeywordLower;

			// KeywordLower always ends in a space
			assert(
				KeywordLower[ strlen(KeywordLower) - 1 ] == ' '
			);

			// hence skip the space at the beginning of word
			assert( word[0] == ' ' );

			// add the word to the keyword list
			KeywordLower = strjoin( KeywordLower, word + 1 );

			FreeMem(tmp);
		}

	}
}

/*
-------------------------------------------------------------------------------
$begin search_get_keywords$$
$spell
	str
	Mem
$$

$section Gets An Allocated Copy of the Keywords$$

$head Syntax$$
$icode%str% = SearchGetKeywords()%$$

$head Prototype$$
$srcfile%src/search.c%
	0%// BEGIN_SEARCH_GET_KEYWORDS%// END_SEARCH_GET_KEYWORDS%1
%$$

$head Current Section$$
see $cref/current section/search_begin/Current Section/$$.

$head str$$
is an allocated '\0' terminate copy of the keywords for the
current section.
The words have been converted to lower case,
duplicate keywords have been removed,
an each keyword is surrounded by a space.
The memory for the return value is allocated with
$cref AllocMem_dev$$ and should be freed with
$cref/FreeMem/AllocMem_dev/FreeMem/$$
when it is no longer needed.

$end
*/
// BEGIN_SEARCH_GET_KEYWORDS
char *SearchGetKeywords()
// END_SEARCH_GET_KEYWORDS
{	int len;
	int i, j, k;
	char *s;

	len = strlen(KeywordLower);
	k   = len;
	for(i = 0; i < len; i++)
	{		if( KeywordLower[i] == '&' )
				k += 8;
	}

	s = AllocMem(k + 1, sizeof(char));

	j = 0;
	for(i = 0; i < len; i++)
	{	if( KeywordLower[i] == '&' )
		{	assert( j + 9 <= k );

			s[j++] = 'a';
			s[j++] = 'm';
			s[j++] = 'p';
			s[j++] = 'e';
			s[j++] = 'r';
			s[j++] = 's';
			s[j++] = 'a';
			s[j++] = 'n';
			s[j++] = 'd';
		}
		else
		{	assert( j <= k );
			s[j++] = KeywordLower[i];
		}

	}
	assert( j == k );
	s[j] = '\0';

	return s;
}

/*
----------------------------------------------------------------------------
$begin search_end$$
$spell
$$

$section Outputs the Search Information for this Section$$

$head Syntax$$
$codei%SearchEnd()%$$

$head Prototype$$
$srcfile%src/search.c%
	0%// BEGIN_SEARCH_END%// END_SEARCH_END%1
%$$

$head Current Section$$
see $cref/current section/search_begin/Current Section/$$.

$head Tag$$
The tag for this section is written to the output file
and both $icode Tag$$ and $icode TagLower$$ are freed.

$head Title$$
The title for this section is written to the output file
and both $icode Title$$ and $icode TitleLower$$ are freed.

$head KeywordLower$$
A lower case version of keywords for this section are written to
the output file. Entire that are equal to the tag, or in the title,
are not included. In addition, duplicates are not included

$head Output Format$$
This information is output as a Javascript object in the following format
and on one line:
$codei%
	{ tag:'%Tag%', title:'%Title%', other:'%other%' }
%$$
If this is not the first such line, a comma $code ,$$ is placed infront
of the left brace $code {$$.

$end
*/
// BEGIN_SEARCH_END
void SearchEnd()
// END_SEARCH_END
{
	assert( SectionOpen );
	SectionOpen = 0;

	// output the search information for this section
	if( SectionCount > 0 )
		fputc(',', Fp);

	assert( Tag != NULL );
	assert( Title != NULL);
	assert( Fp != NULL );

	fprintf(Fp, "\n{ tag: '");
	Output(Tag, "', title:'");
	Output(Title, "', other:'");
	MakeKeywordList();
	Output(KeywordList, "' }");

	FreeMem(Tag);
	FreeMem(TagLower);

	FreeMem(Title);
	FreeMem(TitleLower);

	FreeMem(KeywordLower);

	Tag        = NULL;
	TagLower   = NULL;

	Title      = NULL;
	TitleLower = NULL;

	KeywordLower = NULL;

	++SectionCount;
}
/*
$begin close_search_file$$
$spell
	tmp
	Javascript
$$

$section Close Search Page For the Web Site$$

$head Syntax$$
$codei%CloseSearchFile(%delete%)%$$

$head Prototype$$
$srcfile%src/search.c%
	0%// BEGIN_CLOSE_SEARCH_FILE%// END_CLOSE_SEARCH_FILE%1
%$$

$head Output$$
This operation closes the file
$cref/fileTag/open_search_file/fileTag/$$.
Calls to the other $cref search_dev$$ routines, except
$cref/OpenSearchFile/open_search_file/$$, are invalid after this call.

$head delete$$
If $icode delete$$ is true,
the search file $icode%fileTag%.tmp%$$
is not used and so it is
deleted from the directory (as well as a supporting Javascript file).
Temporary memory that is allocated for these file names
is freed when $code CloseSearchFile$$ is called.

$end
*/

// BEGIN_CLOSE_SEARCH_FILE
void CloseSearchFile(int delete)
// END_CLOSE_SEARCH_FILE
{	char *next;
	char *str;
	char *javascript;

	assert(SectionCount >= 1);
	assert( Fp != NULL );

	// the keyword data starts with /^\[$/ and it ends
	// with /^\]$/ so it can be extracted easily with sed
	fprintf(Fp, "\n]\n");

	// search for .htm in javascript
	javascript = str_alloc(Javascript);
	str        = javascript;
	next       = strstr(str, ".htm");
	assert( next != NULL );
	assert( strlen(next) > 4 );
	*next = '\0';

	// replace .htm in output
	fprintf(Fp, "%s", str);
	fprintf(Fp, "%s", Internal2Out("OutputExtension"));


	// make sure only one .htm in javascript
	str   = next + 4;
	assert( strstr(str, ".htm") == NULL );

	// output rest of javascript
	fprintf(Fp, "%s", str);

	FreeMem(javascript);

	if( Fp != NULL )
		fclose(Fp);

	Fp = NULL;

	if( delete )
	{	unlink(FrameOneName);
		unlink(JavascriptName);
	}
	FreeMem(FrameOneName);
	FreeMem(JavascriptName);

	return;
}
