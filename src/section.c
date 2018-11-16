/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2018 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
=============================================================================
$begin SectionInfoNew$$
$escape #$$
$spell
	const
$$

$index SectionInfoNew$$
$mindex new section information record$$

$section Create a New Section Information Record$$

$head Syntax$$
$codei%SectionInfo *SectionInfoNew(
	const SectionInfo *navigateCopy,
	const char *%filename%
)%$$

$head See Also$$
$mref/SectionInfoNew/$$


$head Purpose$$
Uses $mref/AllocMem/$$ to allocate memory for a new
$mref/SectionInfo/$$ record.
All of the field values in the record
are initialized as $code NULL$$ with the following exceptions:

$subhead navigate$$
This field is not a pointer so it is not initialized as $code NULL$$.
If $icode navigateCopy$$ is equal to $code NULL$$,
$code navigate$$ is initialized using the default value for all its
sub-fields with the exception of $code navigate.tag$$ which is
initialized as $code NULL$$.
If $icode navigateCopy$$ is not equal to $code NULL$$,
$code navigate$$ is initialized to contain a deep copy of the
$code navigate$$ field in $icode navigateCopy$$.

$subhead style$$
This file is not a pointer, so it is not $code NULL$$
but all of the pointers it contains are initialized as $code NULL$$.

$subhead nFrame$$
This field is set equal to 1

$subhead Frame[0]$$
This field is set equal to 100 (its default value).

$subhead root and ext$$
If $icode filename$$ is not $code NULL$$, it is a $code '\0'$$
terminated character row vector
that specifies the name of the input file corresponding to the section.
In this case the $code SectionInfo$$
fields named $code root$$ and $code ext$$ are set to $code '\0'$$
terminated character row vectors.
To be specific, $code ext$$
contains the
$cref/extension/glossary/File Extension/$$ corresponding to $icode filename$$
and $code root$$
contains the other characters in $icode filename$$.
Both $code root$$ and $code ext$$ are allocated memory using
$mref/AllocMem/$$.
The
$mref/SectionFreeTree/$$ routine is designed to free this memory.

$end
=============================================================================
$begin SectionDefaultStyle$$

$mindex default style$$
$section Replace Undefined Style Values by Defaults$$

$head Syntax$$
$codei%void SectionDefaultStyle(
	SectionInfo *%To,
	SectionInfo *%From%
)%$$


$head Description$$
Suppose that $icode field$$ is such that
$icode/To/->style/./field/$$
is equal to $code NULL$$ and
$icode/From/->style/./field/$$
is not equal to $code NULL$$.
In this case,
$icode/To/->style/./field/$$
is set equal to
a separate copy of
$icode/From/->style/./field/$$


$end
=============================================================================

$begin SectionFreeTree$$
$escape #$$
$spell
	FreeMem
$$

$mindex free SectionInfo tree$$
$section Free All SectionInfo Records of Corresponding Section Tree$$

$head Syntax$$
$codei%void SectionFreeTree(
	SectionInfo *%tree%
)%$$

$head See Also$$
$mref/SectionInfoNew/$$



$head Description$$
Use $cref/FreeMem/AllocMem/FreeMem/$$ to free all of the
$mref/SectionInfo/$$ records in the specified
$cref/Section tree/glossary/Section Tree/$$.
The argument $icode tree$$ is a $code SectionInfo$$ pointer to
the root node of the tree.
In addition, all of the field with type $code char *$$
in the corresponding $code SectionInfo$$
records are also freed using $code FreeMem$$.


$head Restrictions$$
The $code previous$$ and $code parent$$ fields
must be equal to $code NULL$$; i.e.,
there cannot be any siblings before $icode tree$$
and $icode tree$$ cannot have a parent.

$end
=============================================================================
$begin SectionFind$$
$escape #$$
$spell
	const
$$


$mindex find SectionInfo record tag$$
$index search, Section Info record #by tag$$


$section Find the SectionInfo Record With a Specified Tag$$


$head Syntax$$
$codei%SectionInfo* SectionFind(
	SectionInfo *%tree%,
	const char *%tag%
)%$$

$head See Also$$
$mref/SectionInfo/$$


$head Description$$
Searches the specified
$cref/Section tree/glossary/Section Tree/$$
for the $mref/SectionInfo/$$ record that has the specified
value for its $code tag$$ field.
The argument
$icode tree$$ points to the
Section tree that is being searched.
The argument $icode tag$$ is a $code '\0'$$ terminated character vector.
The return value is a pointer to a $code SectionInfo$$ record
with corresponding $code tag$$ field equal to $icode tag$$.
If there is no such record in the tree, $code NULL$$ is returned.

