/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
The documentation below is for these routines with respect to other files; i.e.,
it does not include communication through static variables in this file.
============================================================================
$begin PushOutput$$
$spell
	const
	Microsoft
$$

$index PushOutput$$
$index output file$$

$section Place a New File on Top of Output Stack$$

$table
$bold Syntax$$
$cnext $codei%void PushOutput(const char *%name%)%$$
$tend


$head Description$$
Opens the file corresponding to the
$cref/string/glossary/String/$$ $italic name$$
and places it on the top of the output stack.
Upper case letters in $italic name$$
are interpreted as lower case.
This is because Microsoft Windows is not really case
sensitive when it comes to distinguishing file names.

$head Current Output File$$
The file specified by $italic name$$ becomes
the current output file.
The $cref PopOutput$$ function removes the
current output file from the top of the stack
and makes the previous output file the current one.

$end
============================================================================
$begin FormatOutput$$
$spell
	const
	fmt
$$

$index FormatOutput$$
$index format output string$$

$section Write a String Plus Formating to Output File$$

$table
$bold Syntax$$
$cend $codei%void FormatOutput(const char *%fmt%, const char *%s1%)%$$
$rnext
$cend $codei%void FormatOutput2(const char *%fmt%, const char *%s1%, const char *%s2%)%$$
$tend

$head Description$$
Write the
$cref/string/glossary/String/$$
specified by $italic s1$$
(and $italic s2$$ if it is present)
using the format specified by $italic fmt$$.
The output is written to the
$cref/current output file/PushOutput/Current Output File/$$.
$syntax/

FormatOutput(/fmt/, /s1/)
/$$
there is must be only one formatting command in $italic fmt$$,
it must be a $code %s$$ command,
and it represents where $italic s1$$ goes in the output.
$syntax/

FormatOutput2(/fmt/, /s1/, /s2/)
/$$
there is must be two formatting command in $italic fmt$$,
they must be $code %s$$ commands,
the first represents where $italic s1$$ goes in the output,
the second represents where $italic s2$$ goes in the output.


$end
============================================================================
$begin OutputString$$
$spell
	const
$$

$index OutputString$$
$index output string$$

$section Write a String to Output File$$

$table
$bold Syntax$$
$cend $codei%void OutputString(const char *%s%)%$$
$tend

$head Description$$
Write the
$cref/string/glossary/String/$$
specified by $italic s$$ to the
$cref/current output file/PushOutput/Current Output File/$$.


$end
============================================================================
$begin OutputChar$$
$spell
	const
	ch
$$

$index OutputChar$$
$index output character$$

$section Write a Character to Output File$$

$table
$bold Syntax$$
$cend $codei%void OutputChar(const char %ch%)%$$
$tend

$head Description$$
Write the
character specified by $italic ch$$ to the
$cref/current output file/PushOutput/Current Output File/$$.


$end
============================================================================
$begin PopOutput$$

$index PopOutput$$
$index output file$$

$section Remove The File Currently on Top of Output Stack$$

$table
$bold Syntax$$
$cnext $codei%void PopOutput()%$$
$tend


$head Description$$
Closes the
$cref/current output file/PushOutput/Current Output File/$$
and removes it from the top of the output stack.
This makes the previous output file the current one.
If no file is currently on the output stack,
this call has no effect.

$end
============================================================================
$begin OutputName$$
$spell
	const
$$

$index OutputName$$
$index name, output file$$
$index output file, name$$

$section Returns the name of the Current Output File$$

$table
$bold Syntax$$
$cnext $codei%const char *OutputName()%$$
$tend


$head Description$$
Returns the name of the output file currently on top
of the stack as specified by previous calls to $cref PushOutput$$
and $cref PopOutput$$.
If no file is currently on the output stack,
the NULL pointer is returned.

$end
*/
# include <stdio.h>
# include <ctype.h>

# include "output.h"
# include "fatalerr.h"
# include "str_alloc.h"
# include "allocmem.h"


# define MAX_FILE   10


// output files
static FILE *Fp[MAX_FILE];
static char *Name[MAX_FILE];

// index of the current file
static int Index = -1;

void PushOutput(const char *name)
{	char *lower;
	int  i;

	Index++;
	if( Index >= MAX_FILE ) fatalerr(
		"To many output files at once",
		NULL
	);

	lower = str_alloc(name);
	for(i = 0; lower[i] != '\0'; i++)
		lower[i] = (char) tolower((int) lower[i]);

	Fp[Index]   = fopen(lower, "w");
	Name[Index] = lower;
	if( Fp[Index] == NULL ) fatalerr(
		"Cannot open the output file: ",
		lower,
		NULL
	);

	return;
}

void PopOutput(void)
{	if( Index >= 0 )
	{	fclose(Fp[Index]);
		FreeMem(Name[Index]);
		--Index;
	}
	return;
}

const char *OutputName(void)
{	if( Index >= 0 )
		return Name[Index];
	return NULL;
}

void FormatOutput(const char *fmt, const char *s)
{	if( Index >= 0 )
		fprintf(Fp[Index], fmt, s);
}

void FormatOutput2(const char *fmt, const char *s1, const char *s2)
{	if( Index >= 0 )
		fprintf(Fp[Index], fmt, s1, s2);
}

void OutputString(const char *s)
{	FormatOutput("%s", s);
}

void OutputChar(char ch)
{	if( Index >= 0 )
		putc(ch, Fp[Index]);
}
