/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin KeywordIndex$$
$dollar @$$
$spell
	cindex
	tmp
	Href
	preceeded
	OMhelp
	fatalomh
	Mem
$$

$section Keyword and Index Utilities$$

$head Syntax$$
$codei%InsertInIndex(%key%, %tag%, %head%, %escape%)
%$$
$codei%MultipleIntoIndex(%key%, %tag%, %head%, %escape%, %ignore%)
%$$
$codei%CycleIntoIndex(%key%, %tag%, %head%, %escape%)
%$$
$codei%IndexPass1(%section%)
%$$
$codei%IndexFreeMem()%$$



$head Key$$
The '\0' terminated character vector $icode key$$
is the key for the index entry.
It contains the text that will be in alphabetic order in the index.
Key escape characters (see below) are used to convey special meaning
to the routines in this section and will not appear in the
index entries.
Upper case alphabetic letters in $icode key$$ are assumed to be
part of a spelling error.
They are converted to lower case and displayed in Red.

$subhead Key Escape Character$$
We define a key escape character in $icode key$$
as any character
that is equal to the $icode escape$$ character.

$subhead Key Comma$$
We define a key comma character in $icode key$$
as a comma character
that is not directly preceeded by an key escape character.

$subhead Key Space Character$$
We define a key space character in $icode key$$
as any white space character
that is not directly preceeded by an key escape character.

$subhead Key Word$$
We define a key word in $icode key$$
as starting with a non key space character
and continuing to, but not including, the next key space character
or the '\0' at the end of $icode key$$.

$subhead Key Comment$$
We define a key comment in $icode key$$
as a key word that
is directly preceeded by a key escape character.

$head Tag$$
The '\0' terminated character vector $icode tag$$ is the cross reference
tag for this index entry. It specifies the section that the index entry
points to.

$head Head$$
The '\0' terminated character vector $icode head$$ is the
$cref/cross reference heading/glossary/Cross Reference Heading/$$
for this index entry.
It specifies the location with in the section
that the index entry points to.
If $icode head$$ equals NULL or
$icode/head/[0]/$$ equals '\0',
the entry points to the entire section specified by $icode tag$$.

$head Escape$$
This is the current escape character
(it cannot be a white space character.)
The escape character is used for special processing of index entries
and does not appear in the index entries.

$head Section$$
This is a $cref SectionInfo$$ pointer
that specifies the section corresponding to the automatically
generated index page.

$head InsertInIndex$$
$index InsertInIndex$$
this routine will insert one index entry corresponding to
the text in $icode key$$.
The characters in $icode key$$ before the first
$cref/key comma/KeywordIndex/Key.Key Comma/$$
specify the first level of the index entry.
If there is a key comma in $icode key$$
the text after the first key comma specifies
the second level of the index entry.

$head MultipleIntoIndex$$
$index MultipleIntoIndex$$
This routine will insert a one level index entry for each
$cref/key word/KeywordIndex/Key.Key Word/$$
that is not a
$cref/key comment/KeywordIndex/Key.Key Comment/$$.
(For this function,
the comma does not have the special meaning it has in $code InsertInIndex$$.)
Words that appear in $icode ignore$$ will not be included in the index.

$head CycleIntoIndex$$
$index CycleIntoIndex$$
This routine will insert a two level index entry for each
$cref/key word/KeywordIndex/Key.Key Word/$$
that is not a
$cref/key comment/KeywordIndex/Key.Key Comment/$$.
The first level of the index entry will be the key word.
The second level will be the entire $icode key$$.
$pre

$$
If a comma character appears in $icode key$$ and it not
is preceded by the
$cref/key escape/KeywordIndex/Key.Key Escape Character/$$ character,
an error message for the $code cindex$$ command is generated.


$head IndexPass1$$
$index IndexPass1$$
this routine creates the pass one version of the
index page in the file with root name $icode/section/->tag/$$
and extension $code .tmp$$.
It is a Pass1 version because
the cross references use the HrefOutputPass1 format.
In addition, for the $icode letter$$
between $code A$$ and $code Z$$ that has index entries
starting with that letter:
there a heading for that letter together with a
$codei%
	<a name="%letter%"></a>
%$$
reference that points to the position of that letter in the index.
In addition, it is added to the list of cross references to this section.

$head IndexFreeMem$$
The routines listed above allocate memory using $cref AllocMem$$.
The routine $code IndexFreeMem$$ must be called
after the last call to any of the routines above,
and before calling
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$.


$head Errors$$
All the routines documented above use
$cref/fatalomh/fatalerr/$$ to report error messages; i.e.,
they assume that there is an open input file and
that we are currently parsing OMhelp input.

$end
*/

# include "index.h"

# include <ctype.h>
# include <string.h>
# include <assert.h>

# include "cross.h"
# include "allocmem.h"
# include "strjoin.h"
# include "str_alloc.h"
# include "output.h"
# include "convert.h"
# include "href.h"
# include "fatalerr.h"
# include "Tag2Title.h"
# include "section.h"
# include "main.h"
# include "StrRemove.h"
# include "Internal2Out.h"
# include "ClipWhiteSpace.h"

