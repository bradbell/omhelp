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
---------------------------------------------------------------------------
END COPYRIGHT

$begin near_equal_c$$
$spell
	OMhelp
	ifdef
	stdio
	printf
	endif
$$

$section Determine if Two Values Are Nearly Equal$$

$head Syntax$$
$syntax%%e% = near_equal_c(%x%, %y%, %r%, %a%)%$$

$head Purpose$$
Returns true, 
if $italic x$$ is nearly equal to $italic y$$ and false otherwise.

$head x$$
The argument $italic x$$ has prototype
$syntax%
	double %x%
%$$

$head y$$
The argument $italic y$$ has prototype
$syntax%
	double %y%
%$$

$head r$$
The relative error criteria $italic r$$ has prototype
$syntax%
	double %r%
%$$
It must be greater than or equal zero.
The relative error condition is satisfied if
$latex \[
	| x - y | \leq r ( |x| + |y| )
\] $$
where $latex \leq$$ denotes less than or equal.

$head a$$
The absolute error criteria $italic a$$ has prototype
$syntax%
	double %a%
%$$
It must be greater than or equal zero.
The absolute error condition is satisfied if
$latex \[
	| x - y | \leq a
\] $$

$head e$$
The return value $italic e$$ has prototype
$syntax%
	int %e%
%$$
If either the relative or absolute error condition is satisfied,
it is one.
Otherwise, it is zero.


$head Example$$
The following is an example and test of $code near_equal_c$$,
it returns true if the test succeeds and false if it fails:

$comment no indent, start output at text following END COPYRIGHT$$
$code
$verbatim%ok_near_equal_c.c%0%END COPYRIGHT%$$
$$


$end
---------------------------------------------------------------------------
*/
# include <math.h>

int near_equal_c(double x, double y, double r, double a)
{	double ax = fabs(x);
	double ay = fabs(y);
	double ad = fabs(x - y);
	int e = (ad <= a) | (ad <= r * (ax + ay));
	return e;
}
