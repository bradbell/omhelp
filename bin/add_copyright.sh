#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ ! -e "bin/add_copyright.sh" ]
then
	echo "bin/add_copyright.sh: must be executed from its parent directory"
	exit 1
fi
# -----------------------------------------------------------------------------
if [ "$1" == "" ]
then
	echo "bin/add_copyright.sh: file_name"
	exit 1
fi
file_name="$1"
if [ ! -e "$file_name" ]
then
	echo "$file_name does not exist"
	exit 1
fi
ext=`echo $file_name | sed -e 's/.*\.//'`
if [ "$ext" == "" ]
then
	echo "bin/add_copyright.sh: file_name does not have an extension"
	exit 1
fi
# -----------------------------------------------------------------------------
sed -n -e '1,17p' $file_name > add_copyright.$$
if diff add_copyright.$$ bin/old_copyright.txt
then
	echo "add_copyright.sh: remove old copyright from $file_name"
	sed -e '1,17d' -i $file_name
fi
# -----------------------------------------------------------------------------
#
echo "write copyright message to bin/add_copyright.$$"
case $ext in
	c | h | omh)
	cat << EOF  > bin/add_copyright.$$
/* -----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
EOF
	;;

	sh)
	cat << EOF  > bin/add_copyright.$$
#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
EOF
	echo "chmod +x bin/add_copyright.$$"
	      chmod +x bin/add_copyright.$$
	;;

	*)
	echo bin/"add_copyright.sh: extension $ext is not yet supported"
	exit 1
esac
#
# Add check for execution directory to scripts in bin/*.sh files
if ( echo $file_name | grep 'bin/[^.]*\.sh$' > /dev/null )
then
	cat << EOF >> bin/add_copyright.$$
if [ \$0 != "$file_name" ]
then
	echo "$file_name: must be executed from its parent directory"
	exit 1
fi
EOF
fi
#
echo "cat $file_name >> bin/add_copyright.$$"
      cat $file_name >> bin/add_copyright.$$
#
echo "mv $file_name ~/trash"
      mv $file_name ~/trash
#
echo "mv bin/add_copyright.$$ $file_name"
      mv bin/add_copyright.$$ $file_name
