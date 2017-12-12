var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'overview.htm',
'install.htm',
'installunix.htm'
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
'installunix.htm',
'installwindows.htm'
];
var list_down0 = [
'highlight.sh.htm'
];
var list_current0 = [
'installunix.htm#Requirements',
'installunix.htm#Requirements.source-highlight',
'installunix.htm#Requirements.Octave',
'installunix.htm#Requirements.flex, bison',
'installunix.htm#Download OMhelp',
'installunix.htm#Create Distribution Directory',
'installunix.htm#CMake Command',
'installunix.htm#CMake Command.boost_regex_prefix',
'installunix.htm#CMake Command.source_highlight_prefix',
'installunix.htm#CMake Command.have_flex_and_bison',
'installunix.htm#CMake Command.omhelp_prefix',
'installunix.htm#CMake Command.omhelp_datadir',
'installunix.htm#CMake Command.omhelp_c_flags',
'installunix.htm#CMake Command.omhelp_build_type',
'installunix.htm#Build Executable',
'installunix.htm#OMhelp Documentation',
'installunix.htm#OMhelp Documentation.Developer Documentation',
'installunix.htm#OMhelp Documentation.User Documentation',
'installunix.htm#Install OMhelp',
'installunix.htm#Getting Started',
'installunix.htm#Spelling List',
'installunix.htm#Spelling List.english.wrd',
'installunix.htm#Spelling List.local.wrd',
'installunix.htm#Spelling List.dictionary.bin',
'installunix.htm#Vim Editor'
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
