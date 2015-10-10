#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ ! -e "bin/new_copyright.sh" ]
then
	echo "bin/new_copyright.sh: must be executed from its parent directory"
	exit 1
fi
# -----------------------------------------------------------------------------
if [ "$1" == "" ]
then
	echo "bin/new_copyright.sh: file_name"
	exit 1
fi
file_name="$1"
if [ ! -e "$file_name" ]
then
	echo "$file_name does not exist"
	exit 1
fi
# -----------------------------------------------------------------------------
# check for first version of old copyright
sed -n -e '1,19p' $file_name           > junk1.$$
sed -e 's|1998-[0-9]\{4\}|1998-2015|' -i junk1.$$
if diff junk1.$$ bin/old_copyright.txt > /dev/null
then
	sed -e '1,19d' -i $file_name
fi
# -----------------------------------------------------------------------------
# check for second version of old copyright
sed -e '1,1d' -e '19,19d' bin/old_copyright.txt      > junk1.$$
sed -n -e '1,17p' $file_name                         > junk2.$$
sed \
	-e 's|1998-[0-9]\{4\}|1998-2015|' \
	-e 's|^c|#|'  \
	-e 's|^/\* -|# -----|' \
	-e 's|^\(-*\) \*/|\1---|' \
	-e 's|^$|#|' \
	-e 's|^[^#]|# &|' \
	-i junk2.$$
if diff junk1.$$ junk2.$$ > /dev/null
then
	sed -e '1,17d' -i $file_name
fi
# -----------------------------------------------------------------------------
# check for third version of old copyright
sed -n -e '1,18p' $file_name                         > junk2.$$
sed \
	-e 's|1998-[0-9]\{4\}|1998-2015|' \
	-e '/^#! \/bin\/bash/d' \
	-i junk2.$$
if diff junk1.$$ junk2.$$ > /dev/null
then
	sed -e '1,18d' -i $file_name
fi
# -----------------------------------------------------------------------------
# check for fourth version of old copyright
sed -n -e '1,20p' $file_name                         > junk2.$$
sed \
	-e 's|1998-[0-9]\{4\}|1998-2015|' \
	-e '/^# ifndef/d' \
	-e '/^# define/N' \
	-e '/^# define [A-Z0-9_]* *\n *$/d' \
	-e 's|^/\* -|-----|' \
	-e 's|^\(-*\) \*/|\1---|' \
	-e 's|^$|#|' \
	-e 's|^[^#]|# &|' \
	-i junk2.$$
if diff junk1.$$ junk2.$$ > /dev/null
then
	sed -e '1,20d' -i $file_name
fi
# mv junk1.$$ junk1
# mv junk2.$$ junk2
# exit 0
# -----------------------------------------------------------------------------
# check for fifth version of old copyright
sed -n -e '1,19p' $file_name                         > junk2.$$
sed \
	-e 's|1998-[0-9]\{4\}|1998-2015|' \
	-e '/^\/\/ BEGIN SHORT COPYRIGHT/d' \
	-e '/^\/\/ END SHORT COPYRIGHT/d' \
	-e 's|^/\* -|-----|' \
	-e 's|^\(-*\) \*/|\1---|' \
	-e 's|^$|#|' \
	-e 's|^[^#]|# &|' \
	-i junk2.$$
if diff junk1.$$ junk2.$$ > /dev/null
then
	sed -e '1,20d' -i $file_name
fi
# -----------------------------------------------------------------------------
# check for sixth version of old copyright
sed -n -e '1,22p' $file_name                         > junk2.$$
sed \
	-e 's|1998-[0-9]\{4\}|1998-2015|' \
	-e '/^\/\/ BEGIN SHORT COPYRIGHT/d' \
	-e '/^\/\/ END SHORT COPYRIGHT/d' \
	-e '/^# ifndef/d' \
	-e '/^# define/N' \
	-e '/^# define [A-Z0-9_]* *\n *$/d' \
	-e 's|^/\* -|-----|' \
	-e 's|^\(-*\) \*/|\1---|' \
	-e 's|^$|#|' \
	-e 's|^[^#]|# &|' \
	-i junk2.$$
if diff junk1.$$ junk2.$$ > /dev/null
then
	sed -e '1,22d' -i $file_name
fi
# =============================================================================
# write new version of copyright message to junk1.$$
ext=`echo $file_name | sed -e 's/.*\.//'`
case $ext in
	omh)
	cat << EOF  > junk1.$$
-------------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
-------------------------------------------------------------------------------
EOF
	;;

	c)
	cat << EOF  > junk1.$$
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
EOF
	;;

	h)
	name=`echo $file_name | sed \
		-e 's|.*/||' \
		-e 's|\.h||' \
		-e 's|\([a-z]\)\([A-Z]\)|\1_\2|' | tr [a-z] [A-Z]`
	cat << EOF  > junk1.$$
# ifndef ${name}_INCLUDED
# define ${name}_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
EOF
	;;

	sh)
	cat << EOF  > junk1.$$
#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
EOF
	chmod +x junk1.$$
	;;

	f)
	cat << EOF  > junk1.$$
c -----------------------------------------------------------------------------
c OMhelp: Language Independent Embedded Documentation
c           Copyright (C) 1998-2015 Bradley M. Bell
c OMhelp is distributed under the terms of the
c             GNU General Public License Version 2.
c -----------------------------------------------------------------------------
EOF
	;;

	bat)
	cat << EOF  > junk1.$$
ECHO off
REM ---------------------------------------------------------------------------
REM OMhelp: Language Independent Embedded Documentation
REM           Copyright (C) 1998-2015 Bradley M. Bell
REM OMhelp is distributed under the terms of the
REM             GNU General Public License Version 2.
REM ---------------------------------------------------------------------------
ECHO on
EOF
	;;


	*)
	echo bin/"new_copyright.sh: extension $ext is not yet supported"
	rm junk1.$$
	rm junk2.$$
	exit 1
esac
#
# Add check for execution directory to scripts in bin/*.sh files
if ( echo $file_name | grep 'bin/[^.]*\.sh$' > /dev/null )
then
	cat << EOF >> junk1.$$
if [ \$0 != "$file_name" ]
then
	echo "$file_name: must be executed from its parent directory"
	exit 1
fi
EOF
fi
# =============================================================================
# check for new version of copyright
length=`wc -l junk1.$$ | sed -e 's|^\([0-9]*\) .*|\1|'`
sed -n -e "1,${length}p" $file_name    > junk2.$$
sed -e 's|1998-[0-9]\{4\}|1998-2015|' -i junk2.$$
if diff junk1.$$ junk2.$$ > /dev/null
then
	sed -e "1,${length}d" -i $file_name
fi
# -----------------------------------------------------------------------------
# make sure no copyright messages left
if grep 'Copyright (C)' $file_name
then
	echo "$file_name has an unknown Copyright message in it"
	exit 1
fi
# -----------------------------------------------------------------------------
cat $file_name >> junk1.$$
mv junk1.$$ $file_name
# -----------------------------------------------------------------------------
rm junk2.$$
echo "new_copyright.sh: OK"
