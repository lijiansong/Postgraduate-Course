//==--- tools/clang-check/ClangInterpreter.cpp - Clang Interpreter tool --------------===//
//===----------------------------------------------------------------------===//

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/EvaluatedExprVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;

#include "Environment.h"

class InterpreterVisitor : 
   public EvaluatedExprVisitor<InterpreterVisitor> {
public:
   explicit InterpreterVisitor(const ASTContext &context, Environment * env)
   : EvaluatedExprVisitor(context), mEnv(env) {}
   virtual ~InterpreterVisitor() {}

   virtual void VisitBinaryOperator (BinaryOperator * bop) {
	   VisitStmt(bop);
	   mEnv->binop(bop);
   }

   virtual void VisitDeclRefExpr(DeclRefExpr * expr) {
	   VisitStmt(expr);
	   mEnv->declref(expr);
   }

   virtual void VisitCastExpr(CastExpr * expr) {
	   VisitStmt(expr);
	   mEnv->cast(expr);
   }

   virtual void VisitCallExpr(CallExpr * call) {
	   VisitStmt(call);
	   mEnv->call(call);
         FunctionDecl * callee = call->getDirectCallee();
         Stmt *body=callee->getBody();
         if(body && isa<CompoundStmt>(body) )
         {
              VisitStmt(body);
         }
   }

  virtual void VisitDeclStmt(DeclStmt * declstmt) {
          VisitStmt(declstmt);
	   mEnv->decl(declstmt);
   }
   
   //Add other modules
   virtual void VisitIfStmt(IfStmt *ifstmt) {
          Expr *expr=ifstmt->getCond();
          Visit(expr);
          //cout<<expr->getStmtClassName()<<endl;
          //BinaryOperator * bop = dyn_cast<BinaryOperator>(expr);
          bool cond=mEnv->getcond(expr);
          if(cond)
          {
            VisitStmt(ifstmt->getThen());
          }
          else
          {
            Stmt *else_block=ifstmt->getElse();
            if(else_block)
              VisitStmt(else_block);
          }
   }

   virtual void VisitWhileStmt(WhileStmt *whilestmt) {
          Expr *expr = whilestmt->getCond();
          Visit(expr);
          //BinaryOperator *bop = dyn_cast<BinaryOperator>(expr);
          bool cond=mEnv->getcond(expr);
          Stmt *body=whilestmt->getBody();
          while(cond)
          {
            if( body && isa<CompoundStmt>(body) )
            {
              VisitStmt(whilestmt->getBody());
            }
            Visit(expr);
            cond=mEnv->getcond(expr);
          }
   }
   virtual void VisitUnaryOperator(UnaryOperator *uop)
   {
            VisitStmt(uop);
            mEnv->unaryop(uop);
   }
   virtual void VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *uop)
   {
            VisitStmt(uop);
            mEnv->unarysizeof(uop);
   }
   virtual void VisitReturnStmt(ReturnStmt *retstmt) {
           VisitStmt(retstmt);
           //Visit(retstmt);
           mEnv->ret(retstmt);
   }

   // virtual void VisitParmVarDecl(ParmVarDecl *parm)
   // {
   //         VisitDecl(parm);
   //         mEnv->parmdecl(parm);
   // }

   // virtual void VisitFunctionDecl(FunctionDecl *func) {
   //         // VisitDecl(func);
   //         // mEnv->funcdecl(func);
   // }

   virtual void VisitIntegerLiteral(IntegerLiteral *integer)
   {
      //VisitStmt(integer);
      mEnv->integerliteral(integer);
   }
   
private:
   Environment * mEnv;
};

class InterpreterConsumer : public ASTConsumer {
public:
   explicit InterpreterConsumer(const ASTContext& context) : mEnv(),
   	   mVisitor(context, &mEnv) {
   }
   virtual ~InterpreterConsumer() {}

   virtual void HandleTranslationUnit(clang::ASTContext &Context) {
	   TranslationUnitDecl * decl = Context.getTranslationUnitDecl();
	   mEnv.init(decl);

	   FunctionDecl * entry = mEnv.getEntry();
	   mVisitor.VisitStmt(entry->getBody());
  }
private:
   Environment mEnv;
   InterpreterVisitor mVisitor;
};

class InterpreterClassAction : public ASTFrontendAction {
public: 
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    return std::unique_ptr<clang::ASTConsumer>(
        new InterpreterConsumer(Compiler.getASTContext()));
  }
};
//static cl::opt<std::string> FileName(cl::Positional ,cl::desc("Input file"),cl::Required);

int main (int argc, char ** argv) {
   if (argc > 1) {
       clang::tooling::runToolOnCode(new InterpreterClassAction, argv[1]);
   }
   
   /*cl::ParseCommandLineOptions(argc, argv, "cmd line \n");
   
   new InterpreterClassAction;
   return 0;*/
}