$head Restrictions$$
The $code previous$$ and $code parent$$ fields
must be equal to $code NULL$$; i.e.,
there cannot be any siblings before $icode tree$$
and $icode tree$$ cannot have a parent.
$pre

$$
Every section must have its cross reference tag defined
before this routine is called.

$end
=============================================================================
$begin SectionSetTag$$
$escape #$$
$spell
	const
	Mem
$$

$mindex SectionInfo tag$$
$section Set a SectionInfo Record Tag Field$$

$head Syntax$$
$codei%void SectionSetTag(
	SectionInfo *%section%,
	const char *%tag%
)%$$

$head See Also$$
$mref/SectionInfo/$$


$head Description$$
Sets the $code tag$$ field of the specified $mref/SectionInfo/$$
record to point to a copy of the $code '\0'$$ terminated
character row vector $icode tag$$.
In addition, the $code tagLower$$ field
points to a copy of $icode tag$$ in which upper case characters
are changed to lower case.
The memory pointed to by $code tag$$ and $code tagLower$$
is allocated by $mref/AllocMem/$$
and must be freed using $cref/FreeMem/AllocMem/FreeMem/$$.

$head Restrictions$$
The value of the $code tag$$ and $code tagLower$$ fields
must be $code NULL$$ when this routine is called.


$end
=============================================================================

$begin SectionNumber$$
$spell
	Mem
$$

$section Numbers All Sections in Printable Order$$

$head Syntax$$
$codei%char *SectionNumber(
	SectionInfo *%section%
)%$$


$head Description$$
Returns an identifying $code number$$ corresponding to the specified section.
The return value is a $code '\0'$$ terminated
character row vector.
It is assumed that there is only one section at the top
of the tree. The identifying number corresponding to that section
is the empty string.
The memory pointed to by the return value
is allocated by $mref/AllocMem/$$
and must be freed using $cref/FreeMem/AllocMem/FreeMem/$$.

$head Assumptions$$
The numbering scheme identifies a section relative to the sections
that come before it in the tree; i.e., the number of previous siblings
and the number corresponding to its parent determine the section number.
Thus, if a section is inserted before section X,
the number corresponding to section X changes,
and hence the number corresponding to all the children of section X changes.

$end
=============================================================================
$begin SectionTagNotDefined$$
$escape #$$
$spell
	const
$$


$mindex SectionInfo tag$$

$section Search For a Section With Undefined Tag$$


$head Syntax$$
$codei%SectionInfo* SectionTagNotDefined(
	SectionInfo *%root%
)%$$

$head See Also$$
$mref/SectionFind/$$


$head Description$$
Searches the specified
$cref/Section tree/glossary/Section Tree/$$
starting at $icode root$$,
for a $mref/SectionInfo/$$ record that does not have its
$code tag$$ field defined.
The return value is a pointer to a $code SectionInfo$$ record
in which the $code tag$$ field is $code NULL$$.
$pre

$$
The siblings that come before $icode root$$,
and the parents of $icode root$$,
are not searched.
$pre

$$
If there is no such section,
the value $code NULL$$ is returned.

$end
=============================================================================
$begin SectionReadOrder$$
$escape #$$
$spell
	const
	next next
$$


$mindex SectionInfo read next$$

$section Return Next or Previous Section in Read Order$$


$head Syntax$$
$codei%SectionInfo* SectionReadNext( SectionInfo *%section%)
%$$
$codei%SectionInfo* SectionReadPrevious( SectionInfo *%section%)%$$


$head Description$$
Read order is described by the numbers
in the following example section tree:
$pre
	| 1 |

	  |
	  | children
	  v
	         next
	| 2 | ---------->  | 6 |

	  |                  |
	  | children         | children
	  v                  v
	      next               next
	| 3 | ---> | 4 |   | 7 | ---> | 8 |

	             |
	             | children
	             v

	           | 5 |
$$
If $icode section$$ is the first section in read order,
$code SectionReadPrevious$$ returns NULL.
If $icode section$$ is the last section in read order,
$code SectionReadNext$$ returns NULL.

$end
=============================================================================
$begin SectionNavigate$$
$spell
	const
	ntoken
	subfield
	Prev
	Down Down
$$

$section Changing Relative Navigation Links for a Section$$

