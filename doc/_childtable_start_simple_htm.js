// Child table for section start_simple
document.write('\
<select onchange="start_simple_child(this)">\
<option>start_simple-&gt;</option>\
<option>simple_example</option>\
</select>\
');
function start_simple_child(item)
{	var child_list = [
		'simple_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
