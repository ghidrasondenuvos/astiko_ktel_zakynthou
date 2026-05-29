/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"

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

#line 191 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CREATE = 3,                     /* CREATE  */
  YYSYMBOL_TABLE = 4,                      /* TABLE  */
  YYSYMBOL_SELECT = 5,                     /* SELECT  */
  YYSYMBOL_FROM = 6,                       /* FROM  */
  YYSYMBOL_WHERE = 7,                      /* WHERE  */
  YYSYMBOL_GROUP = 8,                      /* GROUP  */
  YYSYMBOL_BY = 9,                         /* BY  */
  YYSYMBOL_ORDER = 10,                     /* ORDER  */
  YYSYMBOL_LIMIT = 11,                     /* LIMIT  */
  YYSYMBOL_JOIN = 12,                      /* JOIN  */
  YYSYMBOL_ON = 13,                        /* ON  */
  YYSYMBOL_AS = 14,                        /* AS  */
  YYSYMBOL_TYPE_INT = 15,                  /* TYPE_INT  */
  YYSYMBOL_TYPE_FLOAT = 16,                /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_VARCHAR = 17,              /* TYPE_VARCHAR  */
  YYSYMBOL_AND = 18,                       /* AND  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_IN = 21,                        /* IN  */
  YYSYMBOL_EQUALS = 22,                    /* EQUALS  */
  YYSYMBOL_NOT_EQUALS = 23,                /* NOT_EQUALS  */
  YYSYMBOL_GREATER_EQUAL = 24,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 25,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER = 26,                   /* GREATER  */
  YYSYMBOL_LESS = 27,                      /* LESS  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 29,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_LPAREN = 31,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 32,                    /* RPAREN  */
  YYSYMBOL_ASTERISK = 33,                  /* ASTERISK  */
  YYSYMBOL_INT_VAL = 34,                   /* INT_VAL  */
  YYSYMBOL_FLOAT_VAL = 35,                 /* FLOAT_VAL  */
  YYSYMBOL_STRING_VAL = 36,                /* STRING_VAL  */
  YYSYMBOL_IDENTIFIER = 37,                /* IDENTIFIER  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_statements = 40,                /* statements  */
  YYSYMBOL_statement = 41,                 /* statement  */
  YYSYMBOL_create_table_stmt = 42,         /* create_table_stmt  */
  YYSYMBOL_43_1 = 43,                      /* $@1  */
  YYSYMBOL_create_col_list = 44,           /* create_col_list  */
  YYSYMBOL_create_col_def = 45,            /* create_col_def  */
  YYSYMBOL_data_type = 46,                 /* data_type  */
  YYSYMBOL_select_stmt = 47,               /* select_stmt  */
  YYSYMBOL_48_2 = 48,                      /* $@2  */
  YYSYMBOL_select_col_list = 49,           /* select_col_list  */
  YYSYMBOL_column_list = 50,               /* column_list  */
  YYSYMBOL_column_item = 51,               /* column_item  */
  YYSYMBOL_table_ref = 52,                 /* table_ref  */
  YYSYMBOL_join_clause_list = 53,          /* join_clause_list  */
  YYSYMBOL_join_clause = 54,               /* join_clause  */
  YYSYMBOL_where_clause = 55,              /* where_clause  */
  YYSYMBOL_condition = 56,                 /* condition  */
  YYSYMBOL_rel_op = 57,                    /* rel_op  */
  YYSYMBOL_literal = 58,                   /* literal  */
  YYSYMBOL_literal_list = 59,              /* literal_list  */
  YYSYMBOL_group_by_clause = 60,           /* group_by_clause  */
  YYSYMBOL_order_by_clause = 61,           /* order_by_clause  */
  YYSYMBOL_limit_clause = 62               /* limit_clause  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   85

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  100

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   174,   175,   180,   181,   186,   186,   209,
     210,   215,   233,   234,   235,   247,   247,   335,   336,   341,
     342,   347,   358,   373,   384,   396,   411,   413,   418,   422,
     424,   429,   462,   486,   510,   511,   512,   513,   518,   518,
     518,   518,   518,   518,   523,   524,   525,   530,   534,   540,
     542,   546,   548,   552,   554
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CREATE", "TABLE",
  "SELECT", "FROM", "WHERE", "GROUP", "BY", "ORDER", "LIMIT", "JOIN", "ON",
  "AS", "TYPE_INT", "TYPE_FLOAT", "TYPE_VARCHAR", "AND", "OR", "NOT", "IN",
  "EQUALS", "NOT_EQUALS", "GREATER_EQUAL", "LESS_EQUAL", "GREATER", "LESS",
  "COMMA", "SEMICOLON", "DOT", "LPAREN", "RPAREN", "ASTERISK", "INT_VAL",
  "FLOAT_VAL", "STRING_VAL", "IDENTIFIER", "$accept", "program",
  "statements", "statement", "create_table_stmt", "$@1", "create_col_list",
  "create_col_def", "data_type", "select_stmt", "$@2", "select_col_list",
  "column_list", "column_item", "table_ref", "join_clause_list",
  "join_clause", "where_clause", "condition", "rel_op", "literal",
  "literal_list", "group_by_clause", "order_by_clause", "limit_clause", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      48,    16,   -65,    17,    48,   -65,   -65,   -65,   -21,   -22,
     -65,   -65,   -65,   -65,   -11,    20,    24,   -65,     9,     7,
      18,    19,    21,   -65,   -12,   -65,   -65,    33,    13,   -65,
      25,   -65,    -2,   -65,   -65,    23,   -65,    21,    28,   -65,
     -13,    18,   -65,    53,    29,   -65,   -65,   -13,   -13,    12,
     -10,    51,    56,    57,    34,   -65,    -5,    47,    38,   -65,
     -65,   -65,   -65,   -65,   -65,    -6,   -13,   -13,    19,    19,
      61,    60,   -65,   -65,    41,    -6,   -65,   -65,   -65,   -65,
     -65,    55,    52,    24,    19,    42,    49,    -6,   -65,    14,
      19,    24,   -65,   -65,    15,    -6,   -65,   -65,   -65,   -65
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    15,     0,     2,     3,     5,     6,     0,     0,
       1,     4,     7,    17,    21,     0,    18,    19,     0,     0,
       0,     0,     0,    22,    23,    26,    20,     0,     0,     9,
       0,    25,    29,    12,    13,     0,    11,     0,     0,    24,
       0,     0,    27,    49,     0,    10,     8,     0,     0,     0,
      30,     0,     0,    51,     0,    36,     0,     0,     0,    38,
      39,    40,    41,    42,    43,     0,     0,     0,     0,     0,
       0,    53,    14,    37,     0,     0,    44,    45,    46,    31,
      34,    35,     0,    50,     0,     0,     0,     0,    47,     0,
       0,    52,    54,    16,     0,     0,    32,    28,    33,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,   -65,   -65,    73,   -65,   -65,   -65,    43,   -65,   -65,
     -65,   -65,   -63,    -9,    44,   -65,   -65,   -65,   -44,   -65,
     -64,    -8,   -65,   -65,   -65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,    18,    28,    29,    36,     7,
       9,    15,    16,    49,    25,    32,    42,    43,    50,    65,
      88,    89,    53,    71,    86
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      17,    79,    30,    55,    56,    40,    83,    47,    66,    67,
      41,    13,    26,    66,    67,    14,    12,    10,    48,    19,
       8,    91,    80,    81,    14,    31,    20,    73,    76,    77,
      78,    99,    57,    58,    59,    60,    61,    62,    63,    64,
      22,    37,    95,    95,    23,    38,    96,    98,    33,    34,
      35,     1,    21,     2,    44,    24,    14,    46,    27,    82,
      17,    52,    39,    54,    68,    69,    72,    70,    74,    75,
      84,    85,    87,    66,    90,    17,    92,    11,    93,    94,
      45,    97,     0,     0,     0,    51
};

static const yytype_int8 yycheck[] =
{
       9,    65,    14,    47,    48,     7,    69,    20,    18,    19,
      12,    33,    21,    18,    19,    37,    37,     0,    31,    30,
       4,    84,    66,    67,    37,    37,     6,    32,    34,    35,
      36,    95,    20,    21,    22,    23,    24,    25,    26,    27,
      31,    28,    28,    28,    37,    32,    32,    32,    15,    16,
      17,     3,    28,     5,    31,    37,    37,    29,    37,    68,
      69,     8,    37,    34,    13,     9,    32,    10,    21,    31,
       9,    11,    31,    18,    22,    84,    34,     4,    29,    87,
      37,    90,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,    39,    40,    41,    42,    47,     4,    48,
       0,    41,    37,    33,    37,    49,    50,    51,    43,    30,
       6,    28,    31,    37,    37,    52,    51,    37,    44,    45,
      14,    37,    53,    15,    16,    17,    46,    28,    32,    37,
       7,    12,    54,    55,    31,    45,    29,    20,    31,    51,
      56,    52,     8,    60,    34,    56,    56,    20,    21,    22,
      23,    24,    25,    26,    27,    57,    18,    19,    13,     9,
      10,    61,    32,    32,    21,    31,    34,    35,    36,    58,
      56,    56,    51,    50,     9,    11,    62,    31,    58,    59,
      22,    50,    34,    29,    59,    28,    32,    51,    32,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    43,    42,    44,
      44,    45,    46,    46,    46,    48,    47,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    53,    53,    54,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    57,    57,
      57,    57,    57,    57,    58,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     0,     8,     1,
       3,     2,     1,     1,     4,     0,    11,     1,     1,     1,
       3,     1,     3,     1,     3,     2,     0,     2,     6,     0,
       2,     3,     5,     6,     3,     3,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       3,     0,     3,     0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 7: /* $@1: %empty  */
