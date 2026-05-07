%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUM

%%
S : E { printf("Result = %d\n", $1); }
  ;

E : E '+' E { $$ = $1 + $3; }
  | E '-' E { $$ = $1 - $3; }
  | E '*' E { $$ = $1 * $3; }
  | E '/' E { $$ = $1 / $3; }
  | '(' E ')' { $$ = $2; }
  | NUM { $$ = $1; }
  ;
%%

int main() {
    printf("Enter expression:\n");
    yyparse();
    return 0;
}

int yyerror() {
    printf("Error\n");
    return 0;
}