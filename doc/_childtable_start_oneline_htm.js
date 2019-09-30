// Child table for section start_oneline
document.write('\
<select onchange="start_oneline_child(this)">\
<option>start_oneline-&gt;</option>\
<option>near_equal_f</option>\
</select>\
');
function start_oneline_child(item)
{	var child_list = [
		'near_equal_f.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
