#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2019 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/check_all.sh" ]
then
	echo "bin/check_all.sh: must be executed from its parent directory"
	exit 1
fi
top_srcdir=`pwd`
if [ "$version" == 'local' ]
then
	exit_on_warning='yes'
else
	exit_on_warning='no'
fi
# -----------------------------------------------------------------------------
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
# check copyright message
check_copyright.sh
#
# check version number
version.sh check
# -----------------------------------------------------------------------------
highlight_prefix=`grep source_highlight_prefix bin/run_cmake.sh | \
		sed -e 's|^.*=||' -e 's|" .*||' -e 's|"||' -e "s|[$]HOME|$HOME|"`
# -----------------------------------------------------------------------------
for test_case in highlight_no highlight_yes
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
		# highlight_no waning is there, check if got another for highlight_yes
		if [ "$number" == 2 ]
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
	# Build omhelp executable and run_all
	echo_log_eval cd build
	echo_log_eval make
	echo_log_eval omh/getstarted/run_all
	echo_log_eval cd ..
	# ------------------------------------------------------------------------
	# Must check get_started first because doc and dev include omhelp.xam.log
	echo_log_eval bin/get_started.sh batch
	# -------------------------------------------------------------------------
	# check omhelp documentation
	if [ "$test_case" == 'highlight_yes' ]
	then
		echo_log_eval run_omhelp.sh -clean dev
	fi
	echo_log_eval run_omhelp.sh -clean doc
	# ------------------------------------------------------------------------
	if [ "$test_case" == 'highlight_no' ]
	then
		echo_eval mv $highlight_prefix.no $highlight_prefix
	fi
done
# ----------------------------------------------------------------------------
# re-run cmake with release version and highlighting
echo_log_eval bin/run_cmake.sh release
# ----------------------------------------------------------------------------
echo "check_all.sh: OK"
exit 0
