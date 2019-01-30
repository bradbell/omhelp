var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'whatsnew.htm'
];
var list_current0 = [
'whatsnew.htm#Introduction',
'whatsnew.htm#19-01-29',
'whatsnew.htm#19-01-26',
'whatsnew.htm#19-01-18',
'whatsnew.htm#18-11-16',
'whatsnew.htm#18-11-15',
'whatsnew.htm#18-10-31',
'whatsnew.htm#18-05-13',
'whatsnew.htm#18-03-13',
'whatsnew.htm#18-03-11',
'whatsnew.htm#17-06-28',
'whatsnew.htm#17-01-08',
'whatsnew.htm#16-10-04',
'whatsnew.htm#16-09-26',
'whatsnew.htm#16-06-25',
'whatsnew.htm#16-04-19',
'whatsnew.htm#16-02-14',
'whatsnew.htm#16-02-06',
'whatsnew.htm#16-02-04',
'whatsnew.htm#16-02-01',
'whatsnew.htm#15-10-14',
'whatsnew.htm#15-10-12',
'whatsnew.htm#15-10-11',
'whatsnew.htm#15-10-10',
'whatsnew.htm#15-10-08',
'whatsnew.htm#15-10-07',
'whatsnew.htm#15-06-03',
'whatsnew.htm#15-06-02',
'whatsnew.htm#15-05-31',
'whatsnew.htm#15-01-18',
'whatsnew.htm#15-01-10',
'whatsnew.htm#14-11-27',
'whatsnew.htm#14-11-23',
'whatsnew.htm#14-11-21',
'whatsnew.htm#14-07-27',
'whatsnew.htm#14-07-20',
'whatsnew.htm#14-07-17',
'whatsnew.htm#14-05-26',
'whatsnew.htm#13-01-16',
'whatsnew.htm#13-01-02',
'whatsnew.htm#12-05-09',
'whatsnew.htm#12-02-24',
'whatsnew.htm#12-02-12',
'whatsnew.htm#12-01-25',
'whatsnew.htm#10-10-20',
'whatsnew.htm#10-07-05',
'whatsnew.htm#10-09-02',
'whatsnew.htm#10-02-25',
'whatsnew.htm#09-05-12',
'whatsnew.htm#09-03-28',
'whatsnew.htm#09-03-24',
'whatsnew.htm#09-02-24',
'whatsnew.htm#09-02-12',
'whatsnew.htm#09-02-10',
'whatsnew.htm#09-02-08',
'whatsnew.htm#09-02-07',
'whatsnew.htm#09-02-06',
'whatsnew.htm#09-02-01',
'whatsnew.htm#09-01-31',
'whatsnew.htm#09-01-28',
'whatsnew.htm#08-10-01',
'whatsnew.htm#08-07-08',
'whatsnew.htm#08-04-11',
'whatsnew.htm#08-03-22',
'whatsnew.htm#08-03-21',
'whatsnew.htm#07-12-13',
'whatsnew.htm#07-11-03',
'whatsnew.htm#07-10-20',
'whatsnew.htm#07-10-18',
'whatsnew.htm#07-09-14',
'whatsnew.htm#07-08-14',
'whatsnew.htm#07-07-21',
'whatsnew.htm#07-04-06',
'whatsnew.htm#07-03-25',
'whatsnew.htm#07-03-13',
'whatsnew.htm#07-01-28',
'whatsnew.htm#06-12-23',
'whatsnew.htm#06-12-09',
'whatsnew.htm#06-09-30',
'whatsnew.htm#06-09-27',
'whatsnew.htm#06-09-19',
'whatsnew.htm#06-09-18',
'whatsnew.htm#06-09-16',
'whatsnew.htm#06-09-13',
'whatsnew.htm#06-08-30',
'whatsnew.htm#06-08-29',
'whatsnew.htm#06-08-28',
'whatsnew.htm#06-08-17',
'whatsnew.htm#06-08-15',
'whatsnew.htm#06-08-11',
'whatsnew.htm#06-07-25',
'whatsnew.htm#06-07-12',
'whatsnew.htm#06-07-08',
'whatsnew.htm#06-07-07',
'whatsnew.htm#06-06-30',
'whatsnew.htm#06-04-11',
'whatsnew.htm#06-04-10',
'whatsnew.htm#06-04-09',
'whatsnew.htm#06-04-08',
'whatsnew.htm#06-04-07',
'whatsnew.htm#06-03-14',
'whatsnew.htm#06-03-09',
'whatsnew.htm#06-03-03',
'whatsnew.htm#06-02-10',
'whatsnew.htm#06-01-25',
'whatsnew.htm#06-01-07',
'whatsnew.htm#06-01-06',
'whatsnew.htm#05-12-16',
'whatsnew.htm#05-12-06',
'whatsnew.htm#05-11-08',
'whatsnew.htm#05-10-27',
'whatsnew.htm#05-10-22',
'whatsnew.htm#05-10-05',
'whatsnew.htm#05-09-24',
'whatsnew.htm#05-08-15',
'whatsnew.htm#05-08-14',
'whatsnew.htm#05-07-05',
'whatsnew.htm#05-06-29',
'whatsnew.htm#05-06-26',
'whatsnew.htm#05-06-24',
'whatsnew.htm#05-05-18',
'whatsnew.htm#05-02-17',
'whatsnew.htm#05-02-15',
'whatsnew.htm#05-02-13',
'whatsnew.htm#05-02-10',
'whatsnew.htm#05-02-05'
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
