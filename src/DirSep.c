/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
Convert file names from internal representation to external representation.

The windows file system uses the back slash to separate directories
in file names. The Unix file system uses forward slashes.
The directory separators are converted to the proper character for the
system that is doing the compliation.
*/

# include <stdio.h>
# include <ctype.h>

# ifdef WIN32
# include <io.h>
# endif

# include "str_alloc.h"
# include "allocmem.h"

# include "DirSep.h"


# define FORWARD_SLASH 47
# define BACK_SLASH    92

# ifdef WIN32
# define FROM FORWARD_SLASH
# define TO   BACK_SLASH
# else
# define FROM BACK_SLASH
# define TO   FORWARD_SLASH
# endif

void DirSep(char *name)
{	while( *name != '\0' )
	{	if( *name == FROM )
			*name = TO;
		name++;
	}
}