$head Syntax$$
$codei%void SectionNavigate(
	SectionInfo *%S%      ,
	int          %ntoken% ,
	const char  *%text%   ,
	int          line     )
%$$


$head Purpose$$
This changes the navigation links for the section
$icode S$$ the one specified by $icode ntoken$$ and $icode text$$.

$head S$$
Pointer the section information record that is being changed.
The subfield $codei%S->navigate%$$ is changed,
and the rest of the section information is left as is.

$head ntoken$$
The argument $icode ntoken$$ must be an even number.
It specifies the number of tokens pointed to by $icode text$$
It must also be less than or equal 16 (there can be at most 8 token pairs)
(or else an error is posted).

$head text$$
The argument $icode text$$ is contains $icode ntoken$$
$code '\0'$$ terminated character strings called tokens.
The value $icode text$$ points to the beginning
of the first token.
The next token starts at the character directly following
the terminating $code '\0'$$ for the current token.
These tokens come in pairs of where
the first value in each pair is a navigation type and
the second is the label that the user sees for that navigation type.
Leading and trailing white space in each token is ignored.

$subhead Navigation Types$$
The valid navigation types values are
$codei%
	Across
	Down
	Down_up_%i%
	Current
	Content
	Next
	Prev
	Top
	Sibling
	Up
%$$
where $icode i$$ is a single decimal digit.

$subhead Labels$$
None of the labels can begin with the character $pre "_"$$ except
for the following special case:
$codei%_up_%i%$$.

$head line$$
If one of the requested navigation types is not valid, the invalid type
is reported as coming from a $code navigate$$ command on the specified line.

$end
*/

# include <ctype.h>
# include <string.h>
# include <stdio.h>

# include "allocmem.h"
# include "str_alloc.h"
# include "input.h"
# include <assert.h>
# include "StrLowAlloc.h"
# include "strjoin.h"
# include "ClipWhiteSpace.h"
# include "fatalerr.h"
# include "int2str.h"
# include "AutoTag.h"

# include "section.h"

# ifndef WIN32
# define stricmp strcasecmp
# endif


// Note that MAX_NAVIGATE is 19 so need 19 entries
static NavigateInfo NavigateType = {
	19,
	{
		{ ACROSS_nav,   "Across"       },
		{ CONTENT_nav,  "Content"      },
		{ CURRENT_nav,  "Current"      },
		{ DOWN_nav,      "Down"        },
		{ DOWN_UP_9_nav, "Down_up_9"   },
		{ DOWN_UP_8_nav, "Down_up_8"   },
		{ DOWN_UP_7_nav, "Down_up_7"   },
		{ DOWN_UP_6_nav, "Down_up_6"   },
		{ DOWN_UP_5_nav, "Down_up_5"   },
		{ DOWN_UP_4_nav, "Down_up_4"   },
		{ DOWN_UP_3_nav, "Down_up_3"   },
		{ DOWN_UP_2_nav, "Down_up_2"   },
		{ DOWN_UP_1_nav, "Down_up_1"   },
		{ DOWN_UP_0_nav, "Down_up_0"   },
		{ NEXT_nav,      "Next"        },
		{ PREV_nav,      "Prev"        },
		{ SIBLING_nav,   "Sibling"     },
		{ TOP_nav,       "Top"         },
		{ UP_nav,        "Up"          }
	}
};
static NavigateInfo Default = {
	10,
	{
		{ PREV_nav,      "Prev"      },
		{ NEXT_nav,      "Next"      },
		{ ACROSS_nav,    "Index"     },
		{ UP_nav,        "Up"        },
		{ DOWN_UP_4_nav, "_up_4"     },
		{ DOWN_UP_3_nav, "_up_3"     },
		{ DOWN_UP_2_nav, "_up_2"     },
		{ DOWN_UP_1_nav, "_up_1"     },
		{ DOWN_UP_0_nav, "_up_0"     },
		{ CURRENT_nav,   "Headings"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  },
		{ INVALID_nav,   "not used"  }
	}
};

