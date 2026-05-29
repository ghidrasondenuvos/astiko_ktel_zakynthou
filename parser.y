%{
/* Φωνάζουμε 3 έξυπνους φίλους μας που ξέρουν να κάνουν ειδικά πράγματα: */
#include <stdio.h>   // Ο φίλος που ξέρει να γράφει και να διαβάζει μηνύματα στην οθόνη.
#include <stdlib.h>  // Ο φίλος που ξέρει να μας δίνει άδεια κουτιά στη μνήμη για να βάζουμε πράγματα.
#include <string.h>  // Ο φίλος που είναι ξεφτέρης στο να συγκρίνει λέξεις.

// Λέμε στο ρομπότ ότι θα έχουμε μια φωνή για να φωνάζουμε "Λάθος!" αν κάτι πάει στραβά.
void yyerror(const char *s);
// Λέμε στο ρομπότ ότι υπάρχει ένα βοηθάκι που του δίνει μία-μία τις λέξεις.
int yylex(void);

// Ένας μετρητής που ξεκινάει από το 1 για να ξέρουμε σε ποια γραμμή του βιβλίου διαβάζουμε.
int line_num = 1; 

/* =========================================================================
   ΔΟΜΕΣ ΔΕΔΟΜΕΝΩΝ & ΠΙΝΑΚΑΣ ΣΥΜΒΟΛΩΝ (ΤΟ ΜΕΓΑΛΟ ΝΤΟΥΛΑΠΙ ΜΕ ΤΑ ΠΑΙΧΝΙΔΙΑ)
   ========================================================================= */
#define MAX_TABLES 50        // Κανόνας: Μπορούμε να έχουμε το πολύ 50 μεγάλα κουτιά (πίνακες).
#define MAX_COLUMNS 50       // Κανόνας: Κάθε μεγάλο κουτί χωράει το πολύ 50 μικρά κουτάκια (στήλες).
#define MAX_USED_COLUMNS 100 // Κανόνας: Μπορούμε να θυμόμαστε μέχρι 100 αυτοκόλλητα μαζί.

// Φτιάχνουμε ένα μαγικό μεγεθυντικό φακό για να βλέπουμε αν δύο λέξεις είναι ίδιες...
int icmp(const char *s1, const char *s2) {
    // ...ακόμα κι αν η μία έχει μεγάλα γράμματα και η άλλη μικρά!
    while (*s1 && *s2) {
        char c1 = *s1;
        char c2 = *s2;
        // Αν είναι κεφαλαίο γράμμα, το κάνουμε μικρό στο μυαλό μας.
        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
        // Αν βρούμε γράμμα που δεν ταιριάζει, σταματάμε.
        if (c1 != c2) return c1 - c2;
        s1++; s2++;
    }
    char c1 = *s1; char c2 = *s2;
    if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
    if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
    return c1 - c2;
}

// Σχεδιάζουμε πώς είναι μια "Στήλη": Έχει ένα όνομα (sticker) και έναν τύπο (τι παιχνίδι χωράει).
typedef struct {
    char name[50]; // Το όνομα της στήλης.
    int type;      // 1 για αριθμούς, 2 για δεκαδικούς, 3 για γράμματα.
} Column;

// Σχεδιάζουμε πώς είναι ένας "Πίνακας": Ένα μεγάλο κουτί που έχει όνομα και πολλά μικρά κουτάκια μέσα.
typedef struct {
    char name[50];             // Το όνομα του πίνακα.
    Column columns[MAX_COLUMNS]; // Τα μικρά κουτάκια (στήλες) που κρύβει μέσα του.
    int col_count;             // Πόσα κουτάκια βάλαμε τελικά μέσα.
} Table;

// Αυτό είναι το μεγάλο μας Ντουλάπι! Εδώ θα κλειδώνουμε όλους τους πίνακες που φτιάχνουμε.
Table symbol_table[MAX_TABLES];
int table_count = 0; // Στην αρχή το ντουλάπι είναι άδειο (0 πίνακες).

// Πρόχειρα χαρτιά για να σημειώνουμε πράγματα την ώρα που φτιάχνουμε έναν πίνακα:
char current_table_name[50];       // Το όνομα του πίνακα που φτιάχνουμε ΤΩΡΑ.
Column temp_columns[MAX_COLUMNS];  // Οι στήλες που μαζεύουμε πρόχειρα.
int temp_col_count = 0;            // Πόσες στήλες μαζέψαμε προσωρινά.

// Σχεδιάζουμε ένα κουτάκι "Ενεργός Πίνακας": Μας λέει ποιον πίνακα χρησιμοποιούμε τώρα και ποιο είναι το κρυφό του όνομα (Alias).
typedef struct {
    char table_name[50]; // Το αληθινό όνομα.
    char alias_name[50]; // Το χαϊδευτικό/σύντομο όνομα.
} ActiveTable;

// Μια λίστα για να βλέπουμε ποιους πίνακες έχουμε ανοίξει πάνω στο χαλί για να παίξουμε.
ActiveTable active_tables[MAX_TABLES];
int active_table_count = 0; // Στην αρχή κανένας πίνακας δεν είναι ανοιχτός.

// Σχεδιάζουμε μια λίστα για να γράφουμε ποιες στήλες ζήτησε το παιδί.
typedef struct {
    char table_or_alias[50]; // Από ποιο κουτί είναι η στήλη.
    char col_name[50];       // Πώς τη λένε τη στήλη.
    int line;                // Σε ποια γραμμή τη βρήκαμε.
} UsedColumn;

// Εδώ αποθηκεύουμε όλες τις στήλες που χρησιμοποιούνται για να τις ελέγξουμε στο τέλος.
UsedColumn used_columns[MAX_USED_COLUMNS];
int used_column_count = 0; // Ξεκινάει από το μηδέν.

// Πρόχειρος κουμπαράς για να κρατάει τους τύπους δεδομένων όταν ελέγχουμε τη λίστα "IN".
int current_in_types[100];
int current_in_count = 0;

/* --- ΜΑΓΙΚΕΣ ΣΥΝΑΡΤΗΣΕΙΣ ΑΝΑΖΗΤΗΣΗΣ --- */

// Ψάχνει στο μεγάλο ντουλάπι να βρει αν υπάρχει ο πίνακας με αυτό το όνομα.
int find_table(const char *name) {
    for (int i = 0; i < table_count; i++) {
        if (icmp(symbol_table[i].name, name) == 0) return i; // Τον βρήκαμε!
    }
    return -1; // Δεν υπάρχει τέτοιος πίνακας στο ντουλάπι.
}

// Ψάχνει μέσα σε ένα συγκεκριμένο μεγάλο κουτί να δει αν υπάρχει το μικρό κουτάκι (στήλη) που θέλουμε.
int find_column_in_table(int table_idx, const char *col_name) {
    if (table_idx < 0 || table_idx >= table_count) return -1;
    for (int i = 0; i < symbol_table[table_idx].col_count; i++) {
        if (icmp(symbol_table[table_idx].columns[i].name, col_name) == 0) {
            return symbol_table[table_idx].columns[i].type; // Τη βρήκαμε και επιστρέφουμε τον τύπο της!
        }
    }
    return -1; // Δεν υπάρχει αυτή η στήλη εκεί μέσα.
}

// Κοιτάζει τους πίνακες που έχουμε ανοιχτούς στο χαλί και μας λέει ποιο είναι το αληθινό όνομα πίσω από ένα χαϊδευτικό (alias).
int resolve_active_table(const char *name_or_alias) {
    for (int i = 0; i < active_table_count; i++) {
        if (icmp(active_tables[i].alias_name, name_or_alias) == 0 ||
            icmp(active_tables[i].table_name, name_or_alias) == 0) {
            return find_table(active_tables[i].table_name); // Επιστρέφει τη θέση του αληθινού πίνακα.
        }
    }
    return -1;
}
%}

