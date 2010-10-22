#!/bin/bash
# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2010 Bradley M. Bell
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# ---------------------------------------------------------------------------
#
# Build distribution
#
# Default values used for arguments to configure during this script.
# These defaults are development system dependent and can be changed.
VIMRUNTIME=/usr/share/vim/vim71
#
# date currently in configure.ac
AcDate=`grep "^ *AC_INIT(" configure.ac | \
	sed -e "s/.*, *\([0-9][0-9]-[0-9][0-9]-[0-9][0-9]\) *,.*/\1/"`
#
# version
#
if [ "$1" = "version" ] || [ "$1" = "all" ]
then
	#
	# Today's date in yy-mm-dd decimal digit format with leading zeros
	Today=`date +%g-%m-%d`
	#
	sed configure.ac > configure.tmp -e \
	"s/(OMhelp, [0-9][0-9]-[0-9][0-9]-[0-9][0-9],/(OMhelp, $Today,/"
	#
	diff configure.ac  configure.tmp
	mv   configure.tmp configure.ac
	#
	# change Autoconf date to today
	AcDate=$Today
	#
	sed omh/overview.omh > overview.tmp -e \
	"s/Version [0-9][0-9]-[0-9][0-9]-[0-9][0-9]/Version $Today/g"
	#
	diff omh/overview.omh overview.tmp
	mv   overview.tmp     omh/overview.omh
	#
	# configure file is out of date so remove it
	if [ -e configure ]
	then
		rm configure
	fi
	#
	if [ "$1" != "all" ]
	then
		exit 0
	fi
fi
#
# aclocal
#
if [ "$1" = "automake" ] || [ "$1" = "all" ]
then
	if [ -e configure ]
	then
		rm configure
	fi
	echo "---------------------------------------------------------"
	echo "If aclocal generates warning messages, try running ./FixAclocal"
	echo "aclocal"
	if ! aclocal
	then
		echo "build.sh: aclocal failed."
		exit 1
	fi
	echo "---------------------------------------------------------"
	#
	echo "autoheader"
	if ! autoheader
	then
		echo "build.sh: autoheader failed."
		exit 1
	fi
	#
	echo "autoconf"
	if ! autoconf
	then
		echo "build.sh: autoconf failed."
		exit 1
	fi
	#
	echo "automake -add-missing"
	if ! automake --add-missing
	then
		echo "build.sh: automake failed."
		exit 1
	fi
	#
	if [ "$1" != "all" ]
	then
		exit 0
	fi
fi
#
# configure
#
if [ "$1" = "configure" ] || [ "$1" = "all" ]
then
	#
	if [ -e $VIMRUNTIME/syntax ]
	then
		TMP="VIMRUNTIME=$VIMRUNTIME"
	else
		TMP=""
	fi
	echo "./configure $TMP"
	if ! ./configure $TMP 
	then
		echo "build.sh: configure failed."
		exit 1
	fi
	#
	# Fix Makefile for what appears to be a bug in gzip under cygwin
	echo "FixMakefile"
	./FixMakefile
	#
	if [ "$1" != "all" ]
	then
		exit 0
	fi
fi
#
# compile
#
if [ "$1" = "make" ] || [ "$1" = "all" ]
then
	# remove Doc, Dev and OMhelp/dictionay.bin becasue they are
	# created by make (see ./Makefile.am).
	if [ -e Doc ]    ; then rm -r Doc ; fi
	if [ -e Dev ]    ; then rm -r Dev ; fi
	if [ -e OMhelp/dictionary.bin ] ; then rm OMhelp/dictionary.bin ; fi
	#
	echo "make"
	if ! make
	then
		echo "build.sh: make failed."
		exit 1
	fi
	#
	if [ "$1" != "all" ]
	then
		exit 0
	fi
fi
#
# dist
if [ "$1" = "dist" ] || [ "$1" = "all" ]
then
	#
	if [ -e omhelp-$AcDate ]
	then
		echo "rm -r omhelp-$AcDate"
		rm -r omhelp-$AcDate
	fi
	for file in OMhelp.dos.zip OMhelp.unix.tar.gz
	do
		if [ -e $file ]
		then
			echo "rm $file"
			if ! rm $file
			then
				echo "build.sh rm $file failed."
				exit 1
			fi
		fi
	done
	#
	echo "make dist"
	if ! make dist
	then
		echo "build.sh make dist failed."
		exit 1
	fi
	#
	if [ ! -e omhelp-$AcDate.tar.gz ]
	then
		echo "build.sh: omhelp-$AcDate.tar.gz does not exist"
		echo "perhaps version is out of date"
		#
		exit 1
	fi
	#
	# create the unix version
	mv omhelp-$AcDate.tar.gz OMhelp.unix.tar.gz
	#
	if [ "$1" != "all" ]
	then
		exit 0
	fi
