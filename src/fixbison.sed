/^yyparse ()$/b fix
b end
:fix
N
s/yyparse ().    ;/yyparse ()/
:end
