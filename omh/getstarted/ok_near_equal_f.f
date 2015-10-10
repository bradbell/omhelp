c -----------------------------------------------------------------------------
c OMhelp: Language Independent Embedded Documentation
c           Copyright (C) 1998-2015 Bradley M. Bell
c OMhelp is distributed under the terms of the
c             GNU General Public License Version 2.
c -----------------------------------------------------------------------------
c END COPYRIGHT
c Use integer for return value so that this function is callable by C
      integer function ok_near_equal_f()
      double precision x, y, r, a
      logical near_equal_f
      external near_equal_f
      x = 1.1
      y = 1.2
      r = .1
      a = 0.
      if( near_equal_f(x, y, r, a) ) then
            ok_near_equal_f = 1
      else
            ok_near_equal_f = 0
      endif
      end
