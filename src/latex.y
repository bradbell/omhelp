// BEGIN SHORT COPYRIGHT
/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2004 Bradley M. Bell

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
// END SHORT COPYRIGHT
%{

# include <stdio.h>
# include <assert.h>
# include <string.h>
# include <ctype.h>

# include "texparse.h"
# include "output.h"
# include "int2str.h"
# include "fatalerr.h"
# include "TexStype.h"
# include "allocmem.h"
# include "str_alloc.h"
# include "convert.h"
# include "pending.h"

# include "TexStype.h"
# define YYSTYPE TexStype

# define YYDEBUG 1

// external function defined in omhelp.y
extern int PreviousOmhelpOutputWasHeading(void);

/*
----------------------------------------------------------------------------
$beign TexInitialNumberPending$$
$dollar @$$

$section Number of Commands Pending When @latex Command Started$$

$table
$bold Syntax$$
$cnext $syntax/TexInitialNumberPending()/$$
$tend

$end
----------------------------------------------------------------------------
*/

static int InitialNumberPending = 0;
int TexInitialNumberPending()
{	return InitialNumberPending; }

// ******************* Stype Functions (all Static ) *************************

static void OutputTexStype(TexStype *T)
{
	assert( T != NULL );
	while( T != NULL )
	{	assert( T->str != NULL );
		OutputString( T->str );

		// at point of output, extra pointer must be NULL
		assert( T->extra == NULL );

		T = T->next;
	}
	return;
}

static void FreeTexStype(TexStype *T)
{
	TexStype *N;

	assert( T != NULL );
	FreeMem( T->str );
	assert( T->extra == NULL );

	T = T->next;
	while( T != NULL )
	{	
		FreeMem( T->str );

		// at point of removal, extra pointer must be NULL
		assert( T->extra == NULL );

		N = T->next;
		FreeMem(T);
		T = N;
	}
	return;
}

static void StypePlusStype(TexStype *Head, TexStype *Tail)
{	TexStype *S;

	S = Head;
	while( S->next != NULL )
	{	assert( S->str != NULL );
		S = S->next;
	}

	S->next    = AllocMem(sizeof(TexStype), 1);
	*(S->next) = *Tail;

	return;
}

static void CharPlusStype(const char *head, TexStype *Head)
{	TexStype *S;

	assert( Head->str != NULL );

	S  = AllocMem(sizeof(TexStype), 1);
	*S = *Head;

	Head->next = S;
	Head->str  = str_alloc(head);

	return;
}

static void StypePlusChar(TexStype *Head, const char *tail)
{	TexStype *S;

	S = Head;
	while( S->next != NULL )
	{	assert( S->str != NULL );
		S = S->next;
	}

	S->next        = AllocMem(sizeof(TexStype), 1);
	S->next->str   = str_alloc(tail);
	S->next->extra = NULL;
	S->next->next  = NULL;

	return;
}

static int LengthStype(TexStype *Head)
{	TexStype *S;
	int      count;

	S     = Head;
	count = 1;
	assert( S != NULL );
	while( S->next != NULL )
	{	assert( S->str != NULL );
		S = S->next;
		count++;
	}

	return count;
}

// *********************** Static Data **********************************

// Maximum number of columns in an array
# define MAX_ARRAY_COL      100

// Maximum number of levels that an array can nest inside another array
# define MAX_ARRAY_LEVEL    10

// if base.data has this value, and base has this length
// display (base sub/sup term) using (base under/over term)
# define SUBSUP_2_UNDEROVER_DATA    (MAX_ARRAY_COL+1)
# define SUBSUP_2_UNDEROVER_LENGTH  3

static int BlockDisplay = 0;
static int ArrayLevel   = 0;
static const char *ArrayAlign[MAX_ARRAY_LEVEL][MAX_ARRAY_COL];

// values for tracking the current grouping by braces level
# define MAX_FONT_LEVEL  20
static int FontLevel;

// stack used to track fonts at each level
static char *CurrentFont[MAX_FONT_LEVEL];

// *********************** Other Static Functions *************************

static void IncFontLevel()
{

	FontLevel++;
	if( FontLevel == MAX_FONT_LEVEL ) fataltex(
		"request to nest left braces \"{\" and arrays deeper than ",
		int2str(MAX_FONT_LEVEL),
		" levels",
		NULL
	);
	assert( FontLevel >= 0 );

	// start with no font at this level 
	CurrentFont[FontLevel] = NULL;
}

static void DecFontLevel(TexStype *Head, int TerminateBeforeHead)
{
	// terminate font that is limited to this level
	assert( FontLevel >= 0 );
	if( CurrentFont[FontLevel] != NULL )
	{	// terminate current font
		FreeMem( CurrentFont[FontLevel] );
		if( TerminateBeforeHead )
		{	// check for special case where Head is empty
			if( Head->str == NULL )
			{	assert( Head->next == NULL );
				Head->str = str_alloc( "</mstyle>" );
			}
			else	CharPlusStype("</mstyle>", Head);
		}
		else	StypePlusChar(Head, "</mstyle>");
	}

	FontLevel--;
}

static const char *GetCurrentFont()
{	int i = FontLevel;

	while( i > 0 && CurrentFont[i] == NULL )
		i--;

	return CurrentFont[i];
}

static void SetArrayAlign(char *str)
{	size_t len;
	size_t i;

	assert( ArrayLevel <= MAX_ARRAY_LEVEL );
	if( ArrayLevel == MAX_ARRAY_LEVEL ) fataltex(
		"request to nest arrays deeper than ",
		int2str(MAX_ARRAY_LEVEL),
		" levels",
		NULL
	);

	// number of columns in array
	len = strlen( str );
	assert( len > 0 );
	if( len >= MAX_ARRAY_COL ) fataltex(
		"request for more than ",
		int2str(MAX_ARRAY_COL - 1),
		" columns in an array",
		NULL
	);

	// NULL is used to mark last column is previous column
	ArrayAlign[ArrayLevel][len] = NULL;

	for(i = 0; i < len; i++)
	{	switch( str[i] )
		{
			case 'l':
			ArrayAlign[ArrayLevel][i] = "columnalign=\"left\"";
			break;

			case 'c':
			ArrayAlign[ArrayLevel][i] = "columnalign=\"center\"";
			break;

			case 'r':
			ArrayAlign[ArrayLevel][i] = "columnalign=\"right\"";
			break;

			default:
			fataltex(
				"Invalid column alignment character \"",
				str,
				"\".\n",
				"The valid column alignment characters are ",
				"l, c, and r.",
				NULL
			);
		}
	}
}


// ***********************************************************************
%}

