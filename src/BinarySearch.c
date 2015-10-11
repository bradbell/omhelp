/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2015 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin BinarySearch$$
$spell
	len
	const
	strcmp
$$

$section Binary Search An Array of Names$$

$head Syntax$$
$codei/BinarySearch(/array/, /len/, /name/)/$$


$head Description$$
The argument $icode array$$ is an array of $icode len$$
and has prototype
$codei%
	const char *%array%[]
%$$
Each element $icode%array%[%i%]%$$
is a '\0' terminated character vector.
The argument $icode array$$ is sorted in $code strcmp$$ order; i.e.,
if $icode i$$ is less than $icode j$$,
$codei%
	strcmp(%array%[%i%], %array%[%j%])
%$$
is less than zero.
The return value is a $code int$$
index $icode i$$ such that
$codei%
	strcmp(%array%[%i%], %name%)
%$$
is equal to zero.
If no such index exists, the value $icode len$$ is returned.
(Note that the valid indices for $icode array$$ are
$math%i=0, ... , len-1%$$.)
$end
*/

# include "BinarySearch.h"
# include <stdio.h>
# include <string.h>
# include <assert.h>


int BinarySearch(const char *array[], int len, const char *name)
{	int i, di;
	int j, dj;
	int k, dk;

	if( len <= 0 )
		return len;

	// lower index
	i  = 0;
	di = strcmp(name, array[i]);
	if( di == 0 )
		return i;

	if( di < 0 )
		return len;

	// upper index
	k  = len - 1;
	dk = strcmp(name, array[k]);
	if( dk == 0 )
		return k;

	if( dk > 0 )
		return len;

	// middle index
	j  = (i + k) / 2;
	dj = strcmp(name, array[j]);
	if( dj == 0 )
		return j;


	while( i < k )
	{	assert( di > 0 );
		assert( dk < 0 );

		if( i + 1 == k)
			return len;

		if( dj > 0 )
		{	i  = j;
			di = dj;
		}
		else
		{	k  = j;
			dk = dj;
		}

		j  = (i + k) / 2;
		dj = strcmp(name, array[j]);
		if( dj == 0 )
			return j;
	}
	assert(0);
	return len;
}
