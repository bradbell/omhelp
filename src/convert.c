/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
=============================================================================
$begin ConvertNewline_dev$$
$escape #$$
$spell
	const
	int
	Newline
$$

$index CovertForcedNewline$$
$cindex new line #in output file$$

$section Outputs the New Line in HTML format$$

$head Syntax$$
$codei/void ConvertForcedNewline(const int /n/)/$$


$head Description$$
Outputs $icode n$$ forced new lines; i.e., new lines
that are not just white space
but actually cause line breaks when the HTML is viewed.
For example, in pre-formatted mode, every '\n' is converted to
a forced new line.


$end
==============================================================================
$begin ConvertOutput_dev$$
$escape #$$
$spell
	const
	ch
	preformatted
	newline
$$

$index ConvertOutputCh$$
$index ConvertOutputString$$
$cindex convert special character #in output$$

$section Convert Special Characters and Output Text in HTML Format$$

$head Syntax$$
$codei/void ConvertOutputCh(const char /ch/, const int /preformatted/)
/$$
$codei%void ConvertOutputString(const char *%s%, const int %preformatted%)%$$


$head ConvertOutputCh$$
Output the character $icode ch$$
to the current output file.

$head ConvertOutputString$$
This just calls $code ConvertOutputCh$$ for each element
of the $code '\0'$$ terminated character vector $icode s$$
excluding the $code '\0'$$ (which is the last element of $icode s$$).


$head Always Converted$$
If $icode ch$$ (or a character in $icode s$$)
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
If $icode ch$$ (or a character in $icode s$$)
is equal to one of these codes
it is converted to the corresponding output in HTML format.


$head preformatted$$
The argument $icode preformatted$$ is either zero, one, or two.

$subhead zero$$
If $icode preformatted$$ is zero,
the space, tab, and new line characters,
are not converted (just output as is).
There is one exception, when the current output column is the
beginning of a line, tab, and newline are not output at all.

$subhead one$$
If $icode preformatted$$ is one,
the space, tab, and new line characters,
are converted so that each one is visible
when the HTML file is viewed in a browser.

$subhead two$$
If $icode preformatted$$ is two,
this text is preformatted and that both space and newline
are output as is.
The tab characters are converted to the corresponding number of spaces.

$end
==============================================================================
$begin ConvertAddColumn_dev$$
$escape #$$
$spell
	const
	ch
$$

$index ConvertAddColumn$$
$cindex correct column #when bypassing ConvertOutputCh$$

$section Correct Column Count When Bypassing ConvertOutputCh$$

$head Syntax$$
$codei/int ConvertAddColumn(const int /add/)/$$

$head See Also$$
$mref/ConvertSetTabSize_dev/ConvertOutput_dev/$$



$head Description$$
The routines listed in $cref convert_dev$$
keep track of the current output column number.
This is used for
converting tab characters in pre-formatted mode.
The routine $code ConvertAddColumn$$
is used when the current output column changes because
of output that does not use one of the $cref convert_dev$$ routines.
Calling $code ConvertAddColumn$$, adds the value $icode add$$ to
the current output column number and returns the resulting column.
The call
$codei/
	ConvertAddColumn(-ConvertAddColumn(0))
/$$
can be used to set the current column to zero.

$end
==============================================================================
$begin ConvertSetTabSize_dev$$
$spell
	const
	Ch
$$
$escape #$$

$index ConvertSetTabSize$$
$cindex tab character column number$$

$section Set the Number of Columns Corresponding to a Tab Character$$

$head Syntax$$
$codei/void ConvertSetTabSize(const int /size/)/$$

$head See Also$$
$mref/ConvertAddColumn_dev/ConvertOutput_dev/$$


$head Description$$
The routines $code ConvertOutputCh$$ and $code ConvertOutputString$$
convert tab characters to the proper number of spaces
(when in pre-format mode).
This routine sets the number of characters between each
of the columns that correspond to a tab character.


$end
==============================================================================
$begin ConvertPreviousNewline_dev$$
$spell
	newline
	newlines
$$

$index newline$$
$index ConvertPreviousNewline$$

$section Determine Number of Previous New Lines$$

$head Syntax$$
$codei/int ConvertPreviousNewline()
/$$
$codei/void ConvertAddPrevious(int /n/)/$$


$codei/

ConvertPreviousNewline()
/$$
Returns the number of newlines, since the previous non white space character,
that were output by any of the
$cref/convert routines/convert_dev/Convert Routines/$$.

$codei/

ConvertAddPrevious(/n/)
/$$
The value $icode n$$ is added to the previous newline counter.
If newlines are output by routines other than the
$cref/convert routines/convert_dev/Convert Routines/$$,
a positive value of $icode n$$ will adjust for this.
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
If $icode n$$ is greater than zero, the current
$cref/column counter/ConvertAddColumn_dev/$$ is set to zero.


$end
===========================================================================
$begin ConvertInternalString_dev$$
$escape #$$
$spell
	Mem
	const
	ch
$$

$index ConvertInternalString$$
$mindex convert special character format$$

$section Internal Conversion of Special Characters (no output)$$

$head Syntax$$
$codei%char *ConvertInternalString(const char *%s%)
%$$

$head See Also$$
$cref ConvertOutput_dev$$


$head Description$$
The return value is a copy of $icode s$$ with certain characters converted.
If a character in $icode s$$
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
The return value is allocated with $cref AllocMem_dev$$ and should be freed
with $cref/FreeMem/AllocMem_dev/FreeMem/$$ when it is no longer needed.


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
{	assert( 0 <= preformatted && preformatted <= 2);
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
		if( preformatted == 1 )
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
		else if( preformatted == 2 )
		{	switch(ch)
			{
				case '\t':
				ntab = TabSize - Column % TabSize;
				if( ntab == 0 ) ntab = TabSize;
				Column = Column + ntab;
				while( ntab-- )
					OutputChar(' ');
				break;

				case '\n':
				OutputChar(ch);
				Column = 0;
				NewlineOutput += 1;
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