%token CHAR_AMPERSAND_lex
%token CHAR_CARET_lex
%token CHAR_ENDINPUT_lex
%token CHAR_LEFTBRACE_lex
%token CHAR_LEFTBRACKET_lex
%token CHAR_LETTERS_lex
%token CHAR_OPERATOR_lex
%token CHAR_RIGHTBRACE_lex
%token CHAR_RIGHTBRACKET_lex
%token CHAR_UNDERBAR_lex
%token CMD_BACKSLASH_lex
%token CMD_BEGIN_ARRAY_lex
%token CMD_DIACRITICAL_lex
%token CMD_END_ARRAY_lex
%token CMD_CHAR_lex
%token CMD_COMMA_lex
%token CMD_COLON_lex
%token CMD_FONT_lex
%token CMD_FRAC_lex
%token CMD_HSPACE_lex
%token CMD_LEFT_lex
%token CMD_LEFTBRACKET_lex
%token CMD_MATHML_lex
%token CMD_OVERBRACE_lex
%token CMD_OVERLINE_lex
%token CMD_RIGHT_lex
%token CMD_RIGHTBRACKET_lex
%token CMD_SEMICOLON_lex
%token CMD_SQRT_lex
%token CMD_STACKREL_lex
%token CMD_UNDERBRACE_lex
%token CMD_UNDERLINE_lex
%token CMD_WIDEHAT_lex
%token CMD_WIDETILDE_lex
%token NUMBER_lex
%token STDFUN_lex
%token STD_DISPLAY_lex
%token SYM_ARROW_lex
%token SYM_BINARYOP_lex
%token SYM_DISPLAY_lex
%token SYM_DOTS_lex
%token SYM_ENCLOSE_lex
%token SYM_GREEK_lex
%token SYM_INTEGRAL_lex
%token SYM_MISC_lex
%token SYM_RELATION_lex

%%

