#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2016 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
# list files in repository (not deleted)
# -----------------------------------------------------------------------------
if [ $0 != "bin/ls_files.sh" ]
then
	echo "bin/ls_files.sh: must be executed from its parent directory"
	exit 1
fi
# -----------------------------------------------------------------------------
list=`git ls-files`
git ls-files -d > list_files.$$
for file in $list
do
	if ! grep "$file" list_files.$$ > /dev/null
	then
		echo $file
	fi
done
rm list_files.$$
# ----------------------------------------------------------------------------
exit 0
