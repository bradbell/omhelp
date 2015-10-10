/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

# include <stdio.h>
# include <stdlib.h>

# include "c2fortran.h"

# define OK_NEAR_EQUAL_F C2FORTRAN_GLOBAL_(ok_near_equal_f, OK_NEAR_EQUAL_F)

extern int ok_near_equal_c(void);  // C version
extern int OK_NEAR_EQUAL_F(void);  // Fortran version
int main()
{	int not_ok = 0;
	if( ok_near_equal_c() )
		printf("ok: C version of near_equal\n");
	else
	{	not_ok = 1;
		printf("error: C version of near_equal\n");
	}
	if( OK_NEAR_EQUAL_F() )
		printf("ok: Fortran version of near_equal\n");
	else
	{	not_ok = 1;
		printf("error: Fortran version of near_equal\n");
	}
	exit(not_ok);
}
