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
/*
=============================================================================
$begin ConvertNewline$$
$escape #$$
$spell 
	const
	int 
	Newline
$$

$index CovertForcedNewline$$
$cindex new line #in output file$$

$section Outputs the New Line in HTML format$$

$table
$bold Syntax$$ 
$cend $syntax/void ConvertForcedNewline(const int /n/)/$$  $rend
$tend

$fend 25$$

$head Description$$
Outputs $italic n$$ forced new lines; i.e., new lines
that are not just white space
but actually cause line breaks when the HTML is viewed.
For example, in pre-formatted mode, every '\n' is converted to
a forced new line.


$end
==============================================================================
$begin ConvertOutput$$
$escape #$$
$spell
	const
	ch
$$

$index ConvertOutputCh$$
$index ConvertOutputString$$
$cindex convert special character #in output$$

$section Convert Special Characters and Output Text in HTML Format$$ 

$table 
$bold Syntax$$
$cend 
$syntax/void ConvertOutputCh(const char /ch/, const int /pre/)/$$
$rend $cend 
$syntax%void ConvertOutputString(const char *%s%, const int %pre%)%$$
$tend

$fend 25$$

$head ConvertOutputCh$$
Output the character $italic ch$$
to the current output file.

$head ConvertOutputString$$
This just calls $code ConvertOutputCh$$ for each element
of the $code '\0'$$ terminated character vector $italic s$$ 
excluding the $code '\0'$$ (which is the last element of $italic s$$).


$head Always Converted$$
If $italic ch$$ (or a character in $italic s$$) 
is one of the special characters,
$code <$$,
$code >$$,
$code &$$,
$code "$$,
it is converted to its representation in HTML.

$head Special Symbols$$
The ascii character codes 
$code COPYRIGHT_CHARACTER$$ and 
$code REGISTERED_TRADE_MARK_CHARACTER$$,
are defined in $code convert.h$$.
If $italic ch$$ (or a character in $italic s$$) 
is equal to one of these codes
it is converted to the corresponding output in HTML format.


$head Pre-formatted Output$$
If $italic pre$$ is equal one,
the space, tab, and new line characters,
are converted so that they are visible
when the HTML file is viewed in a browser.
Otherwise, $italic pre$$ must be equal to zero.

$end
==============================================================================
$begin ConvertAddColumn$$
$escape #$$
$spell
	const
	ch
$$

$index ConvertAddColumn$$
$cindex correct column #when bypassing ConvertOutputCh$$

$section Correct Column Count When Bypassing ConvertOutputCh$$

$table
$bold Syntax$$
$cend $syntax/int ConvertAddColumn(const int /add/)/$$ $rend
$bold See Also$$
$cend $mref/ConvertSetTabSize/ConvertOutput/$$
$tend

$fend 25$$


$head Description$$
The routines listed in $xref/convert/$$
keep track of the current output column number.
This is used for
converting tab characters in pre-formatted mode.
The routine $code ConvertAddColumn$$
is used when the current output column changes because
of output that does not use one of the $xref/convert/$$ routines.
Calling $code ConvertAddColumn$$, adds the value $italic add$$ to
the current output column number and returns the resulting column.
The call
$syntax/
	ConvertAddColumn(-ConvertAddColumn(0))
/$$
can be used to set the current column to zero.

$end
==============================================================================
$begin ConvertSetTabSize$$
$spell
	const
	Ch
$$
$escape #$$

$index ConvertSetTabSize$$
$cindex tab character column number$$ 

$section Set the Number of Columns Corresponding to a Tab Character$$

$table
$bold Syntax$$
$cend $syntax/void ConvertSetTabSize(const int /size/)/$$ $rend
$bold See Also$$
$cend $mref/ConvertAddColumn/ConvertOutput/$$
$tend

$fend 25$$

$head Description$$
The routines $code ConvertOutputCh$$ and $code ConvertOutputString$$
convert tab characters to the proper number of spaces
(when in pre-format mode).
This routine sets the number of characters between each
of the columns that correspond to a tab character.


$end
==============================================================================
$begin ConvertPreviousNewline$$
$spell
	newline
	newlines
$$

$index newline$$
$index ConvertPreviousNewline$$

$section Determine Number of Previous New Lines$$

$table
$bold Syntax$$
$cnext $syntax/int ConvertPreviousNewline()/$$ $rnext
$cnext $syntax/void ConvertAddPrevious(int /n/)/$$
$tend

$fend 25$$

$syntax/

ConvertPreviousNewline()
/$$
Returns the number of newlines, since the previous non white space character,
that were output by any of the 
$xref/convert/Convert Routines/convert routines/$$.

$syntax/

ConvertAddPrevious(/n/)
/$$
The value $italic n$$ is added to the previous newline counter.
If newlines are output by routines other than the
$xref/convert/Convert Routines/convert routines/$$,
a positive value of $italic n$$ will adjust for this.
$pre

$$
If non-white space is output by routines other than 
the convert routines, the function call 
$codep
	ConvertAddPrevious(- ConvertPreviousNewline() )
$$
will reset the previous newline counter to zero.
$pre

$$
If $italic n$$ is greater than zero, the current 
$xref/ConvertAddColumn//column counter/$$ is set to zero.


$end
===========================================================================
$begin ConvertInternalString$$
$escape #$$
$spell
	Mem
	const
	ch
$$

$index ConvertInternalString$$
$mindex convert special character format$$

$section Internal Conversion of Special Characters (no output)$$ 

$table 
$bold Syntax$$
$cend 
$syntax%char *ConvertInternalString(const char *%s%)%$$ $rnext
$bold See Also$$
$xref/ConvertOutput/$$
$tend

$fend 25$$

$head Description$$
The return value is a copy of $italic s$$ with certain characters converted.
If a character in $italic s$$ 
is one of the special characters,
$code <$$,
$code >$$,
$code &$$,
$code "$$,
$code COPYRIGHT_CHARACTER$$ or 
$code REGISTERED_TRADE_MARK_CHARACTER$$,
it is converted to its representation in HTML.
The ascii character codes 
$code COPYRIGHT_CHARACTER$$ and 
$code REGISTERED_TRADE_MARK_CHARACTER$$,
are defined in $code convert.h$$.

$head Memory$$
The return value is allocated with $xref/AllocMem/$$ and should be freed
with $xref/AllocMem/FreeMem/FreeMem/$$ when it is no longer needed.


$end
===========================================================================
*/

