// Classes corresponding to all the non terminal nodes and corresponding codeGens

#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <llvm/PassManager.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;
using namespace llvm;

class AbstractVisitor;

// Base class for all the nodes in AST
class Node
{
	public:
		virtual Value *genCode(AbstractVisitor &visitor) = 0;
};

// Declarations for all the classes in AST
class ProgramNode;
class FieldDeclsNode;
class FieldDeclNode;
class IdentifiersNode;
class Identifier1Node;
class MethodDeclsNode;
class MethodDeclNode;
class ParamsNode;
class BlockNode;
class VarDeclsNode;
class VarDeclNode;
class DeclsNode;
class StatementsNode;
class StatementNode;
class MethodCallNode;
class PassParamsNode;
class MethodNameNode;
class LocationNode;
class CalloutArgsNode;
class ExprNode;
class LiteralNode;
class BoolLiteralNode;
class IntLiteralNode;
class TypeNode;
class AssignOpNode;
class IdentifierNode;
class ReturnStrNode;
class BreakStrNode;
class ContinueStrNode;
class StringLiteralNode;
class CharLiteralNode;
class OperatorNode;

// Class to maintain code and local variables of a basic block during code generation
class CodeBasicBlock 
{
    public:
        BasicBlock *blockCode;
        map<string, Value*> localVars;
};

// Code manager class to keep track of which basic block's code is being generated now
class CodeGenManager 
{
    stack<CodeBasicBlock *> blocks;							// Stack is used as we can have nested blocks
    Function *mainF;
    
    public:
    Module *module;
    CodeGenManager() 
    { 
    	module = new Module("main", getGlobalContext()); 
    }
	void pushBlock(BasicBlock *bb) 
    { 
    	blocks.push(new CodeBasicBlock()); 
    	blocks.top()->blockCode = bb; 
    }
    void popBlock() 
    { 
    	CodeBasicBlock *top = blocks.top(); 
    	blocks.pop(); 
    	delete top; 
    }
    map<string, Value*>& localVars() 
    { 
    	return blocks.top()->localVars; 
    }
    BasicBlock *getCurrentBlock() 
    { 
    	return blocks.top()->blockCode; 
    }
    void genLLCode(ProgramNode* root);
};

class AbstractVisitor
{
	public:
		virtual Value *codeGen(ProgramNode &node) = 0;
		virtual Value *codeGen(FieldDeclsNode &node) = 0;
		virtual Value *codeGen(FieldDeclNode &node) = 0;
		virtual Value *codeGen(IdentifiersNode &node) = 0;
		virtual Value *codeGen(Identifier1Node &node) = 0;
		virtual Value *codeGen(MethodDeclsNode &node) = 0;
		virtual Value *codeGen(MethodDeclNode &node) = 0;
		virtual Value *codeGen(ParamsNode &node) = 0;
		virtual Value *codeGen(BlockNode &node) = 0;
		virtual Value *codeGen(VarDeclsNode &node) = 0;
		virtual Value *codeGen(VarDeclNode &node) = 0;
		virtual Value *codeGen(DeclsNode &node) = 0;
		virtual Value *codeGen(StatementsNode &node) = 0;
		virtual Value *codeGen(StatementNode &node) = 0;
		virtual Value *codeGen(MethodCallNode &node) = 0;
		virtual Value *codeGen(PassParamsNode &node) = 0;
		virtual Value *codeGen(MethodNameNode &node) = 0;
		virtual Value *codeGen(LocationNode &node) = 0;
		virtual Value *codeGen(CalloutArgsNode &node) = 0;
		virtual Value *codeGen(ExprNode &node) = 0;
		virtual Value *codeGen(LiteralNode &node) = 0;
		virtual Value *codeGen(BoolLiteralNode &node) = 0;
		virtual Value *codeGen(IntLiteralNode &node) = 0;
		virtual Value *codeGen(TypeNode &node) = 0;
		virtual Value *codeGen(AssignOpNode &node) = 0;
		virtual Value *codeGen(IdentifierNode &node) = 0;
		virtual Value *codeGen(ReturnStrNode &node) = 0;
		virtual Value *codeGen(BreakStrNode &node) = 0;
		virtual Value *codeGen(ContinueStrNode &node) = 0;
		virtual Value *codeGen(StringLiteralNode &node) = 0;
		virtual Value *codeGen(CharLiteralNode &node) = 0;
		virtual Value *codeGen(OperatorNode &node) = 0;
};

// **************************************************************************************************
// Class definitions for all the AST nodes
// **************************************************************************************************
class ProgramNode : public Node
{
	public:
	Node *fieldDecls;
	Node *methodDecls;
	
