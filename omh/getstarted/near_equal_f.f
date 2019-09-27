c -----------------------------------------------------------------------------
c OMhelp: Language Independent Embedded Documentation
c           Copyright (C) 1998-2019 Bradley M. Bell
c OMhelp is distributed under the terms of the
c             GNU General Public License Version 2.
c -----------------------------------------------------------------------------
c BEGIN_NEAR_EQUAL
c $begin near_equal_f$$ $newlinech c$$
c $spell
c $$
c
c $section Determine if Two Values Are Nearly Equal$$
c
c $head Syntax$$
c $icode%e% = near_equal_f(%x%, %y%, %r%, %a%)%$$
c
c $head Purpose$$
c Returns true,
c if $icode x$$ is nearly equal to $icode y$$ and false otherwise.
c
c $head x$$
c The argument $icode x$$ has prototype
c $codei%
c	double precision %x%
c %$$
c
c $head y$$
c The argument $icode y$$ has prototype
c $codei%
c	double precision %y%
c %$$
c
c $head r$$
c The relative error criteria $icode r$$ has prototype
c $codei%
c	double precision %r%
c %$$
c It must be greater than or equal zero.
c The relative error condition is satisfied if
c $latex \[
c	| x - y | \leq r ( |x| + |y| )
c \] $$
c where $latex \leq$$ denotes less than or equal.
c
c $head a$$
c The absolute error criteria $icode a$$ has prototype
c $codei%
c	double precision %a%
c %$$
c It must be greater than or equal zero.
c The absolute error condition is satisfied if
c $latex \[
c	| x - y | \leq a
c \] $$
c
c $head e$$
c The return value $icode e$$ has prototype
c $codei%
c	logical %e%
c %$$
c If either the relative or absolute error condition is satisfied,
c it is true.
c Otherwise, it is false.
c
c
c $head Example$$
c The following is an example and test of $code near_equal_f$$.
c It returns true if the test succeeds and false if it fails.
c
c $comment no indent, start output at text following END COPYRIGHT$$
c $code
c $verbatim%omh/getstarted/ok_near_equal_f.f%
c       5%c BEGIN_OK_NEAR_EQUAL_F%c END_OK_NEAR_EQUAL_F%0
c %$$
c $$
c
c $end
c ---------------------------------------------------------------------------
      logical function near_equal_f(x, y, r, a)
      double precision x, y, r, a
      double precision ax, ay, d
      ax = dabs(x);
      ay = dabs(y);
      ad = dabs(x - y);
      near_equal_f = (ad .le. a) .or. (ad .le. r * (ax + ay));
      end
c END_NEAR_EQUAL