/* Λέμε στο ρομπότ να φτιάξει μια ειδική ταυτότητα για τις στήλες ώστε να μην μπερδεύεται μετά. */
%code requires {
    typedef struct {
        char table_or_alias[50];
        char col_name[50];
    } ColumnRef;
}

/* =========================================================================
   Ο ΜΑΓΙΚΟΣ ΣΑΚΟΣ (UNION) ΚΑΙ ΤΑ ΤΟΥΒΛΑΚΙΑ (TOKENS)
   ========================================================================= */
%union {
    int ival;        // Ο σάκος μπορεί να κρατήσει έναν κανονικό αριθμό.
    float fval;      // Ή έναν αριθμό με τελεία (δεκαδικό).
    char *sval;      // Ή μια λέξη.
    ColumnRef col;   // Ή μια στήλη με το όνομα του πίνακα της.
    int type_val;    // Ή έναν κωδικό τύπου.
}

/* Εδώ δηλώνουμε όλες τις λέξεις-κλειδιά που μοιάζουν με ειδικά τουβλάκια LEGO στο παιχνίδι μας: */
%token CREATE TABLE SELECT FROM WHERE GROUP BY ORDER LIMIT JOIN ON AS
%token TYPE_INT TYPE_FLOAT TYPE_VARCHAR
%token AND OR NOT IN
%token EQUALS NOT_EQUALS GREATER_EQUAL LESS_EQUAL GREATER LESS
%token COMMA SEMICOLON DOT LPAREN RPAREN ASTERISK

