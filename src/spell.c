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

$begin spell$$
$spell 
	non 
	wrd 
	Init 
	dir 
	Ok
	const
$$

$section Spell Checking Routines$$
$index spell$$
$index check, spell$$
$index error, spell$$
$index SpellingOkList$$
$index InitSpelling$$
$index SpellingError$$
$index FreeSpelling$$

$table
$bold Syntax$$ 
$cend $syntax%void InitSpelling(const char *%dir%)%$$        $rend
$cend $syntax%void SpellingOkList(const char *%special%)%$$  $rend
$cend $syntax%const char *SpellingError(const char *%text%, int *%nOut%)%$$ $rend
$cend $syntax%void FreeSpelling(int %debug%)%$$ 
$tend

$fend 25$$

$head Description$$
Routines that do spell checking and manage the 
current list of special words.


$syntax/

InitSpelling(/dir/)
/$$
The '\0' terminated character vector $italic dir$$ specifies the directory
where the spelling files are installed.
The last character in $italic dir$$ must be a $code \$$ or $code /$$.
If the file $code dictionary.bin$$ exists in the directory
$italic dir$$, it is
used for a fast initialization. Otherwise, the file $code english.wrd$$
(and the optional file $code local.wrd$$) are
used and a message ending in '\n' is printed on standard out
telling the user that initialization will take longer.
The list of special word (see $code SpellingOkList$$ below) is initialized
as empty.

$syntax/

SpellingOkList(/list/)
/$$
The '\0' terminated character vector $italic list$$
contains a list of special words that are considered properly spelled even
if they are not in the dictionary mentioned above.
Each word in this context must be separated by a non alphabetic character
or the capital letter that begins the next word.
Spell checking is not case sensitive.
If $syntax//list/[0]/$$ is '\0',
the list of special words is initialized to empty.
Otherwise, the words in $italic list$$ are added to the current
list of special words.
$syntax/

SpellingError(/text/, /nOut/)
/$$
The '\0' terminated character vector $italic text$$ contains text that
is checked for words that are not correctly spelled.
A word in this context is an Upper or lower case letter
followed by a sequence of lower case letters.
If there is no spelling error in $italic text$$, the return value is
$code NULL$$.
Otherwise the return value is a pointer to the beginning of the first
spelling error in $italic text$$. 
The error extends from this pointer, 
for $italic nOut$$ characters.
The spelling error is added to the list of OK words for this
section so that the error is only reported once.
$syntax/


FreeSpelling(debug)
/$$
Frees all memory that is connected to spell checking
This memory is allocated using $mref/AllocMem/$$
and should be freed before calling 
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$.

If debug is true, a list of all reported spelling errors is written
in alphabetical order and lower case to a file called error.wrd.
$end
*/

# include <stdio.h>
# include <string.h>
# include <ctype.h>
#ifdef WIN32
# include <io.h>
#endif
# include <assert.h>
# include <stdlib.h>

# include "trace_exit.h"
# include "allocmem.h"
# include "strjoin.h"
# include "fatalerr.h"
# include "DirSep.h"

# include "spell.h"

# define MAX_WORD  200

/*-------------- static data ------------------------------------*/

// current list of special words
static char *Special = NULL;

static int  Nword;         // total number words to check
static int  Mword;         // amount of space allocated
static int *Word  = NULL;  // the allocated space

static int Nmemory;       // number of characters in the words
static int Mmemory;       // number of characters allocated
static char *Memory = NULL;        // the allocated space

typedef struct spellError {
	char *word;
	struct spellError *next;
} SpellError;
static SpellError *ErrorList = NULL;

	

/*------------ static functions -----------------------------*/

static int BinarySearch(char *w, int low, int up)
{	
	int   mid;
	int   diff;

	// upper limit of search
	diff = strcmp(w, Memory + Word[up]);
	if( diff > 0 )
		return -1;
	if( diff == 0 )
		return up;

	// lower limit of search
	diff = strcmp(Memory + Word[low], w);
	if( diff > 0 )
		return -1;
	if( diff == 0 )
		return low;


	// bianry search 
	while( up > low + 1 )
	{	mid = low + (up - low) / 2;

		diff = strcmp(w, Memory + Word[mid]);
		if( diff > 0 )
			low = mid;
		else if( diff == 0 )
			return mid;
		else	up = mid;
	}
	return -1;
}

static int find(char *word)
{	
	int up;
	int low;
	int index;

	// search dictionary
	low = 0;
	up  = Nword - 1;
	index = BinarySearch(word, low, up);
	return index;
}

