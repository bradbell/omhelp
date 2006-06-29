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
/*
Assumption: ~tag[0] != '\0' and ! isspace(tag[0])
=============================================================================
$begin HrefOutputPass1$$
$escape @$$
$spell
	Href
	const
	url
	isspace
	displayframe
$$
$index HrefOutputPass1$$
$cindex output pass1 cross reference$$

$section Output Cross References During Pass1$$

$table
$bold Syntax$$
$cend $syntax%void HrefOutputPass1( 
	const char *%tag%, 
	const char *%head%, 
	const char *%external%,
	const char *%displayframe%
)%$$ $rend
$bold See Also$$ 
$cend $mref/HrefOutputPass2/$$
$tend

$fend 25$$

$head Description$$
The arguments are all
$code '\0'$$ terminated character vectors.
The following value is written to the output file:
$syntax%
	<HREF="%tag%#%head%#%external%#%displayframe%">
%$$
$end
=============================================================================
$begin HrefOutputPass2$$
$escape @$$
$spell
	Href
	const
	url
	isspace
	displayframe
$$
$index HrefOutputPass2$$
$cindex output pass2 cross reference$$

$section Output Cross References During Pass2$$

$table
$bold Syntax$$
$cend $syntax%void HrefOutputPass2( 
	const char *%tag%, 
	const char *%head%, 
	const char *%external%,
	const char *%displayframe%
)%$$ $rend
$bold See Also$$ 
$cend $mref/HrefOutputPass1/HrefPrintablePass2/$$
$tend

$fend 25$$

$head Description$$
The arguments are all
$code '\0'$$ terminated character vectors.
$syntax%

%tag%
%$$
This argument specifies the referenced section by its
cross reference tag.
$syntax%

%head%
%$$
This argument specifies the heading with in the referenced
section that the link is to. 
If the link is to the entire section, head is equal to the empty string.
$syntax%

%external%
%$$
If $italic external$$ is $syntax%"%true%"%$$,
the cross reference is a complete specified by $italic tag$$
is a complete URL.
Otherwise, $italic external$$ must be false
and the cross reference is internal to the web site being built.
$syntax%

%displayframe%
%$$
If $italic displayframe$$ is the empty string,
or if $code NoFrame()$$ is true,
the entire window is replaced by the link.
Otherwise, the frame named $syntax%frame%displayframe%$$ is replaced.


$head Restrictions$$
The argument $italic tag$$ must satisfy the following conditions:
$syntax%
	assert( %tag%[0] != '\0' );
	assert( ! isspace(%tag%[0]) );
%$$
A call to the routine $mref/HrefEnd/$$ must follow any call
to $code HrefOutputPass2$$ and precede a call to any of the routines
listed in section $tref href$$.
$end
=============================================================================
$begin HrefPrintablePass2$$
$escape @$$
$spell
	Href
	const
	url
	isspace
	displayframe
	printable
	printid
$$
$index HrefPrintablePass2$$
$cindex printable pass2 cross reference$$

$section Printable Version of Cross References During Pass2$$

$table
$bold Syntax$$
$cend $syntax%void HrefPrintablePass2( 
	const char *%printid%
)%$$ $rend
$bold See Also$$ 
$cend $mref/HrefOutputPass1/HrefOutputPass2/$$
$tend

$fend 25$$

$head Description$$
The argument $italic printid$$ is a
$code '\0'$$ terminated character vector.
$syntax%

%printid%
%$$
This is the unique id that specifies the cross reference 
within the output file.
It is assumed that the destination point is defined by an
anchor with NAME equal to this value


$head Restrictions$$
A call to the routine $mref/HrefEnd/$$ must follow any call
to $code HrefPrintablePass2$$ and precede a call to any of the routines
listed in section $tref href$$.
$end
=============================================================================
$begin HrefEnd$$
$escape @$$
$spell
	Href
	const
$$

$index HrefEnd$$
$cindex terminate pass1 @or pass2 cross reference$$

$section Terminate a Pass1 or Pass2 Cross References$$

$table
$bold Syntax$$
$cend $syntax%void HrefEnd(
	const char *%s%
)%$$ $rend
$bold See Also$$ 
$cend $mref/HrefOutputPass1/HrefOutputPass2/$$
$tend

$fend 25$$

$head Description$$
The text output after a call to
$mref/HrefOutputPass1/$$ or
$mref/HrefOutputPass2/$$ is what the user sees for 
a cross reference link.
The routine $code HrefEnd$$ terminates this linking text. 
In addition, it follows this termination by the text specified
by $italic s$$ where $italic s$$ is a $code '\0'$$ terminated
character vector.

$head Terminate a Pass1 Reference$$
If a call to $code HrefOutputPass1$$ preceded the call to $code HrefEnd$$,
the value
$syntax%
	</HREF>%s%
%$$
is written to the output file.

$head Terminate a Pass2 Reference$$
If a call to $code HrefOutputPass2$$ preceded the call to $code HrefEnd$$,
the value
$syntax%
	</a>%s%
%$$
is written to the output file.
Any addition formatting initiated by the preceding call is also terminated.

$head Restrictions$$
A call to the routine $mref/HrefOutputPass1/$$ 
or $mref/HrefOutputPass2/$$ must precede any call
to $code HrefEnd$$ and no other of the routines
listed in section $tref href$$ can be between these calls.

$end
=============================================================================
$begin HrefAddList$$
$escape @$$
$spell
	Href
	const
	TagFrom
	HeadFrom
	UrlTo
	HeadTo
$$
$index HrefAddList$$
$cindex add @to cross reference track list$$

$section Add an Entry to The Cross Reference Tracking List$$

$table
$bold Syntax$$
$cend $syntax%void HrefAddList(
	const char *%TagFrom%,
	const char *%HeadFrom%,
	const char *%UrlTo%,
	const char *%HeadTo%
)%$$ $rend
$bold See Also$$
$cend $mref/HrefOutputList/$$
$tend

$fend 25$$

$head Description$$
A call to $code HrefAddList$$ adds a cross reference to
the list that is output by a call to $mref/HrefOutputList/$$. 
$syntax%

%TagFrom%
%$$
The $code '\0'$$ 
terminated character vector $italic TagFrom$$ specifies 
the cross reference tag
for the section where the cross reference command occurs.
$syntax%

%HeadFrom%
%$$
The $code '\0'$$ 
terminated character vector $italic TagFrom$$ specifies 
the previous $xref/glossary/Cross Reference Heading/cross reference heading/$$ 
in the section where the cross reference command occurs.
$syntax%

%UrlTo%
%$$
The $code '\0'$$ terminated character vector 
$italic UrlTo$$ specifies the destination web resource for the
cross reference address as a URL.
$syntax%

%HeadTo%
%$$
The $code '\0'$$ terminated character vector 
$italic HeadTo$$ specifies the heading (or data) for the web resource 
being referenced by $italic UrlTo$$.
$end
=============================================================================
$begin HrefOutputList$$
$escape @$$
$spell
	Href
	const
	tmp
$$

$index HrefOutputList$$
$cindex output cross reference track list$$

$section Output Cross References Tracking List as an HTML File$$

$table
$bold Syntax$$
$cend $syntax%void HrefOutputList(
	SectionInfo *%section%
)%$$ $rend
$bold See Also$$
$cend $mref/HrefAddList/$$
$tend

$fend 25$$


$head Description$$
Creates a Pass1 HTML file that contains
a list of all the references corresponding to calls to $mref/HrefAddList/$$.
The argument $italic section$$ is a $xref/SectionInfo/$$ pointer
that specifies the section corresponding to this automatically 
generated output.
The output file has root name $syntax//section/->tag/$$
and extension $code .tmp$$.
It is a Pass1 output file because the cross references
use the $xref/HrefOutputPass1/$$ format.
The resulting section contains a table of cross reference links
where each destination link is matched to all there places where
it is referenced.

$end
=============================================================================
$begin HrefFreeMemory$$
$spell
	Href
$$

$index HrefFreeMemory$$
$cindex free href allocate memory$$
$section Free All Memory Allocated by Href Routines$$

$table
$bold Syntax$$
$cend $syntax/void HrefFreeMemory()/$$  $rend
$bold See Also$$
$cend $mref/href/$$
$tend

$fend 25$$


$head Description$$
This routine frees all memory associated with
other routines in the $mref/href/$$ section.
It should be called after all the calls to those
routines and before any call to 
$xref/AllocMem/CheckMemoryLeak/CheckMemoryLeak/$$.
None of the routines listed in $mref/href/$$ should be called
after this routine is called.
$end
=============================================================================
*/
# include "href.h"

# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>

# include "url.h"
# include "convert.h"
# include "output.h"
# include "allocmem.h"
# include "str_cat.h"
# include "input.h"
# include "str_alloc.h"
# include "allocmem.h"
# include "cross.h"
# include "main.h"
# include "section.h"
# include "Internal2Out.h"

# ifndef WIN32
# define stricmp strcasecmp 
# endif

# define UNDEFINED  -1
# define YES         1
# define NO          0

// did previous href have a heading
static int PreviousItalic = UNDEFINED;

// pass corresponding to previous href
static int PreviousPass    = UNDEFINED;

void HrefOutputPass1(
	const char *tag, 
	const char *head, 
	const char *external,
	const char *displayframe)
{
	assert( *tag != '\0' );
	assert( ! isspace(*tag) );
	assert(PreviousPass == UNDEFINED);


	FormatOutput("<HREF=\"%s",     tag);
	FormatOutput("#%s", head);
	FormatOutput("#%s", external);
	FormatOutput("#%s\">", displayframe);

	// previous heading is undefined on pass 1
	PreviousPass    = 1;
	PreviousItalic  = UNDEFINED;
}

void HrefOutputPass2(
	const char *tag, 
	const char *head, 
	const char *external,
	const char *displayframe )
{	char *url;
	char *target;

	assert( *tag != '\0' );
	assert( ! isspace(*tag) );
	assert( strcmp(external, "true") == 0 || 
	        strcmp(external, "false") == 0 
	);

	// overide displayframe setting
	if( NoFrame() )
		displayframe = "";

	// make sure not nesting href calls
	assert(PreviousItalic == UNDEFINED);
	assert(PreviousPass   == UNDEFINED);

	// set url
	url = Url(tag, head, external);

	// set target
	if( displayframe[0] == '\0' )
		target = str_alloc( "_top" );
	else	target = str_cat("frame", displayframe);

	FormatOutput("<a href=\"%s\"", url);
	FormatOutput(" target=\"%s\">", target);

	PreviousItalic = NO;
	if( displayframe[0] != '\0' )
	{	PreviousItalic = YES;
		OutputString("<i>");
	}
	PreviousPass = 2;
	
	FreeMem(target);
	FreeMem(url);
	return;
}

