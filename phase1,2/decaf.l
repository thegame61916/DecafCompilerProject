%{
/* Lex code to implement a parser for a decaf grammar */

#define YY_DECL extern "C" int yylex()
#include<fstream>
#include <iostream>
using namespace std;

#include "decaf.tab.h"  // to get the token types that we return
fstream foutlex("flex_output.txt",ios::out);
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
STRING_LITERAL			\".*\"
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

{CLASS}					{ foutlex<<"CLASS"<<"\n"; 				yylval.sval = strdup(yytext); return Class; }
{PROGRAM_STRING} 		{ foutlex<<"PROGRAM"<<"\n"; 			yylval.sval = strdup(yytext); return ProgramString; }
{VOID}					{ foutlex<<"VOID"<<"\n"; 				yylval.sval = strdup(yytext); return Void; }
{BREAK}					{ foutlex<<"BREAK"<<"\n"; 				yylval.sval = strdup(yytext); return Break; }
{CALLOUT}				{ foutlex<<"CALLOUT"<<"\n"; 			yylval.sval = strdup(yytext); return Callout; }
{CONTINUE}				{ foutlex<<"CONTINUE"<<"\n"; 			yylval.sval = strdup(yytext); return Continue; }
{ELSE}					{ foutlex<<"ELSE"<<"\n"; 				yylval.sval = strdup(yytext); return Else; }
{RETURN}				{ foutlex<<"RETURN"<<"\n"; 				yylval.sval = strdup(yytext); return Return; }
{FOR}					{ foutlex<<"FOR"<<"\n"; 				yylval.sval = strdup(yytext); return For; }
{IF}					{ foutlex<<"IF"<<"\n"; 					yylval.sval = strdup(yytext); return If; }
{INT}					{ foutlex<<"INT_DECLARATION"<<"\n"; 	yylval.sval = strdup(yytext); return Int; }
{BOOLEAN}				{ foutlex<<"BOOLEAN_DECLARATION"<<"\n";	yylval.sval = strdup(yytext); return Boolean; }
{FALSE}					{ foutlex<<"BOOLEAN:false"<<"\n"; 		yylval.sval = strdup(yytext); return False; }
{TRUE}					{ foutlex<<"BOOLEAN:true"<<"\n"; 		yylval.sval = strdup(yytext); return True; }
{MINUS}					{ foutlex<<"-"<<"\n"; 					yylval.sval = strdup(yytext); return Minus; }
{IDENTIFIER}			{ foutlex<<"ID:"<<yytext<<"\n"; 		yylval.sval = strdup(yytext); return Identifier; }
{OPEN_BRACKET} 			{ yylval.sval = strdup(yytext); return OpenBracket; }
{CLOSE_BRACKET} 		{ yylval.sval = strdup(yytext); return CloseBracket; }
{OPEN_SQUARE} 			{ yylval.sval = strdup(yytext); return OpenSquare; }
{CLOSE_SQUARE} 			{ yylval.sval = strdup(yytext); return CloseSquare; }
{SEMICOLON} 			{ yylval.sval = strdup(yytext); return SemiColon; }
{OPEN_PAREN} 			{ yylval.sval = strdup(yytext); return OpenParen; }
{CLOSE_PAREN} 			{ yylval.sval = strdup(yytext); return CloseParen; }
{COMMA} 				{ yylval.sval = strdup(yytext); return Comma; }
{EQUAL} 				{ foutlex<<"="<<"\n"; 					yylval.sval = strdup(yytext); return Equal; }
{PLUS_EQUAL} 			{ foutlex<<"+="<<"\n"; 					yylval.sval = strdup(yytext); return PlusEqual; }
{MINUS_EQUAL} 			{ foutlex<<"-="<<"\n"; 					yylval.sval = strdup(yytext); return MinusEqual; }
{DECIMAL_LITERAL} 		{ foutlex<<"INT:"<<yytext<<"\n"; 		yylval.sval = strdup(yytext); return Decimal_literal; }
{HEX_LITERAL} 			{ foutlex<<"INT:"<<yytext<<"\n"; 		yylval.sval = strdup(yytext); return Hex_literal; }
{CHAR_LITERAL} 			{ foutlex<<"CHARACTER:"<<yytext<<"\n"; 	yylval.sval = strdup(yytext); return Char_literal; }
{STRING_LITERAL}		{ foutlex<<"STRING:"<<yytext<<"\n"; 	yylval.sval = strdup(yytext); return String_literal; }
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
