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
# Script for converting syntax commands to codei and icode commands
# Also: correct $beign -> $begin
if [ -e junk.sed ]
then
	rm junk.sed
fi
E='\$\$'
list='% | /'
for D in $list
do
	P="\([^$D]*\)"
	echo "s@\$syntax$D$D@\$icode$D@g" >> junk.sed
	echo "s@\$syntax$D@\$codei$D@g"   >> junk.sed
done
list=`git ls-files | sed  \
	-e '/^bin\/batch_edit\.sh$/d'`
for file in $list
do
	git checkout $file
	ext=`echo $file | sed -e 's|.*\.||'`
	case $ext in
		omh | c | h | l | sh | f | bat )
		if grep 'syntax' $file > /dev/null
		then
			sed -f junk.sed -i $file
			if grep '$syntax' $file > /dev/null
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
