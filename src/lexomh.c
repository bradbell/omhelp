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
Lexical analyizer for OMhelp commands
------------------------------------------------------------------------------
$begin CommandKeyCharacter$$
$dollar @$$
$spell
	OMhelp
	omhlex
$$


$section The Current Command Key Character$$

$table
$bold Syntax$$
$cnext $syntax%CommandKeyCharacter()%$$

$tend

$fend 20$$

$head Description$$
The user input
$syntax%
	@OMhelpKeyCharacter=%c%
%$$
changes the current command key character from $code @$$ to the
one specified by $italic c$$ where
$italic c$$ is not an alphabetic letter, a decimal digit, or 
white space.
The function
$syntax%
	CommandKeyCharacter()
%$$
returns the current command key character.

$head End of File$$
The current command key character is changed back to $code @$$ at
the end of every file; i.e., just before $code EOF_lex$$ is returned
by $code omhlex$$.
For this reason, the string portion of a $code EOF_lex$$ token
is set to the current key character just before the end of file.


$end
------------------------------------------------------------------------------
$begin TokenCode2String$$
$spell
	Mem
$$

$section Converting Integer Token Code to User Input$$

$table
$bold Syntax$$
$cnext $syntax%%string% = TokenCode2String(%code%)%$$
$tend

$fend 20$$

$head Purpose$$
The lexical analyzer now passes back token integer codes for error reporting.
This routine converts the integer code to the corresponding users input
(including the @ character).

$head code$$
The argument $italic code$$ has prototype
$syntax%
	int %code%
%$$
It is the integer code for the token to be converted.

$head string$$
The result $italic string$$ has prototype
$syntax%
	char *%string%
%$$
It points to memory that 
should be freed using the routine $xref/AllocMem/FreeMem/FreeMem/$$
when it is no longer needed.
If this memory is not freed,
a call to 
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$
will report the corresponding source code line in the routine
$code TokenCode2String$$. 

$end
*/

#ifdef WIN32
# include <conio.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

# include "strjoin.h"
# include "allocmem.h"
# include "input.h"
# include "fatalerr.h"
# include "str_alloc.h"
# include "OmhLexSetInputLine.h"
# include "BinarySearch.h"
# include "int2str.h"

# include "OmhStype.h"
# define YYSTYPE OmhStype

// include file for this file
# include "lexomh.h"

// automatically generated include file generated by yacc from omhelp.y
# include "omhelp.h"


// maximum number of characters in a token
# define MAX_TOKEN    100000

// debug execution of lexical analyzer
# define DEBUG_TOKENS 0

static char CommandKeyChar = '$';
char CommandKeyCharacter(void)
{	return CommandKeyChar; }

static enum state {
	EOF_state,
	EMPTY_state,
	KEY_state,
	BEGIN_state,
	CHANGE_state,
	OMHELP_state,
	LATEX_state
} State;   

static int Initialize  = 1;

static int CurrentLine;
static char Buffer[MAX_TOKEN];
static char Ch;


