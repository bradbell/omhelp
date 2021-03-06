/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
==============================================================================
$begin ExecuteNextFile_dev$$
$escape #$$

$index ExecuteNextFile$$
$cindex next execute file$$

$section Determine Next Execute File Name$$

$head Syntax$$
$codei%ExecuteNextFile()%$$

$head See Also$$
$mref/ExecuteSetFile_dev/$$


$head Description$$
An execute file is pending between a call to $mref/ExecuteSetFile_dev/$$
and the following call to $mref/ExecuteWriteFile_dev/$$.
If there is no execute file pending,
$code ExecuteNextFile$$ returns $code NULL$$.
Otherwise it returns a pointer to a $code '\0'$$
terminated character string containing the name of the next execute file
(in lower case).

$end
==============================================================================
$begin ExecuteSetFile_dev$$
$escape #$$
$spell
	const
	fatalomh
	OMhelp
$$

$index ExecuteSetFile$$
$cindex set execute file name$$

$section Set Name of Next Execution File$$

$head Syntax$$
$codei%ExecuteSetFile(
	const char *%name%,
	const char *%tag%
)%$$

$head See Also$$
$mref/ExecuteWriteFile_dev/$$


$head Description$$
Sets the name of the next execute file
(as returned by $mref/ExecuteNextFile_dev/$$) to a lower case version
of the characters in the $code '\0'$$ terminated character
vector $icode name$$.
The $code '\0'$$ terminated character vector $icode tag$$ specifies the
cross reference tag for the section where the execute file was created.
This is used for error reporting if the same file name is
specified by another call to $code ExecuteSetFile$$.

$head Error$$
It is considered a user error if
the same name was used for a previous execute file.
It is also a user error if the file name contains the \ or the " character.
In either of these cases,
a fatal error message identifying the problem is reported using
$cref/fatalomh/fatalerr_dev/$$; i.e.,
it is assumed that there is an open input file and
that we are currently parsing OMhelp input.

$head Restriction$$
It is considered a program error if
$cref/ExecuteNextFile()/ExecuteNextFile_dev/$$
is not equal to $code NULL$$ when $code ExecuteSetFile$$ is called.
$end
==============================================================================
$begin ExecuteWriteFile_dev$$
$escape #$$
$spell
	const
	fatalomh
	OMhelp
$$

$index ExecuteWriteFile$$
$index write execute file$$
$section Write Next Execute File$$

$head Syntax$$
$codei%ExecuteWriteFile(
	const char *%text%
)%$$

$head See Also$$
$mref/ExecuteNextFile_dev/$$


$head Description$$
Writes the characters in the '\0' terminated character vector
$icode text$$ to the file specified by
$cref/ExecuteNextFile()/ExecuteNextFile_dev/$$.
The value of $code ExecuteNextFile()$$ is then set to $code NULL$$.

$head Error$$
If the next execute file cannot be written,
a fatal error message identifying the problem is reported using
$cref/fatalomh/fatalerr_dev/$$; i.e.,
it is assumed that there is an open input file and
that we are currently parsing OMhelp input.


$head Restriction$$
It is considered a program error if
$cref/ExecuteNextFile()/ExecuteNextFile_dev/$$
is equal to $code NULL$$ when $code ExecuteWriteFile$$ is called.
$end
============================================================================
$begin ExecuteFree_dev$$
$escape #$$

$cindex free execute allocate memory$$
$index ExecuteFree$$
$section Free Hidden Memory Allocated by Execute Routines$$

$head Syntax$$
$codei%void ExecuteFree()%$$

$head See Also$$
$mref/execute_dev/$$


$head Description$$
This routines listed in $mref/execute_dev/$$ allocate some memory
that is hidden from the calling routines.
This routine must be called before
$cref/CheckMemoryLeak/AllocMem_dev/CheckMemoryLeak/$$
or this memory will be reported as a leak.
No other routines listed in $mref/execute_dev/$$
should be called after a call to this routine.

$end
============================================================================
*/

# include <stdio.h>
# include <assert.h>
# include <string.h>
# include "fatalerr.h"
# include "str_alloc.h"
# include "allocmem.h"
# include "StrLowAlloc.h"
# include "DirSep.h"

# include "execute.h"

# ifndef WIN32
# define stricmp strcasecmp
# endif

// maximum number of executes
# define MAX_EXECUTE  1000


// name of the file corresponding to the next execute
static char *NextFile = NULL;
static char *NextTag  = NULL;

// name of all the previous execute files
static char *PreviousFile[MAX_EXECUTE];

// cross reference tag corresponding to all the previous executes
static char *PreviousTag[MAX_EXECUTE];

// number of previous executes
static int   NumberPrevious = 0;

char *ExecuteNextFile()
{	return NextFile;
}


void ExecuteSetFile(const char *name, const char *tag)
{	int i;

	assert(tag != NULL);
	assert(NextFile ==  NULL);
	assert(NextTag == NULL);

	if( strchr(name, '/') != NULL ) fatalomh(
		"The character \"/\" is present in the $execute file name\n",
		name,
		NULL
	);
	if( strchr(name, '\\') != NULL ) fatalomh(
		"The character \"\\\" is present in the $execute file name\n",
		name,
		NULL
	);


	for(i =0; i < NumberPrevious; i++)
	if( stricmp(PreviousFile[i], name) == 0 ) fatalomh(
		"The execute file name (not case sensitive)\n",
		name,
		" was used before in the ",
		PreviousTag[i],
		" section",
		NULL
	);

	NextFile = StrLowAlloc(name);
	NextTag  = str_alloc(tag);

	// convert directory separators
	DirSep(NextFile);

	return;
}


void ExecuteWriteFile(const char *text)
{	FILE *fp;
	unsigned int nchar;

	assert( NextFile != NULL );

	fp = fopen(NextFile, "w");
	if( fp == NULL ) fatalomh(
		"Cannot open the file ",
		NextFile,
		" for writing",
		NULL
	);

	nchar = strlen(text);
	if( nchar != fwrite(text, sizeof(char), nchar, fp) ) fatalomh(
		"Error writing the file ",
		NextFile,
		NULL
	);

	if( NumberPrevious == MAX_EXECUTE ) fatalomh(
		"To many $execute commands",
		NULL
	);

	fclose(fp);
	PreviousTag[NumberPrevious]     = NextTag;
	PreviousFile[NumberPrevious++]  = NextFile;
	NextFile                        = NULL;
	NextTag                         = NULL;
	return;
}

void ExecuteFree()
{	int i;

	for(i = 0; i < NumberPrevious; i++)
	{	FreeMem(PreviousFile[i]);
		FreeMem(PreviousTag[i]);
	}
	NumberPrevious = 0;
	return;
}
