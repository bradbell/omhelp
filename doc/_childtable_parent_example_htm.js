// Child table for section parent_example
document.write('\
<select onchange="parent_example_child(this)">\
<option>parent_example-&gt;</option>\
<option>child_1_example</option>\
<option>child_2_example</option>\
</select>\
');
function parent_example_child(item)
{	var child_list = [
		'child_1_example.htm',
		'child_2_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
