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
# include <cstdlib>
# include "srchilite/sourcehighlight.h"
# include "srchilite/langmap.h"

# define DATADIR "/home/bradbell/prefix/highlight/share/source-highlight"

extern "C" char* highlight(
	const char* input_text  ,
	const char* input_lang  ,
	const char* output_lang )
{	using std::string;

	// input string stream
	std::stringstream input_sstream( input_text );

	// ctor
	srchilite::SourceHighlight hiliter( output_lang );

	// source-highlight data directory
	hiliter.setDataDir(DATADIR);

	// output stream
	std::stringstream output_sstream;

	// convert from the input to output string stream
	hiliter.highlight(input_sstream, output_sstream, string(input_lang) );

	// return value
	size_t len = output_sstream.str().size();
	char* ret = static_cast<char*>( std::malloc( (len + 1) * sizeof(char) ) );
	for(size_t i = 0; i < len; i++)
		ret[i] = output_sstream.str()[i];
	ret[len] = '\0';

	return ret;
}

extern "C" char* file2lang(const char* file_name)
{
	srchilite::LangMap lang_map(DATADIR, "lang.map");
	std::string lang = lang_map.getMappedFileNameFromFileName(file_name);

	// return value
	size_t len = lang.size();
	char* ret = static_cast<char*>( std::malloc( (len + 1) * sizeof(char) ) );
	for(size_t i = 0; i < len; i++)
		ret[i] = lang[i];
	ret[len] = '\0';

	return ret;
}

int main(int argc, char *argv[])
{	using std::string;

	// get input and output file names
	if( argc != 3 )
	{	std::cerr << "usage: hilite input_file output_file" << std::endl;
		return 1;
	}
	const char* input_file  = argv[1];
	const char* output_file = argv[2];

	// language corresponding to input file
	char* input_lang = file2lang(input_file);

	// output file language
	string output_lang = "html.outlang";

	// input stream
	std::fstream input_stream(input_file, std::fstream::in);

	// read file into a string
	string input_string;
	char ch;
	while( input_stream.get(ch) )
		input_string += ch;

	// output stream
	std::fstream output_stream(output_file, std::fstream::out);

	if( string(input_lang) != "" )
	{	char* output_text = highlight(
			input_string.c_str(),
			input_lang,
			output_lang.c_str()
		);

		// output highlighted test
		output_stream << output_text;

		// free memory allocated by highlight
		std::free(output_text);
	}
	else
	{	// output text as input
		output_stream << input_string.c_str();
	}
	// free memory allocated by file2lang
	std::free(input_lang);

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
