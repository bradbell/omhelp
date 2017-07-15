#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
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
@spell
	xml
	Firefox
	Linux
	htm
@@
@section One@@

@head Problem@@
The drop down menus in the file @href%one.xml%@@
(e.g, @code one->@@)
do not work for 32 bit Firefox 54.0.1 on Windows.
They do work for this file using 64 bit Firefox 52.0 on Linux.
They also work for the file @href%one.htm%@@ using
32 bit Firefox 54.0.1 32 on Windows.


@children%two.omh%@@

@end
EOF
echo "create htm/two.omh"
cat << EOF > htm/two.omh
@begin two@@
@section Two@@

See @cref/problem/one/Problem/@@.

@end
EOF
sed -e 's|@|$|g' -i htm/one.omh
sed -e 's|@|$|g' -i htm/two.omh
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
echo_eval ../$program ./one.omh -noframe -omhelp_dir ../../omhelp_data
echo_eval ../$program ./one.omh -noframe -xml -omhelp_dir ../../omhelp_data
# -----------------------------------------------------------------------------
if [ -e junk.sed ]
then
	rm junk.sed
fi
cat << EOF >> junk.sed
/>Prev</! b three
: one
N
/<\\/td><td>$/! b one
: two
N
/<\\/td>$/! b two
d
# ----------------------------------------------------------------------------
: three
/^var list_across/! b five
: four
N
/\\]/! b four
d
# ----------------------------------------------------------------------------
: five
/^function choose_across0/! b seven
: six
N
/}/! b six
d
# ----------------------------------------------------------------------------
: seven
s|<a href="_contents.htm" target="_top">\\([^<]*\\)<\/a>|\\1|
s|<a href="_contents_xml.htm" target="_top">\\([^<]*\\)<\/a>|\\1|
#
/<option>contents<\/option>/d
/'_contents_xml.htm'/d
/'_contents.htm'/d
#
/<option>index<\/option>/d
/'_index_xml.htm'/d
/'_index_htm'/d
#
/<option>search<\/option>/d
/'_search_xml.htm'/d
/'_search_htm'/d
#
/<option>reference<\/option>/d
/'_reference_xml.htm'/d
/'_reference_htm'/d
#
EOF
list='
	one.htm
	one.xml
	_one_htm.js
	_one_xml.js

	two.htm
	two.xml
	_two_htm.js
	_two_xml.js
'
for file in $list
do
	sed $file -f junk.sed > junk
	if ! diff $file junk > /dev/null
	then
		mv junk $file
	fi
done
# ----------------------------------------------------------------------------
list='
	one.omh
	two.omh

	_close.gif
	_closeblue.gif
	_open.gif
	_openblue.gif

	_contents.htm
	_contents_xml.htm
	_contents.js
	__contents_htm.js
	__contents_xml.js

	index.html
	_index.htm
	__index_htm.js
	_index.xml
	__index_xml.js

	_search.htm.js
	_search.xml.js
	_search.htm
	__search_htm.js
	_search_xml.htm
	__search_xml.js

	_reference.htm
	__reference_htm.js
	_reference.xml
	__reference_xml.js
'
for file in $list
do
	rm $file
done
# ----------------------------------------------------------------------------
cd ..
if [ -e $HOME/share/htm ]
then
	rm -r $HOME/share/htm
fi
cp -r htm $HOME/share/htm

