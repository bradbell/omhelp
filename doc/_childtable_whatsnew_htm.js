// Child table for section whatsnew
document.write('\
<select onchange="whatsnew_child(this)">\
<option>whatsnew-&gt;</option>\
<option>whatsNew04</option>\
<option>whatsNew03</option>\
<option>whatsNew02</option>\
<option>whatsNew01</option>\
</select>\
');
function whatsnew_child(item)
{	var child_list = [
		'whatsnew04.htm',
		'whatsnew03.htm',
		'whatsnew02.htm',
		'whatsnew01.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
