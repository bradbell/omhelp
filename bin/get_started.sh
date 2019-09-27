#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2019 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
if [ "$0" != 'bin/get_started.sh' ]
then
	echo 'bin/get_started.sh: must be run from its parent directory'
	exit 1
fi
if [ "$1" != "" ] && [ "$1" != "batch" ]
then
	echo "usage: get_started.sh [batch]"
	echo "If batch is present, get_started.sh runs with out user interaction"
	exit 1
fi
# -----------------------------------------------------------------------------
top_srcdir=`pwd`
omhelp="$top_srcdir/build/src/omhelp"
omhelp_dir="$top_srcdir/omhelp_data"
# -----------------------------------------------------------------------------
if [ -e get_started ]
then
	rm -r get_started
fi
mkdir -p get_started/htm
input_list='
	simple_example.omh
	head_example.omh
	pre_example.omh
	font_example.omh
	spell_example.omh
	latex_example.omh
	image_example.omh;w3c_home.gif
	verbatim_example.omh;verbatim_example.dat
	near_equal_c.c;ok_near_equal_c.c
	near_equal_f.f;ok_near_equal_f.f
	parent_example.omh;child_1_example.omh;child_2_example.omh
	cref_example.omh;cref_children.omh
	index_example.omh;index_children.omh
'
for input in $input_list
do
	sub_list=`echo $input | sed -e 's|;| |g'`
	for file in $sub_list
	do
		ext=`echo $file | sed -e 's|.*\.||'`
		if [ "$ext" != 'gif' ] && [ "$ext" != 'dat' ]
		then
			sed < "omh/getstarted/$file" > get_started/$file \
				-e 's|omh/getstarted/||'
		else
			echo_eval cp "omh/getstarted/$file" get_started/$file
		fi
	done
	file=`echo $input | sed -e 's|;.*||'`
	output=`echo $file | \
		sed -e 's|;.*||' -e s/\.omh/.htm/ -e 's|\.[cf]|.htm|'`
	#
	echo 'Executing following command in get_started/htm directory'
	cd get_started/htm
	cmd="$omhelp ../$file -debug -noframe -omhelp_dir $omhelp_dir"
	echo $cmd
	if ! $cmd
	then
		echo "cannot run omh/getstarted/$file example"
		exit 1
	fi
	if [ "$1" = "batch" ]
	then
		if [ ! -e $output ]
		then
			echo "file get_started/htm/$output missing"
			exit 1
		fi
	else
		echo ""
		echo 'You can view the soruce files in get_started'
		echo "View result by opening get_started/htm/$output in your browser"
		echo 'Just return will continue, any text will stop this script.'
		read response
		if [ "$response" != "" ]
		then
			exit 0
		fi
	fi
	cd ../..
	rm get_started/htm/*
	for file in $sub_list
	do
		rm get_started/$file
	done
done
# ----------------------------------------------------------------------------
echo 'bin/get_started.sh: OK'
exit 0
