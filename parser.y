%{
#include <stdio.h>
#include <stdlib.h>

// Add function prototypes
int yylex(void);
int yyerror(const char *s);
%}

%token NUMBER
%token PLUS MINUS MUL DIV
%token NEWLINE

%%
input: /* empty */
     | input line
     ;

line: NEWLINE
    | expr NEWLINE { printf("Result: %d\n", $1); }
    ;

expr: NUMBER            { $$ = $1; }
    | expr PLUS expr    { $$ = $1 + $3; }
    | expr MINUS expr   { $$ = $1 - $3; }
    | expr MUL expr     { $$ = $1 * $3; }
    | expr DIV expr     { 
                           if ($3 == 0) {
                               yyerror("Division by zero");
                               $$ = 0;
                           } else {
                               $$ = $1 / $3;
                           }
                         }
    ;
%%

int main() {
    printf("Calculator ready (supports +, -, *, /)\n");
    printf("Enter expressions (e.g., 5+3 or 10*4):\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {  // Fixed: Added int return type and const
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}