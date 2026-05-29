%{
#include "parser.tab.h" 
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     

extern int line_num;
%}

%option caseless
%option noyywrap

/* Φτιάχνουμε ένα Κρυφό Δωμάτιο (COMMENT) για τα μεγάλα σχόλια */
%x COMMENT

%%

"CREATE"    { /* Τουβλάκι CREATE */ printf("%s", yytext); return CREATE; }
"TABLE"     { /* Τουβλάκι TABLE */ printf("%s", yytext); return TABLE; }
"SELECT"    { /* Τουβλάκι SELECT */ printf("%s", yytext); return SELECT; }
"FROM"      { /* Αυτοκόλλητο FROM */ printf("%s", yytext); return FROM; }
"WHERE"     { /* Αυτοκόλλητο WHERE */ printf("%s", yytext); return WHERE; }
"GROUP"     { /* Αυτοκόλλητο GROUP */ printf("%s", yytext); return GROUP; }
"BY"        { /* Αυτοκόλλητο BY */ printf("%s", yytext); return BY; }
"ORDER"     { /* Αυτοκόλλητο ORDER */ printf("%s", yytext); return ORDER; }
"LIMIT"     { /* Αυτοκόλλητο LIMIT */ printf("%s", yytext); return LIMIT; }
"JOIN"      { /* Αυτοκόλλητο JOIN */ printf("%s", yytext); return JOIN; }
"ON"        { /* Αυτοκόλλητο ON */ printf("%s", yytext); return ON; }
"AS"        { /* Αυτοκόλλητο AS */ printf("%s", yytext); return AS; }

"INT"       { /* Μόνο ολόκληροι αριθμοί */ printf("%s", yytext); return TYPE_INT; }
"FLOAT"     { /* Αριθμοί με τελεία/δεκαδικοί */ printf("%s", yytext); return TYPE_FLOAT; }
"VARCHAR"   { /* Κείμενο ή λέξεις */ printf("%s", yytext); return TYPE_VARCHAR; }

"AND"       { /* Λογικό ΚΑΙ */ printf("%s", yytext); return AND; }
"OR"        { /* Λογικό Ή */ printf("%s", yytext); return OR; }
"NOT"       { /* Λογικό ΟΧΙ */ printf("%s", yytext); return NOT; }
"IN"        { /* Λογικό ΜΕΣΑ ΣΕ */ printf("%s", yytext); return IN; }

"="         { /* Σύμβολο ΙΣΟΝ */ printf("%s", yytext); return EQUALS; }
"!="        { /* Σύμβολο ΔΙΑΦΟΡΟ */ printf("%s", yytext); return NOT_EQUALS; }
">="        { /* Μεγαλύτερο ή ίσο */ printf("%s", yytext); return GREATER_EQUAL; }
"<="        { /* Μικρότερο ή ίσο */ printf("%s", yytext); return LESS_EQUAL; }
">"         { /* Σκέτο Μεγαλύτερο */ printf("%s", yytext); return GREATER; }
"<"         { /* Σκέτο Μικρότερο */ printf("%s", yytext); return LESS; }

","         { /* Κόμμα */ printf("%s", yytext); return COMMA; }
";"         { /* Ερωτηματικό για το τέλος της πρότασης */ printf("%s", yytext); return SEMICOLON; }
"."         { /* Τελεία */ printf("%s", yytext); return DOT; }
"("         { /* Ανοιχτή παρένθεση */ printf("%s", yytext); return LPAREN; }
")"         { /* Κλειστή παρένθεση */ printf("%s", yytext); return RPAREN; }
"*"         { /* Αστεράκι για όλα τα παιχνίδια */ printf("%s", yytext); return ASTERISK; }

[0-9]+\.[0-9]+ { 
                /* Βρήκα δεκαδικό αριθμό (π.χ. 3.14), τον βάζω στο σακίδιο */
                printf("%s", yytext); 
                yylval.fval = atof(yytext); 
                return FLOAT_VAL; 
              }

[0-9]+         { 
                /* Βρήκα ολόκληρο αριθμό (π.χ. 45), τον βάζω στο σακίδιο */
                printf("%s", yytext); 
                yylval.ival = atoi(yytext); 
                return INT_VAL; 
              }

"'"[^']*"'"    { 
                /* Βρήκα λέξη μέσα σε εισαγωγικά (string), την αντιγράφω στο σακίδιο */
                printf("%s", yytext); 
                yylval.sval = strdup(yytext); 
                return STRING_VAL; 
              }

[a-zA-Z_][a-zA-Z0-9_]* { 
                /* Βρήκα ένα κανονικό όνομα, το βάζω στο σακίδιο */
                printf("%s", yytext); 
                yylval.sval = strdup(yytext); 
                return IDENTIFIER; 
              }

"--"[^\n]* { /* Σχόλιο μίας γραμμής: το τυπώνω αλλά δεν στέλνω τουβλάκι */ printf("%s", yytext); } 

"/*"            { /* Μπαίνω στο κρυφό δωμάτιο των σχολίων */ BEGIN(COMMENT); printf("%s", yytext); }
<COMMENT>"*/"   { /* Βγαίνω από το κρυφό δωμάτιο */ BEGIN(INITIAL); printf("%s", yytext); }
<COMMENT>\n     { /* Ανεβαίνω όροφο μέσα στο κρυφό δωμάτιο */ line_num++; printf("%s", yytext); }
<COMMENT>.      { /* Οτιδήποτε άλλο μέσα στο κρυφό δωμάτιο, απλά το τυπώνω */ printf("%s", yytext); }

[ \t\r]+       { /* Αγνοώ τον αέρα ανάμεσα στις λέξεις (κενά, tabs) */ printf("%s", yytext); } 
\n             { /* Αλλαγή γραμμής: ανεβαίνω όροφο στο κανονικό παιχνίδι */ printf("%s", yytext); line_num++; } 

.              { 
                /* Άγνωστος χαρακτήρας: βάζω τα κλάματα και σταματάω! */
                printf("%s", yytext); 
                fprintf(stderr, "\n\n[Λεκτικό Σφάλμα] Άγνωστος χαρακτήρας '%s' στη γραμμή %d\n", yytext, line_num); 
                exit(1); 
              }

%%