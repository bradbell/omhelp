# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2015 Bradley M. Bell
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
SET(CMAKE_BUILD_TYPE DEBUG)

SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(bindir ${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${srcdir} ${bindir})

# create main.c
CONFIGURE_FILE(main.c.in main.c)

# crete omhelp.h , omhelp.c
ADD_CUSTOM_COMMAND(OUTPUT omhelp.h omhelp.c
	COMMAND bison ${srcdir}/omhelp.y --defines -p omh -o omhelp.c
)
# create latex.h , latex.c
ADD_CUSTOM_COMMAND(OUTPUT latex.h latex.c
	COMMAND bison ${srcdir}/latex.y --defines -p tex -o latex.c
)

ADD_EXECUTABLE(omhelp
	${bindir}/main.c
	${bindir}/omhelp.c
	${bindir}/latex.c
	alloca.c
	allocate.c
	allocmem.c
	automatic.c
	AutomaticLink.c
	BinarySearch.c
	browser.c
	children.c
	ClipWhiteSpace.c
	Color.c
	color_switch.c
	content.c
	convert.c
	copyfile.c
	cross.c
	DirSep.c
	execute.c
	fatalerr.c
	FileEqual.c
	FrameSet.c
	funref.c
	head.c
	hilite.c
	href.c
	HtmlHead.c
	index.c
	input.c
	int2str.c
	Internal2Out.c
	LatexAtomic.c
	LatexMacro.c
	lexomh.c
	lextex.c
	libyyerr.c
	libyywra.c
	links.c
	math.c
	output.c
	output_text.c
	PatternMatch.c
	pending.c
	relative.c
	search.c
	section.c
	spell.c
	SplitText.c
	StrCat.c
	StrLowCase.c
	StrRemove.c
	style.c
	trace_exit.c
	UniformWhiteSpace.c
	url.c
	warning.c
)