/* Αυτά τα τουβλάκια φέρνουν μαζί τους και ένα δώρο (μια τιμή) μέσα από τον σάκο: */
%token <ival> INT_VAL
%token <fval> FLOAT_VAL
%token <sval> STRING_VAL IDENTIFIER

/* Ορίζουμε ποιοι κανόνες επιστρέφουν τι είδους πράγματα: */
%type <col> column_item
%type <type_val> data_type literal

/* Λέμε στο ρομπότ ποια λογικά τουβλάκια είναι πιο δυνατά από τα άλλα για να μην μπερδευτεί. */
%left OR
%left AND
%right NOT

%%

/* =========================================================================
   ΟΙ ΚΑΝΟΝΕΣ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ (ΓΡΑΜΜΑΤΙΚΗ BNF)
   ========================================================================= */

// Το "πρόγραμμα" είναι απλά μια στοίβα από εντολές.
program:
    statements
    ;

// Μπορεί να έχουμε μία εντολή ή πολλές εντολές μαζί, τη μία κάτω από την άλλη.
statements:
    statement
    | statements statement
    ;

// Κάθε εντολή μπορεί να είναι είτε "Φτιάξε Κουτί" (CREATE) είτε "Διάλεξε Παιχνίδια" (SELECT).
statement:
    create_table_stmt
    | select_stmt
    ;

/* --- ΚΑΝΟΝΑΣ: ΦΤΙΑΞΕ ΚΟΥΤΙ (CREATE TABLE) --- */
create_table_stmt:
    CREATE TABLE IDENTIFIER {
        // Μόλις δούμε το όνομα του πίνακα, ελέγχουμε αν υπάρχει ήδη στο ντουλάπι.
        if (find_table($3) != -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' υπάρχει ήδη.\n", line_num, $3);
            exit(1); // Αν υπάρχει ήδη, το ρομπότ θυμώνει και σταματάει το παιχνίδι!
        }
        strcpy(current_table_name, $3); // Σημειώνουμε το όνομα του νέου πίνακα.
        temp_col_count = 0;              // Μηδενίζουμε τις πρόχειρες στήλες.
        free($3);                        // Πετάμε το χαρτάκι που δεν χρειαζόμαστε πια.
    } LPAREN create_col_list RPAREN SEMICOLON {
        // Μόλις κλείσει η παρένθεση και μπει το ερωτηματικό (;), βάζουμε τον πίνακα στο μεγάλο ντουλάπι!
        strcpy(symbol_table[table_count].name, current_table_name);
        symbol_table[table_count].col_count = temp_col_count;
        for (int i = 0; i < temp_col_count; i++) {
            symbol_table[table_count].columns[i] = temp_columns[i];
        }
        table_count++; // Τώρα έχουμε έναν πίνακα παραπάνω στο ντουλάπι μας!
        printf("\n[OK] Δημιουργήθηκε ο πίνακας '%s'.\n\n", current_table_name);
    }
    ;

