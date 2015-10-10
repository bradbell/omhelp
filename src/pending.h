# ifndef PENDING_INCLUDED
# define PENDING_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */

extern int  NumberPending(void);
extern void PushPending(int line, const char *name);
extern void PopPending(int line, const char *name);
extern void OmhPendingError(int line, const char *command);
extern void TexPendingError(const char *msg);

# endif

