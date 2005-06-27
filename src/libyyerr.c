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
# include "string.h"
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
