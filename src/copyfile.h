# ifndef COPYFILE_INCLUDED
# define COPYFILE_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern void copyfile(
	const char *destination,
	const char *source
);
extern void copyfileFreeMemory(void);

# ifdef __cplusplus
}
# endif
# endif
