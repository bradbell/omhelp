// Child table for section installunix
document.write('\
<select onchange="installunix_child(this)">\
<option>installunix-&gt;</option>\
<option>highlight.sh</option>\
</select>\
');
function installunix_child(item)
{	var child_list = [
		'highlight.sh.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
