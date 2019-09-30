// Child table for section start_multiple
document.write('\
<select onchange="start_multiple_child(this)">\
<option>start_multiple-&gt;</option>\
<option>parent_example</option>\
</select>\
');
function start_multiple_child(item)
{	var child_list = [
		'parent_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
