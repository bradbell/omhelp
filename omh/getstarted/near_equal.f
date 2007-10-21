c $begin near_equal.f$$ $newlinech c$$
c $spell
c $$
c 
c $section Determine if Two Values Are Nearly Equal$$
c 
c $head Syntax$$
c $syntax%e = near_equal(%x%, %y%, %r%, %a%)%$$
c 
c $head Purpose$$
c Returns true, 
c if $italic x$$ is nearly equal to $italic y$$ and false otherwise.
c 
c $head x$$
c The argument $italic x$$ has prototype
c $syntax%
c 	DOUBLE PRECISION %x%
c %$$
c 
c $head y$$
c The argument $italic y$$ has prototype
c $syntax%
c 	DOUBLE PRECISION %y%
c %$$
c 
c $head r$$
c The relative error criteria $italic r$$ has prototype
c $syntax%
c 	DOUBLE PRECISION %r%
c %$$
c It must be greater than or equal zero.
c The relative error condition is satisfied if
c $latex \[
c 	| x - y | \leq r ( |x| + |y| )
c \] $$
c where $latex \leq$$ denotes less than or equal.
c 
c $head a$$
c The absolute error criteria $italic a$$ has prototype
c $syntax%
c 	DOUBLE PRECISION %a%
c %$$
c It must be greater than or equal zero.
c The absolute error condition is satisfied if
c $latex \[
c 	| x - y | \leq a
c \] $$
c 
c $head e$$
c The return value $italic e$$ has prototype
c $syntax%
c 	logical %e%
c %$$
c If either the relative or absolute error condition is satisfied,
c it is true.
c Otherwise, it is false.
c 
c 
c $head Example$$
c The Fortran following program would print yes:
c $codep
c     PROGRAM main
c     DOUBLE PRECISION x, y, r, a
c     LOGICAL near_equal
c     external near_equal
c     x = 1.1
c     y = 1.2
c     r = .1
c     a = 0.
c     IF( near_equal(x, y, r, a) ) THEN
c           write(6, *) 'yes'
c     ELSE
c           write(6, *) 'no'
c     ENDIF
c     END
c $$
c $end
c ---------------------------------------------------------------------------
      LOGICAL function near_equal(x, y, r, a)
      DOUBLE PRECISION x, y, r, a
      DOUBLE PRECISION ax, ay, d
      ax = dabs(x);
      ay = dabs(y);
      ad = dabs(x - y);
      near_equal = (ad .LE. a) .OR. (ad .LE. r * (ax + ay));
      END
