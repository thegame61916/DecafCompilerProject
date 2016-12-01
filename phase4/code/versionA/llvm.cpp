// Definitions of code generators for different type of nodes in AST

#include "llvm.h"

static Type *llvmLocalType = NULL;
static vector<string> paramNames;
static vector<Type *> paramTypes;
static vector<Value *> args;
static IRBuilder<> Builder(getGlobalContext());
static int debug = 0;
extern CodeGenManager manager;

void printDebug(string s)
{
	if(debug)
		cout<<s;
}

// Starting point for code generation
void CodeGenManager::genLLCode(ProgramNode* root)
{
	printDebug("Starting Code Generation\n");
	vector<Type*> argTypes;
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainF = Function::Create(ftype, GlobalValue::InternalLinkage, "Class Program", module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entryBlock", mainF, 0);

	pushBlock(bblock);
	Visitor visit;
	root->genCode(visit);
	popBlock();

	printDebug("Code generation completed\n\n");
	cout << "================================================\n";
	cout << "Generated code is in file LLVM_output \n";
	cout << "================================================\n";
	PassManager pm;
	string err;
	raw_fd_ostream *fd = new raw_fd_ostream("LLVM_output", err);
	pm.add(createPrintModulePass(fd));
	pm.run(*module);
	fd->close();
	delete fd;
}

// **************************************************************************************************
// Method defintions for Visitor class i.e. code generation for every AST node Type
// **************************************************************************************************
Value * Visitor::codeGen(ProgramNode &node)
{
	Value *v = NULL;
	if(node.fieldDecls)
		v = node.fieldDecls->genCode(*this);
	if(node.methodDecls)
		v = node.methodDecls->genCode(*this);
	return v;
}

Value * Visitor::codeGen(FieldDeclsNode &node)
{
	Value *v = NULL;
	if(node.fieldDecls)
		v = node.fieldDecls->genCode(*this);
	if(node.fieldDecl)
		v = node.fieldDecl->genCode(*this);
	return v;
}

Value * Visitor::codeGen(FieldDeclNode &node)
{	
	Value *v = NULL;
	if(node.type)
		v = node.type->genCode(*this);
	if(node.identifiers)
		v = node.identifiers->genCode(*this);
	return v;
}

Value * Visitor::codeGen(IdentifiersNode &node)
{
	Value *v = NULL;
	if(node.identifiers1)
		v = node.identifiers1->genCode(*this);
	if(node.identifiers)
		v = node.identifiers->genCode(*this);
	return v;
}

Value * Visitor::codeGen(Identifier1Node &node)
{
	Value *v;
	Value *identifier;
	if(node.identifier)
	{
		identifier = node.identifier->genCode(*this);
		string id = ((ConstantDataSequential*)identifier)->getAsCString();
		printDebug("Identifier Found: " + id + "\n");
		AllocaInst *alloc = new AllocaInst(llvmLocalType, id, manager.getCurrentBlock());
		manager.localVars()[id] = alloc;
		v=alloc;
	}
    return v;
}

Value * Visitor::codeGen(MethodDeclsNode &node)
{
	Value *v = NULL;
	if(node.methodDecl)
		v = node.methodDecl->genCode(*this);
	if(node.methodDecls)
		v = node.methodDecls->genCode(*this);
	return NULL;
}

Value * Visitor::codeGen(MethodDeclNode &node)
{
	Value *methodName;
	Type *returnType = NULL;
	string mName;
	paramNames.resize(0);
	paramTypes.resize(0);
	if(node.identifier)
	{
		methodName = node.identifier->genCode(*this);
		mName = ((ConstantDataSequential*)methodName)->getAsCString();
	}
	if(node.params)
		node.params->genCode(*this);
	if(node.type)
	{
		node.type->genCode(*this);
		returnType = llvmLocalType;
	}	
	printDebug("Generating code for method : " + mName + "\n");
	FunctionType *ft = FunctionType::get(returnType, paramTypes, false);
	Function *func = Function::Create(ft, GlobalValue::InternalLinkage, mName, manager.module);
	BasicBlock *bb = BasicBlock::Create(getGlobalContext(), "entryBlock", func, 0);
	Builder.SetInsertPoint(bb);
	manager.pushBlock(bb);
	for(int i=0; i<paramNames.size(); i++)
	{
	    AllocaInst *alloc = new AllocaInst(paramTypes[i], paramNames[i], manager.getCurrentBlock());
	    manager.localVars()[paramNames[i]] = alloc;
	}
	if(node.block)
		node.block->genCode(*this);
	ReturnInst::Create(getGlobalContext(), bb);	
	manager.popBlock();
	printDebug("Code generatin completed for method : " + mName + "\n");
	return func;
}

Value * Visitor::codeGen(ParamsNode &node)
{
	if(node.type)
	{
		node.type->genCode(*this);
		paramTypes.push_back(llvmLocalType);
		if(node.identifier)
		{
			Value *id = node.identifier->genCode(*this);
			paramNames.push_back(((ConstantDataSequential*)id)->getAsCString());
		}
	}
	if(node.params)
		node.params->genCode(*this);
	return NULL;
}

Value * Visitor::codeGen(BlockNode &node)
{
	Value *v = NULL;
	if(node.varDecls)
	{
		v = node.varDecls->genCode(*this);
	}
	if(node.statements)
	{
		v = node.statements->genCode(*this);
	}
	return v;
}

Value * Visitor::codeGen(VarDeclsNode &node)
{
	Value *v = NULL;
	if(node.varDecl)
		v = node.varDecl->genCode(*this);
	if(node.varDecls)
		v = node.varDecls->genCode(*this);
	return v;
}

Value * Visitor::codeGen(VarDeclNode &node)
{
	Value *v = NULL;
	if(node.type)
		v = node.type->genCode(*this);
	if(node.decls)
		v = node.decls->genCode(*this);
	return v;
}

Value * Visitor::codeGen(DeclsNode &node)
{
	Value *v = NULL;
	if(node.identifier)
	{
		Value * id = node.identifier->genCode(*this);
		string varName = ((ConstantDataSequential*)id)->getAsCString();
		printDebug("Identifier Found: " + varName + "\n");
		AllocaInst *alloc = new AllocaInst(llvmLocalType, varName, manager.getCurrentBlock());
		manager.localVars()[varName] = alloc;
	}
	if(node.decls)
		v = node.decls->genCode(*this);
    return v;
}

Value * Visitor::codeGen(StatementsNode &node)
{
	Value *v;
	if(node.statement)
		v = node.statement->genCode(*this);
	if(node.statements)
		v = node.statements->genCode(*this);
	return v;
}

Value * Visitor::codeGen(StatementNode &node)
{
	Value * V = NULL;
	if(node.assignOp)
	{	
		printDebug("Generating code for assignment operation\n");
		Value *rhs = NULL;
		Value *o = node.assignOp->genCode(*this);
		string op = ((ConstantDataSequential*)o)->getAsCString();
		string id = "";
		Instruction::BinaryOps inst;
		Value *binOp = NULL;
		
		if(node.location)
		{
			id = ((IdentifierNode*)(((LocationNode*)node.location)->identifier))->identifier;
			if(manager.localVars().find(id) == manager.localVars().end())
			{
				cout<<"ERROR: Variable not declared: "<<id<<"\n";
				return NULL;
			}
		}
		if(node.Expr)
			rhs = node.Expr->genCode(*this);
				
		if(op == "+=")
		{
			inst=Instruction::Add;
			if(manager.localVars()[id]!=NULL && rhs!=NULL)
				binOp = BinaryOperator::Create(inst, manager.localVars()[id], rhs, "", manager.getCurrentBlock());
        }
    	else if(op == "-=")
    	{
    		inst = Instruction::Sub;
			if(manager.localVars()[id]!=NULL && rhs!=NULL)
				binOp = BinaryOperator::Create(inst, manager.localVars()[id], rhs, "", manager.getCurrentBlock());
        }

		if(binOp!=NULL)
			rhs = new StoreInst(binOp, manager.localVars()[id], manager.getCurrentBlock());
		else if(rhs!=NULL)
			rhs = new StoreInst(rhs, manager.localVars()[id], manager.getCurrentBlock());
		printDebug("Code generation complete for assignment operation\n");
		return rhs;
    }
	if(node.methodCall)
		return node.methodCall->genCode(*this);
	
	if(node.exprInsideParen)
	{
		printDebug("Generating code for if\n");
        Value* condVal = node.exprInsideParen->genCode(*this);
        Function *parentFunc = Builder.GetInsertBlock()->getParent();
        BasicBlock *ifBlock = BasicBlock::Create(getGlobalContext(), "if", parentFunc);
        BasicBlock *elseBlock = BasicBlock::Create(getGlobalContext(), "else");
        BasicBlock *mergeBlock = BasicBlock::Create(getGlobalContext(), "ifCont");
        Builder.CreateCondBr(condVal, ifBlock, elseBlock);
        Builder.SetInsertPoint(ifBlock);
        BasicBlock *bb = BasicBlock::Create(getGlobalContext(), "entryBlock", parentFunc, 0);
		Builder.SetInsertPoint(bb);
		manager.pushBlock(bb);
        Value *ifV =  node.blockAfterIf->genCode(*this);
		manager.popBlock();
        Builder.CreateBr(mergeBlock);
        ifBlock = Builder.GetInsertBlock();
        parentFunc->getBasicBlockList().push_back(elseBlock);
        Builder.SetInsertPoint(elseBlock);
        Value *elseV =  node.blockAfterElse->genCode(*this);
        Builder.CreateBr(mergeBlock);
        elseBlock = Builder.GetInsertBlock();
        parentFunc->getBasicBlockList().push_back(mergeBlock);
        Builder.SetInsertPoint(mergeBlock);
        PHINode *PN = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()), 2,"iftmp");
        PN->addIncoming(ifV, ifBlock);
        PN->addIncoming(elseV, elseBlock);
		printDebug("Code generation complete for if\n");
        return PN;
	}
	if(node.identifierInsideFor)
	{
		printDebug("Generating code for for loop\n");
        Value *initExp = node.exprInsideFor->genCode(*this);
        Value *o = node.identifierInsideFor->genCode(*this);
        string loopVar = ((ConstantDataSequential*)o)->getAsCString();
        Function *parentFunc = Builder.GetInsertBlock()->getParent();
        IRBuilder<> tmpB(&parentFunc->getEntryBlock(), parentFunc->getEntryBlock().begin());
        AllocaInst *alloc = tmpB.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, loopVar.c_str());
        Builder.CreateStore(initExp, alloc);
        BasicBlock *preheaderBlock = Builder.GetInsertBlock();
        BasicBlock *loopBlock = BasicBlock::Create(getGlobalContext(), "for", parentFunc);
        Builder.CreateBr(loopBlock);
        Builder.SetInsertPoint(loopBlock);
        PHINode *loopVariable = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()), 2, string(loopVar));
        loopVariable->addIncoming(initExp, preheaderBlock);
        AllocaInst *tempVal = (AllocaInst *)(manager.localVars()[loopVar]);
        manager.localVars()[loopVar] = alloc;
        BasicBlock *bb = BasicBlock::Create(getGlobalContext(), "entryBlock", parentFunc, 0);
		Builder.SetInsertPoint(bb);
		manager.pushBlock(bb);
        node.blockInsideFor->genCode(*this);
		manager.popBlock();
        Value* incVal = ConstantInt::get(getGlobalContext(), APInt(32,1));
        Value *curVal = Builder.CreateLoad(alloc, string(loopVar));
        Value *nextVal = Builder.CreateAdd(curVal, incVal, "nextvar");
        Builder.CreateStore(nextVal, alloc);
        Value *exitCond = node.exprInsideForAfterComma->genCode(*this);
        exitCond = Builder.CreateICmpULE(loopVariable, exitCond, "exitCond");
        BasicBlock *endLoopBlock = Builder.GetInsertBlock();
        BasicBlock *blockAfterLoop = BasicBlock::Create(getGlobalContext(), "afterFor", parentFunc);
        Builder.CreateCondBr(exitCond, loopBlock, blockAfterLoop);
        Builder.SetInsertPoint(blockAfterLoop);
        loopVariable->addIncoming(nextVal, endLoopBlock);
        if (tempVal)
            manager.localVars()[loopVar] = tempVal;
        else
            manager.localVars().erase(string(loopVar));

		printDebug("Code generation complete for for loop\n");
		return NULL;
	}
	if(node.returnStr)
	{
		printDebug("Generating code for return statement\n");
		if(node.exprAfterReturn)
		{
			Value *val=node.exprAfterReturn->genCode(*this);
			return ReturnInst::Create(getGlobalContext(), val, manager.getCurrentBlock());
		}
		else
		{
			return ReturnInst::Create(getGlobalContext(), manager.getCurrentBlock());
		}
	}
	if(node.breakStr)
		return ConstantInt::get(getGlobalContext(), APInt(32, 1));
	if(node.continueStr)
		return ConstantInt::get(getGlobalContext(), APInt(32, 1));
	if(node.block)
		return node.block->genCode(*this);
	return NULL;
}