static void getWord(
	char word[MAX_WORD], 
	FILE *fp, 
	int *ch, 
	int *line, 
	char *file
)
{	int i;

	// skip leading spaces
	while( isspace((int) *ch) )
	{	if( *ch == '\n' )
			(*line)++;
		*ch = getc(fp);
	}

	// check for end of file
	if( *ch == EOF )
	{	word[0] = 127;
		word[1] = '\0';
		return;
	}

	// copy word into buffer
	for(i = 0; ! isspace((int) *ch) && i < MAX_WORD - 1; i++)
	{	if( *ch >= 127 ) 
		{	char number[100];
			sprintf(number, "%d", *line);
			fatalerr(
			"An ascii code >= 127 appears at line ",
			number,
			"\nin file ",
			file,
			NULL
			);
		}
		
		word[i]  = (char) tolower((int) *ch);
		*ch       = getc(fp);
	}
	word[i] = '\0';

	// check length of word
	if( i == MAX_WORD - 1) fatalerr(
	"Either english.wrd or local.wrd contains\n",
	word,
	"\nwhich is to long of a word",
	NULL
	);
}

/*------------------------------------------------------------------*/

void InitSpelling(const char *dir)
{
	FILE           *fpDic,             *fpEng,           *fpLoc;
	char         *fileDic,           *fileEng,         *fileLoc;
	char  wrdDic[MAX_WORD],  wrdEng[MAX_WORD], wrdLoc[MAX_WORD];
	int  chEng,   chLoc;
	int  lineEng, lineLoc;

	int  ok;
	int  n;
	int  binaryDictionary;

	n      = strlen(dir);
	assert( n > 0 );
	assert( dir[n-1] == '\\' || dir[n-1] == '/' );

	fileDic          = strjoin(dir, "dictionary.bin");
	DirSep(fileDic);

	fpDic            = fopen(fileDic, "rb");
	binaryDictionary = fpDic != NULL;
	if( binaryDictionary )
	{	// read the binary form of the dictionary
		ok = 1;
	    	ok = ok && fread(&Nword, sizeof(int), 1, fpDic) == 1;
		ok = ok && fread(&Nmemory, sizeof(int), 1, fpDic) == 1;

		Word  = AllocMem(Nword, sizeof(int));
		n     = fread(Word, sizeof(int), Nword, fpDic);
		ok    = ok && n == Nword;
		Mword = Nword;

		Memory  = AllocMem(Nmemory, sizeof(char));
		n       = fread(Memory, sizeof(char), Nmemory, fpDic);
		ok      = ok && n == Nmemory;
		Mmemory = Nmemory;

		if( ! ok ) fatalerr(
			fileDic,
			" has an error in it\n",
			"You can recreate it by deleting it and providing\n",
			"the files english.wrd and local.wrd",
			NULL
		);

		FreeMem(fileDic);
		fclose(fpDic);
		return;
	}
    	printf("%s does not exist, wait while it is created\n",
    		fileDic);
	FreeMem(fileDic);

	// open ascii word list files
	fileEng = strjoin(dir, "english.wrd");
	DirSep(fileEng);

	fpEng   = fopen(fileEng, "r");
	if( fpEng == NULL )
	{	printf("Cannot open the file %s\n", fileEng);
		printf("Check windows INI file and\n");
		printf("the environment variable omhelp_dir\n");
		printf("which are described in running.htm\n");
		trace_exit(1);
	}
	fileLoc   = strjoin(dir, "local.wrd");
	DirSep(fileLoc);

	fpLoc     = fopen(fileLoc, "r");

	// initialize memory allocation
	Mmemory = 8;
	Mword   = 4;
	Memory  = (char *) AllocMem(Mmemory, sizeof(char));
	Word    = (int *) AllocMem(Mword, sizeof(int));
	Nword   = 0;
	Nmemory = 0;

	// first character from each file
	chEng = getc(fpEng);
	if( fpLoc != NULL )
		chLoc = getc(fpLoc);
	else	chLoc = EOF;
	if( chEng == EOF ) fatalerr(
		"No words in the file ",
		fileEng,
		NULL
	);

	// get first word from each file
	lineEng = 1;
	lineLoc = 1;
	getWord(wrdEng, fpEng, &chEng, &lineEng, fileEng);
	getWord(wrdLoc, fpLoc, &chLoc, &lineLoc, fileLoc);
	while(chEng != EOF || chLoc != EOF)
	{	// get the smaller of the two words
		if( strcmp(wrdEng, wrdLoc) < 0 )
		{	strcpy(wrdDic, wrdEng);
			getWord(wrdEng, fpEng, &chEng, &lineEng, fileEng);
		}
		else
		{	strcpy(wrdDic, wrdLoc);
			getWord(wrdLoc, fpLoc, &chLoc, &lineLoc, fileLoc);
		}

		// check if need more word memory
		if( Nword == Mword )
		{	int *tmp;
			int i;

			Mword = 2 * Mword;
			tmp = (int *) AllocMem(Mword, sizeof(int));
			for(i = 0; i < Nword; i++)
				tmp[i] = Word[i];

			FreeMem(Word);
			Word = tmp;
		}

		// check if need more character memory
		if( Nmemory > Mmemory - MAX_WORD )
		{	char *tmp;
			int i;

			Mmemory = 2 * Mmemory;
			tmp = (char *) AllocMem(Mmemory, sizeof(char));
			for(i = 0; i < Nmemory; i++)
				tmp[i] = Memory[i];

			FreeMem(Memory);
			Memory = tmp;
		}

		// start of this word
		Word[Nword++] = Nmemory;

		// copy the word to character memory
		strcpy(Memory + Nmemory, wrdDic);

		// advance memory pointer past terminating '\0'
		Nmemory = Nmemory + strlen(wrdDic) + 1;

		// check order of input values
		if( Nword > 1 )
		{	int diff;
			int w1;
			int w2;
			w1 = Word[Nword - 1];
			w2 = Word[Nword - 2];
			diff = strcmp(Memory + w1, Memory + w2);
			if( diff < 0 )
			{	char numberEng[100];
				char numberLoc[100];

				sprintf(numberEng, "%d", lineEng);
				sprintf(numberLoc, "%d", lineLoc);

				 fatalerr(
				"The word \"",
				Memory + w2,
				"\" or \"",
				Memory + w1,
				"\"\nis not in alphabetical order.\n",
				"Detected at line ",
				 numberEng,
				" of file ",
				fileEng,
				"\nand line ",
				numberLoc,
				" of file ",
				fileLoc,
				NULL
				);
			}

		}
	}
	/*
	create a new binary dictionary
	*/

	fileDic = strjoin(dir, "dictionary.bin");
	DirSep(fileDic);

	fpDic   = fopen(fileDic, "wb");
	if( fpDic == NULL ) fatalerr(
		"cannot create the file ",
		fileDic,
		NULL
	);

	ok = 1;
	ok = ok && fwrite(&Nword, sizeof(int), 1, fpDic) == 1;
	ok = ok && fwrite(&Nmemory, sizeof(int), 1, fpDic) == 1;
	ok = ok && fwrite(Word, sizeof(int), Nword, fpDic) == (unsigned) Nword;
	ok = ok && fwrite(Memory, sizeof(char), Nmemory, fpDic) == (unsigned) Nmemory;

	if( ! ok ) fatalerr(
		"Error writing the file ",
		fileDic,
		NULL
	);

	// free allocated memory to enable checking for leaks
	FreeMem(fileDic);
	FreeMem(fileEng);
	FreeMem(fileLoc);
	fclose(fpDic);
	fclose(fpEng);
	if( fpLoc != NULL ) fclose(fpLoc);

	return;
}

