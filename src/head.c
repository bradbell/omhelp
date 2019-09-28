/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin heading_dev$$
$spell
	const
	initializes
	fatalomh
	OMhelp
$$

$section Routines That Manage Headings$$

$index heading$$
$index InitializeHeading$$
$index SetHeading$$
$index SetSubHeading$$
$index HeadingAndSubHeading$$
$index HeadingAndSubPrintId$$

$head Syntax$$
$codei%InitializeHeading()%$$
$codei%SetHeading(%heading%)%$$
$codei%SetSubHeading(%subheading%)%$$
$codei%HeadingAndSubHeading()%$$
$codei%HeadingAndSubPrintId()%$$


$head Description$$
These routines manage headings and subheadings.
$codei%

InitializeHeading()%
%$$
This initializes the set of headings a empty and should be
done at the beginning of each section.
This also has the effect of freeing all locally allocated
memory that is used by the other routines documented below.
Hence it should be called after those routines
and before checking for memory leaks.
$codei%

SetHeading(%heading%)%
%$$
This sets the current heading value.
$codei%

SetSubHeading(%subheading%)%
%$$
This sets the current subheading value.
It is assumed that the current heading is not empty
when this routine is called; i.e.,
there is a call to $code SetHeading$$ after the
previous $code InitializeHeading$$ and before this $code SetSubHeading$$.
$pre

$$
If $code SetSubHeading$$ is called when the current heading is empty,
a fatal error message is generated telling the user that
within each section, a $code subhead$$
command must be preceded by a  $code head$$ commands.
$codei%

HeadingAndSubHeading()%
%$$
Returns a '\0' terminated character vector containing the current
heading followed by the current subheading with a single
period ($code .$$) added between the two.
If the current subheading is empty,
only the current heading is returned and with no extra period.
If the current heading is empty,
the empty string is returned; i.e., the first element of
$code HeadingAndSubHeading$$ is '\0'.
The return value is a $code const char*$$ and hence the memory
it points to cannot be modified by the calling routine.
$codei%

HeadingAndSubPrintId()%
%$$
Returns a '\0' terminated character vector containing
counter that identifies the current heading and subheading values.
The counter is a sequences of letters that in alphabetic order
identify the position of the header withing the current section.
This specification is in terms of
how many calls to $code SetHeading$$ there were since the
previous $code InitializeHeading$$ and how many calls
how many calls to $code SetSubHeading$$ there were since the
previous $code SetHeading$$.
The return value is a $code const char*$$ and hence the memory
it points to cannot be modified by the calling routine.
If there is no current heading, the first element of the
return value is '\0', otherwise it is '\.'; i.e. the period character.


$head Errors$$
All the routines documented above use
$cref/fatalomh/fatalerr_dev/$$ to report error messages; i.e.,
they assume that there is an open input file and
that we are currently parsing OMhelp input.
$end
------------------------------------------------------------------------
*/

# include "str_alloc.h"
# include "allocmem.h"
# include "fatalerr.h"

# include <assert.h>
# include <stddef.h>


static char  *Heading          = NULL;
static char  *HeadingAndSub    = NULL;
static size_t HeadingNumber    = 0;
static size_t SubHeadingNumber = 0;

static char  Printid[20];

static size_t Number2String(char *id, size_t number)
{	size_t i, j, k;
	char buffer[9];

	k = 0;
	i = number;
	while(i)
	{	j = (i - 1) % 26;

		assert( k < 8 && 0 <= j && j < 26 );
		buffer[k++] = 'a' + j;

		i = (i - 1) / 26;
	}
	for(i = 0; i < k; i++)
		id[i] = buffer[k - i - 1];

	buffer[k] = '\0';

	return k;
}
static void SetPrintid()
{	size_t i = 0;

	if( HeadingNumber != 0 )
	{	Printid[i++] = '.';
		i += Number2String(Printid + i, HeadingNumber);

		if( SubHeadingNumber != 0 )
		{	Printid[i++] = '.';
			i += Number2String(Printid + i, SubHeadingNumber);
		}
	}
	Printid[i++] = '\0';

	return;
}


void InitializeHeading()
{	FreeMem(Heading);
	FreeMem(HeadingAndSub);

	Heading          = NULL;
	HeadingAndSub    = NULL;

	HeadingNumber    = 0;
	SubHeadingNumber = 0;

	SetPrintid();
}
void SetHeading(const char* heading)
{	FreeMem(Heading);
	FreeMem(HeadingAndSub);

	Heading       = str_alloc(heading);
	HeadingAndSub = str_alloc(heading);

	HeadingNumber++;
	SubHeadingNumber = 0;

	SetPrintid();
}
void SetSubHeading(const char* subheading)
{
	if( HeadingNumber == 0 ) fatalomh(
		"With in each section, a $subhead command\n",
		"must be preceded by a head command.",
		NULL
	);

	FreeMem(HeadingAndSub);
	HeadingAndSub = StrCat(
		__FILE__,
		__LINE__,
		Heading,
		".",
		subheading,
		NULL
	);
	SubHeadingNumber++;

	SetPrintid();
}
const char *HeadingAndSubHeading()
{	if( HeadingAndSub == NULL )
		HeadingAndSub = str_alloc("");

	return HeadingAndSub;
}
const char *HeadingAndSubPrintId()
{	return Printid;
}