Value * Visitor::codeGen(MethodCallNode &node)
{
	printDebug("Generating code for method call\n");
	Function *function = NULL;
	if(node.methodName)
	{
		Value *mn = node.methodName->genCode(*this);
		string callee = ((ConstantDataSequential*)mn)->getAsCString();
		function = manager.module->getFunction(callee);
		if(function==NULL)
		{
			cout<<"ERROR: Function not declared: "<<callee<<"\n";
			return NULL;
		}
		args.resize(0);
		if(node.passParams)
			node.passParams->genCode(*this);
	}
	if(node.stringLiteralInsideParen)
	{
		Value *mn = node.stringLiteralInsideParen->genCode(*this);;
		string callee = ((ConstantDataSequential*)mn)->getAsCString();
		function = manager.module->getFunction(callee);
		if(function==NULL)
		{
			cout<<"ERROR: Function not declared: "<<callee<<"\n";
			return NULL;
		}
		args.resize(0);
		if(node.callOutArgs)
			node.callOutArgs->genCode(*this);
	}
	CallInst *call = CallInst::Create(function, args, "", manager.getCurrentBlock());
	printDebug("Code generation complete for method call\n");
	return call;
}

Value * Visitor::codeGen(PassParamsNode &node)
{
	if(node.expr)
		args.push_back(node.expr->genCode(*this));
	if(node.passParams)
		node.passParams->genCode(*this);
	return NULL;
}

