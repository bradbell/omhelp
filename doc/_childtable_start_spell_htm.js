// Child table for section start_spell
document.write('\
<select onchange="start_spell_child(this)">\
<option>start_spell-&gt;</option>\
<option>spell_example</option>\
</select>\
');
function start_spell_child(item)
{	var child_list = [
		'spell_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
