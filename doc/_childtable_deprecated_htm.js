// Child table for section deprecated
document.write('\
<select onchange="deprecated_child(this)">\
<option>deprecated-&gt;</option>\
<option>wspace</option>\
<option>xref</option>\
<option>fend</option>\
<option>syntax</option>\
<option>math</option>\
<option>number</option>\
<option>path</option>\
</select>\
');
function deprecated_child(item)
{	var child_list = [
		'wspace.htm',
		'xref.htm',
		'fend.htm',
		'syntax.htm',
		'math.htm',
		'number.htm',
		'path.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
