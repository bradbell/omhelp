/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2010 Bradley M. Bell

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
$begin search$$
$spell
	Javascript
	tmp
	omhelp
	OMhelp
	fatalomh
	Mem
$$

$section Routines That Create Search Page For a Web Site$$

$mindex search page keyword$$
$mindex 
	OpenSearchFile
	SearchBegin
	SearchTitle
	SearchKeywords
	SearchGetKeywords
	SearchEnd
	CloseSearchFile
$$

$table
$bold Syntax$$
$cend $syntax%OpenSearchFile(%fileTag%, %siteTitle%)%$$  $rend
$cend $syntax%SearchBegin(%tag%)%$$               $rend
$cend $syntax%SearchTitle(%title%)%$$             $rend
$cend $syntax%SearchKeywords(%list%, %escape%, %ignore%)%$$ $rend
$cend $syntax%SearchGetKeywords()%$$              $rend
$cend $syntax%SearchEnd()%$$                      $rend        
$cend $syntax%CloseSearchFile(%delete%)%$$        
$tend

$fend 25$$

$head Description$$
These routines create a Pass One version of the
web page that searches the web site being created.
It is a Pass One version because it is written
to a file with extension $code .tmp%$$ and does not have any 
Pass One escape sequences; i.e., no matches for
$code MatchText$$ in $code omhelp.y$$.
$syntax%

OpenSearchFile(%fileTag%, %siteTitle%)%
%$$
The '\0' terminated character vector $italic fileTag$$
specifies the cross reference tag for the search utility.
The '\0' terminated character string $italic siteTitle$$
specifies the title for the automatically generated web page that 
is a search utility for this web site.
This call opens a new file called 
$syntax%%fileTag%.tmp%$$ 
in which the search information is written.
This will be a  Pass One version of the web page that
can be used to search the web site being created.
It needs to be linked up as the proper frame of a page in the system
during Pass Two.
The $code OpenSearchFile$$ routine must be called
before any of the other routines documented below.
$syntax%

SearchBegin(%tag%)%
%$$
This begins a the search information for a new section.
The '\0' terminated character vector $italic tag$$
specifies the cross reference tag for the current section.
(It is assumed that $syntax%%tag%[0]%$$ is not equal to '\0'.)
The title and keywords that come between a call to $code SearchBegin$$
and the following call to $code SearchEnd$$
are linked by the search utility
to the web page $syntax%%tag%.%ext%$$
(where $italic ext$$ is the output file extension specified by
$xref/Internal2Out/$$).
If multiple sequential white spaces characters
occur in $italic tag$$, a fatal error message 
is generated and the program is terminated. 
$pre

$$
$syntax%

SearchTitle(%title%)%
%$$
The '\0' terminated character vector $italic title$$ specifies the title
for the current section.  
The current section is defined as the one specified by the
previous call to $code SearchBegin$$.
It is assumed that the corresponding call to $code SearchEnd$$
has not yet occurred.
It is also assumed that there is one and only one call to 
$code SearchTitle$$ between each call to $code SectionBegin$$
and the next call to $code SectionEnd$$.
$syntax%

SearchKeywords(%list%, %escape%, %ignore%)%
%$$
Adds the keywords in $italic list$$ to the 
set of keywords for the current section
where $italic list$$ is a '\0' terminated character vector.
$pre

$$
The current section is defined as the one specified by the
previous call to $code SearchBegin$$.
It is assumed that the corresponding call to $code SearchEnd$$
has not yet occurred.
$pre

$$
A keyword is any sequence of characters (in $italic list$$) not including
white space or commas. 
Keywords beginning with the character $italic escape$$
are not included. 
Commas are treated as white space
except for those commas that are preceded by the $italic escape$$
character.
Words that appear in $icode ignore$$, surrounded by spaces, are not included
in the search keywords.
$syntax%

SearchGetKeywords()
%$$
returns a '\0' terminate copy of the keywords for the 
current section.
The words have been converted to lower case,
duplicate keywords have been removed,
an each keyword is surrounded by a space.
The memory for the return value is allocated with
$xref/AllocMem/$$ and should be freed with $xref/AllocMem/FreeMem/FreeMem/$$
when it is no longer needed.
$syntax%

SearchEnd()
%$$
This completes the current section specified by
the previous call to $code SearchBegin$$.
(Temporary memory that is allocated for this section by $code SearchTitle$$
and $code SearchKeywords$$ is freed by this call.)
$syntax%

CloseSearchFile(%delete%)
%$$
Closes the $syntax%%fileTag%.tmp%$$ file.
Calls to the other routines documented above are invalid
after this call.
If $italic delete$$ is true,
it is assumed that the search file
$syntax%%fileTag%.tmp%$$ 
is not used and so it is
deleted from the directory (as well as a supporting Javascript file).
(Temporary memory that is allocated for these file names
is freed when $code CloseSearchFile$$ is called.)

$head Errors$$
All the routines documented above use 
$xref/fatalerr//fatalomh/$$ to report error messages; i.e.,
they assume that there is an open input file and
that we are currently parsing OMhelp input.

