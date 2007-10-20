#! /bin/bash
#
# BEGIN SHORT COPYRIGHT
# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2004 Bradley M. Bell
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
# END SHORT COPYRIGHT
#
if [ "$1" != "" ] && [ "$1" != "batch" ]
then
	echo "usage: run_all.sh [batch]"
	echo "If batch is present, run_all.sh runs with out user interaction"
	exit 1
fi
if [ -e htm ]
then
	echo "rm -r htm"
	if ! rm -r htm
	then
		echo "cannot remove old getstarted/htm directory"
		exit 1
	fi
fi
echo "mkdir htm"
mkdir htm
echo "cd htm"
if ! cd htm
then
	echo "cannot cd to getstarted/htm directory"
	exit 1
fi
input_list="
	simple_example.omh
	head_example.omh
	image_example.omh
	pre_example.omh
	font_example.omh
	spell_example.omh
	verbatim_example.omh
	Factorial.c
	Factorial.m
	multiple_example_1.omh
	cref_example_1.omh
	index_example_1.omh
	latex_example.omh
"
for input in $input_list
do
	output=`echo $input | \
		tr '[A-Z]' '[a-z]' |\
		sed -e s/\.omh/.htm/ -e 's|\.[cm]|&.htm|'`
	cmd="../../../src/omhelp 
		../$input -debug -noframe -omhelp_dir ../../../OMhelp"
	echo $cmd
	if ! $cmd
	then
		echo "cannot run omh/getstarted/$input example"
		exit 1
	fi
	if [ "$1" = "batch" ]
	then
		if [ ! -e $output ]
		then
			echo "file omh/getstarted/htm/$output missing"
			exit 1
		fi
	else
		echo ""
		echo "You can now view: omh/getstarted/htm/$output"
		echo "Hit return to continue, enter text to stop"
		read response
		if [ "$response" != "" ]
		then
			exit 0
		fi
	fi
done
input=latex_example.omh
output=`echo $input | tr '[A-Z]' '[a-z]' | sed -e 's/\.omh/.xml/'`
cmd="../../../src/omhelp 
	../$input -xml -debug -noframe -omhelp_dir ../../../OMhelp"
echo $cmd
if ! $cmd
then
	echo "cannot run omh/getstarted/$input xml example"
	exit 1
fi
if [ "$1" = "batch" ]
then
	if [ ! -e $output ]
	then
		echo "file omh/getstarted/htm/$output missing"
		exit 1
	fi
else
	echo ""
	echo "You can now view: omh/getstarted/htm/$output"
fi
