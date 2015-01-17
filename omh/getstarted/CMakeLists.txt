# ---------------------------------------------------------------------------
# OMhelp: Source Code -> Help Files: Copyright (C) 1998-2015 Bradley M. Bell
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# ---------------------------------------------------------------------------
SET(CMAKE_BUILD_TYPE DEBUG)

SET(bindir ${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${srcdir} ${bindir})
FortranCInterface_HEADER(c2fortran.h MACRO_NAMESPACE "C2FORTRAN_")

ADD_EXECUTABLE(run_all
	ok_near_equal_c.c
	ok_near_equal_f.f
	near_equal_c.c
	near_equal_f.f
	run_all.c
)
