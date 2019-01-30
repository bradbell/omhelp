// Child table for section start_embed
document.write('\
<select onchange="start_embed_child(this)">\
<option>start_embed-&gt;</option>\
<option>view_near_equal_c</option>\
<option>near_equal_c</option>\
<option>view_near_equal_f</option>\
<option>near_equal_f</option>\
</select>\
');
function start_embed_child(item)
{	var child_list = [
		'view_near_equal_c.htm',
		'near_equal_c.htm',
		'view_near_equal_f.htm',
		'near_equal_f.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
