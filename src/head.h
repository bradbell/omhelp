# ifndef HEAD_INCLUDED
# define HEAD_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

extern void InitializeHeading(void);
extern void SetHeading(const char* heading);
extern void SetSubHeading(const char* subheading);
extern const char *HeadingAndSubHeading(void);
extern const char *HeadingAndSubPrintId(void);

# endif
