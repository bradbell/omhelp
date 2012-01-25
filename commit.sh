# ! /bin/bash
# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2010 Bradley M. Bell
# License: GNU General Public License; version 2 or higher.
# ---------------------------------------------------------------------------
# replacement text for this commit
cat << EOF > commit.$$
This is a template for making commits to the OMhelpPackage repository.
Lines with no 'at' characters, are general comments not connected to 
a specific file. Lines containing an 'at' character are "file name" 
followed by comment; for example

commit.sh@ For this example, commit.sh is the only file committed.
EOF
# -----------------------------------------------------------------------
if [ "$1" == 'files' ]
then
	cvs update 2> /dev/null | sed -n -e '/^[RAM] /p' | \
		sed -e 's/^[RAM] //' -e 's/$/@/' | sort -u
	rm commit.$$
	exit 0
fi
if [ "$1" != '' ]
then
cat << EOF
usage: ./commit.sh files
       ./commit.sh

The first from lists the files that have changed and should be
listed at the beginning of the file commit.sh.

The second form actually commits the files (provided that you reply
y to the [y/n] prompt that commit.sh generates).
EOF
	rm commit.$$
	exit 0
fi
# -----------------------------------------------------------------------
dir=`pwd | sed -e 's|.*/OMhelpPackage/\([^/]*\).*|\1|'`
list=`sed -e '/@/! d' -e 's/@.*//' commit.$$`
msg=`sed -e '/@ *$/d' -e 's|.*/\([^/]*@\)|\1|' -e 's|@|:|' commit.$$`
# -----------------------------------------------------------------------
for file in $list
do
	if [ -e $file ]
	then
		echo "sed -f commit.sed < $file > commit.$$"
		sed -f commit.sed < $file > commit.$$
		diff $file commit.$$
	fi
done
rm commit.$$
echo "--------------------------------------------------------------------"
echo "cvs commit -m \""
echo "$msg"
echo "\" \\"
echo "$list"
read -p "is this ok [y/n] ?" response
if [ "$response" != "y" ]
then
     exit 1
fi
for file in $list
do
	if [ -e $file ]
	then
		echo "sed -f commit.sed -i $file"
		sed -f commit.sed -i $file
	fi
done
#
echo "cvs commit -m '$msg' $list"
if ! cvs commit -m "$msg" $list
then
	echo "commit.sh: failed"
	exit 1
fi
#
echo "mv commit.sh commit.old"
mv commit.sh commit.old
#
echo "cvs update commit.sh"
cvs update commit.sh
