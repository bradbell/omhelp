// Child table for section start_src
document.write('\
<select onchange="start_src_child(this)">\
<option>start_src-&gt;</option>\
<option>src_example</option>\
</select>\
');
function start_src_child(item)
{	var child_list = [
		'src_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
