/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
// BEGIN_NEAR_EQUAL
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
if $icode x$$ is nearly equal to $icode y$$ and false otherwise.

$head x$$
The argument $icode x$$ has prototype
$codei%
	double %x%
%$$

$head y$$
The argument $icode y$$ has prototype
$codei%
	double %y%
%$$

$head r$$
The relative error criteria $icode r$$ has prototype
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
The absolute error criteria $icode a$$ has prototype
$codei%
	double %a%
%$$
It must be greater than or equal zero.
The absolute error condition is satisfied if
$latex \[
	| x - y | \leq a
\] $$

$head e$$
The return value $icode e$$ has prototype
$codei%
	int %e%
%$$
If either the relative or absolute error condition is satisfied,
it is one.
Otherwise, it is zero.


$head Example$$
The following is an example and test of $code near_equal_c$$,
it returns true if the test succeeds and false if it fails:

$verbatim%omh/getstarted/ok_near_equal_c.c%
	5%// BEGIN_OK_NEAR_EQUAL%// END_OK_NEAR_EQUAL%0
%$$


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
// END_NEAR_EQUAL
