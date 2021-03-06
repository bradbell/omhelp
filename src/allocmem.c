/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin AllocMem_dev$$
$spell
	Alloc
	num
	const
	Mem
	ptr
	allocmem
$$

$section Routines That Track Allocation and Freeing of Memory$$
$mindex memory allocate free$$

$head Syntax$$
$codei%void *AllocMemory(int %num%, int %size%, const char *%file%, int %line%)
%$$
$codei%void *AllocMem(int %num%, int %size%)
%$$
$codei%void FreeMemory(void *%ptr%, const char *%file%, int %line%)
%$$
$codei%void FreeMem(void *%ptr%)
%$$
$codei%void CheckMemoryLeak(void)%$$


$head AllocMemory$$
$index AllocMemory$$
This routine returns a pointer to space that is sufficient
for $icode num$$ elements each of size $icode size$$
where $icode num$$ and $icode size$$ are positive integers.
The memory is allocated using $cref c_alloc_dev$$.
The
$cref/string/glossary_dev/String/$$ $icode file$$ is the
file name and the integer $icode line$$ is the line number
where the call to $code AllocMemory$$ is made.
The standard macros $code __FILE__$$ and $code __LINE__$$
can be used to obtain these values.

$head AllocMem$$
$index AllocMem$$
If $code NDEBUG$$ is defined when $code allocmem.h$$ is included,
this macro calls $code AllocMemory$$ with
the file and line set by the macros
$code __FILE__$$ and $code __LINE__$$ respectively.
Otherwise, this macro just uses
$cref c_alloc_dev$$ to allocate the requested memory.

$head FreeMemory$$
$index FreeMemory$$
This routine frees memory that was allocated with $code AllocMemory$$.
The value $icode ptr$$ must be either $code NULL$$
or a pointer that was allocated using
$code AllocMemory$$.
(If it is $code NULL$$, no action is taken).
The $cref/string/glossary_dev/String/$$ $icode file$$
is the file name and the integer $icode line$$ is the line number
where the call to $code FreeMemory$$ is made.
The standard macros $code __FILE__$$ and $code __LINE__$$
can be used to obtain these values.
If the value $icode ptr$$ was not allocated
using $code AllocMemory$$,
a fatal error message is printed and execution is terminated.

$head FreeMem$$
$index FreeMem$$
If $code NDEBUG$$ is defined when $code allocmem.h$$ is included,
this macro calls $code FreeMemory$$ with
the file and line set by the macros
$code __FILE__$$ and $code __LINE__$$ respectively.
Otherwise, this macro uses $cref/c_free/c_alloc_dev/$$ to directly
the memory pointed to by $icode ptr$$.


$head CheckMemoryLeak$$
$mindex CheckMemoryLeak$$
This routine checks that there are no memory leaks. It generates
an assertion error if any of the memory allocated by $code AllocMemory$$
has not yet been freed by $code FreeMemory$$. If this error occurs, it
also creates a file called $code memory.out$$ in the current directory that
contains the source code file names and line numbers where the memory
that was not freed was allocated.

$end
------------------------------------------------------------------------------
$begin c_alloc_dev$$
$spell
	alloc
	num
	ptr
$$

$section Check Memory Allocation and Free$$

$head Syntax$$
$codei%void *c_alloc(int %n%, int %size%)
%$$
$codei%void c_free(void *%p%)%$$


$head c_alloc$$
$index c_alloc$$
This routine returns a pointer to space that is sufficient
for $icode num$$ elements each of size $icode size$$
where $icode num$$ and $icode size$$ are positive integers.
If the memory cannot be allocated,
an error message is generated on standard output and
the program is terminated.

$head c_free$$
$index c_free$$
This routine frees memory that was allocated with $code c_alloc$$.
The value $icode ptr$$ must be either $code NULL$$
or a pointer that was allocated using
$code AllocMemory$$.
(If it is $code NULL$$, no action is taken.)

$end
*/

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# include "allocmem.h"
# include "trace_exit.h"

typedef struct element
{	void  *ptr;            // value returned by AllocMemory
	char  *check;          // value past end of allocated memory
	char *file;            // corresponding file name
	int   line;            // corresponding line number
	struct element *next;  // next element in linked list
} AllocElement;

// begining of linked list
AllocElement *List = NULL;

void *c_alloc(int n, int size)
{	void *p;
	p = malloc(n * size + 1);
	if( p == NULL)
	{	printf("Cannot allocate %d x %d bytes of memory.\n",
			n, size);
		trace_exit(1);
	}
	return p;
}

void c_free(void *p)
{	if( p != NULL )
		free(p);
	return;
}


void *AllocMemory(int num, int size, const char *file, int line)
{
	void         *R;
	AllocElement *P;

	R = c_alloc(num, size);

	// allocation element for this entry
	P        = (AllocElement *) c_alloc(1, sizeof(AllocElement));

	// value returned by AllocMemory for this element
	P->ptr   = R;

	// place a value to check past the end
	P->check    = ((char *) R) + num * size;
	*(P->check) = 'x';

	// file for this element
	P->file  = (char *) c_alloc(strlen(file) + 1, sizeof(char));
	strcpy(P->file, file);

	// line number for this element
	P->line  = line;

	// put at the front of linked list
	P->next  = List;
	List     = P;

	return R;
}

void FreeMemory(void *ptr, const char *file, int line)
{
	AllocElement        *P;
	AllocElement *Previous;

	if( ptr == NULL) return;

	// search list for pointer
	P        = List;
	Previous = NULL;
	while(P != NULL && P->ptr != ptr)
	{	Previous = P;
		P        = P->next;
	}

	// check if pointer was not in list
	if( P == NULL )
	{	printf("Program Error AllocMem: File %s: Line %d\n",
			file, line);
		printf("Invalid pointer in call FreeMemory(%p)\n", ptr);
		trace_exit(1);
	}

	// check value past end of allocation
	if( *(P->check) != 'x' )
	{	printf("Program Error AllocMem: File %s: Line %d\n",
			file, line);
		printf("Memory over written past the end of allocation\n");
		trace_exit(1);
	}

	// remove pointer from list
	if( Previous != NULL )
		Previous->next = P->next;
	else	List           = P->next;

	c_free(P->file);
	c_free(P);

	c_free(ptr);
	return;
}

void CheckMemoryLeak()
{
	AllocElement *list;
	AllocElement *P;

	if( List == NULL ) return;

	// pointer to memory leaks before call to fp_open which will create
	// more (note that AllocMemory will put new ones at front)
	list = List;

	printf("Program Error: Memory leaks\n");
	for(P = list; P != NULL; P = P->next)
	{	printf("File %s: Line %d\n", P->file, P->line);
		printf("String = %s\n", (char *) P->ptr);
	}
	trace_exit(1);
}