fi
if [ "$1" = "dos" ] || ( [ "$1" = "all" ] && [ "$2" != "unix" ] )
then
	if [ ! -e src/src.exe ]
	then
		echo "Must use MS project to build src.exe before executing"
		echo "build.sh dos"
		exit 1 
	fi
	if [ ! -e OMhelp.unix.tar.gz ]
	then
		echo "Must build unix version before executing: build.sh dos"
		exit 0
	fi
	#
	if [ -e omhelp-$AcDate ]
	then
		echo "rm -r omhelp-$AcDate"
		if ! rm -r omhelp-$AcDate
		then
			echo "build.sh: rm -r omhelp-$AcDate failed."
			exit 1
		fi
	fi
	if [ -e OMhelp.dos.zip ]
	then
		echo "rm OMhelp.dos.zip"
		if ! rm OMhelp.dos.zip
		then
			echo "build.sh: rm -r OMhelp.dos.zip failed."
			exit 1
		fi
	fi
	#
	# extract from compressed tar
	tar -xvzf OMhelp.unix.tar.gz 
	#
	if [ ! -e omhelp-$AcDate ]
	then
		echo "build.sh: omhelp-$AcDate.tar.gz does not exist"
		echo "perhaps OMhelp.unix.tar.gz is out of date"
		#
		exit 1
	fi
	#
	# convert files to dos format
	for file in  omhelp-$AcDate/*
	do
		if [ -f $file ]
		then
			if ! unix2dos $file
			then
				echo "build.sh: unix2dos $file failed."
				exit 1
			fi
		fi
	done
	for file in omhelp-$AcDate/OMhelp/*.wrd omhelp-$AcDate/OMhelp/*.xsl
	do
		if [ -f $file ]
		then
			if ! unix2dos $file
			then
				echo "build.sh: unix2dos $file failed."
				exit 1
			fi
		fi
	done
	for dir in \
		omh/getstarted 
	do
		for file in \
			omhelp-$AcDate/$dir/*.omh \
			omhelp-$AcDate/$dir/*.dat \
			omhelp-$AcDate/$dir/*.c
		do
			if ! unix2dos $file
			then
				echo "build.sh: unix2dos $file failed."
				exit 1
			fi
		done
	done
	for dir in \
		src \
		src/omh \
		omh \
		omh/latex
	do
		for file in omhelp-$AcDate/$dir/*
		do
			if [ -f $file ]
			then
				if ! unix2dos $file
				then
					echo "build.sh: unix2dos $file failed."
					exit 1
				fi
			fi
		done
	done
	#
	# copy the executable to the distribution
	echo "cp src/src.exe omhelp-$AcDate/src/src.exe"
	if ! cp src/src.exe omhelp-$AcDate/src/src.exe
	then
		echo "build.sh copy src/src.exe failed."
		exit 1
	fi
	#
	# Make sure that dates in certain files are in certain order
	# (necessary because of unix2dos conversion above)
	touch omhelp-$AcDate/aclocal.m4
	sleep 2
	touch omhelp-$AcDate/src/config.h.in
	sleep 2
	touch omhelp-$AcDate/Makefile.in
	touch omhelp-$AcDate/*/Makefile.in
	sleep 2
	touch omhelp-$AcDate/configure
	#
	# create the dos version
	echo "zip -r OMhelp.dos.zip omhelp-$AcDate"
	if ! zip -r OMhelp.dos.zip omhelp-$AcDate
	then
		echo "zip -r OMhelp.dos.zip omhelp-$AcDate failed."
		exit 1
	fi
	#
	# clean up
	echo "rm -r omhelp-$AcDate"
	if ! rm -r omhelp-$AcDate
	then
		echo "rm -r omhelp-$AcDate failed."
		exit 1
	fi
	#
	if [ "$1" != "all" ]
	then
		exit 0
	fi
fi
if [ "$1" = "test" ] || [ "$1" = "all" ] 
then
	echo "tar -xvzf OMhelp.unix.tar.gz"
	if ! tar -xvzf OMhelp.unix.tar.gz
	then
		echo "tar -xvzf OMhelp.unix.tar.gz failed."
		exit 1
	fi
	if ! cd omhelp-$AcDate
	then
		echo "cd omhelp-$AcDate failed."
		exit 1
	fi
	if ! ./build.sh configure
	then
		echo "build.sh: build.sh configure failed."
		exit 1
	fi
	if ! make
	then
		echo "build.sh: make failed."
		exit 1
	fi
	cd omh/getstarted
	if ! ./run_all.sh batch
	then
		echo "build.sh: omh/getstarted/run_all.sh failed to run"
		exit 1
	fi
	if ! ./run_all
	then
		echo "build.sh: a omh/getstarted/run_all.c test failed"
		exit 1
	fi
	if [ "$1" != "all" ]
	then
		exit 0
	fi
fi
if [ "$1" = "all" ]
then
        exit
fi
#
if [ "$1" = "" ]
then
	echo "usage: build.sh option (where valid options are listed below)" 
else
	echo "$1 is not a valid option (valid options are listed below)"
fi
echo "option"
echo "------"
echo "version     update configure.ac and Doc.omh version number"
echo "automake    run autoconf and automake to create configure script"
echo "configure   run configure script to create make files"
echo "make        compile omhlep and use it to build its documentaiton"
echo "dist        create the distribution files OMhelp.unix.tar.gz"
echo "dos         create the distribution files OMhelp.dos.zip"
echo "test        unpack and test unix distribution"
echo
echo "build.sh all: This command executes all the options in the order above"
echo
echo "build.sh all unix"
echo "This command executes all the options in the order above"
echo "with the exception that \"dos\" will be excluded."
