// Classes corresponding to all the non terminal nodes and corresponding visitors

#include <string>
#include <iostream>
#include <sstream>
#include<fstream>

using namespace std;

class AbstractVisitor;
extern string output;
extern string localType;
extern int declarationCount;
extern int methodCount;
extern fstream fout;

class Node
{
	public:
		virtual void display(AbstractVisitor &visitor, string tabs) = 0;
};

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

class AbstractVisitor
{
	public:
		virtual void visit(ProgramNode &node, string tabs) = 0;
		virtual void visit(FieldDeclsNode &node, string tabs) = 0;
		virtual void visit(FieldDeclNode &node, string tabs) = 0;
		virtual void visit(IdentifiersNode &node, string tabs) = 0;
		virtual void visit(Identifier1Node &node, string tabs) = 0;
		virtual void visit(MethodDeclsNode &node, string tabs) = 0;
		virtual void visit(MethodDeclNode &node, string tabs) = 0;
		virtual void visit(ParamsNode &node, string tabs) = 0;
		virtual void visit(BlockNode &node, string tabs) = 0;
		virtual void visit(VarDeclsNode &node, string tabs) = 0;
		virtual void visit(VarDeclNode &node, string tabs) = 0;
		virtual void visit(DeclsNode &node, string tabs) = 0;
		virtual void visit(StatementsNode &node, string tabs) = 0;
		virtual void visit(StatementNode &node, string tabs) = 0;
		virtual void visit(MethodCallNode &node, string tabs) = 0;
		virtual void visit(PassParamsNode &node, string tabs) = 0;
		virtual void visit(MethodNameNode &node, string tabs) = 0;
		virtual void visit(LocationNode &node, string tabs) = 0;
		virtual void visit(CalloutArgsNode &node, string tabs) = 0;
		virtual void visit(ExprNode &node, string tabs) = 0;
		virtual void visit(LiteralNode &node, string tabs) = 0;
		virtual void visit(BoolLiteralNode &node, string tabs) = 0;
		virtual void visit(IntLiteralNode &node, string tabs) = 0;
		virtual void visit(TypeNode &node, string tabs) = 0;
		virtual void visit(AssignOpNode &node, string tabs) = 0;
		
		virtual void visit(IdentifierNode &node, string tabs) = 0;
		virtual void visit(ReturnStrNode &node, string tabs) = 0;
		virtual void visit(BreakStrNode &node, string tabs) = 0;
		virtual void visit(ContinueStrNode &node, string tabs) = 0;
		virtual void visit(StringLiteralNode &node, string tabs) = 0;
		virtual void visit(CharLiteralNode &node, string tabs) = 0;
		virtual void visit(OperatorNode &node, string tabs) = 0;
};

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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
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
	void display(AbstractVisitor &visitor, string tabs)
	{
		visitor.visit(*this, tabs);
	}
};

// Visitor class to visit all the nodes
class Visitor : public AbstractVisitor
{
	public:
		void visit(ProgramNode &node, string tabs)
		{
			stringstream countOutD;
			stringstream countOutS;
			tabs = tabs + "\t";
			if(node.fieldDecls)
				node.fieldDecls->display(*this, tabs+"\t");
			output = output + "\t</field_declarations>\n";
			string temp = output;
			output = "";
			if(node.methodDecls)
				node.methodDecls->display(*this, tabs+"\t");
			output = output + "\t</methods>\n";
			
			countOutD << declarationCount;
			countOutS << methodCount;
			
			output = "\t<methods count=\"" + countOutS.str() + "\">\n" + output;
			output = temp + output;
			output = "\t<field_declarations count=\"" + countOutD.str() + "\">\n" + output;
			output = "<program>\n" + output;
			output = output + "</program>\n";
			fout<<output;
		}

		void visit(FieldDeclsNode &node, string tabs)
		{
			if(node.fieldDecls)
				node.fieldDecls->display(*this, tabs);
			if(node.fieldDecl)
				node.fieldDecl->display(*this, tabs);
		}

