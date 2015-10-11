/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
The documentation below is for these routines with respect to other files; i.e.,
it does not include communication through static variables in this file.
============================================================================
$begin InputGet$$
$escape #$$

$index InputGet$$
$index read, next input character$$
$cindex get input character$$

$section Get Next Character From Current Input File$$

$table
$bold Syntax$$
$cend $codei%char InputGet()%$$ $rend
$bold See Also$$
$cend $mref/InputPush/$$
$tend

$head Description$$
Get the next character from the top of the input
$cref/stack/InputPush/$$.
If there are no more characters in the input file
the value $code '\001'$$
is returned to signal end of file.

$head Restrictions$$
If there are no files on the input stack, an $code assert$$
will halt execution of the program.

$end
=======================================================================
$begin InputInit$$
$escape #$$
$spell
	Init
	const
$$

$section Initialize Input By Setting The Local Name Directory$$

$table
$bold Syntax$$
$cend $codei%void InputInit(
	const char *%directory%
)%$$
$tend

$head Description$$
The $code '\0'$$ terminated character vector $icode directory$$
specifies the local directory for all input file searching by
$cref InputPush$$ and $cref InputAddPath$$.
The last character in $icode directory$$ must be either a forward
or back slash; i.e., '/' or '\\'.

$head Assumptions$$
$list number$$
this routine is called only once.
$lnext
$icode directory$$ is a
$cref/complete path specification/glossary/Complete Path Specification/$$.
$lnext
$code InputInit$$
is called before any of the other routines in $cref input$$
(except for $cref InputName$$ which will return "NONE" if called before
$code InputInit$$).
$lend

$end
============================================================================
$begin InputPush$$
$escape #$$
$spell
	const
	nspace
	fatalomh
	fatalerr
$$
$escape #$$

$cindex open file #and push #on input stack$$
$index InputPush$$
$section Open File and Put it on Top of Input Stack$$

$table
$bold Syntax$$
$cend $codei%void InputPush(
	const char *%root%,
	const char *%ext%,
	const int   %nspace%
)%$$ $rend
$bold See Also$$
$cend $mref/InputSplitName/InputPop/$$
$tend

$head Description$$
The $code '\0'$$ terminated character row vector $icode ext$$
specifies the
$cref/extension/glossary/File Extension/$$
of the file to be pushed on the input stack.
The $code '\0'$$ terminated character row vector $icode root$$
specifies the
$cref/root/glossary/Root File Name/$$ file name of the file.
The routine
$cref InputSearch$$ specifies how the input file is searched for.

$head File Opened$$
If the file is opened for reading, it is placed on top of the input stack.
In addition, the new line character $code '\n'$$ is printed
on standard output, followed by $icode nspace$$ spaces,
followed by the name of the file with the matching path
and extension added on.

$head File Not Opened$$
It is considered a user error if
the file cannot be opened for reading,
or if the file name corresponding to $icode root$$ followed by $icode ext$$
is equal to $code "NONE"$$.
In either of these cases,
a fatal error message is reported
and this routine does not return.

$head Errors$$
If there is currently a file on the input stack,
the routines documented above use
$cref/fatalomh/fatalerr/$$ to report error messages.
Otherwise they use $code fatalerr$$.

$end
============================================================================
$begin InputPop$$
$escape #$$

$cindex close file #and pop #from input stack$$
$index InputPop$$
$section Close File and Remove it from the Input Stack$$

$table
$bold Syntax$$
$cend $codei%void InputPop()%$$ $rend
$bold See Also$$
$cend $mref/InputPush/$$
$tend

$head Description$$
The file currently on the top of the input stack is closed
and removed from the stack.

$end
============================================================================
$begin InputName$$
$escape #$$
$spell
	const
$$

$cindex name #of current input file$$
$index InputName$$
$section Name of Current Input File$$

$table
$bold Syntax$$
$cend $codei%const char *InputName()%$$ $rend
$bold See Also$$
$cend $mref/InputLine/InputPush/$$
$tend

$head Description$$
Returns the $icode root$$ plus $icode ext$$ corresponding
to the call to $mref/InputPush/$$ that placed the current input
file on top of the input stack.
$pre

$$
If there is no file on the input stack,
the value $code "NONE"$$ is returned.
$pre

$$
The $cref/local directory/InputInit/$$ is not included
at the beginning of the file name.

$end
============================================================================
$begin InputLine$$
$escape #$$
$spell
	const
$$

$cindex current input file line number$$
$index InputLine$$
$section Line Number Corresponding to Current Input File$$

