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
cat << EOF > junk.sed
/@syntax/b got_syntax_cmd
/\$syntax/! b skip
#
: loop
/\\\$\\\$/! N
/\\\$\\\$/! b loop
#
: got_syntax_cmd
#
EOF
E='\$\$'
list='% | /'
for D in $list
do
	P="\([^$D]*\)"
cat << EOF >> junk.sed
s#\$syntax$D$D#\$icode$D#g
s#\$syntax$D#\$codei$D#g
#
s#@syntax$D$D#@icode$D#g
s#@syntax$D#@codei$D#g
#
EOF
done
echo ': skip' >> junk.sed
list=`git ls-files | sed  \
	-e '/^omh\/syntax\.omh$/d' \
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
