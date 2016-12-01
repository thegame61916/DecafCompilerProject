%{
// Bison code to parse decaf
#include <cstdio>
#include<string.h>
#include<fstream>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
void yyerror(const char *s);
extern "C" fstream foutlex;
fstream fout("bison_output.txt",ios::out);
%}
// Union for data types of tokens that can be returned by flex
%union {
	int ival;
	char *sval;
}

// Different tokens that can be returned by flex
%token <sval> Class ProgramString Identifier OpenBracket CloseBracket OpenSquare CloseSquare SemiColon OpenParen CloseParen Comma Void Break Callout Continue Else Return Equal PlusEqual MinusEqual For If Int Boolean Decimal_literal Hex_literal Char_literal String_literal True False
%left ConditionalOr
%left ConditionalAnd
%left EqualTo NotEqualTo
%left LessThan LessThanEqual GreaterThanEqual GreaterThan
%left Addition Minus
%left Multiplication Division Remainder
%left Negation
%left UMinus

%%
// Grammar that'll be parsed by bison
Program 
	: 	Class ProgramString OpenBracket field_decls method_decls CloseBracket  	{fout <<"PROGRAM ENCOUNTERED\n"; };

field_decls
	:	field_decls field_decl												
	|;				 															

field_decl
	:	Type Identifiers SemiColon;

Identifiers
	: 	Identifier1
	|	Identifiers Comma Identifier1;

Identifier1
	:	Identifier 																{ fout<<"ID="<<$1<<"\n"; }
	|	Identifier OpenSquare Decimal_literal CloseSquare						{ fout<<"ID="<<$1<<"\n"<<"SIZE="<<$3<<"\n"; }
	|	Identifier OpenSquare Hex_literal CloseSquare							{ fout<<"ID="<<$1<<"\n"<<"SIZE="<<$3<<"\n"; };
method_decls
	:	method_decl method_decls												
	|;

method_decl
	:	Type Identifier OpenParen Params CloseParen Block						{ fout<<"METHOD="<<$2<<"\n"; }
	|	Type Identifier OpenParen CloseParen Block								{ fout<<"METHOD="<<$2<<"\n"; }
	|	Void Identifier OpenParen Params CloseParen Block						{ fout<<"METHOD="<<$2<<"\n"; }
	|	Void Identifier OpenParen CloseParen Block								{ fout<<"METHOD="<<$2<<"\n"; };

Params
	:	Type Identifier											
	|	Type Identifier Comma Params;

Block
	: 	OpenBracket var_decls Statements CloseBracket;

var_decls
	:	var_decl var_decls												
	|;

var_decl
	:	Type decls SemiColon;

decls
	: 	Identifier																{ fout<<"ID="<<$1<<"\n"; }
	|	Identifier Comma decls													{ fout<<"ID="<<$1<<"\n"; };

Statements
	: 	Statement Statements													
	|;																			

Statement
	: 	Location Assign_op Expr SemiColon										{ fout<<"ASSIGNMENT OPERATION ENCOUNTERED\n"; }
	|	Method_call SemiColon				
	| 	If OpenParen Expr CloseParen Block 										{ fout<<"IF ENCOUNTERED\n"; }
	| 	If OpenParen Expr CloseParen Block Else Block							{ fout<<"IF ENCOUNTERED\n"; }
	|	For Identifier Equal Expr Comma Expr Block								{ fout<<"FOR ENCOUNTERED\n"; }
	|	Return SemiColon														{ fout<<"RETURN ENCOUNTERED\n"; }
	|	Return Expr SemiColon													{ fout<<"RETURN ENCOUNTERED\n"; }					
	|	Break SemiColon															{ fout<<"BREAK ENCOUNTERED\n"; }
	|	Continue SemiColon														{ fout<<"CONTINUE ENCOUNTERED\n"; }
	|	Block;

Method_call
	:	Method_name OpenParen PassParams CloseParen						
	|	Method_name OpenParen CloseParen
	| 	Callout	OpenParen String_literal CloseParen								{ fout<<"CALLOUT TO "<<$3<<" ENCOUNTERED\n"; }
	| 	Callout	OpenParen String_literal Comma CalloutArgs CloseParen 			{ fout<<"CALLOUT TO "<<$3<<" ENCOUNTERED\n"; };

