#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2016 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
move_list='
	omh/src.omh
	omh/no_src.omh
	omh/getstarted/src_example.omh
	omh/getstarted/src_example.py
	omh/getstarted/start_src.omh
'
move_sed='s|src|srcfile|'
#
no_change_list='
	src/relative.c
'
cat << EOF > junk.sed
s|src_example\.|srcfile_example.|
s|src_omh|srcfile_omh|
s|src\.omh|srcfile.omh|
s|^\\tsrc\$|&\\n\\tsrcfile|
#
s|\$src\\([^a-z_]\)|\$srcfile\\1|g
s|\$cref src\\([^a-z_]\)|\$cref srcfile\\1|g
s|\$head src\\([^a-z_]\)|\$head srcfile\\1|g
s|\$begin src\\([^a-z_]\)|\$begin srcfile\\1|g
s|\$mref/src/|\$mref/srcfile/|g
s|@src\\([^a-z_]\)|@srcfile\\1|g
#
s|\\tsrc py newline|\\tsrcfile py newline|
EOF
# -----------------------------------------------------------------------------
if [ $0 != "bin/batch_edit.sh" ]
then
	echo "bin/batch_edit.sh: must be executed from its parent directory"
	exit 1
fi
# -----------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
cp bin/batch_edit.sh $HOME/trash/batch_edit.sh
git reset --hard
# ---------------------------------------------------------------------------
list_all=`bin/ls_files.sh`
for file in $list_all
do
	if [ "$file" != 'bin/batch_edit.sh' ]
	then
		echo_eval sed -f junk.sed -i $file
	fi
done
# ----------------------------------------------------------------------------
for old in $move_list
do
	new=`echo $old | sed -e "$move_sed"`
	echo_eval git mv $old $new
done
# ----------------------------------------------------------------------------
# files that were hand edited and cached using 'git_new.sh to'
if [ -e new ]
then
	echo_eval git_new.sh from
fi
# ----------------------------------------------------------------------------
# file that should not change
for file in $no_change_list
do
	echo_eval git checkout $file
done
# ----------------------------------------------------------------------------
cp $HOME/trash/batch_edit.sh bin/batch_edit.sh
# ----------------------------------------------------------------------------
echo "$0: OK"
exit 0
