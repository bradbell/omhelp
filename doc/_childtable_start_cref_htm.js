// Child table for section start_cref
document.write('\
<select onchange="start_cref_child(this)">\
<option>start_cref-&gt;</option>\
<option>cref_example_1</option>\
</select>\
');
function start_cref_child(item)
{	var child_list = [
		'cref_example_1.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
