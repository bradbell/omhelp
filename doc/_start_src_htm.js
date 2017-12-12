var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'get_started.htm',
'start_src.htm'
];
var list_down2 = [
'license.htm',
'why.htm',
'install.htm',
'get_started.htm',
'running.htm',
'files.htm',
'titles+headings.htm',
'cross.htm',
'format.htm',
'spellchecking.htm',
'latex.htm',
'other.htm',
'browser.htm',
'glossary.htm',
'wish_list.htm',
'whatsnew.htm'
];
var list_down1 = [
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
var list_down0 = [
'src_example.htm'
];
var list_current0 = [
'start_src.htm#srcfile',
'start_src.htm#srccode',
'start_src.htm#Execute The Following Steps',
'start_src.htm#Execute The Following Steps.src_example.omh',
'start_src.htm#Execute The Following Steps.Example In This Web Site Context',
'start_src.htm#Execute The Following Steps.Execute OMhelp',
'start_src.htm#Execute The Following Steps.Example by Itself'
];
function choose_across0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_across0[index-1];
}
function choose_up0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_up0[index-1];
}
function choose_down2(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down2[index-1];
}
function choose_down1(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down1[index-1];
}
function choose_down0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down0[index-1];
}
function choose_current0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_current0[index-1];
}
