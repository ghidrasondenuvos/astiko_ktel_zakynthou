%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%union {
    int ival;
    char *sval;
}

%token SET EQUALS SEMICOLON
%token <ival> VALUE
%token <sval> IDENTIFIER

%%

config:
    | config assignment
    ;

assignment:
    SET IDENTIFIER EQUALS VALUE SEMICOLON {
        printf("Config matched: Variable '%s' set to %d\n", $2, $4);
        free($2);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main(void) {
    printf("Enter configuration (e.g., SET brightness = 80;):\n");
    yyparse();
    return 0;
}