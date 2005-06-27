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
=============================================================================
$begin SectionInfoNew$$
$escape #$$
$spell
	const
$$

$index SectionInfoNew$$
$mindex new section information record$$

$section Create a New Section Information Record$$

$table
$bold Syntax$$
$cend $syntax%SectionInfo *SectionInfoNew(
	const char *%filename%
)%$$ $rend
$bold See Also$$
$cend $mref/SectionInfoNew/$$
$tend

$fend 25$$

$head Description$$
Uses $mref/AllocMem/$$ to allocate memory for a new 
$mref/SectionInfo/$$ record.
All of the field values in the record 
are initialized as $code NULL$$ with the following exceptions:

$subhead style$$
This file is not a pointer, so it is not $code NULL$$
but all of the pointers it contains are initialized as $code NULL$$.

$subhead nFrame$$
This field is set equal to 1

$subhead Frame[0]$$
This field is set equal to 100 (its default value).

$subhead root and ext$$
If $italic filename$$ is not $code NULL$$, it is a $code '\0'$$
terminated character row vector 
that specifies the name of the input file corresponding to the section.
In this case the $code SectionInfo$$
fields named $code root$$ and $code ext$$ are set to $code '\0'$$
terminated character row vectors. 
To be specific, $code ext$$
contains the
$xref/glossary/File Extension/extension/$$ corresponding to $italic filename$$
and $code root$$
contains the other characters in $italic filename$$.
Both $code root$$ and $code ext$$ are allocated memory using 
$mref/AllocMem/$$. 
The 
$mref/SectionFreeTree/$$ routine is designed to free this memory.

$end
=============================================================================
$begin SectionDefaultStyle$$

$mindex default style$$
$section Replace Undefined Style Values by Defaults$$

$table
$bold Syntax$$
$cend $syntax%void SectionDefaultStyle(
	SectionInfo *%To,
	SectionInfo *%From%
)%$$ $rend
$tend

$fend 25$$

$head Description$$
Suppose that $italic field$$ is such that
$syntax//To/->style/./field/$$
is equal to $code NULL$$ and
$syntax//From/->style/./field/$$
is not equal to $code NULL$$.
In this case,
$syntax//To/->style/./field/$$
is set equal to 
a separate copy of 
$syntax//From/->style/./field/$$
 

$end
=============================================================================

$begin SectionFreeTree$$
$escape #$$
$spell
	FreeMem
$$

$mindex free SectionInfo tree$$
$section Free All SectionInfo Records of Corresponding Section Tree$$ 

$table
$bold Syntax$$
$cend $syntax%void SectionFreeTree(
	SectionInfo *%tree%
)%$$ $rend
$bold See Also$$
$cend $mref/SectionInfoNew/$$
$tend

$fend 25$$


$head Description$$
Use $xref/AllocMem/FreeMem/FreeMem/$$ to free all of the 
$mref/SectionInfo/$$ records in the specified 
$xref/glossary/Section Tree/Section tree/$$.
The argument $italic tree$$ is a $code SectionInfo$$ pointer to 
the root node of the tree. 
In addition, all of the field with type $code char *$$
in the corresponding $code SectionInfo$$
records are also freed using $code FreeMem$$.


$head Restrictions$$
The $code previous$$ and $code parent$$ fields
must be equal to $code NULL$$; i.e.,
there cannot be any siblings before $italic tree$$
and $italic tree$$ cannot have a parent.

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


$table
$bold Syntax$$
$cend $syntax%SectionInfo* SectionFind(
	SectionInfo *%tree%,
	const char *%tag%
)%$$ $rend
$bold See Also$$
$cend $mref/SectionInfo/$$
$tend

$fend 25$$

$head Description$$
Searches the specified 
$xref/glossary/Section Tree/Section tree/$$
for the $mref/SectionInfo/$$ record that has the specified 
value for its $code tag$$ field.
The argument 
$italic tree$$ points to the
Section tree that is being searched.
The argument $italic tag$$ is a $code '\0'$$ terminated character vector.
The return value is a pointer to a $code SectionInfo$$ record
with corresponding $code tag$$ field equal to $italic tag$$. 
If there is no such record in the tree, $code NULL$$ is returned.

$head Restrictions$$
The $code previous$$ and $code parent$$ fields
must be equal to $code NULL$$; i.e.,
there cannot be any siblings before $italic tree$$
and $italic tree$$ cannot have a parent.
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

$table
$bold Syntax$$
$cend $syntax%void SectionSetTag(
	SectionInfo *%section%,
	const char *%tag%
)%$$ $rend
$bold See Also$$
$cend $mref/SectionInfo/$$
$tend

$fend 25$$

$head Description$$
Sets the $code tag$$ field of the specified $mref/SectionInfo/$$
record to point to a copy of the $code '\0'$$ terminated
character row vector $italic tag$$.
In addition, the $code tagLower$$ field 
points to a copy of $italic tag$$ in which upper case characters
are changed to lower case.
The memory pointed to by $code tag$$ and $code tagLower$$
is allocated by $mref/AllocMem/$$
and must be freed using $xref/AllocMem/FreeMem/FreeMem/$$.

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

$table
$bold Syntax$$
$cend $syntax%char *SectionNumber(
	SectionInfo *%section%
)%$$
$tend

$fend 20$$

$head Description$$
Returns an identifying $code number$$ corresponding to the specified section.
The return value is a $code '\0'$$ terminated
character row vector.
It is assumed that there is only one section at the top 
of the tree. The identifying number corresponding to that section
is the empty string.
The memory pointed to by the return value
is allocated by $mref/AllocMem/$$
and must be freed using $xref/AllocMem/FreeMem/FreeMem/$$.

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


$table
$bold Syntax$$
$cend $syntax%SectionInfo* SectionTagNotDefined(
	SectionInfo *%root%
)%$$ $rend
$bold See Also$$
$cend $mref/SectionFind/$$
$tend

$fend 25$$

$head Description$$
Searches the specified 
$xref/glossary/Section Tree/Section tree/$$
starting at $italic root$$,
for a $mref/SectionInfo/$$ record that does not have its 
$code tag$$ field defined.
The return value is a pointer to a $code SectionInfo$$ record
in which the $code tag$$ field is $code NULL$$.
$pre

$$
The siblings that come before $italic root$$,
and the parents of $italic root$$,
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


$table
$bold Syntax$$
$cend $syntax%SectionInfo* SectionReadNext( SectionInfo *%section%)%$$ 
$rend
$cend $syntax%SectionInfo* SectionReadPrevious( SectionInfo *%section%)%$$ 
$tend

$fend 25$$

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
If $italic section$$ is the first section in read order,
$code SectionReadPrevious$$ returns NULL.
If $italic section$$ is the last section in read order,
$code SectionReadNext$$ returns NULL.

$end
=============================================================================





*/

# include <ctype.h>
# include <string.h>
# include <stdio.h>

# include "allocmem.h"
# include "str_alloc.h"
# include "input.h"
# include <assert.h>
# include "StrLowAlloc.h"
# include "str_cat.h"

# include "section.h"

# ifndef WIN32
# define stricmp strcasecmp 
# endif


// =========================================================================
SectionInfo *SectionInfoNew(
	const char *inputfile
)
{
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

	return;
}

static void SectionFreeSubTree(SectionInfo *tree)
{	SectionInfo *next;

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

	section->tag      = str_alloc(tag);
	section->tagLower = StrLowAlloc(tag); 

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
		tmp = str_cat(buf, ret);
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
