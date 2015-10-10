# ifndef ALLOCMEM_INCLUDED
# define ALLOCMEM_INCLUDED

// BEGIN SHORT COPYRIGHT
/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2004 Bradley M. Bell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
------------------------------------------------------------------------ */
// END SHORT COPYRIGHT

// NDEBUG is define by the compiler, do not edit the if of this clause
#ifdef NDEBUG
# define ALLOCMEM_ON	0
#else
# define ALLOCMEM_ON	1
#endif

extern void *AllocMemory(int num, int size, const char *file, int line);
extern void FreeMemory(void *ptr, const char *file, int line);
extern void CheckMemoryLeak();

extern void *c_alloc(int num, int size);
extern void c_free(void *ptr);

/*
WARNING: if you change AllocMem, make sure StrCat.c agrees with the change
*/

# if ALLOCMEM_ON

# define AllocMem(num, size) \
	AllocMemory(num, size, __FILE__, __LINE__)

# define FreeMem(ptr) \
	FreeMemory(ptr, __FILE__, __LINE__)

# else

# define AllocMem(num, size) \
	c_alloc(num, size)

# define FreeMem(ptr) \
	c_free(ptr)

# endif

# endif
