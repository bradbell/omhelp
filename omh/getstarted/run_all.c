/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell

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
extern int ok_near_equal_c(void);    // C version
extern int ok_near_equal_f__(void);  // Fortran version
int main()
{	int not_ok = 0;
	if( ok_near_equal_c() )
		printf("ok: C version of near_equal\n");
	else
	{	not_ok = 1;
		printf("error: C version of near_equal\n");
	}
	if( ok_near_equal_f__() )
		printf("ok: Fortran version of near_equal\n");
	else
	{	not_ok = 1;
		printf("error: Fortran version of near_equal\n");
	}
	exit(not_ok);
}
