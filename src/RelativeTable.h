void RelativeTable(SectionInfo *F)
{
	SectionInfo *S;
	char        *name;
	char        *url;
	FILE        *javascript_fp;
	const char  *icon_link = IconLink();
	const char  *icon_file = IconFile();
	const char  *script;
	int          i;

	// Open the Javascript file for these drop down links.
	name = StrCat(
		__FILE__,
		__LINE__,
		F->tagLower,
		".js",
		NULL
	);
	javascript_fp = fopen(name, "w");
	if( javascript_fp == NULL ) fatalerr(
		"Can not create the output file ",
		name,
		NULL
	);
	FreeMem(name);

	// -----------------------------------------------------------------
	// Begin table that contains the links in a single row
	OutputString("<table><tr>\n");

	// Icon --------------------------------------------------------- 
	if( icon_link != NULL )
	{	OutputString("<td>\n");
		if( icon_link[0] != '\0' )
		{	FormatOutput(
				"<a href=\"%s\" target=\"_top\">", icon_link
			);
			FormatOutput(
				"<img border=\"0\" src=\"%s\"", icon_file
			);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("</a>\n");
		}
		else
		{	FormatOutput(
				"<img border=\"0\" src=\"%s\"", icon_file
			);
			OutputString(Internal2Out("SelfTerminateCmd"));
			OutputString("\n");
		}
		OutputString("</td>\n");
	}

	// Previous and Next ---------------------------------------------
	OutputString("<td>\n");
	OutputString("<table><tr><td>\n");
	S = SectionReadPrevious(F);
	if( S == NULL )
		OutputString("prev");
	else
	{	HrefOutputPass2(S->tag, "", "false", "");
		OutputString("prev");
		HrefEnd("\n");
	}
	OutputString("</td><td>");
	S = SectionReadNext(F);
	if( S == NULL )
		OutputString("next");
	else
	{	HrefOutputPass2(S->tag, "", "false", "");
		OutputString("next");
		HrefEnd("\n");
	}
	OutputString("</td></tr></table>\n");
	OutputString("</td>");

	// Up ------------------------------------------------------------
	OutputString("<td>\n");
	OutputString(
		"<select onchange='choose_up(this.selectedIndex)'>\n"
	); 
	OutputString("<option>Up -></option>\n");
	fprintf(javascript_fp, "var list_up = [\n");
	S = F;
	while(S != NULL)
	{	FormatOutput( "<option>%s</option>\n", S->tag);
		url = Url(S->tag, "", "false");
		fprintf(javascript_fp, "'%s'", url);
		FreeMem(url);
		S = S->parent;
		if( S != NULL )
			fprintf(javascript_fp, ",\n");
		else	fprintf(javascript_fp, "\n];\n");
	}	
	OutputString("</select>\n</td>\n"); 

	// Sibling -------------------------------------------------------
	OutputString("<td>\n");
	OutputString(
		"<select onchange='choose_sibling(this.selectedIndex)'>\n"
	); 
	OutputString("<option>Sibling -></option>\n");
	fprintf(javascript_fp, "var list_sibling = [\n");
	S = F;
	while(S->previous != NULL )
		S = S->previous;
	while( IsAutomaticSection(S) )
		S = S->next;
	while(S != NULL)
	{	FormatOutput( "<option>%s</option>\n", S->tag);
		url = Url(S->tag, "", "false");
		fprintf(javascript_fp, "'%s'", url);
		FreeMem(url);
		S = S->next;
		while( S != NULL && IsAutomaticSection(S) )
			S = S->next;
		if( S != NULL )
			fprintf(javascript_fp, ",\n");
		else	fprintf(javascript_fp, "\n];\n");
	}	
	OutputString("</select>\n</td>\n"); 

	// Down ---------------------------------------------------------
	S = F->children;
	if( S != NULL )
	{	OutputString("<td>\n");
		OutputString(
		"<select onchange='choose_down(this.selectedIndex)'>\n"
		); 
		OutputString("<option>Down -></option>\n");
		fprintf(javascript_fp, "var list_down = [\n");
		while(S->previous != NULL )
			S = S->previous;
		while( IsAutomaticSection(S) )
			S = S->next;
		while(S != NULL)
		{	FormatOutput( "<option>%s</option>\n", S->tag);
			url = Url(S->tag, "", "false");
			fprintf(javascript_fp, "'%s'", url);
			FreeMem(url);
			S = S->next;
			while( S != NULL && IsAutomaticSection(S) )
				S = S->next;
			if( S != NULL )
				fprintf(javascript_fp, ",\n");
			else	fprintf(javascript_fp, "\n];\n");
		}
		OutputString("</select>\n</td>\n"); 
	}	

	// Across ---------------------------------------------------------
	OutputString("<td>\n");
	OutputString(
		"<select onchange='choose_across(this.selectedIndex)'>\n"
	); 
	OutputString("<option>Across -></option>\n");
	fprintf(javascript_fp, "var list_across = [\n");
	i = 0;
	while( AutomaticTag(i) != NULL )
	{	const char *tag = AutomaticTag(i);
		while( *tag == '_' )
			tag++;
		FormatOutput( "<option>%s</option>\n", tag);
		url = Url(AutomaticTag(i), "", "false");
		fprintf(javascript_fp, "'%s'", url);
		FreeMem(url);
		i++;
		if( AutomaticTag(i) != NULL )
			fprintf(javascript_fp, ",\n");
		else	fprintf(javascript_fp, "\n];\n");
	}
	OutputString("</select>\n</td>\n"); 

	// -----------------------------------------------------------------
	// End table that contains the links
	OutputString("</tr></table><br");
	OutputString(Internal2Out("SelfTerminateCmd"));
	OutputString("\n");

	// End javascript file
	script =
	"function choose_up(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_up[index-1];\n"
	"}\n"
	"function choose_sibling(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_sibling[index-1];\n"
	"}\n"
	"function choose_down(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_down[index-1];\n"
	"}\n"
	"function choose_across(index)\n"
	"{	if(index > 0)\n"
	"		document.location = list_across[index-1];\n"
	"}\n"
	;
	fprintf(javascript_fp, script);
	fclose(javascript_fp);
}
