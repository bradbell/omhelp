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
# Script for converting italic commands that correspond to variables in syntax
cat << EOF > junk.sed
s|\$italic \([a-zA-Z][a-zA-Z0-9_]*\)\\\$\\\$|\$icode \\1\$\$|g
s|\$italic \([a-zA-Z][a-zA-Z]* [0-9]\)\\\$\\\$|\$icode \\1\$\$|g
EOF
list=`git ls-files | sed  \
	-e '/^omh\/syntax\.omh$/d' \
	-e '/^bin\/batch_edit\.sh$/d'`
for file in $list
do
	git checkout $file
	ext=`echo $file | sed -e 's|.*\.||'`
	case $ext in
		omh | c | h | l | sh | f | bat )
		if grep 'italic' $file > /dev/null
		then
			sed -f junk.sed -i $file
		fi
		;;

		*)
		# skip
		;;
	esac
done
sed -e 's|$italic word list|$icode word_list|' -i omh/spell.omh
sed -e 's|$italic pre-formattted|$icode pre_formatted|' -i omh/codep.omh
sed -e 's|$italic linkingtext|$cref/href/linkingtext/|' -i omh/whatsnew.omh
sed -e 's|$italic italic ntoken|$icode ntoken|' -i src/section.c
sed -e 's|$italic F->nFrame|$icode F-nFrame|' -i src/FrameSet.c
sed -e 's|$italic section/|$icode section|' -i src/automatic.c

