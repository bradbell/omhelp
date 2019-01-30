// Child table for section symbol
document.write('\
<select onchange="symbol_child(this)">\
<option>symbol-&gt;</option>\
<option>latexnormal</option>\
<option>latexnumber</option>\
<option>latexspecial</option>\
<option>ellipsis</option>\
<option>greek</option>\
<option>BinaryOp</option>\
<option>RelationSym</option>\
<option>ArrowSym</option>\
<option>MiscSym</option>\
<option>DisplaySym</option>\
<option>space</option>\
</select>\
');
function symbol_child(item)
{	var child_list = [
		'latexnormal.htm',
		'latexnumber.htm',
		'latexspecial.htm',
		'ellipsis.htm',
		'greek.htm',
		'binaryop.htm',
		'relationsym.htm',
		'arrowsym.htm',
		'miscsym.htm',
		'displaysym.htm',
		'space.htm'
	];
	var index = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = child_list[index-1];
}
