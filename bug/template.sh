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
name='template'
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
echo "create build/bug/one.omh"
cat << EOF > one.omh
@begin one@@
@section Example Section One@@
@childtable%two.omh%@@
@end
EOF
cat << EOF > two.omh
@begin two@@
@section Example Section Two@@
@end
EOF
sed -i one.omh -e 's|@|$|g'
sed -i two.omh -e 's|@|$|g'
#
echo_eval ../src/omhelp ./one.omh -noframe -omhelp_dir ../../omhelp_data
