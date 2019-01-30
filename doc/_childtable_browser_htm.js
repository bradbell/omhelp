// Child table for section browser
document.write('\
<select onchange="browser_child(this)">\
<option>browser-&gt;</option>\
<option>Firefox</option>\
<option>Explorer</option>\
</select>\
');
function browser_child(item)
{	var child_list = [
		'firefox.htm',
		'explorer.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
