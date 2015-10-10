# ifndef STR_ALLOC_INCLUDED
# define STR_ALLOC_INCLUDED

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

$table
$bold Syntax$$ $cend
$syntax%str_alloc(*%s%)%$$
$rend
$bold See Also$$ $cend $mref/StrCat/$$
$tend

$fend 25$$

$head Description$$
returns a pointer to a separately allocated
copy of the $code '\0'$$ terminated
character vector specified by $italic s$$.

$head Memory$$
The return value of $code str_alloc$$
points to memory that
should be freed using the routine $xref/AllocMem/FreeMem/FreeMem/$$
when it is no longer needed.
If this memory is not freed,
a call to
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$
will report the corresponding source code line and file where the
corresponding call to $code str_alloc$$ is located.

$head Prototype$$
The argument $italic s$$ is specified as a $code const char*$$
and the return value is a $code char*$$.

$end
------------------------------------------------------------------------
*/

# include <stdlib.h>
# include "StrCat.h"

# define str_alloc(s1)       StrCat(__FILE__, __LINE__, s1, NULL)

# endif
