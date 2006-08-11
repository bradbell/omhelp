/*
$begin navigate$$

$section Setting Navibation Names$$

$head Syntax$$
$syntax%void PushNavigatge(int %ntoken%, const char *%text%)
%$$
$syntax%void PopNavigate(void)
%$$
$syntax%int NavigateNpush(void)
%$$
$syntax%int NavigateNumber(void)
%$$
$syntax%enum NavigateStyle NavigateEntry(int index)
%$$


$head PushNavigate$$
This routine sets changes the current navigation sequence to the one
specified by $italic italic ntoken$$ and $italic text$$.
The argument $italic ntoken$$ must be an even number$$
The argument $italic text$$ is contains $italic ntoken$$
$code '\0'$$ terminated character strings called tokens.
The value $italic text$$ points to the beginning
of the first token.
The next token starts at the character directly following
the terminating $code '\0'$$ for the current token.
These tokens come in pairs of where the first value in
each pair is a style and the second is the label that the user
sees for that style.
The valid style values are
$pre
	$$
"Content",
"Prev",
"Next",
"Up",
"Sibling",
"Down",
"Across",
"Current".
$pre

$$
Leading and trailing white space in each token is ignored.
$pre

$$
At most two navigation sequences can be on the stack at one time.
The argument $italic ntoken$$ must be less than or equal 16
(there can be at most 8 token pairs).
$pre

$$
If one of the requested styles is not valid, the invalid style
is returned by $code PushNavigate$$.
Otherwise, $code PushNavigate$$ returns the empty string.
(If one of the requested styles is the empty string, a program
assert occurs.)

$head PopNavigate$$
This routine restores the navigation sequence to its
value before the previous call to $code PushNavigate$$.
$pre

$$
The routine $code PushNavigate$$ uses 
$xref/AllocMem/$$ to allocate memory for the name sets
and it is necessary to call $code PopNavigate$$ to free this memory.

$head NavigateNpush$$
This routine returns the number of navigation sequences
that are currently pushed onto the stack.

$head NavigateNumber$$
This routine returns the number of navigation entries 
in the current navigation sequence.

$head NavigateStyle$$
The argument $italic index$$ must be between zero
and the number of entries in the current navigation sequence.
This routine returns the navigation style 
for the entry with the specified index.

$head NavigateLabel$$
The argument $italic index$$ must be between zero
and the number of entries in the current navigation sequence.
This routine returns the navigation label 
for the entry with the specified index.

$end
*/

# define MaxNavigate 2

# include <string.h>
# include <assert.h>

# include "navigate.h"
# include "str_alloc.h"
# include "ClipWhiteSpace.h"
# include "allocmem.h"

typedef struct navigateItem {
	enum navigateStyle style;
	char *label;
} NavigateItem;

static int          Npush        = 0;
static int          Number[2];
static NavigateItem Buffer[8][2];

static NavigateItem Default[8] = {
	{ CONTENT_nav, "Content"   },
	{ PREV_nav,    "Prev"      },
	{ NEXT_nav,    "Next"      },
	{ UP_nav,      "Up->"      },
	{ SIBLING_nav, "Sibling->" },
	{ DOWN_nav,    "Down->"    },
	{ ACROSS_nav,  "Across->"  },
	{ CURRENT_nav, "Current->" }
};	


static enum navigateStyle Style(const char *name)
{	enum navigateStyle ret;
	int  i;
	char *tmp = str_alloc(name);
	ClipWhiteSpace(tmp);

	ret = INVALID_nav;
	for(i = 0; i < 8; i++) 
	{	if( strcmp(tmp, Default[i].label) == 0 )
			ret = Default[i].style;
	}
	FreeMem(tmp);
	return ret;
}



const char *PushNavigate(int ntoken, const char *text)
{	const char        *cptr;
	int                number, total, len, index;
	enum navigateStyle style;

	assert( Npush < 2 );
	assert( (ntoken % 2) == 0 );
	assert( ntoken <= 16 );
	
	number = ntoken / 2;
	cptr   = text;
	total  = 0;
	for(index = 0; index < number; index++)
	{	// assume cptr not empty string
		len   = strlen(cptr) + 1;
		assert( len > 1 );         

		// get and check navigation style
		style = Style(cptr);
		if( style == INVALID_nav )
			return cptr; 

		// store the style 
		Buffer[index][Npush].style = style;

		// next token
		cptr  += len;
		total += len;   

		// store the lable
		Buffer[index][Npush].label = str_alloc(cptr);
		ClipWhiteSpace(  Buffer[index][Npush].label );

	}
	// number of entries in this navigation sequence
	Number[Npush] = number;

	// number of sequences on the stack
	++Npush;
	return "";
}

void PopNavigate(void)
{	int index;
	 
	if( Npush > 0 );
	{	Npush--;
		for( index = 0; index < Number[Npush]; index++)
			FreeMem( Buffer[index][Npush].label );
	}
}

int NavigateNpush(void)
{	return Npush; }

int NavigateNumber(void)
{	if( Npush > 0 )
		return Number[Npush-1];
	else	return 8;
}

enum navigateStyle NavigateStyle(int index)
{	if( Npush == 0 )
	{	assert( index < 8 );
		return Default[index].style;
	}
	assert( index < Number[Npush-1] );
	return Buffer[index][Npush-1].style;
}

const char *NavigateLabel(int index)
{	if( Npush == 0 )
	{	assert( index < 8 );
		return Default[index].label;
	}
	assert( index < Number[Npush-1] );
	return Buffer[index][Npush-1].label;
}
