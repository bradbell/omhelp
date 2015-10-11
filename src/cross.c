/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
==============================================================================
$begin CreateCrossReference$$
$spell
	printid
$$
$index CrossReference$$
$index CreateCrossReference$$

$section Create a New Cross Reference Record$$


$table
$bold Syntax$$
$cend $codei%CreateCrossReference(%tag%, %head%, %file%)%$$ $rend
$tend

$head Description$$
Uses $mref/AllocMem/$$ to allocate memory for a new
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
$cref/cross reference heading/glossary/Cross Reference Heading/$$
refers to
$rend

$cref/tag/CrossReference/Tag/$$       $cend       $italic tag$$  $cend
a separated allocated copy of section tag
$rend

$cref/head/CrossReference/Head/$$      $cend       $italic head$$ $cend
a separated allocated copy of a
$cref/cross reference heading/glossary/Cross Reference Heading/$$
$rend

$cref/file/CrossReference/File/$$      $cend       $italic file$$ $cend
name of user input file corresponding to this cross reference
$rend

$cref/printid/CrossReference/Printid/$$    $cend       $code NULL$$ $cend
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
$mref/FindCrossReference/$$ would not return $code NULL$$

$end
==============================================================================
$begin FindCrossReference$$

$index cross reference, find$$
$index FindCrossReference$$

$section Find Record Corresponding to a Cross Reference$$

$table
$bold Syntax$$
$cend $codei/FindCrossReference(/tag/, /head/)/$$
$tend

$head Description$$
Search the cross reference list for a Cross Reference record that has the
specified
$cref/tag/CrossReference/Tag/$$
and
$cref/heading/CrossReference/Head/$$.
The return value is a $code CrossReference$$ pointer to the cross
reference. If such a cross reference is found, a pointer to it is returned.
Otherwise $code NULL$$ is returned.

$end
==============================================================================
$begin DefineCrossReference$$
$spell
	printid
$$

$index DefineCrossReference$$
$index cross reference, define$$
$index target, cross reference$$

$section Define a Cross Reference Destination Point$$

$table
$bold Syntax$$
$cend $codei/DefineCrossReference(/tag/, /head/, /file/, /frame/, /printid/)/$$
$tend

$head Description$$
The cross reference with the specified
$cref/tag/CrossReference/Tag/$$
and
$cref/head/CrossReference/Head/$$
is searched for.
If no such cross reference is found, a new one is created.
$pre

$$
If a cross reference destination with the same $italic tag$$
and $italic head$$ has already been
$cref/defined/CrossReference/Defined/$$,
a fatal error message is printed and the program stops.
(Note that defined is different from created.)
$pre

$$
The cross reference is marked as defined. In addition, the
$cref/frame/CrossReference/Frame/$$
and
$cref/file/CrossReference/File/$$
fields are set to the values specified by the call.
$pre

$$
If $italic file$$
is equal to $mref/InputName/$$,
the line number is set to $mref/InputLine/$$.
$pre

$$
The argument  $italic printid$$
specifies the
$cref/printid/CrossReference/Printid/$$
for this cross reference.
The argument $italic printid$$ can point to the empty string
in which case there is no print id for this cross reference.
$pre

$$
A pointer to the cross reference is returned.
$end
==============================================================================
$begin NextCrossReference$$

$index NextCrossReference$$
$index cross reference, next$$

$section Return Next Cross Reference In Definition Order$$

$table
$bold Syntax$$
$cend $codei/NextCrossReference(/cross/)/$$
$tend

$head Description$$
Returns a $code CrossReference$$ pointer that has the same
$cref/tag/CrossReference/Tag/$$ as $italic cross$$
and is defined directly after the definition of $italic cross$$.
The argument $italic cross$$ is a $code CrossReference$$ pointer.
If no such a cross reference exists,
$code NULL$$ is returned.
This is useful for listing the
$cref/cross reference headings/glossary/Cross Reference Heading/$$
and corresponding links for a particular section.

$end
==============================================================================
$begin FreeCrossReference$$
$spell
	Mem
$$

$index FreeCrossReference$$
$index memory, cross reference table$$
$index check, cross reference$$

$section Delete Cross Reference Table$$

$table
$bold Syntax$$
$cend $codei/FreeCrossReference()/$$
$tend

$head Description$$
Checks that all the cross references were defined and prints an error
message for each one that was not. In addition Frees all the memory
associated with the cross reference list
(using $cref/FreeMem/AllocMem/FreeMem/$$) and leave the list
as empty.
This should be done before
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$ is called.

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
