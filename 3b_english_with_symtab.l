%{
#include <stdio.h>
#include <string.h>

struct symtab {
    char word[50];
    char type[20];
} table[100];

int count = 0;

void add(char *word, char *type) {
    strcpy(table[count].word, word);
    strcpy(table[count].type, type);
    count++;
}
%}

%%
"car"|"house"|"man"   { add(yytext,"NOUN"); }
"she"|"he"|"we"       { add(yytext,"PRONOUN"); }
"come"|"go"|"walk"    { add(yytext,"VERB"); }
"pretty"|"old"        { add(yytext,"ADJECTIVE"); }
"by"|"with"           { add(yytext,"PREPOSITION"); }

[a-zA-Z]+             { add(yytext,"UNKNOWN"); }

[ \t\n]+ ;
%%

int main() {
    yylex();

    printf("\nSymbol Table:\n");
    for(int i=0;i<count;i++) {
        printf("%s -> %s\n", table[i].word, table[i].type);
    }
    return 0;
}
how to run:
flex scanner.l
gcc lex.yy.c -o scanner -lfl
./scanner