#line 186 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                            {
        // Μόλις δούμε το όνομα του πίνακα, ελέγχουμε αν υπάρχει ήδη στο ντουλάπι.
        if (find_table((yyvsp[0].sval)) != -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' υπάρχει ήδη.\n", line_num, (yyvsp[0].sval));
            exit(1); // Αν υπάρχει ήδη, το ρομπότ θυμώνει και σταματάει το παιχνίδι!
        }
        strcpy(current_table_name, (yyvsp[0].sval)); // Σημειώνουμε το όνομα του νέου πίνακα.
        temp_col_count = 0;              // Μηδενίζουμε τις πρόχειρες στήλες.
        free((yyvsp[0].sval));                        // Πετάμε το χαρτάκι που δεν χρειαζόμαστε πια.
    }
#line 1310 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 8: /* create_table_stmt: CREATE TABLE IDENTIFIER $@1 LPAREN create_col_list RPAREN SEMICOLON  */
#line 195 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                                              {
        // Μόλις κλείσει η παρένθεση και μπει το ερωτηματικό (;), βάζουμε τον πίνακα στο μεγάλο ντουλάπι!
        strcpy(symbol_table[table_count].name, current_table_name);
        symbol_table[table_count].col_count = temp_col_count;
        for (int i = 0; i < temp_col_count; i++) {
            symbol_table[table_count].columns[i] = temp_columns[i];
        }
        table_count++; // Τώρα έχουμε έναν πίνακα παραπάνω στο ντουλάπι μας!
        printf("\n[OK] Δημιουργήθηκε ο πίνακας '%s'.\n\n", current_table_name);
    }
