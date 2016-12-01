%{
// Bison code to parse decaf
#include "Module3.h"
#include <cstdio>
#include<string.h>
#include<fstream>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
string output = "";
string localType = "";
int declarationCount = 0;
int methodCount = 0;
void yyerror(const char *s);
fstream fout("XML_visitor.txt",ios::out);
%}
// Union for data types of tokens that can be returned by flex
%union {
	Node *astNode;
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
%type <sval> ConditionalOr ConditionalAnd EqualTo NotEqualTo LessThan LessThanEqual GreaterThanEqual GreaterThan Addition Minus Multiplication Division Remainder Negation
%type <astNode> Program field_decls field_decl Identifiers Identifier1 method_decls method_decl Params Block var_decls var_decl decls Statements Statement Method_call PassParams Method_name Location CalloutArgs Expr Literal Bool_literal Int_literal Type Assign_op

%%
// Grammar that'll be parsed by bison
Program 
	: 	Class ProgramString OpenBracket field_decls method_decls CloseBracket  	
	{ $$ = new ProgramNode($4, $5); Visitor visitor; $$->display(visitor, ""); };

field_decls
	:	field_decls field_decl												    { $$ = new FieldDeclsNode($1,$2); }
	|																			{ $$ = new FieldDeclsNode(NULL, NULL); };
	
field_decl
	:	Type Identifiers SemiColon												{ $$ = new FieldDeclsNode($1, $2); };

Identifiers
	: 	Identifier1																{ $$ = new IdentifiersNode($1, NULL); }
	|	Identifiers Comma Identifier1											{ $$ = new IdentifiersNode($3, $1); };

Identifier1
	:	Identifier 																
	{ $$ = new Identifier1Node(new IdentifierNode($1), NULL); }
	|	Identifier OpenSquare Int_literal CloseSquare							
	{ $$ = new Identifier1Node(new IdentifierNode($1), $3); };
	
method_decls
	:	method_decl method_decls												{ $$ = new MethodDeclsNode($1, $2); }
	|																			{ $$ = new MethodDeclsNode(NULL, NULL); };

method_decl
	:	Type Identifier OpenParen Params CloseParen Block						
	{ $$ = new MethodDeclNode($1, new IdentifierNode($2), $4, $6); }
	|	Type Identifier OpenParen CloseParen Block								
	{ $$ = new MethodDeclNode($1, new IdentifierNode($2), NULL, $5); }
	|	Void Identifier OpenParen Params CloseParen Block						
	{ $$ = new MethodDeclNode(NULL, new IdentifierNode($2), $4, $6); }
	|	Void Identifier OpenParen CloseParen Block								
	{ $$ = new MethodDeclNode(NULL, new IdentifierNode($2), NULL, $5); };

Params
	:	Type Identifier															
	{ $$ = new ParamsNode($1, new IdentifierNode($2), NULL); }
	|	Type Identifier Comma Params											
	{ $$ = new ParamsNode($1, new IdentifierNode($2), $4); };

Block
	: 	OpenBracket var_decls Statements CloseBracket							{ $$ = new BlockNode($2, $3); };

var_decls
	:	var_decl var_decls														{ $$ = new VarDeclsNode($1, $2); }
	|																			{ $$ = new VarDeclsNode(NULL, NULL); };

var_decl
	:	Type decls SemiColon													{ $$ = new VarDeclNode($1, $2); };

decls
	: 	Identifier																
	{ $$ = new DeclsNode(new IdentifierNode($1), NULL); }
	|	Identifier Comma decls													
	{ $$ = new DeclsNode(new IdentifierNode($1), $3); };

Statements
	: 	Statement Statements													{ $$ = new StatementsNode($1, $2); }
	|																			{ $$ = new StatementsNode(NULL, NULL); };

Statement
	: 	Location Assign_op Expr SemiColon										
	{ $$ = new StatementNode($1, $2, $3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }
	|	Method_call SemiColon													
	{ $$ = new StatementNode(NULL, NULL, NULL, $1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }
	| 	If OpenParen Expr CloseParen Block 										
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, $3, $5, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }
	| 	If OpenParen Expr CloseParen Block Else Block							
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, $3, $5, $7, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }
	|	For Identifier Equal Expr Comma Expr Block								
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, new IdentifierNode($2), $4, $6, $7, NULL, NULL, NULL, NULL, NULL); }
	|	Return SemiColon														
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, new ReturnStrNode($1), NULL, NULL, NULL, NULL); }
	|	Return Expr SemiColon													
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, new ReturnStrNode($1), $2, NULL, NULL, NULL); }
	|	Break SemiColon															
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, new BreakStrNode($1), NULL, NULL); }
	|	Continue SemiColon														
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, new ContinueStrNode($1), NULL); }
	|	Block																	
	{ $$ = new StatementNode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, $1); };