// Η λίστα στηλών είναι είτε μία στήλη είτε πολλές στήλες που χωρίζονται με κόμμα (,).
create_col_list:
    create_col_def
    | create_col_list COMMA create_col_def
    ;

// Πώς ορίζεται μια στήλη: Έχει όνομα και τύπο.
create_col_def:
    IDENTIFIER data_type {
        // Ελέγχουμε αν βάλαμε κατά λάθος δύο φορές την ίδια στήλη στο ίδιο κουτί!
        for (int i = 0; i < temp_col_count; i++) {
            if (icmp(temp_columns[i].name, $1) == 0) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' ορίζεται δύο φορές στον πίνακα '%s'.\n", line_num, $1, current_table_name);
                exit(1); // Ζαβολιά! Το ρομπότ σταματάει.
            }
        }
        // Αν όλα είναι καλά, την κρατάμε προσωρινά.
        strcpy(temp_columns[temp_col_count].name, $1);
        temp_columns[temp_col_count].type = $2;
        temp_col_count++;
        free($1);
    }
    ;

// Τι μπορεί να κρύβει μέσα του ένα κουτάκι:
data_type:
    TYPE_INT { $$ = 1; }     // Κωδικός 1: Μόνο ολόκληρους αριθμούς (π.χ. 5 στρατιωτάκια).
    | TYPE_FLOAT { $$ = 2; } // Κωδικός 2: Αριθμούς με τελεία (π.χ. 2.5 κιλά Lego).
    | TYPE_VARCHAR LPAREN INT_VAL RPAREN {
        // Κωδικός 3: Λέξεις. Αλλά το μέγεθος της λέξης πρέπει να είναι θετικός αριθμός!
        if ($3 <= 0) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Το μέγεθος του VARCHAR πρέπει να είναι > 0.\n", line_num);
            exit(1);
        }
        $$ = 3;
    }
    ;

