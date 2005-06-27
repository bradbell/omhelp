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

# include "allocmem.h"
# include "str_cat.h"
# include "str_alloc.h"
# include "copyfile.h"
# include "InitParser.h"
# include "spell.h"
# include "Internal2Out.h"
# include "omhparse.h"
# include "input.h"
# include "StrLowAlloc.h"

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

# ifdef WIN32
# include <windows.h>
# endif

# define RUN_IN_DEBUGGER 0

// unsed by GNU allocate.c routine
const char *program_name = "omhelp";


int  DebugOmhelp         = 0;

static int GenerateXml   = 0;

static int printable  = 0;
int PrintableOmhelp()
{	return printable;
}

static int nowarn     = 0;
int PostWarnings()
{	return ! nowarn;
}

static const char *siteName = NULL;
const char *SiteName()
{	return siteName;
}

static const char *iconLink = NULL;
const char *IconLink()
{	return iconLink;
}

static char *iconFile = NULL;
const char *IconFile()
{	return iconFile;
}

static char *omhDir = NULL;
const char *OmhDir()
{	return omhDir;
}

extern void InitLex(void);

void done(int i)
{
	fprintf(stderr, "done(%d)\n", i);
	exit(i);
}

int main(int argc, const char *argv[])
{
	const char *omhdir   = NULL;
	const char *root     = NULL;
	const char *icon     = NULL;
	int error            = 0;
	int iarg             = 0;
	int morearg          = 0;
	char ch;

	// set default output file type
	Internal2OutSet("htm");

# if RUN_IN_DEBUGGER
	//
	root = "../omh/overview.omh";
	printf("root file = %s\n", root);
	omhdir = "../OMhelp";
	printf("omhelp_dir = %s\n", omhdir);
	//
	// iconLink = "index.htm";
	// printf("icon link = %s\n", iconLink);
	//
	// Internal2OutSet("xml");
	// GenerateXml = 1;
	//
	// printable = 1;
# else
	error = argc < 2;
	if( ! error )
	{	root = argv[1];
		iarg = 2;
	}
	while( iarg < argc && ! error )
	{	morearg = iarg + 1 < argc;
		if( morearg && strcmp(argv[iarg], "-g") == 0 )
		{	printf(
			"The -g option on the command line has been removed\n"
			"because the glossary is no longer a special section.\n"
			"To obtain the backward compatibility:\n"
			"\tPlace $aindex head$$ before the first $head in\n"
			"\tthe glossary file and specify the glossary file\n"
			"\tas the last child of the root section.\n"
			);
			exit(0);
		}
		else if( morearg && strcmp(argv[iarg], "-l") == 0 )
		{	iarg++;
			iconLink = argv[iarg];
			if( strchr(iconLink, '\\') != NULL )
			{
				printf("must use \"/\" in place of \"\\\" "
				       "in the link internet address\n"
				);
				exit(1);
			}
		}
		else if( morearg && strcmp(argv[iarg], "-i") == 0 )
		{	iarg++;
			icon = argv[iarg];
		}
		else if( morearg && strcmp(argv[iarg], "-site") == 0 )
		{	iarg++;
			siteName = argv[iarg];
		}
		else if( morearg && strcmp(argv[iarg], "-omhelp_dir") == 0 )
		{	iarg++;
			omhdir = argv[iarg];
		}
		else if( strcmp(argv[iarg], "-debug") == 0 )
			DebugOmhelp = 1;
		else if( strcmp(argv[iarg], "-printable") == 0 )
			printable = 1;
		else if( strcmp(argv[iarg], "-nowarn") == 0 )
			nowarn  = 1;
		else if( strcmp(argv[iarg], "-xml") == 0 )
		{	Internal2OutSet("xml");
			GenerateXml = 1;
		}
		else	error = 1;
		#
		iarg = iarg + 1;
	}
	error = error || iarg != argc;

	// version information
# if NDEBUG
	printf("OMhelp Release Version 05-06-25\n");
# else
	printf("OMhelp Debug Version 05-06-25\n");
# endif
	if( error )
	{	
		printf(
			"omhelp  root "
			"[-l link] "
			"[-i icon] "
			"[-site name] "
			"[-omhelp_dir dir] "
			"[-debug]  "
			"[-printable] "
			"[-xml] "
			"[-nowarn] "
			"\n"
		);
		printf("see the file Doc/running.htm or Doc/running.xml\n");
		exit(1);
	}
# endif
	if( omhdir == NULL )
		omhdir = getenv("omhelp_dir");

	if( omhdir == NULL )
# ifdef WIN32
	{
		// Look for omhelp_dir in windows system INI file
		const char *appName =  "OMhelp";
		const char *keyName =  "omhelp_dir";
		const char *Default =  ""; 
		char returnString[_MAX_PATH + 1]; 
		size_t nSize = _MAX_PATH;
		GetProfileString(
			appName,
			keyName,
			Default,
			returnString,
			nSize
		);
		if( returnString[0] != '\0' )
		{	char *stmp = str_cat("omhelp_dir=", returnString);
			putenv(stmp);
			FreeMem(stmp);
			omhdir = getenv("omhelp_dir");
		}
		else 
		{	size_t flag = GetWindowsDirectory(returnString, nSize);
			printf("omhelp_dir environment variable not set and\n");
			printf(" Cannot find: %s=value\n", keyName);
			printf("       Under: [%s]\n", appName);
			printf("     In file: win.ini\n");
			if( 0 < flag && flag <= nSize )
				printf("In directory: %s\n", returnString);
			printf(
				"Where value is replaced by the "
				"OMhelp install directory.");
			exit(1);
		}
	}
# else
	{	printf("The enviroment variable omhelp_dir is not set\n");
		exit(1);
	}
# endif
	ch = omhdir[strlen(omhdir) - 1];
	if( ch == '/' || ch == '\\' )
		omhDir = str_alloc(omhdir);
	else	omhDir = str_cat(omhdir, "\\");
	

	// must initialize parser before calling error routines
	// and copyfile may call error routines.
	// In addition, initializing parser initializes input routines.
	InitParser(root);

	// copy the icon file to the current directory
	if( iconLink != NULL )
	{	const char *dir;
		char *root;
		char *ext;
		char *fullname;

		if( icon == NULL )
		{	fullname = StrCat(
				__FILE__,
				__LINE__,
				omhDir,
				"icon.gif",
				NULL
			);
			iconFile = str_alloc("_icon.gif");
		}
		else
		{
			InputSplitName(&root, &ext, icon);
			if( ext[0] == '\0' ) printf(
				"The icon file name %s"
				"\ndoes not have an extension",
				icon
			);
			dir      = InputSearch(root, ext);
			fullname = StrCat(
				__FILE__,
				__LINE__,
				dir,
				root,
				ext,
				NULL
			);
			iconFile = str_cat("_icon", ext);

			FreeMem(root);
			FreeMem(ext);
		}
	
		// make a local copy of file
		copyfile(iconFile, fullname);

		FreeMem( fullname );
	}

	// copy the mathml style files to the current directory
	if( GenerateXml )
	{	char *fullname;

		/*
		pmathml.xsl
		*/
		fullname = StrCat(
			__FILE__,
			__LINE__,
			omhDir,
			"pmathml.xsl",
			NULL
		);
		copyfile("pmathml.xsl", fullname);
		FreeMem( fullname );

		/*
		pmathmlcss.xsl
		*/
		fullname = StrCat(
			__FILE__,
			__LINE__,
			omhDir,
			"pmathmlcss.xsl",
			NULL
		);
		copyfile("pmathmlcss.xsl", fullname);
		FreeMem( fullname );

	}

	InitSpelling(omhDir);

	omhparse();

	FreeMem(omhDir);
	FreeMem(iconFile);

	CheckMemoryLeak();

	return 0;
}
