#! /bin/bash -e
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
# @begin one@@
# @section 2017-07-27: Check One Spelling Warning Per Word Per Section@@
#
# First warning: notaword.
# No warning:    notaword.
#
# @children%two.omh%@@
#
# @end 
EOF
echo "create htm/two.omh"
cat << EOF > htm/two.omh
# @begin two@@
# @section 2017-07-27: Second section@@
#
# First warning: notaword.
# No warning:    notaword.
#
# @end 
EOF
sed -e 's|@|$|g' -i htm/one.omh
sed -e 's|@|$|g' -i htm/two.omh
#
if [ ! -e '../OMhelp' ]
then
	echo '../OMhelp does not exist'
	echo 'must first run: ./build.sh automake'
	exit 1
fi
echo_eval cd htm
echo_eval ../../src/omhelp ./one.omh -omhelp_dir ../../OMhelp
