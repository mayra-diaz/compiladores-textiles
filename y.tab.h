/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    a = 258,
    sh1 = 259,
    sh2 = 260,
    sh3 = 261,
    sh4 = 262,
    sh5 = 263,
    sv1 = 264,
    sv2 = 265,
    sv3 = 266,
    sv4 = 267,
    sv5 = 268,
    n1 = 269,
    n2 = 270,
    n3 = 271,
    n4 = 272,
    n5 = 273,
    ac1 = 274,
    ac2 = 275,
    ac3 = 276,
    ac4 = 277,
    c1 = 278,
    c2 = 279,
    c3 = 280,
    c4 = 281,
    AF = 282,
    OTHER = 283
  };
#endif
/* Tokens.  */
#define a 258
#define sh1 259
#define sh2 260
#define sh3 261
#define sh4 262
#define sh5 263
#define sv1 264
#define sv2 265
#define sv3 266
#define sv4 267
#define sv5 268
#define n1 269
#define n2 270
#define n3 271
#define n4 272
#define n5 273
#define ac1 274
#define ac2 275
#define ac3 276
#define ac4 277
#define c1 278
#define c2 279
#define c3 280
#define c4 281
#define AF 282
#define OTHER 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