#line 1325 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 11: /* create_col_def: IDENTIFIER data_type  */
#line 215 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                         {
        // Ελέγχουμε αν βάλαμε κατά λάθος δύο φορές την ίδια στήλη στο ίδιο κουτί!
        for (int i = 0; i < temp_col_count; i++) {
            if (icmp(temp_columns[i].name, (yyvsp[-1].sval)) == 0) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' ορίζεται δύο φορές στον πίνακα '%s'.\n", line_num, (yyvsp[-1].sval), current_table_name);
                exit(1); // Ζαβολιά! Το ρομπότ σταματάει.
            }
        }
        // Αν όλα είναι καλά, την κρατάμε προσωρινά.
        strcpy(temp_columns[temp_col_count].name, (yyvsp[-1].sval));
        temp_columns[temp_col_count].type = (yyvsp[0].type_val);
        temp_col_count++;
        free((yyvsp[-1].sval));
    }
#line 1344 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 12: /* data_type: TYPE_INT  */
#line 233 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
             { (yyval.type_val) = 1; }
#line 1350 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 13: /* data_type: TYPE_FLOAT  */
#line 234 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                 { (yyval.type_val) = 2; }
#line 1356 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 14: /* data_type: TYPE_VARCHAR LPAREN INT_VAL RPAREN  */
#line 235 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                                         {
        // Κωδικός 3: Λέξεις. Αλλά το μέγεθος της λέξης πρέπει να είναι θετικός αριθμός!
        if ((yyvsp[-1].ival) <= 0) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Το μέγεθος του VARCHAR πρέπει να είναι > 0.\n", line_num);
            exit(1);
        }
        (yyval.type_val) = 3;
    }
