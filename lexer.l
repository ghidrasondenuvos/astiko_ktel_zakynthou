/* =========================================================================
   ΕΠΙΠΕΔΟ 1: ΒΙΒΛΙΟΘΗΚΕΣ ΚΑΙ ΔΗΛΩΣΕΙΣ
   ========================================================================= */
%{
#include "parser.tab.h" 
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     

extern int line_num;
%}

/* =========================================================================
   ΕΠΙΠΕΔΟ 2: ΡΥΘΜΙΣΕΙΣ ΑΝΑΛΥΤΗ
   ========================================================================= */
%option caseless
%option noyywrap

%x COMMENT

%%

/* =========================================================================
   ΕΠΙΠΕΔΟ 3: ΔΕΣΜΕΥΜΕΝΕΣ ΛΕΞΕΙΣ (KEYWORDS)
   ========================================================================= */
"CREATE"    { printf("%s", yytext); return CREATE; }
"TABLE"     { printf("%s", yytext); return TABLE; }
"SELECT"    { printf("%s", yytext); return SELECT; }
"FROM"      { printf("%s", yytext); return FROM; }
"WHERE"     { printf("%s", yytext); return WHERE; }
"GROUP"     { printf("%s", yytext); return GROUP; }
"BY"        { printf("%s", yytext); return BY; }
"ORDER"     { printf("%s", yytext); return ORDER; }
"LIMIT"     { printf("%s", yytext); return LIMIT; }
"JOIN"      { printf("%s", yytext); return JOIN; }
"ON"        { printf("%s", yytext); return ON; }
"AS"        { printf("%s", yytext); return AS; }

/* =========================================================================
   ΕΠΙΠΕΔΟ 4: ΤΥΠΟΙ ΔΕΔΟΜΕΝΩΝ ΚΑΙ ΛΟΓΙΚΟΙ ΤΕΛΕΣΤΕΣ
   ========================================================================= */
"INT"       { printf("%s", yytext); return TYPE_INT; }
"FLOAT"     { printf("%s", yytext); return TYPE_FLOAT; }
"VARCHAR"   { printf("%s", yytext); return TYPE_VARCHAR; }
"AND"       { printf("%s", yytext); return AND; }
"OR"        { printf("%s", yytext); return OR; }
"NOT"       { printf("%s", yytext); return NOT; }
"IN"        { printf("%s", yytext); return IN; }

/* =========================================================================
   ΕΠΙΠΕΔΟ 5: ΤΕΛΕΣΤΕΣ ΣΥΓΚΡΙΣΗΣ ΚΑΙ ΣΥΜΒΟΛΑ ΣΤΙΞΗΣ
   ========================================================================= */
"="         { printf("%s", yytext); return EQUALS; }
"!="        { printf("%s", yytext); return NOT_EQUALS; }
">="        { printf("%s", yytext); return GREATER_EQUAL; }
"<="        { printf("%s", yytext); return LESS_EQUAL; }
">"         { printf("%s", yytext); return GREATER; }
"<"         { printf("%s", yytext); return LESS; }
","         { printf("%s", yytext); return COMMA; }
";"         { printf("%s", yytext); return SEMICOLON; }
"."         { printf("%s", yytext); return DOT; }
"("         { printf("%s", yytext); return LPAREN; }
")"         { printf("%s", yytext); return RPAREN; }
"*"         { printf("%s", yytext); return ASTERISK; }

/* =========================================================================
   ΕΠΙΠΕΔΟ 6: ΑΝΑΓΝΩΡΙΣΗ ΤΙΜΩΝ ΚΑΙ ΟΝΟΜΑΤΩΝ
   ========================================================================= */
[0-9]+\.[0-9]+ { printf("%s", yytext); yylval.fval = atof(yytext); return FLOAT_VAL; }
[0-9]+         { printf("%s", yytext); yylval.ival = atoi(yytext); return INT_VAL; }
"'"[^']*"'"    { printf("%s", yytext); yylval.sval = strdup(yytext); return STRING_VAL; }
[a-zA-Z_][a-zA-Z0-9_]* { printf("%s", yytext); yylval.sval = strdup(yytext); return IDENTIFIER; }

/* =========================================================================
   ΕΠΙΠΕΔΟ 7: ΔΙΑΧΕΙΡΙΣΗ ΣΧΟΛΙΩΝ
   ========================================================================= */
"--"[^\n]* { printf("%s", yytext); } 
"/*"           { BEGIN(COMMENT); printf("%s", yytext); }
<COMMENT>"*/"  { BEGIN(INITIAL); printf("%s", yytext); }
<COMMENT>\n    { line_num++; printf("%s", yytext); }
<COMMENT>.     { printf("%s", yytext); }

/* =========================================================================
   ΕΠΙΠΕΔΟ 8: ΚΕΝΑ ΚΑΙ ΣΦΑΛΜΑΤΑ
   ========================================================================= */
[ \t\r]+       { printf("%s", yytext); } 
\n             { printf("%s", yytext); line_num++; } 
.              { printf("%s", yytext); fprintf(stderr, "\n[Λεκτικό Σφάλμα] Άγνωστος χαρακτήρας '%s' στη γραμμή %d\n", yytext, line_num); exit(1); }

%%