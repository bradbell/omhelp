#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2017 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/run_omhelp.sh" ]
then
	echo "bin/run_omhelp.sh: must be executed from its parent directory"
	exit 1
fi
echo "$0 $*"
arguments='[-clean] [-printable] [-xml] (doc|dev|xam)'
clean='no'
printable=''
xml=''
dir=''
dev='no'
if [ "$1" == '-clean' ]
then
	clean='yes'
	shift
fi
if [ "$1" == '-printable' ]
then
	printable='-printable'
	shift
fi
#
if [ "$1" == '-xml' ]
then
	xml='-xml'
	shift
fi
#
if [ "$1" == 'doc' ] || [ "$1" == 'dev' ] || [ "$1" == 'xam' ]
then
	dir="$1"
	shift
else
	echo "usage: bin/run_omhelp.sh $arguments"
	exit 1
fi
if [ "$1" == 'doc' ] && [ ! -e omhelp.dev.log ]
then
	echo 'must execute bin/omhelp.sh [-clean] [-printable] [-xml] dev'
	echo 'before bin/omhelp.sh [-clean] [-printable] [-xml] doc'
	exit 1
fi
# -----------------------------------------------------------------------------
if [ "$clean" == 'yes' ]
then
	if [ -e $dir ]
	then
		echo_eval rm -r $dir
	fi
fi
# -----------------------------------------------------------------------------
if [ ! -d "$dir" ]
then
	echo_eval mkdir $dir
fi
echo_eval cd $dir
if [ "$dir" == 'dev' ]
then
	root='../src/omh/omhelp.omh'
elif [ "$dir" == 'doc' ]
then
	root='../omh/overview.omh'
else
	root='../omh/getstarted/multiple_example_1.omh'
fi
if ! ../build/src/omhelp \
		"$root" \
		$printable \
		$xml \
		-image_link https://github.com/bradbell/omhelp \
		-noframe \
		-debug \
		-omhelp_dir \
		../omhelp_data > ../omhelp.$dir.log
then
	cat ../omhelp.$dir.log
	echo "OMhelp could not build $dir."
	echo "See the complete error message in omhelp.$dir.log."
	grep "^OMhelp Error:" ../omhelp.$dir.log
	exit 1
fi
cd ..
if grep "^OMhelp Warning:" omhelp.$dir.log
then
	echo "See the complete warning messages in omhelp.$dir.log."
	exit 1
fi
# -----------------------------------------------------------------------------
echo 'run_omhelp.sh OK'
exit 0