	ProgramNode(Node *l, Node *m)
	{	
		fieldDecls = l;
		methodDecls = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class FieldDeclsNode : public Node
{
	public:
	Node *fieldDecls;
	Node *fieldDecl;
	
	FieldDeclsNode(Node *l, Node *m)
	{	
		fieldDecls = l;
		fieldDecl = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class FieldDeclNode : public Node
{
	public:
	Node *type;
	Node *identifiers;

	FieldDeclNode(Node *l, Node *m)
	{	
		type = l;
		identifiers = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class IdentifiersNode : public Node
{
	public:
	Node *identifiers1;
	Node *identifiers;

	IdentifiersNode(Node *l, Node *m)
	{	
		identifiers1 = l;
		identifiers = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class IdentifierNode : public Node
{
	public:
	string identifier;

	IdentifierNode(char *l)
	{	
		identifier = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class ReturnStrNode : public Node
{
	public:
	string returnStr;

	ReturnStrNode(char *l)
	{	
		returnStr = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class BreakStrNode : public Node
{
	public:
	string breakStr;

	BreakStrNode(char *l)
	{	
		breakStr = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class ContinueStrNode : public Node
{	
	public:
	string continueStr;

	ContinueStrNode(char *l)
	{	
		continueStr = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class StringLiteralNode : public Node
{
	public:
	string stringLiteral;

	StringLiteralNode(char *l)
	{	
		stringLiteral = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class CharLiteralNode : public Node
{
	public:
	string charLiteral;

	CharLiteralNode(char *l)
	{	
		charLiteral = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class OperatorNode : public Node
{
	public:
	string operator1;

	OperatorNode(char *l)
	{	
		operator1 = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class Identifier1Node : public Node
{
	public:
	Node* identifier;
	Node *intLiteral;

	Identifier1Node(Node *l, Node *m)
	{	
		identifier = l;
		intLiteral = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class MethodDeclsNode : public Node
{
	public:
	Node *methodDecl;
	Node *methodDecls;

	MethodDeclsNode(Node *l, Node *m)
	{	
		methodDecl = l;
		methodDecls = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class MethodDeclNode : public Node
{
	public:
	Node *type;
	Node *identifier;
	Node *params;
	Node *block;

	MethodDeclNode(Node *l, Node *m, Node *n, Node *o)
	{	
		type = l;
		identifier = m;
		params = n;
		block = o;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class ParamsNode : public Node
{
	public:
	Node *type;
	Node *identifier;
	Node *params;

	ParamsNode(Node *l, Node *m, Node *n)
	{	
		type = l;
		if(m)
			identifier = m;
		params = n;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class BlockNode : public Node
{
	public:
	Node *varDecls;
	Node *statements;	

	BlockNode(Node *l, Node *m)
	{	
		varDecls = l;
		statements = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class VarDeclsNode : public Node
{
	public:
	Node *varDecl;
	Node *varDecls;

	VarDeclsNode(Node *l, Node *m)
	{	
		varDecl = l;
		varDecls = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class VarDeclNode : public Node
{
	public:
	Node *type;
	Node *decls;

	VarDeclNode(Node *l, Node *m)
	{	
		type = l;
		decls = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class DeclsNode : public Node
{
	public:
	Node *identifier;
	Node *decls;

	DeclsNode(Node *l, Node *m)
	{	
		identifier = l;
		decls = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class StatementsNode : public Node
{
	public:
	Node *statement;
	Node *statements;

	StatementsNode(Node *l, Node *m)
	{	
		statement = l;
		statements = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class StatementNode : public Node
{
	public:
	Node *location;
	Node *assignOp;
	Node *Expr;
	Node *methodCall;
	Node *exprInsideParen;
	Node *blockAfterIf;
	Node *blockAfterElse;
	Node *identifierInsideFor;
	Node *exprInsideFor;
	Node *exprInsideForAfterComma;
	Node *blockInsideFor;
	Node *returnStr;
	Node *exprAfterReturn;
	Node *breakStr;
	Node *continueStr;
	Node *block;

	StatementNode(Node *l, Node *m, Node *n, Node *o, Node *p, Node *q, Node *r, Node *s, Node *t, Node *u, Node *v, Node *w, Node *x, Node *y, Node *z, Node *a)
	{	
		location = l;
		assignOp = m;
		Expr = n;
		methodCall = o;
		exprInsideParen = p;
		blockAfterIf = q;
		blockAfterElse = r;
		identifierInsideFor = s;
		exprInsideFor = t;
		exprInsideForAfterComma = u;
		blockInsideFor = v;
		returnStr = w;
		exprAfterReturn = x;
		breakStr = y;
		continueStr = z;
		block = a;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};


class MethodCallNode : public Node
{
	public:
	Node *methodName;
	Node *passParams;
	Node *stringLiteralInsideParen;
	Node *callOutArgs;

	MethodCallNode(Node *l, Node *m, Node *n, Node *o)
	{	
		methodName = l;
		passParams = m;
		stringLiteralInsideParen = n;
		callOutArgs = o;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class PassParamsNode : public Node
{
	public:
	Node *expr;
	Node *passParams;

	PassParamsNode(Node *l, Node *m)
	{	
		expr = l;
		passParams = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class MethodNameNode : public Node
{
	public:
	Node *identifier;

	MethodNameNode(Node *l)
	{	
		identifier = l;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class LocationNode : public Node
{
	public:
	Node *identifier;
	Node *expr;

	LocationNode(Node *l, Node *m)
	{	
		identifier = l;
		expr = m;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class CalloutArgsNode : public Node
{
	public:
	Node *expr;
	Node *stringLiteral;
	Node *exprBeforeComma;
	Node *calloutArgsWithExpr;
	Node *stringLiteralBeforeComma;
	Node *calloutArgsWithStringLiteral;

	CalloutArgsNode(Node *l, Node *m, Node *n, Node *o, Node *p, Node *q)
	{	
		expr = l;
		stringLiteral = m;
		exprBeforeComma = n;
		calloutArgsWithExpr = o;
		stringLiteralBeforeComma = p;
		calloutArgsWithStringLiteral = q;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};


class ExprNode : public Node
{
	public:
	Node *location;
	Node *methodCall;
	Node *literal;
	Node *exprBeforeOperator;
	Node *operator1;
	Node *exprAfterOperator;
	Node *exprInsideParen;
	
	ExprNode(Node *l, Node *m, Node *n, Node *o, Node *p, Node *q, Node *r)
	{	
		location = l;
		methodCall = m;
		literal = n;
		exprBeforeOperator = o;
		operator1 = p;
		exprAfterOperator = q;
		exprInsideParen = r;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class LiteralNode : public Node
{
	public:
	Node *intLiteral;
	Node *charLiteral;
	Node *boolLiteral;

	LiteralNode(Node *l, Node *m, Node *n)
	{	
		intLiteral = l;
		charLiteral = m;
		boolLiteral = n;
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};


class BoolLiteralNode : public Node
{
	public:
	string boolLiteral;

	BoolLiteralNode(char *l)
	{	
		boolLiteral = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class IntLiteralNode : public Node
{
	public:
	string intLiteral;

	IntLiteralNode(char *l)
	{	
		intLiteral = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};

class TypeNode : public Node
{
	public:
	string type;

	TypeNode(char *l)
	{	
		type = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};
class AssignOpNode : public Node
{
	public:
	string assignOp;
	AssignOpNode(char *l)
	{	
		assignOp = string(l);
	}

	Value *genCode(AbstractVisitor &visitor)
	{
		return visitor.codeGen(*this);
	}
};


// Visitor class declaration with codeGens corresponding to each AST node type
class Visitor : public AbstractVisitor
{
	public:
		Value *codeGen(ProgramNode &node);
		Value *codeGen(FieldDeclsNode &node);
		Value *codeGen(FieldDeclNode &node);
		Value *codeGen(IdentifiersNode &node);
		Value *codeGen(Identifier1Node &node);
		Value *codeGen(MethodDeclsNode &node);
		Value *codeGen(MethodDeclNode &node);
		Value *codeGen(ParamsNode &node);
		Value *codeGen(BlockNode &node);
		Value *codeGen(VarDeclsNode &node);
		Value *codeGen(VarDeclNode &node);
		Value *codeGen(DeclsNode &node);
		Value *codeGen(StatementsNode &node);
		Value *codeGen(StatementNode &node);
		Value *codeGen(MethodCallNode &node);
		Value *codeGen(PassParamsNode &node);
		Value *codeGen(MethodNameNode &node);
		Value *codeGen(LocationNode &node);
		Value *codeGen(CalloutArgsNode &node);
		Value *codeGen(ExprNode &node);
		Value *codeGen(LiteralNode &node);
		Value *codeGen(BoolLiteralNode &node);
		Value *codeGen(IntLiteralNode &node);
		Value *codeGen(CharLiteralNode &node);
		Value *codeGen(StringLiteralNode &node);
		Value *codeGen(TypeNode &node);
		Value *codeGen(AssignOpNode &node);
		Value *codeGen(IdentifierNode &node);
		Value *codeGen(ReturnStrNode &node);
		Value *codeGen(BreakStrNode &node);
		Value *codeGen(ContinueStrNode &node);
		Value *codeGen(OperatorNode &node);
};