$end
*/

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
"<tr><td>\n"
"	1: Enter keywords separated by spaces\n"
"	</td><td>\n"
"	3: <input\n"
"	type='button'\n"
"	value='Goto'\n"
"	onclick='Goto()'\n"
"	/>\n"
"	section\n"
"</td><tr><td>\n"
"	<input\n"
"	type='text'\n"
"	name='keywords'\n"
"	onkeydown='UpdateList(event)'\n"
"	size='50'\n"
"	/></td>\n"
"	</td><td>\n"
"	<input\n"
"	type='text'\n"
"	name='choice'\n"
"	size='20'\n"
"	/>\n"
"</td></tr>\n"
"</table></p>\n"
"<p><table>\n"
"<tr><td>2: Select from following list of keyword matches</td></tr>\n"
"<tr><td><textarea\n"
"	name='list'\n"
"	rows='20'\n"
"	cols='80'\n"
"	onclick='Choose(this)'"
"	></textarea></td></tr>\n"
"</table></p>\n"
"</form>\n"
"<script type='text/javascript' src='_search.htm.js'>\n"
"</script>\n"
;
/*
MaxList  = Maximum number entries to display
Nstring  = number of characters in string
Nkeyword = number topics; i.e., number of keyword list
*/

static char *Javascript =
"\n"
"var MaxList = 100;\n"
"var Nstring = -1;\n"
"var Nkeyword = Keyword.length / 2;\n"
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
"	var nlist = 0;\n"
"	var list  = '';\n"
"	for(i = 0; (i < Nkeyword) && (nlist < MaxList) ; i++)\n"
"	{\n"
		// does this line match the search string
"		var match = true;\n"
"		for(j = 0; j < nword; j++)\n"
"		{	var flag = pattern[j].test(Keyword[2*i]);\n"
"			flag     = flag || pattern[j].test(Keyword[2*i+1]);\n"
"			match    = match && flag;\n"
"		}\n"
"\n"
"		if( match )\n"
"		{\n"
			// store first match as choice
"			line  = Keyword[2*i].split(/\\s+/);\n"
"			line  = line.join(' ');\n"
"			list  = list + line + '\\n';\n"
"			nlist = nlist + 1;\n"
"		}\n"
"	}\n"
"	document.search.list.value    = list;\n"
"}\n"
"function Choose(textarea)\n"
"{	var start_select = textarea.value.substring(0, textarea.selectionStart);\n"
"	var start_pos    = Math.max(0, start_select.lastIndexOf('\\n') );\n"
"	var length       = textarea.value.length;\n"
"	var end_select   = \n"
"		textarea.value.substring(textarea.selectionEnd, length);\n"
"	var end_pos      = end_select.indexOf('\\n');\n"
"	if( end_pos >= 0 ) \n"
"	{	end_pos = textarea.selectionEnd + end_pos;\n"
"	} else \n"
"	{	end_pos = length;\n"
"	}\n"
"	// highlight the selected line\n"
"	textarea.selectionStart = start_pos;\n"
"	textarea.selectionEnd   = end_pos;\n"
"	// get the choice from the beginning of the line\n"
"	var line = textarea.value.substring(start_pos, length);\n"
"	var end_choice = line.indexOf(' ');\n"
"	if( end_choice >= 0 )\n"
"	{	var choice = line.substring(0, end_choice);\n"
"		document.search.choice.value = choice.toLowerCase();\n"
"	}\n"
"	\n"
"	return true;\n"
"}\n"
"function Goto()\n"
"{\n"
"parent.location = document.search.choice.value + '.htm';\n"
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


void OpenSearchFile(const char *fileTag, const char *siteTitle)
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
		"// ------------------------------------------------------- \n"
		"// Copyright (C) Bradley M. Bell 2003, All rights reserved \n" 
		"// ------------------------------------------------------- \n"
	);
	// the keyword data starts with /^\[$/ and it ends 
	// with /^\]$/ so it can be extracted easily with sed
	fprintf(Fp, "Keyword = \n[");

	// initialize section counter
	SectionCount = 0;

	return;
}

void SearchBegin(const char *tag)
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

void SearchTitle(const char *title)
{	
	assert( SectionOpen );
	assert( Title == NULL );
	assert( TitleLower == NULL );

	Title      = str_alloc(title);
	TitleLower = StrLowAlloc(title);
}

void SearchKeywords(
	const char *keyword , 
	const char escape   ,
	const char* ignore  )
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

char *SearchGetKeywords()
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

void SearchEnd()
{
	assert( SectionOpen );
	SectionOpen = 0;

	// output the search information for this section
	if( SectionCount > 0 )
		fputc(',', Fp);

	assert( Tag != NULL );
	assert( Title != NULL);
	assert( Fp != NULL );

	fprintf(Fp, "\n'");
	Output(Tag, "  ");
	Output(Title, "  ','");
	MakeKeywordList();
	Output(KeywordList, " '");

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

void CloseSearchFile(int delete)
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
