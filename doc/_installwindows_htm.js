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
'installwindows.htm'
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
var list_current0 = [
'installwindows.htm#Using Cygwin and MinGw',
'installwindows.htm#Requirements',
'installwindows.htm#Requirements.7z',
'installwindows.htm#Requirements.cmake',
'installwindows.htm#Requirements.Visual Studio',
'installwindows.htm#Requirements.Optional',
'installwindows.htm#Download OMhelp',
'installwindows.htm#Create Distribution Directory',
'installwindows.htm#CMake Command',
'installwindows.htm#CMake Command.boost_regex_prefix',
'installwindows.htm#CMake Command.source_highlight_prefix',
'installwindows.htm#CMake Command.have_flex_and_bison',
'installwindows.htm#CMake Command.omhelp_prefix',
'installwindows.htm#CMake Command.omhelp_datadir',
'installwindows.htm#CMake Command.omhelp_c_flags',
'installwindows.htm#CMake Command.omhelp_build_type',
'installwindows.htm#Build Executable',
'installwindows.htm#OMhelp Documentation',
'installwindows.htm#OMhelp Documentation.Developer Documentation',
'installwindows.htm#OMhelp Documentation.User Documentation',
'installwindows.htm#Install OMhelp',
'installwindows.htm#Getting Started',
'installwindows.htm#Spelling List',
'installwindows.htm#Spelling List.english.wrd',
'installwindows.htm#Spelling List.local.wrd',
'installwindows.htm#Spelling List.dictionary.bin'
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
