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
'start_embed.htm'
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
'view_near_equal_c.htm',
'near_equal_c.htm',
'view_near_equal_f.htm',
'near_equal_f.htm'
];
var list_current0 = [
'start_embed.htm#begin, end',
'start_embed.htm#A Language with Block Structured Comments',
'start_embed.htm#A Language with Block Structured Comments.near_equal_c.c',
'start_embed.htm#A Language with Block Structured Comments.Example In This Web Site Context',
'start_embed.htm#A Language with Block Structured Comments.Execute OMhelp',
'start_embed.htm#A Language with Block Structured Comments.Example by Itself',
'start_embed.htm#A Language with only One Line Comments',
'start_embed.htm#A Language with only One Line Comments.near_equal_f.f',
'start_embed.htm#A Language with only One Line Comments.Example In This Web Site Context',
'start_embed.htm#A Language with only One Line Comments.Execute OMhelp',
'start_embed.htm#A Language with only One Line Comments.Example by Itself'
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
