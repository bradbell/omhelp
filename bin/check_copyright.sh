#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2016 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/check_copyright.sh" ]
then
	echo "bin/check_copyright.sh: must be executed from its parent directory"
	exit 1
fi
if [ ! -e .git ]
then
	echo 'This is not a git repository so cannot check copyright.'
	echo 'check_copyright.sh: skipped'
	exit 0
fi
list=`git status |\
	 sed -n \
        -e '/^[#\t ]*modified:/p' \
        -e '/^[#\t ]*both modified:/p' \
        -e '/^[#\t ]*renamed:/p' \
        -e '/^[#\t ]*new file:/p' | \
	sed -e 's/^.*: *//' -e 's/.* -> *//' | \
	sed \
		-e '/makefile.in$/d' \
		-e '/^src\/omhelp.c$/d' \
		-e '/^.gitignore$/d' | \
	sort -u`
cat << EOF > check_copyright.1.$$
# Change copyright second year to current year
s/Copyright (C) \\([0-9]\\{4\\}\\)-[0-9]* Bradley M. Bell/Copyright (C) \\1-2016 Bradley M. Bell/
EOF
ok=true
for file in $list
do
	if ! grep 'Copyright (C) [0-9]\{4\}-[0-9]* Bradley M. Bell' $file \
		> /dev/null
	then
		echo 'bin/check_copyright.sh: cannot find copyrigh in'
		echo "$file"
		rm check_copyright.*.$$
		exit 1
	fi
	if [ -e $file ]
	then
		sed -f check_copyright.1.$$ $file > check_copyright.2.$$
		if ! diff $file check_copyright.2.$$ > /dev/null
		then
			echo '----------------------------------------------------'
			echo "check_copyright.sh: automatic changes to $file:"
			if diff $file check_copyright.2.$$
			then
				echo 'bin/check_copyright.sh: program error'
				rm check_copyright.*.$$
				exit 1
			fi
			ok='no'
			if [ -x $file ]
			then
				mv check_copyright.2.$$ $file
				chmod +x $file
			else
				mv check_copyright.2.$$ $file
			fi
		fi
	fi
done
if [ "$ok" == 'no' ]
then
	rm check_copyright.*.$$
	exit 1
fi
rm check_copyright.*.$$
# ----------------------------------------------------------------------------
echo "$0: OK"
exit 0
