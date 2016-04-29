#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
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
@spell
	Firefox
	Inline
@@
@section 2016-04-29: Firefox Spacing Above and Below MathML Inline Equations@@

@head Problem@@
Firefox seems to be putting more than necessary vertical white space
above a line with and inline MathML equation:

@head Example@@
This line comes before the inline equation:
@pre
@@
Line with the inline equation @latex y = f(x)@@
@pre
@@
This line comes after the inline equation.

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
echo_eval ../$program ./one.omh -noframe -xml -omhelp_dir ../../omhelp_data
