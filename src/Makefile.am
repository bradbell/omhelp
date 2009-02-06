# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# ---------------------------------------------------------------------------
#
# automake input file
#
BUILT_SOURCES = \
	omhelp.c \
	omhelp.h \
	latex.c \
	latex.h
#
# Microsoft project files
EXTRA_DIST = src.sln src.vcproj
#
bin_PROGRAMS   = omhelp
#
AM_CFLAGS  = -g -Wall 
#
omhelp_SOURCES = \
	AutomaticLink.h \
	AutoTag.h \
	BinarySearch.h \
	ClipWhiteSpace.h \
	Color.h \
	color_switch.h \
	DirSep.h \
	FileEqual.h \
	FrameSet.h \
	HtmlHead.h \
	InitParser.h \
	Internal2Out.h \
	LatexAtomic.h \
	LatexLexHistory.h \
	LatexLexPut.h \
	LatexMacro.h \
	OmhLexSetInputLine.h \
	OmhStype.h \
	PatternMatch.h \
	SplitText.h \
	StrCat.h \
	StrLowAlloc.h \
	StrLowCase.h \
	StrRemove.h \
	Tag2Title.h \
	TexStype.h \
	UniformWhiteSpace.h \
	allocmem.h \
	automatic.h \
	browser.h \
	children.h \
	content.h \
	convert.h \
	copyfile.h \
	cross.h \
	execute.h \
	fatalerr.h \
	funref.h \
	head.h \
	hilite.h \
	href.h \
	index.h \
	input.h \
	int2str.h \
	latex.h \
	lexomh.h \
	links.h \
	main.h \
	math.h \
	omhelp.h \
	omhparse.h \
	output.h \
	output_text.h \
	pending.h \
	relative.h \
	search.h \
	section.h \
	spell.h \
	str_alloc.h \
	strjoin.h \
	style.h \
	texparse.h \
	trace_exit.h \
	url.h \
	warning.h \
	AutomaticLink.c \
	BinarySearch.c \
	ClipWhiteSpace.c \
	Color.c \
	color_switch.c \
	DirSep.c \
	FileEqual.c \
	Internal2Out.c \
	LatexAtomic.c \
	LatexMacro.c \
	PatternMatch.c \
	SplitText.c \
	StrCat.c \
	StrLowCase.c \
	StrRemove.c \
	UniformWhiteSpace.c \
	alloca.c \
	allocate.c \
	allocmem.c \
	automatic.c \
	browser.c \
	children.c \
	content.c \
	convert.c \
	copyfile.c \
	cross.c \
	execute.c \
	fatalerr.c \
	FrameSet.c \
	funref.c \
	head.c \
	hilite.c \
	href.c \
	HtmlHead.c \
	index.c \
	input.c \
	int2str.c \
	latex.c \
	lexomh.c \
	lex.tex.c \
	libyyerr.c \
	libyywra.c \
	links.c \
	main.c \
	math.c \
	omhelp.c \
	output.c \
	output_text.c \
	pending.c \
	relative.c \
	search.c \
	section.c \
	style.c \
	spell.c \
	trace_exit.c \
	url.c \
	warning.c
#
# Rule for main.c (replace DATA_DIR in omhdir="DATA_DIR/OMhelp";)
main.c: main.src
	sed -e "s%DATA_DIR%$(datadir)%" < main.src > main.c
#
# Rule for omhelp.h
omhelp.h: omhelp.y
	bison omhelp.y --defines -p omh -o omhelp.c
	mv omhelp.c omhelp.tmp
	sed -f fixbison.sed < omhelp.tmp > omhelp.c
#
# Same rule for omhelp.c
omhelp.c: omhelp.y
	bison omhelp.y --defines -p omh -o omhelp.c
	mv omhelp.c omhelp.tmp
	sed -f fixbison.sed < omhelp.tmp > omhelp.c
#
# Rule for lex.tex.c
lex.tex.c: latex.l
	flex -Ptex latex.l
#
# Rule for latex.h
latex.h: latex.y
	bison latex.y --defines -p tex -o latex.c
	mv latex.c latex.tmp
	sed -f fixbison.sed < latex.tmp > latex.c

#
# Same rule for latex.c
latex.c: latex.y
	bison latex.y --defines -p tex -o latex.c
	mv latex.c latex.tmp
	sed -f fixbison.sed < latex.tmp > latex.c