start
	: start_inline list_or_empty CHAR_ENDINPUT_lex
	{	assert( $1.str == NULL );
		assert( $3.str == NULL );
	
		assert( $2.str != NULL || $2.line == 0 );
		assert( $2.str != NULL || LengthStype(& $2) == 1 );

		assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $3) == 1 );

		if( $2.str == NULL ) 
			return BlockDisplay;

		// close font command at this level
		assert( FontLevel == 0 );
		DecFontLevel(& $2, 0);

		// need a newline after heading in the inline case
		if( PreviousOmhelpOutputWasHeading() )
			ConvertForcedNewline(1);

		OutputString(
			"\n<math xmlns=\"http://www.w3.org/1998/Math/MathML\""
			" display=\"inline\"><mrow>\n"
		);
		OutputTexStype(& $2);
		OutputString("</mrow></math>\n\n");

		FreeTexStype(& $2);

		return BlockDisplay;
	}
	| start_block list_or_empty CMD_RIGHTBRACKET_lex CHAR_ENDINPUT_lex
	{	assert( $1.str == NULL );
		assert( $3.str == NULL );
		assert( $4.str == NULL );
	
		assert( $2.str != NULL || $2.line == 0 );
		assert( $2.str != NULL || LengthStype(& $2) == 1 );

		assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $3) == 1 );
		assert( LengthStype(& $4) == 1 );

		if( $2.str == NULL ) fataltex(
			"empty $latex command between \\[ and \\]",
			NULL
		);

		// close font command that at this level
		assert( FontLevel == 0 );
		DecFontLevel(& $2, 0);

		OutputString(
			"\n<math xmlns=\"http://www.w3.org/1998/Math/MathML\""
			" display=\"block\"><mrow>\n"
		);
		OutputTexStype(& $2);
		OutputString("</mrow></math>\n\n");

		FreeTexStype(& $2);

		PopPending($3.line, "\\[");

		assert( NumberPending() == InitialNumberPending );

		return BlockDisplay;
	}
	;

start_inline
	:
	{	yydebug      = 0;
		BlockDisplay = 0;
		FontLevel    = -1;
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		InitialNumberPending = NumberPending();

		$$.line  = 0;
		$$.data  = 0;
		$$.str   = NULL;
		$$.next  = NULL;
		$$.extra = NULL;
	}
	;

start_block
	:	CMD_LEFTBRACKET_lex
	{	yydebug      = 0;
		BlockDisplay = 1;
		FontLevel    = -1;
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		InitialNumberPending = NumberPending();

		PushPending($1.line, "\\[");

		$$.line  = 0;
		$$.data  = 0;
		$$.str   = NULL;
		$$.next  = NULL;
		$$.extra = NULL;
	}
	;

argument
	: CHAR_LEFTBRACKET_lex list_or_empty CHAR_RIGHTBRACKET_lex
	{	assert( $1.str == NULL );
		assert( $2.str != NULL || $2.line == 0 );
		assert( $3.str == NULL );
		assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $3) == 1 );

		if( $2.str == NULL )
			$2.str = str_alloc(" ");

		CharPlusStype("<mrow>", & $2);
		StypePlusChar(& $2, "</mrow>");
		
		$$      = $2;
		$$.line = $1.line;
	}
	;

array
	: array_begin array_rows CMD_END_ARRAY_lex
	{	assert( $1.str != NULL );
		assert( $2.str != NULL || $2.line == 0 );
		assert( $2.str != NULL || LengthStype(& $2) == 1 );
		assert( $3.str == NULL );
		assert( ArrayLevel > 0 );
		assert( LengthStype(& $3) == 1 );

		if( $2.str != NULL )
			StypePlusStype(& $1, & $2);

		DecFontLevel(& $1, 0);
		StypePlusChar(& $1, "</mtd></mtr></mtable>\n");

		--ArrayLevel;

		PopPending($1.line , "\\begin{array}" );

		$$ = $1;
	}
	;

array_begin
	: CMD_BEGIN_ARRAY_lex array_rowalign array_colalign
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );
		assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $2) == 1 );
		assert( LengthStype(& $3) == 1 );

		$1.str  = StrCat(
			__FILE__,
			__LINE__,
			"<mtable ",
			$2.str,
			" ><mtr><mtd ",
			ArrayAlign[ArrayLevel][0],
			" >\n",
			NULL
		);
		++ArrayLevel;

		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		FreeMem($2.str);

		PushPending($1.line , "\\begin{array}" );

		$$ = $1;
	}
	;

array_colalign_list
	: CHAR_LETTERS_lex
	{
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		SetArrayAlign($1.str);
		FreeMem($1.str);

		$1.str  = NULL;
		$$      = $1;
	}
	;

array_colalign
	: CHAR_LEFTBRACE_lex array_colalign_list CHAR_RIGHTBRACE_lex
	{	assert( $1.str == NULL );
		assert( $2.str == NULL );
		assert( $3.str == NULL );
		assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $2) == 1 );
		assert( LengthStype(& $3) == 1 );

		$$ = $1;
	}
	;


array_col_next
	: CHAR_AMPERSAND_lex 
	{	
		assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// done with previous column when this is reduced
		DecFontLevel(& $1, 1);
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		$$      = $1;
	}
	;

