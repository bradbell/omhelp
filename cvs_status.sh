#! /bin/bash
cvs update | sed \
	-e '/^[?] wish_list.htm$/d'                 \
	-e '/^[?].*\.bin$/d'                        \
	-e '/^[?].*\.cache$/d'                      \
	-e '/^[?].*\.gz$/d'                         \
	-e '/^[?].*\.ilk$/d'                        \
	-e '/^[?].*\.log$/d'                        \
	-e '/^[?].*\.m4$/d'                         \
	-e '/^[?].*\.ncb$/d'                        \
	-e '/^[?].*\.suo$/d'                        \
	-e '/^[?].*\.tar$/d'                        \
	-e '/^[?].*\.tmp$/d'                        \
	-e '/^[?].*\.zip$/d'                        \
	-e '/^[?].*[/ ]\.deps$/d'                   \
	-e '/^[?].*[/ ]confdefs\./d'                \
	-e '/^[?].*[/ ]conftest\./d'                \
	-e '/^[?].*[/ ]config\./d'                  \
	-e '/^[?].*[/ ]configure$/d'                \
	-e '/^[?].*[/ ]Debug$/d'                    \
	-e '/^[?].*[/ ]Doc$/d'                      \
	-e '/^[?].*[/ ]junk$/d'                     \
	-e '/^[?].*[/ ]junk.sh$/d'                  \
	-e '/^[?].*[/ ][Mm]akefile$/d'              \
	-e '/^[?].*[/ ][Mm]akefile.in$/d'           \
	-e '/^[?].*[/ ]omhelp-[0-9-]*$/d'           \
	-e '/^[?].*[/ ]stamp-h1$/d'                 \
	-e '/^[?] omh\/getstarted\/run_all$/d'      \
	-e '/^[?] src\/latex.c$/d'                  \
	-e '/^[?] src\/latex.h$/d'                  \
	-e '/^[?] src\/lex.tex.c$/d'                \
	-e '/^[?] src\/make.c$/d'                   \
	-e '/^[?] src\/omhelp$/d'                   \
	-e '/^[?] src\/omhelp.c$/d'                 \
	-e '/^[?] src\/omhelp.h$/d'                 \
	-e '/^[?] src\/main.c$/d'                   \


