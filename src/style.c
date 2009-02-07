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
$begin style$$
$spell
	bgcolor
	textcolor
	AllocMem
$$

$section Output Style Command for Current Section$$

$head Syntax$$
$syntax%char *StyleCommand(SectionInfo *%S%)%$$

$head Purpose$$
Return a style command for the current section to the current output file.

$head Background Color$$
The value $syntax%%S%->style.bgcolor%$$ is used
for the background color in the style command.

$head Text Color$$
The value $syntax%%S%->style.textcolor%$$ is used
for the text color in the style command.

$head Link Color$$
The value $syntax%%S%->style.linkcolor%$$ is used
for the link color in the style command.

$head Memory$$
The return value is allocated using $xref/AllocMem/$$
and should be freed using $code FreeMem$$

$end
*/

# include <stdlib.h>

# include "style.h"
# include "StrCat.h"

char *StyleCommand(SectionInfo *S)
{	const char *bgcolor;
	const char *textcolor;
	const char *linkcolor;
	char *cmd;

	if( S->style.bgcolor == NULL )
		bgcolor = "white";
	else	bgcolor = S->style.bgcolor;

	if( S->style.textcolor == NULL )
		textcolor = "black";
	else	textcolor = S->style.textcolor;

	if( S->style.linkcolor == NULL )
		linkcolor = "purple";
	else	linkcolor = S->style.linkcolor;

	// note must use the same case for body as is used in the <body>
	// command for this section or the xml will not display correctly
	cmd = StrCat(
		__FILE__,
		__LINE__,
		"\n<style type='text/css'>\nbody { color : ",
		textcolor,
		" }\nbody { background-color : ",
		bgcolor,
		" }\nA:link { color : ",
		linkcolor,
		" }\nA:visited { color : ",
		linkcolor,
		" }\nA:active { color : ",
		linkcolor,
		" }\n</style>\n",
		NULL
	);
	return cmd;
}
