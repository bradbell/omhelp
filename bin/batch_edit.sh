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
# Script for converting syntax to a separate paragraph
cat << EOF > junk.sed
/\$table/N
/\$table\\n*\$bold Syntax/! b skip_syntax
#
: loop_syntax
N
/\$bold See Also/b end_syntax
/\$tend/! b loop_syntax
: end_syntax
s|\\([%/]\\)\$\$ *\$rnext *|\n\\1\$\$|g
s|\\([%/]\\)\$\$ *\\n\$rnext *|\n\\1\$\$|g
s|\$\$ *\$rnext *|\$\$|g
s|\$\$ *\$rend *|\$\$|g
#
s|\\([%/]\\)\$\$ *\$rend *|\n\\1\$\$|g
s|\\([%/]\\)\$\$ *\\n\$rend *|\n\\1\$\$|g
#
: loop_also
/\$tend/! N
/\$tend/! b loop_also
#
s|\\([%/]\\)\$\$ *\$rnext *|\\1\$\$|g
s|\\([%/]\\)\$\$ *\$rend *|\\1\$\$|g
s|\$\$ *\$rnext *|\$\$|g
s|\$\$ *\$rend *|\$\$|g
#
s|\\n *\$cnext *\\n|\\n|g
s|\\n *\$cnext *|\\n|g
s|\$cnext *||g
s|\\n *\$cend *\\n|\\n|g
s|\\n *\$cend *|\\n|g
s|\$cend *||g
s| *\$table *\\n||
s| *\$tend *||
s| *\$bold Syntax|\$head Syntax|
s| *\$bold See Also|\\n\$head See Also|
#
:skip_syntax
EOF
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
