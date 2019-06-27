# ifndef ALLOCMEM_INCLUDED
# define ALLOCMEM_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif

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

# ifdef __cplusplus
}
# endif
# endif
