// Child table for section start_font
document.write('\
<select onchange="start_font_child(this)">\
<option>start_font-&gt;</option>\
<option>font_example</option>\
</select>\
');
function start_font_child(item)
{	var child_list = [
		'font_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
