// Child table for section table
document.write('\
<select onchange="table_child(this)">\
<option>table-&gt;</option>\
<option>align</option>\
</select>\
');
function table_child(item)
{	var child_list = [
		'align.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