# include "allocmem.h"
# include "convert.h"
# include "output.h"
# include "Internal2Out.h"
# include <assert.h>
# include <ctype.h>
# include <stdio.h>
# include <string.h>


// number of columns corresponding to a tab character
static int TabSize = 5;

// previous output column
static int Column = 0;

// newline output counter
static int NewlineOutput = 0;


// ====================================================================
void ConvertForcedNewline(const int n)
{	int i;
	for(i = 0; i < n; i++)
	{	OutputString("<br");
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");
		Column = 0;
	}
	NewlineOutput += n;
	return;
}

int ConvertPreviousNewline()
{	return NewlineOutput;
}

void ConvertAddPrevious(int n)
{	NewlineOutput += n;
	if( NewlineOutput < 0 )
		NewlineOutput = 0;

	if( n > 0 )
		Column = 0;
}

int ConvertAddColumn(const int n)
{	Column = Column + n;
	return Column;
}

void ConvertSetTabSize(const int size)
{	TabSize = size;
}

void ConvertOutputCh(const char ch, const int preformatted)
{
	int ntab;

	switch(ch)
	{	case '<':
		OutputString("&lt;");   // lt = x60
		break;

		case '>':
		OutputString("&gt;");   // gt = x62
		break;

		case '&':
		OutputString("&amp;");  // amp = x26
		break;

		case '"':
		OutputString("&quot;"); // quot = x22
		break;

		case REGISTERED_TRADE_MARK_CHARACTER:
		OutputString("&#174;");
		break;

		case COPYRIGHT_CHARACTER:
		OutputString("&#169;");
		break;

		default:
		if( preformatted )
		{	switch(ch)
			{
				case ' ':
				// non-breaking space
				OutputString(
					Internal2Out("NonBreakingSpace")
				);
				Column++;
				break;
				
				case '\t':
				ntab = TabSize - Column % TabSize;
				if( ntab == 0 ) ntab = TabSize;
				Column = Column + ntab;
				while( ntab-- ) OutputString(
					Internal2Out("NonBreakingSpace")
				);
				break;
				
				case '\n':
				ConvertForcedNewline(1);
				break;

				default:
				OutputChar(ch);
				Column++;
				break;
			}
		}
		else
		{	if( Column != 0 || ! isspace((int) ch) )
			{	OutputChar(ch);
				Column++;
			}
		}

		if( ! isspace((int) ch) )
			NewlineOutput = 0;

		break;
	}
	return;
}

void ConvertOutputString(const char *s, const int preformatted)
{	
	while ( *s != '\0' )
		ConvertOutputCh( *s++, preformatted );
}

static char InternalCh[] = {'\0', '\0'};
static const char *ConvertInternalCh(char ch)
{
	const char *result;

	switch(ch)
	{	case '<':
		result = "&lt;";   // lt = x60
		break;

		case '>':
		result = "&gt;";   // gt = x62
		break;

		case '&':
		result = "&amp;";  // amp = x26
		break;

		case '"':
		result = "&quot;"; // quot = x22
		break;

		case REGISTERED_TRADE_MARK_CHARACTER:
		result = "&#174;";
		break;

		case COPYRIGHT_CHARACTER:
		result = "&#169;";
		break;


		default:
		InternalCh[0]  = ch;
		result         = InternalCh;
	}

	return result;
}

char *ConvertInternalString(const char *s)
{	int   len;
	int     i;

	char      *result;
	const char  *stmp;
	const char    *Ch;
	

	stmp = s;
	len  = 0;
	while ( *stmp != '\0' )
	{	Ch   = ConvertInternalCh( *stmp++);
		len += strlen( Ch );
	}

	result = AllocMem(sizeof(char), len + 1);

	i    = 0;
	stmp = s;
	while ( *stmp != '\0' )
	{	Ch   = ConvertInternalCh( *stmp++ );

		while ( *Ch != '\0' )
			result[i++] = *Ch++;

	}

	assert( i == len );

	result[i] = '\0';

	return result;
}