static struct
{	char *name;  // The keywords name
	int  code;   // The corresponding integer code defined by bison
}
keyword_table[] =
{
	{ "aindex",     AINDEX_lex      },
	{ "align",      ALIGN_lex       },
	{ "begin",      BEGIN_lex       },
	{ "bgcolor",    BGCOLOR_lex     },
	{ "big",        BIG_lex         },
	{ "bold",       BOLD_lex        },
	{ "cend",       CEND_lex        },
	{ "center",     CENTER_lex      },
	{ "children",   CHILDREN_lex    },
	{ "childtable", CHILDTABLE_lex  },
	{ "cindex",     CINDEX_lex      },
	{ "cmark",      CMARK_lex       },
	{ "cnext",      CNEXT_lex       },
	{ "code",       CODE_lex        },
	{ "codecolor",  CODECOLOR_lex   },
	{ "codei",      CODEI_lex       },
	{ "codep",      CODEP_lex       },
	{ "comment",    COMMENT_lex     },
	{ "contents",   CONTENTS_lex    },
	{ "cref",       CREF_lex        },
	{ "date",       DATE_lex        },
	{ "dollar",     DOLLAR_lex      },
	{ "end",        END_lex         },
	{ "errorcolor", ERRORCOLOR_lex  },
	{ "escape",     ESCAPE_lex      },
	{ "execute",    EXECUTE_lex     },
	{ "fend",       FEND_lex        },
	{ "fixed",      FIXED_lex       },
	{ "head",       HEAD_lex        },
	{ "hilitecmd",  HILITECMD_lex   },
	{ "hilitecolor",HILITECOLOR_lex },
	{ "hiliteseq",  HILITESEQ_lex   },
	{ "href",       HREF_lex        },
	{ "icode",      ICODE_lex       },
	{ "icon",       ICON_lex        },
	{ "image",      IMAGE_lex       },
	{ "include",    INCLUDE_lex     },
	{ "index",      INDEX_lex       },
	{ "italic",     ITALIC_lex      },
	{ "latex",      LATEX_lex       },
	{ "lend",       LEND_lex        },
	{ "linkcolor",  LINKCOLOR_lex   },
	{ "list",       LIST_lex        },
	{ "lnext",      LNEXT_lex       },
	{ "math",       MATH_lex        },
	{ "mindex",     MINDEX_lex      },
	{ "mref",       MREF_lex        },
	{ "navigate",   NAVIGATE_lex    },
	{ "newlinech",  NEWLINECH_lex   },
	{ "nobreak",    NOBREAK_lex     },
	{ "nospell",    NOSPELL_lex     },
	{ "path",       PATH_lex        },
	{ "pre",        PRE_lex         },
	{ "rend",       REND_lex        },
	{ "rmark",      RMARK_lex       },
	{ "rnext",      RNEXT_lex       },
	{ "rref",       RREF_lex        },
	{ "section",    SECTION_lex     },
	{ "skipnl",     SKIPNL_lex      },
	{ "small",      SMALL_lex       },
	{ "spell",      SPELL_lex       },
	{ "subhead",    SUBHEAD_lex     },
	{ "syntax",     SYNTAX_lex      },
	{ "table",      TABLE_lex       },
	{ "tabsize",    TABSIZE_lex     },
	{ "tend",       TEND_lex        },
	{ "textcolor",  TEXTCOLOR_lex   },
	{ "th",         TH_lex          },
	{ "title",      TITLE_lex       },
	{ "trace",      TRACE_lex       },
	{ "tref",       TREF_lex        },
	{ "verbatim",   VERBATIM_lex    },
	{ "visitcolor", VISITCOLOR_lex  },
	{ "wspace",     WSPACE_lex      },
	{ "xref",       XREF_lex        }
};
static int n_keyword   = sizeof keyword_table / sizeof keyword_table[0];
static const char *Key[  sizeof keyword_table / sizeof keyword_table[0] ];

char *TokenCode2String(int code)
{	int i;
	for(i = 0; i < n_keyword; i++)
		if( keyword_table[i].code == code )
			return strjoin("$", keyword_table[i].name);
	switch( code )
	{
		case ACCENT_lex:
		return str_alloc("$'");

		case EOF_lex:
		return str_alloc("eof");

		case DOUBLE_DOLLAR_lex:
		return str_alloc("$$");

		case NUMBER_lex:
		return str_alloc("$<number>");

		case TEXT_lex:
		return str_alloc("<text>");
	}
	assert(0);
	return str_alloc("<TokenCode2String: OMhelp program error.>");
}


// routine to set return value for parser (omhelp.y)
static void SetOmhLvalStr(int code, const char *token, const char *str)
{
	if( DEBUG_TOKENS )
		printf("\nLex(%s) ", token);

	omhlval.code = code;
	omhlval.line = CurrentLine;

	if( str == NULL )
		omhlval.str = NULL;
	else	omhlval.str  = str_alloc(str);


	CurrentLine = InputLine();

	return;

}
static void SetOmhLvalChar(int code, const char *token, char ch)
{	char str[2];
	str[0] = ch;
	str[1] = '\0';

	SetOmhLvalStr(code, token, str);
} 
/***************************************************************************/