void HrefPrintablePass2(
	const char *printid )
{
	FormatOutput("<a href=\"#%s\">", printid);


	PreviousPass   = 2;
	PreviousItalic = NO;
	
	return;
}
void HrefEnd(const char *s)
{
	assert( PreviousPass  != UNDEFINED );
	if( PreviousPass == 2 )
		assert( PreviousItalic != UNDEFINED );

	if( PreviousPass == 2 && PreviousItalic == YES )
		OutputString("</i>");

	if( PreviousPass == 1 )
		FormatOutput("</HREF>%s", s);
	else	FormatOutput("</a>%s", s);

	// previous href is  not defined
	PreviousItalic  = UNDEFINED;
	PreviousPass    = UNDEFINED;
}



typedef struct hrefInfo {
	char *TagFrom;    // tag where this href coming from
	char *HeadFrom;   // cross reference heading where coming from
	char *UrlTo;      // universal resource location where reference is to 
	char *HeadTo;     // heading where reference it to
	struct hrefInfo *next;
} HrefInfo;

static HrefInfo *Root = NULL;

void HrefAddList(
	const char *TagFrom, 
	const char *HeadFrom,
	const char *UrlTo, 
	const char *HeadTo)
{
	HrefInfo *track;
	HrefInfo *previous;

	assert( *TagFrom != '\0' );
	assert( *UrlTo != '\0' );

	assert( ! isspace(*TagFrom) );
	assert( ! isspace(*UrlTo) );

	// search to find location of this entry in sorted list
	track    = Root;
	previous = NULL;
	while( track != NULL 
	       && stricmp(track->UrlTo, UrlTo) < 0
	)
	{
		previous = track;
		track    = track->next;
	}
	while( track != NULL 
	       && stricmp(track->UrlTo, UrlTo) == 0 
	       && stricmp(track->HeadTo, UrlTo) < 0
	)
	{
		previous = track;
		track    = track->next;
	}
	track            = AllocMem(1, sizeof(HrefInfo));
	track->TagFrom   = str_alloc(TagFrom);
	track->HeadFrom  = str_alloc(HeadFrom);
	track->UrlTo     = str_alloc(UrlTo);
	track->HeadTo    = str_alloc(HeadTo);
	if( previous == NULL )
	{	track->next = Root;
		Root        = track;
	}
	else
	{	track->next    = previous->next;
		previous->next = track;
	}
}
	
