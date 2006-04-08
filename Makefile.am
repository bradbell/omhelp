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
# Note that config.h is needed by VC++; i.e., for users that do not run
# the configure script but rather use project files
#
# check if vim data directory has been specified
if OMhelp_VIMRUNTIME
vimsyntaxdir = $(VIMRUNTIME)/syntax
vimsyntax_DATA = \
	OMhelp/omhelp.vim
endif
#
nobase_include_HEADERS = \
	src/config.h 
#
SUBDIRS = \
	src
#
nobase_dist_data_DATA = \
	OMhelp/omhelp.vim \
	OMhelp/_close.gif \
	OMhelp/_closeblue.gif \
	OMhelp/_open.gif \
	OMhelp/_openblue.gif \
	OMhelp/english.wrd \
	OMhelp/icon.gif \
	OMhelp/local.wrd \
	OMhelp/pmathml.xsl \
	OMhelp/pmathmlcss.xsl \
	OMhelp/dictionary.bin
#
EXTRA_DIST = \
	Build \
	FixMakefile \
	FixAclocal \
	RunOMhelp \
	RunOMhelp.bat \
	SetNoExecute \
	setenv.bat \
	omh \
	src/omh \
	src/main.src \
	src/omhelp.y \
	src/latex.y \
	src/latex.l \
	src/src.sln \
	src/src.vcproj 
#
OMhelp/dictionary.bin:
	./RunOMhelp Doc
	./RunOMhelp Developer
# 
# Make sure that unix install rebuilds main.c from main.src.
# Remove all the CVS informaiton.
# Remove the dictionary.bin (does in data directory but is machine dependent).
dist-hook:
	touch $(distdir)/src/main.src
	rm -r `find $(distdir)/omh -name CVS`
	rm -r `find $(distdir)/src/omh -name CVS`
	rm $(distdir)/OMhelp/dictionary.bin
