/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin style_dev$$
$spell
	bgcolor
	textcolor
	AllocMem
	linkcolor
	visitcolor
$$

$section Output Style Command for Current Section$$

$head Syntax$$
$codei%char *StyleCommand(SectionInfo *%S%)%$$

$head Purpose$$
Return a style command for the current section to the current output file.

$head Background Color$$
The value $icode%S%->style.bgcolor%$$ is used
for the background color in the style command.

$head Text Color$$
The value $icode%S%->style.textcolor%$$ is used
for the text color in the style command.

$head Link Color$$
The value $icode%S%->style.linkcolor%$$ is used
for the link color in the style command.

$head Visited Color$$
The value $icode%S%->style.visitcolor%$$ is used
for the visited link color in the style command.

$head Memory$$
The return value is allocated using $cref AllocMem_dev$$
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
	const char *visitcolor;
	char *cmd;

	if( S->style.bgcolor == NULL )
		bgcolor = "white";
	else	bgcolor = S->style.bgcolor;

	if( S->style.textcolor == NULL )
		textcolor = "black";
	else	textcolor = S->style.textcolor;

	if( S->style.linkcolor == NULL )
		linkcolor = "blue";
	else	linkcolor = S->style.linkcolor;

	if( S->style.visitcolor == NULL )
		visitcolor = "purple";
	else	visitcolor = S->style.linkcolor;

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
		visitcolor,
		" }\nA:active { color : ",
		visitcolor,
		" }\n</style>\n",
		NULL
	);
	return cmd;
}
