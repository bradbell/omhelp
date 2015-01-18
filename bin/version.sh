#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/version.sh" ]
then
	echo "bin/version.sh: must be executed from its parent directory"
	exit 1
fi
if [ "$1" != 'get' ] && [ "$1" != 'set' ] && [ "$1" != 'copy' ]
then
	echo 'usage: bin/version.sh (get | set | copy) [version]'
	echo 'get:  Gets the current version number from CMakeLists.txt.'
	echo 'set:  Sets CMakeLists.txt version number to version.'
	echo '      If version is not present, uses current yyyy.mmdd.'
	echo 'copy: Copies version number from CMakeLists.txt to other files.'
	exit 1
fi
echo_eval() {
     echo $* 
     eval $*
}
# -----------------------------------------------------------------------------
if [ "$1" == 'set' ]
then
	if [ "$2" == '' ]
	then
		version=`date +%Y%m%d`
	else
		version="$2"
	fi
	echo 'sed -i.old CMakeLists.txt ...'
	sed  \
	-e "s/(\(omhelp_version *\)\"[0-9.]\{8\}\" *)/(\1\"$version\" )/"  \
		-i.old CMakeLists.txt
	if diff CMakeLists.txt.old CMakeLists.txt
	then
		echo 'No change in CMakeLists.txt'
		exit 1
	fi
	echo_eval rm CMakeLists.txt.old
	#
	echo 'bin/version.sh set: OK'
	exit 0
fi
# -----------------------------------------------------------------------------
# get the current version number
version=`grep '^SET *( *omhelp_version ' CMakeLists.txt | \
	sed -e 's|^SET *( *omhelp_version *"\([0-9.]\{8\}\)" *)|\1|'`
if ! (echo $version | grep '[0-9]\{8\}') > /dev/null
then
	echo 'bin/version.sh: Cannot find verison number in CMakeLists.txt'
	exit 1
fi 
if [ "$1" == 'get' ]
then
	echo "$version"
	exit 0
fi
# -----------------------------------------------------------------------------
# Make the version number in the relevant files is the same
list='
	omh/overview.omh
'
for file in $list
do
	sed -e "s/omhelp-[0-9]\{8\}/omhelp-$version/" -i.old $file
done 
for name in $list
do
	echo '-------------------------------------------------------------'
	echo "diff $name.old $name"
	if diff $name.old $name
	then
		echo '	no difference was found'
	fi
	#
	echo_eval rm $name.old
done
echo 'bin/version.sh copy: OK'
