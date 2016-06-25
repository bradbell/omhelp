#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2016 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/run_cmake.sh" ]
then
	echo "bin/run_cmake.sh: must be executed from its parent directory"
	exit 1
fi
if [ "$1" == 'debug' ]
then
	build_type='DEBUG'
elif [ "$1" == 'release' ]
then
	build_type='RELEASE'
else
	echo "bin/run_cmake.sh: build_type"
	echo "where build type is debug or release"
	exit 1
fi
# ----------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
if [ ! -e build ]
then
	echo_eval mkdir build
fi
echo_eval cd build
if [ -e 'CMakeCache.txt' ]
then
	echo_eval rm CMakeCache.txt
fi
echo_eval cmake \
	-D boost_regex_prefix='/usr' \
	-D source_highlight_prefix="$HOME/prefix/highlight" \
	-D have_flex_and_bison=YES \
	-D omhelp_prefix=$HOME/prefix/omhelp \
	-D omhelp_datadir=share \
	-D omhelp_c_flags='-Wall' \
	-D omhelp_build_type="$build_type" \
	..
echo 'run_cmake.sh: OK'
