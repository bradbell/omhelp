#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#            Copyright (C) 2003-15 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/check_include_file.sh" ]
then
	echo "bin/check_include_file.sh: must be executed from its parent directory"
	exit 1
fi
#
echo "Checking difference between C include directives and file names."
echo "-----------------------------------------------------------------"
# ignore latex.h and omhelp.h becasue they are generated by src/CMakeLists.txt
grep '^# *include *"' src/*.c src/*.h src/*.y |\
	sed -e 's/^[^"]*"\([^"]*\)"/\1/' -e '/^latex.h$/d' -e '/^omhelp.h$/d' |\
	sort -u > junk.1
#
ls src/*.h |\
sed -e 's/src\///' |\
sort -u > junk.2
#
diff junk.1 junk.2
echo "-----------------------------------------------------------------"
echo "Nothing should be between the two dashed lines above"
