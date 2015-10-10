# ifndef OUTPUT_INCLUDED
# define OUTPUT_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

extern void  FormatOutput(const char *fmt, const char *s);
extern void  FormatOutput2(const char *fmt, const char *s1, const char *s2);
extern void  OutputString(const char *s);
extern void  OutputChar(char ch);
extern void  PopOutput(void);
extern void  PushOutput(const char *name);
extern const char *OutputName(void);

# endif
