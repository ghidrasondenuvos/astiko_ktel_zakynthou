/* =========================================================================
   ΕΠΙΠΕΔΟ 1: ΒΙΒΛΙΟΘΗΚΕΣ ΚΑΙ ΓΕΝΙΚΕΣ ΔΗΛΩΣΕΙΣ
   ========================================================================= */
%{
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>
#include <windows.h>  
#undef IN

void yyerror(const char *s);
int yylex(void);
int line_num = 1; 
%}

/* =========================================================================
   ΕΠΙΠΕΔΟ 2: ΔΟΜΕΣ ΔΕΔΟΜΕΝΩΝ ΚΑΙ ΣΗΜΑΣΙΟΛΟΓΙΚΟΙ ΕΛΕΓΧΟΙ
   ========================================================================= */
%{
#define MAX_TABLES 50        
#define MAX_COLUMNS 50       
#define MAX_USED_COLUMNS 100 

/* Βοηθητική συνάρτηση για σύγκριση συμβολοσειρών χωρίς διάκριση πεζών/κεφαλαίων */
int icmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = *s1;
        char c2 = *s2;
        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
        if (c1 != c2) return c1 - c2;
        s1++; s2++;
    }
    char c1 = *s1; char c2 = *s2;
    if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
    if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
    return c1 - c2;
}

/* Ορισμός δομών για τη διαχείριση της βάσης δεδομένων */
typedef struct {
    char name[50]; 
    int type;      // 1: INT, 2: FLOAT, 3: VARCHAR
} Column;

typedef struct {
    char name[50];             
    Column columns[MAX_COLUMNS];
    int col_count;             
} Table;

Table symbol_table[MAX_TABLES];
int table_count = 0; 

char current_table_name[50];
Column temp_columns[MAX_COLUMNS];  
int temp_col_count = 0;

typedef struct {
    char table_name[50]; 
    char alias_name[50]; 
} ActiveTable;

ActiveTable active_tables[MAX_TABLES];
int active_table_count = 0; 

typedef struct {
    char table_or_alias[50];
    char col_name[50];       
    int line;
} UsedColumn;

UsedColumn used_columns[MAX_USED_COLUMNS];
int used_column_count = 0; 
int current_in_types[100];
int current_in_count = 0;

/* Συναρτήσεις αναζήτησης στον πίνακα συμβόλων */
int find_table(const char *name) {
    for (int i = 0; i < table_count; i++) {
        if (icmp(symbol_table[i].name, name) == 0) return i;
    }
    return -1; 
}

int find_column_in_table(int table_idx, const char *col_name) {
    if (table_idx < 0 || table_idx >= table_count) return -1;
    for (int i = 0; i < symbol_table[table_idx].col_count; i++) {
        if (icmp(symbol_table[table_idx].columns[i].name, col_name) == 0) {
            return symbol_table[table_idx].columns[i].type;
        }
    }
    return -1;
}

int resolve_active_table(const char *name_or_alias) {
    for (int i = 0; i < active_table_count; i++) {
        if (icmp(active_tables[i].alias_name, name_or_alias) == 0 ||
            icmp(active_tables[i].table_name, name_or_alias) == 0) {
            return find_table(active_tables[i].table_name);
        }
    }
    return -1;
}
%}

/* =========================================================================
   ΕΠΙΠΕΔΟ 3: ΟΡΙΣΜΟΣ ΤΥΠΩΝ ΚΑΙ TOKENS
   ========================================================================= */
%code requires {
    typedef struct {
        char table_or_alias[50];
        char col_name[50];
    } ColumnRef;
}

%union {
    int ival;
    float fval;      
    char *sval;
    ColumnRef col;   
    int type_val;
}

%token CREATE TABLE SELECT FROM WHERE GROUP BY ORDER LIMIT JOIN ON AS
%token TYPE_INT TYPE_FLOAT TYPE_VARCHAR
%token AND OR NOT IN
%token EQUALS NOT_EQUALS GREATER_EQUAL LESS_EQUAL GREATER LESS
%token COMMA SEMICOLON DOT LPAREN RPAREN ASTERISK

%token <ival> INT_VAL
%token <fval> FLOAT_VAL
%token <sval> STRING_VAL IDENTIFIER

%type <col> column_item
%type <type_val> data_type literal

