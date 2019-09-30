// Child table for section cref_example
document.write('\
<select onchange="cref_example_child(this)">\
<option>cref_example-&gt;</option>\
<option>cref_child_1</option>\
<option>cref_child_2</option>\
</select>\
');
function cref_example_child(item)
{	var child_list = [
		'cref_child_1.htm',
		'cref_child_2.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
