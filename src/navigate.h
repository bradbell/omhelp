# ifndef NAVIGATE_INCLUDED
# define NAVIGATE_INCLUDED


enum navigateStyle {
	INVALID_nav,
	CONTENT_nav,
	PREV_nav,
	NEXT_nav,
	UP_nav,
	SIBLING_nav,
	DOWN_nav,
	ACROSS_nav,
	CURRENT_nav
};

extern const char *PushNavigate(int ntoken, const char *text);
extern void PopNavigate(void);
extern int NavigateNpush(void);
extern int NavigateNumber(void);
extern enum navigateStyle NavigateStyle(int index);
extern const char *NavigateLabel(int index);



# endif