array_cols
	: list_or_empty
	{	assert( $1.str != NULL || $1.line == 0 );
		assert( ArrayLevel > 0 );

		$$      = $1;
		$$.data = 1;    // first column of the array
	}
	| array_cols array_col_next list_or_empty
	{	char *str;
	
		int col;

		assert( $1.str != NULL || $1.line == 0 );
		assert( $1.str != NULL || LengthStype(& $1) == 1);

		// $2.str == NULL if no font is pending
		assert( LengthStype(& $2) == 1 );

		assert( $3.str != NULL || $3.line == 0 );
		assert( $3.str != NULL || LengthStype(& $3) == 1);

		assert( ArrayLevel > 0 );
		assert( $$.data > 0 );

		col   = $1.data;

		if( ArrayAlign[ArrayLevel-1][col] == NULL ) fataltex(
			"to many columns of data in array",
			NULL
		);

		str = StrCat(
			__FILE__,
			__LINE__,
			"</mtd><mtd ",
			ArrayAlign[ArrayLevel-1][col],
			" >\n",
			NULL
		);

		if( $1.str != NULL )
		{	if( $2.str != NULL )
				StypePlusStype(& $1, & $2);

			StypePlusChar(& $1, str);
			FreeMem( str );

			if( $3.str != NULL )
				StypePlusStype(& $1, & $3);
		}
		else
		{	if( $2.str != NULL )
			{	$1 = $2;

				StypePlusChar(& $1, str);
				FreeMem( str );

				if( $3.str != NULL )
					StypePlusStype(& $1, & $3);
			}
			else
			{	$1.str = str;
				// do not want to free str in this case

				if( $3.str != NULL )
					StypePlusStype(& $1, & $3);
			}
		}

		$$      = $1;
		$$.data = col + 1;   // next column of the array
	}
	;

array_rowalign
	:
	{	// center is the default row alignment
		$$.line  = 0;
		$$.data  = 0;
		$$.str   = str_alloc("rowalign=\"center\"");
		$$.next  = NULL;
		$$.extra = NULL;
	}
	| CHAR_LEFTBRACKET_lex CHAR_LETTERS_lex CHAR_RIGHTBRACKET_lex
	{	size_t len;

		char *str;

		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str == NULL );
		assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $2) == 1 );
		assert( LengthStype(& $3) == 1 );

		str = $2.str;
		len = strlen(str);

		if( len > 1 ) fataltex(
			"The row alignment specification \"",
			str,
			"\"\ncontains more than one character.",
			NULL
		);
		switch( str[0] )
		{	case 'b':
			$1.str = str_alloc("rowalign=\"bottom\"");
			break;

			case 'c':
			$1.str = str_alloc("rowalign=\"center\"");
			break;

			case 't':
			$1.str = str_alloc("rowalign=\"top\"");
			break;

			default:
			fataltex(
				"The row alignment character \"",
				str,
				"\" is not valid.\n",
				"The valid row alignment characters are ",
				"b, c, and t.",
				NULL
			);
		}
		FreeMem(str);

		$$ = $1;
	}
	;
	

array_rows
	: array_cols
	{	assert( $1.str != NULL || $1.line == 0 );
		assert( $1.str != NULL || LengthStype(& $1) == 1 );

		assert( ArrayLevel > 0 );
		$$      = $1;

		// no longer counting columns
		$$.data = 0;
	}
	| array_rows CMD_BACKSLASH_lex array_cols
	{	assert( $1.str != NULL || $1.line == 0 );
		assert( $1.str != NULL || LengthStype(& $1) == 1 );

		assert( $3.str != NULL || $3.line == 0 );
		assert( $3.str != NULL || LengthStype(& $3) == 1 );

		assert( $2.str == NULL );
		assert( LengthStype(& $2) == 1 );

		// no longer counting columns
		$3.data = 0;

		$2.str = StrCat(
			__FILE__,
			__LINE__,
			"</mtd></mtr><mtr><mtd ",
			ArrayAlign[ArrayLevel-1][0],
			" >\n",
			NULL
		);
		DecFontLevel(& $2, 1);
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		if( $1.str != NULL )
			StypePlusStype(& $1, & $2);
		else	$1 = $2;
		if( $3.str != NULL )
			StypePlusStype(& $1, & $3);

		$$ = $1;
	}
	;

