/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin StrCat$$
$spell str StrCat printf Mem$$

$section Memory Allocation And Concatenation Of Strings$$

$index string, allocation with memory checking$$
$index string, concatenation$$
$index concatenation of strings$$
$index StrCat$$

$head Syntax$$ $codei/StrCat(/file/, /line/, /s1/, /s2/, /.../, NULL)
/$$

$head See Also$$ $mref/strjoin/str_alloc/$$


$head Description$$
returns a pointer to the concatenation of the strings
$icode s1$$, $icode s2$$, ...
which are '\0' terminated character vectors except for the last
string which is NULL.
There can be at most 100 '\0' terminated strings in the argument list.
$pre

$$
The argument $icode file$$ is a '\0' terminated
character vector that specifies
the file for memory allocation reporting.
The argument $icode line$$ is an integer specifying the line for
memory allocate reporting.
$pre

$$
The return value is memory that was allocated with $mref/AllocMem/$$
and should be freed using the routine $cref/FreeMem/AllocMem/FreeMem/$$.

$head Example$$
The macros $code __FILE__$$ and $code __LINE__$$
can be used to pass the current file and line number to $code StrCat$$.
If $code s$$ is a $code char *$$ and you execute the call
$codep
	s = StrCat(__FILE__, __LINE__, "String one", "String two", NULL);
	printf("%s\n", s);
$$
The text
$codep
	string oneString two
$$
will be printed on standard out.
When you are done with the string, you should free the memory pointed to
by $code s$$, for example, you could make the call
$codep
	FreeMem(s);
$$
if $code s$$ has not changed since its assignment above.
$end
------------------------------------------------------------------------
*/

# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <assert.h>
# include "allocmem.h"
# include "StrCat.h"

# define MAX_STRING 100

char *StrCat(const char *file, int line, ... )
{
	char     *s[MAX_STRING];
	char     *r;
	int      len;
	int      n;
	int      i;
	va_list  argList;

	// skip first two arguments
	va_start(argList, line);

	// get the string arguments
	n    = 0;
	len  = 0;
	s[n] = va_arg(argList, char *);
	while( s[n] != NULL )
	{	assert(n < MAX_STRING);
		len = len + strlen(s[n]);
		n++;
		s[n] = va_arg(argList, char*);
	}

	// allocate memory with same specification as AllocMem
	// except that file and line correspond to calling routine
# if ALLOCMEM_ON
	r   = (char *) AllocMemory(len + 1, sizeof(char), file, line);
# else
	r   = (char *) c_alloc(len + 1, sizeof(char));
# endif


	// copy the strings into the return value
	len = 0;
	for(i = 0; i < n; i++)
	{	strcpy(r + len, s[i]);
		len = len + strlen(s[i]);
	}

	return r;
}
