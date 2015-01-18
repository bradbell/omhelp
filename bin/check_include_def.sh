#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#            Copyright (C) 2003-15 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/check_include_def.sh" ]
then
	echo "bin/check_include_def.sh: must be executed from its parent directory"
	exit 1
fi
echo "Checking difference between # ifndef directives and file names."
echo "---------------------------------------------------------------"
#
grep '^# *ifndef *[A-Z_]*INCLUDED$' \
	src/*.h \
	| sort -u \
	> junk.1
sed < junk.1 \
	-e 's/^src\/\([^.]*\)\.h:.*/\1/' \
	-e 's/\([a-z]\)\([A-Z]\)/\1_\2/g' | \
	tr [a-z] [A-Z] \
	> junk.2
sed -e 's/^.*# *ifndef *//' -e 's/_INCLUDED$//' < junk.1 > junk.3
diff junk.2 junk.3
#
grep '^# *define *[A-Z_]*INCLUDED$' \
	src/*.h \
	| sort -u \
	> junk.1
sed < junk.1 \
	-e 's/^src\/\([^.]*\)\.h:.*/\1/' \
	-e 's/\([a-z]\)\([A-Z]\)/\1_\2/g'| \
	tr [a-z] [A-Z] \
	> junk.2
sed -e 's/^.*# *define *//' -e 's/_INCLUDED$//' < junk.1 > junk.3
diff junk.2 junk.3
echo "---------------------------------------------------------------"
echo "Nothing should be between the two dashed lines above"