#line 1369 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 247 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
           { 
        // Μόλις ξεκινήσει το SELECT, καθαρίζουμε τις λίστες μας για να γράψουμε καινούργια πράγματα.
        used_column_count = 0; 
        active_table_count = 0; 
    }
#line 1379 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 16: /* select_stmt: SELECT $@2 select_col_list FROM table_ref join_clause_list where_clause group_by_clause order_by_clause limit_clause SEMICOLON  */
#line 252 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                                                                                                                        {
        
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
#line 1463 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 21: /* column_item: IDENTIFIER  */
#line 347 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
               {
        strcpy((yyval.col).table_or_alias, "");
        strcpy((yyval.col).col_name, (yyvsp[0].sval));
        
        // Τη γράφουμε στη λίστα για να την ελέγξει το ρομπότ στο τέλος.
        strcpy(used_columns[used_column_count].table_or_alias, "");
        strcpy(used_columns[used_column_count].col_name, (yyvsp[0].sval));
        used_columns[used_column_count].line = line_num;
        used_column_count++;
        free((yyvsp[0].sval));
    }
#line 1479 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 22: /* column_item: IDENTIFIER DOT IDENTIFIER  */
#line 358 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                                {
        strcpy((yyval.col).table_or_alias, (yyvsp[-2].sval));
        strcpy((yyval.col).col_name, (yyvsp[0].sval));
        
        // Τη γράφουμε στη λίστα μαζί με το πρόθεμά της.
        strcpy(used_columns[used_column_count].table_or_alias, (yyvsp[-2].sval));
        strcpy(used_columns[used_column_count].col_name, (yyvsp[0].sval));
        used_columns[used_column_count].line = line_num;
        used_column_count++;
        free((yyvsp[-2].sval)); free((yyvsp[0].sval));
    }
#line 1495 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 23: /* table_ref: IDENTIFIER  */
#line 373 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
               {
        int idx = find_table((yyvsp[0].sval));
        if (idx == -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' δεν έχει δημιουργηθεί.\n", line_num, (yyvsp[0].sval));
            exit(1); // Πάμε να παίξουμε με ένα κουτί που δεν έχουμε φτιάξει ποτέ! Λάθος!
        }
        strcpy(active_tables[active_table_count].table_name, (yyvsp[0].sval));
        strcpy(active_tables[active_table_count].alias_name, (yyvsp[0].sval));
        active_table_count++;
        free((yyvsp[0].sval));
    }
