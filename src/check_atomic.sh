#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
#  Check the entries in the file LatexAtomic.c
#
byalpha="http://www.w3.org/TR/MathML2/byalpha.html"
if [ ! -e byalpha.html ]
then
	echo "wget byalpha.html"
	wget $byalpha
fi
#
if [  ! -e byalpha.txt ]
then
	echo "create byalpha.txt"
	sed < byalpha.html > byalpha.txt \
		-e '1,/Previous:/d'  \
		-e '/<\/pre>/,$d' \
		-e 's/.*<pre>//' \
		-e 's/, */, /' \
		-e 's/\([^,]*\), *U\([^,]*\),.*/\1_\2/'
fi
if [  -e LatexAtomic.txt ]
then
	echo "create LatexAtomic.txt"
cat << EOF > LatexAtomic.sed
1,/MATHML NAM/d
/^}; *$/,\$d
: loop
/}/b end_loop
N
b loop
: end_loop
/\t\/\/ *\n/d
s/\n//
s/\n//
s/\n//
s/\t//
s/[^,]*,//
s/[^,]*,//
s/^\t//
s|// "&||
s/;",\t*"&#x/_/
s/;".*//
: skip
EOF
	sed -f LatexAtomic.sed < LatexAtomic.c > LatexAtomic.txt
fi
list=`cat LatexAtomic.txt`
for text in $list
do
	if ! grep "^$text"  byalpha.txt > /dev/null
	then
		echo "cannot find $text"
	fi
done
