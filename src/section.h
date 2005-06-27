# ifndef OMHELP_SECTION_INCLUDED
# define OMHELP_SECTION_INCLUDED

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

// maximum number of frames in one section
# define MAX_FRAME  10

typedef struct styleInfo {
	char *textcolor;
	char *bgcolor;
} StyleInfo;

// list of input files
typedef struct sectionInfo {
	// corresponding input file name
	char      *root;                // file name without extension
	char      *ext;                 // "" or file extension including '.'

	// information about this section 
	StyleInfo style;                // style for presenting this section
	char      *tag;                 // cross reference tag 
	char      *tagLower;            // lower case version of tag
	char      *title;               // title
	char      *keywords;            // keywords 
	int       nFrame;               // number of frames 
	int       Frame[MAX_FRAME];     // size of each frame

	

	// position of section in contents tree
	struct sectionInfo   *parent;    // section above 
	struct sectionInfo   *children;  // first section below
	struct sectionInfo   *previous;  // previous section
	struct sectionInfo   *next;      // next section

} SectionInfo;
extern SectionInfo *SectionFind(SectionInfo *tree, const char *tag);
extern SectionInfo *SectionInfoNew(const char *inputfile);
extern void         SectionDefaultStyle(SectionInfo *To, SectionInfo *From);
extern void         SectionFreeTree(SectionInfo *tree);
extern void         SectionSetTag(SectionInfo *section, const char *tag);
extern char        *SectionNumber(SectionInfo *section);
extern SectionInfo *SectionTagNotDefined(SectionInfo *root);
extern SectionInfo *SectionReadNext(SectionInfo *section);
extern SectionInfo *SectionReadPrevious(SectionInfo *section);

/*
$begin SectionInfo$$
$escape #$$
$spell
	OMhelp
	bgcolor
	textcolor
$$

$section Section Information Routines$$ 

$head Description$$
Each OMhelp section has a corresponding $code SectionInfo$$ record
with the following information:
$table
$bold Name$$ 
$cend $bold Type$$ 
$cend $bold Description$$ 
$rend
$code root$$ 
$cend $code char*$$  
$cend input file name without extension 
$rend
$code ext$$  
$cend $code char*$$  
$cend input file name extension 
$rend
$code style.textcolor$$
$cend $code char*$$  
$cend the color for normal text in this section
$rend
$code style.bgcolor$$
$cend $code char*$$  
$cend the background color for this section
$rend
$code tag$$  
$cend $code char*$$  
$cend cross reference tag for this section 
$rend
$code tagLower$$ 
$cend $code char*$$  
$cend lower case version of $code tag$$
$rend
$code title$$    
$cend $code char*$$
$cend title for this section 
$rend
$code keywords$$    
$cend $code char*$$
$cend keywords for this section 
$rend
$code nFrame$$      
$cend $code int$$
$cend number of frames in this section
$rend
$code Frame$$       
$cend $code int[MAX_FRAME]$$
$cend percent of total window corresponding to each frame
$rend
$code parent$$
$cend $code SectionInfo*$$
$cend information record for this section's parent section
$rend
$code children$$
$cend $code SectionInfo*$$
$cend information record for this section's first child
$rend
$code next$$
$cend $code SectionInfo*$$
$cend information record for this section's next sibling 
$rend
$code previous$$
$cend $code SectionInfo*$$
$cend information record for this section's previous sibling 
$tend

$comment
Only the section.c file can be included here because the routines in that file
refer back to here to list all the routines in that file.
$$
$childtable/
	section.c/$$

$end
*/

# endif
