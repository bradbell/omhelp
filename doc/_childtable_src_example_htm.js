// Child table for section src_example
document.write('\
<select onchange="src_example_child(this)">\
<option>src_example-&gt;</option>\
<option>src_example.py</option>\
</select>\
');
function src_example_child(item)
{	var child_list = [
		'src_example.py.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
