// Child table for section spellchecking
document.write('\
<select onchange="spellchecking_child(this)">\
<option>spellchecking-&gt;</option>\
<option>spell</option>\
<option>nospell</option>\
</select>\
');
function spellchecking_child(item)
{	var child_list = [
		'spell.htm',
		'nospell.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
