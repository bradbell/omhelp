// Child table for section cref_example_1
document.write('\
<select onchange="cref_example_1_child(this)">\
<option>cref_example_1-&gt;</option>\
<option>cref_example_2</option>\
<option>Cref3Example</option>\
</select>\
');
function cref_example_1_child(item)
{	var child_list = [
		'cref_example_2.htm',
		'cref3example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
