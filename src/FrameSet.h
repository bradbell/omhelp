# ifndef FRAME_SET_INCLUDED
# define FRAME_SET_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


# include "section.h"

extern void OutputFrameSet(
	SectionInfo *F, const char *FrameOneExt, int link_frame);

# ifdef __cplusplus
}
# endif
# endif
