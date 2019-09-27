/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
// BEGIN_OK_NEAR_EQUAL
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
// END_OK_NEAR_EQUAL
