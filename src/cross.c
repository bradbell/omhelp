/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
==============================================================================
$begin CreateCrossReference_dev$$
$spell
	printid
$$
$index CrossReference$$
$index CreateCrossReference$$

$section Create a New Cross Reference Record$$


$head Syntax$$
$codei%CreateCrossReference(%tag%, %head%, %file%)%$$


$head Description$$
Uses $mref/AllocMem_dev/$$ to allocate memory for a new
$code CrossReference$$ record with the following fields and settings:

$table
$bold Field$$     $cend $bold Initial Value$$ $cend
$bold  Description$$
$rend

$code defined$$   $cend       0  $cend
has the destination for this cross reference been defined
$rend

$code frame$$     $cend       0  $cend
if head[0]!='\0', frame that the
$cref/cross reference heading/glossary_dev/Cross Reference Heading/$$
refers to
$rend

$cref/tag/CrossReference_dev/Tag/$$       $cend       $icode tag$$  $cend
a separated allocated copy of section tag
$rend

$cref/head/CrossReference_dev/Head/$$      $cend       $icode head$$ $cend
a separated allocated copy of a
$cref/cross reference heading/glossary_dev/Cross Reference Heading/$$
$rend

$cref/file/CrossReference_dev/File/$$      $cend       $icode file$$ $cend
name of user input file corresponding to this cross reference
$rend

$cref/printid/CrossReference_dev/Printid/$$    $cend       $code NULL$$ $cend
identification of cross reference in printed version of web site
$rend

$code line$$      $cend       $code InputLine()$$ $cend
if file[0] != 0,  is input line corresponding to cross reference
$rend

$code next_created$$      $cend       $code NULL$$ $cend
next record in list of created cross references
(only used by this file).
$rend

$code next_defined$$      $cend       $code NULL$$ $cend
next record in list of defined cross references
(only used by this file).


$tend

$head Return Value$$
A $code CrossReference$$ pointer to the
new cross reference is returned and it is programming error
to create a cross reference that already exists; i.e., for which
$mref/FindCrossReference_dev/$$ would not return $code NULL$$

$end
==============================================================================
$begin FindCrossReference_dev$$

$index cross reference, find$$
$index FindCrossReference$$

$section Find Record Corresponding to a Cross Reference$$

$head Syntax$$
$codei/FindCrossReference(/tag/, /head/)/$$


$head Description$$
Search the cross reference list for a Cross Reference record that has the
specified
$cref/tag/CrossReference_dev/Tag/$$
and
$cref/heading/CrossReference_dev/Head/$$.
The return value is a $code CrossReference$$ pointer to the cross
reference. If such a cross reference is found, a pointer to it is returned.
Otherwise $code NULL$$ is returned.

$end
==============================================================================
$begin DefineCrossReference_dev$$
$spell
	printid
$$

$index DefineCrossReference$$
$index cross reference, define$$
$index target, cross reference$$

$section Define a Cross Reference Destination Point$$

$head Syntax$$
$codei/DefineCrossReference(/tag/, /head/, /file/, /frame/, /printid/)/$$


$head Description$$
The cross reference with the specified
$cref/tag/CrossReference_dev/Tag/$$
and
$cref/head/CrossReference_dev/Head/$$
is searched for.
If no such cross reference is found, a new one is created.
$pre

$$
If a cross reference destination with the same $icode tag$$
and $icode head$$ has already been
$cref/defined/CrossReference_dev/Defined/$$,
a fatal error message is printed and the program stops.
(Note that defined is different from created.)
$pre

$$
The cross reference is marked as defined. In addition, the
$cref/frame/CrossReference_dev/Frame/$$
and
$cref/file/CrossReference_dev/File/$$
fields are set to the values specified by the call.
$pre

$$
If $icode file$$
is equal to $mref/InputName_dev/$$,
the line number is set to $mref/InputLine_dev/$$.
$pre

$$
The argument  $icode printid$$
specifies the
$cref/printid/CrossReference_dev/Printid/$$
for this cross reference.
The argument $icode printid$$ can point to the empty string
in which case there is no print id for this cross reference.
$pre

$$
A pointer to the cross reference is returned.
$end
==============================================================================
$begin NextCrossReference_dev$$

$index NextCrossReference$$
$index cross reference, next$$

$section Return Next Cross Reference In Definition Order$$

$head Syntax$$
$codei/NextCrossReference(/cross/)/$$


$head Description$$
Returns a $code CrossReference$$ pointer that has the same
$cref/tag/CrossReference_dev/Tag/$$ as $icode cross$$
and is defined directly after the definition of $icode cross$$.
The argument $icode cross$$ is a $code CrossReference$$ pointer.
If no such a cross reference exists,
$code NULL$$ is returned.
This is useful for listing the
$cref/cross reference headings/glossary_dev/Cross Reference Heading/$$
and corresponding links for a particular section.

$end
==============================================================================
$begin FreeCrossReference_dev$$
$spell
	Mem
$$

$index FreeCrossReference$$
$index memory, cross reference table$$
$index check, cross reference$$

$section Delete Cross Reference Table$$

$head Syntax$$
$codei/FreeCrossReference()/$$


$head Description$$
Checks that all the cross references were defined and prints an error
message for each one that was not. In addition Frees all the memory
associated with the cross reference list
(using $cref/FreeMem/AllocMem_dev/FreeMem/$$) and leave the list
as empty.
This should be done before
$cref/CheckMemoryLeak/AllocMem_dev/CheckMemoryLeak/$$ is called.

$end
*/

