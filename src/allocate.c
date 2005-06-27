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
/* Allocate and clear storage for bison,
   Copyright (C) 1984, 1989 Free Software Foundation, Inc.

This file is part of Bison, the GNU Compiler Compiler.

Bison is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

Bison is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Bison; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */


#include <stdio.h>

extern char *calloc ();
extern char *realloc ();
extern void done ();

extern char *program_name;

char *
xmalloc (n)
     register unsigned n;
{
  register char *block;

  /* Avoid uncertainty about what an arg of 0 will do.  */
  if (n == 0)
    n = 1;
  block = calloc (n, 1);
  if (block == NULL)
    {
      fprintf (stderr, "%s: memory exhausted\n", program_name);
      done (1);
    }

  return (block);
}

char *
xrealloc (block, n)
     register char *block;
     register unsigned n;
{
  /* Avoid uncertainty about what an arg of 0 will do.  */
  if (n == 0)
    n = 1;
  block = realloc (block, n);
  if (block == NULL)
    {
      fprintf (stderr, "%s: memory exhausted\n", program_name);
      done (1);
    }

  return (block);
}
