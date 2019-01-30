// Child table for section keycharacter
document.write('\
<select onchange="keycharacter_child(this)">\
<option>keycharacter-&gt;</option>\
<option>KeyCharExample</option>\
</select>\
');
function keycharacter_child(item)
{	var child_list = [
		'keycharexample.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
