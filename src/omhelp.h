/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_OMH_HOME_BRADBELL_REPO_OMHELP_GIT_SRC_OMHELP_H_INCLUDED
# define YY_OMH_HOME_BRADBELL_REPO_OMHELP_GIT_SRC_OMHELP_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int omhdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ACCENT_lex = 258,
    AINDEX_lex = 259,
    ALIGN_lex = 260,
    BEGIN_lex = 261,
    BGCOLOR_lex = 262,
    BIG_lex = 263,
    BOLD_lex = 264,
    CEND_lex = 265,
    CENTER_lex = 266,
    CHILDREN_lex = 267,
    CHILDTABLE_lex = 268,
    CINDEX_lex = 269,
    CMARK_lex = 270,
    CNEXT_lex = 271,
    CODE_lex = 272,
    CODECOLOR_lex = 273,
    CODEI_lex = 274,
    CODEP_lex = 275,
    COMMENT_lex = 276,
    CONTENTS_lex = 277,
    CREF_lex = 278,
    DATE_lex = 279,
    DOLLAR_lex = 280,
    DOUBLE_DOLLAR_lex = 281,
    END_lex = 282,
    EOF_lex = 283,
    ERRORCOLOR_lex = 284,
    ESCAPE_lex = 285,
    EXECUTE_lex = 286,
    FEND_lex = 287,
    FIXED_lex = 288,
    HEAD_lex = 289,
    HILITECMD_lex = 290,
    HILITECOLOR_lex = 291,
    HILITESEQ_lex = 292,
    HREF_lex = 293,
    ICODE_lex = 294,
    ICON_lex = 295,
    IMAGE_lex = 296,
    INCLUDE_lex = 297,
    INDEX_lex = 298,
    ITALIC_lex = 299,
    LATEX_lex = 300,
    LEND_lex = 301,
    LINKCOLOR_lex = 302,
    LIST_lex = 303,
    LNEXT_lex = 304,
    MATH_lex = 305,
    MINDEX_lex = 306,
    MREF_lex = 307,
    NAVIGATE_lex = 308,
    NEWLINECH_lex = 309,
    NOBREAK_lex = 310,
    NOSPELL_lex = 311,
    NUMBER_lex = 312,
    PATH_lex = 313,
    PRE_lex = 314,
    REND_lex = 315,
    RMARK_lex = 316,
    RNEXT_lex = 317,
    RREF_lex = 318,
    SECTION_lex = 319,
    SKIPNL_lex = 320,
    SMALL_lex = 321,
    SPELL_lex = 322,
    SRCCODE_lex = 323,
    SRCFILE_lex = 324,
    SRCTHISFILE_lex = 325,
    SUBHEAD_lex = 326,
    SYNTAX_lex = 327,
    TABLE_lex = 328,
    TABSIZE_lex = 329,
    TEND_lex = 330,
    TEXT_lex = 331,
    TEXTCOLOR_lex = 332,
    TH_lex = 333,
    TITLE_lex = 334,
    TRACE_lex = 335,
    TREF_lex = 336,
    VERBATIM_lex = 337,
    VISITCOLOR_lex = 338,
    WSPACE_lex = 339,
    XREF_lex = 340
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE omhlval;

int omhparse (void);

#endif /* !YY_OMH_HOME_BRADBELL_REPO_OMHELP_GIT_SRC_OMHELP_H_INCLUDED  */
