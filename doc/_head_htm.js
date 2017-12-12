var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'titles+headings.htm',
'head.htm'
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
'begin.htm',
'section.htm',
'title.htm',
'head.htm'
];
var list_current0 = [
'head.htm#Syntax',
'head.htm#See Also',
'head.htm#Description',
'head.htm#Cross Reference Linking',
'head.htm#Aindex',
'head.htm#Example Heading',
'head.htm#Topic',
'head.htm#Example Subheading',
'head.htm#Example Subheading.Topic',
'head.htm#Reference'
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
