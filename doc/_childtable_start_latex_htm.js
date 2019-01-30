// Child table for section start_latex
document.write('\
<select onchange="start_latex_child(this)">\
<option>start_latex-&gt;</option>\
<option>latex_example</option>\
</select>\
');
function start_latex_child(item)
{	var child_list = [
		'latex_example.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