/* --- ΚΑΝΟΝΑΣ: ΔΙΑΛΕΞΕ ΠΑΙΧΝΙΔΙΑ (SELECT) --- */
select_stmt:
    SELECT { 
        // Μόλις ξεκινήσει το SELECT, καθαρίζουμε τις λίστες μας για να γράψουμε καινούργια πράγματα.
        used_column_count = 0; 
        active_table_count = 0; 
    } 
    select_col_list FROM table_ref join_clause_list where_clause group_by_clause order_by_clause limit_clause SEMICOLON {
        
        /* ΤΩΡΑ ΤΟ ΡΟΜΠΟΤ ΚΑΝΕΙ ΤΟΝ ΜΕΓΑΛΟ ΕΛΕΓΧΟ ΣΕ ΟΛΕΣ ΤΙΣ ΣΤΗΛΕΣ ΠΟΥ ΖΗΤΗΣΑΜΕ! */
        for (int i = 0; i < used_column_count; i++) {
            char *prefix = used_columns[i].table_or_alias; // Το όνομα του πίνακα/alias που γράψαμε μπροστά από την τελεία.
            char *cname = used_columns[i].col_name;       // Το όνομα της στήλης.
            int line = used_columns[i].line;              // Η γραμμή που τη βρήκαμε.
            int t_idx = -1;                               // Η θέση του πίνακα στο ντουλάπι.
            
            if (strlen(prefix) > 0) {
                // Αν γράψαμε πρόθεμα (π.χ. s.gpa), ψάχνουμε να βρούμε αν αυτό το χαϊδευτικό (alias) υπάρχει στο χαλί μας.
                int match_idx = -1;
                for (int j = 0; j < active_table_count; j++) {
                    if (icmp(active_tables[j].alias_name, prefix) == 0) {
                        match_idx = j;
                        break;
                    }
                }
                
                // Αν δεν το βρούμε ως alias, κοιτάμε αν το παιδί χρησιμοποίησε το αληθινό όνομα του πίνακα, ενώ είχε δώσει alias!
                if (match_idx == -1) {
                    for (int j = 0; j < active_table_count; j++) {
                        if (icmp(active_tables[j].table_name, prefix) == 0) {
                            if (icmp(active_tables[j].table_name, active_tables[j].alias_name) != 0) {
                                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Πρέπει να χρησιμοποιηθεί το alias '%s' αντί για το όνομα του πίνακα '%s'.\n", line, active_tables[j].alias_name, prefix);
                                exit(1); // Λάθος! Αφού συμφωνήσαμε να το λέμε με το χαϊδευτικό του!
                            }
                            match_idx = j;
                            break;
                        }
                    }
                }
                
                if (match_idx == -1) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας ή το alias '%s' δεν συμμετέχει στο ερώτημα.\n", line, prefix);
                    exit(1); // Αυτός ο πίνακας δεν είναι καν ανοιχτός στο χαλί!
                }
                t_idx = find_table(active_tables[match_idx].table_name);
            } else {
                // Αν γράψαμε τη στήλη σκέτη (χωρίς τελεία, π.χ. gpa), το ρομπότ ψάχνει σε όλους τους ανοιχτούς πίνακες να τη βρει.
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
                    exit(1); // Δεν υπάρχει αυτή η στήλη σε κανέναν ανοιχτό πίνακα.
                }
                if (matches > 1) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι ασαφής (υπάρχει σε πάνω από έναν πίνακα).\n", line, cname);
                    exit(1); // Μπέρδεμα! Υπάρχει σε δύο πίνακες και το ρομπότ δεν ξέρει ποια από τις δύο εννοούμε!
                }
                if (requires_alias) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' πρέπει υποχρεωτικά να έχει το πρόθεμα του alias '%s'.\n", line, cname, req_alias_name);
                    exit(1); // Κανόνας της άσκησης: Αν βάλαμε alias, πρέπει να το χρησιμοποιούμε πάντα!
                }
            }
            
            // Τελικός έλεγχος: Υπάρχει πράγματι αυτή η στήλη μέσα στο μεγάλο κουτί στο ντουλάπι;
            if (find_column_in_table(t_idx, cname) == -1) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' δεν υπάρχει στον πίνακα '%s'.\n", line, cname, symbol_table[t_idx].name);
                exit(1);
            }
        }
        
        printf("\n[OK] Επιτυχής αναγνώριση και έλεγχος εντολής SELECT.\n\n");
    }
    ;

// Στο SELECT μπορούμε να ζητήσουμε είτε ένα αστεράκι (*) που σημαίνει "όλα τα παιχνίδια", είτε μια συγκεκριμένη λίστα.
select_col_list:
    ASTERISK
    | column_list
    ;

// Λίστα από στήλες χωρισμένες με κόμμα.
column_list:
    column_item
    | column_list COMMA column_item
    ;

// Μια στήλη μπορεί να γραφτεί είτε σκέτη (id) είτε με τον πίνακα της μπροστά (Students.id).
column_item:
    IDENTIFIER {
        strcpy($$.table_or_alias, "");
        strcpy($$.col_name, $1);
        
        // Τη γράφουμε στη λίστα για να την ελέγξει το ρομπότ στο τέλος.
        strcpy(used_columns[used_column_count].table_or_alias, "");
        strcpy(used_columns[used_column_count].col_name, $1);
        used_columns[used_column_count].line = line_num;
        used_column_count++;
        free($1);
    }
    | IDENTIFIER DOT IDENTIFIER {
        strcpy($$.table_or_alias, $1);
        strcpy($$.col_name, $3);
        
        // Τη γράφουμε στη λίστα μαζί με το πρόθεμά της.
        strcpy(used_columns[used_column_count].table_or_alias, $1);
        strcpy(used_columns[used_column_count].col_name, $3);
        used_columns[used_column_count].line = line_num;
        used_column_count++;
        free($1); free($3);
    }
    ;

