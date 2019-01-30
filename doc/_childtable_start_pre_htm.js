// Child table for section start_pre
document.write('\
<select onchange="start_pre_child(this)">\
<option>start_pre-&gt;</option>\
<option>pre_example</option>\
</select>\
');
function start_pre_child(item)
{	var child_list = [
		'pre_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
