c ---------------------------------------------------------------------------
c OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell
c
c This program is free software; you can redistribute it and/or
c modify it under the terms of the GNU General Public License
c as published by the Free Software Foundation; either version 2
c of the License, or (at your option) any later version.
c
c This program is distributed in the hope that it will be useful,
c but WITHOUT ANY WARRANTY; without even the implied warranty of
c MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
c GNU General Public License for more details.
c
c You should have received a copy of the GNU General Public License
c along with this program; if not, write to the Free Software
c Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
c ---------------------------------------------------------------------------
c END COPYRIGHT
c
c $begin near_equal_f$$ $newlinech c$$
c $spell
c $$
c
c $section Determine if Two Values Are Nearly Equal$$
c
c $head Syntax$$
c $syntax%%e% = near_equal_f(%x%, %y%, %r%, %a%)%$$
c
c $head Purpose$$
c Returns true,
c if $italic x$$ is nearly equal to $italic y$$ and false otherwise.
c
c $head x$$
c The argument $italic x$$ has prototype
c $syntax%
c	double precision %x%
c %$$
c
c $head y$$
c The argument $italic y$$ has prototype
c $syntax%
c	double precision %y%
c %$$
c
c $head r$$
c The relative error criteria $italic r$$ has prototype
c $syntax%
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
c The absolute error criteria $italic a$$ has prototype
c $syntax%
c	double precision %a%
c %$$
c It must be greater than or equal zero.
c The absolute error condition is satisfied if
c $latex \[
c	| x - y | \leq a
c \] $$
c
c $head e$$
c The return value $italic e$$ has prototype
c $syntax%
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
c $verbatim%ok_near_equal_f.f%0%END COPYRIGHT%$$
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
