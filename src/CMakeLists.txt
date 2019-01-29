# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2019 Bradley M. Bell
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
SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(bindir ${CMAKE_CURRENT_BINARY_DIR})

IF( source_highlight_01 )
	SET(extra_inc_dirs
		${source_highlight_prefix}/include ${boost_regex_prefix}/include
	)
	SET(extra_lib_dirs ${source_highlight_dir} ${boost_regex_dir})
	SET(extra_libs     "source-highlight" "boost_regex" )
	LINK_DIRECTORIES( ${extra_lib_dirs} )
ELSE( source_highlight_01 )
	SET(extra_inc_dirs "")
	SET(extra_lib_dirs "")
	SET(extra_libs     "")
ENDIF( source_highlight_01 )
#
INCLUDE_DIRECTORIES(${srcdir} ${bindir} ${extra_inc_dirs} )
ADD_DEFINITIONS( -DSOURCE_HIGHLIGHT_01=${source_highlight_01} )

# create main.c
CONFIGURE_FILE(main.c.in main.c)
IF( have_flex_and_bison )
	# crete omhelp.h , omhelp.c
	ADD_CUSTOM_COMMAND(OUTPUT ${srcdir}/omhelp.c
		COMMAND bison --defines -p omh -o ${srcdir}/omhelp.c ${srcdir}/omhelp.y
		DEPENDS omhelp.y
	)
	# create latex.h , latex.c
	ADD_CUSTOM_COMMAND(OUTPUT ${srcdir}/latex.c
		COMMAND bison --defines -p tex -o ${srcdir}/latex.c ${srcdir}/latex.y
		DEPENDS latex.y
	)
	# create lex.tex.c
	# -Ptex maps lex.yy.c -> lex.tex.c
	ADD_CUSTOM_COMMAND(OUTPUT ${srcdir}/lex.tex.c
		COMMAND flex -Ptex -o ${srcdir}/lex.tex.c ${srcdir}/latex.l
		DEPENDS latex.l
	)
ENDIF( have_flex_and_bison )

ADD_EXECUTABLE(omhelp
	${bindir}/main.c
	${srcdir}/omhelp.c
	${srcdir}/latex.c
	${srcdir}/lex.tex.c
	jump_table.c
	AutomaticLink.c
	BinarySearch.c
	ClipWhiteSpace.c
	Color.c
	color_switch.c
	DirSep.c
	FileEqual.c
	Internal2Out.c
	LatexAtomic.c
	LatexMacro.c
	PatternMatch.c
	SplitText.c
	StrCat.c
	StrLowCase.c
	StrRemove.c
	UniformWhiteSpace.c
	allocate.c
	allocmem.c
	automatic.c
	browser.c
	children.c
	content.c
	convert.c
	copyfile.c
	cross.c
	execute.c
	fatalerr.c
	FrameSet.c
	funref.c
	head.c
	highlight.cpp
	hilite.c
	href.c
	HtmlHead.c
	index.c
	input.c
	int2str.c
	lexomh.c
	libyyerr.c
	libyywra.c
	links.c
	math.c
	math_jax.c
	output.c
	output_text.c
	pending.c
	relative.c
	search.c
	section.c
	select_childtable.c
	style.c
	spell.c
	trace_exit.c
	url.c
	warning.c
)
TARGET_LINK_LIBRARIES(omhelp ${extra_libs} )
