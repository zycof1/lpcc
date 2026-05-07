%{
#include <stdio.h>
%}

%%
"car"|"house"|"man"|"state"|"ocean"|"country"|"city"   { printf("%s -> NOUN\n", yytext); }

"she"|"he"|"we"|"they"|"it"   { printf("%s -> PRONOUN\n", yytext); }

"come"|"go"|"walk"|"did"|"have"|"read"|"write" { printf("%s -> VERB\n", yytext); }

"pretty"|"old"|"blue"|"smart" { printf("%s -> ADJECTIVE\n", yytext); }

"abnormally"|"accidentally"|"actually"|"beautifully" { printf("%s -> ADVERB\n", yytext); }

"by"|"with"|"about"|"until" { printf("%s -> PREPOSITION\n", yytext); }

"and"|"but"|"or"|"while"|"because" { printf("%s -> CONJUNCTION\n", yytext); }

"oh"|"wow"|"oops" { printf("%s -> INTERJECTION\n", yytext); }

[a-zA-Z]+   { printf("%s -> UNKNOWN\n", yytext); }

[ \t\n]+    ;   // ignore spaces
%%

int main() {
    printf("Enter sentence:\n");
    yylex();
    return 0;
}

how to run:
flex scanner.l
gcc lex.yy.c -o scanner -lfl
./scanner
