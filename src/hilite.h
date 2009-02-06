# ifndef HILITE_INLUDED
# define HILITE_INLUDED


void hilite_command(
	int         line      ,
	int         n_command ,
	char       *commands 
);
void hilite_token(
	int         line      ,
	int         n_pair    ,
	char       *pairs   
);
void hilite_set_default(void);
void hilite_get_default(void);
void hilite_out(
	const char *command        ,
	int         line           , 
	int         check_spell    , 
	const char *error_color    , 
	const char *hilite_color   ,
	int         pre            , 
	char       *text
);

# endif
