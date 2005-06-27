# ifndef CONVERT_INCLUDED
# define CONVERT_INCLUDED

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

// special character that is converted to a resistered trade mark symbol
# define REGISTERED_TRADE_MARK_CHARACTER '\01'
# define COPYRIGHT_CHARACTER             '\02'

extern int ConvertPreviousNewline();
extern void ConvertAddPrevious(
	int n
);
extern void ConvertForcedNewline( 
	const int n
);
extern void ConvertOutputCh(
	const char ch, 
	const int pre
);
extern void ConvertOutputString( 
	const char *s, 
	const int pre
);
extern int ConvertAddColumn(
	const int add
);
extern void ConvertSetTabSize(
	const int size
);
extern char *ConvertInternalString(
	const char *s
);

# endif

/*

$begin convert$$
$escape #$$
$spell 
	const
	int 
	ch 
$$

$section Convert Special Characters On Output$$

$head Description$$
The functions listed below output text in HTML format.
In addition, they convert characters that require a special 
representation in that format.
(The function $code ConvertInternalString$$ just converts
special characters with out output.)

$head Convert Routines$$
$childtable/
	convert.c/$$


$end

*/