arrow
	: SYM_ARROW_lex
	{	// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & $1);
		StypePlusChar(& $1, "</mo>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;
	}
	;

binary
	: SYM_BINARYOP_lex
	{	// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mo stretchy=\"false\">" , & $1);
		StypePlusChar(& $1, "</mo>\n");

		$$ = $1;
	}
	;

diacritical
	: CMD_DIACRITICAL_lex group
	{	assert( $1.str != NULL );
		assert( $2.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mover accent='false'>", & $2);
		StypePlusChar(& $2, "<mo stretchy='false'>");
		StypePlusStype(& $2, & $1);
		StypePlusChar(& $2, "</mo></mover>\n");

		$$      = $2;
		$$.line = $1.line;
	}
	;


dots
	: SYM_DOTS_lex
	{	// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & $1);
		StypePlusChar(& $1, "</mo>\n");

		$$ = $1;
	}
	;
		

encloser
	: SYM_ENCLOSE_lex
	{	assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		$$ = $1;
	}
	| encloser_check
	{	assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		switch( $1.str[0] )
		{
			case '{':
			case '}':
			case ')':
			case '(':
			case '[':
			case ']':
			case '/':
			case '|':
			case '.':
			break;

			default:
			fataltex(
				"The character ",
				$1.str,
				"\ncannot be used directly after ",
				"\\left or \\right",
				"\nbecause it is not an enclosing character",
				NULL
			);
		}

		$$ = $1;
	}
	;

encloser_check
	: CHAR_OPERATOR_lex
	{	assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );
	
		$$ = $1;
	}
	| CHAR_LETTERS_lex
	{	assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		fataltex(
			"The text ",
			$1.str,
			"\ncannot be used directly after ",
			"\\left or \\right",
			"\nbecause it does not begin with ",
			"an enclosing character",
			NULL
		);
	
	}
	| CMD_CHAR_lex
	{	assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );
	
		$$ = $1;
	}
	;

element 
	: array
	{	$$ = $1; }
	| arrow
	{	$$ = $1; }
	| binary
	{	$$ = $1; }
	| diacritical
	{	$$ = $1; }
	| dots
	{	$$ = $1; }
	| font
	{	$$ = $1; }
	| frac
	{	$$ = $1; }
	| greek
	{	$$ = $1; }
	| group 
	{	$$ = $1; }
	| left_right
	{	$$ = $1; }
	| letter
	{	$$ = $1; }
	| mathml
	{	$$ = $1; }
	| misc
	{	$$ = $1; }
	| number
	{	$$ = $1; }
	| operator
	{	$$ = $1; }
	| over
	{	$$ = $1; }
	| relation
	{	$$ = $1; }
	| space 
	{	$$ = $1; }
	| special_char
	{	$$ = $1; }
	| sqrt
	{	$$ = $1; }
	| stackrel
	{	$$ = $1; }
	| stdfun
	{	$$ = $1; }
	| std_display
	{	$$ = $1; }
	| sym_display
	{	$$ = $1; }
	| sym_enclose
	{	$$ = $1; }
	| sym_integral
	{	$$ = $1; }
	| underbrace
	{	$$ = $1; }
	| underline
	{	$$ = $1; }
	;

font
	: CMD_FONT_lex
	{	assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );


		// close previous font command and start new one
		assert( FontLevel >= 0 );
		if( CurrentFont[FontLevel] != NULL )
		{	FreeMem( CurrentFont[FontLevel] );
			CurrentFont[FontLevel] = str_alloc( $1.str );

			// terminate previous font command
			CharPlusStype("</mstyle>", & $1);
		}
		else	CurrentFont[FontLevel] = str_alloc( $1.str );

		// $1 contains the <mstyle mathvariant='$1'> argument
		CharPlusStype("<mstyle mathvariant='", & $1);
		StypePlusChar(& $1, "'>");

		$$ = $1;
	}
	;

frac
	: CMD_FRAC_lex group group
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mfrac>", & $2);
		StypePlusStype(& $2, & $3);	
		StypePlusChar(& $2, "</mfrac>\n");

		$$      = $2;
		$$.line = $1.line;
	}
	;

greek
	: SYM_GREEK_lex
	{	char *s;

		// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		if( GetCurrentFont() != NULL )
		{	s = StrCat(
				__FILE__,
				__LINE__,
				"<mi mathvariant='", 
				GetCurrentFont(),
				"'>",
				NULL
			);  
			CharPlusStype(s, & $1);
			FreeMem(s);
		}
		else	CharPlusStype("<mi mathvariant='normal'>", & $1);

		StypePlusChar(& $1, "</mi>\n");

		$$ = $1;
	}
	;


group
	: group_begin list_or_empty CHAR_RIGHTBRACE_lex
	{	// done processing this group
		assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $3) == 1 );
		assert( $1.str == NULL );
		assert( $3.str == NULL );

		if( $2.str == NULL )
			$2.str = str_alloc(" ");

		// terminate font that is limited to this group
		DecFontLevel(& $2, 0);
		assert( FontLevel >= 0 );

		CharPlusStype("<mrow>", & $2);
		StypePlusChar(& $2, "</mrow>\n");

		PopPending($3.line, "{");

		$$      = $2;
		$$.line = $1.line;
	}
	;

group_begin
	: CHAR_LEFTBRACE_lex
	{	// begin a group
		assert( LengthStype(& $1) == 1 );
		assert( $1.str == NULL );

		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		PushPending($1.line, "{");

		$$ = $1;
	}
	;

