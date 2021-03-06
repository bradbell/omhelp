%{
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
Lexical analyizer for a subset of Latex Commands
$begin  LatexLexPut$$
$spell
	const
	ntoken
$$

$section Set Input Characters Corresponding Latex Lexical Analyzer$$

$head Syntax$$
$codei/LatexLexPut(/line/, /input/)/$$


$head Description$$
The Latex lexical analyzer reads its data from memory.
This call sets the input data to the $code const$$ '\0' terminated
character vector specified by $icode input$$.
The integer $icode line$$ specifies the line
number in the file $cref/InputName()/InputName_dev/$$
where $icode input$$ started.

$head Memory Allocation$$
This call allocates memory using $cref AllocMem_dev$$.
This memory is freed when the Latex lexical analyzer returns
$code CHAR_ENDINPUT_lex$$.


$end
------------------------------------------------------------------------
$begin LatexLexHistory_dev$$
$spell
	ntoken
$$

$section Recall Tokens Recently Returned To Parser$$

$head Syntax$$
$codei/LatexLexHistory(/number/, /length/, /line/, /token/)/$$


$head Description$$
The return value of $code LatexLexHistory$$ is a $code int$$
which we refer to as $icode ntoken$$.
It specifies the actual number of tokens returned
by $code LatexLexHistory$$.
$codei/

int /number/
/$$
The value $icode number$$ specifies the
maximum number of tokens to return.
The value $icode ntoken$$ will be less than or
equal $icode number$$.
$codei/

int /length/
/$$
The value $icode length$$ specifies the
maximum number of character to return for each token.
$codei%

int *%line%
%$$
The array $icode line$$ must have at least $icode number$$
elements in it.
The input value of the elements of $icode line$$ does not matter.
For $math% i=0,...,ntoken-1 %$$
the value of $icode/line/[/i/]/$$ is set to the line
number where the token
$icode/token/[/i/]/$$ appeared in the
file $cref/InputName()/InputName_dev/$$.
$codei%

char **%token%
%$$
The array $icode token$$ must have at least $icode number$$
elements in it.
Each element of $icode token$$ is in turn an array of characters
with at least $icode length$$ elements in it.
The input value of the elements of $icode token$$ does not matter.
For $math% i=0,...,ntoken-1 %$$,
the value of $icode/token/[/i/]/$$ is a '\0' terminated
character vector containing a previous token.
The tokens are returned
in reverse order of how they appeared in the input.
If a token is longer than $math% length-1 %$$ characters,
only the first $math% length-1 %$$ characters are included.

$end
*/
# include "LatexLexPut.h"
# include "LatexLexHistory.h"

#ifdef WIN32
# include <conio.h>
#endif

# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>

# include "LatexMacro.h"
# include "fatalerr.h"
# include "str_alloc.h"
# include "allocmem.h"
# include "input.h"
# include "int2str.h"
# include "LatexAtomic.h"

# include "TexStype.h"
# define YYSTYPE  TexStype
# ifdef WIN32
# define YY_NO_UNISTD_H
# endif

// see http://sourceware.org/ml/gdb-patches/2010-01/msg00372.html
# define YY_NO_INPUT

// maximum input token buffer sizes
# define MAX_TOKEN_LENGTH 100
# define MAX_TOKEN_NUMBER 10


// print debugging information
# define DEBUG_TOKENS 0

// automatically generated include file generated by yacc from latex.y
# include "latex.h"


static void SetTexLval(const char *token, const char *str);

// define the character input routine
# undef YY_INPUT
# define YY_INPUT(buf, result, max_size) \
{	assert( max_size != 0 );         \
	buf[0]  = LatexMacroGetCh();     \
	result = 1;                      \
}

static char Cmd_Bracket_Mode = '\0';

/*
Source:  http://www.w3.org/TR/MathML2/isodia.html
Source:  http://www.w3.org/TR/MathML2/byalpha.html
Date:    02-11-21
Section: IDODIA Characters and Glyphs
Chapter: Entities, Characters and Fonts
*/
static struct cmdover {
	char *name;
	char *mathml;
} Diacritical[] = {
	// Latex       MathML
	{ "acute",  "&#x000B4;" },      // DiacriticalAcute = x000B4
	{ "bar",    "&#x000AF;" },      // OverBar          = x000AF
	{ "breve",  "&#x002D8;" },      // Breve            = x002D8
	{ "check",  "&#x002C7;" },      // caron            = x002C7
	{ "ddot",   "&#x000A8;" },      // Dot              = x000A8
	{ "dot",    "&#x002D9;" },      // dot              = x002D9
	{ "hat",    "&#x0005E;" },      // circ             = x0005E
	{ "grave",  "&#x00060;" },      // grave            = x00060
	{ "tilde",  "&#x002DC;" },      // tilde            = x002DC
	{ "vec",    "&#x021C0;" }       // RightVector      = x021C0
};
static size_t NDiacritical =
	sizeof(Diacritical) / sizeof(Diacritical[0]);

/***************************************************************************/
%}
%option nounput