PassParams
	:	Expr
	|	Expr Comma PassParams;

Method_name
	:	Identifier																{ fout<<"METHOD CALL="<<$1; };

Location
	:	Identifier																{ fout<<"LOCATION ENCOUNTERED="<<$1<<"\n"; }
	|	Identifier OpenSquare Expr CloseSquare;

CalloutArgs
	:	Expr
	|	String_literal
	|	Expr Comma CalloutArgs
	|	String_literal Comma CalloutArgs;
	
Expr
	:	Location
	|	Method_call
	|	Literal
	|	Expr ConditionalOr Expr													{ fout<<"CONDITIONAL OR ENCOUNTERED\n"; }
	|	Expr ConditionalAnd Expr												{ fout<<"CONDITIONAL AND ENCOUNTERED\n"; }
	|	Expr EqualTo Expr														{ fout<<"EQUAL TO ENCOUNTERED\n"; }
	|	Expr NotEqualTo Expr													{ fout<<"NOT EQUAL TO ENCOUNTERED\n"; }
	|	Expr LessThan Expr														{ fout<<"LESS THAN ENCOUNTERED\n"; }
	|	Expr LessThanEqual Expr													{ fout<<"LESS THAN EQUAL ENCOUNTERED\n"; }
	|	Expr GreaterThanEqual Expr												{ fout<<"GREATER THAN EQUAL ENCOUNTERED\n"; }
	|	Expr GreaterThan Expr													{ fout<<"GREATER THAN ENCOUNTERED\n"; }
	|	Expr Addition Expr														{ fout<<"ADDITION ENCOUNTERED\n"; }
	|	Expr Minus Expr															{ fout<<"SUBTRACTION ENCOUNTERED\n"; }
	|	Expr Multiplication Expr												{ fout<<"MULTIPLICATION ENCOUNTERED\n"; }
	|	Expr Division Expr														{ fout<<"DIVIDION ENCOUNTERED\n"; }
	|	Expr Remainder Expr														{ fout<<"MOD ENCOUNTERED\n"; }
	|	Minus Expr %prec UMinus													{ fout<<"UNARY MINUS ENCOUNTERED\n"; }
	|	Negation Expr															{ fout<<"NEGATION ENCOUNTERED\n"; }
	|	OpenParen Expr CloseParen;

Literal
	:	Int_literal			
	|	Char_literal															{ fout<<"CHAR ENCOUNTERED="<<$1<<"\n"; }
	|	Bool_literal;

Bool_literal
	:	True																	{ fout<<"BOOLEAN ENCOUNTERED="<<$1<<"\n"; }
	|	False																	{ fout<<"BOOLEAN ENCOUNTERED="<<$1<<"\n"; };

Int_literal
	:	Decimal_literal															{ fout<<"INT ENCOUNTERED="<<$1<<"\n"; }
	|	Hex_literal																{ fout<<"INT ENCOUNTERED="<<$1<<"\n"; };

Type
	:	Int																		{ fout<<"INT DECLARATION ENCOUNTERED\n"; }
	|	Boolean																	{ fout<<"BOOLEAN DECLARATION ENCOUNTERED\n"; };
	
Assign_op
	:	Equal 																	{ fout<<"ASSIGNMENT ENCOUNTERED\n"; }
	|	PlusEqual 																{ fout<<"ADDITION ASSIGNMENT ENCOUNTERED\n"; }
	|	MinusEqual																{ fout<<"SUBTRACTION ASSIGNMENT ENCOUNTERED\n"; };
%%

int main(int argc, char** argv) 
{
	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) 
	{
		cout << "I can't open input file!" << endl;
		return -1;
	}
	yyin = myfile;
	do 
	{
		yyparse();
	} while (!feof(yyin));
	cout<<"Success\n";
	fout.close();
	foutlex.close();
	return 0;
}

void yyerror(const char *s) {
	cout<<"Syntax error\n";
	fout.close();
	exit(-1);
}