		void visit(FieldDeclNode &node, string tabs)
		{
			if(node.type)
				node.type->display(*this, tabs);
			if(node.identifiers)
				node.identifiers->display(*this, tabs);
		}

		void visit(IdentifiersNode &node, string tabs)
		{
			if(node.identifiers1)
				node.identifiers1->display(*this, tabs);
			if(node.identifiers)
				node.identifiers->display(*this, tabs);
		}

		void visit(Identifier1Node &node, string tabs)
		{
			declarationCount++;
			if(node.intLiteral)
			{
				output = output + tabs+"Array\n";
				output = output + tabs+"<declaration name=\"";
				if(node.identifier)
					node.identifier->display(*this, tabs);
				output = output + "\"";
				output = output + " count=\"";
				node.intLiteral->display(*this, tabs);			
				output = output + "\"";
				output = output + " type=\""+localType+"\" />\n";
			}
			else
			{
				output = output + tabs+"Normal\n";
				output = output + tabs+"<declaration name=\"";
				if(node.identifier)
					node.identifier->display(*this, tabs);
				output = output + "\"";
				output = output + " type=\""+localType+"\" />\n";
			}
		}

		void visit(MethodDeclsNode &node, string tabs)
		{
			if(node.methodDecl)
				node.methodDecl->display(*this, tabs);
			if(node.methodDecls)
				node.methodDecls->display(*this, tabs);
		}

		void visit(MethodDeclNode &node, string tabs)
		{
			methodCount++;
			output = output + tabs+"<method name=\"";
			if(node.identifier)
				node.identifier->display(*this, tabs);
			output = output + "\" return_type=\"";
			if(node.type)
			{
				node.type->display(*this, tabs);
				output = output + localType+"\"";
			}
			else
				output = output + "void";
			output = output + ">\n";
			if(node.params)
			{
				output = output + tabs + "\t" +"<params>\n";
				node.params->display(*this, tabs + "\t\t");
				output = output + tabs+"\t"+"</params>\n";
			}
			if(node.block)
			{
				output = output + tabs + "\t" +"<body>\n";
				node.block->display(*this, tabs + "\t\t");
				output = output + tabs+"\t"+"</body>\n";
			}
			output = output + tabs+"</method>\n";
		}

		void visit(ParamsNode &node, string tabs)
		{
			if(node.type)
			{
				output = output + tabs+"<param type=\"";
				node.type->display(*this, tabs);
				output = output + localType+"\" name=\"";
				if(node.identifier)
					node.identifier->display(*this, tabs);
				output = output + "\">\n";
			}
			if(node.params)
				node.params->display(*this, tabs);
		}

		void visit(BlockNode &node, string tabs)
		{
			if(node.varDecls)
			{
				output = output + tabs+"<locals>\n";
				node.varDecls->display(*this, tabs+"\t");
				output = output + tabs+"</locals>\n";
			}
			if(node.statements)
			{
				output = output + tabs+"<statements>\n";
				node.statements->display(*this, tabs + "\t");
				output = output + tabs+"</statements>\n";
			}
		}

		void visit(VarDeclsNode &node, string tabs)
		{
			if(node.varDecl)
				node.varDecl->display(*this, tabs);
			if(node.varDecls)
				node.varDecls->display(*this, tabs);
		}

		void visit(VarDeclNode &node, string tabs)
		{
			if(node.type)
				node.type->display(*this, tabs);
			if(node.decls)
				node.decls->display(*this, tabs);
		}

		void visit(DeclsNode &node, string tabs)
		{
			if(node.identifier)
			{
				output = output + tabs+"<local name=\"";
				if(node.identifier)
					node.identifier->display(*this, tabs);
				output = output + "\"";
				output = output + " type=\""+localType+"\" />\n";
			}
			if(node.decls)
				node.decls->display(*this, tabs);
		}

		void visit(StatementsNode &node, string tabs)
		{
			if(node.statement)
				node.statement->display(*this, tabs);
			if(node.statements)
				node.statements->display(*this, tabs);
		}