#line 1511 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 24: /* table_ref: IDENTIFIER AS IDENTIFIER  */
#line 384 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                               {
        // Αν πούμε: FROM Students AS s, τότε το αληθινό είναι "Students" και το χαϊδευτικό είναι "s".
        int idx = find_table((yyvsp[-2].sval));
        if (idx == -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' δεν έχει δημιουργηθεί.\n", line_num, (yyvsp[-2].sval));
            exit(1);
        }
        strcpy(active_tables[active_table_count].table_name, (yyvsp[-2].sval));
        strcpy(active_tables[active_table_count].alias_name, (yyvsp[0].sval));
        active_table_count++;
        free((yyvsp[-2].sval)); free((yyvsp[0].sval));
    }
#line 1528 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 25: /* table_ref: IDENTIFIER IDENTIFIER  */
#line 396 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                            {
        // Το ίδιο με το από πάνω, αλλά χωρίς τη λέξη AS (π.χ. FROM Students s).
        int idx = find_table((yyvsp[-1].sval));
        if (idx == -1) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ο πίνακας '%s' δεν έχει δημιουργηθεί.\n", line_num, (yyvsp[-1].sval));
            exit(1);
        }
        strcpy(active_tables[active_table_count].table_name, (yyvsp[-1].sval));
        strcpy(active_tables[active_table_count].alias_name, (yyvsp[0].sval));
        active_table_count++;
        free((yyvsp[-1].sval)); free((yyvsp[0].sval));
    }
#line 1545 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 31: /* condition: column_item rel_op literal  */
#line 429 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                               {
        /* ΕΛΕΓΧΟΣ ΣΥΜΒΑΤΟΤΗΤΑΣ: Ταιριάζουν τα παιχνίδια; */
        int t_idx = -1;
        if (strlen((yyvsp[-2].col).table_or_alias) > 0) {
            t_idx = resolve_active_table((yyvsp[-2].col).table_or_alias);
        } else {
            for (int j = 0; j < active_table_count; j++) {
                int tmp = find_table(active_tables[j].table_name);
                if (find_column_in_table(tmp, (yyvsp[-2].col).col_name) != -1) t_idx = tmp;
            }
        }
        
        if (t_idx != -1) {
            int col_type = find_column_in_table(t_idx, (yyvsp[-2].col).col_name); // Τι τύπος είναι η στήλη.
            int lit_type = (yyvsp[0].type_val);                                      // Τι τύπος είναι η τιμή που δώσαμε.
            
            // Αν η στήλη θέλει ολόκληρο αριθμό (INT) και εμείς της δώσουμε γράμματα, το ρομπότ φωνάζει!
            if (col_type == 1 && lit_type != 1) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι INT.\n", line_num, (yyvsp[-2].col).col_name);
                exit(1);
            }
            // Αν η στήλη θέλει δεκαδικό (FLOAT) και της δώσουμε γράμματα, πάλι σφάλμα!
            if (col_type == 2 && (lit_type != 1 && lit_type != 2)) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι FLOAT.\n", line_num, (yyvsp[-2].col).col_name);
                exit(1);
            }
            // Αν η στήλη θέλει λέξη (VARCHAR) και της δώσουμε αριθμό, το ρομπότ σταματάει το παιχνίδι!
            if (col_type == 3 && lit_type != 3) {
                fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Η στήλη '%s' είναι VARCHAR.\n", line_num, (yyvsp[-2].col).col_name);
                exit(1);
            }
        }
    }
