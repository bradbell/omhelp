#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#            Copyright (C) 2003-15 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
if [ $0 != "bin/run_omhelp.sh" ]
then
	echo "bin/run_omhelp.sh: must be executed from its parent directory"
	exit 1
fi
if [ "$1" != "doc" ] && [ "$1" != "dev" ]
then
	echo 'usage: bin/run_omhelp.sh target'
	echo 'where target is doc or dev'
	exit 1
fi
if [ "$1" = dev ]
then
	if [ -e dev ]
	then
		rm -r -f dev
	fi
	mkdir dev
	cd    dev
	if ! ../build/src/omhelp ../src/omh/omhelp.omh > ../omhelp.dev.log \
		-debug -omhelp_dir ../OMhelp
	then
		cat ../omhelp.dev.log
		echo "OMhelp could not build developer documentation."
		echo "See the complete error message in omhelp.dev.log."
		grep "^OMhelp Error:" ../omhelp.dev.log
		exit 1
	fi
	cd ..
	if grep "^OMhelp Warning:" omhelp.dev.log
	then
		echo "See the complete warning messages in omhelp.dev.log."
		exit 1
	fi
fi
if [ "$1" = doc ]
then
	if [ ! -e omhelp.dev.log ]
	then
		echo 'must run bin/run_omhelp.sh dev'
		echo 'before   bin/run_omhelp.sh doc'
		exit 1
	fi
	if [ -e doc ]
	then
		rm -r -f doc
	fi
	mkdir doc
	cd    doc
	if ! ../build/src/omhelp ../omh/overview.omh > ../omhelp.doc.log \
		-noframe -xml -debug -omhelp_dir ../OMhelp
	then
		cat ../omhelp.dev.log
		echo "OMhelp could not build user documentation."
		echo "See the complete error message in omhelp.doc.log."
		grep "^OMhelp Error:" ../omhelp.doc.log
		exit 1
	fi
	../build/src/omhelp ../omh/overview.omh  -noframe -debug -omhelp_dir ../OMhelp
	cd ..
	if grep "^OMhelp Warning:" omhelp.doc.log
	then
		echo "See the complete warning messages in omhelp.doc.log."
	fi
fi
echo 'run_omhelp.sh OK'
exit 0
