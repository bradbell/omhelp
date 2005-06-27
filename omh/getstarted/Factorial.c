/*
---------------------------------------------------------------------------
$begin Factorial.c$$
$spell
	ifdef
	stdio
	printf
	endif
$$

$section Compute Factorial of an Integer$$

$table
$bold Syntax$$
$syntax%int Factorial(int %n%)%$$
$tend

$head Description$$
Returns the value
$math%
	n * (n-1) * ... * 2 * 1
%$$
where $italic n$$ is a positive integer.

$head Example$$
If the preprocessor directive $code TestFactorial$$ is defined,
the following code computes the factorial of 3:
$comment The C soruce code below is both in program and OMhelp output$$
$codep */

# ifdef TestFactorial
# include <stdio.h>

main()
{	printf("Factorial(3) = %d\n", Factorial(3));
	exit(0);
}

# endif

/* $$

$end
---------------------------------------------------------------------------
*/

int Factorial(n)
{
	if( n == 1 )
		return 1;
	else	return n * Factorial(n-1);
}
