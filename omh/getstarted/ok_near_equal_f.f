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
