#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2016 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------
#
if [ -e htm ]
then
	echo_eval rm -r htm
fi
echo_eval mkdir htm
echo "create htm/one.cpp"
cat << EOF > htm/one.cpp
/*
@begin one@@
@spell
	srcfile
@@
@section 2017-08-12: srcfile causes Wrong Line number in Error Message@@

@srcfile%one.cpp%0%// BEGIN_PROTOTYPE%// END_PROTOTYPE%2%@@
@srcfile%one.cpp%0%// BEGIN_PROTOTYPE%// END_PROTOTYPE%2%@@

Line 11: The error is in the following command: @icode%x% = 0@@.
Line 12.
line 13: The error is reported as being in this line.

@end
*/
// BEGIN_PROTOTYPE
void f(void)
// END_PROTOTYPE
EOF
sed -e 's|@|$|g' -i htm/one.cpp
#
program='../build/src/omhelp'
if [ ! -e "$program"  ]
then
	echo "$program does not exist"
	echo 'The following commands will build it:"'
	echo '	cd .. ; bin/run_cmake ; cd build ; make'
	exit 1
fi
echo_eval cd htm
echo_eval ../$program ./one.cpp -xml -omhelp_dir ../../omhelp_data
