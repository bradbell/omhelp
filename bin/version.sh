#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2017 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/version.sh" ]
then
	echo "bin/version.sh: must be executed from its parent directory"
	exit 1
fi
if [ "$1" != 'get' ] \
&& [ "$1" != 'set' ] \
&& [ "$1" != 'date' ] \
&& [ "$1" != 'copy' ] \
&& [ "$1" != 'check' ]
then
	echo 'usage: bin/version.sh (get|set|date|copy|check) [version]'
	echo 'get:   Gets the current version number from CMakeLists.txt.'
	echo 'set:   Sets CMakeLists.txt version number to version.'
	echo 'date   Sets CMakeList.txt version number to yyyymmdd.'
	echo 'copy:  Copies version number from CMakeLists.txt to other files.'
	echo 'check: Checks that CMakeLists.txt version has been copied.'
	exit 1
fi
# -----------------------------------------------------------------------------
echo_eval() {
     echo $*
     eval $*
}
# -----------------------------------------------------------------------------
if [ "$1" == 'get' ] && [ "$2" == '' ]
then
	version.sh get
	exit 0
fi
if [ "$1" == 'copy' ] || [ "$1" == 'check' ]
then
	version.sh $1 omh/overview.omh
else
	version.sh $*
fi
# -----------------------------------------------------------------------------
echo "bin/version.sh $1: OK"
