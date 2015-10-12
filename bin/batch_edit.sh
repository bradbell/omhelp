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
# Converting one argument delimiter sequence to use space for delimiter.
cmd_list='
	icode
	codei
	cref
'
del_list='
	%
	|
	/
'
for cmd in $cmd_list
do
	for del in $del_list
	do
cat << EOF > junk.sed
s#\$$cmd$del\\([^$del]*\\)\\$del\\\$\\\$#\$$cmd \\1\$\$#g
EOF
	done
done
list=`git ls-files | sed  \
	-e '/^bin\/batch_edit\.sh$/d'`
for file in $list
do
	git checkout $file
	ext=`echo $file | sed -e 's|.*\.||'`
	case $ext in
		omh | c | h | l | sh | f | bat )
		sed -f junk.sed -i $file
		;;

		*)
		# skip
		;;
	esac
done
