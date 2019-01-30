// Child table for section other
document.write('\
<select onchange="other_child(this)">\
<option>other-&gt;</option>\
<option>comment</option>\
<option>date</option>\
<option>deprecated</option>\
</select>\
');
function other_child(item)
{	var child_list = [
		'comment.htm',
		'date.htm',
		'deprecated.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
