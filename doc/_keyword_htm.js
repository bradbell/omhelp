var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'cross.htm',
'keyword.htm'
];
var list_current0 = [
'keyword.htm#Syntax',
'keyword.htm#See Also',
'keyword.htm#Description',
'keyword.htm#The Keyword Index',
'keyword.htm#Keyword List',
'keyword.htm#Escape Character',
'keyword.htm#Headings',
'keyword.htm#Headings.Example',
'keyword.htm#Index',
'keyword.htm#Index.Example',
'keyword.htm#Mindex',
'keyword.htm#Mindex.Example',
'keyword.htm#Aindex',
'keyword.htm#Aindex.Excluded Words',
'keyword.htm#Aindex.Root Section',
'keyword.htm#Aindex.Example',
'keyword.htm#Cindex',
'keyword.htm#Cindex.Example'
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
