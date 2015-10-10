# ifndef STRJOIN_INCLUDED
# define STRJOIN_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

/*
$begin strjoin$$
$spell
	printf
	Mem
	strjoin
	alloc
$$

$section Macro For Allocating The Concatenation Of Two Strings$$

$index string, allocation with memory checking$$
$index string, concatenation$$
$index concatenation, of strings$$
$index strjoin$$

$table
$bold Syntax$$ $cend
$syntax/strjoin(/s1/, /s2/)/$$
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
	s = strjoin("String one", "String two");
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

# define strjoin(s1, s2)       StrCat(__FILE__, __LINE__, s1, s2, NULL)

# endif
