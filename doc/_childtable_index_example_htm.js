// Child table for section index_example
document.write('\
<select onchange="index_example_child(this)">\
<option>index_example-&gt;</option>\
<option>index_child_1</option>\
<option>index_child_2</option>\
</select>\
');
function index_example_child(item)
{	var child_list = [
		'index_child_1.htm',
		'index_child_2.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
