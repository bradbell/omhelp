var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'latex.htm',
'latexmacro.htm'
];
var list_down2 = [
'license.htm',
'why.htm',
'install.htm',
'get_started.htm',
'running.htm',
'files.htm',
'titles+headings.htm',
'cross.htm',
'format.htm',
'spellchecking.htm',
'latex.htm',
'other.htm',
'browser.htm',
'glossary.htm',
'wish_list.htm',
'whatsnew.htm'
];
var list_down1 = [
'symbol.htm',
'diacritical.htm',
'stdfun.htm',
'subsup.htm',
'frac.htm',
'sqrt.htm',
'array.htm',
'left_right.htm',
'under_over.htm',
'stackrel.htm',
'latexfont.htm',
'latexcomment.htm',
'latexmacro.htm',
'mathml.htm',
'diff_xml_htm.htm'
];
var list_current0 = [
'latexmacro.htm#Syntax',
'latexmacro.htm#Syntax.Definition',
'latexmacro.htm#Syntax.Usage',
'latexmacro.htm#Definition',
'latexmacro.htm#Definition.Global Scope',
'latexmacro.htm#Definition.Section Scope',
'latexmacro.htm#Definition.Name',
'latexmacro.htm#Definition.Text',
'latexmacro.htm#Definition.M',
'latexmacro.htm#Definition.N',
'latexmacro.htm#Definition.JK',
'latexmacro.htm#Usage',
'latexmacro.htm#Examples',
'latexmacro.htm#Examples.No Arguments',
'latexmacro.htm#Examples.Two Arguments',
'latexmacro.htm#Examples.Using Pound Sign in a Macro',
'latexmacro.htm#Examples.Recursion',
'latexmacro.htm#Examples.Mathml',
'latexmacro.htm#Restrictions',
'latexmacro.htm#Nonstandard'
];
function choose_across0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_across0[index-1];
}
function choose_up0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_up0[index-1];
}
function choose_down2(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down2[index-1];
}
function choose_down1(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down1[index-1];
}
function choose_down0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down0[index-1];
}
function choose_current0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_current0[index-1];
}
