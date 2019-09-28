# ifndef CONVERT_INCLUDED
# define CONVERT_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
# ifdef __cplusplus
extern "C" {
# endif


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

# ifdef __cplusplus
}
# endif
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
$childtable%
	src/convert.c%$$


$end

*/
