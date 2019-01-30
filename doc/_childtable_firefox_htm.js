// Child table for section firefox
document.write('\
<select onchange="firefox_child(this)">\
<option>firefox-&gt;</option>\
<option>NegativeSpace</option>\
</select>\
');
function firefox_child(item)
{	var child_list = [
		'negativespace.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
