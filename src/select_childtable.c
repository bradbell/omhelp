/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin select_childtable$$
$spell
	Javascript
	childtable
	xml
	htm
	js
	Mem
$$

$section Outputs Javascript That Selects from Child Table$$

$head Syntax$$
$icode%file_name% = select_childtable(%This)%$$

$head This$$
This is the section that we are creating the
javascript child table for.

$head tag$$
We use $icode tag$$ to denote $icode%This%->tagLower%$$.

$head ext$$
We use $icode ext$$ to denote the output extension; i.e., $code xml$$
or $code htm$$.

$head file_name$$
The file name is
$codei%
	%file_name% = _childtable_%tag%_%ext%.js
%$$
This file is created the first time $code select_childtable$$ is called.
When this file is included in an $code xml$$ or $code htm$$ file,
it creates a select menu for choosing any of the children of $icode This$$
section.
When you no longer need $icode file_name$$ it should be freed using
$codei%FreeMem(%file_name%)%$$.

$end
*/
# include <stdio.h>
# include <assert.h>

# include "select_childtable.h"
# include "automatic.h"
# include "Internal2Out.h"
# include "StrCat.h"
# include "fatalerr.h"

# include "allocmem.h" // for FreeMem

char* select_childtable(SectionInfo* This)
{	static int call_count = 0;

	// file extension for this xml or htm file
	const char* ext;

	// lower case version of cross reference tag
	const char* tagLower = This->tagLower;

	// name of the javascript file
	char* script_name;

	// file pointer for the javascript file
	FILE* script_fp;

	// pointer to the first section in the child table
	SectionInfo* F;

	// temporary section pointer
	SectionInfo* S;

	// First child of this section, not including the atuomatic sections
	F = This->children;
	assert(F != NULL);
	while(F->previous != NULL )
		F = F->previous;
	while( IsAutomaticSection(F) )
	{	F = F->next;
		assert(F != NULL);
	}

	// The Output extension is xml or htm with out leading dot
	ext = Internal2Out("OutputExtension");
	assert( *ext == '.' );
	ext++;

	// Name of javascript file that contains the childtable for this section
	script_name = StrCat(
		__FILE__,
		__LINE__,
		"_childtable_",
		tagLower,
		"_",
		ext,
		".js",
		NULL
	);

	// Check if file already exists
	++call_count;
	if( call_count > 1 )
			return script_name;

	// Create the file
	script_fp = fopen(script_name, "w");
	if( script_fp == NULL ) fatalerr(
		"Can not create the output file ",
		script_name,
		NULL
	);

	// ----------------------------------------------------------------------
	// place <select> ... </select> in htm or xml file that includes script
	// ----------------------------------------------------------------------
	fprintf(script_fp, "// Child Table for section %s\n", tagLower);
	fprintf(script_fp, "document.write('\\\n");
	fprintf(script_fp, "<select onchange=\"%s_child(this)\">\\\n", tagLower);
	fprintf(script_fp, "<option>%s-&gt;</option>\\\n", tagLower);
	S = F;
	while( S != NULL )
	{	fprintf(script_fp, "<option>%s</option>\\\n", S->tag);
		S = S->next;
	}
	fprintf(script_fp, "</select>\\\n");
	fprintf(script_fp, "');\n");
	fprintf(script_fp, "function %s_child(item)\n", tagLower);
	fprintf(script_fp, "{\tvar child_list = [\n");
	S = F;
	while( S != NULL )
	{	if( S->next != NULL )
			fprintf(script_fp, "\t\t'%s.%s',\n", S->tag, ext);
		else
			fprintf(script_fp, "\t\t'%s.%s'\n", S->tag, ext);
		S = S->next;
	}
	fprintf(script_fp,
		"\t];\n"
		"\tvar index = item.selectedIndex;\n"
		"\titem.selectedIndex = 0;\n"
		"\tif(index > 0)\n"
		"\t\tdocument.location = child_list[index-1];\n"
		"}\n"
	);
	//
	return script_name;
}
