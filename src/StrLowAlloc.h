# ifndef STR_LOWALLOC_INCLUDED
# define STR_LOWALLOC_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

/*
$begin StrLowAlloc$$
$spell
	Mem
	str
	alloc
	const
$$

$index StrLowAlloc$$
$cindex string lower case allocate$$
$section Allocated Memory for a Lower Case Copy of a String$$

$table
$bold Syntax$$ $cend
$syntax%StrLowAlloc(
	const char *%s%
)%$$ $rend
$rend
$bold See Also$$ $cend $mref/str_alloc/$$
$tend

$head Description$$
returns a pointer to a lower case
copy of the $code '\0'$$ terminated
character vector specified by $italic s$$.

$head Memory$$
The return value of $code StrLowAlloc$$
points to memory that
should be freed using the routine $xref/AllocMem/FreeMem/FreeMem/$$
when it is no longer needed.
If this memory is not freed,
a call to
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$
will report the corresponding source code line and file where the
corresponding call to $code StrLowAlloc$$ is located.

$head Prototype$$
The argument $italic s$$ is specified as a constant $code char*$$
but the compiler will not check that the argument matches the prototype.

$end
------------------------------------------------------------------------
*/

# include <stdlib.h>
# include "StrCat.h"
# include "StrLowCase.h"

# define StrLowAlloc(s)       StrLowCase( str_alloc(s) )

# endif
