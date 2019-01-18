#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2018 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------
#
if [ -e htm ]
then
	echo_eval rm -r htm
fi
echo_eval mkdir htm
echo "create htm/one.omh"
cat << EOF > htm/one.omh
@begin one@@
@navigate%
    Current%_jump_table
%@@

@section Jump Table@@

@head 0-Header@@
If you change this header to start with 1 instead of 0,
the sub-header will be indented in the jump table.

@subhead Sub-header@@


@end
EOF
sed -e 's|@|$|g' -i htm/one.omh
#
program='../build/src/omhelp'
if [ ! -e "$program"  ]
then
	echo "$program does not exist"
	echo 'The following commands will build it:"'
	echo '	cd .. ; bin/run_cmake ; cd build ; make'
	exit 1
fi
echo_eval cd htm
echo_eval ../$program ./one.omh -omhelp_dir ../../omhelp_data