%left OR
%left AND
%right NOT

%%

/* =========================================================================
   ΕΠΙΠΕΔΟ 4: ΓΡΑΜΜΑΤΙΚΗ ΥΨΗΛΟΥ ΕΠΙΠΕΔΟΥ
   ========================================================================= */
program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
    create_table_stmt
    | select_stmt
    ;

/* =========================================================================
   ΕΠΙΠΕΔΟ 5: ΥΛΟΠΟΙΗΣΗ ΕΝΤΟΛΗΣ CREATE TABLE
   ========================================================================= */
create_table_stmt:
    CREATE TABLE IDENTIFIER {
        if (find_table($3) != -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' υπάρχει ήδη.\n", line_num, $3);
            exit(1); 
        }
        strcpy(current_table_name, $3); 
        temp_col_count = 0;
        free($3);                        
    } LPAREN create_col_list RPAREN SEMICOLON {
        strcpy(symbol_table[table_count].name, current_table_name);
        symbol_table[table_count].col_count = temp_col_count;
        for (int i = 0; i < temp_col_count; i++) {
            symbol_table[table_count].columns[i] = temp_columns[i];
        }
        table_count++; 
        printf("\n[OK] Δημιουργήθηκε ο πίνακας '%s'.\n\n", current_table_name);
    }
    ;

create_col_list:
    create_col_def
    | create_col_list COMMA create_col_def
    ;

create_col_def:
    IDENTIFIER data_type {
        for (int i = 0; i < temp_col_count; i++) {
            if (icmp(temp_columns[i].name, $1) == 0) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' ορίζεται δύο φορές στον πίνακα '%s'.\n", line_num, $1, current_table_name);
                exit(1);
            }
        }
        strcpy(temp_columns[temp_col_count].name, $1);
        temp_columns[temp_col_count].type = $2;
        temp_col_count++;
        free($1);
    }
    ;

data_type:
    TYPE_INT { $$ = 1; }
    | TYPE_FLOAT { $$ = 2; }
    | TYPE_VARCHAR LPAREN INT_VAL RPAREN {
        if ($3 <= 0) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Το μέγεθος του VARCHAR πρέπει να είναι > 0.\n", line_num);
            exit(1);
        }
        $$ = 3;
    }
    ;

/* =========================================================================
   ΕΠΙΠΕΔΟ 6: ΥΛΟΠΟΙΗΣΗ SELECT ΚΑΙ ΔΙΑΧΕΙΡΙΣΗ ΠΙΝΑΚΩΝ
   ========================================================================= */
select_stmt:
    SELECT { 
        used_column_count = 0; 
        active_table_count = 0; 
    } 
    select_col_list FROM table_ref join_clause_list where_clause group_by_clause order_by_clause limit_clause SEMICOLON {
        
        for (int i = 0; i < used_column_count; i++) {
            char *prefix = used_columns[i].table_or_alias;
            char *cname = used_columns[i].col_name;       
            int line = used_columns[i].line;              
            int t_idx = -1;
            
            if (strlen(prefix) > 0) {
                int match_idx = -1;
                for (int j = 0; j < active_table_count; j++) {
                    if (icmp(active_tables[j].alias_name, prefix) == 0) {
                        match_idx = j;
                        break;
                    }
                }
                
                if (match_idx == -1) {
                    for (int j = 0; j < active_table_count; j++) {
                        if (icmp(active_tables[j].table_name, prefix) == 0) {
                            if (icmp(active_tables[j].table_name, active_tables[j].alias_name) != 0) {
                                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Πρέπει να χρησιμοποιηθεί το alias '%s' αντί για το όνομα του πίνακα '%s'.\n", line, active_tables[j].alias_name, prefix);
                                exit(1);
                            }
                            match_idx = j;
                            break;
                        }
                    }
                }
                
                if (match_idx == -1) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας ή το alias '%s' δεν συμμετέχει στο ερώτημα.\n", line, prefix);
                    exit(1);
                }
                t_idx = find_table(active_tables[match_idx].table_name);
            } else {
                int matches = 0;
                int requires_alias = 0;
                char req_alias_name[50] = "";
                for (int j = 0; j < active_table_count; j++) {
                    int tmp = find_table(active_tables[j].table_name);
                    if (find_column_in_table(tmp, cname) != -1) {
                        t_idx = tmp;
                        matches++;
                        if (icmp(active_tables[j].table_name, active_tables[j].alias_name) != 0) {
                            requires_alias = 1;
                            strcpy(req_alias_name, active_tables[j].alias_name);
                        }
                    }
                }
                
                if (matches == 0) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' δεν ανήκει στους επιλεγμένους πίνακες.\n", line, cname);
                    exit(1);
                }
                if (matches > 1) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι ασαφής.\n", line, cname);
                    exit(1);
                }
                if (requires_alias) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' πρέπει υποχρεωτικά να έχει το πρόθεμα του alias '%s'.\n", line, cname, req_alias_name);
                    exit(1);
                }
            }
            
            if (find_column_in_table(t_idx, cname) == -1) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' δεν υπάρχει στον πίνακα '%s'.\n", line, cname, symbol_table[t_idx].name);
                exit(1);
            }
        }
        printf("\n[OK] Επιτυχής αναγνώριση και έλεγχος εντολής SELECT.\n\n");
    }
    ;

