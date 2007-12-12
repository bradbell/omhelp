# ifndef OUTPUT_TEXT_INCLUDED
# define OUTPUT_TEXT_INCLUDED

extern int output_text(
	int         line        , 
	const char *s           , 
	int         pre         ,
	char        skip        ,
	int         check_spell ,
	const char *error_color 
);

# endif
