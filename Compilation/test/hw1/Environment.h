//==--- tools/clang-check/ClangInterpreter.cpp - Clang Interpreter tool --------------===//
//===----------------------------------------------------------------------===//
#include <stdio.h>

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/Decl.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include <iostream>
#include <string>

using namespace clang;
using namespace std;
#define INF 0x7fffffffffffffff

/// Heap maps address to a value
class Heap {
   /// The allocated bufs, key is the address, val is its size
   std::map<long, long> mBufs;
   /// The map that maps address to value
   std::map<long, long> mContents;
public:
	Heap() : mBufs(), mContents(){
   }

   long Malloc(int size) {
      //assert (mBufs.find(addr) == mHeap.end());
      /// Allocate the buf
      int * buf = (int *)malloc(size * sizeof(int) );
      mBufs.insert(std::make_pair((long)buf, size));

      /// Initialize the Content
      for (int i=0; i<size; i ++) {
         mContents.insert(std::make_pair((long)(buf+i), 0));
      }
      return (long)buf;
   } 
   void Free (long addr) {
      /// Clear the contents;
      //assert (mHeap.find(addr) != mHeap.end());
   	  assert (mBufs.find(addr) != mBufs.end());
      int * buf = (int *)addr;
      long size = mBufs.find(addr)->second;
      mBufs.erase(mBufs.find(addr));

      for (int i = 0; i < size; i++) {
      	assert (mContents.find((long)(buf+i)) == mContents.end());
          mContents.erase((long)(buf+i));
      }
        /// Free the allocated buf
      //free(mHeap.find(addr)->second);
      free(buf);
   }

   void Update(long addr, long val) {
      assert (mContents.find(addr) != mContents.end());
      mContents[addr] = val;
   }
   int get(int addr) {
      assert (mContents.find(addr) != mContents.end());
      return mContents.find(addr)->second;
    }
};

class StackFrame {
   /// StackFrame maps Variable Declaration to Value
   /// Which are either integer or addresses (also represented using an Integer value)
   std::map<Decl*, long> mVars;
   std::map<Stmt*, long> mExprs;
   Heap * mHeap;
   /// The current stmt
   Stmt * mPC;
public:
   StackFrame() : mVars(), mExprs(), mHeap(), mPC() {
   }

   void bindHeapStmt(Stmt * stmt,int size)
   {
   	  long addr=mHeap->Malloc(size);
   	  mExprs[stmt]=addr;
   }
   void freeHeap(long addr)
   {
   	mHeap->Free(addr);
   }
   // void setHeap()
   // {

   // }
   // long getHeapStmt(Stmt *stmt)
   // {
   // 	  assert (mExprs.find(stmt) != mExprs.end());
	  // return mExprs[stmt];
   // }
   void bindDecl(Decl* decl, int val) {
      mVars[decl] = val;
   }
   long getDeclVal(Decl * decl) {
      assert (mVars.find(decl) != mVars.end());
      return mVars.find(decl)->second;
   }
   void bindStmt(Stmt * stmt, int val) {
	   mExprs[stmt] = val;
   }
   long getStmtVal(Stmt * stmt) {
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
	   auto * left = bop->getLHS();
	   auto * right = bop->getRHS();

	//assignment operation
	   if (bop->isAssignmentOp()) {
		   int val = mStack.back().getStmtVal(right);
		   mStack.back().bindStmt(left, val);
		   //cout<<"-----assignment left val: "<<left->getStmtClassName()<<endl;
		   if (DeclRefExpr * declexpr = dyn_cast<DeclRefExpr>(left)) {
			   Decl * decl = declexpr->getFoundDecl();
			   mStack.back().bindDecl(decl, val);
		   }
	   }
	   int valLeft=mStack.back().getStmtVal(left);
	   int valRight=mStack.back().getStmtVal(right);

	   if(bop->isComparisonOp())
	   {
	   	switch(bop->getOpcode())
	   	{
	   		case BO_LT:
	   		if( valLeft < valRight )
	   			mStack.back().bindStmt(bop,true);
	   		else
	   			mStack.back().bindStmt(bop,false);
	   		break;

	   		case BO_GT:
	   		if( valLeft > valRight )
	   			mStack.back().bindStmt(bop,true);
	   		else
	   			mStack.back().bindStmt(bop,false);
	   		break;

	   		case BO_GE:
	   		if( valLeft >= valRight )
	   			mStack.back().bindStmt(bop,true);
	   		else
	   			mStack.back().bindStmt(bop,false);
	   		break;

	   		case BO_LE:
	   		if( valLeft <= valRight )
	   			mStack.back().bindStmt(bop,true);
	   		else
	   			mStack.back().bindStmt(bop,false);
	   		break;

	   		case BO_EQ:
	   		if( valLeft == valRight )
	   			mStack.back().bindStmt(bop,true);
	   		else
	   			mStack.back().bindStmt(bop,false);
	   		break;

	   		case BO_NE:
	   		if( valLeft != valRight )
	   			mStack.back().bindStmt(bop,true);
	   		else
	   			mStack.back().bindStmt(bop,false);
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
	   		mStack.back().bindStmt(bop,valLeft+valRight);
	   		break;

	   		case BO_Sub:
	   		mStack.back().bindStmt(bop,valLeft-valRight);
	   		break;
	   	}
	   }

	   if(bop->isMultiplicativeOp())
	   {
	   	switch(bop->getOpcode())
	   	{
	   		case BO_Mul:
	   		mStack.back().bindStmt(bop,valLeft * valRight);
	   		break;
	   	}
	   }
   }