// =========================================================================
SectionInfo *SectionInfoNew(
	const SectionInfo *navigateCopy,
	const char        *inputfile
)
{
	int         index;
	char       *root;
	char       *ext;
	SectionInfo *F;

	F    = AllocMem(1, sizeof(SectionInfo));

	root = NULL;
	ext  = NULL;

	if( inputfile != NULL )
		InputSplitName(&root, &ext, inputfile);

	F->nFrame   = 1;
	F->Frame[0] = 100;

	F->root     = root;
	F->ext      = ext;
	F->tag      = NULL;
	F->tagLower = NULL;
	F->title    = NULL;
	F->keywords = NULL;
	F->parent   = NULL;
	F->children = NULL;
	F->previous = NULL;
	F->next     = NULL;

	F->style.textcolor = NULL;
	F->style.bgcolor   = NULL;
	F->style.linkcolor = NULL;
	F->style.visitcolor= NULL;

	if( navigateCopy == NULL )
	{	F->navigate.number = Default.number;
		for(index = 0; index < F->navigate.number; index++)
		{	F->navigate.item[index].nav_type
				= Default.item[index].nav_type;
			F->navigate.item[index].label
				= str_alloc( Default.item[index].label );
		}
	}
	else
	{	F->navigate.number = navigateCopy->navigate.number;
		for(index = 0; index < F->navigate.number; index++)
		{	F->navigate.item[index].nav_type =
				navigateCopy->navigate.item[index].nav_type;
			F->navigate.item[index].label = str_alloc(
				navigateCopy->navigate.item[index].label
			);
		}
	}
	assert( F->navigate.number <= MAX_NAVIGATE );
	return F;
}

void SectionDefaultStyle(
	SectionInfo *To,
	SectionInfo *From
)
{
	if( To->style.textcolor == NULL &&  From->style.textcolor != NULL )
		To->style.textcolor = str_alloc(From->style.textcolor);

	if( To->style.bgcolor == NULL &&  From->style.bgcolor != NULL )
		To->style.bgcolor = str_alloc(From->style.bgcolor);


	if( To->style.linkcolor == NULL &&  From->style.linkcolor != NULL )
		To->style.linkcolor = str_alloc(From->style.linkcolor);

	if( To->style.visitcolor == NULL &&  From->style.visitcolor != NULL )
		To->style.visitcolor = str_alloc(From->style.visitcolor);

	return;
}

static void SectionFreeSubTree(SectionInfo *tree)
{	SectionInfo *next;
	int          index;

	// sequence through siblings
	while(tree != NULL)
	{	// free children of this sibling
		SectionFreeSubTree(tree->children);

		// remember next sibling
		next = tree->next;

		// free this sibling
		FreeMem(tree->root);
		FreeMem(tree->ext);
		FreeMem(tree->tag);
		FreeMem(tree->tagLower);
		FreeMem(tree->title);
		FreeMem(tree->keywords);

		FreeMem(tree->style.textcolor);
		FreeMem(tree->style.bgcolor);
		FreeMem(tree->style.linkcolor);
		FreeMem(tree->style.visitcolor);

		for(index = 0; index < tree->navigate.number; index++)
			FreeMem(tree->navigate.item[index].label);

		FreeMem(tree);

		// advance to next
		tree = next;
	}
	return;
}

void SectionFreeTree(SectionInfo *tree)
{
	assert(tree->parent == NULL);
	assert(tree->previous == NULL);

	SectionFreeSubTree(tree);
	return;
}


static SectionInfo *SectionFindSub(SectionInfo *tree, const char *tag)
{	SectionInfo *child;

	while(tree != NULL )
	{	assert( tree->tag != NULL );
		if( stricmp(tree->tag, tag) == 0 )
			return tree;
		child = SectionFindSub(tree->children, tag);
		if( child != NULL )
			return child;
		tree  = tree->next;
	}
	return NULL;
}

SectionInfo *SectionFind(SectionInfo *tree, const char *tag)
{
	assert(tree->parent == NULL);
	assert(tree->previous == NULL);

	return SectionFindSub(tree, tag);
}

void SectionSetTag(SectionInfo *section, const char *tag)
{
	assert(section->tag == NULL);
	assert(section->tagLower == NULL);

	section->tag          = str_alloc(tag);
	section->tagLower     = StrLowAlloc(tag);

	return;
}

char *SectionNumber(SectionInfo *section)
{	char *ret;
	char *tmp;
	char buf[20];
	int  count;

	assert( section != NULL );

	ret = str_alloc("");
	while( section->parent != NULL )
	{	count = 1;
		while( section->previous != NULL )
		{	++count;
			section = section->previous;
		}

		if( section->parent->parent == NULL )
			sprintf(buf, "%d", count);
		else	sprintf(buf, ".%d", count);
		tmp = strjoin(buf, ret);
		FreeMem(ret);
		ret = tmp;

		section = section->parent;
	}
	assert( section->next == NULL && section->previous == NULL );

	return ret;
}