$table
$bold Syntax$$
$cend $codei%const int InputLine()%$$ $rend
$bold See Also$$
$cend $mref/InputName/$$
$tend

$head Description$$
Returns the line number corresponding to the next call to
next character read from the current input file.
If there is no current input file,
the value zero is returned
(otherwise the return value is greater than zero).

$end
============================================================================
$begin InputAddPath$$
$escape #$$
$spell
	const
$$

$cindex add input search path$$
$index InputAddPath$$
$section Add to the Set of Input Search Paths$$

$table
$bold Syntax$$
$cend $codei%void InputAddPath(
	const char *%path%,
	const char *%ext%
)%$$ $rend
$bold See Also$$
$cend $mref/InputSearch/$$
$tend

$head Description$$
Adds the search path specified by $icode path$$
to the set of input search paths for the
$cref/extension/glossary/File Extension/$$
specified by $icode ext$$.
Both $icode path$$ and $icode ext$$ must be
$code '\0'$$ terminated character row vectors.


$end
============================================================================
$begin InputSearch$$
$escape #$$
$spell
	const
$$

$cindex search input path$$
$index InputSearch$$
$index open, search for input file$$

$section Search Input Paths for a Specific Input File$$

$table
$bold Syntax$$
$cend $codei%const char *InputSearch(
	const char *%root%,
	const char *%ext%
)%$$ $rend
$bold See Also$$
$cend $mref/InputAddPath/$$
$tend

$head Description$$
Searches the set of paths corresponding to the
$cref/extension/glossary/File Extension/$$ specified
by $icode ext$$ for a file that has its
$cref/root/glossary/Root File Name/$$ name equal to $icode root$$.
The arguments $icode root$$ and $icode ext$$ are
$code '\0'$$ terminated character row vectors.

$head Searching For File$$
If $icode root$$ has a
$cref/complete path specification/glossary/Complete Path Specification/$$,
no path are added to the $icode root$$ before searching for the file.
Otherwise, the
$cref/local directory/InputInit/$$ is placed in front of
$icode root$$ and the file is searched for.
If the file is not found relative to the local directory,
each of the
$cref/search paths/InputAddPath/$$ is placed in front of
$icode root$$ and the file is searched for.
For each search path, if it is not a complete path specification,
the $cref/local directory/InputInit/$$ is placed
in front of it to complete the path specification.
$pre

$$
The return value is the directory in which the file
is found.
(The actual file is InputSearch(root, ext) + root + ext
where + denotes string concatenation.)

$head Errors$$
If the file is not found, an error message is reported using
$mref/fatalerr/$$
and the this routine does not return.

$end
============================================================================
$begin InputSplitName$$
$escape #$$
$spell
	const
	proot
	pext
	Mem
$$

$cindex input file root #and extension$$
$index InputSplitName$$
$section Determine Root and Extension Corresponding to an Input File$$

$table
$bold Syntax$$
$cend $codei%void InputSplitName(
	char **%proot%,
	char **%pext%,
	const char *%filename%
)%$$ $rend
$bold See Also$$
$cend $mref/InputPush/$$
$tend

$head Description$$
Determine the
$cref/root/glossary/Root File Name/$$
and
$cref/extension/glossary/File Extension/$$
corresponding to the file specified by
$icode filename$$.
The argument $icode filename$$ is a
$code '\0'$$ terminated
character vector specifying the file name.
Leading and trailing white space in $icode filename$$ is ignored.
$pre

$$
The character row vector $codei%*%pext%$$
is set to be $code '\0'$$ terminated and contains the
$cref/extension/glossary/File Extension/$$
corresponding to $icode filename$$.
The character row vector $codei%*%proot%$$
is set to be $code '\0'$$ terminated and contains the
$cref/root/glossary/Root File Name/$$
corresponding to $icode filename$$.

$head Memory Allocation$$
The character vectors corresponding to
both $codei%*%proot%$$ and $codei%*%pext%$$ is allocated using
$mref/AllocMem/$$ and is not freed by any of the
$mref/input/$$ routines.
In particular, it is not freed by $mref/InputFree/$$.
Hence the calling routine
must ensure that the character vectors corresponding to
both $codei%*%proot%$$ and $codei%*%pext%$$
are freed using $cref/FreeMem/AllocMem/FreeMem/$$.

$end
============================================================================
$begin InputFree$$
$escape #$$

$cindex free input allocate memory$$
$index InputFree$$
$section Free Hidden Memory Allocated by Input Routines$$

$table
$bold Syntax$$
$cend $codei%void InputFree()%$$ $rend
$bold See Also$$
$cend $mref/input/$$
$tend

