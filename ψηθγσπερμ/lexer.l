%{                                    /* Επίπεδο 1: Βιβλιοθήκες και εξωτερικές μεταβλητές */
#include "parser.tab.h" 
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
extern int line_num;
%}



                                             /* Επίπεδο 2: Ρυθμίσεις αναλυτή */
%option noyywrap
%x COMMENT



%%

[Cc][Rr][Ee][Aa][Tt][Ee]     { printf("%s", yytext); return CREATE; /* Επίπεδο 3: Δεσμευμένες λέξεις (Keywords) */}
[Tt][Aa][Bb][Ll][Ee]         { printf("%s", yytext); return TABLE; /* σύστημα regex */}
[Ss][Ee][Ll][Ee][Cc][Tt]     { printf("%s", yytext); return SELECT; }
[Ff][Rr][Oo][Mm]             { printf("%s", yytext); return FROM; }
[Ww][Hh][Ee][Rr][Ee]         { printf("%s", yytext); return WHERE; }
[Gg][Rr][Oo][Uu][Pp]         { printf("%s", yytext); return GROUP; }
[Bb][Yy]                     { printf("%s", yytext); return BY; }
[Oo][Rr][Dd][Ee][Rr]         { printf("%s", yytext); return ORDER; }
[Ll][Ii][Mm][Ii][Tt]         { printf("%s", yytext); return LIMIT; }
[Jj][Oo][Ii][Nn]             { printf("%s", yytext); return JOIN; }
[Oo][Nn]                     { printf("%s", yytext); return ON; }
[Aa][Ss]                     { printf("%s", yytext); return AS; }



[Ii][Nn][Tt]                 { printf("%s", yytext); return TYPE_INT; /* Επίπεδο 4: Τύποι δεδομένων και λογικοί τελεστές */ }
[Ff][Ll][Oo][Aa][Tt]         { printf("%s", yytext); return TYPE_FLOAT; }
[Vv][Aa][Rr][Cc][Hh][Aa][Rr] { printf("%s", yytext); return TYPE_VARCHAR; }
[Aa][Nn][Dd]                 { printf("%s", yytext); return AND; }
[Oo][Rr]                     { printf("%s", yytext); return OR; }
[Nn][Oo][Tt]                 { printf("%s", yytext); return NOT; }
[Ii][Nn]                     { printf("%s", yytext); return IN; }



"=" { printf("%s", yytext); return EQUALS; /* Επίπεδο 5: Τελεστές σύγκρισης και σύμβολα στίξης */ }
"!=" { printf("%s", yytext); return NOT_EQUALS; }
">=" { printf("%s", yytext); return GREATER_EQUAL; }
"<=" { printf("%s", yytext); return LESS_EQUAL; }
">" { printf("%s", yytext); return GREATER; }
"<" { printf("%s", yytext); return LESS; }
"," { printf("%s", yytext); return COMMA; }
";" { printf("%s", yytext); return SEMICOLON; }
"." { printf("%s", yytext); return DOT; }
"(" { printf("%s", yytext); return LPAREN; }
")" { printf("%s", yytext); return RPAREN; }
"*" { printf("%s", yytext); return ASTERISK; /* (↓)Επίπεδο 6: Αναγνώριση αριθμών, συμβολοσειρών και αναγνωριστικών */ }



[0-9]+\.[0-9]+ { printf("%s", yytext); yylval.fval = atof(yytext); return FLOAT_VAL;  }
[0-9]+ { printf("%s", yytext); yylval.ival = atoi(yytext); return INT_VAL; }
"'"[^']*"'" { printf("%s", yytext); yylval.sval = strdup(yytext); return STRING_VAL; }
[a-zA-Z_][a-zA-Z0-9_]* { printf("%s", yytext); yylval.sval = strdup(yytext); return IDENTIFIER; }



"--"[^\n]* { printf("%s", yytext);  /* Επίπεδο 7: Διαχείριση σχολίων */ }
"/*" { BEGIN(COMMENT); printf("%s", yytext); }
<COMMENT>"*/" { BEGIN(INITIAL); printf("%s", yytext); }
<COMMENT>\n { line_num++; printf("%s", yytext); }
<COMMENT>. { printf("%s", yytext); }



[ \t\r]+ { printf("%s", yytext); } /* Επίπεδο 8: Κενά διαστήματα, αλλαγές γραμμής και χειρισμός σφαλμάτων */
\n { printf("%s", yytext); line_num++; } 
. { printf("%s", yytext); fprintf(stderr, "\n[Λεκτικό Σφάλμα] Άγνωστος χαρακτήρας '%s' στη γραμμή %d\n", yytext, line_num); exit(1); }
%%