// Child table for section omhelp
document.write('\
<select onchange="omhelp_child(this)">\
<option>omhelp-&gt;</option>\
<option>License</option>\
<option>why</option>\
<option>Install</option>\
<option>get_started</option>\
<option>running</option>\
<option>files</option>\
<option>titles_headings</option>\
<option>cross</option>\
<option>format</option>\
<option>spellchecking</option>\
<option>latex</option>\
<option>other</option>\
<option>browser</option>\
<option>glossary</option>\
<option>wish_list</option>\
<option>whats_new</option>\
<option>_reference</option>\
<option>_index</option>\
<option>_search</option>\
<option>_external</option>\
</select>\
');
function omhelp_child(item)
{	var child_list = [
		'license.htm',
		'why.htm',
		'install.htm',
		'get_started.htm',
		'running.htm',
		'files.htm',
		'titles_headings.htm',
		'cross.htm',
		'format.htm',
		'spellchecking.htm',
		'latex.htm',
		'other.htm',
		'browser.htm',
		'glossary.htm',
		'wish_list.htm',
		'whats_new.htm',
		'_reference.htm',
		'_index.htm',
		'_search.htm',
		'_external.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