$head Description$$
This routines listed in $mref/input/$$ allocate some memory
that is hidden from the calling routines.
This routine must be called before
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$
or this memory will be reported as a leak.
No other routines listed in $mref/input/$$
should be called after a call to this routine.

$end
============================================================================
*/

# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>


# ifdef WIN32
# include <io.h>
# else
# include <unistd.h>
# endif

# include "allocmem.h"
# include "strjoin.h"
# include "str_alloc.h"
# include "fatalerr.h"
# include "StrCat.h"
# include "DirSep.h"
# include "OmhLexSetInputLine.h"
# include "lexomh.h"

# include "input.h"

# define MAX_FILE   20
# define MAX_PATH   20


// local directory with proper separator charactor; i.e., after DirSep
static char *LocalDirectory = NULL;

// input files
struct {
	FILE *fp;
	char *name;
	int line;
	char ch;
	char command_key_character_at_push_input;
} File[MAX_FILE];

// index of the current file
static int Index = -1;

// current search path
static int  NPath = 0;
static char *User[MAX_PATH];
static char *Path[MAX_PATH];
static char *Ext[MAX_PATH];

static int CompletePath(char *name)
{	if( name[0] == '\0' )
		return 0;
	if( name[0] == '/' || name [0] == '\\' || name[1] == ':' )
		return 1;
	return 0;
}
static const char *LocalName(const char *CompletePath)
{	int   i;
	char ch;
	const char *name;

	i    = 0;
	ch   = CompletePath[i];
	while( (ch != '\0' && ch == LocalDirectory[i])  ||
	       (ch == '\\' && LocalDirectory[i] == '/') ||
	       (ch == '/' && LocalDirectory[i] == '\\')
	)	ch = CompletePath[++i];

	// remove the local directory from the file name
	if( LocalDirectory[i] == '\0' )
		name = CompletePath + i;
	else	name = CompletePath;

	return name;
}

char InputGet()
{	int ch;
	assert(Index >= 0 );

	ch = getc(File[Index].fp);
	if( ch == '\n' )
		File[Index].line++;
	if( ch == EOF )
		ch = '\001';
	File[Index].ch = ch;
	return ch;
}

void InputInit(const char *directory)
{	assert( LocalDirectory == NULL );

	LocalDirectory = str_alloc(directory);
	DirSep(LocalDirectory);

	return;
}

void InputPush(const char *root, const char *ext, const int nspace)
{	int index;
	int i;

	char *localname;
	char *name;

	const char *path;

	void (*error)(const char *s1, ...);
	if( Index < 0 )
		error = fatalerr;
	else	error = fatalomh;

	// path corresponding to this file
	localname = strjoin(root, ext);
	path      = InputSearch(root, ext);
	name      = strjoin(path, localname);
	DirSep(name);

	// special name used for empty input stack
	if( strcmp("NONE", name) == 0 ) error(
		"Attempt to open the file named \"NONE\" for reading",
		NULL
	);

	// do not advance Index until we are sure no error occurs
	// so that InputName and InputLine can be used for error reporting
	index = Index + 1;

	if( index >= MAX_FILE ) error(
		"To many input files at once",
		NULL
	);
	File[index].fp = fopen(name, "r");
	if( File[index].fp == NULL ) error(
		"Cannot open the input file: \"",
		name,
		"\"",
		NULL
	);
	File[index].ch   = '\0';
	File[index].line = 1;
	File[index].name = str_alloc(name);

	// ok, no errors occured pushing the file on the stack
	Index = index;

	// print the file name
	if( nspace >= 0 )
	{	printf("\n");
		for(i=0; i<nspace; i++)
			printf(" ");
		printf("%s:", LocalName(name) );
	}

	FreeMem(name);
	FreeMem(localname);

	OmhLexSetInputLine( File[Index].line );

	// save command key character at time of push
	if( Index > 0 )
		File[Index-1].command_key_character_at_push_input =
			GetCommandKeyCharacter();

	// Initialize command key character for this file.
	// The $include command will change it back to previous value
	// (see omhelp.y).
	SetCommandKeyCharacter('$');
	return;
}

void InputPop()
{	assert( Index >= 0 );

	fclose(File[Index].fp);
	FreeMem(File[Index].name);
	Index--;

	if( Index >= 0 )
	{	OmhLexSetInputLine( File[Index].line );
		SetCommandKeyCharacter(
			File[Index].command_key_character_at_push_input
		);
		// This should be done for more than just the '\n' character.
		// To be specific, it should be done whenever we have looked ahead
		// one character before reconizing a token.
		if( File[Index].ch == '\n' )  // this case needed for newlinech
			ungetc(File[Index].ch, File[Index].fp);
	}
	else	SetCommandKeyCharacter('$');
	return;
}