const char *SpellingError(const char *text, int *nOut)
{
	const char *startWord;
	const char *lastWord;

	char lowcase[MAX_WORD];
	char lowlast[MAX_WORD];

	SpellError *previous, *current, *next;
	int  i;
	int  found;
	int  len;


	assert(Memory != NULL);

	// advance to beginning of first word
	while( *text != '\0' && ! isalpha((int) *text) )
		text++;

	// initialize previous word as empty
	lowlast[0] = '\0';
	startWord  = NULL;

	while( *text != '\0' )
	{
		// copy the word and also make a lower case copy
		// surrounded by spaces
		lastWord    = startWord;
		startWord   = text;
		lowcase[0]  = ' ';
		lowcase[1]  = tolower((int) *text);
		i           = 1;
		text        = text + 1;
		while( *text != '\0' && islower((int) *text) )
		{	if( i > MAX_WORD/2 - 4 )
			{	*nOut = i - 1;
				return startWord;
			}
			lowcase[i + 1]  = tolower((int) *text);
			i++;
			text++;
		}
		// terminate word
		lowcase[i + 1] = ' ';
		lowcase[i + 2] = '\0';
		len            = i + 2;

		// check the special word list where words are
		// surrounded by spaces
		if( i == 0 )
			found = 1;
		else if( Special != NULL )
			found = strstr(Special, lowcase) != NULL;
		else	found = 0;

		// check for this word the same as the last word
		// but ignore single letter words
		if( strcmp(lowcase, lowlast) == 0 && len > 3 )
		{	
			assert( len + len - 1 < MAX_WORD );

			// the double word starts here
			startWord = lastWord;

			// change lowcase to two copies of lowcase
			// with only one space between copies
			for(i = 0; i < len - 1; i++)
				lowcase[len + i] = lowcase[i + 1];
			lowcase[len + len - 1] = '\0';
			len = len + len - 1;

			// see if double word is in list
			if( Special != NULL )
				found = strstr(Special, lowcase) != NULL;
			else	found = 0;

		}
		else
		{	// copy into previous word
			strcpy(lowlast, lowcase);

		}

		if( ! found )
		{
			// remove trailing space
			lowcase[len - 1] = '\0';
			--len;

			// find the word in the dictionary
			// without leading and trailing spaces
			found = find(lowcase + 1) >= 0;
		}
		if( ! found )
		{	
			// determine alphabetical position in error list
			previous = NULL;
			next     = ErrorList;
			while ( 
				(next != NULL) &&  
				(strcmp(next->word, lowcase + 1) < 0)
			){			
				previous = next;
				next     = next->next;
			}
			if( next == NULL || strcmp(next->word, lowcase+1) > 0 )
			{
				// new entry for the list
				current = AllocMem(1, sizeof(SpellError));
				current->word = AllocMem(len, sizeof(char));
				assert( strlen(lowcase) == (unsigned) len );

				// do not include leading space
				strcpy(current->word, lowcase + 1);

				// insert current in list
				current->next = next;
				if( previous == NULL )
					ErrorList      = current;
				else	previous->next = current;
			}
			// add work to OK list so only one warning per word per section
			SpellingOkList(lowcase);
			//
			// warn about this occurance of the word
			*nOut = text - startWord;
			return startWord;
		}

		// advance to beginning of next word
		while( *text != '\0' && ! isalpha((int) *text) )
		{	if( ! isspace((int) *text) )
				lowlast[0] = '\0';
			text++;
		}
	}
	*nOut = 0;
	return NULL;
}

