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
if [ "$1" != 'create' ] && [ "$1" != 'delete' ]
then
	echo 'usage: bin/tag.sh create description'
	echo '       bin/tage.s delete tag_name'
	exit 1
fi
# -----------------------------------------------------------------------------
if [ "$option" == 'delete' ]
then
	tag_name="$2"
	if ! tag | grep "$tag_name"
	then
		echo "git tag $tag_name does not exist"
		exit 
	fi
	read -p 'delete this tag are you sure [yes/no] ?' response
	if [ "$response" != 'yes' ]
	then
		exit 1
	fi
	git tag -d "$tag_name"
	exit 0
fi
# -----------------------------------------------------------------------------