		void visit(StatementNode &node, string tabs)
		{
			if(node.assignOp)
			{	
				output = output + tabs+"<assignment>\n";
				node.assignOp->display(*this, tabs + "\t");
				if(node.location)
					node.location->display(*this, tabs + "\t");
				if(node.Expr)
					node.Expr->display(*this, tabs + "\t");
				output = output + tabs+"</assignment>\n";
			}
			if(node.methodCall)
				node.methodCall->display(*this, tabs);
			if(node.exprInsideParen)
				node.exprInsideParen->display(*this, tabs);
			if(node.blockAfterIf)
				node.blockAfterIf->display(*this, tabs);
			if(node.blockAfterElse)
				node.blockAfterElse->display(*this, tabs);
			if(node.identifierInsideFor)
			{
				output = output + tabs + "<for>\n";
				output = output + tabs+"\t"+"identifier value=\"";
				node.identifierInsideFor->display(*this, tabs);
				output = output + ">\n";
				if(node.exprInsideFor)
					node.exprInsideFor->display(*this, tabs+"\t");
				if(node.exprInsideForAfterComma)
					node.exprInsideForAfterComma->display(*this, tabs+"\t");
				if(node.blockInsideFor)
					node.blockInsideFor->display(*this, tabs+"\t");
				output = output + tabs + "</for>\n";
			}
			if(node.returnStr)
				node.returnStr->display(*this, tabs);
			if(node.exprAfterReturn)
				node.exprAfterReturn->display(*this, tabs);
			if(node.breakStr)
				node.breakStr->display(*this, tabs);
			if(node.continueStr)
				node.continueStr->display(*this, tabs);
			if(node.block)
				node.block->display(*this, tabs);
		}

		void visit(MethodCallNode &node, string tabs)
		{
			if(node.methodName)
			{
				output = output + tabs+"<calling method name=\"";
				node.methodName->display(*this, tabs);
				output = output + "\">\n";
				if(node.passParams)
					node.passParams->display(*this, tabs+"\t");
				output = output + tabs+"</calling>\n";
			}
			if(node.stringLiteralInsideParen)
			{
				output = output + tabs+"<callout function=";
				node.stringLiteralInsideParen->display(*this, tabs);
				output = output + ">\n";
				if(node.callOutArgs)
					node.callOutArgs->display(*this, tabs + "\t");
				output = output + tabs+"</callout>\n";
			}
		}

		void visit(PassParamsNode &node, string tabs)
		{
			if(node.expr)
				node.expr->display(*this, tabs);
			if(node.passParams)
				node.passParams->display(*this, tabs);
		}

		void visit(MethodNameNode &node, string tabs)
		{
			if(node.identifier)
				node.identifier->display(*this, tabs);
		}

		void visit(LocationNode &node, string tabs)
		{
			if(node.expr)
			{
				output = output + tabs+"Array\n";
				if(node.identifier)
				{
					output = output +  tabs +"<location id=\"";
					node.identifier->display(*this, tabs);
					output = output + "\"/>\n";
				}
				output = output + tabs + "\t"+"<position>\n";
				node.expr->display(*this, tabs + "\t\t");
				output = output + tabs + "\t"+"</position>\n";
				output = output +  tabs +"</location>\n";
			}
			else
			{
				output = output + tabs+"Normal\n";
				if(node.identifier)
				{
					output = output +  tabs +"<location id=\"";
					node.identifier->display(*this, tabs);
					output = output + "\"/>\n";
				}
			}
		}

		void visit(CalloutArgsNode &node, string tabs)
		{
			if(node.expr)
				node.expr->display(*this, tabs);
			if(node.stringLiteral)
			{
				output = output + tabs + "<string value =";
				node.stringLiteral->display(*this, tabs);
				output = output + "/>\n";
			}
			if(node.exprBeforeComma)
				node.exprBeforeComma->display(*this, tabs);
			if(node.calloutArgsWithExpr)
				node.calloutArgsWithExpr->display(*this, tabs);
			if(node.stringLiteralBeforeComma)
			{
				output = output + tabs + "<string value =";
				node.stringLiteralBeforeComma->display(*this, tabs);
				output = output + "/>\n";
			}
			if(node.calloutArgsWithStringLiteral)
			{
				output = output + tabs + "<string value =";
				node.calloutArgsWithStringLiteral->display(*this, tabs);
				output = output + "/>\n";
			}
		}

