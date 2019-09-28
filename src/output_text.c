/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin output_text_dev$$
$spell
	const
$$

$section Outputting Text$$

$head Syntax$$
$codei%int output_text(
	int         %line%        ,
	const char *%s%           ,
	int         %pre%         ,
	char        %skip%        ,
	int         %check_spell% ,
	const char *%error_color% )%$$

$head Purpose$$
Outputs text converting the characters to HTML (or XML) format
and also checking for spelling errors.

$head line$$
The argument $icode line$$ specifies the current input file line number
(where the corresponding text started).

$head s$$
The argument $icode s$$ contains the text that is to be output.

$head pre$$
The argument $icode pre$$ is either zero, one, or two.

$subhead zero$$.
If $icode pre$$ is zero, the text being output is not pre-formatted.

$subhead one$$
If $icode pre$$ is one,
the output is changed to be non-wrapping white space.
This is pre-formatted just in the sense that white space is significant,
the font is not changed to be uniformly spaced.

$subhead two$$
If $icode pre$$ is two,
the output is pre-formatted text and the current output formatting is
already pre-formatted..

$head skip$$
The argument $icode skip$$ specifies a character that is not included in the
output; i.e., it is skipped.
(Use $code '\0'$$ if there is no such character.)

$head check_spell$$
The argument $icode check_spell$$ is either true or false.
If it is true, the output is spell checked, otherwise it is not.

$head error_color$$
The argument $icode error_color$$ specifies the color
to use for reporting spelling errors.

$head Return Value$$
The return value is the line number where the text ended; i.e.
the line corresponding to the last element of $icode s$$.

$end
*/

# include "spell.h"
# include "main.h"
# include "convert.h"
# include "output.h"
# include "input.h"

# include <stddef.h>
# include <string.h>
# include <assert.h>
# include <stdio.h>
# include <ctype.h>

int output_text(
	int         line        ,
	const char *s           ,
	int         pre         ,
	char        skip        ,
	int         check_spell ,
	const char *error_color )
{	assert( 0 <= pre && pre <= 2 );

	const char *bad = NULL;
	int nchar;

	assert(error_color != NULL );

	if( *s == '\0' ) return line;

	if( pre == 1 )
	{	// a standard compliant way to inhibit line breaks at
		// '-' in MS Internet Explorer (should not be necessary)
		// (also done in color_switch.c).
		OutputString("<span style='white-space: nowrap'>");
	}

	while( *s != '\0' )
	{
		if( check_spell )
			bad = SpellingError(s, &nchar);

		if( bad == NULL )
			bad = s + strlen(s);

		while( s < bad )
		{	line += (*s == '\n');
			if( *s != skip )
				ConvertOutputCh(*s, pre);
			s++;
		}

		assert( bad != NULL );
		if( *bad != '\0' )
		{
			assert( nchar > 0 );
			if( PostWarnings() )
			{	printf(
					"\nOMhelp Warning: spelling "
					"in line %d of file %s: ",
					line,
					InputName()
				);
				OutputString("<font color=\"");
				OutputString(error_color);
				OutputString("\">");

				while( nchar-- )
				{
					if( isspace((int) *s) )
						printf(" ");
					else	printf("%c", *s);

					line += (*s == '\n');
					ConvertOutputCh(*s++, pre);
				}
				OutputString("</font>");
				printf("\n");
			}
			else	while( nchar-- )
			{
				line += (*s == '\n');
				if( *s != skip )
					ConvertOutputCh(*s, pre);
				s++;
			}
		}
	}
	if( pre == 1 )
		OutputString("</span>");

	return line;
}
