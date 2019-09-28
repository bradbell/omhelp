/* ----------------------------------------------------------------------------
OMhelp: Language Independent Embedded Documentation
          Copyright (C) 1998-2019 Bradley M. Bell
OMhelp is distributed under the terms of the
            GNU General Public License Version 2.
---------------------------------------------------------------------------- */
/*
$begin LatexAtomic_dev$$
$spell
	Mathml
	const
$$

$section Convert Latex Atomic Commands To Mathml Text$$

$head Syntax$$
$codei/LatexAtomic(/name/, /token/)/$$


$head Description$$
The arguments $codei%const char *%name%$$
is '\0' terminated
and contains the command name
(with out the $code \$$ in front).
The return value of $code LatexAtomic$$
is a '\0' terminated $code const char*$$ containing
the UNICODE characters corresponding to the command.
If $icode name$$ is not in the specified group,
$code NULL$$ is returned.
$pre

$$
The input value of
$codei%int *%token%$$
does not matter.
If the return value of $code LatexAtomic$$ is not
$code NULL$$,
the output value of
$codei%int *%token%$$
specifies which type of token $icode name$$ represents.
It will be one of the following:


$table
$bold Value$$    $cnext $bold Description$$ $rnext
STDFUN_lex       $cnext log-like functions $rnext
STD_DISPLAY_lex  $cnext functions that act differently in Display mode $rnext
SYM_GREEK_lex    $cnext greek letter $rnext
SYM_BINARYOP_lex $cnext binary operator $rnext
SYM_RELATION_lex $cnext relation symbol $rnext
SYM_ARROW_lex    $cnext arrow symbol $rnext
SYM_MISC_lex     $cnext miscellaneous symbol $rnext
SYM_DISPLAY_lex  $cnext symbols that act differently in Display mode $rnext
SYM_DOTS_lex     $cnext multiple dots (ellipsis)
SYM_ENCLOSE_lex  $cnext an enclosing symbol (overrides other types)
SYM_INTEGRAL_lex $cnext integral symbols (also Display mode dependent) $rnext
$tend

$end
*/

/*
Source:    http://www.w3.org/TR/MathML2/byalpha.html
Date:      02-10-30
Section:   Characters Ordered by MathML Names
Chapter:   Entities, Characters and Fonts
*/

# include "LatexAtomic.h"
# include <string.h>
# include <assert.h>
# include "BinarySearch.h"

// automatically generated include file generated by yacc from latex.y
# include "latex.h"

