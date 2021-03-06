# ifndef LINKS_INCLUDED
# define LINKS_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


extern void BeginLinks(
	const char *fromtag,
	const char *direction,
	const char *image_link,
	const char *image_file,
	const char *stylecmd
);
extern void TitleLinks(
	const char *title
);
extern void AddLink(
	const char *text,
	const char *tag,
	const char *crossheading
);
void EndLinks();

# ifdef __cplusplus
}
# endif
# endif
