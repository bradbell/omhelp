# ifndef SEARCH_INCLUDED
# define SEARCH_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

extern void OpenSearchFile(const char *fileTag, const char *siteTitle);
extern void SearchBegin(const char *tag);
extern void SearchTitle(const char *title);
extern void SearchKeywords(
	const char *list   ,
	const char escape  ,
	const char* ignore
);
extern char *SearchGetKeywords();
extern void SearchEnd(void);
extern void CloseSearchFile(int delete);

# endif