left_right_begin
	: CMD_LEFT_lex
	{
		assert( $1.str == NULL );
		assert( LengthStype( & $1 ) == 1 );

		PushPending($1.line, "\\left");

		$$ = $1;
	}
	;

left_right
	: left_right_begin encloser list CMD_RIGHT_lex encloser
	{
		assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str != NULL );
		assert( $4.str == NULL );
		assert( $5.str != NULL );
		
		assert( LengthStype( & $1 ) == 1 );
		assert( LengthStype( & $2 ) == 1 );
		assert( LengthStype( & $4 ) == 1 );
		assert( LengthStype( & $5 ) == 1 );

		if( strcmp($2.str, ".") == 0 )
		{	FreeMem($2.str);
			$2.str = str_alloc(" "); // replace . by nothing
		}
		if( strcmp($5.str, ".") == 0 )
		{	FreeMem($5.str);
			$5.str = str_alloc(" "); // replace . by nothing
		}
	
		CharPlusStype("<mrow><mo stretchy=\"true\">", & $2);
		StypePlusChar(& $2, "</mo><mrow>");
		StypePlusStype(& $2, & $3);
		StypePlusChar(& $2, "</mrow><mo stretchy=\"true\">");
		StypePlusStype(& $2, & $5);
		StypePlusChar(& $2, "</mo></mrow>\n");

		PopPending($4.line, "\\left");

		$$      = $2;
		$$.line = $1.line;

	}
	;

letter
	: CHAR_LETTERS_lex
	{	char *s;

		// str is the single letter
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		if( GetCurrentFont() != NULL )
		{	s = StrCat(
				__FILE__,
				__LINE__,
				"<mi mathvariant='", 
				GetCurrentFont(),
				"'>",
				NULL
			);  
			CharPlusStype(s, & $1);
			FreeMem(s);
		}
		else	CharPlusStype("<mi mathvariant='italic'>", & $1);

		StypePlusChar(& $1, "</mi>\n");

		$$ = $1;
	}
	;

list
	: element
	{	assert( $1.str != NULL );
		$$ = $1;
	}
	| subsup
	{	assert( $1.str != NULL );
		$$ = $1;
	}
	| list element
	{	assert( $1.str != NULL );
		assert( $2.str != NULL );

		StypePlusStype(& $1, & $2);

		$$ = $1;
	}
	| list subsup
	{	assert( $1.str != NULL );
		assert( $2.str != NULL );

		StypePlusStype(& $1, & $2);

		$$ = $1;
	}
	;

list_or_empty
	:
	{	
		$$.line  = 0;
		$$.data  = 0;
		$$.str   = NULL;
		$$.next  = NULL;
		$$.extra = NULL;
	}
	| list
	{	$$ = $1; }
	;

mathml
	: CMD_MATHML_lex 
	{	int i;
		int j;
		int escape;
		char *str;

		assert( $1.str != NULL );
		assert( LengthStype(& $1 ) == 1 );

		// replace escape sequences used for macros
		i      = 0;
		j      = 0;
		escape = 0;
		str    = $1.str;
		while( str[i] != '\0' )
		{	if( escape )
			{	if( str[i] == '#' )
					--j;
				escape = 0;
			}
			else	escape = (str[i] == '\\');
			str[j] = str[i];
			++j;
			++i;
		}
		str[j] = '\0';

		$$ = $1;
	}
	;

misc
	: SYM_MISC_lex
	{	// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & $1);
		StypePlusChar(& $1, "</mo>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;
	}
	;

number
	: NUMBER_lex
	{	// str contains the number
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mn>", & $1);
		StypePlusChar(& $1, "</mn>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;
	}
	;

operator
	: CHAR_OPERATOR_lex
	{	// str is one character and equal to operator 
		char *str = $1.str;

		assert( str != NULL );
		assert( strlen(str) == 1 );
		assert( LengthStype(& $1) == 1 );

		switch( str[0] )
		{
			case '<':
			FreeMem(str);
			$1.str = str = str_alloc("&lt;"); // lt = x0003C
			break;
			
			case '>':
			FreeMem(str);
			$1.str = str = str_alloc("&gt;"); // gt = x0003E
			break;

			default:
			;
		}

		CharPlusStype("<mo stretchy=\"false\">" , & $1);
		StypePlusChar(& $1, "</mo>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;
	}
	;

over
	: over_cases group
	{	assert( $1.str != NULL );
		assert( $2.str != NULL );

		CharPlusStype("<mover>", & $2);
		StypePlusStype(& $2, & $1);

		$$      = $2;
		$$.line = $1.line;
	}
	;

over_cases
	: CMD_OVERBRACE_lex
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// OverBrace = #x0FE37
		$1.str = str_alloc(
		"<mo stretchy=\"true\">&#x0FE37;</mo></mover>\n"
		);
		$$ = $1;
	}
	| CMD_OVERLINE_lex
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// OverBar = #x000AF
		$1.str = str_alloc(
		"<mo stretchy=\"true\">&#x000AF;</mo></mover>\n"
		);

		$$ = $1;
	}
	| CMD_WIDEHAT_lex 
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// Hat = #x00302
		$1.str = str_alloc(
		"<mo stretchy=\"true\">&#x00302;</mo></mover>\n"
		);

		$$ = $1;
	}
	| CMD_WIDETILDE_lex 
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// DiacriticalTilde = x002DC
		$1.str = str_alloc(
		"<mo stretchy=\"true\">&#x002DC;</mo></mover>\n"
		);

		$$ = $1;
	}
	;


