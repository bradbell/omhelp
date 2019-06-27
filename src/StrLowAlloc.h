# ifndef STR_LOWALLOC_INCLUDED
# define STR_LOWALLOC_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


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

$head Syntax$$
$codei%StrLowAlloc(
	const char *%s%
)
%$$

$head See Also$$ $mref/str_alloc/$$


$head Description$$
returns a pointer to a lower case
copy of the $code '\0'$$ terminated
character vector specified by $icode s$$.

$head Memory$$
The return value of $code StrLowAlloc$$
points to memory that
should be freed using the routine $cref/FreeMem/AllocMem/FreeMem/$$
when it is no longer needed.
If this memory is not freed,
a call to
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$
will report the corresponding source code line and file where the
corresponding call to $code StrLowAlloc$$ is located.

$head Prototype$$
The argument $icode s$$ is specified as a constant $code char*$$
but the compiler will not check that the argument matches the prototype.

$end
------------------------------------------------------------------------
*/

# include <stdlib.h>
# include "StrCat.h"
# include "StrLowCase.h"

# define StrLowAlloc(s)       StrLowCase( str_alloc(s) )

# ifdef __cplusplus
}
# endif
# endif
