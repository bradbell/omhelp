/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin HtmlHead_dev$$
$spell
	http
	equiv
	charset
	utf
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
$codei%void OutputHtmlHead(SectionInfo *%F%)%$$

$head Purpose$$
Outputs the HTML $code <head>$$ record for an OMhelp section.

$head Title$$
A $code <title>$$ record is output with the following value
$codei%
	%F->title%
%$$.

$head Character Encoding$$
A $code <meta>$$ record is output with the following values
$codei%
	http-equiv='Content-Type'
	content='text/html'
	charset='utf-8'
%$$

$head Description$$
A $code <meta>$$ record is output with the following values
$codei%
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
$codei%
	name="keywords"
	id="keywords"
	content="%F->keywords%"
%$$

$head Style$$
The $cref/StyleCommand/style_dev/$$ function is used to determine
a style record that is also output as part of the header.

$head Script$$
If $code NoFrame()$$ is true, declare
$codei%
	_%F->tagLower%_%ext%.js
%$$
to be the javascript file for this section
where $icode ext$$ is $code Internal2Out("OutputExtension")$$
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

	// Declare character type as ascii
	OutputString(
	"\n<meta http-equiv='Content-Type' content='text/html' charset='utf-8'"
	);
	OutputString(Internal2Out("SelfTerminateCmd"));

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