Value * Visitor::codeGen(MethodNameNode &node)
{
	return node.identifier->genCode(*this);
}

Value * Visitor::codeGen(LocationNode &node)
{	
	string id;
	if(node.identifier)
	{
		Value * val = node.identifier->genCode(*this);
		id = ((ConstantDataSequential*)val)->getAsCString();
	}
	if (manager.localVars().find(id) == manager.localVars().end()) 
	{   
		cout<<"ERROR: Variable not declared: "<<id<<"\n";
		return NULL;
    }   
     return new LoadInst(manager.localVars()[id], "", false, manager.getCurrentBlock());
}

Value * Visitor::codeGen(CalloutArgsNode &node)
{
	if(node.expr)
		args.push_back(node.expr->genCode(*this));
	if(node.stringLiteral)
	{
		args.push_back(node.stringLiteral->genCode(*this));
	}
	if(node.exprBeforeComma)
		args.push_back(node.exprBeforeComma->genCode(*this));
	if(node.calloutArgsWithExpr)
		node.calloutArgsWithExpr->genCode(*this);
	if(node.stringLiteralBeforeComma)
	{
		args.push_back(node.stringLiteralBeforeComma->genCode(*this));
	}
	if(node.calloutArgsWithStringLiteral)
	{
		node.calloutArgsWithStringLiteral->genCode(*this);
	}
	return NULL;
}

