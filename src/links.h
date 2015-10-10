# ifndef LINKS_INCLUDED
# define LINKS_INCLUDED

/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2006 Bradley M. Bell

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

# endif
