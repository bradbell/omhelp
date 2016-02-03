#! /bin/bash -e
# -----------------------------------------------------------------------------
# OMhelp: Language Independent Embedded Documentation
#           Copyright (C) 1998-2016 Bradley M. Bell
# OMhelp is distributed under the terms of the
#             GNU General Public License Version 2.
# -----------------------------------------------------------------------------
move_list='
	omh/getstarted/srcfile_example.omh
	omh/getstarted/srcfile_example.py
	omh/getstarted/start_srcfile.omh
'
move_sed='s|srcfile|src|'
#
no_change_list='
'
cat << EOF > junk.sed
s|srcfile_example|src_example|g
s|srcfile_omh|src_omh|g
s|start_srcfile|start_src|g
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
	if [ ! -e $old ]
	then
		echo "Cannot move file $old (does not exist)"
		cp bin/batch_edit.sh $HOME/trash/batch_edit.sh
		exit 1
	fi
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
