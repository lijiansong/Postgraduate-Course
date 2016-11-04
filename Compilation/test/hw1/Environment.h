//==--- tools/clang-check/ClangInterpreter.cpp - Clang Interpreter tool --------------===//
//===----------------------------------------------------------------------===//
#include <stdio.h>

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/Decl.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include<iostream>

using namespace clang;
using namespace std;

class StackFrame {
   /// StackFrame maps Variable Declaration to Value
   /// Which are either integer or addresses (also represented using an Integer value)
   std::map<Decl*, int> mVars;
   std::map<Stmt*, int> mExprs;
   /// The current stmt
   Stmt * mPC;
public:
   StackFrame() : mVars(), mExprs(), mPC() {
   }

   void bindDecl(Decl* decl, int val) {
      mVars[decl] = val;
   }
   int getDeclVal(Decl * decl) {
      assert (mVars.find(decl) != mVars.end());
      return mVars.find(decl)->second;
   }
   void bindStmt(Stmt * stmt, int val) {
	   mExprs[stmt] = val;
   }
   int getStmtVal(Stmt * stmt) {
	   assert (mExprs.find(stmt) != mExprs.end());
	   return mExprs[stmt];
   }
   void setPC(Stmt * stmt) {
	   mPC = stmt;
   }
   Stmt * getPC() {
	   return mPC;
   }
};

/// Heap maps address to a value
/*
class Heap {
   /// The allocated bufs, key is the address, val is its size
   std::map<int, int> mBufs;
   /// The map that maps address to value
   std::map<int, int> mContents;
public:
   int Malloc(int size) {
      assert (mBufs.find(addr) == mHeap.end());
      /// Allocate the buf
      int * buf = malloc(size * sizeof(int) );
      mBufs.insert(std::make_pair(addr, size));

      /// Initialize the Content
      for (int i=0; i<size; i ++) {
         mContents.insert(std::make_pair(buf+i, 0));
      }
      return buf;
   } 
   void Free (int addr) {
      /// Clear the contents;
      assert (mHeap.find(addr) != mHeap.end());
      int * buf = addr;
      int size = mHeap.find(addr)->second;
      for (int i = 0; i < size; i++) {
          assert (mContents.find(buf+i) != mContents.end());
          mContents.erase(buf+i);
      }
        /// Free the allocated buf
      free(mHeap.find(addr)->second);
   }
   void Update(int addr, int val) {
      assert (mContents.find(addr) != mContents.end());
      mContents[addr] = val;
   }
   int get(int addr) {
      assert (mContents.find(addr) != mContents.end());
      return mContents.find(addr)->second;
    }
};
*/

class Environment {
   std::vector<StackFrame> mStack;

   FunctionDecl * mFree;				/// Declartions to the built-in functions
   FunctionDecl * mMalloc;
   FunctionDecl * mInput;
   FunctionDecl * mOutput;

   FunctionDecl * mEntry;
public:
   /// Get the declartions to the built-in functions
   Environment() : mStack(), mFree(NULL), mMalloc(NULL), mInput(NULL), mOutput(NULL), mEntry(NULL) {
   }


   /// Initialize the Environment
   void init(TranslationUnitDecl * unit) {
	   for (TranslationUnitDecl::decl_iterator i =unit->decls_begin(), e = unit->decls_end(); i != e; ++ i) {
		   if (FunctionDecl * fdecl = dyn_cast<FunctionDecl>(*i) ) {
			   if (fdecl->getName().equals("FREE")) mFree = fdecl;
			   else if (fdecl->getName().equals("MALLOC")) mMalloc = fdecl;
			   else if (fdecl->getName().equals("GET")) mInput = fdecl;
			   else if (fdecl->getName().equals("PRINT")) mOutput = fdecl;
			   else if (fdecl->getName().equals("main")) mEntry = fdecl;
		   }
	   }
	   mStack.push_back(StackFrame());
   }

   FunctionDecl * getEntry() {
	   return mEntry;
   }