void FreeSpelling(int debug)
{	// initialize to avoid warning (set again before used)	
	FILE *fp = NULL;

	SpellError *current, *next;

	FreeMem(Special);
	FreeMem(Word);
	FreeMem(Memory);

	if( debug)
		fp = fopen("error.wrd", "w");
	
	current     = ErrorList;
	while ( current != NULL )
	{	
		if( debug )
			fprintf(fp, "%s\n", current->word);
		next = current->next;
		FreeMem(current->word);
		FreeMem(current);
		current = next;
	}
	if( debug )
		fclose(fp);
	ErrorList = NULL;

	Special  = NULL;
	Word     = NULL;
	Memory   = NULL;
}

void SpellingOkList(const char *list)
{	int len_list;
	int len_special;
	int i;
	int j;

	char *special;

	if( list[0] == '\0' )
	{	// clear the special list
		FreeMem(Special);
		Special = NULL;
		return;
	}

	// length of list 
	len_list = strlen(list);

	// length of special word 
	if( Special == NULL )
		len_special = 0;
	else	len_special = strlen(Special);

	len_special = len_special + 2 * len_list + 3;

	// allocate new list
	special = (char *) AllocMem(len_special, sizeof(char));

	// copy old special words
	j = 0;
	if( Special == NULL )
		special[j++] = ' ';
	else while( Special[j] != '\0' ) 
	{	special[j] = Special[j];
		j++;
	}
	assert( special[j-1] == ' ' );

	// convert to lower case and surround each word by spaces
	for(i = 0; i < len_list; i++)
	{	char ch;
		int space;

		ch    = list[i];
		space = special[j-1] == ' ';

		if( isupper((int) ch) )
			if( ! space )
				special[j++] = ' ';

		if( isalpha((int) ch) )
			special[j++] = tolower((int) ch);
		else	if( ! space )
				special[j++] = ' ';

		assert( j < len_special - 1 );
	}
	if( ! ( special[j-1] == ' ' ) )
		special[j++] = ' ';
	special[j] = '\0';

	// replace old version of special list by the new one
	FreeMem(Special);
	Special = special;

	assert( Special[0] == ' ' );
	assert( Special[ strlen(Special) - 1 ] == ' ' );

	return;
}
