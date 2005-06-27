# ifndef CROSS_INCLUDED
# define CROSS_INCLUDED

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

/*
$begin CrossReference$$
$spell
	isspace
	printid
$$

$section Cross References$$
$index cross reference$$

$head Description$$
The following variable name convention 
is used for the cross reference routines:

$head Tag$$
$index tag, cross reference$$
A variable or record field called $italic tag$$
refers to the cross reference tag for an particular section and
is a '\0' terminated character vector.
Two different values for $italic tag$$ are called equal
if they are equal without regard to case. 
The value $italic tag$$ should never be empty nor 
should it begin with white space; 
i.e. $syntax%%tag%[0] != '\0'%$$ and 
$syntax%! isspace(%tag%[0])%$$. 

$head File$$
$index file, cross reference$$
A variable or record field called $italic file$$,
is a '\0' terminated character vector.
Two different values for $italic file$$ are called equal
if they are equal without regard to case. 
If $italic file$$ is not empty, 
it corresponds to the input file where the cross reference was created.

$head Head$$
$index head, cross reference$$
A variable or record field called $italic head$$ 
is a $xref/glossary/Cross Reference Heading/cross reference heading/$$.
Two different values for $italic head$$ are called equal
if they are equal in a case sensitive sense. 

$head Printid$$
$index printid, cross reference$$
A variable or record field called $italic printid$$
is a '\0' terminated character vector.
It serves as a unique identifier for the cross reference
and represents its position in the document tree.
It may be empty,
in which case this cross reference is not identified in the printed version.


$head Frame$$
$index frame, cross reference$$
An integer variable or record field called $italic frame$$ 
specifies the destination frame
corresponding to a cross reference.
The value $math/frame = 0/$$ 
should be used for the overall section, 
$math/frame = 1/$$ corresponds
to the first user defined frame, and so on. 
If $xref/CrossReference/Head/head/$$ is empty, 
it must hold that $math/frame = 0/$$.

$head Defined$$
$index defined, cross reference$$
The record field called $italic defined$$ is 
either zero or one.
If it is zero, the destination of the cross reference is not yet defined.
If it is one, the destination is defined.

$head Next Created$$
The record field called $italic next_created$$
points to the next cross reference in the list of existing
cross references.
(This is for use by cross.c only.)

$head Next Defined$$
The record field called $italic next_defined$$ 
points to the next cross reference int he list of
cross references that have been defined
(This is for use by cross.c only.)

$childtable/
	cross.c/$$

$end
==============================================================================
*/

typedef struct crossReference {
	int                   defined;
	int                   line;
	int                   frame;
	char                 *file;
	char                  *tag;
	char                  *head;
	char                  *printid;
	struct crossReference *next_created;
	struct crossReference *next_defined;
} CrossReference;

extern CrossReference *CreateCrossReference(
	const char *tag, 
	const char *head,
	const char *file
);
extern CrossReference *FindCrossReference(
	const char *tag, 
	const char *head
);

extern CrossReference *NextCrossReference(
	const CrossReference* cross
);

extern CrossReference *DefineCrossReference(
	const char *tag, 
	const char *head,
	const char *file,
	const int  frame,
	const char *printid
);
extern void FreeCrossReference(void);

# endif
