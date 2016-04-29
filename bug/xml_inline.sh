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
	fc
@@
@section 2016-04-29: Firefox Spacing Above MathML Inline Equations@@

@head Problem@@
Firefox on Fedora is be putting more than necessary vertical white space
above a line with an inline MathML equation.
To be more specific
enough extra space to fit another line (with normal spacing above and below).

@head RPM@@
firefox-45.0-4.fc22.x86_64

@head Example@@
This line comes before the inline equation:
@pre
@@
Line with the inline equation @latex y = f(x)@@.
@pre
@@
This line comes after the inline equation.

@head Other Systems@@
This extra space does not appear on Windows with Firefox 43.0.1.

@head Bug Report@@
This has been submitted as the following bug
@href|https://bugzilla.redhat.com/show_bug.cgi?id=1331765|@@

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
