# ifndef HREF_INCLUDED
# define HREF_INCLUDED

/* -----------------------------------------------------------------------
OMhelp: Source Code -> Help Files: Copyright (C) 1998-2009 Bradley M. Bell

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

# include "section.h"

extern void HrefOutputPass1(
	const char *tag,
	const char *head,
	const char *external,
	const char *displayframe,
	const char *display_printid
);
extern void HrefOutputPass2(
	const char *tag,
	const char *head,
	const char *external,
	const char *displayframe
);
extern void HrefPrintablePass2(
	const char *printid,
	const char *display_printid
);
extern void HrefEnd(
	const char *s
);
extern void HrefAddList(
	const char *tagfrom,
	const char *headfrom,
	const char *urlto,
	const char *headto
);
extern void HrefOutputList(
	SectionInfo *section
);
extern void HrefFreeMemory(
	void
);

/*
$begin href$$
$escape #$$
$spell

$$

$section Output Cross References During Both Pass1 and Pass2$$

$head Description$$
The functions listed below output and track cross references during both
Pass1 and Pass2. During Pass1, these references may refer to a
cross reference tag and heading. During Pass2, they always refer to
an HTML file.

$comment
Only include href.c because routines in that file refer
back to here for the list of all routines in that file
$$
$childtable/
	href.c/$$
$end
*/

# endif