Method_call
	:	Method_name OpenParen PassParams CloseParen								{ $$ = new MethodCallNode($1, $3, NULL, NULL); }
	|	Method_name OpenParen CloseParen										{ $$ = new MethodCallNode($1, NULL, NULL, NULL); }
	| 	Callout	OpenParen String_literal CloseParen								
	{ $$ = new MethodCallNode(NULL, NULL, new StringLiteralNode($3), NULL); }
	| 	Callout	OpenParen String_literal Comma CalloutArgs CloseParen 			
	{ $$ = new MethodCallNode(NULL, NULL, new StringLiteralNode($3), $5); };

PassParams
	:	Expr																	{ $$ = new PassParamsNode($1, NULL); }
	|	Expr Comma PassParams													{ $$ = new PassParamsNode($1, $3); };

Method_name
	:	Identifier																{ $$ = new MethodNameNode(new IdentifierNode($1)); };

Location
	:	Identifier																
	{ $$ = new LocationNode(new IdentifierNode($1), NULL); }
	|	Identifier OpenSquare Expr CloseSquare									
	{ $$ = new LocationNode(new IdentifierNode($1), $3); };

CalloutArgs
	:	Expr													{ $$ = new CalloutArgsNode($1, NULL, NULL, NULL, NULL, NULL); }
	|	String_literal											
	{ $$ = new CalloutArgsNode(NULL, new StringLiteralNode($1), NULL, NULL, NULL, NULL); }
	|	Expr Comma CalloutArgs									{ $$ = new CalloutArgsNode(NULL, NULL, $1, $3, NULL, NULL); }
	|	String_literal Comma CalloutArgs						
	{ $$ = new CalloutArgsNode(NULL, NULL, NULL, NULL, new StringLiteralNode($1), $3); };
	
Expr
	:	Location												{ $$ = new ExprNode($1, NULL, NULL, NULL, NULL, NULL, NULL); }
	|	Method_call												{ $$ = new ExprNode(NULL, $1, NULL, NULL, NULL, NULL, NULL); }
	|	Literal													{ $$ = new ExprNode(NULL, NULL, $1, NULL, NULL, NULL, NULL); }
	|	Expr ConditionalOr Expr									
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr ConditionalAnd Expr								
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr EqualTo Expr										
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr NotEqualTo Expr									
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr LessThan Expr										
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr LessThanEqual Expr									
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr GreaterThanEqual Expr								
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr GreaterThan Expr									
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr Addition Expr										
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr Minus Expr										
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr Multiplication Expr								
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr Division Expr										
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Expr Remainder Expr										
	{ $$ = new ExprNode(NULL, NULL, NULL, $1, new OperatorNode($2), $3, NULL); }
	|	Minus Expr %prec UMinus									
	{ $$ = new ExprNode(NULL, NULL, NULL, NULL, new OperatorNode($1), $2, NULL); }
	|	Negation Expr											
	{ $$ = new ExprNode(NULL, NULL, NULL, NULL, new OperatorNode($1), $2, NULL); }
	|	OpenParen Expr CloseParen								
	{ $$ = new ExprNode(NULL, NULL, NULL, NULL, NULL, NULL, $2); };

Literal
	:	Int_literal																
	{ $$ = new LiteralNode($1, NULL, NULL); }		
	|	Char_literal															
	{ $$ = new LiteralNode(NULL, new CharLiteralNode($1), NULL); }
	|	Bool_literal															
	{ $$ = new LiteralNode(NULL, NULL, $1); };

Bool_literal
	:	True																	{ $$ = new BoolLiteralNode($1); }
	|	False																	{ $$ = new BoolLiteralNode($1); };

Int_literal
	:	Decimal_literal															{ $$ = new IntLiteralNode($1); }
	|	Hex_literal																{ $$ = new IntLiteralNode($1); };

Type
	:	Int																		{ $$ = new TypeNode($1); }
	|	Boolean																	{ $$ = new TypeNode($1); };
	
Assign_op
	:	Equal 																	{ $$ = new AssignOpNode($1); }
	|	PlusEqual 																{ $$ = new AssignOpNode($1); }
	|	MinusEqual																{ $$ = new AssignOpNode($1); };
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
	fout.close();
	cout<<"Success\n";
	return 0;
}

void yyerror(const char *s) {
	cout<<"Syntax error\n";
	exit(-1);
}
