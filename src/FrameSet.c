/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin FrameSet$$
$spell
	const
	Html
	noframe
	htm
$$

$section Output Frame Set for a Section$$

$head Syntax$$
$codei%void OutputFrameSet(SectionInfo *%
	F%, const char *%FrameOneExt%, int %link_frame%)%$$

$head Purpose$$
This routine outputs the frame set corresponding to the section
$icode F$$ (provided that the command line argument $code -noframe$$
is not present).

$head Output File$$
The frame set file for this section is named
$codei%
	%F->tagLower%.%FrameOneExt%
%$$

$head link_frame$$
If $icode link_frame$$ is true,
a file containing the relative links for this section is output with
the name
$codei%
	%F->tagLower%.%ext%
%$$
where $icode ext$$ is the return value from the function
$code Internal2Out("OutputExtension")$$.
This file is displayed in a tall frame to the left of the section information.
Otherwise, there is no link frame in this frame set.

$head User Frames$$
The other frames are displayed one above the other
(in order) to the right of the link frame.
For $icode j$$ equal one to $icode F-nFrame$$,
the file containing the $th j$$ frames information is assumed to be named
$codei%
	%F->tagLower%_frame%j%.%ext%
%$$
If $icode j$$ is one
$icode ext$$ is equal to $icode FrameOneExt$$.
Otherwise,
$icode ext$$ is the return value from the function
$code Internal2Out("OutputExtension")$$.
The $th j$$ frame is given the following HTML $code name$$ and $code id$$
values
$codei%
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

void OutputFrameSet(SectionInfo *F, const char *FrameOneExt, int link_frame)
{	const char *ext;
	char buffer[200];
	int iFrame;

	// name of the frameset file
	sprintf(buffer, "%s%s", F->tagLower, FrameOneExt);

	// start the frameset file
	PushOutput(buffer);
	OutputString(Internal2Out("StartOutputFile"));
	OutputString("\n");
	OutputHtmlHead(F);

	// frameset file has no <body> content

	// split into left and right frames
	if( link_frame )
	{	OutputString("<frameset cols=\"15%,*\">\n");

		// left frame is navation links
		ext = Internal2Out("OutputExtension");
		FormatOutput2( "<frame src=\"%s_links%s\"", F->tagLower, ext);
		OutputString(Internal2Out("SelfTerminateCmd"));
		OutputString("\n");
	}

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
	if( link_frame )
		OutputString("</frameset>\n");

	// terminate this output file
	OutputString("</html>\n");
	PopOutput();

	return;
}