Value * Visitor::codeGen(ExprNode &node)
{
	Value *v = NULL;
	if(node.location)
		v = node.location->genCode(*this);
	if(node.methodCall)
		v = node.methodCall->genCode(*this);
	if(node.literal)
	{
		v = node.literal->genCode(*this);
	}
	if(node.exprBeforeOperator)
	{
		printDebug("Generating code for binary opration\n");
		Value* lhs = node.exprBeforeOperator->genCode(*this);
    	Value* rhs = node.exprAfterOperator->genCode(*this);
        
		Value *o = node.operator1->genCode(*this);  
		string op = ((ConstantDataSequential*)o)->getAsCString();         
		Instruction::BinaryOps inst;
		if(op.compare("+") == 0)
			inst=Instruction::Add;
		if(op.compare("-") == 0)
			inst=Instruction::Sub;
		if(op.compare("*") == 0)
			inst=Instruction::Mul;
		if(op.compare("/") == 0)
			inst=Instruction::SDiv;
		if(op.compare("%") == 0)
			inst=Instruction::SRem;
		if(op.compare("&&") == 0)
			inst=Instruction::And;
		if(op.compare("||") == 0)
			inst=Instruction::Or;
		if(op.compare("<") == 0)
			return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULT, lhs, rhs, "", manager.getCurrentBlock());
		if(op.compare(">") == 0)
			return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGT, lhs, rhs, "", manager.getCurrentBlock());
		if(op.compare("<=") == 0)
			return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULE, lhs, rhs, "", manager.getCurrentBlock());
		if(op.compare(">=") == 0)
			return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGE, lhs, rhs, "", manager.getCurrentBlock());
		if(op.compare("==") == 0)
			return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, lhs, rhs, "", manager.getCurrentBlock());
		if(op.compare("!=") == 0)
			return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_NE, lhs, rhs, "", manager.getCurrentBlock());
		
		Value *binOp=NULL;

		if(lhs!=NULL && rhs!=NULL)
			binOp = BinaryOperator::Create(inst, lhs, rhs, "", manager.getCurrentBlock());
		printDebug("code generation complete for binary operation\n");
		return binOp;
	}
	else if(node.operator1)
	{
		printDebug("Generating code for unary operation\n");
		Value *o = node.operator1->genCode(*this);
		string op = ((ConstantDataSequential*)o)->getAsCString();  
		Value* rhs = node.exprAfterOperator->genCode(*this);
		Value* lhs = ConstantInt::get(getGlobalContext(), APInt(32, 0));
		Value *binOp=NULL;
		Instruction::BinaryOps inst;
		if(op.compare("!") == 0)
		{
			lhs = ConstantInt::get(getGlobalContext(), APInt(1, 1));
			inst=Instruction::Sub;
		}
		if(op.compare("-") == 0)
			inst=Instruction::Sub;
			
		if(lhs!=NULL && rhs!=NULL)
			binOp = BinaryOperator::Create(inst, lhs, rhs, "", manager.getCurrentBlock());
		printDebug("code generation complete for unary operation\n");
		return binOp;
	}
	if(node.exprInsideParen)
		v = node.exprInsideParen->genCode(*this);
	return v;
}