select_col_list:
    ASTERISK
    | column_list
    ;

column_list:
    column_item
    | column_list COMMA column_item
    ;

column_item:
    IDENTIFIER {
        strcpy($$.table_or_alias, "");
        strcpy($$.col_name, $1);
        strcpy(used_columns[used_column_count].table_or_alias, "");
        strcpy(used_columns[used_column_count].col_name, $1);
        used_columns[used_column_count].line = line_num;
        used_column_count++;
        free($1);
    }
    | IDENTIFIER DOT IDENTIFIER {
        strcpy($$.table_or_alias, $1);
        strcpy($$.col_name, $3);
        strcpy(used_columns[used_column_count].table_or_alias, $1);
        strcpy(used_columns[used_column_count].col_name, $3);
        used_columns[used_column_count].line = line_num;
        used_column_count++;
        free($1); free($3);
    }
    ;

table_ref:
    IDENTIFIER {
        int idx = find_table($1);
        if (idx == -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' δεν έχει δημιουργηθεί.\n", line_num, $1);
            exit(1);
        }
        strcpy(active_tables[active_table_count].table_name, $1);
        strcpy(active_tables[active_table_count].alias_name, $1);
        active_table_count++;
        free($1);
    }
    | IDENTIFIER AS IDENTIFIER {
        int idx = find_table($1);
        if (idx == -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' δεν έχει δημιουργηθεί.\n", line_num, $1);
            exit(1);
        }
        strcpy(active_tables[active_table_count].table_name, $1);
        strcpy(active_tables[active_table_count].alias_name, $3);
        active_table_count++;
        free($1); free($3);
    }
    | IDENTIFIER IDENTIFIER {
        int idx = find_table($1);
        if (idx == -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' δεν έχει δημιουργηθεί.\n", line_num, $1);
            exit(1);
        }
        strcpy(active_tables[active_table_count].table_name, $1);
        strcpy(active_tables[active_table_count].alias_name, $2);
        active_table_count++;
        free($1); free($2);
    }
    ;

/* =========================================================================
   ΕΠΙΠΕΔΟ 7: ΣΥΝΘΗΚΕΣ, ΦΙΛΤΡΑΡΙΣΜΑ ΚΑΙ ΛΟΙΠΕΣ ΛΕΙΤΟΥΡΓΙΕΣ
   ========================================================================= */
join_clause_list:
    %empty
    | join_clause_list join_clause
    ;

join_clause:
    JOIN table_ref ON column_item EQUALS column_item
    ;

where_clause:
    %empty
    | WHERE condition
    ;

