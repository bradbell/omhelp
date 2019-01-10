#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2018 Bradley M. Bell
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
top_srcdir=`pwd`
if [ "$version" == 'local' ]
then
	exit_on_warning='yes'
else
	exit_on_warning='no'
fi
# -----------------------------------------------------------------------------
remote_tarball="https://github.com/bradbell/omhelp/archive/$version.tar.gz"
omhelp_prefix="$HOME/prefix/omhelp"
omhelp_datadir='share'
omhelp_c_flags='-Wall'
# -----------------------------------------------------------------------------
temporary_file="$top_srcdir/check_all.$$"
echo_log_eval() {
	echo $*
	echo $* >> $top_srcdir/check_all.log
	if ! eval $* >& $temporary_file
	then
		cat $temporary_file >> $top_srcdir/check_all.log
		echo 'Error: see check_all.log'
		rm $temporary_file
		exit 1
	fi
	cat $temporary_file >> $top_srcdir/check_all.log
	if grep '[0-9]: warning' $temporary_file > /dev/null
	then
		echo 'Warnings: see check_all.log'
		if [ "$exit_on_warning" == 'yes' ]
		then
			rm $temporary_file
			exit 1
		fi
	fi
	rm $temporary_file
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
# -----------------------------------------------------------------------------
# Create Distribution
if [ "$version" == 'local' ]
then
	# check copyright message
	check_copyright.sh
	#
	# check version number
	version.sh check
	#
	for dir in build dev doc
	do
		if [ -e $dir ]
		then
			echo_eval rm -r $dir
		fi
	done
else
	# check for version number here has to wait for new tarball
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
	#
	# check version number
	check=`grep '^SET(omhelp_version' CMakeLists.txt | \
		sed -e 's|^[^"]*"\([^"]*\).*|\1|'`
	if [ "$version" != "$check" ]
	then
		echo 'check_all.sh: CMakeLists.txt version number name of tarball'
		exit 1
	fi
fi
# -----------------------------------------------------------------------------
highlight_prefix=`grep source_highlight_prefix bin/run_cmake.sh | \
		sed -e 's|^.*=||' -e 's|" .*||' -e 's|"||' -e "s|[$]HOME|$HOME|"`
# -----------------------------------------------------------------------------
for test_case in highlight_yes highlight_no
do
	if [ "$test_case" == 'highlight_no' ]
	then
		echo_eval mv $highlight_prefix $highlight_prefix.no
	fi
	# -------------------------------------------------------------------------
	echo_log_eval bin/run_cmake.sh debug
	number=`grep 'WARNING: \$srcfile command NOT available' \
	$top_srcdir/check_all.log | wc -l`
	if [ "$test_case" == 'highlight_no' ]
	then
		if [ "$number" != 1 ]
		then
			echo 'check_all.sh: test case highlight_no'
			echo 'bin/run_cmake.sh srcfile WARNING missing'
			if [ "$exit_on_warning" == 'yes' ]
			then
				exit 1
			fi
		fi
	else
		if [ "$number" != 0 ]
		then
			echo 'check_all.sh: test case highlight_yes'
			echo 'bin/run_cmake.sh srcfile WARNING present'
			if [ "$exit_on_warning" == 'yes' ]
			then
				exit 1
			fi
		fi
	fi
	# -------------------------------------------------------------------------
	# Build Executable
	echo_log_eval cd build
	echo_log_eval make
	echo_log_eval cd ..
	# -------------------------------------------------------------------------
	# Build Documentation and Get Started
	if [ "$test_case" == 'highlight_yes' ]
	then
		echo_log_eval bin/run_omhelp.sh dev
	fi
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
	#
	if [ "$test_case" == 'highlight_no' ]
	then
		echo_eval mv $highlight_prefix.no $highlight_prefix
	fi
done
echo "check_all.sh: OK"
exit 0
