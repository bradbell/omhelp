#! /bin/bash -e
#
if [ ! -e htm ]
then
	echo "mkdir htm"
	mkdir htm
fi
echo "create htm/key_character.omh"
cat << EOF > htm/key_character.omh
# \$OMHelpKeyCharacter=@
# @begin key_character@
# @dollar &@@
# @section 2012-01-25: Bug in Changing Command Character@
#
# The lexical analyzer falls into an infinite loop while scaning
# the command character change above because Help should be help.
#
# @end 
EOF
echo "cd .."
cd ..
#
for cmd in automake configure make 
do
	echo "./build.sh $cmd"
	./build.sh $cmd
done
#
echo "cd bug/htm"
cd bug/htm
#
echo "../../src/omhelp ./key_character.omh -omhelp_dir ../../OMhelp"
echo "Stuck here in an infinite loop !"
../../src/omhelp ./key_character.omh -omhelp_dir ../../OMhelp
