/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin int2str$$
$spell
	Mem
	str
	alloc
$$

$index int2str$$
$mindex convert integer number string$$

$section Convert and Integer to a String$$

$table
$bold Syntax$$ $cend
$codei%int2str(%i%)%$$
$rend
$bold See Also$$ $cend $mref/str_alloc/$$
$tend

$head Description$$
returns a pointer to a
$code '\0'$$ terminated character vector that
contains the ascii representation of $italic i$$.

$head Memory$$
The return value of $code int2str$$
points to memory that
should be freed using the routine $cref/FreeMem/AllocMem/FreeMem/$$
when it is no longer needed.
If this memory is not freed,
a call to
$cref/CheckMemoryLeak/AllocMem/CheckMemoryLeak/$$
will report the corresponding source code line and file where the
corresponding call to $code str_alloc$$ is located.

$head Prototype$$
The argument $italic i$$ is specified as an $code int$$
and the return value is a $code char*$$.

$end
------------------------------------------------------------------------
*/

# include "int2str.h"
# include <stdio.h>
# include <assert.h>
# include "allocmem.h"

char *int2str(int i)
{	char *str;

	assert(-1e30 < i && i < 1e30);

	str = AllocMem(20, sizeof(char));
	sprintf(str, "%d", i);

	return str;
}