   //Support comparison operation
   void binop(BinaryOperator *bop) {
	   Expr * left = bop->getLHS();
	   Expr * right = bop->getRHS();

	//assignment operation
	   if (bop->isAssignmentOp()) {
		   int val = mStack.front().getStmtVal(right);
		   mStack.front().bindStmt(left, val);
		   //cout<<"-----assignment left val: "<<left->getStmtClassName()<<endl;
		   if (DeclRefExpr * declexpr = dyn_cast<DeclRefExpr>(left)) {
			   Decl * decl = declexpr->getFoundDecl();
			   mStack.front().bindDecl(decl, val);
		   }
	   }
	   int valRight=mStack.front().getStmtVal(right);
	   int valLeft=mStack.front().getStmtVal(left);
	   if(bop->isComparisonOp())
	   {
	   	switch(bop->getOpcode())
	   	{
	   		case BO_LT:
	   		if( valLeft < valRight )
	   			mStack.front().bindStmt(bop,true);
	   		else
	   			mStack.front().bindStmt(bop,false);
	   		break;

	   		case BO_GT:
	   		if( valLeft > valRight )
	   			mStack.front().bindStmt(bop,true);
	   		else
	   			mStack.front().bindStmt(bop,false);
	   		break;

	   		case BO_GE:
	   		if( valLeft >= valRight )
	   			mStack.front().bindStmt(bop,true);
	   		else
	   			mStack.front().bindStmt(bop,false);
	   		break;

	   		case BO_LE:
	   		if( valLeft <= valRight )
	   			mStack.front().bindStmt(bop,true);
	   		else
	   			mStack.front().bindStmt(bop,false);
	   		break;

	   		case BO_EQ:
	   		if( valLeft == valRight )
	   			mStack.front().bindStmt(bop,true);
	   		else
	   			mStack.front().bindStmt(bop,false);
	   		break;

	   		case BO_NE:
	   		if( valLeft != valRight )
	   			mStack.front().bindStmt(bop,true);
	   		else
	   			mStack.front().bindStmt(bop,false);
	   		break;
	   		default:
	   		cout<<" invalid input comparisons! "<<endl;
	   		break;
	   	}
	   }

	   if(bop->isAdditiveOp())
	   {
	   	switch(bop->getOpcode())
	   	{
	   		case BO_Add:
	   		mStack.front().bindStmt(bop,valLeft+valRight);
	   		break;

	   		case BO_Sub:
	   		mStack.front().bindStmt(bop,valLeft-valRight);
	   		break;
	   	}
	   }

	   if(bop->isMultiplicativeOp())
	   {
	   	switch(bop->getOpcode())
	   	{
	   		case BO_Mul:
	   		mStack.front().bindStmt(bop,valLeft * valRight);
	   		break;
	   	}
	   }
   }

   //UnaryOperator
   void unaryop(UnaryOperator* uop)
   {
   	Expr *expr=uop->getSubExpr();
   	int val=mStack.front().getStmtVal(expr);
   	//if( uop->isPrefix() )
   	//{
   		switch(uop->getOpcode())
   		{
	   		case UO_Plus:
	   		mStack.front().bindStmt(uop,val);
	   		break;

	   		
	   		case UO_Minus:
	   		mStack.front().bindStmt(uop,-val);
	   		break;
   		}
   	//}
   }

   void integerliteral(IntegerLiteral* integer)
   {
   	int val=(int)(integer->getValue().bitsToDouble());
   	mStack.front().bindStmt(integer,val);
   }

   bool getcond(/*BinaryOperator *bop*/Expr *expr)
   {
   	return mStack.front().getStmtVal(expr);
   }

   void funcdecl(FunctionDecl *func)
   {
   	
   }

   void parmdecl(ParmVarDecl *parm)
   {

   }

   void ret(ReturnStmt *retstmt)
   {
   	Expr *expr=retstmt->getRetValue();
   	int val=mStack.front().getStmtVal(expr);
   	mStack.front().bindStmt(retstmt,val);
   }

   void decl(DeclStmt * declstmt) {
	   for (DeclStmt::decl_iterator it = declstmt->decl_begin(), ie = declstmt->decl_end();
			   it != ie; ++ it) {
		   Decl * decl = *it;
		   if (VarDecl * vardecl = dyn_cast<VarDecl>(decl)) {
			   mStack.front().bindDecl(vardecl, 0);
		   }
	   }
   }

   void declref(DeclRefExpr * declref) {
	   mStack.front().setPC(declref);
	   if (declref->getType()->isIntegerType()) {
		   Decl* decl = declref->getFoundDecl();

		   int val = mStack.front().getDeclVal(decl);
		   mStack.front().bindStmt(declref, val);
	   }
   }

   void cast(CastExpr * castexpr) {
	   mStack.front().setPC(castexpr);
	   if (castexpr->getType()->isIntegerType()) {
		   Expr * expr = castexpr->getSubExpr();
		   int val = mStack.front().getStmtVal(expr);
		   //cout<<"------CastExpr expr val: "<<val<<" getSubExpr expr:"<<expr->getStmtClassName()<<endl;
		   mStack.front().bindStmt(castexpr, val );
	   }
   }

   /// Support Function Call
   void call(CallExpr * callexpr) {
	   mStack.front().setPC(callexpr);
	   int val = 0;
	   FunctionDecl * callee = callexpr->getDirectCallee();
	   if (callee == mInput) {
		  llvm::errs() << "Please Input an Integer Value : ";
		  scanf("%d", &val);

		  mStack.front().bindStmt(callexpr, val);
	   } else if (callee == mOutput) {
		   Expr * decl = callexpr->getArg(0);
		   val = mStack.front().getStmtVal(decl);
		   llvm::errs() << val;
	   } else {
		   /// You could add your code here for Function call Return
		   
	   }
   }
};


