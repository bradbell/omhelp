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
@begin one@@
@section 2014-12-20: Demonstrate missing error message@@

@index erf@@

@end 
EOF
sed -e 's|@|$|g' -i htm/one.omh
#
if [ ! -e '../OMhelp' ]
then
	echo '../OMhelp does not exist'
	echo 'must first run: ./build.sh automake'
	exit 1
fi
echo_eval cd htm
echo_eval ../../src/omhelp ./one.omh -xml -omhelp_dir ../../OMhelp
