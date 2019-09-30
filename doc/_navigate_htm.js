var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'omhelp.htm',
'cross.htm',
'navigate.htm'
];
var list_down2 = [
'license.htm',
'why.htm',
'install.htm',
'get_started.htm',
'running.htm',
'files.htm',
'titles_headings.htm',
'cross.htm',
'format.htm',
'spellchecking.htm',
'latex.htm',
'other.htm',
'browser.htm',
'glossary.htm',
'wish_list.htm',
'whats_new.htm'
];
var list_down1 = [
'keyword.htm',
'cref.htm',
'href.htm',
'rref.htm',
'tref.htm',
'mref.htm',
'navigate.htm'
];
var list_current0 = [
'navigate.htm#Syntax',
'navigate.htm#Purpose',
'navigate.htm#Type',
'navigate.htm#Type.Content',
'navigate.htm#Type.Prev',
'navigate.htm#Type.Next',
'navigate.htm#Type.Across',
'navigate.htm#Type.Top',
'navigate.htm#Type.Up',
'navigate.htm#Type.Sibling',
'navigate.htm#Type.Down',
'navigate.htm#Type.Down_up_i',
'navigate.htm#Type.Current',
'navigate.htm#Type.Example',
'navigate.htm#Label',
'navigate.htm#Label.Default',
'navigate.htm#Label._up_i',
'navigate.htm#Label._jump_table',
'navigate.htm#Prev and Next',
'navigate.htm#No Such Section',
'navigate.htm#Default',
'navigate.htm#Example',
'navigate.htm#Root Section'
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