relation
	: SYM_RELATION_lex
	{	// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & $1);
		StypePlusChar(& $1, "</mo>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;
	}
	;

space
	: CMD_COMMA_lex
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// .9/5 because \hspace{.9em} is same as \, \, \, \, \,
		$1.str = str_alloc("<mspace width='.18em'/>\n");

		$$ = $1;
	}
	| CMD_COLON_lex
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// .9/4 because \hspace{.9em} is same as \: \: \: \:
		$1.str = str_alloc("<mspace width='.225em'/>\n");

		$$ = $1;
	}
	| CMD_SEMICOLON_lex
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		// .9/3 because \hspace{.9em} is same as \; \; \;
		$1.str = str_alloc("<mspace width='.3em'/>\n");

		$$ = $1;
	}
	| CMD_HSPACE_lex 
	{	assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mspace width='", & $1);
		StypePlusChar(& $1, "'/>\n");

		$$ = $1;
	}
	;

special_char
	: CMD_CHAR_lex
	{	// str is the entire command
		char *str = $1.str;
		assert( strlen($1.str) == 1 );
		assert( LengthStype(& $1) == 1 );

		assert( str != NULL );

		switch( str[0] )
		{
			case '&':
			// convert raw ampersand to Unicode
			FreeMem(str);
			$1.str = str = str_alloc("&amp;"); // amp = x00026
			// now drop same as the cases below

			case '#':
			case '$':
			case '%':
			case '_':
			case '{':
			case '}':
			CharPlusStype("<mo stretchy=\"false\">", & $1);
			StypePlusChar(& $1, "</mo>\n");
			break;

			default:
			assert(0);
		}
		assert( LengthStype( & $1 ) == 3 );

		$$ = $1;
	}
	;

sub_element_sup_element
	: CHAR_UNDERBAR_lex element CHAR_CARET_lex element
	{	assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $3) == 1 );

		$$       = $2;
		$$.line  = $1.line;
		$$.extra = AllocMem(sizeof(TexStype), 1);
		*($$.extra) = $4;

	}
	| CHAR_CARET_lex element CHAR_UNDERBAR_lex element
	{	assert( LengthStype(& $1) == 1 );
		assert( LengthStype(& $3) == 1 );

		$$       = $4;
		$$.line  = $1.line;
		$$.extra = AllocMem(sizeof(TexStype), 1);
		*($$.extra) = $2;

	}
	;

subsup
	: element sub_element_sup_element
	{	TexStype *E;
		int munderover;

		assert( $1.str != NULL );
		assert(   $2.str != NULL );
		assert( $2.extra != NULL );

		E        = $2.extra;
		$2.extra = NULL;

		munderover = ( $1.data == SUBSUP_2_UNDEROVER_DATA )
		           && ( LengthStype(& $1) == SUBSUP_2_UNDEROVER_LENGTH )
		;
	
		if( munderover )
			CharPlusStype("<munderover>", & $1);
		else	CharPlusStype("<msubsup>", & $1);

		StypePlusStype(& $1, & $2);
		StypePlusStype(& $1, E);
	
		if( munderover )
			StypePlusChar(& $1, "</munderover>\n");
		else	StypePlusChar(& $1, "</msubsup>\n");

		FreeMem(E);
		$$ = $1;
	}
	| element CHAR_UNDERBAR_lex element
	{	int munder;

		assert( $1.str != NULL );
		assert( $3.str != NULL );
		assert( LengthStype(& $2) == 1 );


		munder = ( $1.data == SUBSUP_2_UNDEROVER_DATA )
		           && ( LengthStype(& $1) == SUBSUP_2_UNDEROVER_LENGTH )
		;

		if( munder )
			CharPlusStype("<munder>", & $1);
		else	CharPlusStype("<msub>", & $1);

		StypePlusStype(& $1, & $3);

		if( munder )
			StypePlusChar(& $1, "</munder>\n");
		else	StypePlusChar(& $1, "</msub>\n");

		$$ = $1;
	}
	| element CHAR_CARET_lex element
	{	int mover;

		assert( $1.str != NULL );
		assert( $3.str != NULL );
		assert( LengthStype(& $2) == 1 );

		mover = ( $1.data == SUBSUP_2_UNDEROVER_DATA )
		           && ( LengthStype(& $1) == SUBSUP_2_UNDEROVER_LENGTH )
		;

		if( mover )
			CharPlusStype("<mover>", & $1);
		else	CharPlusStype("<msup>", & $1);

		StypePlusStype(& $1, & $3);

		if( mover )
			StypePlusChar(& $1, "</mover>\n");
		else	StypePlusChar(& $1, "</msup>\n");

		$$ = $1;
	}
	;

