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
$begin FrameSet$$
$spell
	Html
	noframe
	htm
$$

$section Output Frame Set for a Section$$

$head Syntax$$
$syntax%void OutputFrameSet(SectionInfo *%F%, const char *%FrameOneExt%)%$$

$head Purpose$$
This routine outputs the frame set corresponding to the section
$italic F$$ (provided that the command line argument $code -noframe$$
is not present).

$head Output File$$
The frame set file for this section is named
$syntax%
	%F->tagLower%.%ext%
%$$
where $italic ext$$ is the return value from the function
$code Internal2Out("OutputExtension")$$.

$head Link Frame$$
The file containing the relative links for this section is assumed to be named 
$syntax%
	%F->tagLower%.%ext%
%$$
where $italic ext$$ is the return value from the function
$code Internal2Out("OutputExtension")$$.
This file is displayed in a tall frame to the left of the section information.

$head User Frames$$
The other frames are displayed one above the other 
(in order) to the right of the link frame.
For $italic j$$ equal one to $italic F->nFrame$$,
the file containing the $th j$$ frames information is assumed to be named
$syntax%
	%F->tagLower%_frame%j%.%ext%
%$$
If $italic j$$ is one 
$italic ext$$ is equal to $italic FrameOneExt$$.
Otherwise, 
$italic ext$$ is the return value from the function
$code Internal2Out("OutputExtension")$$.
The $th j$$ frame is given the following HTML $code name$$ and $code id$$
values
$syntax%
	name="frame%j%" id="frame%j%"
%$$

$end
---------------------------------------------------------------------------
*/

# include <stdio.h>

# include "section.h"
# include "Internal2Out.h"
# include "output.h"
# include "HtmlHead.h"

void OutputFrameSet(SectionInfo *F, const char *FrameOneExt)
{	const char *ext;
	char buffer[200]; 
	int iFrame;

	// get the output extension
	ext = Internal2Out("OutputExtension");

	// name of the frameset file
	sprintf(buffer, "%s%s", F->tagLower, ext);

	// start the frameset file
	PushOutput(buffer);
	OutputString(Internal2Out("StartOutputFile"));
	OutputString("\n");
	OutputHtmlHead(F);

	// frameset file has no <body> content

	// split into left and right frames
	OutputString("<frameset cols=\"15%,*\">\n");
	
	// left frame is navation links
	FormatOutput2( "<frame src=\"%s_links%s\"", F->tagLower, ext);
	OutputString(Internal2Out("SelfTerminateCmd"));
	OutputString("\n");
	
	// users set of frames
	OutputString("<frameset rows=\"");
	for(iFrame = 1; iFrame <= F->nFrame; iFrame++)
	{	sprintf(buffer, "%d", F->Frame[iFrame - 1]);
		OutputString(buffer);
		if( F->nFrame == 1 )
			OutputString("%,*\">\n");
		else if( iFrame != F->nFrame )
			OutputString("%,");
		else	OutputString("%\">\n");
	}
	for(iFrame = 1; iFrame <= F->nFrame; iFrame++)
	{	if( iFrame == 1 )
			ext = FrameOneExt;
		else	ext = Internal2Out("OutputExtension");


		OutputString("<frame src=");
		sprintf(buffer, 
			"\"%s_frame%d%s\"", 
			F->tagLower, 
			iFrame,
			ext
		);
		OutputString(buffer);
		OutputString(" name=");
		sprintf(buffer, 
			"\"frame%d\"", 
			iFrame
		);
		OutputString(buffer);
		OutputString(" id=");
		sprintf(buffer, 
			"\"frame%d\"", 
			iFrame
		);
		OutputString(buffer);
		sprintf(buffer, 
			"%s\n", 
			Internal2Out("SelfTerminateCmd")
		);
		OutputString(buffer);
	}
	// end user frameset
	OutputString("</frameset>\n");

	// end left / right
	OutputString("</frameset>\n");
	
	// terminate this output file
	OutputString("</html>\n");
	PopOutput();

	return;
}
