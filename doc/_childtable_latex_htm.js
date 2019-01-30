// Child table for section latex
document.write('\
<select onchange="latex_child(this)">\
<option>latex-&gt;</option>\
<option>symbol</option>\
<option>diacritical</option>\
<option>stdfun</option>\
<option>subsup</option>\
<option>frac</option>\
<option>sqrt</option>\
<option>array</option>\
<option>left_right</option>\
<option>under_over</option>\
<option>stackrel</option>\
<option>latexfont</option>\
<option>latexcomment</option>\
<option>LatexMacro</option>\
<option>mathml</option>\
<option>diff_xml_htm</option>\
</select>\
');
function latex_child(item)
{	var child_list = [
		'symbol.htm',
		'diacritical.htm',
		'stdfun.htm',
		'subsup.htm',
		'frac.htm',
		'sqrt.htm',
		'array.htm',
		'left_right.htm',
		'under_over.htm',
		'stackrel.htm',
		'latexfont.htm',
		'latexcomment.htm',
		'latexmacro.htm',
		'mathml.htm',
		'diff_xml_htm.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
