# ifndef CROSS_INCLUDED
# define CROSS_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


/*
$begin CrossReference_dev$$
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
A variable or record field called $icode tag$$
refers to the cross reference tag for an particular section and
is a '\0' terminated character vector.
Two different values for $icode tag$$ are called equal
if they are equal without regard to case.
The value $icode tag$$ should never be empty nor
should it begin with white space;
i.e. $icode%tag%[0] != '\0'%$$ and
$codei%! isspace(%tag%[0])%$$.

$head File$$
$index file, cross reference$$
A variable or record field called $icode file$$,
is a '\0' terminated character vector.
Two different values for $icode file$$ are called equal
if they are equal without regard to case.
If $icode file$$ is not empty,
it corresponds to the input file where the cross reference was created.

$head Head$$
$index head, cross reference$$
A variable or record field called $icode head$$
is a $cref/cross reference heading/glossary_dev/Cross Reference Heading/$$.
Two different values for $icode head$$ are called equal
if they are equal in a case sensitive sense.

$head Printid$$
$index printid, cross reference$$
A variable or record field called $icode printid$$
is a '\0' terminated character vector.
It serves as a unique identifier for the cross reference
and represents its position in the document tree.
It may be empty,
in which case this cross reference is not identified in the printed version.


$head Frame$$
$index frame, cross reference$$
An integer variable or record field called $icode frame$$
specifies the destination frame
corresponding to a cross reference.
The value $math/frame = 0/$$
should be used for the overall section,
$math/frame = 1/$$ corresponds
to the first user defined frame, and so on.
If $cref/head/CrossReference_dev/Head/$$ is empty,
it must hold that $math/frame = 0/$$.

$head Defined$$
$index defined, cross reference$$
The record field called $icode defined$$ is
either zero or one.
If it is zero, the destination of the cross reference is not yet defined.
If it is one, the destination is defined.

$head Next Created$$
The record field called $icode next_created$$
points to the next cross reference in the list of existing
cross references.
(This is for use by cross.c only.)

$head Next Defined$$
The record field called $icode next_defined$$
points to the next cross reference int he list of
cross references that have been defined
(This is for use by cross.c only.)

$childtable%
	src/cross.c%$$

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

# ifdef __cplusplus
}
# endif
# endif
