#! /bin/bash -e
# -----------------------------------------------------------------------------
# CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-18 Bradley M. Bell
#
# CppAD is distributed under multiple licenses. This distribution is under
# the terms of the
#                     Eclipse Public License Version 1.0.
#
# A copy of this license is included in the COPYING file of this distribution.
# Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
# -----------------------------------------------------------------------------
# configuration file for tools in ~/devel.
#
# web address linked by run_omhelp.sh to the Home icon on each page.
# Have not yet converted omhelp to using ~/devel/run_omhelp.
# image_link='https://bradbell.github.io/omhelp'
# echo "image_link=$image_link"
#
# list of files that are not automatically ignored by check_copyright.sh
copyright_ignore='
	omhelp.c
'
echo "copyright_ignore=$copyright_ignore"
