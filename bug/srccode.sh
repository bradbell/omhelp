#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
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
cat << EOF > htm/srccode.omh
@begin srccode@@
@spell srccode@@

@section Bug in srccode Command@@
The @code if@@ does not line up with the @code return@@ below it.

@srccode|cpp| */
double function max(double a, double b)
{	if( a > b )
		return a;
	return b;
}
/* |@@
@end
*/
EOF
sed -e 's|@|$|g' -i htm/srccode.omh
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
echo_eval ../$program ./srccode.omh -xml -omhelp_dir ../../omhelp_data
