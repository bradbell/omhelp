// BEGIN SHORT COPYRIGHT
/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2004 Bradley M. Bell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
------------------------------------------------------------------------ */
// END SHORT COPYRIGHT
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
$syntax%int2str(%i%)%$$
$rend
$bold See Also$$ $cend $mref/str_alloc/$$
$tend

$fend 25$$

$head Description$$
returns a pointer to a
$code '\0'$$ terminated character vector that
contains the ascii representation of $italic i$$.

$head Memory$$
The return value of $code int2str$$
points to memory that
should be freed using the routine $xref/AllocMem/FreeMem/FreeMem/$$
when it is no longer needed.
If this memory is not freed,
a call to
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$
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
