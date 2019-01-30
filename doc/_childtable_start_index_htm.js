// Child table for section start_index
document.write('\
<select onchange="start_index_child(this)">\
<option>start_index-&gt;</option>\
<option>index_example_1</option>\
</select>\
');
function start_index_child(item)
{	var child_list = [
		'index_example_1.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
