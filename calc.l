%{
#include "y.tab.h"
#include <stdio.h>
%}

%%
[0-9]+   { yylval = atoi(yytext); return NUM; }
[ \t]    ;
\n       return 0;
.        return yytext[0];
%%
flex calc.l
bison -d calc.y
g++ calc.tab.c lex.yy.c -lfl -o calc
./calc
