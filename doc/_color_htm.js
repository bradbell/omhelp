var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'format.htm',
'color.htm'
];
var list_current0 = [
'color.htm#Syntax',
'color.htm#Purpose',
'color.htm#command',
'color.htm#colorname',
'color.htm#RGB Values',
'color.htm#Style',
'color.htm#Root Section',
'color.htm#Non-Style Examples',
'color.htm#Non-Style Examples.codecolor',
'color.htm#Non-Style Examples.errorcolor',
'color.htm#Non-Style Examples.hilitecolor',
'color.htm#Style Examples',
'color.htm#Style Examples.bgcolor',
'color.htm#Style Examples.textcolor',
'color.htm#Style Examples.linkcolor'
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
