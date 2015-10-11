/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin copyfile$$
$spell
	copyfile
	str
	Mem
	backslash
$$

$mindex copy file$$
$section Creating A Copy of a File$$

$table
$bold Syntax$$
$cend $codei/copyfile(/destination/, /source/)/$$ $rend
$cend $codei/copyfileFreeMemory()/$$ $rend
$tend

$codei/

copyfile(/destination/, /source/)
/$$
copies the file specified by $icode source$$
to the file specified by $icode destination$$
where $icode source$$ and $icode destination$$
are '\0' terminated character vectors.
The case of the letters in $icode destination$$ is ignored
and all the letters in the resulting file are in lower case.
Either the backslash '\\' or the forward slash '/' can be
used to separate directories in both $icode source$$
and  $icode destination$$.
$pre

$$
It is a programming error
(not user error) if $code copyfileFreeMemory$$ was called prior
to a call to $code copyfile$$.


$head User Errors$$
It is a user error to call $code copyfile$$ twice with the same
value for $icode destination$$.
It is also a user error if the source or destination file
cannot be opened.
The value of $cref InputName$$ and $cref InputLine$$
are used to identify where the access to
$icode source$$ and $icode destination$$ occurred.
If a user error occurs, an error message is printed
and this routine does not return.

$codei/

copyfileFreeMemory()
/$$
Uses $cref/FreeMem/AllocMem/FreeMem/$$ to free memory that was allocated using
$cref AllocMem$$ (so that
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$ can be used).
This memory is used to track what line and file certain destination
file names were used at.

$end

*/

#ifdef WIN32
# include <io.h>
# include <sys\stat.h>
# include <sys\types.h>
#else
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
#endif


# include <fcntl.h>
# include <assert.h>
# include <string.h>

# include "allocmem.h"
# include "strjoin.h"
# include "str_alloc.h"
# include "StrLowAlloc.h"
# include "DirSep.h"
# include "fatalerr.h"
# include "input.h"
# include "FileEqual.h"

# include "copyfile.h"

# define BUFFER_LEN 1000

// O_BINARY is defined under windows for open in binary mode
# ifndef O_BINARY
# define O_BINARY 0
# endif

typedef struct fileInfo {
	char *inputLine;
	char *inputFile;
	char *Sname;
	char *Dname;
	struct fileInfo *next;
} FileInfo;

static FileInfo *Info = NULL;
static int       Done = 0;


void copyfile(
	const char *destination,
	const char *source
)
{	int D;
	int S;
	int nread;
	int nwrite;
	char *Sname;
	char *Dname;
	FileInfo *info;

	unsigned char buffer[BUFFER_LEN];

	assert( ! Done );

	// open the source file
	Sname = str_alloc(source);
	DirSep(Sname);
	S = open(Sname, O_RDONLY | O_BINARY, S_IREAD);
	if( S == -1 )
	{	fatalerr(
			"Cannot read the file\n",
			Sname,
			NULL
		);
	}


	// check for previous use of destination name
	Dname = StrLowAlloc(destination);
	DirSep(Dname);
	info = Info;
	while( info != NULL )
	{	if( strcmp(Dname, info->Dname) == 0 &&
		    FileEqual(Sname, info->Sname) )
		{	// already copied this file
			FreeMem(Sname);
			FreeMem(Dname);
			if( close(S) != 0 ) fatalerr(
				"Error closing the file\n",
				Sname,
				NULL
			);
			return;
		}
		if( strcmp(Dname, info->Dname) == 0 ) fatalerr(
			"The file ",
			info->Sname,
			"\nis used at line ",
			info->inputLine,
			" of file ",
			info->inputFile,
			"\nThe current use of",
			Sname,
			"\nwill overwrite the copy of ",
			info->Sname,
			NULL
		);
		info = info->next;
	}

	// add this entry to the list
	info = AllocMem(sizeof( FileInfo ), 1);
	info->inputLine   = AllocMem(sizeof(char), 10);
	sprintf(info->inputLine, "%d", InputLine());
	info->inputFile   = StrLowAlloc(InputName());
	info->Dname       = Dname;
	info->Sname       = Sname;
	info->next        = Info;
	Info              = info;

	// Open the destination file
	D = open(Dname,
	    O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, S_IWRITE
	);
	if( D == -1 )
	{	fatalerr(
			"Cannot create the file\n",
			Dname,
			NULL
		);
	}

	nread = 1;
        nwrite = 1;
        while( nread > 0 && nwrite == nread)
	{	nread = read(S, (void *) buffer, BUFFER_LEN);
		if( nread > 0 )
			nwrite = write(D, (void *) buffer, nread);
		else	nwrite = 0;
		if( nwrite != nread )
		{	fatalerr(
				"Error writing the file\n",
				Dname,
				NULL
			);
		}
	}

# ifndef WIN32
	// set mode for use after program finishes
	// read:  user, group, and other
	// write: user
	fchmod(D, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
# endif

	// close the files
	close(S);
	close(D);

	return;
}

void copyfileFreeMemory()
{
	FileInfo *info;

	while( Info != NULL )
	{	info = Info;
		Info = Info->next;
		FreeMem(info->Dname);
		FreeMem(info->Sname);
		FreeMem(info->inputFile);
		FreeMem(info->inputLine);
		FreeMem(info);
	}

	Done = 1;
	Info = NULL;
	return;
}
