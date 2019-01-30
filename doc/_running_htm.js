var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'running.htm'
];
var list_current0 = [
'running.htm#Syntax',
'running.htm#Purpose',
'running.htm#Output File Names',
'running.htm#Output File Names.index.html',
'running.htm#Exit Status',
'running.htm#root_file',
'running.htm#debug',
'running.htm#debug.Input Files',
'running.htm#debug.External Links',
'running.htm#debug.Spelling Errors',
'running.htm#xml',
'running.htm#xml.Displaying MathML',
'running.htm#printable',
'running.htm#noframe',
'running.htm#nowarn',
'running.htm#image_link',
'running.htm#image_file',
'running.htm#favicon',
'running.htm#site',
'running.htm#omhelp_dir',
'running.htm#Example'
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
