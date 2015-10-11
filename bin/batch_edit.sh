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
# Script for converting xref command to cref command
P='\([^/]*\)'
E='\$\$'
cat << EOF > junk.sed
/^\txref\$/d
#
s|\$xref *$P$E|\$cref \\1\$\$|g
s|\$xref/$P/$E|\$cref \\1\$\$|g
s|\$xref/$P/$P/$E|\$cref/\\1/\\1/\\2/\$\$|g
s|\$xref/$P/$P/$P/$E|\$cref/\\3/\\1/\\2/\$\$|g
s|\$xref/$P/$P/$P/$P/$E|\$cref/\\3/\\1/\\2/\$\$|g
s|\$xref/$P/$P/$P/$P/$P/$E|\$cref/\\4/\\1/\\2/\\3/\$\$|g
s|//\\\$\\\$|/\$\$|g
#
s|@xref *$P@@|@cref \\1@@|g
s|@xref/$P/@@|@cref \\1@@|g
s|@xref/$P/$P/@@|@cref/\\1/\\1/\\2/@@|g
s|@xref/$P/$P/$P/@@|@cref/\\3/\\1/\\2/@@|g
s|@xref/$P/$P/$P/$P/@@|@cref/\\3/\\1/\\2/@@|g
s|@xref/$P/$P/$P/$P/$P/@@|@cref/\\4/\\1/\\2/\\3/@@|g
s|//@@|/@@|g
#
/\$xref\/\$/! b skip_forward_slash
N
N
N
s|\$xref/\\n\\t$P/\\n\\t$P/\\n\\t$P/$E|\$cref/\\3\\n\\t/\\1\\n\\t/\\2/\$\$|
: skip_forward_slash
EOF
P='\([^|]*\)'
cat << EOF >> junk.sed
/\$xref|why|/! b skip_why
N
N
s/\$xref|why|\\n\\t$P|\\n\\t$P|$E/\$cref|\\2\\n\\t|why\\n\\t|\\1\\n|\$\$/
: skip_why
EOF
list=`git ls-files | sed  \
	-e '/^omh\/xref\.omh$/d' \
	-e '/^omh\/whatsnew.*\.omh$/d' \
	-e '/^bin\/batch_edit\.sh$/d'`
for file in $list
do
	git checkout $file
	ext=`echo $file | sed -e 's|.*\.||'`
	case $ext in
		omh | c | h | l | sh | f | bat )
		if grep 'xref' $file > /dev/null
		then
			sed -f junk.sed -i $file
			if grep '$xref' $file > /dev/null
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
sed -e 's|$cref/cross references/xref/|$cref/cross references/cref/|' \
	-i omh/running.omh
sed \
	-e 's|$cref/xref/xref/|$cref cref|' \
	-e 's|that section using the|the section; e.g., using the|' \
	-i omh/glossary.omh
