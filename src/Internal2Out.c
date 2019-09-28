/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin Internal2Out_dev$$
$spell
	const
	htm
	xml
	Str
	Html
	Cmd
	jax
	inline
$$

$index Internal2Out$$
$mindex output file representation$$

$section Maps Strings From Internal Meaning To Output File Representation$$

$head Syntax$$
$codei%void Internal2OutSet(const char *%out%)
%$$
$codei%const char *Internal2Out(const char *%internal%)%$$

$head Internal2OutSet$$
sets the current output file type to $icode out$$ where
$icode out$$ is equal to $code htm$$ or $code xml$$.

$subhead html$$
If $icode out$$ is $code htm$$ we can that the output files type is
$code htm$$.

$subhead xml$$
If $icode out$$ is $code xml$$ we can that the output files type is
$code xml$$.

$head Internal2Out$$
The argument $icode internal$$ must be one of the internal
$cref/strings/glossary_dev/String/$$
listed in the table below.
The return value it is one of the output strings listed in the
table below
(and depends on the output file type).



$head Table$$
The table below lists the possible values for $icode internal$$
and corresponding return value for $code Internal2Out$$.
Note that the output values depend on the output file type.

$table
$bold Internal$$   $cnext $bold htm$$  $cnext $bold xml$$
$rnext
OutputExtension    $cnext $code .htm$$ $cnext $code .xml$$
$rnext
HtmlOnlyExtension  $cnext $code .htm$$ $cnext $code _xml.htm$$
$rnext
SelfTerminateCmd   $cnext $code >$$    $cnext $code />$$
$rnext
StartOutputFile
	$cnext $italic Htm Start$$ $pre  $$
	$cnext $italic Xml Start$$
$rnext
math_jax_begin_inline  $cnext $code @(@ $$ $cnext error
$rnext
math_jax_end_inline    $cnext $code @)@ $$ $cnext error
$rnext
math_jax_begin_display $cnext $code @[@ $$ $cnext error
$rnext
math_jax_end_display   $cnext $code @]@ $$ $cnext error
$tend

$head Htm Start$$
$nospell
$codep
<script type='text/x-mathjax-config'>
MathJax.Hub.Config({
  tex2jax: {
    inlineMath:  [ ['@(@','@)@'] ] ,
    displayMath: [ ['@[@','@]@'] ]
  }
});
</script>
<script type='text/javascript' src=
'https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=default'
>
</script>
$$
$$

$head Xml Start$$
$nospell
$codep
<?xml version='1.0'?>
<?xml-stylesheet type='text/xsl' href='pmathml.xsl'?>
<html xmlns='http://www.w3.org/1999/xhtml'>
$$
$$

$end
*/

# include "Internal2Out.h"
# include <string.h>
# include <assert.h>

# include <stdio.h>


static char *Table[] = {
"NonBreakingSpace",        "&nbsp;",   "&#xA0;",
"OutputExtension",         ".htm",     ".xml",
"HtmlOnlyExtension",       ".htm",     "_xml.htm",
"SelfTerminateCmd",        ">",        "/>",
"math_jax_begin_inline",   "@(@",      "",
"math_jax_end_inline",     "@)@",      "",
"math_jax_begin_display",  "@[@",      "",
"math_jax_end_display",    "@]@",      "",
"StartOutputFile",

"<html>\n"
"<script type='text/x-mathjax-config'>\n"
"MathJax.Hub.Config({\n"
"  tex2jax: {\n"
"    inlineMath:  [ ['@(@','@)@'] ] ,\n"
"    displayMath: [ ['@[@','@]@'] ]\n"
"  }\n"
"});\n"
"</script>\n"
"<script type='text/javascript' src=\n"
"'https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=default'\n"
">\n"
"</script>\n"

,
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
		{	const char* ret = Table[i + OutputCol - 1];
			assert( strcmp(ret, "") != 0 );
			return ret;
		}

	assert(0);
	return NULL;
}
