%{
#include "parser.tab.h"  // Fixed: Use the correct header name
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
\n          { return NEWLINE; }
[ \t]       ; /* ignore whitespace */
%%

int yywrap() { return 1; }// kai nomizes oti tha ekanes git
//kala nomizes