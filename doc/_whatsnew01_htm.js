var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'whatsnew.htm',
'whatsnew01.htm'
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
'whatsnew04.htm',
'whatsnew03.htm',
'whatsnew02.htm',
'whatsnew01.htm'
];
var list_current0 = [
'whatsnew01.htm#Description',
'whatsnew01.htm#12-07',
'whatsnew01.htm#12-05',
'whatsnew01.htm#12-04',
'whatsnew01.htm#10-16',
'whatsnew01.htm#09-19',
'whatsnew01.htm#08-20',
'whatsnew01.htm#08-16',
'whatsnew01.htm#08-14',
'whatsnew01.htm#08-09',
'whatsnew01.htm#08-08',
'whatsnew01.htm#08-07',
'whatsnew01.htm#07-24',
'whatsnew01.htm#07-21',
'whatsnew01.htm#07-18',
'whatsnew01.htm#07-17',
'whatsnew01.htm#07-07',
'whatsnew01.htm#07-06',
'whatsnew01.htm#06-29',
'whatsnew01.htm#06-27',
'whatsnew01.htm#06-26',
'whatsnew01.htm#06-24',
'whatsnew01.htm#06-23',
'whatsnew01.htm#06-22',
'whatsnew01.htm#06-21',
'whatsnew01.htm#06-19',
'whatsnew01.htm#06-18',
'whatsnew01.htm#06-16',
'whatsnew01.htm#06-15',
'whatsnew01.htm#06-14',
'whatsnew01.htm#06-13',
'whatsnew01.htm#06-09',
'whatsnew01.htm#06-04',
'whatsnew01.htm#06-01',
'whatsnew01.htm#05-31',
'whatsnew01.htm#05-30',
'whatsnew01.htm#05-29',
'whatsnew01.htm#05-24',
'whatsnew01.htm#05-18',
'whatsnew01.htm#05-12',
'whatsnew01.htm#05-11',
'whatsnew01.htm#05-09',
'whatsnew01.htm#04-22'
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
