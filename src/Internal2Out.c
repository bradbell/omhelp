// BEGIN SHORT COPYRIGHT
/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2010 Bradley M. Bell

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
$begin Internal2Out$$
$spell
	const
$$

$index Internal2Out$$
$mindex output file representation$$

$section Maps Strings From Internal Meaning To Output File Representation$$

$table
$bold Syntax$$
$cend $syntax%void Internal2OutSet(const char *%out%)%$$          $rnext
$cend $syntax%const char *Internal2Out(const char *%internal%)%$$ 
$tend

$end

$fend 25$$

$head Description
$syntax/Internal2OutSet/
/$$
sets the current output file type to $itlaic out$$ where
$italic out$$ is equal to $code htm$$ or $code xml$$. 
$syntax/

/StrInternal2Out(/internal/)
/$$
The argument $italic internal$$ must be one of the internal 
$xref/glossary/String/strings/$$
listed in the table below.
The return value it is one of the output strings listed in the 
table below
(and depends on the output file type).


$head Table$$
The table below lists the possible values for $italic internal$$
and corresponding return value for $code Internal2Out$$.
Note that the output values depend on the output file type.

$table
$bold Internal$$   $cnext $bold htm$$  $cnext $bold xml$$
$rnext
OutputExtension    $cnext .htm         $cnext .xml
$rnext
HtmlOnlyExtension  $cnext .htm         $cnext _xml.htm
$rnext
SelfTerminateCmd   $cnext >            $cndex />
$rnext
StartOutputFile    $cndex <html>       $cnext

$pre <?xml version='1.0'?>
<?xml-stylesheet type='text/xsl' href='pmathml.xsl'?>
<html xmlns='http://www.w3.org/1999/xhtml'> $$

$tend             

*/

# include "Internal2Out.h"
# include <string.h>
# include <assert.h>

# include <stdio.h>


static char *Table[] = {
"NonBreakingSpace",  "&nbsp;",   "&#xA0;",
"OutputExtension",     ".htm",     ".xml",
"HtmlOnlyExtension",   ".htm", "_xml.htm",
"SelfTerminateCmd",       ">",       "/>",
"StartOutputFile",   "<html>", 
	"<?xml version='1.0'?>\n"
	"<html xmlns='http://www.w3.org/1999/xhtml'\n"
	"      xmlns:math='http://www.w3.org/1998/Math/MathML'\n"
	">\n"
};
static const unsigned int TableSize   = sizeof(Table) / sizeof(Table[0]);
static const unsigned int NumberOfCol = 3;
static unsigned int OutputCol         = 0;

void Internal2OutSet(const char *out)
{
	if( strcmp(out, "htm") == 0 )
		OutputCol = 2;
	else if( strcmp(out, "xml") == 0 )
		OutputCol = 3;
	else	assert(0);

}

const char *Internal2Out(const char *internal)
{	unsigned int i;

	assert( OutputCol == 2 || OutputCol == 3 );

	for(i = 0; i < TableSize; i += NumberOfCol)
		if( strcmp(Table[i], internal) == 0 )
			return Table[i + OutputCol - 1];

	assert(0);
	return NULL;
}