const char *InputName()
{	const char *name;

	if( Index < 0 )
		name = "NONE";
	else
	{	assert( LocalDirectory != NULL );
		name = LocalName( File[Index].name );
	}

	return name;
}

int InputLine()
{	int line;
	if( Index < 0 )
		return 0;

	line = File[Index].line;
	if( File[Index].ch == '\n')
		line--;
	return line;
}

void InputAddPath(const char *path, const char *ext)
{	char *s;
	char ch;
	int i;


	void (*error)(const char *s1, ...);
	if( Index < 0 )
		error = fatalerr;
	else	error = fatalomh;

	assert( LocalDirectory != NULL );

	if( NPath == MAX_PATH ) error(
		"Too many $path commands",
		NULL
	);

	ch = path[strlen(path) - 1];

	if(  ch == '/' || ch == '\\' )
		s = str_alloc(path);
	else	s = strjoin(path, "\\");

	DirSep(s);

	for(i = 0; i < NPath; i++ )
	{	if( strcmp(s, User[i]) == 0 && strcmp( Ext[i], ext ) == 0 )
		{	FreeMem(s);
			return;
		}
	}
	User[NPath] = s;
	Ext[NPath]  = str_alloc(ext);
	if( CompletePath(s) )
		Path[NPath] = str_alloc(s);
	else	Path[NPath] = strjoin(LocalDirectory, s);

	NPath++;
}

const char *InputSearch(const char *root, const char *ext)
{
	int i;
	char *name;
	char *fullname;
	char *message;

	void (*error)(const char *s1, ...);
	if( Index < 0 )
		error = fatalerr;
	else	error = fatalomh;

	name = strjoin(root, ext);
	DirSep(name);
	if( CompletePath(name) )
	{
		if( access(name, 0) == 0 )
		{	FreeMem(name);
			return "";
		}
		message = StrCat(
			__FILE__,
			__LINE__,
			"Cannot find the file \"",
			name,
			"\"",
			NULL
		);
		error(message, NULL);
	}

	fullname = strjoin(LocalDirectory, name);
	if( access(fullname, 0) == 0 )
	{	FreeMem(fullname);
		FreeMem(name);
		return LocalDirectory;
	}
	FreeMem(fullname);

	for(i = 0; i < NPath; i++)
	{	if( strcmp(ext, Ext[i]) == 0 )
		{	fullname = strjoin(Path[i], name);
			if(access(fullname, 0) == 0 )
			{	FreeMem(fullname);
				FreeMem(name);
				return Path[i];
			}
			FreeMem(fullname);
		}
	}

	message = StrCat(
		__FILE__,
		__LINE__,
		"Cannot find the file \"",
		name,
		"\"\nstarting file directory: ",
		LocalDirectory,
		"\n",
		NULL
	);
	for(i = 0; i < NPath; i++)
	{	if( strcmp(ext, Ext[i]) == 0 )
		{	char *s1, *s2;
			s1 = strjoin(message, "\nsearch path: ");
			s2 = strjoin(s1, User[i]);
			FreeMem(message);
			FreeMem(s1);
			message = s2;
		}
	}
	error(message, NULL);

	return NULL;
}

void InputFree()
{	int i;

	for(i = 0; i < NPath; i++)
	{	FreeMem(User[i]);
		FreeMem(Path[i]);
		FreeMem(Ext[i]);
	}
	NPath = 0;

	FreeMem(LocalDirectory);
	LocalDirectory = NULL;
}

void InputSplitName(char **proot, char **pext, const char *filename)
{	char *root;
	char *ext;

	// skip leading white space
	while( isspace((int) *filename ) )
		filename++;

	root = str_alloc(filename);

	// pointer to end of filename copy in root
	ext  = root + strlen(root) - 1;

	// skip trailing white space
	while( isspace((int) *ext ) )
	{	*ext = '\0';
		ext--;
	}


	// pointer to last '.' in filename copy
	while( ext > root && *ext != '.' && *ext != '\\' && *ext != '/' )
		ext--;

	// if there case an extension filename, change '.' to a '\0'
	// and then separately allocate the extension
	if( ext > root && *ext == '.' )
	{	*ext++ = '\0';
		ext = strjoin(".", ext);
	}
	else	ext = str_alloc("");

	// return the pointers
	*proot = root;
	*pext  = ext;
	return;
}
