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
// END COPYRIGHT
// This extern statement should be in an include file so that it can be
// included and checked by near_equal_c.c.
extern int near_equal_c(double x, double y, double r, double a);

int ok_near_equal_c()
{	double x = 1.1;
	double y = 1.2;
	double r = .1;
	double a = 0.;
 	if( near_equal_c(x, y, r, a) )
		return 1; // expected return value (true)
	else	return 0; // error return value (false)
}
