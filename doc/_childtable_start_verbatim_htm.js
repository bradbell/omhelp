// Child table for section start_verbatim
document.write('\
<select onchange="start_verbatim_child(this)">\
<option>start_verbatim-&gt;</option>\
<option>verbatim_example</option>\
</select>\
');
function start_verbatim_child(item)
{	var child_list = [
		'verbatim_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