# define TAB_SIZE  5
# define MAX_WORD  100


// current index entries
typedef struct indexEntry {
	char              escape;
	struct indexEntry  *next;
	char              *major;
	char              *minor;
	char                *tag;
	char               *head;
} IndexEntry;
IndexEntry *Index = NULL;

static int IndexOrder(const char *s1, const char *s2)
{	int  i     = 0;
	int  done  = 0;
	int  diff;
	char c1;
	char c2;

	while( ! done )
	{	c1   = s1[i];
		c2   = s2[i];
		done = (c1 == '\0') | (c2 == '\0');
		++i;

		diff = tolower((int) c1) - tolower((int) c2);
		if( diff != 0 )
			return diff;
		diff = c1 - c2;
		if( diff != 0 )
			return diff;
	}
	return 0;
}


static int KeyCompare(IndexEntry *E, IndexEntry *F)
{	int major;
	int minor;

	major = IndexOrder(E->major, F->major);
	minor = IndexOrder(E->minor, F->minor);

	if( major != 0 )
		return major;

	return minor;
}


static int Space(char current, char previous, char escape)
{	return isspace((int) current) && (previous != escape);
}

static void OutPre(const char *s)
{	int preformatted = 1;

	while( *s != '\0' )
		ConvertOutputCh(*s++, preformatted);
}

static void OutKey(char *s)
{	int preformatted = 1;
	int bold         = 0;
	int flag;
	char ch;


	ch = *s++;
	while( ch != '\0' )
	{
		// determine if switching to or from bold
		flag  = isalpha((int) ch);
		flag |= isdigit((int) ch);
		flag |= ch == ',';
		flag  = ! flag;

		if( flag && ! bold )
			OutputString("<b>");

		if( ! flag && bold )
			OutputString("</b>");

		bold = flag;

		if( isspace((int) ch) )
			ConvertOutputCh(' ', preformatted);
		else	ConvertOutputCh(ch, preformatted);

		ch = *s++;
	}
	if( bold )
		OutputString("</b>");
}

void InsertInIndex(
	const char *key,
	const char *tag,
	const char *head,
	const char escape
)
{	char *s;
	char ch;

	IndexEntry *E, *L, *N;

	// put new entry at front of index
	E         = (IndexEntry *) AllocMem(1, sizeof (IndexEntry));
	E->next   = Index;
	E->major  = str_alloc(key);
	E->tag    = str_alloc(tag);
	if( head != NULL )
		E->head   = str_alloc(head);
	else	E->head   = str_alloc("");

	ClipWhiteSpace(E->major);

	// check for a comma with out an escape
	ch = '\0';
	s  = E->major;
	while( *s != '\0' && (*s != ',' || ch == escape) )
		ch = *s++;

	// if there, it is the beginning of the minor key
	// note no allocation for E->minor in either case
	if( *s == ',' )
	{	// beginning of minor key
		E->minor = s + 1;

		// skip leading white space
		while( isspace((int) *(E->minor) ) )
			++(E->minor);

		// end of major key
		*s = '\0';
		--s;

		// skip trailing white space
		while( s > E->major && isspace((int) *s ) )
		{	*s = '\0';
			--s;
		}
	}
	else
	{	assert( *s == '\0' );
		E->minor = s;
	}

	// remove escape characters from major and minor keys
	StrRemove(E->major, escape);
	StrRemove(E->minor, escape);

	// move E to proper place in index
	if( Index == NULL )
		Index = E;
	else if( KeyCompare(E, Index) < 0 )
		Index   = E;
	else
	{	L  = Index;
		N  = L->next;
		while( N != NULL && KeyCompare(E, N) > 0 )
		{	L = N;
			N = N->next;
		}
		L->next = E;
		E->next = N;
	}
	return;
}

// insert each key word in key
void MultipleIntoIndex(
	const char *key,
	const char *tag,
	const char *head,
	const char escape,
	const char *ignore
)
{	char keyword[MAX_WORD];
	char ch;

	assert( ! isspace((int) escape) );

	// skip leading white space
	while( isspace((int) *key) )
		key++;

	ch = '\0';
	while( *key != '\0' )
	{	if( *key == escape )
		{	while( *key != '\0' && ! Space(*key, ch, escape) )
			{	ch = *key;
				key++;
			}
		}
		else
		{	int   i;

			assert( ! isspace((int) *key ) );

			i = 0;
			keyword[i++] = ch = *key++;
			while( *key != '\0' && ! Space(*key, ch, escape) )
			{	if( i+1 < MAX_WORD )
					keyword[i++] = *key;
				ch = *key++;
			}
			keyword[i] = '\0';

			if( strstr(ignore, keyword) == NULL )
			{
				InsertInIndex(
					keyword,
					tag,
					head,
					escape
				);
			}
		}

		// skip leading white space
		while( isspace((int) *key) )
			key++;
	}

	return;
}

