/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_FCG_YACC_H_INCLUDED
# define YY_YY_FCG_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTVAL = 259,
    FLTVAL = 260,
    DBLVAL = 261,
    STRVAL = 262,
    CHARVAL = 263,
    VOID = 264,
    CHAR = 265,
    SHORT = 266,
    INT = 267,
    LONG = 268,
    FLOAT = 269,
    DOUBLE = 270,
    EQ = 271,
    NE = 272,
    GE = 273,
    LE = 274,
    GT = 275,
    LT = 276,
    ADD = 277,
    SUB = 278,
    MUL = 279,
    DIV = 280,
    MOD = 281,
    OR = 282,
    AND = 283,
    BITOR = 284,
    BITAND = 285,
    BITXOR = 286,
    NOT = 287,
    COM = 288,
    LSH = 289,
    RSH = 290,
    SET = 291,
    SETADD = 292,
    SETSUB = 293,
    SETMUL = 294,
    SETDIV = 295,
    SETMOD = 296,
    SETOR = 297,
    SETAND = 298,
    SETXOR = 299,
    SETLSH = 300,
    SETRSH = 301,
    RETURN = 302,
    DO = 303,
    WHILE = 304,
    FOR = 305,
    SWITCH = 306,
    CASE = 307,
    DEFAULT = 308,
    IF = 309,
    ELSE = 310,
    CONTINUE = 311,
    BREAK = 312,
    GOTO = 313,
    UNSIGNED = 314,
    TYPEDEF = 315,
    STRUCT = 316,
    UNION = 317,
    CONST = 318,
    STATIC = 319,
    EXTERN = 320,
    AUTO = 321,
    REGISTER = 322,
    SIZEOF = 323
  };
#endif
/* Tokens.  */
#define ID 258
#define INTVAL 259
#define FLTVAL 260
#define DBLVAL 261
#define STRVAL 262
#define CHARVAL 263
#define VOID 264
#define CHAR 265
#define SHORT 266
#define INT 267
#define LONG 268
#define FLOAT 269
#define DOUBLE 270
#define EQ 271
#define NE 272
#define GE 273
#define LE 274
#define GT 275
#define LT 276
#define ADD 277
#define SUB 278
#define MUL 279
#define DIV 280
#define MOD 281
#define OR 282
#define AND 283
#define BITOR 284
#define BITAND 285
#define BITXOR 286
#define NOT 287
#define COM 288
#define LSH 289
#define RSH 290
#define SET 291
#define SETADD 292
#define SETSUB 293
#define SETMUL 294
#define SETDIV 295
#define SETMOD 296
#define SETOR 297
#define SETAND 298
#define SETXOR 299
#define SETLSH 300
#define SETRSH 301
#define RETURN 302
#define DO 303
#define WHILE 304
#define FOR 305
#define SWITCH 306
#define CASE 307
#define DEFAULT 308
#define IF 309
#define ELSE 310
#define CONTINUE 311
#define BREAK 312
#define GOTO 313
#define UNSIGNED 314
#define TYPEDEF 315
#define STRUCT 316
#define UNION 317
#define CONST 318
#define STATIC 319
#define EXTERN 320
#define AUTO 321
#define REGISTER 322
#define SIZEOF 323

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "fcg.y" /* yacc.c:1909  */

    char* id;

#line 194 "fcg.yacc.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FCG_YACC_H_INCLUDED  */
