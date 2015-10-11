/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
// END COPYRIGHT
/*
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
$icode%e% = near_equal_c(%x%, %y%, %r%, %a%)%$$

$head Purpose$$
Returns true,
if $italic x$$ is nearly equal to $italic y$$ and false otherwise.

$head x$$
The argument $italic x$$ has prototype
$codei%
	double %x%
%$$

$head y$$
The argument $italic y$$ has prototype
$codei%
	double %y%
%$$

$head r$$
The relative error criteria $italic r$$ has prototype
$codei%
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
$codei%
	double %a%
%$$
It must be greater than or equal zero.
The absolute error condition is satisfied if
$latex \[
	| x - y | \leq a
\] $$

$head e$$
The return value $italic e$$ has prototype
$codei%
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
