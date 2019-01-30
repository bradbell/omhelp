// Child table for section cross
document.write('\
<select onchange="cross_child(this)">\
<option>cross-&gt;</option>\
<option>Keyword</option>\
<option>cref</option>\
<option>href</option>\
<option>rref</option>\
<option>tref</option>\
<option>mref</option>\
<option>navigate</option>\
</select>\
');
function cross_child(item)
{	var child_list = [
		'keyword.htm',
		'cref.htm',
		'href.htm',
		'rref.htm',
		'tref.htm',
		'mref.htm',
		'navigate.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
