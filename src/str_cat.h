# ifndef STR_CAT_INCLUDED
# define STR_CAT_INCLUDED

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
------------------------------------------------------------------------
Copyright (C) Harmonic Software Inc. 1997-1998, All rights reserved. 
-------------------------------------------------------------------------
$begin str_cat$$
$spell printf Mem str alloc$$

$section Macro For Allocating The Concatenation Of Two Strings$$

$index string, allocation with memory checking$$
$index string, concatenation$$
$index concatenation, of strings$$
$index str_cat$$

$table
$bold Syntax$$ $cend
$syntax/str_cat(/s1/, /s2/)/$$
$rend
$bold See Also$$ $cend $mref/StrCat/str_alloc/$$
$tend

$fend 15$$

$head Description$$
returns a pointer to the concatenation of the strings
$italic s1$$, and $italic s2$$, 
which are '\0' terminated character vectors.
$pre

$$
The return value is memory that was allocated with $mref/AllocMem/$$
and should be freed using the routine $xref/AllocMem/FreeMem/FreeMem/$$.

$head Example$$
If $code s$$ is a $code char *$$ and you execute the call
$codep
	s = str_cat("String one", "String two");
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

# include <stdlib.h>
# include "StrCat.h"

# define str_cat(s1, s2)       StrCat(__FILE__, __LINE__, s1, s2, NULL)

# endif
