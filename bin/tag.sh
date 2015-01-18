#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#            Copyright (C) 2003-15 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/tag.sh" ]
then
	echo "bin/tag.sh: must be executed from its parent directory"
	exit 1
fi
option="$1"
if [ "$2" == '' ]
then
	option=''
fi
if [ "$option" != 'create' ] && [ "$option" != 'delete' ]
then
	echo 'usage: bin/tag.sh create description'
	echo '       bin/tag.sh delete version'
	exit 1
fi
if [ "$option" == 'create' ]
then
	description="$2"
else
	version="$2"
fi
# -----------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
if [ "$option" == 'delete' ]
then
	if ! git tag -n | grep "$version"
	then
		echo "git tag $version does not exist"
		exit 
	fi
	read -p 'delete this tag are you sure [yes/no] ?' response
	if [ "$response" != 'yes' ]
	then
		exit 1
	fi
	echo_eval git tag -d $version
	echo_eval git push --delete origin $version
	echo 'tag.sh: OK'
	exit 0
fi
# -----------------------------------------------------------------------------
list=`git status -s`
if [ "$list" != '' ]
then
	echo "tag.sh: 'git status -s' is not empty"
	exit 1
fi
version=`bin/version.sh get`
echo_eval bin/version.sh copy
list=`git status -s`
if [ "$list" != '' ]
then
	echo "tag.sh: 'bin/version.sh copy' changed something"
	exit 1
fi
echo "git tag -a -m \"$description\" $version"
git tag -a -m "$description" "$version"
echo_eval git push origin $version
#
echo 'tag.sh: OK'