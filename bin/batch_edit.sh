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
cat << EOF > junk.sed
/\$fend [0-9]*\\\$\\\$/N
/\$fend [0-9]*\\\$\\\$ *\\n *\$/d
s|$xref
EOF
list=`git ls-files | sed  \
	-e '/^omh\/whatsnew\.omh$/d' \
	-e '/omh\/href\.omh$/d' \
	-e '/^bin\/batch_edit\.sh$/d' `
for file in $list
do
	ext=`echo $file | sed -e 's|.*\.||'`
	case $ext in
		omh | c | h | l | sh | f | bat )
		if grep 'fend' $file > /dev/null
		then
			git checkout $file
			sed -f junk.sed -i $file
			if grep '$fend' $file > /dev/null
			then
				echo "$file failed"
				exit 1
			fi
		fi
		;;

		*)
		# skip
		;;
	esac
done