SectionInfo *SectionTagNotDefined(SectionInfo *root)
{	SectionInfo *child;

	while(root != NULL )
	{
		if( root->tag == NULL )
			return root;

		child = SectionTagNotDefined(root->children);
		if( child != NULL )
			return child;

		root  = root->next;
	}
	return NULL;
}

SectionInfo *SectionReadPrevious(SectionInfo *section)
{	SectionInfo *R;

	//  previous sibling
	R = section->previous;

	if( R == NULL )
		R = section->parent;
	else
	{	while( R->children != NULL )
		{	// children are read after parents so change level
			R = R->children;

			// find last sibling at this level of the tree
			while( R->next != NULL )
				R = R->next;
		}
	}
	return R;
}

SectionInfo *SectionReadNext(SectionInfo *section)
{	SectionInfo *R;

	// first child of current section
	R = section->children;

	if( R == NULL )
	{	// next sibling of current section
		R = section->next;

		if( R == NULL )
		{	// closest parent of current seciton
			// that has a next sibling
			R = section->parent;
			while( R != NULL && R->next == NULL )
				R = R->parent;

			// next sibling of the parent
			if( R != NULL )
				R = R->next;
		}
	}
	return R;
}

const char *SectionNavigate(
	SectionInfo *S, int ntoken, const char *text, int line)
{	const char        *cptr;
	char              *tmp;
	int                number, len, index, i;
	enum navigateType nav_type;

	// free old section information
	for(index = 0; index < S->navigate.number; index++)
		FreeMem( S->navigate.item[index].label );

	if( ntoken > 2 * MAX_NAVIGATE ) fatalomh(
		"In the $navigate command in line ",
		int2str(line),
		"\nTo many delimiters in the delimiter sequence",
		NULL
	);
	if( (ntoken % 2) != 0 ) fatalomh(
		"In the $navigate command in line ",
		int2str(line),
		"\nCommand has an even number of delimiters ",
		"\n(odd number of arguments).",
		NULL
	);

	number = S->navigate.number = ntoken / 2;
	cptr   = text;
	for(index = 0; index < number; index++)
	{	// assume cptr not empty string
		len   = strlen(cptr);
		assert( len > 1 );

		// get and check navigation type
		nav_type = INVALID_nav;
		tmp      = str_alloc(cptr);
		ClipWhiteSpace(tmp);
		for(i = 0; i < NavigateType.number; i++)
		{
			if( strcmp(tmp, NavigateType.item[i].label) == 0 )
				nav_type = NavigateType.item[i].nav_type;
		}
		if( nav_type == INVALID_nav ) fatalomh(
			"In the $navigate command in line ",
			int2str(line),
			"\n\"", tmp, "\"",
			" is not a valid navigation type.",
			NULL
		);
		FreeMem(tmp);

		// store the navigation type
		S->navigate.item[index].nav_type = nav_type;

		// next token
		cptr += len + 1;
		len   = strlen(cptr);

		// store the label (freed later)
		tmp = str_alloc(cptr);
		ClipWhiteSpace(tmp);
		S->navigate.item[index].label = tmp;

		if( tmp[0] == '\0' ) fatalomh(
			"In the $navigate command in line ",
			int2str(line),
			".\nThere is only white space between two",
			"\nof the delimiters in this command.",
			NULL
		);
		if( strcmp(tmp, "_jump_table") != 0 && tmp[0] == '_' )
		if(
			strlen(tmp) != 5 ||
			strncmp(tmp, "_up_", 4) != 0 ||
			! isdigit((int) tmp[4] )
		) fatalomh(
			"In the $navigate command in line ",
			int2str(line),
			"\n\"The label \"", tmp, "\"",
			" begins with \"_\"\n",
			"and is not of form \"_up_i\" where i between 0 and 9",
			NULL
		);


		// next token
		cptr  += len + 1;
	}
	// Top section is a special case where we need to change
	// navigation for contents section (see InitParser)
	if( S->parent == NULL )
	{	SectionInfo *F = S->children;
		assert( strcmp(F->tag, CONTENTS_TAG) == 0 );

		// free old navigation information for table of contents
		for(index = 0; index < F->navigate.number; index++)
			FreeMem( F->navigate.item[index].label );

		// copy navigation information from top section
		F->navigate.number = S->navigate.number;
		for(index = 0; index < F->navigate.number; index++)
		{	F->navigate.item[index].nav_type =
				S->navigate.item[index].nav_type;
			F->navigate.item[index].label = str_alloc(
				S->navigate.item[index].label
			);
		}
	}
	return "";
}