// insert each circularly shifted verison of key
void CycleIntoIndex(
	const char *key,
	const char *tag,
	const char *head,
	const char escape
)
{	char  *entry;
	char      ch;
	int        i;
	int    comma;
	int      len;

	assert( ! isspace((int) escape) );

	// skip spaces at the beginning of key
	while( isspace((int) *key) )
		++key;

	// length ot key
	len   = strlen(key);

	// space for twice as many characters as in key plus one.
	entry = StrCat(__FILE__, __LINE__, key, ",", key, NULL);
	assert( strlen(entry) == ( (unsigned) 2 * len + 1 ));

	// check for a comma that is not preceded by an escape
	for(i = 0; i < len; i++)
	{
		if( i == 0 )
			comma = key[i] == ',';
		else	comma = key[i] == ',' && key[i-1] != escape;

		if( comma ) fatalomh(
			"The text for a $cindex command contains a comma\n",
			"that is not preceeded by the escape character",
			NULL
		);
	}

	i     = 0;
	ch    = '\0';
	while( key[i] != '\0' )
	{	int j, k;

		// skip spaces infront of next word
		while( key[i] != '\0' &&  Space(key[i], ch, escape) )
		{	ch = key[i];
			++i;
		}
		assert( ! isspace((int) key[i] ) );

		// insert this entry
		if( key[i] != '\0' && key[i] != escape )
		{
			// copy word starting at index i into major key
			j = 0;
			entry[j++] = ch = key[i++];
			while(key[i] != '\0' && ! Space(key[i], ch, escape))
				entry[j++] = ch = key[i++];

			// separate major from minor key
			entry[j++] = ',';

			// copy entire key as minor key
			for(k = 0; k < len; k++)
				entry[j++] = key[k];
			entry[j] = '\0';

			// check length assumption
			assert( j <= 2 * len + 1 );

			InsertInIndex(
				entry,
				tag,
				head,
				escape
			);
		}

		// skip escaped words
		while(key[i] != '\0' && ! Space(key[i], ch, escape))
			ch = key[i++];
	}

	FreeMem(entry);
	return;
}
void IndexPass1(SectionInfo *section)
{
	char *filename;
	char *major;
	char *minor;
	char *tag;
	char *head;
	const char *title;
	int letter;
	char ch;

	char letterHead[2];

	IndexEntry *Previous;
	IndexEntry *Current;


	// open output file
	filename = strjoin(section->tag, ".tmp");
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

	// initialize
	letter         = 0;
	letterHead[1]  = '\0';

	Previous = NULL;
	Current  = Index;
	while( Current != NULL )
	{
		major   = Current->major;
		minor   = Current->minor;
		tag     = Current->tag;
		head    = Current->head;
		title   = Tag2Title(tag);

		assert(title != NULL);

		// check for next letter in alphabet
		ch = tolower((int) Current->major[0]);
		while(ch > 'a' + letter && letter < 26)
			letter++;
		if( ch == 'a' + letter && letter < 26 )
		{
			letterHead[0] = 'A' + letter;
			FormatOutput("\n<b><big><a name=\"%s\">", letterHead);
			FormatOutput("%s</a></big></b>\n", letterHead);
			ConvertForcedNewline(1);
			DefineCrossReference(
				section->tag, letterHead, "", 1, letterHead);
			letter++;
		}


		if( Previous == NULL ||
		    IndexOrder(Previous->major, major) != 0 )
		{	// new major part of key
			OutKey(major);

			if( minor[0] != '\0' )
			{	OutputString("<br");
				OutputString(Internal2Out("SelfTerminateCmd"));
				OutputString("\n");
			}
		}
		else if( minor[0] == '\0' )
		{	// same as previous major part of key
			int len;
			int i;
			len = strlen(major);
			// 160 is code for non-breaking space
			for(i = 0; i < len; i++)
				OutputString("&#160;");
		}

		// output the minor part of the key
		if( minor[0] != '\0' )
		{	int i;

			// indentation for minor keys
			for(i = 0; i < TAB_SIZE; i++)
				OutputString("&#160;");

			// output the minor key
			OutKey(minor);
		}


		// space
		OutputString("&#160;");

		// destination for this index entry
		if( head[0] == '\0' )
			HrefOutputPass1(tag, head, "false", "", "true");
		else	HrefOutputPass1(tag, head, "false", "1", "true");

		// title for this destination
		OutPre(title);
		if( strlen(head) > 0 )
		{	OutputString(":&#160;");
			OutPre(head);
		}

		// end of this index entry
		HrefEnd("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");

		Previous = Current;
		Current  = Current->next;
	}

	PopOutput();
}

void IndexFreeMem()
{
	IndexEntry *Next = Index;

	while( Next != NULL )
	{	Index = Next;
		Next  = Index->next;

		FreeMem(Index->major);
		FreeMem(Index->tag);
		FreeMem(Index->head);
		FreeMem(Index);
	}
	return;
}
