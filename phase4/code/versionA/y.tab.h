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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    Class = 258,
    ProgramString = 259,
    Identifier = 260,
    OpenBracket = 261,
    CloseBracket = 262,
    OpenSquare = 263,
    CloseSquare = 264,
    SemiColon = 265,
    OpenParen = 266,
    CloseParen = 267,
    Comma = 268,
    Void = 269,
    Break = 270,
    Callout = 271,
    Continue = 272,
    Else = 273,
    Return = 274,
    Equal = 275,
    PlusEqual = 276,
    MinusEqual = 277,
    For = 278,
    If = 279,
    Int = 280,
    Boolean = 281,
    Decimal_literal = 282,
    Hex_literal = 283,
    Char_literal = 284,
    String_literal = 285,
    True = 286,
    False = 287,
    ConditionalOr = 288,
    ConditionalAnd = 289,
    EqualTo = 290,
    NotEqualTo = 291,
    LessThan = 292,
    LessThanEqual = 293,
    GreaterThanEqual = 294,
    GreaterThan = 295,
    Addition = 296,
    Minus = 297,
    Multiplication = 298,
    Division = 299,
    Remainder = 300,
    Negation = 301,
    UMinus = 302
  };
#endif
/* Tokens.  */
#define Class 258
#define ProgramString 259
#define Identifier 260
#define OpenBracket 261
#define CloseBracket 262
#define OpenSquare 263
#define CloseSquare 264
#define SemiColon 265
#define OpenParen 266
#define CloseParen 267
#define Comma 268
#define Void 269
#define Break 270
#define Callout 271
#define Continue 272
#define Else 273
#define Return 274
#define Equal 275
#define PlusEqual 276
#define MinusEqual 277
#define For 278
#define If 279
#define Int 280
#define Boolean 281
#define Decimal_literal 282
#define Hex_literal 283
#define Char_literal 284
#define String_literal 285
#define True 286
#define False 287
#define ConditionalOr 288
#define ConditionalAnd 289
#define EqualTo 290
#define NotEqualTo 291
#define LessThan 292
#define LessThanEqual 293
#define GreaterThanEqual 294
#define GreaterThan 295
#define Addition 296
#define Minus 297
#define Multiplication 298
#define Division 299
#define Remainder 300
#define Negation 301
#define UMinus 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 14 "llvm.y" /* yacc.c:1909  */

	Node *astNode;
	int ival;
	char *sval;

#line 154 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