#line 1583 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 32: /* condition: column_item IN LPAREN literal_list RPAREN  */
#line 462 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                                                {
        /* Έλεγχος τύπων για την εντολή IN (να είναι όλα τα στοιχεία μέσα στην παρένθεση ίδια με τη στήλη) */
        int t_idx = -1;
        if (strlen((yyvsp[-4].col).table_or_alias) > 0) t_idx = resolve_active_table((yyvsp[-4].col).table_or_alias);
        else {
            for (int j = 0; j < active_table_count; j++) {
                int tmp = find_table(active_tables[j].table_name);
                if (find_column_in_table(tmp, (yyvsp[-4].col).col_name) != -1) t_idx = tmp;
            }
        }
        
        if (t_idx != -1) {
            int col_type = find_column_in_table(t_idx, (yyvsp[-4].col).col_name);
            for (int k = 0; k < current_in_count; k++) {
                int lit_type = current_in_types[k];
                if ((col_type == 1 && lit_type != 1) || 
                    (col_type == 2 && (lit_type != 1 && lit_type != 2)) || 
                    (col_type == 3 && lit_type != 3)) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ασύμβατος τύπος στη λίστα του IN για τη στήλη '%s'.\n", line_num, (yyvsp[-4].col).col_name);
                    exit(1);
                }
            }
        }
    }
#line 1612 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 33: /* condition: column_item NOT IN LPAREN literal_list RPAREN  */
#line 486 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                                                    {
        /* Το ίδιο με το IN, αλλά για το NOT IN */
        int t_idx = -1;
        if (strlen((yyvsp[-5].col).table_or_alias) > 0) t_idx = resolve_active_table((yyvsp[-5].col).table_or_alias);
        else {
            for (int j = 0; j < active_table_count; j++) {
                int tmp = find_table(active_tables[j].table_name);
                if (find_column_in_table(tmp, (yyvsp[-5].col).col_name) != -1) t_idx = tmp;
            }
        }
        
        if (t_idx != -1) {
            int col_type = find_column_in_table(t_idx, (yyvsp[-5].col).col_name);
            for (int k = 0; k < current_in_count; k++) {
                int lit_type = current_in_types[k];
                if ((col_type == 1 && lit_type != 1) || 
                    (col_type == 2 && (lit_type != 1 && lit_type != 2)) || 
                    (col_type == 3 && lit_type != 3)) {
                    fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Ασύμβατος τύπος στη λίστα του NOT IN για τη στήλη '%s'.\n", line_num, (yyvsp[-5].col).col_name);
                    exit(1);
                }
            }
        }
    }
#line 1641 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 44: /* literal: INT_VAL  */
#line 523 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
            { (yyval.type_val) = 1; }
#line 1647 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 45: /* literal: FLOAT_VAL  */
#line 524 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                { (yyval.type_val) = 2; }
#line 1653 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 46: /* literal: STRING_VAL  */
#line 525 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                 { (yyval.type_val) = 3; free((yyvsp[0].sval)); }
#line 1659 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 47: /* literal_list: literal  */
#line 530 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
            {
        current_in_count = 0;
        current_in_types[current_in_count++] = (yyvsp[0].type_val); // Βάζουμε την πρώτη τιμή στον κουμπαρά.
    }
#line 1668 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 48: /* literal_list: literal_list COMMA literal  */
#line 534 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                                 {
        current_in_types[current_in_count++] = (yyvsp[0].type_val); // Προσθέτουμε κι άλλες τιμές.
    }
#line 1676 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;

  case 54: /* limit_clause: LIMIT INT_VAL  */
#line 554 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"
                    {
        // Το όριο πρέπει να είναι θετικός αριθμός! Δεν μπορείς να ζητήσεις -5 παιχνίδια.
        if ((yyvsp[0].ival) <= 0) {
            fprintf(stderr, "\n[Σημασιολογικό Σφάλμα] Στη γραμμή %d: Το όριο LIMIT πρέπει να είναι > 0.\n", line_num);
            exit(1);
        }
    }
#line 1688 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"
    break;


#line 1692 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 563 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"


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
