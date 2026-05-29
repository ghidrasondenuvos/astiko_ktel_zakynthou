/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_C_USERS_SOPHIA_GIAKMOGLIDOU_DESKTOP_PROJECTA_PARSER_TAB_H_INCLUDED
# define YY_YY_C_USERS_SOPHIA_GIAKMOGLIDOU_DESKTOP_PROJECTA_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 122 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"

    typedef struct {
        char table_or_alias[50];
        char col_name[50];
    } ColumnRef;

#line 56 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CREATE = 258,                  /* CREATE  */
    TABLE = 259,                   /* TABLE  */
    SELECT = 260,                  /* SELECT  */
    FROM = 261,                    /* FROM  */
    WHERE = 262,                   /* WHERE  */
    GROUP = 263,                   /* GROUP  */
    BY = 264,                      /* BY  */
    ORDER = 265,                   /* ORDER  */
    LIMIT = 266,                   /* LIMIT  */
    JOIN = 267,                    /* JOIN  */
    ON = 268,                      /* ON  */
    AS = 269,                      /* AS  */
    TYPE_INT = 270,                /* TYPE_INT  */
    TYPE_FLOAT = 271,              /* TYPE_FLOAT  */
    TYPE_VARCHAR = 272,            /* TYPE_VARCHAR  */
    AND = 273,                     /* AND  */
    OR = 274,                      /* OR  */
    NOT = 275,                     /* NOT  */
    IN = 276,                      /* IN  */
    EQUALS = 277,                  /* EQUALS  */
    NOT_EQUALS = 278,              /* NOT_EQUALS  */
    GREATER_EQUAL = 279,           /* GREATER_EQUAL  */
    LESS_EQUAL = 280,              /* LESS_EQUAL  */
    GREATER = 281,                 /* GREATER  */
    LESS = 282,                    /* LESS  */
    COMMA = 283,                   /* COMMA  */
    SEMICOLON = 284,               /* SEMICOLON  */
    DOT = 285,                     /* DOT  */
    LPAREN = 286,                  /* LPAREN  */
    RPAREN = 287,                  /* RPAREN  */
    ASTERISK = 288,                /* ASTERISK  */
    INT_VAL = 289,                 /* INT_VAL  */
    FLOAT_VAL = 290,               /* FLOAT_VAL  */
    STRING_VAL = 291,              /* STRING_VAL  */
    IDENTIFIER = 292               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 132 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.y"

    int ival;        // Ο σάκος μπορεί να κρατήσει έναν κανονικό αριθμό.
    float fval;      // Ή έναν αριθμό με τελεία (δεκαδικό).
    char *sval;      // Ή μια λέξη.
    ColumnRef col;   // Ή μια στήλη με το όνομα του πίνακα της.
    int type_val;    // Ή έναν κωδικό τύπου.

#line 118 "C:\\Users\\Sophia Giakmoglidou\\Desktop\\projectA\\parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_C_USERS_SOPHIA_GIAKMOGLIDOU_DESKTOP_PROJECTA_PARSER_TAB_H_INCLUDED  */
