// Child table for section install
document.write('\
<select onchange="install_child(this)">\
<option>install-&gt;</option>\
<option>InstallUnix</option>\
<option>InstallWindows</option>\
</select>\
');
function install_child(item)
{	var child_list = [
		'installunix.htm',
		'installwindows.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
