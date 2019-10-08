#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2019 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------
name='vertical_space'
# -----------------------------------------------
if [ "$0" != "bug/$name.sh" ]
then
    echo "usage: bug/$name.sh"
    exit 1
fi
if [ ! -e 'build/src/omhelp' ]
then
    echo "bug/$name.sh: Error"
    echo 'Must first build omhelp executable; e.g.,'
    exit 1
fi
if [ -e 'build/bug' ]
then
    echo_eval rm -r 'build/bug'
fi
echo_eval mkdir build/bug
echo_eval cd build/bug
#
echo "create build/bug/one.cpp"
cat << EOF > one.cpp
/*
@begin one@@
@section Error in Vertical Spacing@@
@spell
	srcfile
@@

@head srcfile Commands@@
Below is the output of two @code srcfile@@ commands one right after the other.
@srcfile%one.cpp%
	0%// BEGIN_PROTOTYPE%// END_PROTOTYPE%2
%@@
@srcfile%one.cpp%
	0%// BEGIN_PROTOTYPE%// END_PROTOTYPE%2
%@@

@head Second Heading@@
Above is a heading directly after the second @code srcfile@@ command.
This heading does not have a blank line before it.

@end
*/
	// BEGIN_PROTOTYPE
	void f(void);
	// END_PROTOTYPE
EOF
sed -i one.cpp -e 's|@|$|g'
#
echo_eval ../src/omhelp ./one.cpp -noframe -omhelp_dir ../../omhelp_data
