# ----------------------------------------------------------------------------
# None of the lists below can have white space or a dollar sign in an entry.
#
# list of directories that are added to the repository by batch_edit.sh
# new_directories='
# '
# list of files that are deleted by batch_edit.sh
# delete_files='
# '
# List of files that are not edited by the sed commands in this file
# (with the possible exception of the extra_seds commands).
# The files in bin/devel.sh ignore_files are automatically in this list.
# ignore_files='
# '
# list of files and or directories that are moved to new names
# move_paths='
# '
# list of sed commands that map old file and directory names to new names.
# The characters @s, @d, @n get converted to a space, dollar sign, new line.
# move_seds='
# '
# list of files that get edited by the extra_seds command
# extra_files='
#	omh/getstarted/get_started.omh.in
#	omh/getstarted/start_simple.omh
#	omh/getstarted/start_image.omh
#	omh/getstarted/start_verbatim.omh
#	omh/getstarted/start_src.omh
#	omh/getstarted/start_block.omh
#	omh/getstarted/start_oneline.omh
#	omh/getstarted/start_multiple.omh
#	omh/getstarted/start_cref.omh
#	omh/getstarted/start_index.omh
#	omh/getstarted/start_head.omh
#	omh/getstarted/start_pre.omh
#	omh/getstarted/start_font.omh
#	omh/getstarted/start_latex.omh
#	omh/getstarted/start_spell.omh
# '
# list of sed commands that are applied to the extra files,
# after the other sed commands in this file.
# The characters @s, @d, @n get converted to a space, dollar sign, new line.
# extra_seds='
#	s|@dspell|&@n\txam|
# '
# ----------------------------------------------------------------------------
# Put other sed commands below here and without # at start of line
s|/get_started [Dd]irectory/get_started/get_started Directory/|/xam directory/get_started/xam Directory/|
s|%get_started [Dd]irectory%get_started%get_started Directory%|%xam directory%get_started%xam Directory%|