ampersand      ([&])
caretchar      (\^)
command        (\\[a-zA-Z]+\*?)
invalid        (\\[^a-zA-Z])
comment        (%[^\001\n]*([\001]|\n))
eof            ([\001])
integer        (-?[0-9]+)
letter         ([a-zA-Z])
leftbrace      (\{)
leftbracket    (\[)
newline        ([\n])
number         ({integer}|({integer}\.[0-9]*)|(-?\.[0-9]+))
operator       ([!"'()*+./:,;<=>?@`]|\-|\|)
rightbrace     (\})
rightbracket   (\])
underbar       (\_)
unit           (cm|em|ex|in|pc|pt|mm)
white          ([ \t\r]*)

%%

	// special commands with separate constructions
\\\\ {
		assert( strlen(yytext) == 2 );

		SetTexLval(yytext, NULL);
		return CMD_BACKSLASH_lex;
	}
\\\[ {
		assert( strlen(yytext) == 2 );

		SetTexLval(yytext, NULL);
		return CMD_LEFTBRACKET_lex;
	}
\\\] {
		assert( strlen(yytext) == 2 );

		SetTexLval(yytext, NULL);
		return CMD_RIGHTBRACKET_lex;
	}
\\\| {
		assert( strlen(yytext) == 2 );

		// double vertical line
		SetTexLval(yytext, "&#x02016;"); // Vert = x02016

		return SYM_ENCLOSE_lex;
	}
\\, {
		assert( strlen(yytext) == 2 );
		SetTexLval(yytext, NULL);
		return CMD_COMMA_lex;
	}
\\; {
		assert( strlen(yytext) == 2 );
		SetTexLval(yytext, NULL);
		return CMD_SEMICOLON_lex;
	}
\\: {
		assert( strlen(yytext) == 2 );
		SetTexLval(yytext, NULL);
		return CMD_COLON_lex;
	}
\\[#$%&_{}] {
		assert( strlen(yytext) == 2 );

		SetTexLval(yytext, yytext + 1);
		return CMD_CHAR_lex;
	}
{invalid} {
		fataltex(
			"The text '",
			yytext,
			"' is not a valid Latex command.",
			NULL
		);
	}
\\begin[{]array[}] {
		SetTexLval(yytext, NULL);
		Cmd_Bracket_Mode = '[';
		return CMD_BEGIN_ARRAY_lex;
}
\\bf	{
		SetTexLval(yytext, "bold" );
		return CMD_FONT_lex;
	}
\\cal	{
		SetTexLval(yytext, "italic" );
		return CMD_FONT_lex;
	}
\\end[{]array[}] {
		SetTexLval(yytext, NULL);
		return CMD_END_ARRAY_lex;
	}
\\frac	{
		SetTexLval(yytext, NULL);
		return CMD_FRAC_lex;
	}
\\hspace[{]{white}{number}{white}{unit}{white}[}] {
		size_t len = strlen(yytext);

		assert( strncmp( yytext, "\\hspace{", 8 ) == 0 );
		assert( yytext[len-1] == '}' );

		yytext[len-1] = '\0';
		SetTexLval(yytext + 8, yytext + 8);
		yytext[len-1] = '}';

		return CMD_HSPACE_lex;
	}
\\left {
		SetTexLval(yytext, NULL);
		return CMD_LEFT_lex;
	}
\\mathml[{][^}]+[}] {
		size_t len = strlen(yytext);

		assert( len >= 10 );
		assert( yytext[len-1] == '}' );

		yytext[len-1] = '\0';
		SetTexLval(yytext + 8 , yytext + 8);
		yytext[len-1] = '}';

		return CMD_MATHML_lex;
	}
\\overbrace {
		SetTexLval(yytext, NULL);
		return CMD_OVERBRACE_lex;
	}
\\overline {
		SetTexLval(yytext, NULL);
		return CMD_OVERLINE_lex;
	}
\\right {
		SetTexLval(yytext, NULL);
		return CMD_RIGHT_lex;
	}
\\sf	{
		SetTexLval(yytext, "sans-serif" );
		return CMD_FONT_lex;
	}
\\sqrt {
		SetTexLval(yytext, NULL);
		Cmd_Bracket_Mode = '[';
		return CMD_SQRT_lex;
	}
\\tt	{
		SetTexLval(yytext, "monospace" );
		return CMD_FONT_lex;
	}
\\underbrace {
		SetTexLval(yytext, NULL);
		return CMD_UNDERBRACE_lex;
	}
\\underline {
		SetTexLval(yytext, NULL);
		return CMD_UNDERLINE_lex;
	}
\\widehat {
		SetTexLval(yytext, NULL);
		return CMD_WIDEHAT_lex;
	}
\\widetilde {
		SetTexLval(yytext, NULL);
		return CMD_WIDETILDE_lex;
	}
\\rm	{
		SetTexLval(yytext, "normal" );
		return CMD_FONT_lex;
	}
\\stackrel {
		SetTexLval(yytext, NULL);
		return CMD_STACKREL_lex;
	}
{ampersand} {
		SetTexLval(yytext, NULL);
		return CHAR_AMPERSAND_lex;
	}
{caretchar} {
		SetTexLval(yytext, NULL);
		return CHAR_CARET_lex;
	}
{command} {
	const char *name;
	const char  *str;
	int        token;
	size_t         i;

	name = yytext + 1;

	str = LatexAtomic(name, &token);
	if( str != NULL )
	{	SetTexLval(yytext, str);
		return token;
	}
	for(i = 0; i < NDiacritical; i++)
	{	if( strcmp(Diacritical[i].name, name) == 0 )
		{	SetTexLval(yytext, Diacritical[i].mathml);
			return CMD_DIACRITICAL_lex;
		}
	}

	fataltex(
		yytext,
		" is not a valid command in OMhelp's Latex mode.",
		NULL
	);
}
{comment} {
	// ignore
}
{eof} {
	SetTexLval("CHAR_ENDINPUT_lex", NULL);
	return CHAR_ENDINPUT_lex;
}
{leftbrace} {
	SetTexLval(yytext, NULL);
	return CHAR_LEFTBRACE_lex;
}
{leftbracket} {
	if( Cmd_Bracket_Mode == '[' )
	{	SetTexLval(yytext, NULL);
		Cmd_Bracket_Mode = ']';
		return CHAR_LEFTBRACKET_lex;
	}
	if( Cmd_Bracket_Mode == ']' ) fatalerr(
		"another '[' occurred while looking for the ']'\n",
		"that terminates a command argument started with a '['",
		NULL
	);
	SetTexLval(yytext, yytext);
	return CHAR_OPERATOR_lex;
}
{letter}+ {

# ifndef NDEBUG
	size_t i;
	i = strlen(yytext);
	assert( i > 0 );
# endif

	// check begins with a letter
	assert( isalpha((int) yytext[0] ) );

	SetTexLval(yytext, yytext);

	return CHAR_LETTERS_lex;
}
{newline} {
	// ignore
}
{number} {
	SetTexLval(yytext, yytext);
	return NUMBER_lex;
}
{operator} {	// operators that do not need conversion to Unicode

	SetTexLval(yytext, yytext);
	return CHAR_OPERATOR_lex;
}
{rightbrace} {
	SetTexLval(yytext, NULL);
	return CHAR_RIGHTBRACE_lex;
}
{rightbracket} {
	if( Cmd_Bracket_Mode == ']' )
	{	SetTexLval(yytext, NULL);
		Cmd_Bracket_Mode = '\0';
		return CHAR_RIGHTBRACKET_lex;
	}
	SetTexLval(yytext, yytext);
	return CHAR_OPERATOR_lex;
}
{underbar} {
	SetTexLval(yytext, NULL);
	return CHAR_UNDERBAR_lex;
}
{white} {
	// ignore
}

. {
	fataltex(
		"The character with ascii code ",
		int2str( (int) yytext[0] ),
		"\nis not a valid Latex input character.",
		NULL
	);
}

%%
/****************************************************************************/

static char Token[MAX_TOKEN_NUMBER][MAX_TOKEN_LENGTH];
static int  TokenLine[MAX_TOKEN_NUMBER];
static int  TokenStart = 0;
static int  TokenNext  = 0;

static void SetTexLval(const char *token, const char *str)
{	int i;

	assert( token != NULL );

	if( DEBUG_TOKENS )
		printf("\nTexLex(%s) ", token);

	texlval.line  = LatexMacroInputLine();

	if( str == NULL )
		texlval.str = NULL;
	else	texlval.str = str_alloc(str);

	texlval.data  = 0;
	texlval.extra = NULL;
	texlval.next  = NULL;

	// copy the token into the next slot
	i = strlen(token);
	if( i >= MAX_TOKEN_LENGTH )
		i = MAX_TOKEN_LENGTH - 1;

	Token[TokenNext][i] = '\0';
	while( i > 0 )
	{	--i;
		Token[TokenNext][i] = token[i];
	}
	TokenLine[TokenNext] = LatexMacroInputLine();

	// increment the next and start pointers
	TokenNext = (TokenNext + 1) % MAX_TOKEN_NUMBER;
	if( TokenStart == TokenNext )
		TokenStart = (TokenStart + 1) % MAX_TOKEN_NUMBER;
	assert( TokenStart != TokenNext );


	if( Cmd_Bracket_Mode == '[' )
		Cmd_Bracket_Mode = '\0';

	return;

}

void LatexLexPut(int line, const char *input)
{
	LatexMacroUserInput(line, input);

	TokenStart  = 0;
	TokenNext   = 0;
	return;
}


int LatexLexHistory(int number, int length, int *line, char **token)
{	int ntoken;
	int i;
	int next;

	ntoken = 0;
	next   = TokenNext;
	while( next != TokenStart && ntoken < number )
	{	next--;
		if( next < 0 )
			next = MAX_TOKEN_NUMBER - 1;

		i = strlen(Token[next]);
		if( i >= length )
			i = length - 1;
		token[ntoken][i] = 0;
		while( i > 0 )
		{	--i;
			token[ntoken][i] = Token[next][i];
		}
		line[ntoken] = TokenLine[next];
		ntoken++;
	}
	return ntoken;
}