condition:
    column_item rel_op literal {
        int t_idx = -1;
        if (strlen($1.table_or_alias) > 0) {
            t_idx = resolve_active_table($1.table_or_alias);
        } else {
            for (int j = 0; j < active_table_count; j++) {
                int tmp = find_table(active_tables[j].table_name);
                if (find_column_in_table(tmp, $1.col_name) != -1) t_idx = tmp;
            }
        }
        
        if (t_idx != -1) {
            int col_type = find_column_in_table(t_idx, $1.col_name);
            int lit_type = $3;                                      
            if (col_type == 1 && lit_type != 1) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι INT.\n", line_num, $1.col_name);
                exit(1);
            }
            if (col_type == 2 && (lit_type != 1 && lit_type != 2)) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι FLOAT.\n", line_num, $1.col_name);
                exit(1);
            }
            if (col_type == 3 && lit_type != 3) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι VARCHAR.\n", line_num, $1.col_name);
                exit(1);
            }
        }
    }
    | column_item IN LPAREN literal_list RPAREN {
        int t_idx = -1;
        if (strlen($1.table_or_alias) > 0) t_idx = resolve_active_table($1.table_or_alias);
        else {
            for (int j = 0; j < active_table_count; j++) {
                int tmp = find_table(active_tables[j].table_name);
                if (find_column_in_table(tmp, $1.col_name) != -1) t_idx = tmp;
            }
        }
        
        if (t_idx != -1) {
            int col_type = find_column_in_table(t_idx, $1.col_name);
            for (int k = 0; k < current_in_count; k++) {
                int lit_type = current_in_types[k];
                if ((col_type == 1 && lit_type != 1) || 
                    (col_type == 2 && (lit_type != 1 && lit_type != 2)) || 
                    (col_type == 3 && lit_type != 3)) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ασύμβατος τύπος στη λίστα του IN για τη στήλη '%s'.\n", line_num, $1.col_name);
                    exit(1);
                }
            }
        }
    }
    | column_item NOT IN LPAREN literal_list RPAREN {
        int t_idx = -1;
        if (strlen($1.table_or_alias) > 0) t_idx = resolve_active_table($1.table_or_alias);
        else {
            for (int j = 0; j < active_table_count; j++) {
                int tmp = find_table(active_tables[j].table_name);
                if (find_column_in_table(tmp, $1.col_name) != -1) t_idx = tmp;
            }
        }
        
        if (t_idx != -1) {
            int col_type = find_column_in_table(t_idx, $1.col_name);
            for (int k = 0; k < current_in_count; k++) {
                int lit_type = current_in_types[k];
                if ((col_type == 1 && lit_type != 1) || 
                    (col_type == 2 && (lit_type != 1 && lit_type != 2)) || 
                    (col_type == 3 && lit_type != 3)) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ασύμβατος τύπος στη λίστα του NOT IN για τη στήλη '%s'.\n", line_num, $1.col_name);
                    exit(1);
                }
            }
        }
    }
    | condition AND condition 
    | condition OR condition  
    | NOT condition           
    | LPAREN condition RPAREN 
    ;

rel_op:
    EQUALS | NOT_EQUALS | GREATER_EQUAL |
    LESS_EQUAL | GREATER | LESS
    ;

literal:
    INT_VAL { $$ = 1; }
    | FLOAT_VAL { $$ = 2; }
    | STRING_VAL { $$ = 3; free($1); } 
    ;

literal_list:
    literal {
        current_in_count = 0;
        current_in_types[current_in_count++] = $1; 
    }
    | literal_list COMMA literal {
        current_in_types[current_in_count++] = $3; 
    }
    ;

group_by_clause:
    %empty
    | GROUP BY column_list
    ;

order_by_clause:
    %empty
    | ORDER BY column_list
    ;

limit_clause:
    %empty
    | LIMIT INT_VAL {
        if ($2 <= 0) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Το όριο LIMIT πρέπει να είναι > 0.\n", line_num);
            exit(1);
        }
    }
    ;

/* =========================================================================
   ΕΠΙΠΕΔΟ 8: ΛΕΙΤΟΥΡΓΙΑ ΣΦΑΛΜΑΤΩΝ ΚΑΙ MAIN
   ========================================================================= */
%%

void yyerror(const char *s) {
    fprintf(stderr, "\n\n[Συντακτικό Σφάλμα] στη γραμμή %d: %s\n", line_num, s);
    exit(1);
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    if (argc < 2) {
        fprintf(stderr, "Χρήση: %s <όνομα_αρχείου>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Σφάλμα: Αδυναμία ανοίγματος του αρχείου '%s'\n", argv[1]);
        return 1;
    }

    extern FILE *yyin;
    yyin = file;
    printf("--- Έναρξη Ανάλυσης Αρχείου ---\n");
    yyparse(); 
    printf("--- Τέλος Ανάλυσης (Όλα OK!) ---\n");
    fclose(file); 
    return 0;     
}