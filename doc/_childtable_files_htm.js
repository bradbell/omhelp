// Child table for section files
document.write('\
<select onchange="files_child(this)">\
<option>files-&gt;</option>\
<option>children</option>\
<option>include</option>\
<option>image</option>\
<option>verbatim</option>\
<option>srcfile</option>\
<option>srccode</option>\
<option>execute</option>\
<option>KeyCharacter</option>\
</select>\
');
function files_child(item)
{	var child_list = [
		'children.htm',
		'include.htm',
		'image.htm',
		'verbatim.htm',
		'srcfile.htm',
		'srccode.htm',
		'execute.htm',
		'keycharacter.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
