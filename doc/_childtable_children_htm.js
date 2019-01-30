// Child table for section children
document.write('\
<select onchange="children_child(this)">\
<option>children-&gt;</option>\
<option>next</option>\
<option>previous</option>\
<option>stdout</option>\
</select>\
');
function children_child(item)
{	var child_list = [
		'next.htm',
		'previous.htm',
		'stdout.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
