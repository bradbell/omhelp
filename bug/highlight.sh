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
	const char* input_text_cstr  ,
	const char* input_lang_cstr  ,
	const char* output_lang_cstr )
{	using std::string;

	// input string stream
	string input_text( input_text_cstr );
	std::stringstream input_sstream( input_text );

	// ctor
	string output_lang( output_lang_cstr );
	srchilite::SourceHighlight hiliter( output_lang );

	// source-highlight data directory
	hiliter.setDataDir(DATADIR);

	// output stream
	std::stringstream output_sstream;

	// convert from the input to output string stream
	string input_lang( input_lang_cstr );
	hiliter.highlight(input_sstream, output_sstream, input_lang);

	// return value
	size_t len = output_sstream.str().size();
	char* ret = static_cast<char*>( std::malloc( (len + 1) * sizeof(char) ) );
	for(size_t i = 0; i < len; i++)
		ret[i] = output_sstream.str()[i];
	ret[len] = '\0';

	return ret;
}

extern "C" char* file2lang(const char* file_name_cstr)
{
	srchilite::LangMap lang_map(DATADIR, "lang.map");
	std::string file_name( file_name_cstr);
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
	const char* input_file_cstr  = argv[1];
	const char* output_file_cstr = argv[2];

	// language corresponding to input file
	char* input_lang_ptr = file2lang(input_file_cstr);
	if( input_lang_ptr[0] == '\0' )
	{	std::free(input_lang_ptr);
		std::cerr << "cannot deter language for input_file =" << std::endl;
		std::cerr << input_file_cstr << std::endl;
		return 1;
	}

	// output file language
	const char* output_lang_cstr = "html.outlang";

	// input stream
	std::fstream input_stream(input_file_cstr, std::fstream::in);

	// read file into a string
	string input_string;
	char ch;
	while( input_stream.get(ch) )
		input_string += ch;

	// output stream
	std::fstream output_stream(output_file_cstr, std::fstream::out);

	char* output_text_ptr = highlight(
		input_string.c_str(),
		input_lang_ptr,
		output_lang_cstr
	);

	// output highlighted test
	output_stream << output_text_ptr;

	// free memory allocated by highlight
	std::free(output_text_ptr);

	// free memory allocated by file2lang
	std::free(input_lang_ptr);

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