   //UnaryOperator
   void unaryop(UnaryOperator* uop)
   {
   	Expr *expr=uop->getSubExpr();
   	int val=mStack.back().getStmtVal(expr);
	switch(uop->getOpcode())
	{
		case UO_Plus:
		mStack.back().bindStmt(uop,val);
		break;

		
		case UO_Minus:
		mStack.back().bindStmt(uop,-val);
		break;

		case UO_Deref:
		int *val=(int *)mStack.back().getStmtVal(expr);
		mStack.back().bindStmt(uop,*val);
		break;

		// case UO_PostInc:   break;
  //       case UO_PostDec:   break;
  //       case UO_PreInc:    break;
  //       case UO_PreDec:    break;
  //       case UO_AddrOf:    break;
  //       case UO_Plus:      break;
  //       case UO_Minus:     break;
  //       case UO_Not:       break;
  //       case UO_LNot:      break;
  //       case UO_Real:      break;
  //       case UO_Imag:      break;
  //       case UO_Extension: break;
  //       case UO_Coawait:   break;
	}
   }

   void integerliteral(IntegerLiteral* integer)
   {
   	//int val=integer->getValue().bitsToDouble();
   	int val=integer->getValue().getSExtValue();
   	mStack.back().bindStmt(integer,val);
   }

   bool getcond(/*BinaryOperator *bop*/Expr *expr)
   {
   	return mStack.back().getStmtVal(expr);
   }

   void decl(DeclStmt * declstmt) 
   {
	   for (DeclStmt::decl_iterator it = declstmt->decl_begin(), ie = declstmt->decl_end();
			   it != ie; ++ it) 
	   {
		Decl * decl = *it;
		if (VarDecl * vardecl = dyn_cast<VarDecl>(decl)) 
		{
			string type=(vardecl->getType()).getAsString();
			if( !( vardecl->hasInit() ) && (type.compare("int *")) && (type.compare("int **")))
			{
				mStack.back().bindDecl(vardecl, 0);
			}
			//pointer type
			else if(!( vardecl->hasInit() ) && ( !(type.compare("int *")) || !(type.compare("int **")) ))
			{
				mStack.back().bindDecl(vardecl, INF);
			}
			else if( vardecl->hasInit() )
			{
				int val=mStack.back().getStmtVal(vardecl->getInit());
		   		mStack.back().bindDecl(vardecl, val);
			}
	   	}
	   }
		
   }

   void declref(DeclRefExpr * declref) 
   {
	   mStack.back().setPC(declref);
	   if (declref->getType()->isIntegerType()) 
	   {
		   Decl* decl = declref->getFoundDecl();

		   int val = mStack.back().getDeclVal(decl);
		   mStack.back().bindStmt(declref, val);
	   }
   }