# include <ctype.h>
# include <string.h>
# include <stdio.h>
# include "allocmem.h"
# include "input.h"
# include "str_alloc.h"
# include "StrCat.h"
# include "cross.h"
# include "warning.h"
# include <assert.h>
# include "fatalerr.h"
# include "int2str.h"
# include "main.h"

# ifndef WIN32
# define stricmp strcasecmp
# endif

static  CrossReference *CreatedList = NULL;
static  CrossReference *DefinedList = NULL;

static char *IdentifyCrossReference(
	const char *tag,
	const char *head,
	const char *file,
	const int line
)
{	char *ret;

	if( file[0] != '\0' )
	{	char *Line;

		Line = int2str(line);

		ret = StrCat(
			__FILE__,
			__LINE__,
			"Cross reference destination defined at line ",
			Line,
			" of file ",
			file,
			"\nhas tag = \"",
			tag,
			"\" and heading.subheading =\n\"",
			head,
			"\"",
			NULL
		);

		FreeMem(Line);
	}
	else
	{
		ret = StrCat(
			__FILE__,
			__LINE__,
			"Cross reference destination defined in an ",
			"automatically generated file\n",
			"has tag = \"",
			tag,
			"\" and heading.subheading =\n\"",
			head,
			"\"",
			"\nPlease report this error as a bug in OMhelp.",
			NULL
		);
	}

	return ret;
}

CrossReference *CreateCrossReference(
	const char *tag,
	const char *head,
	const char *file
)
{	CrossReference *C;

	assert( *tag != '\0' );
	assert( ! isspace((int) *tag) );

	C = FindCrossReference(tag, head);
	assert(C == NULL);

	C = (CrossReference *) AllocMem(1, sizeof(CrossReference));
	C->defined = 0;
	C->tag     = str_alloc(tag);
	C->head    = str_alloc(head);
	C->file    = str_alloc(file);
	if( file[0] == '\0' )
		C->line = 0;
	else
	{	assert( strcmp(file, InputName()) == 0 );
		C->line = InputLine();
	}

	C->frame           = 0;
	C->next_created    = CreatedList;
	C->printid         = NULL;
	C->next_defined    = NULL;

	CreatedList = C;

	return C;
}

CrossReference *FindCrossReference(
	const char *tag,
	const char *head
)
{
	CrossReference *C;

	assert( *tag != '\0' );
	assert( ! isspace((int) *tag) );

	C = CreatedList;
	while( C != NULL )
	{	if( stricmp(C->tag, tag) == 0 && strcmp(C->head, head) == 0 )
			return C;
		else
			C = C->next_created;
	}
	return NULL;
}

CrossReference *DefineCrossReference(
	const char *tag,
	const char *head,
	const char *file,
	const int  frame,
	const char *printid
)
{	CrossReference *C;
	CrossReference *L;

	assert( *tag != '\0' );
	assert( ! isspace((int) *tag) );

	assert( frame == 0 || head[0] != '\0' );
	assert( strcmp(file, InputName()) == 0 || file[0] == '\0' );


	C = FindCrossReference(tag, head);
	if( C == NULL )
		C = CreateCrossReference(tag, head, file);

	assert( C != NULL );
	assert( stricmp(C->tag, tag) == 0 );
	assert( strcmp(C->head, head) == 0 );

	if( C->defined )
	{	char *msg1;
		char *msg2;
		char *msg3;
		int  line;

		if( strcmp(file, InputName()) == 0 )
			line = InputLine();
		else	line = 0;
		msg1 = IdentifyCrossReference(
			tag, head, file, line);
		msg2 = IdentifyCrossReference(
			C->tag, C->head, C->file, C->line);
		msg3 = "\nIf the file names and line number are the same,"
		       "\nthe file has probably been included twice.";
		fatalerr(
			"\nTwo defintions for the same ",
			"cross reference destination:\n",
			msg1,
			"\n",
			msg2,
			msg3,
			NULL
		);
	}


	// mark as defined
	C->defined = 1;
	C->frame   = frame;


	// change from first usage to destination where defined
	FreeMem(C->file);
	C->file    = str_alloc(file);

	// change line to correspond to file
	if( file[0] == '\0' )
		C->line = 0;
	else
	{	assert( strcmp(file, InputName()) == 0 );
		C->line = InputLine();
	}
	assert( C->printid == NULL );
	C->printid = str_alloc(printid);

	// Add to list of defiend cross references
	if( DefinedList == NULL )
		DefinedList = C;
	else
	{	L = DefinedList;
		while( L->next_defined != NULL )
			L = L->next_defined;

		L->next_defined = C;
	}

	return C;
}

CrossReference *NextCrossReference(const CrossReference *cross)
{
	CrossReference *C;

	C = cross->next_defined;
	if( C == NULL )
		return NULL;
	if( stricmp(C->tag, cross->tag) != 0 )
		return NULL;

	return C;
}

void FreeCrossReference()
{	CrossReference *C;

	while(CreatedList != NULL)
	{	C = CreatedList;

		CreatedList = C->next_created;
		if( (! C->defined) & PostWarnings() )
		{	char *msg;
			char *Line;

			Line = int2str(C->line);

			msg = StrCat(
				__FILE__,
				__LINE__,
				"\nOMhelp Warning: cross reference at line ",
				Line,
				" of file ",
				C->file,
				"\nNo destination is defined with tag = \"",
				C->tag,
				"\" and heading.subheading =\n\"",
				C->head,
				"\"\n",
				NULL
			);
			printf("%s", msg);

			FreeMem(Line);
			FreeMem(msg);
		}

		FreeMem(C->tag);
		FreeMem(C->head);
		FreeMem(C->file);
		FreeMem(C->printid);
		FreeMem(C);
	}
	CreatedList = NULL;
	return;
}
