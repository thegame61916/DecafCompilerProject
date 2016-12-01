%{
/* Lex code to implement a parser for a decaf grammar */

#define YY_DECL extern "C" int yylex()
#include<fstream>
#include <iostream>
using namespace std;
#include "Module3.h"
#include "Module3.tab.h"  // to get the token types that we return
%}


COMMENT					"//".*
CLASS					"class"
PROGRAM_STRING 			"Program"
IDENTIFIER				[_a-zA-Z][_a-zA-Z0-9]*
OPEN_BRACKET 			"{"
CLOSE_BRACKET 			"}"
OPEN_SQUARE 			"["
CLOSE_SQUARE 			"]"
SEMICOLON 				";"
OPEN_PAREN 				"("
CLOSE_PAREN 			")"
COMMA 					","
VOID					"void"
BREAK					"break"
CALLOUT					"callout"
CONTINUE				"continue"
ELSE					"else"
RETURN					"return"
EQUAL 					"="
PLUS_EQUAL 				"+="
MINUS_EQUAL 			"-="
FOR						"for"
IF						"if"
INT						"int"
BOOLEAN					"boolean"
DECIMAL_LITERAL 		[-]?[0-9]+
HEX_LITERAL 			0[xX][0-9a-fA-F]+
CHAR_LITERAL 			"\'"([^\"\'\\]|"\\\""|"\\\'"|"\\\\"|"\\t"|"\\n")"\'"
STRING_LITERAL			\"[^\"]*\"
FALSE					"false"
TRUE					"true"
CONDITIONAL_OR			"||"
CONDITIONAL_AND			"&&"
EQUAL_TO 				"=="
NOT_EQUAL_TO			"!="
LESS_THAN 				"<"
LESS_THAN_EQUAL 		"<="
GREATER_THAN_EQUAL 		">="
GREATER_THAN			">"
ADDITION 				"+"
MINUS					"-"
MULTIPLICATION 			"*"
DIVISION 				"/"
REMAINDER				"%"
NEGATION				"!"

%%	
[ \t\n]          		;
{COMMENT}				;

{CLASS}					{ yylval.sval = strdup(yytext); return Class; }
{PROGRAM_STRING} 		{ yylval.sval = strdup(yytext); return ProgramString; }
{VOID}					{ yylval.sval = strdup(yytext); return Void; }
{BREAK}					{ yylval.sval = strdup(yytext); return Break; }
{CALLOUT}				{ yylval.sval = strdup(yytext); return Callout; }
{CONTINUE}				{ yylval.sval = strdup(yytext); return Continue; }
{ELSE}					{ yylval.sval = strdup(yytext); return Else; }
{RETURN}				{ yylval.sval = strdup(yytext); return Return; }
{FOR}					{ yylval.sval = strdup(yytext); return For; }
{IF}					{ yylval.sval = strdup(yytext); return If; }
{INT}					{ yylval.sval = strdup(yytext); return Int; }
{BOOLEAN}				{ yylval.sval = strdup(yytext); return Boolean; }
{FALSE}					{ yylval.sval = strdup(yytext); return False; }
{TRUE}					{ yylval.sval = strdup(yytext); return True; }
{MINUS}					{ yylval.sval = strdup(yytext); return Minus; }
{IDENTIFIER}			{ yylval.sval = strdup(yytext); return Identifier; }
{OPEN_BRACKET} 			{ yylval.sval = strdup(yytext); return OpenBracket; }
{CLOSE_BRACKET} 		{ yylval.sval = strdup(yytext); return CloseBracket; }
{OPEN_SQUARE} 			{ yylval.sval = strdup(yytext); return OpenSquare; }
{CLOSE_SQUARE} 			{ yylval.sval = strdup(yytext); return CloseSquare; }
{SEMICOLON} 			{ yylval.sval = strdup(yytext); return SemiColon; }
{OPEN_PAREN} 			{ yylval.sval = strdup(yytext); return OpenParen; }
{CLOSE_PAREN} 			{ yylval.sval = strdup(yytext); return CloseParen; }
{COMMA} 				{ yylval.sval = strdup(yytext); return Comma; }
{EQUAL} 				{ yylval.sval = strdup(yytext); return Equal; }
{PLUS_EQUAL} 			{ yylval.sval = strdup(yytext); return PlusEqual; }
{MINUS_EQUAL} 			{ yylval.sval = strdup(yytext); return MinusEqual; }
{DECIMAL_LITERAL} 		{ yylval.sval = strdup(yytext); return Decimal_literal; }
{HEX_LITERAL} 			{ yylval.sval = strdup(yytext); return Hex_literal; }
{CHAR_LITERAL} 			{ yylval.sval = strdup(yytext); return Char_literal; }
{STRING_LITERAL}		{ yylval.sval = strdup(yytext); return String_literal; }
{CONDITIONAL_OR}		{ yylval.sval = strdup(yytext); return ConditionalOr; }
{CONDITIONAL_AND}		{ yylval.sval = strdup(yytext); return ConditionalAnd; }
{EQUAL_TO} 				{ yylval.sval = strdup(yytext); return EqualTo; }
{NOT_EQUAL_TO}			{ yylval.sval = strdup(yytext); return NotEqualTo; }
{LESS_THAN} 			{ yylval.sval = strdup(yytext); return LessThan; }
{LESS_THAN_EQUAL} 		{ yylval.sval = strdup(yytext); return LessThanEqual; }
{GREATER_THAN_EQUAL} 	{ yylval.sval = strdup(yytext); return GreaterThanEqual; }
{GREATER_THAN}			{ yylval.sval = strdup(yytext); return GreaterThan; }
{ADDITION} 				{ yylval.sval = strdup(yytext); return Addition; }
{MULTIPLICATION} 		{ yylval.sval = strdup(yytext); return Multiplication; }
{DIVISION} 				{ yylval.sval = strdup(yytext); return Division; }
{REMAINDER}				{ yylval.sval = strdup(yytext); return Remainder; }
{NEGATION}				{ yylval.sval = strdup(yytext); return Negation; }
%%
