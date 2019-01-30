// Child table for section titles+headings
document.write('\
<select onchange="titles+headings_child(this)">\
<option>titles+headings-&gt;</option>\
<option>begin</option>\
<option>section</option>\
<option>title</option>\
<option>head</option>\
</select>\
');
function titles+headings_child(item)
{	var child_list = [
		'begin.htm',
		'section.htm',
		'title.htm',
		'head.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
