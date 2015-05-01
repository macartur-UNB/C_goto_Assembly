/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_PARSE_H_INCLUDED
# define YY_YY_SRC_PARSE_H_INCLUDED
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
    NUMBER = 258,
    PLUS = 259,
    MINUS = 260,
    TIMES = 261,
    DIVIDE = 262,
    REST = 263,
    NEG = 264,
    BOOL = 265,
    INT = 266,
    VOID = 267,
    FLOAT = 268,
    DOUBLE = 269,
    CHAR = 270,
    FILE_TOKEN = 271,
    AND = 272,
    OR = 273,
    XOR = 274,
    NOT = 275,
    AND_AND = 276,
    OR_OR = 277,
    ASSIGNMENT = 278,
    INCREMENT = 279,
    DECREMENT = 280,
    DIVIDE_EQUAL = 281,
    TIMES_EQUAL = 282,
    REST_EQUAL = 283,
    FALSE = 284,
    TRUE = 285,
    NULL_TOKEN = 286,
    COMPARE_EQUAL = 287,
    COMPARE_MORE = 288,
    COMPARE_LESS = 289,
    COMPARE_MORE_EQUAL = 290,
    COMPARE_LESS_EQUAL = 291,
    IF = 292,
    ELSE = 293,
    WHILE = 294,
    FOR = 295,
    DO = 296,
    LEFT_BRACKETS = 297,
    RIGHT_BRACKETS = 298,
    LEFT_PARENTHESIS = 299,
    RIGHT_PARENTHESIS = 300,
    LEFT_KEYS = 301,
    RIGHT_KEYS = 302,
    BEGIN_MULTILINE_COMMENT = 303,
    END_MULTILINE_COMMENT = 304,
    LINE_COMMENT = 305,
    HEADER_TOKEN = 306,
    IF_NDEF = 307,
    DEFINE = 308,
    INCLUDE = 309,
    END_IF = 310,
    MAIN = 311,
    RETURN = 312,
    END = 313,
    ANYTHING_ELSE = 314,
    END_INSTRUCTION = 315,
    VARIABLE_NAME = 316
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSE_H_INCLUDED  */
