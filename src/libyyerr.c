/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/* libyyerror - flex run-time support library "yyerror" function */

/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignored
 */

# if 0
void yyerror( msg )
char msg[];
	{
	}
# endif

# include "pending.h"
# include "fatalerr.h"
# include "int2str.h"
# include "LatexLexHistory.h"
# include "str_alloc.h"
# include "allocmem.h"

void omherror( char msg[] )
{
	fatalomh(
		"OMhelp parsing error.",
		NULL
	);
}

void texerror( char msg[] )
{	int TexInitialNumberPending(void);

	// check for expected termination of a pending command
	if( NumberPending() != TexInitialNumberPending() )
		TexPendingError("Latex parsing error.");

	// otherwise no more help is avaliable
	fataltex(
		"Latex parsing error.",
		NULL
	);
}