// Πώς ανοίγουμε έναν πίνακα μετά το FROM:
table_ref:
    IDENTIFIER {
        int idx = find_table($1);
        if (idx == -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' δεν έχει δημιουργηθεί.\n", line_num, $1);
            exit(1); // Πάμε να παίξουμε με ένα κουτί που δεν έχουμε φτιάξει ποτέ! Λάθος!
        }
        strcpy(active_tables[active_table_count].table_name, $1);
        strcpy(active_tables[active_table_count].alias_name, $1);
        active_table_count++;
        free($1);
    }
    | IDENTIFIER AS IDENTIFIER {
        // Αν πούμε: FROM Students AS s, τότε το αληθινό είναι "Students" και το χαϊδευτικό είναι "s".
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
        // Το ίδιο με το από πάνω, αλλά χωρίς τη λέξη AS (π.χ. FROM Students s).
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

// Μπορεί να ενώσουμε πολλούς πίνακες μαζί με JOIN, ή κανέναν (κενό).
join_clause_list:
    /* κενό */
    | join_clause_list join_clause
    ;

// Το JOIN ενώνει έναν νέο πίνακα, κοιτάζοντας αν δύο μικρά κουτάκια είναι ίσα (ON s.id = e.id).
join_clause:
    JOIN table_ref ON column_item EQUALS column_item
    ;

// Ο όρος WHERE είναι προαιρετικός (μπορεί να μην υπάρχει - κενό).
where_clause:
    /* κενό */
    | WHERE condition
    ;

// Οι συνθήκες που βάζουμε για να φιλτράρουμε τα παιχνίδια:
condition:
    column_item rel_op literal {
        /* ΕΛΕΓΧΟΣ ΣΥΜΒΑΤΟΤΗΤΑΣ: Ταιριάζουν τα παιχνίδια; */
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
            int col_type = find_column_in_table(t_idx, $1.col_name); // Τι τύπος είναι η στήλη.
            int lit_type = $3;                                      // Τι τύπος είναι η τιμή που δώσαμε.
            
            // Αν η στήλη θέλει ολόκληρο αριθμό (INT) και εμείς της δώσουμε γράμματα, το ρομπότ φωνάζει!
            if (col_type == 1 && lit_type != 1) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι INT.\n", line_num, $1.col_name);
                exit(1);
            }
            // Αν η στήλη θέλει δεκαδικό (FLOAT) και της δώσουμε γράμματα, πάλι σφάλμα!
            if (col_type == 2 && (lit_type != 1 && lit_type != 2)) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι FLOAT.\n", line_num, $1.col_name);
                exit(1);
            }
            // Αν η στήλη θέλει λέξη (VARCHAR) και της δώσουμε αριθμό, το ρομπότ σταματάει το παιχνίδι!
            if (col_type == 3 && lit_type != 3) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι VARCHAR.\n", line_num, $1.col_name);
                exit(1);
            }
        }
    }
    | column_item IN LPAREN literal_list RPAREN {
        /* Έλεγχος τύπων για την εντολή IN (να είναι όλα τα στοιχεία μέσα στην παρένθεση ίδια με τη στήλη) */
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
        /* Το ίδιο με το IN, αλλά για το NOT IN */
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
    | condition AND condition // Μπορούμε να ενώσουμε συνθήκες με το τουβλάκι AND (ΚΑΙ αυτό ΚΑΙ εκείνο).
    | condition OR condition  // Ή με το τουβλάκι OR (Ή αυτό Ή εκείνο).
    | NOT condition           // Ή να τις αντιστρέψουμε με το NOT (ΟΧΙ αυτό).
    | LPAREN condition RPAREN // Μπορούμε να βάλουμε μια συνθήκη μέσα σε παρενθέσεις.
    ;

// Τα τουβλάκια της σύγκρισης: Ίσο, Ίδιο, Μεγαλύτερο, Μικρότερο κλπ.
rel_op:
    EQUALS | NOT_EQUALS | GREATER_EQUAL | LESS_EQUAL | GREATER | LESS
    ;

// Τι τιμές (κυριολεκτικά) μπορούμε να γράψουμε:
literal:
    INT_VAL { $$ = 1; }     // Επιστρέφει 1 (Ακέραιος).
    | FLOAT_VAL { $$ = 2; } // Επιστρέφει 2 (Δεκαδικός).
    | STRING_VAL { $$ = 3; free($1); } // Επιστρέφει 3 (Λέξη/Κείμενο).
    ;

// Μια λίστα από τιμές μέσα σε παρένθεση, π.χ. (1, 2, 3)
literal_list:
    literal {
        current_in_count = 0;
        current_in_types[current_in_count++] = $1; // Βάζουμε την πρώτη τιμή στον κουμπαρά.
    }
    | literal_list COMMA literal {
        current_in_types[current_in_count++] = $3; // Προσθέτουμε κι άλλες τιμές.
    }
    ;

// Ο όρος GROUP BY (ομαδοποίηση): Προαιρετικός.
group_by_clause:
    /* κενό */
    | GROUP BY column_list
    ;

// Ο όρος ORDER BY (ταξινόμηση/σειρά): Προαιρετικός.
order_by_clause:
    /* κενό */
    | ORDER BY column_list
    ;

// Ο όρος LIMIT (σταμάτα να μετράς μόλις βρεις τόσα): Προαιρετικός.
limit_clause:
    /* κενό */
    | LIMIT INT_VAL {
        // Το όριο πρέπει να είναι θετικός αριθμός! Δεν μπορείς να ζητήσεις -5 παιχνίδια.
        if ($2 <= 0) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Το όριο LIMIT πρέπει να είναι > 0.\n", line_num);
            exit(1);
        }
    }
    ;

