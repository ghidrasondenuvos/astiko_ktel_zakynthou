%{
#include "parser.tab.h"
#include <string.h>
%}

%%
"SET"       { return SET; }
"="         { return EQUALS; }
";"         { return SEMICOLON; }
[0-9]+      { yylval.ival = atoi(yytext); return VALUE; }
[a-zA-Z_][a-zA-Z0-9_]*  { 
                yylval.sval = strdup(yytext);  // Allocate copy for Bison to free
                return IDENTIFIER; 
            }
[ \t\n]     ;  // Ignore whitespace
.           { fprintf(stderr, "Unknown character: %s\n", yytext); }
%%

int yywrap() { return 1; }