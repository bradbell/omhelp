// Child table for section start_multiple
document.write('\
<select onchange="start_multiple_child(this)">\
<option>start_multiple-&gt;</option>\
<option>multiple_example_1</option>\
<option>multiple_example_2</option>\
</select>\
');
function start_multiple_child(item)
{	var child_list = [
		'multiple_example_1.htm',
		'multiple_example_2.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
