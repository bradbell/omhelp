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
s|^\\twspace\$|\\tnewlinech|
/^\\t\\twspace\$/d
s|\\([%\$]mref[^\$]*\\)/wspace/|\\1/newlinech/|
s|\$xref/wspace/\$\\\$, ||
EOF
list='
omh/dollar.omh
omh/cmark.omh
omh/newlinech.omh
omh/accent.omh
omh/rmark.omh
omh/getstarted/get_started.omh
'
for file in $list
do
	ext=`echo $file | sed -e 's|.*\.||'`
	case $ext in
		omh | c | h | sh | f | bat )
		git checkout $file
		sed -f junk.sed -i $file
		;;

		*)
		# skip
		;;
	esac
done
