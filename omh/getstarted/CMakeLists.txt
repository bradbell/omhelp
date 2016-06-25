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
SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(bindir ${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${bindir})

# run_all example
ENABLE_LANGUAGE( Fortran OPTIONAL )
IF( CMAKE_Fortran_COMPILER_WORKS )
	INCLUDE( FortranCInterface )
	IF( FortranCInterface_MODULE_FOUND )
		# 2DO: include just C examples when Fortran linking not available

		FortranCInterface_HEADER(c2fortran.h MACRO_NAMESPACE "C2FORTRAN_")
		ADD_EXECUTABLE(run_all
			ok_near_equal_c.c
			ok_near_equal_f.f
			near_equal_c.c
			near_equal_f.f
			run_all.c
		)
	ENDIF( FortranCInterface_MODULE_FOUND )
ENDIF( CMAKE_Fortran_COMPILER_WORKS )

# Build one getstarted example so that omhelp_dir/dictionary.bin gets created.
ADD_CUSTOM_TARGET(
	dictionary_bin
	ALL
	COMMAND ${topbindir}/src/omhelp ${srcdir}/simple_example.omh -omhelp_dir ${topsrcdir}/omhelp_data
)
