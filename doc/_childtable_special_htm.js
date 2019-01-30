// Child table for section special
document.write('\
<select onchange="special_child(this)">\
<option>special-&gt;</option>\
<option>dollar</option>\
<option>cmark</option>\
<option>rmark</option>\
<option>newlinech</option>\
<option>accent</option>\
<option>escape</option>\
<option>tabsize</option>\
</select>\
');
function special_child(item)
{	var child_list = [
		'dollar.htm',
		'cmark.htm',
		'rmark.htm',
		'newlinech.htm',
		'accent.htm',
		'escape.htm',
		'tabsize.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
