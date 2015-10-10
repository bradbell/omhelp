# ifndef URL_INCLUDED
# define URL_INCLUDED
/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
=============================================================================
$begin Url$$
$spell
$$
$index Url, href$$
$index href, Url$$

$section Map Link Representation to a URL$$

$head Syntax$$
$cend $syntax%char *Url(
	const char *%tag% ,
	const char *%head%,
	const char *%head%
)%$$

$head Purpose$$
Maps the internal represent of a link to a web address
(relative to the directory where this web site is stored).

$head Convention$$
All the arguments arguments are all
$code '\0'$$ terminated character vectors.

$head tag$$
If $italic external$$ is equal to $code true$$,
$italic tag$$ is the web address corresponding this this link.
Otherwise,
$italic tag$$ is the cross reference tag for the section
corresponding to this link.

$head head$$
This argument specifies the heading
(with in the file) corresponding to the link.
If the link is to the entire section, head is equal to the empty string; i.e.
$syntax%
	%head%[0] == '\0'
%$$

$head external$$
This argument should be equal to $code true$$ or $code false$$.
See $itlaic tag$$ above for purpose of this argument.

$head Restrictions$$
This function should only be called during the second pass,
when all the cross references have been defined.
The argument $italic tag$$ must satisfy the following conditions:
$syntax%
	assert( %tag%[0] != '\0' );
	assert( ! isspace(%tag%[0]) );
%$$

$head Memory$$
The return value is allocated using $xref/AllocMem/$$
and should be freed using $code FreeMem$$

$end
------------------------------------------------------------------------------
*/

extern char *Url(const char *tag, const char *head, const char *external);

# endif
