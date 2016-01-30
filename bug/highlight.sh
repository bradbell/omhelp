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
cat << EOF
This is a test of using the soure-highlight C++ library (not a bug).
EOF
# ----------------------------------------------------------------------------
if [ ! -e build ]
then
	echo_eval mkdir build
fi
echo_eval cd build
# ----------------------------------------------------------------------------
cat << EOF > hilite.cpp
# include <iostream>
# include <fstream>
# include <sstream>
# include "srchilite/sourcehighlight.h"
# include "srchilite/langmap.h"

# define DATADIR "/home/bradbell/prefix/highlight/share/source-highlight"

int main(int argc, char *argv[])
{	using std::string;

	// get input and output file names
	if( argc != 3 )
	{	std::cerr << "usage: highlight input_file output_file" << std::endl;
		return 1;
	}
	const char* input_file  = argv[1];
	const char* output_file = argv[2];

	// input file language
	string input_lang = "cpp.lang";

	// output file language
	string output_lang = "html.outlang";

	// ctor
	srchilite::SourceHighlight hiliter(output_lang);

	// source-highlight data directory
	hiliter.setDataDir(DATADIR);

	// input stream
	std::fstream input_stream(input_file, std::fstream::in);

	// input string stream
	std::stringstream input_sstream;
	char ch;
	while( input_stream.get(ch) )
		input_sstream << ch;

	// output stream
	std::stringstream output_sstream;

	// convert from the input to output string stream
	hiliter.highlight(input_sstream, output_sstream, input_lang);

	// output stream
	std::fstream output_stream(output_file, std::fstream::out);
	while( output_sstream.get(ch) )
		output_stream << ch;

	return 0;
}
EOF
# ----------------------------------------------------------------------------
prefix="$HOME/prefix/highlight"
echo_eval \
	g++ hilite.cpp -o hilite \
	-g -O0 \
	-I$prefix/include \
	-L$prefix/lib -lsource-highlight
# ----------------------------------------------------------------------------
echo_eval ./hilite hilite.cpp hilite.html
