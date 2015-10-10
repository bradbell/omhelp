# ifndef HREF_INCLUDED
# define HREF_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

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