struct {
	const char *name;
	const int  token;
	const char *mathml;
} Map[] =
{
// LATEX CODE
	// LATEX GROUP
	// MATHML CODE
	// MATHML NAME
{ "Box",
	SYM_MISC_lex,
	// "&squ;",
	"&#x025A1;" } ,
{ "Delta",
	SYM_GREEK_lex,
	// "&Delta;",
	"&#x00394;" } ,
{ "Diamond",
	SYM_MISC_lex,
	// "&Diamond;",
	"&#x022C4;" } ,
{ "Downarrow",
	SYM_ENCLOSE_lex,
	// "&Downarrow;",
	"&#x021D3;" } ,
{ "Gamma",
	SYM_GREEK_lex,
	// "&Gamma;",
	"&#x00393;" } ,
{ "Im",
	SYM_MISC_lex,
	// "&Im;",
	"&#x02111;" } ,
{ "Lambda",
	SYM_GREEK_lex,
	// "&Lambda;",
	"&#x0039B;" } ,
{ "Leftarrow",
	SYM_ARROW_lex,
	// "&Leftarrow;",
	"&#x021D0;" } ,
{ "Leftrightarrow",
	SYM_ARROW_lex,
	// "&Leftrightarrow;",
	"&#x021D4;" } ,
{ "Longleftarrow",
	SYM_ARROW_lex,
	// "&Longleftarrow;",
	"&#x027F8;" } ,
{ "Longleftrightarrow",
	SYM_ARROW_lex,
	// "&Longleftrightarrow;",
	"&#x027FA;" } ,
{ "Longrightarrow",
	SYM_ARROW_lex,
	// "&Longrightarrow;",
	"&#x027F9;" } ,
{ "Omega",
	SYM_GREEK_lex,
	// "&Omega;",
	"&#x003A9;" } ,
{ "Phi",
	SYM_GREEK_lex,
	// "&Phi;",
	"&#x003A6;" } ,
{ "Pi",
	SYM_GREEK_lex,
	// "&Pi;",
	"&#x003A0;" } ,
{ "Pr",
	STDFUN_lex,
	//
	"Pr" } ,
{ "Psi",
	SYM_GREEK_lex,
	// "&Psi;",
	"&#x003A8;" } ,
{ "Re",
	SYM_MISC_lex,
	// "&Re;",
	"&#x0211C;" } ,
{ "Rightarrow",
	SYM_ARROW_lex,
	// "&Rightarrow;",
	"&#x021D2;" } ,
{ "Sigma",
	SYM_GREEK_lex,
	// "&Sigma;",
	"&#x003A3;" } ,
{ "Theta",
	SYM_GREEK_lex,
	// "&Theta;",
	"&#x00398;" } ,
{ "Uparrow",
	SYM_ENCLOSE_lex,
	// "&Uparrow;",
	"&#x021D1;" } ,
{ "Updownarrow",
	SYM_ENCLOSE_lex,
	// "&Updownarrow;",
	"&#x021D5;" } ,
{ "Upsilon",
	SYM_GREEK_lex,
	// "&Upsi;",
	"&#x003D2;" } ,
{ "Xi",
	SYM_GREEK_lex,
	// "&Xi;",
	"&#x0039E;" } ,
{ "aleph",
	SYM_MISC_lex,
	// "&aleph;",
	"&#x02135;" } ,
{ "alpha",
	SYM_GREEK_lex,
	// "&alpha;",
	"&#x003B1;" } ,
{ "amalg",
	SYM_BINARYOP_lex,
	// "&coprod;",
	"&#x02210;" } ,
{ "angle",
	SYM_MISC_lex,
	// "&angle;",
	"&#x02220;" } ,
{ "approx",
	SYM_RELATION_lex,
	// "&approx;",
	"&#x02248;" } ,
{ "arccos",
	STDFUN_lex,
	//
	"arccos" } ,
{ "arcsin",
	STDFUN_lex,
	//
	"arcsin" } ,
{ "arctan",
	STDFUN_lex,
	//
	"arctan" } ,
{ "arg",
	STDFUN_lex,
	//
	"arg" } ,
{ "ast",
	SYM_BINARYOP_lex,
	// "&ast;",
	"&#x0002A;" } ,
{ "asymp",
	SYM_RELATION_lex,
	// "&asympeq;",
	"&#x0224D;" } ,
{ "backslash",
	SYM_ENCLOSE_lex,
	// "&bsol;",
	"&#x0005C;" } ,
{ "beta",
	SYM_GREEK_lex,
	// "&beta;",
	"&#x003B2;" } ,
{ "bigcap",
	SYM_DISPLAY_lex,
	// "&xcap;",
	"&#x022C2;" } ,
{ "bigcirc",
	SYM_BINARYOP_lex,
	// "&cir;",
	"&#x025CB;" } ,
{ "bigcup",
	SYM_DISPLAY_lex,
	// "&bigcup;",
	"&#x022C3;" } ,
{ "bigodot",
	SYM_DISPLAY_lex,
	// "&bigodot;",
	"&#x02A00;" } ,
{ "bigoplus",
	SYM_DISPLAY_lex,
	// "&bigoplus;",
	"&#x02A01;" } ,
{ "bigotimes",
	SYM_DISPLAY_lex,
	// "&bigotimes;",
	"&#x02A02;" } ,
{ "bigtriangledown",
	SYM_BINARYOP_lex,
	// "&bigtriangledown;",
	"&#x025BD;" } ,
{ "bigtriangleup",
	SYM_BINARYOP_lex,
	// "&bigtriangleup;",
	"&#x025B3;" } ,
{ "biguplus",
	SYM_DISPLAY_lex,
	// "&biguplus;",
	"&#x02A04;" } ,
{ "bigvee",
	SYM_DISPLAY_lex,
	// "&bigvee;",
	"&#x022C1;" } ,
{ "bigwedge",
	SYM_DISPLAY_lex,
	// "&bigwedge;",
	"&#x022C0;" } ,
{ "bot",
	SYM_MISC_lex,
	// "&bot;",
	"&#x022A5;" } ,
{ "bowtie",
	SYM_RELATION_lex,
	// "&bowtie;",
	"&#x022C8;" } ,
{ "bullet",
	SYM_BINARYOP_lex,
	// "&bullet;",
	"&#x02022;" } ,
{ "cap",
	SYM_BINARYOP_lex,
	// "&cap;",
	"&#x02229;" } ,
{ "cdot",
	SYM_BINARYOP_lex,
	// "&centerdot;",
	"&#x000B7;" } ,
{ "cdots",
	SYM_DOTS_lex,
	// "&ctdot;",
	"&#x022EF;" } ,

{ "chi",
	SYM_GREEK_lex,
	// "&chi;",
	"&#x003C7;" } ,
{ "circ",
	SYM_BINARYOP_lex,
	// "&compfn;",
	"&#x02218;" } ,
{ "clubsuit",
	SYM_MISC_lex,
	// "&clubsuit;",
	"&#x02663;" } ,
{ "cong",
	SYM_RELATION_lex,
	// "&cong;",
	"&#x02245;" } ,
{ "coprod",
	SYM_DISPLAY_lex,
	// "&coprod;",
	"&#x02210;" } ,
{ "cos",
	STDFUN_lex,
	//
	"cos" } ,
{ "cosh",
	STDFUN_lex,
	//
	"cosh" } ,
{ "cot",
	STDFUN_lex,
	//
	"cot" } ,
{ "coth",
	STDFUN_lex,
	//
	"coth" } ,
{ "csc",
	STDFUN_lex,
	//
	"csc" } ,
{ "cup",
	SYM_BINARYOP_lex,
	// "&cup;",
	"&#x0222A;" } ,
{ "dagger",
	SYM_BINARYOP_lex,
	// "&dagger;",
	"&#x02020;" } ,
{ "dashv",
	SYM_RELATION_lex,
	// "&dashv;",
	"&#x022A3;" } ,
{ "ddagger",
	SYM_BINARYOP_lex,
	// "&ddagger;",
	"&#x02021;" } ,
{ "ddots",
	SYM_DOTS_lex,
	// "&dtdot;",
	"&#x022F1;" } ,
{ "deg",
	STDFUN_lex,
	//
	"deg" } ,
{ "delta",
	SYM_GREEK_lex,
	// "&delta;",
	"&#x003B4;" } ,
{ "det",
	STDFUN_lex,
	//
	"det" } ,
{ "diamond",
	SYM_BINARYOP_lex,
	// "&diamond;",
	"&#x022C4;" } ,
{ "diamondsuit",
	SYM_MISC_lex,
	//
	"&#x02662;" } ,
{ "dim",
	STDFUN_lex,
	//
	"dim" } ,
{ "div",
	SYM_BINARYOP_lex,
	// "&div;",
	"&#x000F7;" } ,
{ "doteq",
	SYM_RELATION_lex,
	// "&doteq;",
	"&#x02250;" } ,
{ "downarrow",
	SYM_ENCLOSE_lex,
	// "&downarrow;",
	"&#x02193;" } ,
{ "ell",
	SYM_MISC_lex,
	// "&ell;",
	"&#x02113;" } ,
{ "emptyset",
	SYM_MISC_lex,
	// "&varnothing;",
	"&#x02205;" } ,
{ "epsilon",
	SYM_GREEK_lex,
	// "&Element;", would use "&epsi;" if IE worked with it
	"&#x02208;" } ,
{ "equiv",
	SYM_RELATION_lex,
	// "&equiv;",
	"&#x02261;" } ,
{ "eta",
	SYM_GREEK_lex,
	// "&eta;",
	"&#x003B7;" } ,
{ "exists",
	SYM_MISC_lex,
	// "&Exists;",
	"&#x02203;" } ,
{ "exp",
	STDFUN_lex,
	//
	"exp" } ,
{ "flat",
	SYM_MISC_lex,
	// "&flat;",
	"&#x0266D;" } ,
{ "forall",
	SYM_MISC_lex,
	// "&forall;",
	"&#x02200;" } ,
{ "frown",
	SYM_RELATION_lex,
	// "&frown;",
	"&#x02322;" } ,
{ "gamma",
	SYM_GREEK_lex,
	// "&gamma;",
	"&#x003B3;" } ,
{ "gcd",
	STDFUN_lex,
	//
	"gcd" } ,
{ "geq",
	SYM_RELATION_lex,
	// "&geq;",
	"&#x02265;" } ,
{ "gg",
	SYM_RELATION_lex,
	// "&gg;",
	"&#x0226B;" } ,
{ "hbar",
	SYM_MISC_lex,
	// "&plankv;",
	"&#x0210F;" } ,
{ "heartsuit",
	SYM_MISC_lex,
	//
	"&#x02661;" } ,
{ "hom",
	STDFUN_lex,
	//
	"hom" } ,
{ "hookleftarrow",
	SYM_ARROW_lex,
	// "&hookleftarrow;",
	"&#x021A9;" } ,
{ "hookrightarrow",
	SYM_ARROW_lex,
	// "&hookrightarrow;",
	"&#x021AA;" } ,
{ "imath",
	SYM_MISC_lex,
	// "&imath;",
	"&#x00131;" } ,
{ "in",
	SYM_RELATION_lex,
	// "&in;",
	"&#x02208;" } ,
{ "inf",
	STD_DISPLAY_lex,
	//
	"inf" } ,
{ "infty",
	SYM_MISC_lex,
	// "&infin;",
	"&#x0221E;" } ,
{ "int",
	SYM_INTEGRAL_lex,
	// "&int;",
	"&#x0222B;" } ,
{ "iota",
	SYM_GREEK_lex,
	// "&iota;",
	"&#x003B9;" } ,
{ "jmath",
	SYM_MISC_lex,
	// "&jmath;",
	"&#x0006A;" } ,
{ "kappa",
	SYM_GREEK_lex,
	// "&kappa;",
	"&#x003BA;" } ,
{ "ker",
	STDFUN_lex,
	//
	"ker" } ,
{ "lambda",
	SYM_GREEK_lex,
	// "&lambda;",
	"&#x003BB;" } ,
{ "langle",
	SYM_ENCLOSE_lex,
	// "&langle;",
	"&#x02329;" } ,
{ "lceil",
	SYM_ENCLOSE_lex,
	// "&lceil;",
	"&#x02308;" } ,
{ "ldots",
	SYM_DOTS_lex,
	// "&hellip;",
	"&#x02026;" } ,
{ "leadsto",
	SYM_ARROW_lex,
	// "&rightsquigarrow;",
	"&#x0219D;" } ,
{ "leftarrow",
	SYM_ARROW_lex,
	// "&leftarrow;",
	"&#x02190;" } ,
{ "leftharpoondown",
	SYM_ARROW_lex,
	// "&leftharpoondown;",
	"&#x021BD;" } ,
{ "leftharpoonup",
	SYM_ARROW_lex,
	// "&leftharpoonup;",
	"&#x021BC;" } ,
{ "leftrightarrow",
	SYM_ARROW_lex,
	// "&leftrightarrow;",
	"&#x02194;" } ,
{ "leq",
	SYM_RELATION_lex,
	// "&leq;",
	"&#x02264;" } ,
{ "lfloor",
	SYM_ENCLOSE_lex,
	// "&lfloor;",
	"&#x0230A;" } ,
{ "lg",
	STDFUN_lex,
	//
	"lg" } ,
{ "lim",
	STD_DISPLAY_lex,
	//
	"lim" } ,
{ "liminf",
	STD_DISPLAY_lex,
	//
	"liminf" } ,
{ "limsup",
	STD_DISPLAY_lex,
	//
	"limsup" } ,
{ "ll",
	SYM_RELATION_lex,
	// "&ll;",
	"&#x0226A;" } ,
{ "ln",
	STDFUN_lex,
	//
	"ln" } ,
{ "log",
	STDFUN_lex,
	//
	"log" } ,
{ "longleftarrow",
	SYM_ARROW_lex,
	// "&longleftarrow;",
	"&#x027F5;" } ,
{ "longleftrightarrow",
	SYM_ARROW_lex,
	// "&longleftrightarrow;",
	"&#x027F7;" } ,
{ "longmapsto",
	SYM_ARROW_lex,
	// "&longmapsto;",
	"&#x027FC;" } ,
{ "longrightarrow",
	SYM_ARROW_lex,
	// "&longrightarrow;",
	"&#x027F6;" } ,
{ "mapsto",
	SYM_ARROW_lex,
	// "&mapsto;",
	"&#x021A6;" } ,
{ "max",
	STD_DISPLAY_lex,
	//
	"max" } ,
{ "mho",
	SYM_MISC_lex,
	// "&mho;",
	"&#x02127;" } ,
{ "mid",
	SYM_RELATION_lex,
	// "&mid;",
	"&#x02223;" } ,
{ "min",
	STD_DISPLAY_lex,
	//
	"min" } ,
{ "models",
	SYM_RELATION_lex,
	// "&models;",
	"&#x022A7;" } ,
{ "mp",
	SYM_BINARYOP_lex,
	// "&mp;",
	"&#x02213;" } ,
{ "mu",
	SYM_GREEK_lex,
	// "&mu;",
	"&#x003BC;" } ,
{ "nabla",
	SYM_MISC_lex,
	// "&nabla;",
	"&#x02207;" } ,
{ "natural",
	SYM_MISC_lex,
	// "&natural;",
	"&#x0266E;" } ,
{ "nearrow",
	SYM_ARROW_lex,
	// "&nearrow;",
	"&#x02197;" } ,
{ "neg",
	SYM_MISC_lex,
	// "&not;",
	"&#x000AC;" } ,
{ "neq",
	SYM_RELATION_lex,
	// "&ne;",
	"&#x02260;" } ,
{ "ni",
	SYM_RELATION_lex,
	// "&ni;",
	"&#x0220B;" } ,
{ "nu",
	SYM_GREEK_lex,
	// "&nu;",
	"&#x003BD;" } ,
{ "nwarrow",
	SYM_ARROW_lex,
	// "&nwarrow;",
	"&#x02196;" } ,
{ "odot",
	SYM_BINARYOP_lex,
	// "&odot;",
	"&#x02299;" } ,
{ "oint",
	SYM_INTEGRAL_lex,
	// "&oint;",
	"&#x0222E;" } ,
{ "omega",
	SYM_GREEK_lex,
	// "&omega;",
	"&#x003C9;" } ,
{ "ominus",
	SYM_BINARYOP_lex,
	// "&ominus;",
	"&#x02296;" } ,
{ "oplus",
	SYM_BINARYOP_lex,
	// "&oplus;",
	"&#x02295;" } ,
{ "oslash",
	SYM_BINARYOP_lex,
	// "&osol;",
	"&#x02298;" } ,
{ "otimes",
	SYM_BINARYOP_lex,
	// "&otimes;",
	"&#x02297;" } ,
{ "parallel",
	SYM_RELATION_lex,
	// "&parallel;",
	"&#x02225;" } ,
{ "partial",
	SYM_MISC_lex,
	// "&part;",
	"&#x02202;" } ,
{ "perp",
	SYM_RELATION_lex,
	// "&perp;",
	"&#x022A5;" } ,
{ "phi",
	SYM_GREEK_lex,
	// "&phi;",
	"&#x003D5;" } ,
{ "pi",
	SYM_GREEK_lex,
	// "&pi;",
	"&#x003C0;" } ,
{ "pm",
	SYM_BINARYOP_lex,
	// "&pm;",
	"&#x000B1;" } ,
{ "prec",
	SYM_RELATION_lex,
	// "&prec;",
	"&#x0227A;" } ,
{ "preceq",
	SYM_RELATION_lex,
	// "&pre;",
	"&#x02AAF;" } ,
{ "prime",
	SYM_MISC_lex,
	// "&prime;",
	"&#x02032;" } ,
{ "prod",
	SYM_DISPLAY_lex,
	// "&prod;",
	"&#x0220F;" } ,
{ "propto",
	SYM_RELATION_lex,
	// "&propto;",
	"&#x0221D;" } ,
{ "psi",
	SYM_GREEK_lex,
	// "&psi;",
	"&#x003C8;" } ,
{ "rangle",
	SYM_ENCLOSE_lex,
	// "&rangle;",
	"&#x0232A;" } ,
{ "rceil",
	SYM_ENCLOSE_lex,
	// "&rceil;",
	"&#x02309;" } ,
{ "rfloor",
	SYM_ENCLOSE_lex,
	// "&rfloor;",
	"&#x0230B;" } ,
{ "rho",
	SYM_GREEK_lex,
	// "&rho;",
	"&#x003C1;" } ,
{ "rightarrow",
	SYM_ARROW_lex,
	// "&rightarrow;",
	"&#x02192;" } ,
{ "rightharpoondown",
	SYM_ARROW_lex,
	// "&rightharpoondown;",
	"&#x021C1;" } ,
{ "rightharpoonup",
	SYM_ARROW_lex,
	// "&rightharpoonup;",
	"&#x021C0;" } ,
{ "rightleftharpoons",
	SYM_ARROW_lex,
	// "&rightleftharpoons;",
	"&#x021CC;" } ,
{ "searrow",
	SYM_ARROW_lex,
	// "&searrow;",
	"&#x02198;" } ,
{ "sec",
	STDFUN_lex,
	//
	"sec" } ,
{ "setminus",
	SYM_BINARYOP_lex,
	// "&setminus;",
	"&#x02216;" } ,
{ "sharp",
	SYM_MISC_lex,
	// "&sharp;",
	"&#x0266F;" } ,
{ "sigma",
	SYM_GREEK_lex,
	// "&sigma;",
	"&#x003C3;" } ,
{ "sim",
	SYM_RELATION_lex,
	// "&sim;",
	"&#x0223C;" } ,
{ "simeq",
	SYM_RELATION_lex,
	// "&simeq;",
	"&#x02243;" } ,
{ "sin",
	STDFUN_lex,
	//
	"sin" } ,
{ "sinh",
	STDFUN_lex,
	//
	"sinh" } ,
{ "smile",
	SYM_RELATION_lex,
	// "&smile;",
	"&#x02323;" } ,
{ "spadesuit",
	SYM_MISC_lex,
	// "&spadesuit;",
	"&#x02660;" } ,
{ "sqcap",
	SYM_BINARYOP_lex,
	// "&sqcap;",
	"&#x02293;" } ,
{ "sqcup",
	SYM_BINARYOP_lex,
	// "&sqcup;",
	"&#x02294;" } ,
{ "sqsubset",
	SYM_RELATION_lex,
	// "&sqsubset;",
	"&#x0228F;" } ,
{ "sqsubseteq",
	SYM_RELATION_lex,
	// "&sqsubseteq;",
	"&#x02291;" } ,
{ "sqsupset",
	SYM_RELATION_lex,
	// "&sqsupset;",
	"&#x02290;" } ,
{ "sqsupseteq",
	SYM_RELATION_lex,
	// "&sqsupseteq;",
	"&#x02292;" } ,
{ "star",
	SYM_BINARYOP_lex,
	// "&starf;",
	"&#x02605;" } ,
{ "subset",
	SYM_RELATION_lex,
	// "&subset;",
	"&#x02282;" } ,
{ "subseteq",
	SYM_RELATION_lex,
	// "&subseteq;",
	"&#x02286;" } ,
{ "succ",
	SYM_RELATION_lex,
	// "&succ;",
	"&#x0227B;" } ,
{ "succeq",
	SYM_RELATION_lex,
	// "&succeq;",
	"&#x02AB0;" } ,
{ "sum",
	SYM_DISPLAY_lex,
	// "&sum;",
	"&#x02211;" } ,
{ "sup",
	STD_DISPLAY_lex,
	//
	"sup" } ,
{ "supset",
	SYM_RELATION_lex,
	// "&supset;",
	"&#x02283;" } ,
{ "supseteq",
	SYM_RELATION_lex,
	// "&supseteq;",
	"&#x02287;" } ,
{ "surd",
	SYM_MISC_lex,
	// "&radic;",
	"&#x0221A;" } ,
{ "swarrow",
	SYM_ARROW_lex,
	// "&swarrow;",
	"&#x02199;" } ,
{ "tan",
	STDFUN_lex,
	//
	"tan" } ,
{ "tanh",
	STDFUN_lex,
	//
	"tanh" } ,
{ "tau",
	SYM_GREEK_lex,
	// "&tau;",
	"&#x003C4;" } ,
{ "theta",
	SYM_GREEK_lex,
	// "&theta;",
	"&#x003B8;" } ,
{ "times",
	SYM_BINARYOP_lex,
	// "&times;",
	"&#x000D7;" } ,
{ "top",
	SYM_MISC_lex,
	// "&top;",
	"&#x022A4;" } ,
{ "triangle",
	SYM_MISC_lex,
	// "&xutri;",
	"&#x025B3;" } ,
{ "triangleleft",
	SYM_BINARYOP_lex,
	// "&vartriangleleft;",
	"&#x022B2;" } ,
{ "triangleright",
	SYM_BINARYOP_lex,
	// "&vartriangleright;",
	"&#x022B3;" } ,
{ "uparrow",
	SYM_ENCLOSE_lex,
	// "&uparrow;",
	"&#x02191;" } ,
{ "updownarrow",
	SYM_ENCLOSE_lex,
	// "&updownarrow;",
	"&#x02195;" } ,
{ "uplus",
	SYM_BINARYOP_lex,
	// "&uplus;",
	"&#x0228E;" } ,
{ "upsilon",
	SYM_GREEK_lex,
	// "&upsilon;",
	"&#x003C5;" } ,
{ "varepsilon",
	SYM_GREEK_lex,
	// "&varepsilon;",
	"&#x003B5;" } ,
{ "varphi",
	SYM_GREEK_lex,
	// "&varphi;",
	"&#x003C6;" } ,
{ "varpi",
	SYM_GREEK_lex,
	// "&varpi;",
	"&#x003D6;" } ,
{ "varrho",
	SYM_GREEK_lex,
	// "&varrho;",
	"&#x003F1;" } ,
{ "varsigma",
	SYM_GREEK_lex,
	// "&varsigma;",
	"&#x003C2;" } ,
{ "vartheta",
	SYM_GREEK_lex,
	// "&vartheta;",
	"&#x003D1;" } ,
{ "vdash",
	SYM_RELATION_lex,
	// "&vdash;",
	"&#x022A2;" } ,
{ "vdots",
	SYM_DOTS_lex,
	// "&vellip;",
	"&#x022EE;" } ,
{ "vee",
	SYM_BINARYOP_lex,
	// "&vee;",
	"&#x02228;" } ,
{ "wedge",
	SYM_BINARYOP_lex,
	// "&wedge;",
	"&#x02227;" } ,
{ "wp",
	SYM_MISC_lex,
	// "&wp;",
	"&#x02118;" } ,
{ "wr",
	SYM_BINARYOP_lex,
	// "&wr;",
	"&#x02240;" } ,
{ "xi",
	SYM_GREEK_lex,
	// "&xi;",
	"&#x003BE;" } ,
{ "zeta",
	SYM_GREEK_lex,
	// "&zeta;",
	"&#x003B6;" } ,
};
static const int N_Map = sizeof(Map) / sizeof(Map[0]);
static const char *Name[ sizeof(Map) / sizeof(Map[0] ) ];
static int Initialize = 1;


const char *LatexAtomic(const char *name, int *token)
{	int i;

	if( Initialize )
	{	for(i = 0; i < N_Map; i++ )
		{	Name[i] = Map[i].name;
			if( i > 0 )
				assert( strcmp( Name[i], Name[i-1] ) > 0 );
		}
		Initialize = 0;
	}

	i = BinarySearch(Name, N_Map, name);
	if( i >= N_Map )
		return NULL;


	*token = Map[i].token;
	return Map[i].mathml;
}
