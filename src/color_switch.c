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
$begin color_switch$$

$section Switch Output Color at Each Delimiter$$

$head Syntax$$
$blueblack%void color_switch(
	char       *%text%             ,
	const char *%first_color%      ,
	const char *%second_color%     ,
	char        %escape%           ,
	int         %line%             ,
	int         %check_spell       ,
	int         %error_color       )%$$

$head Purpose$$
This routine outputs the specified text using a code font
(pre-formatted font)
while switching colors every time a delimiter is encountered.
In addition, if the color is black, the font is also italic.

$head text$$
The is the original text. It starts and ends with a delimiter
and the delimiter is not output. (The output value of this
text is unspecified; i.e., it may be modified.)

$head first_color$$
The is the color after the first delimiter, third delimiter,
and so on.

$head second_color$$
This is the color following the second delimiter, fourth delimiter,
and so on.

$head escape$$
Any occurances of the escape character in the text is not output
This enables the user to line up multiple lines of text where one
line has more delimiters than the other.

$head line$$
Line number where the corresponding omhelp command started
(for error reporting).

$head cmd$$
Name of the corresponding omhelp command
(for error reporting).

$head check_spell$$
The argument $blackblue check_spell$$ is either true or false.
If it is true, the output is spell checked, otherwise it is not.

$head error_color$$
The argument $blackblue error_color$$ specifies the color
to use for reporting spelling errors.

$end
*/
# include "color_switch.h"
# include "SplitText.h"
# include "output.h"
# include "output_text.h"

# include <assert.h>
# include <stddef.h>
# include <string.h>

void color_switch(
	char       *text            ,
	const char *first_color     ,
	const char *second_color    ,
	char        escape          ,
	int         line            ,
	const char *cmd             ,
	int   check_spell           ,
	const char *error_color     )
{
	const char *color;
	char *token;
	char *next;
	int  count;
	int  ntoken;
	int  pre = 1;

	assert( text != NULL );
	assert( first_color != NULL );
	assert( first_color != NULL );

	// split text into tokens
	ntoken = SplitText(line, cmd, text);

	// first token
	token = text + 1;

	// initialize delimter count flag
	count  = 1;

	// for each token
	OutputString("\n<code>");
	while( ntoken-- )
	{	next = token + strlen(token) + 1;
		if( count % 2 == 1 )
			color = first_color;
		else	color = second_color;
		if( strcmp(color, "black") == 0 )
			OutputString("<i>");
		OutputString("<font color=\"");
		OutputString(color);
		OutputString("\">");
		line = output_text(line, token, pre, escape,
			check_spell, error_color
		);
		OutputString("</font>");
		if( strcmp(color, "black") == 0 )
			OutputString("</i>");
		count++;
		token = next;
	}
	OutputString("</code>\n");
}