void HrefOutputList(SectionInfo *section)
{	HrefInfo *track;
	char     *file;
	char     *frame;

	
	// open output file
	file = str_cat(section->tag, ".tmp");
	PushOutput(file);
	FreeMem(file);

	// title for this section
	OutputString("<center><b><big><big>");
	if( PrintableOmhelp() )
	{
		char *printid;
		printid = SectionNumber(section);
		assert( printid[0] != '\0' );
		FormatOutput("<a name=\"%s\">", printid);
		OutputString(printid);
		OutputString(": ");
		FreeMem(printid);
		OutputString(section->title);
		OutputString("</a>\n");
	}
	else	OutputString(section->title);
	OutputString("</big></big></b></center>\n");

	OutputString("<table>\n");
	OutputString("<tr valign=\"top\"><td>\n");

	OutputString("<b>Reference</b></td><td>\n");
	OutputString("<b>Location</b></td></tr>\n");

	track    = Root;
	while(track != NULL)
	{	OutputString("\n<tr valign=\"top\"><td>");
		HrefOutputPass1(track->UrlTo, track->HeadTo, "true", "");

		OutputString(track->UrlTo);
		if( track->HeadTo[0] != '\0' )
		{	OutputString("#");
			OutputString(track->HeadTo);
		}
		HrefEnd("");

		// separate columns of the table
		OutputString("</td><td>");

		frame = "";
		if( track->HeadFrom[0] != '\0' )
			frame = "1";

		HrefOutputPass1(track->TagFrom, track->HeadFrom, "false", frame);
		OutputString(track->TagFrom);
		if( track->HeadFrom[0] != '\0' )
		{	OutputString("#");
			OutputString(track->HeadFrom);
		}
		HrefEnd("");
		OutputString("</td></tr>\n");
	
		track    = track->next;
	}
	OutputString("</table>");

	
	PopOutput();
}

void HrefFreeMemory()
{	HrefInfo *track;

	track = Root;
	while(track != NULL )
	{	Root = track->next;
		FreeMem(track->TagFrom);
		FreeMem(track->HeadFrom);
		FreeMem(track->UrlTo);
		FreeMem(track->HeadTo);
		FreeMem(track);
		track     = Root;
	}
	return;
}

