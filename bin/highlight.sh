#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2015 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
# $begin highlight.sh$$ $newlinech #$$
# $spell
#	srcdir
#	bindir
#	lang
# $$
#
# $section Add Languages to source-highlight Package$$
#
# $head Syntax$$
# $codei%bin/highlight.sh %srcdir% %bindir%$$
#
# $head srcdir$$
# This is the source code directory corresponding to the
# source-highlight package; e.g,
# $codei%
#	%source-highlight-3.1.8%
# %$$
#
# $head bindir$$
# The directory used to build the source-highlight package; i.e.,
# where the $code configure$$ command was executed.
#
# $head Octave$$
# Currently, this command only adds the Octave language to the list of
# $href%https://www.gnu.org/software/src-highlite/source-highlight.html#Supported-languages
# %supported languages%$$. The corresponding file extension is
# $codep
#	m = octave.lang
# $$.
#
# $head Errors$$
# If this script fails for some reason, you may be able to accomplish its
# goals by reading its source code comments and performing the operations
# by hand.
#
# $end
# -----------------------------------------------------------------------------
if [ ! -e "bin/highlight.sh" ]
then
	echo "bin/highlight.sh: must be executed from its parent directory"
	exit 1
fi
# -----------------------------------------------------------------------------
if [ "$2" == '' ]
then
cat << EOF
bin/highlight.sh srcdir bindir
srcdir: directory containing the soucre code for source-highlight.
bindir: directory where source-highlight configure command was executed.

This will add Octave to the source-highlight languages and then
re-execute the configure and make install commands.
EOF
	exit 1
fi
srcdir="$1"
bindir="$2"
# -----------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
echo '------------------------------------------------------------------------'
echo 'copy octave.lang and octave.style to srcdir/src directory'
for ext in lang style
do
	target="$srcdir/src/octave.$ext"
	if [ -e "$target" ]
	then
		if ! diff highlight/octave.$ext $target > /dev/null
		then
			echo "existing $target is not as expected"
			exit 1
		fi
	else
		echo_eval cp highlight/octave.$ext "$target"
	fi
done
ls $srcdir/src/octave.style $srcdir/src/octave.lang
echo '------------------------------------------------------------------------'
echo 'Edit srcdir/src/Makefile.in in the following way:'
echo 'Add octave.style to STYLEFILES and octave.lang to LANGFILES'
cat << EOF > junk.sed
/^STYLEFILES *=/! b one
s| *octave.style *||
s|$|& octave.style|
b end
#
: one
/^LANGFILES *=/! b end
: repeat
N
/\\\\$/b repeat
s| *octave.lang *||
s|$|& octave.lang|
#
: end
EOF
if [ ! -e "$srcdir/src/Makefile.bak" ]
then
	echo_eval cp "$srcdir/src/Makefile.in" "$srcdir/src/Makefile.bak"
fi
sed -f junk.sed "$srcdir/src/Makefile.bak" \
	> "$srcdir/src/Makefile.in"
echo "Changes to $srcdir/src/Makefile.in"
if diff "$srcdir/src/Makefile.bak" "$srcdir/src/Makefile.in"
then
	echo 'highlight.sh: Error: cannot change Makefile.in'
	exit 1
fi
echo '------------------------------------------------------------------------'
echo 'Edit srcdir/src/lang.map in the following way:'
echo 'Add m = octave.lang'
if [ ! -e "$srcdir/src/lang.bak" ]
then
	echo_eval cp "$srcdir/src/lang.map" "$srcdir/src/lang.bak"
fi
sed -e '$,$s|$|\nm = octave.lang|' "$srcdir/src/lang.bak" \
	> "$srcdir/src/lang.map"
echo "Changes to $srcdir/src/lang.map"
if diff "$srcdir/src/lang.bak" "$srcdir/src/lang.map"
then
	echo 'highlight.sh: Error: cannot change lang.map'
	exit 1
fi
echo '------------------------------------------------------------------------'
echo 're-execute the configure command'
echo 'It is assumed that you already executed it without these changes'
if !  cd $bindir
then
	echo "cannot change into bindir=$bindir"
	exit 1
fi
cat << EOF > junk.sed
/Invocation command line was/! b end
s/.*Invocation command line was//
N
s/\n//
N
s/\n//
/^ *\\$/! b end
s/^ *\\$//
p
: end
EOF
configure_command=`sed -n -f junk.sed config.log`
echo "configure_command=$configure_command"
#
# re-execute configure command
if ! $configure_command
then
	echo 're-executing configure_command failed'
	exit 1
fi
echo '------------------------------------------------------------------------'
echo 'make install'
make install
# ----------------------------------------------------------------------------
echo 'bin/highlight.sh: OK'
exit 0
