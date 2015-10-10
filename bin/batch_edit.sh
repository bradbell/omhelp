#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/batch_edit.sh" ]
then
	echo "bin/batch_edit.sh: must be executed from its parent directory"
	exit 1
fi
list=`git ls-files | sed \
	-e '/^bin\/new_copyright\.sh/d' \
	-e '/^omh\/children_cmd\.omh/d' \
	-e '/^omh\/childtable_cmd\.omh/d' \
	-e '/^omh\/copyright\.omh/d' \
	-e '/^omh\/license\.omh/d' \
	-e '/^src\/allocate.c/d' \
	-e '/^src\/lextex.c/d' \
	-e '/^bin\/batch_edit\.sh/d'`
for file in $list
do
	ext=`echo $file | sed -e 's|.*\.||'`
	case $ext in
		omh | c | h | sh | f | bat )
		# add copyright
		echo $file
		git checkout $file
		bin/new_copyright.sh $file
		# for testing pruposes
		git checkout $file
		;;

		*)
		# skip
		;;
	esac
done