   void cast(CastExpr * castexpr) 
   {
	   mStack.back().setPC(castexpr);
	   if (castexpr->getType()->isIntegerType()) 
	   {
		   Expr * expr = castexpr->getSubExpr();
		   int val = mStack.back().getStmtVal(expr);
		   //cout<<"------CastExpr expr val: "<<val<<" getSubExpr expr:"<<expr->getStmtClassName()<<endl;
		   mStack.back().bindStmt(castexpr, val );
	   }
   }
   void unarysizeof(UnaryExprOrTypeTraitExpr *uop)
   {
   	auto *expr=uop->getArgumentExpr();
   	int val =sizeof(expr);
   	mStack.back().bindStmt(uop,val);
   }

   void ret(ReturnStmt *retstmt)
   {
   	Expr *expr=retstmt->getRetValue();
   	//cout<<expr->getStmtClassName()<<endl;
   	int val=0;
   	val=mStack.back().getStmtVal(expr);
   	mStack.back().bindStmt(retstmt,val);
   	mStack.pop_back();
   	Stmt *stmt=mStack.back().getPC();
   	//cout<<stmt->getStmtClassName()<<endl;
   	//CallExpr * callexpr = dyn_cast<CallExpr>(stmt);
   	mStack.back().bindStmt(stmt,val);
   }
   // long getsizeof(UnaryExprOrTypeTraitExpr *uop)
   // {
   // 	auto *expr=uop->getArgumentExpr();
   // 	int val =sizeof(expr);
   // 	mStack.back().bindStmt(uop,val);
   // }

   /// Support Function Call
   void call(CallExpr * callexpr) 
   {
	   mStack.back().setPC(callexpr);
	   int val = 0;
	   FunctionDecl * callee = callexpr->getDirectCallee();
	   if (callee == mInput) 
	   {
		  llvm::errs() << "Please Input an Integer Value : ";
		  scanf("%d", &val);

		  mStack.back().bindStmt(callexpr, val);
	   } 
	   else if (callee == mOutput) 
	   {
		   Expr * decl = callexpr->getArg(0);
		   val = mStack.back().getStmtVal(decl);
		   llvm::errs() << val;
	   } 
	   else if ( callee == mMalloc )
	   {
	   	//To Do:how to get the last node from callexpr,that is a question
	   	//child_iterator
	   	auto param=callexpr->child_end();
	   	//Expr * param = callexpr->getArg(0);
	   	if(isa<UnaryExprOrTypeTraitExpr>(*param))
	   	{
   			int size =(int)(mStack.back().getStmtVal(*param));
   			mStack.back().bindHeapStmt(callexpr,size);
	   	}

	   }
	   else if (callee == mFree )
	   {
	   	auto param=callexpr->child_end();
	   	long addr=mStack.back().getStmtVal(*param);
	   	mStack.back().freeHeap(addr);
	   }
	   else 
	   {
		   /// You could add your code here for Function call Return
		   //llvm::errs() << callee->getName();
	   	//Expr **args=callexpr.getArgs();
	   	//bind the args
	   	// vector<Expr*> args;
	   	// for(CallExpr::arg_iterator it=callexpr->arg_begin(), ie=callexpr->arg_end();it!=ie;++it)
	   	// {
	   	// 	args.push_back(*it);
	   	// }
	   	// int argc=callee->getNumParams();
	   	// for(int i=0;i<argc;++i)
	   	// {
	   	// 	int val=mStack.front().getStmtVal(args[i]);
	   	// 	mStack.front().bindDecl(callee->parameters()[i], val);
	   	// }
	   	// mStack.front().setPC(callee->getBody());

	   	//mStack.front().bindDecl(callee,getret())
	   	//mStack.front().bindStmt(callexpr,10+val);
	   	StackFrame stack;
	   	auto pit=callee->param_begin();
	   	for(auto it=callexpr->arg_begin(), ie=callexpr->arg_end();it!=ie;++it,++pit)
	   	{
	   		int val=mStack.back().getStmtVal(*it);
	   		stack.bindDecl(*pit,val);
	   	}
	   	mStack.push_back(stack);
	   }
   }

};
