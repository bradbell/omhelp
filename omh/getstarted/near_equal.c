/*
---------------------------------------------------------------------------
$begin near_equal.c$$
$spell
	OMhelp
	ifdef
	stdio
	printf
	endif
$$

$section Determine if Two Values Are Nearly Equal$$

$head Syntax$$
$syntax%e = near_equal(%x%, %y%, %r%, %a%)%$$

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
If the preprocessor directive $code TEST_NEAR_EQUAL$$ is defined,
the following program should print yes
(The C source code below is both in program and OMhelp output):
$codep */

# ifdef TEST_NEAR_EQUAL
# include <stdio.h>

extern int near_equal(double x, double y, double r, double a);
main()
{	double x = 1.1;
	double y = 1.2;
	double r = .1;
	double a = 0.;
 	if( near_equal(x, y, r, a) )
		printf("yes\n");
	else	printf("no\n");
	exit(0);
}

# endif

/* $$

$end
---------------------------------------------------------------------------
*/
# include <math.h>

int near_equal(double x, double y, double r, double a)
{	double ax = fabs(x);
	double ay = fabs(y);
	double ad = fabs(x - y);
	int e = (ad <= a) | (ad <= r * (ax + ay));
	return e;
}
