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
if [ "$1" != "Doc" ] && [ "$1" != "dev" ]
then
	echo "RunOMhelp target: where target is Doc or dev"
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
	if ! ../build/src/omhelp ../src/omh/omhelp.omh > ../OMhelp.dev.log \
		-debug -omhelp_dir ../OMhelp
	then
		grep "^OMhelp Error:" ../OMhelp.dev.log
		echo "OMhelp could not build developer documentation."
		echo "See the complete error message in OMhelp.dev.log."
		exit 1
	fi
	cd ..
	if grep "^OMhelp Warning:" OMhelp.dev.log
	then
		echo "See the complete warning messages in OMhelp.dev.log."
		exit 1
	fi
fi
if [ "$1" = Doc ]
then
	if [ ! -e OMhelp.dev.log ]
	then
		echo "Must run \"./RunOMhelp dev\" before \"./RunOMhelp Doc\""
		exit 1
	fi
	echo "Building user documentation"
	if [ -e Doc ]
	then
		rm -r -f Doc
	fi
	mkdir Doc
	cd    Doc
	if ! ../build/src/omhelp ../omh/overview.omh > ../OMhelp.Doc.log \
		-noframe -xml -debug -omhelp_dir ../OMhelp
	then
		grep "^OMhelp Error:" ../OMhelp.Doc.log
		echo "OMhelp could not build user documentation."
		echo "See the complete error message in OMhelp.Doc.log."
		exit 1
	fi
	../build/src/omhelp ../omh/overview.omh  -noframe -debug -omhelp_dir ../OMhelp
	cd ..
	if grep "^OMhelp Warning:" OMhelp.Doc.log
	then
		echo "See the complete warning messages in OMhelp.Doc.log."
	fi
fi
echo 'run_omhelp.sh OK'
exit 0