sqrt
	: CMD_SQRT_lex group
	{	assert( $1.str == NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<msqrt>", & $2);
		StypePlusChar(& $2, "</msqrt>\n");

		$$      = $2;
		$$.line = $1.line;
	}
	| CMD_SQRT_lex argument group
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mroot>", & $3);
		StypePlusStype(& $3, & $2);
		StypePlusChar(& $3, "</mroot>\n");

		$$      = $3;
		$$.line = $1.line;
	}
	; 

stackrel
	: CMD_STACKREL_lex group group
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );
		assert( $3.str != NULL );

		assert( LengthStype(& $1) == 1 );

		$1.str = str_alloc("<mover>");
		StypePlusStype(& $1, & $3);
		StypePlusStype(& $1, & $2);
		StypePlusChar(& $1, "</mover>\n");

		$$ = $1;
	}
	;
		

stdfun
	: STDFUN_lex
	{	// str is the name of the standard function
		assert( $1.str != NULL );
		assert( strlen($1.str) > 1 );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mi>", & $1);
		StypePlusChar(& $1, "</mi>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;
	}
	;

std_display
	: STD_DISPLAY_lex
	{	// str is the name of the standard function
		assert( $1.str != NULL );
		assert( strlen($1.str) > 1 );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mi>", & $1);
		StypePlusChar(& $1, "</mi>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;

		printf("STD_DISPLAY_lex str = %s\n", $1.str);

		// if BlockDisplay is true, use under/over inplace of sub/sup 
		assert( LengthStype( & $$ ) == SUBSUP_2_UNDEROVER_LENGTH );
		if( BlockDisplay )
			$$.data = SUBSUP_2_UNDEROVER_DATA;
	}
	;


sym_display
	: SYM_DISPLAY_lex
	{	char *s;

		// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		if( BlockDisplay )
			s = "<mo stretchy='false' minsize='2em'>";
		else	s = "<mo stretchy='false' >";
		CharPlusStype(s, & $1);
		StypePlusChar(& $1, "</mo>\n");

		$$ = $1;

		// if BlockDisplay is true, use under/over inplace of sub/sup 
		assert( LengthStype( & $$ ) == SUBSUP_2_UNDEROVER_LENGTH );
		if( BlockDisplay )
			$$.data = SUBSUP_2_UNDEROVER_DATA;
	}
	;

sym_enclose
	: SYM_ENCLOSE_lex
	{	// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & $1);
		StypePlusChar(& $1, "</mo>\n");

		assert( LengthStype( & $1 ) == 3 );
		$$ = $1;
	}
	;

sym_integral
	: SYM_INTEGRAL_lex
	{	// str is unicode for this symbol
		assert( $1.str != NULL );
		assert( LengthStype(& $1) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & $1);
		StypePlusChar(& $1, "</mo>\n");

		$$ = $1;
	}
	;

underbrace
	: CMD_UNDERBRACE_lex group
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );

		assert( LengthStype(& $1) == 1 );

		$1.str = str_alloc("<munder>");
		StypePlusStype(& $1, & $2);

		// UnderBrace = x0FE38
		StypePlusChar(& $1, 
		"<mo stretchy=\"true\">&#x0FE38;</mo></munder>\n");

		$$ = $1;
	}
	;

underline
	: CMD_UNDERLINE_lex group
	{	assert( $1.str == NULL );
		assert( $2.str != NULL );

		assert( LengthStype(& $1) == 1 );

		$1.str = str_alloc("<munder>");
		StypePlusStype(& $1, & $2);

		// UnderBar (x00332) does not work in Mozilla
		// so we use OverBar (x000AF) in its place
		StypePlusChar(& $1, 
		"<mo stretchy=\"true\">&#x000AF;</mo></munder>\n");

		$$ = $1;
	}
	;


%%
