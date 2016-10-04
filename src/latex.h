/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_TEX_HOME_BRADBELL_OMHELP_GIT_SRC_LATEX_H_INCLUDED
# define YY_TEX_HOME_BRADBELL_OMHELP_GIT_SRC_LATEX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int texdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR_AMPERSAND_lex = 258,
    CHAR_CARET_lex = 259,
    CHAR_ENDINPUT_lex = 260,
    CHAR_LEFTBRACE_lex = 261,
    CHAR_LEFTBRACKET_lex = 262,
    CHAR_LETTERS_lex = 263,
    CHAR_OPERATOR_lex = 264,
    CHAR_RIGHTBRACE_lex = 265,
    CHAR_RIGHTBRACKET_lex = 266,
    CHAR_UNDERBAR_lex = 267,
    CMD_BACKSLASH_lex = 268,
    CMD_BEGIN_ARRAY_lex = 269,
    CMD_DIACRITICAL_lex = 270,
    CMD_END_ARRAY_lex = 271,
    CMD_CHAR_lex = 272,
    CMD_COMMA_lex = 273,
    CMD_COLON_lex = 274,
    CMD_FONT_lex = 275,
    CMD_FRAC_lex = 276,
    CMD_HSPACE_lex = 277,
    CMD_LEFT_lex = 278,
    CMD_LEFTBRACKET_lex = 279,
    CMD_MATHML_lex = 280,
    CMD_OVERBRACE_lex = 281,
    CMD_OVERLINE_lex = 282,
    CMD_RIGHT_lex = 283,
    CMD_RIGHTBRACKET_lex = 284,
    CMD_SEMICOLON_lex = 285,
    CMD_SQRT_lex = 286,
    CMD_STACKREL_lex = 287,
    CMD_UNDERBRACE_lex = 288,
    CMD_UNDERLINE_lex = 289,
    CMD_WIDEHAT_lex = 290,
    CMD_WIDETILDE_lex = 291,
    NUMBER_lex = 292,
    STDFUN_lex = 293,
    STD_DISPLAY_lex = 294,
    SYM_ARROW_lex = 295,
    SYM_BINARYOP_lex = 296,
    SYM_DISPLAY_lex = 297,
    SYM_DOTS_lex = 298,
    SYM_ENCLOSE_lex = 299,
    SYM_GREEK_lex = 300,
    SYM_INTEGRAL_lex = 301,
    SYM_MISC_lex = 302,
    SYM_RELATION_lex = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE texlval;

int texparse (void);

#endif /* !YY_TEX_HOME_BRADBELL_OMHELP_GIT_SRC_LATEX_H_INCLUDED  */
