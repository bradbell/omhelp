// Child table for section start_block
document.write('\
<select onchange="start_block_child(this)">\
<option>start_block-&gt;</option>\
<option>near_equal_c</option>\
</select>\
');
function start_block_child(item)
{	var child_list = [
		'near_equal_c.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
