/// ch5ex1.cpp
/// This file contains the source code for the custom LLVM IR generator 
/// presented in Chapter 5. It shows you how to programatically generate
/// LLVM IR/modules.

#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h> 
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/ToolOutputFile.h>

using namespace llvm;

Module *makeLLVMModule() {
  Module *mod = new Module("sum.ll", getGlobalContext());
  SmallVector<Type*, 2> FuncTyArgs;
  FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
  FuncTyArgs.push_back(IntegerType::get(mod->getContext(), 32));
  FunctionType *FuncTy = FunctionType::get(IntegerType::get
                                           (mod->getContext(), 32),
                                            FuncTyArgs, false);
  Function *funcSum = 
    Function::Create(FuncTy, GlobalValue::ExternalLinkage, "sum", mod);
  funcSum->setCallingConv(CallingConv::C);
  Function::arg_iterator args = funcSum->arg_begin();
  Value *int32_a = args++;
  int32_a->setName("a");
  Value *int32_b = args++;
  int32_b->setName("b");

  BasicBlock *labelEntry = 
    BasicBlock::Create(mod->getContext(), "entry", funcSum, 0);
  AllocaInst *ptrA = 
    new AllocaInst(IntegerType::get(mod->getContext(), 32), "a.addr", 
                   labelEntry);
  ptrA->setAlignment(4);
  AllocaInst *ptrB = 
    new AllocaInst(IntegerType::get(mod->getContext(), 32), "b.addr", 
                   labelEntry);
  ptrB->setAlignment(4);
      
  StoreInst *st0 = new StoreInst(int32_a, ptrA, false, labelEntry);
  st0->setAlignment(4);
  StoreInst *st1 = new StoreInst(int32_b, ptrB, false, labelEntry);
  st1->setAlignment(4);

  LoadInst *ld0 = new LoadInst(ptrA, "", false, labelEntry);
  ld0->setAlignment(4);
  LoadInst *ld1 = new LoadInst(ptrB, "", false, labelEntry);
  ld1->setAlignment(4);

  BinaryOperator *addRes = BinaryOperator::Create(Instruction::Add, ld0, ld1,
                                                  "add", labelEntry);
  ReturnInst::Create(mod->getContext(), addRes, labelEntry);

  return mod;
}

int main(int argc, char **argv) {
  Module *Mod = makeLLVMModule();
  std::string ErrorInfo;
  std::unique_ptr<tool_output_file> Out(new tool_output_file(
      "./sum.bc", ErrorInfo, sys::fs::F_None));
  if (!ErrorInfo.empty()) {
    errs() << ErrorInfo << "\n";
    return -1;
  }
  WriteBitcodeToFile(Mod, Out->os());
  Out->keep();
  return 0;
}
