// Child table for section format
document.write('\
<select onchange="format_child(this)">\
<option>format-&gt;</option>\
<option>nobreak</option>\
<option>pre</option>\
<option>codep</option>\
<option>codei</option>\
<option>color</option>\
<option>hilite</option>\
<option>th</option>\
<option>center</option>\
<option>table</option>\
<option>list</option>\
<option>special</option>\
<option>font</option>\
</select>\
');
function format_child(item)
{	var child_list = [
		'nobreak.htm',
		'pre.htm',
		'codep.htm',
		'codei.htm',
		'color.htm',
		'hilite.htm',
		'th.htm',
		'center.htm',
		'table.htm',
		'list.htm',
		'special.htm',
		'font.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
