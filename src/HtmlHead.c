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
$begin HtmlHead$$
$spell
	favicon
	rel
	png
	href
	javascript
	js
	Html
	OMhelp
$$

$section Output The HTML Header for a Section$$

$head Syntax$$
$syntax%void OutputHtmlHead(SectionInfo *%F%)%$$

$head Purpose$$
Outputs the HTML $code <head>$$ record for an OMhelp section.

$head Title$$
A $code <title>$$ record is output with the following value
$syntax%
	%F->title%
%$$.

$head Description$$
A $code <meta>$$ record is output with the following values
$syntax%
	name="description"
	id="description"
	content="%F->title%"
%$$


$head Icon$$
If the function $code FaviconSpecified$$ returns true
(non zero),
A $code <link>$$ record is output with the following values
$codep
	rel="icon"
	type="image/png"
	href="_favicon.png"
$$
Otherwise, no such link record is output.

$head Keywords$$
A $code <meta>$$ record is output with the following values
$syntax%
	name="keywords"
	id="keywords"
	content="%F->keywords%"
%$$

$head Style$$
The $xref/style//StyleCommand/$$ function is used to determine
a style record that is also output as part of the header.

$head Script$$
If $code NoFrame()$$ is true, declare
$syntax%
	_%F->tagLower%_%ext%.js
%$$
to be the javascript file for this section
where $italic ext$$ is $code Internal2Out("OutputExtension")$$
with out the leading "." character.


$end
---------------------------------------------------------------------------
*/
# include <stdlib.h>
# include <assert.h>

# include "main.h"
# include "section.h"
# include "output.h"
# include "convert.h"
# include "Internal2Out.h"
# include "style.h"
# include "allocmem.h"
# include "StrCat.h"

void OutputHtmlHead(SectionInfo *F)
{	char *stylecmd;

	// Title
	OutputString("<head>\n<title>");
	ConvertOutputString(F->title, 0);
	OutputString("</title>");

	// Use title for description
	OutputString(
		"\n<meta name=\"description\" id=\"description\" content=\""
	);
	ConvertOutputString(F->title, 0);
	OutputString("\"");
	OutputString(Internal2Out("SelfTerminateCmd"));

	// Link
	// use method suggested at http://www.w3.org/2005/10/howto-favicon
	if( FaviconSpecified() )
	{	OutputString(
		"\n<link rel='icon' type='image/png' href='_favicon.png'"
		);
		OutputString(Internal2Out("SelfTerminateCmd"));
	}

	// Keywords
	if( F->keywords != NULL )
	{	OutputString(
		"\n<meta name=\"keywords\" id=\"keywords\" content=\""
		);
		ConvertOutputString(F->keywords, 0);
		OutputString("\"");
		OutputString(Internal2Out("SelfTerminateCmd"));
	}

	// Style
	stylecmd = StyleCommand(F);
	OutputString(stylecmd);
	FreeMem(stylecmd);

	// Script
	if( NoFrame() )
	{	char *name;
		const char *ext = Internal2Out("OutputExtension");
		assert( *ext == '.' );
		ext++;

		// name of the Javascript file for drop down links.
		name = StrCat(
			__FILE__,
			__LINE__,
			"_",
			F->tagLower,
			"_",
			ext,
			".js",
			NULL
		);

		FormatOutput( 
			"<script type='text/javascript' "
			"language='JavaScript' src='%s'>\n</script>\n",
			name	
		);
		FreeMem(name);
	}
	OutputString("</head>\n");
}
