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
omhelp="../../build/src/omhelp"
omhelp_dir="../../omhelp_data"
example_dir='xam'
# -----------------------------------------------------------------------------
if [ ! -d $example_dir ]
then
	mkdir -p $example_dir/htm
fi
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
	for dir in $example_dir $example_dir/htm
	do
		list=`ls $dir`
		for file in $list
		do
			if [ -f $dir/$file ]
			then
				rm $dir/$file
			fi
		done
	done
	echo "Executing following command in $example_dir/htm directory:"
	cd $example_dir/htm
	#
	sub_list=`echo $input | sed -e 's|;| |g'`
	for file in $sub_list
	do
		echo_eval cp ../../omh/getstarted/$file ../$file
		ext=`echo $file | sed -e 's|.*\.||'`
		if [ "$ext" != 'gif' ] && [ "$ext" != 'dat' ]
		then
			echo "sed -i ../$file -e 's|omh/getstarted/||'"
			sed -i ../$file -e 's|omh/getstarted/||'
		fi
	done
	file=`echo $input | sed -e 's|;.*||'`
	output=`echo $file | \
		sed -e 's|;.*||' -e s/\.omh/.htm/ -e 's|\.[cf]|.htm|'`
	#
	cmd="$omhelp ../$file -debug -noframe -omhelp_dir $omhelp_dir"
	echo "$cmd > ../../omhelp.xam.log"
	if ! $cmd > ../../omhelp.xam.log
	then
		echo "cannot run omh/getstarted/$file example"
		exit 1
	fi
	if [ "$1" = "batch" ]
	then
		if [ ! -e $output ]
		then
			echo "file $example_dir/htm/$output missing"
			exit 1
		fi
	else
		echo ""
		echo "You can view the soruce files in $example_dir"
		echo "View result by opening $example_dir/htm/$output in your browser."
		response=''
		while [ "$response" != 'c' ] && [ "$response" != 's' ]
		do
			echo 'Continue or stop this script [c/s] ?'
			read response
		done
		if [ "$response" == 's' ]
		then
			exit 0
		fi
	fi
	cd ../..
done
# ----------------------------------------------------------------------------
echo 'bin/get_started.sh: OK'
exit 0
