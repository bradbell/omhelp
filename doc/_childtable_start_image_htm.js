// Child table for section start_image
document.write('\
<select onchange="start_image_child(this)">\
<option>start_image-&gt;</option>\
<option>image_example</option>\
</select>\
');
function start_image_child(item)
{	var child_list = [
		'image_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
