// Child table for section multiple_example_1
document.write('\
<select onchange="multiple_example_1_child(this)">\
<option>multiple_example_1-&gt;</option>\
<option>ChildTwoExample</option>\
</select>\
');
function multiple_example_1_child(item)
{	var child_list = [
		'childtwoexample.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
