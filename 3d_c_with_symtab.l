%{
#include <stdio.h>
#include <string.h>

struct symtab {
    char token[50];
    char type[30];
} table[200];

int count = 0;

void add(char *tok, char *type) {
    strcpy(table[count].token, tok);
    strcpy(table[count].type, type);
    count++;
}
%}

%%
"int"|"float"|"if"|"while"|"for"   { add(yytext,"KEYWORD"); }

[0-9]+(\.[0-9]+)?   { add(yytext,"NUMBER"); }

[a-zA-Z_][a-zA-Z0-9_]*   { add(yytext,"IDENTIFIER"); }

"+"|"-"|"*"|"/"|"%"   { add(yytext,"ARITHMETIC OPERATOR"); }

"&&"|"||"   { add(yytext,"LOGICAL OPERATOR"); }

"<"|"<="|">"|">="|"=="   { add(yytext,"RELATIONAL OPERATOR"); }

";"|","|"("|")"|"{"|"}"   { add(yytext,"PUNCTUATION"); }

"%d"|"%c"|"%s"|"%f"   { add(yytext,"FORMAT SPECIFIER"); }

[ \t\n]+ ;
%%

int main() {
    yylex();

    printf("\nSymbol Table:\n");
    for(int i=0;i<count;i++) {
        printf("%s -> %s\n", table[i].token, table[i].type);
    }
    return 0;
}
//////////////
how to run:
flex scanner.l
gcc lex.yy.c -o scanner -lfl
./scanner