// Child table for section index_example_1
document.write('\
<select onchange="index_example_1_child(this)">\
<option>index_example_1-&gt;</option>\
<option>index_example_2</option>\
<option>Index3Example</option>\
</select>\
');
function index_example_1_child(item)
{	var child_list = [
		'index_example_2.htm',
		'index3example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
