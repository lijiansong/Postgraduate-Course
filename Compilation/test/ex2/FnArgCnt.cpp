/// FnArgCnt.cpp
/// This file contains the source code for the custom LLVM IR pass presented in
/// Chapter 5. 

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  class FnArgCnt : public FunctionPass {
  public:
    static char ID;
    FnArgCnt() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      errs() << "FnArgCnt --- ";
      errs() << F.getName() << ": ";
      errs() << F.getArgumentList().size() << '\n';
      return false;
    }
  };
}

char FnArgCnt::ID = 0;
static RegisterPass<FnArgCnt> X("fnargcnt", "Function Argument Count Pass", false, false);
