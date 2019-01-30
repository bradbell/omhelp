// Child table for section get_started
document.write('\
<select onchange="get_started_child(this)">\
<option>get_started-&gt;</option>\
<option>start_simple</option>\
<option>start_head</option>\
<option>start_image</option>\
<option>start_pre</option>\
<option>start_font</option>\
<option>start_spell</option>\
<option>start_latex</option>\
<option>start_verbatim</option>\
<option>start_src</option>\
<option>start_embed</option>\
<option>start_multiple</option>\
<option>start_cref</option>\
<option>start_index</option>\
</select>\
');
function get_started_child(item)
{	var child_list = [
		'start_simple.htm',
		'start_head.htm',
		'start_image.htm',
		'start_pre.htm',
		'start_font.htm',
		'start_spell.htm',
		'start_latex.htm',
		'start_verbatim.htm',
		'start_src.htm',
		'start_embed.htm',
		'start_multiple.htm',
		'start_cref.htm',
		'start_index.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
