#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/check_all.sh" ]
then
	echo "bin/check_all.sh: must be executed from its parent directory"
	exit 1
fi
if [ "$1" == '' ]
then
	echo 'usage: bin/check_all.sh version'
	echo 'where version is a tag name for omhelp on github.'
	echo 'If verison is local, the local repository is used.'
	exit 1
fi
version="$1"
# -----------------------------------------------------------------------------
remote_tarball="https://github.com/bradbell/omhelp/archive/$version.tar.gz"
omhelp_prefix="$HOME/prefix/omhelp"
omhelp_datadir='share'
omhelp_c_flags='-Wall'
# -----------------------------------------------------------------------------
echo_log_eval() {
	echo $*
	echo $* >> $top_srcdir/check_all.log
	if ! eval $* >> $top_srcdir/check_all.log \
		2> $top_srcdir/check_all.err
	then
		cat $top_srcdir/check_all.err
		echo 'Error: see check_all.log'
		exit 1
	fi
	msg=`cat $top_srcdir/check_all.err`
	if [ "$msg" != '' ]
	then
		echo "$msg"
		echo 'Warning: see check_all.err'
		exit 1
	fi
	rm $top_srcdir/check_all.err
}
log_eval() {
	echo $* >> $top_srcdir/check_all.log
	if ! eval $* >> $top_srcdir/check_all.log
	then
		echo "Error: check check_all.log"
		exit 1
	fi
}
echo_eval() {
	echo $*
	eval $*
}
if [ -e check_all.log ]
then
	echo "rm check_all.log"
	rm check_all.log
fi
top_srcdir=`pwd`
# -----------------------------------------------------------------------------
# Create Distribution
if [ "$version" == 'local' ]
then
	for dir in build dev doc
	do
		if [ -e $dir ]
		then
			echo_eval rm -r $dir
		fi
	done
else
	if [ ! -e build ]
	then
		echo_eval mkdir build
	fi
	echo_eval cd build
	if [ -e omhelp-$version.tar.gz ]
	then
		echo_eval rm omhelp-$version.tar.gz
	fi
	if [ -e omhelp-$version ]
	then
		echo_eval rm -r  omhelp-$version
	fi
	#
	echo_log_eval wget \
		$remote_tarball \
		-o check_all.sh.$$ \
		-O omhelp-$version.tar.gz
	echo_log_eval rm check_all.sh.$$
	#
	echo_log_eval tar -xzf omhelp-$version.tar.gz
	echo_log_eval cd omhelp-$version
fi
# -----------------------------------------------------------------------------
highlight_prefix=`grep source_highlight_prefix bin/run_cmake.sh debug | \
		sed -e 's|^.*=||' -e 's|" .*||' -e 's|"||' -e "s|[$]HOME|$HOME|"`
# -----------------------------------------------------------------------------
for test_case in highlight_no highlight_yes
do
	if [ "$test_case" == 'highlight_no' ] && [ -e "$highlight_prefix" ]
	then
		echo_eval mv $highlight_prefix $highlight_prefix.no
	fi
	if [ "$test_case" == 'highlight_yes' ]
	then
		if [ ! -e "$highlight_prefix.no" ]
		then
			echo_eval mv $highlight_prefix $highlight_prefix.no
			echo "check_all.sh: cannot find $highlight_prefix.no"
			exit 1
		fi
		echo_eval mv $highlight_prefix.no $highlight_prefix
	fi
	# -------------------------------------------------------------------------
	# CMake Command
	echo_log_eval bin/run_cmake.sh debug
	if [ "$testcase" == 'highlight_no' ]
	then
		bin/run_cmake.sh debug > check_all.$$
		if ! grep 'WARNING: \$srcfile command NOT available' check_all.$$ \
			> /dev/null
		then
			rm check_all.$$
			echo 'check_all.sh: test case highlight_no'
			echo 'bin/run_cmake.sh WARNING missing'
			exit 1
		fi
		rm check_all.$$
	fi
	# -------------------------------------------------------------------------
	# Build Executable
	echo_log_eval cd build
	echo_log_eval make
	echo_log_eval cd ..
	# -------------------------------------------------------------------------
	# Build Documentation and Get Started
	echo_log_eval bin/run_omhelp.sh dev
	echo_log_eval bin/run_omhelp.sh doc
	echo_log_eval bin/run_omhelp.sh xam
	# ------------------------------------------------------------------------
	# Check multiple language example
	echo_log_eval build/omh/getstarted/run_all
	# ------------------------------------------------------------------------
	# Build each get_started example separately
	echo_log_eval cd omh/getstarted
	echo_log_eval ./run_all.sh batch
	# ------------------------------------------------------------------------
	echo_log_eval cd ../..
done
echo "check_all.sh: OK"
exit 0
