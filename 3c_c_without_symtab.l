%{
#include <stdio.h>
%}

%%
"int"|"float"|"if"|"while"|"for"|"printf"   { printf("%s -> KEYWORD\n", yytext); }

[0-9]+(\.[0-9]+)?   { printf("%s -> NUMBER\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*   { printf("%s -> IDENTIFIER\n", yytext); }

"+"|"-"|"*"|"/"|"%"   { printf("%s -> ARITHMETIC OPERATOR\n", yytext); }

"&&"|"||"   { printf("%s -> LOGICAL OPERATOR\n", yytext); }

"<"|"<="|">"|">="|"=="   { printf("%s -> RELATIONAL OPERATOR\n", yytext); }

";"|","|"("|")"|"{"|"}"|"["|"]"   { printf("%s -> PUNCTUATION\n", yytext); }

"%d"|"%c"|"%s"|"%f"   { printf("%s -> FORMAT SPECIFIER\n", yytext); }

[ \t\n]+ ;
%%

int main() {
    printf("Enter C code:\n");
    yylex();
    return 0;
}
how to run:
flex scanner.l
gcc lex.yy.c -o scanner -lfl
./scanner
