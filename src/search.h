# ifndef SEARCH_INCLUDED
# define SEARCH_INCLUDED

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

extern void OpenSearchFile(const char *fileTag, const char *siteTitle);
extern void SearchBegin(const char *tag);
extern void SearchTitle(const char *title);
extern void SearchKeywords(const char *list, const char escape);
extern char *SearchGetKeywords();
extern void SearchEnd(void);
extern void CloseSearchFile(int delete);

# endif