		void visit(ExprNode &node, string tabs)
		{
			if(node.location)
				node.location->display(*this, tabs);
			if(node.methodCall)
				node.methodCall->display(*this, tabs);
			if(node.literal)
				node.literal->display(*this, tabs);
			if(node.exprBeforeOperator)
			{
				output = output +  tabs + "<binary_expression type=\"";
				if(node.operator1)
					node.operator1->display(*this, tabs);
				output = output + "\">\n";
				node.exprBeforeOperator->display(*this, tabs + "\t");
				if(node.exprAfterOperator)
					node.exprAfterOperator->display(*this, tabs + "\t");
				output = output +  tabs + "</binary_expression>\n";
			}
			else if(node.operator1)
			{
				output = output +  tabs + "<unary_expression type=\"";
				node.operator1->display(*this, tabs);
				output = output + "\">\n";
				if(node.exprAfterOperator)
					node.exprAfterOperator->display(*this, tabs + "\t");
				output = output +  tabs + "</unary_expression>\n";
			}
			if(node.exprInsideParen)
				node.exprInsideParen->display(*this, tabs);
		}

		void visit(LiteralNode &node, string tabs)
		{
			if(node.intLiteral)
			{
				output = output + tabs + "<integer value =\"";
				node.intLiteral->display(*this, tabs);
			}
			if(node.charLiteral)
			{
				output = output + tabs + "<boolean value =\"";
				node.charLiteral->display(*this, tabs);
			}
			if(node.boolLiteral)
			{
				output = output + tabs + "<character value =\"";
				node.boolLiteral->display(*this, tabs);
			}
			output = output + "\"/>\n";
		}

		void visit(BoolLiteralNode &node, string tabs)
		{
			output = output + node.boolLiteral;
		}

		void visit(IntLiteralNode &node, string tabs)
		{
			output = output + node.intLiteral;
		}
		
		void visit(CharLiteralNode &node, string tabs)
		{
			output = output + node.charLiteral;
		}
		
		void visit(StringLiteralNode &node, string tabs)
		{
			output = output + node.stringLiteral;
		}

		void visit(TypeNode &node, string tabs)
		{
			localType = node.type; 
		}

		void visit(AssignOpNode &node, string tabs)
		{
		}
		
		void visit(IdentifierNode &node, string tabs)
		{
			output = output + node.identifier;
		}
		void visit(ReturnStrNode &node, string tabs)
		{
		}
		void visit(BreakStrNode &node, string tabs)
		{
		}
		void visit(ContinueStrNode &node, string tabs)
		{
		}
		
		void visit(OperatorNode &node, string tabs)
		{
			if(node.operator1.compare("+") == 0)
				output = output + "addition";
			if(node.operator1.compare("-") == 0)
				output = output + "minus";
			if(node.operator1.compare("*") == 0)
				output = output + "multiplication";
			if(node.operator1.compare("/") == 0)
				output = output + "division";
			if(node.operator1.compare("%") == 0)
				output = output + "remainder";
			if(node.operator1.compare("<") == 0)
				output = output + "less_than";
			if(node.operator1.compare(">") == 0)
				output = output + "greater_than";
			if(node.operator1.compare("<=") == 0)
				output = output + "less_equal";
			if(node.operator1.compare(">=") == 0)
				output = output + "greater_equal";
			if(node.operator1.compare("==") == 0)
				output = output + "is_equal";
			if(node.operator1.compare("!=") == 0)
				output = output + "is_not_equal";
			if(node.operator1.compare("&&") == 0)
				output = output + "and";
			if(node.operator1.compare("||") == 0)
				output = output + "or";
			if(node.operator1.compare("!") == 0)
				output = output + "not";
		}
};