Value * Visitor::codeGen(LiteralNode &node)
{
	if(node.intLiteral)
	{
		return node.intLiteral->genCode(*this);
	}
	if(node.charLiteral)
	{
		return node.charLiteral->genCode(*this);
	}
	if(node.boolLiteral)
	{
		return node.boolLiteral->genCode(*this);
	}
	return NULL;
}

Value * Visitor::codeGen(BoolLiteralNode &node)
{
	int bl = 1;
	if(node.boolLiteral == "false")
		bl = 0;
	return ConstantInt::get(getGlobalContext(), APInt(1, bl));
}

Value * Visitor::codeGen(IntLiteralNode &node)
{
	return ConstantInt::get(getGlobalContext(), APInt(32, atoi(node.intLiteral.c_str())));
}

Value * Visitor::codeGen(CharLiteralNode &node)
{
	return ConstantDataArray::getString(getGlobalContext(), node.charLiteral, true);
}

Value * Visitor::codeGen(StringLiteralNode &node)
{
	return ConstantDataArray::getString(getGlobalContext(), node.stringLiteral, true);
}

Value * Visitor::codeGen(TypeNode &node)
{
    if(node.type == "int")
    {
        llvmLocalType = Type::getInt64Ty(getGlobalContext());
    }
    else if(node.type == "boolean")
    {
        llvmLocalType = Type::getInt1Ty(getGlobalContext());
    }
    else
    {
    	llvmLocalType = Type::getVoidTy(getGlobalContext());
    }
	return NULL;
}

Value * Visitor::codeGen(AssignOpNode &node)
{
	return ConstantDataArray::getString(getGlobalContext(), node.assignOp, true);
}

Value * Visitor::codeGen(IdentifierNode &node)
{
	return ConstantDataArray::getString(getGlobalContext(), node.identifier, true);
}

Value * Visitor::codeGen(ReturnStrNode &node)
{
	return NULL;
}
Value * Visitor::codeGen(BreakStrNode &node)
{
	return NULL;
}
Value * Visitor::codeGen(ContinueStrNode &node)
{
	return NULL;
}

Value * Visitor::codeGen(OperatorNode &node)
{
	return ConstantDataArray::getString(getGlobalContext(), node.operator1, true);
}
