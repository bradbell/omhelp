# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2010 Bradley M. Bell
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
vimsyntaxdir           = $(VIMRUNTIME)/syntax
vimsyntax_DATA         = OMhelp/omhelp.vim
endif
#
nobase_include_HEADERS = src/config.h 
#
SUBDIRS                = src omh/getstarted
#
noinst_DATA            = OMhelp.Dev.log OMhelp.Doc.log
#
# dictonary.bin gets removed and then rebuilt on target machine; see dist-hook.
# It is only included here so that it gets installed.
nobase_dist_data_DATA = \
	OMhelp/omhelp.vim \
	OMhelp/_close.gif \
	OMhelp/_closeblue.gif \
	OMhelp/_image.gif \
	OMhelp/_open.gif \
	OMhelp/_openblue.gif \
	OMhelp/english.wrd \
	OMhelp/local.wrd \
	OMhelp/dictionary.bin
#
EXTRA_DIST = \
	build.sh \
	FixMakefile \
	FixAclocal \
	install.bat \
	RunOMhelp \
	RunOMhelp.bat \
	SetNoExecute \
	omh \
	src/fixbison.sed \
	src/latex.y \
	src/latex.l \
	src/main.src \
	src/omh \
	src/omhelp.y \
	src/src.sln \
	src/src.vcproj \
	wish_list.omh
#
OMhelp/dictionary.bin:
	src/omhelp ./wish_list.omh -noframe -omhelp_dir OMhelp
#
OMhelp.Dev.log:
	./RunOMhelp Dev
#
OMhelp.Doc.log: OMhelp.Dev.log
	./RunOMhelp Doc
# 
# Make sure that unix install rebuilds main.c from main.src.
# Remove all the CVS informaiton.
# Remove all object and binary files from omh/getstarted 
# Remove the dictionary.bin and then rebuild it on target machine.
dist-hook:
	touch $(distdir)/src/main.src
	rm -rf `find $(distdir)/omh -name CVS`
	rm -rf `find $(distdir)/omh/getstarted -name '*.o'`
	rm -rf `find $(distdir)/omh/getstarted -name '*.exe'`
	rm -rf `find $(distdir)/src/omh -name CVS`
	rm -rf $(distdir)/OMhelp/dictionary.bin
