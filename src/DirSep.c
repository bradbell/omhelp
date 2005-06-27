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
