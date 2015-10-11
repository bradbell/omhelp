/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin math$$
$spell
	int
	preformatted
	ge
	le
	ntoken
$$

$section Outputting Text in Math Mode$$

$table
$bold Syntax$$ $cend
$codei%OutputMath(int %ntoken%,  char *%text%, char %escape%, int %italic%)%$$
$tend

$head Description$$
The character vector $italic text$$ contains $italic ntoken$$
'\0' terminated character strings (that is there is a single
'\0' between each of the strings and $italic ntoken$$ '\0' characters).
These strings are written to the current output file in math mode.
This is preformatted output with the extra feature that
letters are in an italic font while other characters are in a
normal font.
$pre

$$
Italic font can be suppressed by directly preceding a
sequence of letters by the character $italic escape$$
If the sequences of letters is "ge",
it is converted to a greater than or equals sign.
If the sequence of letters is "le",
it is converted to a less than or equals sign.
$pre

$$
If the integer $italic italic$$ is zero,
the font is not italic on input and output from $code OutputMath$$.
If the integer $italic italic$$ is not zero,
the font is italic on input and output from $code OutputMath$$.

$end
*/

# include <ctype.h>
# include <string.h>
# include "output.h"
# include "convert.h"
# include "math.h"

// is current mode italic
static int ItalicMode;

static void OutputMathch(char ch)
{	int pre = 1;

	if( ch == '\n' )
	{	if( ItalicMode )
			OutputString("</i>");
		ItalicMode = 0;

		ConvertOutputCh(ch, pre);

		return;
	}

	if( isalpha((int) ch) )
	{	if( ! ItalicMode )
		{	OutputString("<i>");
			ItalicMode = 1;
		}
	}
	else if( ItalicMode )
	{	OutputString("</i>");
		ItalicMode = 0;
	}

	ConvertOutputCh(ch, pre);
	return;
}

void OutputMath(int ntoken, char *s, char escape, int italic)
{	int i;
	int  pre = 1;

	// initialize ItalicMode
	if( italic )
		OutputString("</i>");
	ItalicMode = 0;

	// set fixed pitch font
	OutputString("<code>");

	// a standard compliant way to inhibit line breaks at
	// '-' in MS Internet Explorer (should not be necessary)
	OutputString("<span style='white-space: nowrap'>");

	for(i = 0; i < ntoken; i++)
	{
		while( *s != '\0' )
		{	char ch = *s++;

			// output this character
			if( (ch == escape) & (s[0] != '\n') )
			{
				if( s[0] == escape )
				{	ConvertOutputCh(ch, pre);
					s = s + 1;
				}
				else if( s[0] == 'g' && s[1] == 'e'
				&& ! isalpha((int) s[2]) )
				{	OutputString("<u>&gt;</u>");
					s = s + 2;
					ConvertAddColumn(1);
				}
				else if( s[0] == 'l' && s[1] == 'e'
				&& ! isalpha((int) s[2]) )
				{	OutputString("<u>&lt;</u>");
					s = s + 2;
					ConvertAddColumn(1);
				}
				else
				{	if( ItalicMode )
						OutputString("</i>");
					ItalicMode = 0;
					ch = *s++;
					while( isalpha((int) ch) )
					{	ConvertOutputCh(ch, pre);
						ch = *s++;
					}
					s = s - 1;
				}
			}
			else	OutputMathch(ch);

		}
		s++;
	}
	if( ItalicMode != italic )
		OutputString("</i>");

	OutputString("</span>");
	OutputString("</code>");

	if( italic )
		OutputString("</i>");

	return;
}
