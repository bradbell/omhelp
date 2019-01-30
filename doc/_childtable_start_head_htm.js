// Child table for section start_head
document.write('\
<select onchange="start_head_child(this)">\
<option>start_head-&gt;</option>\
<option>head_example</option>\
</select>\
');
function start_head_child(item)
{	var child_list = [
		'head_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