int omhlex(void)
{	
	int  code;
	int  match;
	int  escape;
	int  i;

	int     eof  = 1;

	char *begin  = "begin";
	char *change = "OMhelpKeyCharacter=";

	int   beginLen  = strlen(begin);
	int   changeLen = strlen(change);


	if( Initialize )
	{	int i;
		for(i = 0; i < n_keyword; i++ )
		{	Key[i] = keyword_table[i].name;
			if( i > 0 )
				assert( strcmp( Key[i], Key[i-1] ) > 0 );
		}
		CurrentLine = 0;
		Ch          = InputGet();
		Initialize  = 0;
		State       = EMPTY_state;
	}

	// maybe opened new file since previous end of file
	if( Ch == eof )
		Ch = InputGet();

	switch( State )
	{
		case EMPTY_state:
		case EOF_state:
		while( State != OMHELP_state )
		{
			switch( State )
			{
				case EOF_state:
				{
					SetOmhLvalChar(
						EOF_lex, "eof", CommandKeyChar
					);
					State          = EMPTY_state;
					CommandKeyChar = '$';

					return EOF_lex;
				}
				break;

				case EMPTY_state:
				if( Ch == eof )
					State = EOF_state;
				if( Ch == CommandKeyChar )
					State = KEY_state;
				break; 

				case KEY_state:
				if( Ch == eof )
					State = EOF_state;
				else if( Ch == begin[0] )
					State = BEGIN_state;
				else if( Ch == change[0] )
					State = CHANGE_state;
				else	State = EMPTY_state;
				break;

				case BEGIN_state:
				match = 1;
				while( State == BEGIN_state )
				{	if( Ch == eof )
						State = EOF_state;
					else if( Ch == CommandKeyChar )
						State = KEY_state;
					else if( Ch == begin[match] )
						match++;
					else 	State = EMPTY_state;

					if( match == beginLen )
						State = OMHELP_state;

					Ch = InputGet();
				}
				break;

				case CHANGE_state:
				match = 1;
				while( (0 < match) & (match < changeLen) )
				{	if( Ch == eof )
						State = EOF_state;
					else if( Ch == CommandKeyChar )
						State = KEY_state;
					else if( Ch == change[match] )
						match++;
					else 	State = EMPTY_state;

					Ch = InputGet();
				}
				if( State == CHANGE_state )
				{
					if( isalpha(Ch)) fatalomh(
						"Attempt to set the command "
						"key character to a letter "
						"in A-Z or a-z.",
						NULL
					);
					if( isspace(Ch)) fatalomh(
						"Attempt to set the command "
						"key character to a white "
						"space character.",
						NULL
					);
					if( isdigit(Ch)) fatalomh(
						"Attempt to set the command "
						"key character to a decimal "
						"digit.",
						NULL
					);
					if( Ch == eof ) fatalomh(
						"Attempt to set the command "
						"key character to the end of "
						"file character.",
						NULL
					);
					CommandKeyChar = Ch;

					Ch    = InputGet();
					State = EMPTY_state;
				}
				break;

				default:
				assert(0);
			}
			Ch = InputGet();
		}	
		assert( State == OMHELP_state );

		if( Ch == eof )
		{ 
			SetOmhLvalChar(EOF_lex, "eof", CommandKeyChar);
			CommandKeyChar = '$';
			return EOF_lex;
		}
		else
		{	CurrentLine = InputLine();
			SetOmhLvalStr(BEGIN_lex, begin, NULL);
			return BEGIN_lex;
		}
		break;  // ================================================

		case OMHELP_state:
		if( Ch == eof )
		{
			SetOmhLvalChar(EOF_lex, "eof", CommandKeyChar);
			CommandKeyChar = '$';
			return EOF_lex;
		}
		if( Ch == CommandKeyChar )
		{	// next input character
			Ch = InputGet();

			// check for double dollar ------------------------
			if( Ch == CommandKeyChar )
			{	char str[3];
				str[0] = CommandKeyChar;
				str[1] = CommandKeyChar;
				str[2] = '\0';

				Ch = InputGet();
				SetOmhLvalStr(DOUBLE_DOLLAR_lex, str, NULL);
				return DOUBLE_DOLLAR_lex;
			}

			// check for keyword ------------------------------
			match           = 0;
			Buffer[match++] = CommandKeyChar;
			while( isalpha(Ch) )
			{	Buffer[match++] = Ch;
				Ch              = InputGet();
				if( match >= MAX_TOKEN )
				{	Buffer[10] = '\0';
					fatalomh(
						"Keyword beginning with ",
						Buffer,
						" is longer than ",
						int2str(MAX_TOKEN),
						" characters long\n",
						NULL
					);
				}
			}
			Buffer[match] = '\0';

			// skip command key character when matching keywords
			i = BinarySearch(Key, n_keyword, Buffer+1);

			if( i < n_keyword )
			{	code = keyword_table[i].code;

				// check for a change of state
				if( code == LATEX_lex )
					State = LATEX_state;

				if( code == END_lex )
					State = EMPTY_state;

				// skip space following font keywords
				if( Ch == ' ' )
				{	if( (code == FIXED_lex)  |
					    (code == CODE_lex)   |
					    (code == SMALL_lex)  |
					    (code == BIG_lex)    |
					    (code == ITALIC_lex) |
					    (code == BOLD_lex) 
					)
					{	Ch = InputGet();
					}
				}

				SetOmhLvalStr(code, Buffer, NULL);
				return code;
			}
			else if( match > 1 ) fatalomh(
				Buffer, 
				" is an invalid keyword", 
				NULL
			);

			// check for an accent command
			if( Ch == '\'' )
			{	Ch              = InputGet();
				Buffer[match++] = Ch;
				Buffer[match++] = '\0';

				// Ch must be character following command
				Ch              = InputGet(); 

				SetOmhLvalStr(ACCENT_lex, Buffer, Buffer + 1);
				return ACCENT_lex;
			}


			// check for number following dollar -----------------
			if( isdigit(Ch) | (Ch=='.') | (Ch=='+') | (Ch=='-' ) )
			{
				while( 
					isdigit(Ch) | 
					(Ch == '.')   | 
					(Ch == '+')   | 
					(Ch == '-') 
				)
				{	Buffer[match++] = Ch;
					Ch              = InputGet();
					if( match >= MAX_TOKEN )
					{	Buffer[10] = '\0';
						fatalomh(
						"Number beginning with ",
						Buffer,
						" is longer than ",
						int2str(MAX_TOKEN),
						" characters long\n",
						NULL
						);
					}
				}
				Buffer[match] = '\0';
				assert( match > 1 );
				SetOmhLvalStr(NUMBER_lex, Buffer, Buffer + 1);

				return NUMBER_lex;
			}

			// not a valid command
			{	char str[2];
				str[0] = CommandKeyChar;
				str[1] = '\0';

				fatalomh(
				"The command key character ",
				str,
				"\nby itself is not a valid OMhelp token.",
				NULL
				);
			}
		}

		// get text
		match           = 0;
		Buffer[match++] = Ch;
		Ch              = InputGet();
		while( (Ch != eof) & (Ch != CommandKeyChar) )
		{	Buffer[match++] = Ch;
			Ch              = InputGet();
			if( match >= MAX_TOKEN )
			{	Buffer[10] = '\0';
				fatalomh(
					"Text beginning with ",
					Buffer,
					" is longer than ",
					int2str(MAX_TOKEN),
					" characters long\n",
					NULL
				);
			}
		}
		Buffer[match] = '\0';
		SetOmhLvalStr(TEXT_lex, Buffer, Buffer);
		return TEXT_lex;

		case LATEX_state: // =========================================
		if( Ch == eof )
		{
			SetOmhLvalChar(EOF_lex, "eof", CommandKeyChar);
			CommandKeyChar = '$';

			State = EMPTY_state;
			return EOF_lex;
		}

		// get text
		match           = 0;
		escape          = Ch == '\\';
		Buffer[match++] = Ch;
		Ch              = InputGet();
		while( (Ch != eof) & ((Ch != CommandKeyChar) | escape) )
		{	escape          = Ch == '\\';
			Buffer[match++] = Ch;
			Ch              = InputGet();
			if( match >= MAX_TOKEN )
			{	Buffer[10] = '\0';
				fatalomh(
					"Text beginning with ",
					Buffer,
					" is longer than ",
					int2str(MAX_TOKEN),
					" characters long\n",
					NULL
				);
			}
		}
		Buffer[match] = '\0';

		State = OMHELP_state;
		SetOmhLvalStr(TEXT_lex, Buffer, Buffer);
		return TEXT_lex;

		default:
		assert(0);
	}
	assert(0);
	return 0;
}

void OmhLexSetInputLine(int line)
{	CurrentLine = line; }
