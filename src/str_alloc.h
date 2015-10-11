# ifndef STR_ALLOC_INCLUDED
# define STR_ALLOC_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

/*
$begin str_alloc$$
$spell
	Mem
	str
	alloc
	const
$$

$index str_alloc$$
$cindex string copy$$
$cindex allocate memory$$
$section Copy a String to Separately Allocated Memory$$

$head Syntax$$
$codei%str_alloc(*%s%)
%$$

$head See Also$$ $mref/StrCat/$$


$head Description$$
returns a pointer to a separately allocated
copy of the $code '\0'$$ terminated
character vector specified by $icode s$$.

$head Memory$$
The return value of $code str_alloc$$
points to memory that
should be freed using the routine $cref/FreeMem/AllocMem/FreeMem/$$
when it is no longer needed.
If this memory is not freed,
a call to
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$
will report the corresponding source code line and file where the
corresponding call to $code str_alloc$$ is located.

$head Prototype$$
The argument $icode s$$ is specified as a $code const char*$$
and the return value is a $code char*$$.

$end
------------------------------------------------------------------------
*/

# include <stdlib.h>
# include "StrCat.h"

# define str_alloc(s1)       StrCat(__FILE__, __LINE__, s1, NULL)

# endif
