%{
#include "parser.tab.h"
#include <string.h>
%}

%%

"SET"           { return SET; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return IDENTIFIER; }
[0-9]+          { yylval.ival = atoi(yytext); return VALUE; }
"="             { return EQUALS; }
";"             { return SEMICOLON; }
[ \t\n]         { /* ignore whitespace */ }
.               { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}