%%

/* =========================================================================
   ΣΥΝΑΡΤΗΣΕΙΣ C (Η ΦΩΝΗ ΤΟΥ ΡΟΜΠΟΤ ΚΑΙ Η ΕΚΚΙΝΗΣΗ)
   ========================================================================= */

// Η συνάρτηση που φωνάζει όταν βρούμε ένα συντακτικό λάθος στο βιβλίο!
void yyerror(const char *s) {
    fprintf(stderr, "\n\n[Συντακτικό Σφάλμα] στη γραμμή %d: %s\n", line_num, s);
    exit(1); // Το παιχνίδι κλείνει αμέσως με κλάματα!
}

// Η κύρια συνάρτηση (το κουμπί ON του ρομπότ):
int main(int argc, char *argv[]) {
    // Αν ξεχάσουμε να του δώσουμε το όνομα του αρχείου (το βιβλίο), μας το θυμίζει.
    if (argc < 2) {
        fprintf(stderr, "Χρήση: %s <όνομα_αρχείου>\n", argv[0]);
        return 1;
    }

    // Ανοίγουμε το αρχείο για διάβασμα.
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Σφάλμα: Αδυναμία ανοίγματος του αρχείου '%s'\n", argv[1]);
        return 1;
    }

    // Συνδέουμε το βοηθάκι μας (Flex) με το αρχείο.
    extern FILE *yyin;
    yyin = file;

    printf("--- Έναρξη Ανάλυσης Αρχείου ---\n");
    yyparse(); // Λέμε στο ρομπότ: "Ξεκίνα να διαβάζεις τώρα!"
    printf("--- Τέλος Ανάλυσης (Όλα OK!) ---\n");

    fclose(file); // Κλείνουμε το βιβλίο.
    return 0;     // Το ρομπότ είναι χαρούμενο, όλα ήταν τέλεια!
}