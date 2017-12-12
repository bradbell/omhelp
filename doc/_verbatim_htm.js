var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'files.htm',
'verbatim.htm'
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
'path.htm',
'children.htm',
'include.htm',
'image.htm',
'verbatim.htm',
'srcfile.htm',
'srccode.htm',
'execute.htm',
'keycharacter.htm'
];
var list_current0 = [
'verbatim.htm#Syntax',
'verbatim.htm#See Also',
'verbatim.htm#Description',
'verbatim.htm#New Lines',
'verbatim.htm#Example File',
'verbatim.htm#Filename',
'verbatim.htm#Filename.Example',
'verbatim.htm#Highlighting',
'verbatim.htm#Indent',
'verbatim.htm#Indent.Example',
'verbatim.htm#Start',
'verbatim.htm#Stop',
'verbatim.htm#Stop.Example',
'verbatim.htm#Skip',
'verbatim.htm#Skip.Example',
'verbatim.htm#Tab Stops'
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
