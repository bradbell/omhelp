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
name='dot_in_name'
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
echo "create build/bug/one.hpp"
cat << EOF > one.hpp
@begin one_hpp@@
@spell hpp@@
@section Example Section one.hpp@@
The drop down menu with title one.hpp as the title and two.hpp
below it is missing.
If you change the 'begin one.hpp' to 'begin one_hpp'
the drop town menu will appear the resulting output.
@childtable%two.hpp%@@
@end
EOF
cat << EOF > two.hpp
@begin two.hpp@@
@spell hpp@@
@section Example Section two.hpp@@
@end
EOF
sed -i one.hpp -e 's|@|$|g'
sed -i two.hpp -e 's|@|$|g'
#
echo_eval ../src/omhelp ./one.hpp -noframe -omhelp_dir ../../omhelp_data
