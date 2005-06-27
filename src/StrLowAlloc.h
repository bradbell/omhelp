# ifndef STRLOWALLOC_INCLUDED
# define STRLOWALLOC_INCLUDED

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

$fend 25$$

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
