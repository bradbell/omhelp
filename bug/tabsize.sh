#! /bin/bash -e
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
# ------------------------------------------------------------------
echo "create htm/one.omh"
cat << EOF > htm/one.omh
@begin one@@
@section 2015-10-08: Demonstrate Bub in Tab Setting@@
@tabsize 20@@

@head Use Tab Size@@
@codep
012345678901234567890
There is no tab on this line.
	This text should start at column 20.
@@

@end
EOF
# ------------------------------------------------------------------
sed -e 's|@|$|g' -i htm/one.omh
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
echo_eval ../$program ./one.omh -noframe -omhelp_dir ../../omhelp_data
