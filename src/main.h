# ifndef MAIN_INCLUDED
# define MAIN_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern int PrintableOmhelp(void);
extern int PostWarnings(void);
extern int NoFrame(void);
extern int FaviconSpecified(void);
extern const char* ImageFile(void);
extern const char* ImageLink(void);
extern const char* SiteName(void);
extern const char* OmhDir(void);


# ifdef __cplusplus
}
# endif
# endif
