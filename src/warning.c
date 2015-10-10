/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
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
