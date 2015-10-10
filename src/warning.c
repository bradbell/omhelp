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
warning(msg)
prints a warning message on standard output where ~msg is a '\0'
terminated character row vectos.
**/

# include <stdio.h>
# include <string.h>
# include "input.h"
# include "warning.h"

void warning(const char *message)
{	printf("\nWarning: %s\n", message);
	if( strcmp(InputName(), "NONE") != 0 ) printf(
		"Detected at line %d of file %s\n", InputLine(), InputName()
	);
	return;
}
