//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Transforms/Scalar.h>

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstrTypes.h"
#include <vector>

using namespace std;
using namespace llvm;


///!TODO TO BE COMPLETED BY YOU FOR ASSIGNMENT 2
// struct FuncPtrPass : public FunctionPass {
//   static char ID; // Pass identification, replacement for typeid
//   FuncPtrPass() : FunctionPass(ID) {}


//   bool runOnFunction(Function &F) override {
//     errs() << "Hello: ";
//     errs().write_escaped(F.getName()) << '\n';
//     return false;
//   }
// };

//get the function info
class func_data
{
public:
  StringRef func_name;
  unsigned int param_nums;
  vector<llvm::Type::TypeID> params;
};

struct FuncPtrPass : public CallGraphSCCPass 
{
  static char ID; // Pass identification, replacement for typeid
  //FuncPtrPass() : FunctionPass(ID) {}
  FuncPtrPass() : CallGraphSCCPass(ID) {}

  StringRef getTypeInString(Type *type)
  {
    StringRef requiredParamType="";
    switch(type->getTypeID())
    {
      case 0 :
              requiredParamType = "void";
              break;
            
      case 1:
      case 2:
        requiredParamType = "float";
        break;

      case 3:
      case 4:
      case 5:
      case 6:
        requiredParamType = "double";
        break;

      case 7:
         requiredParamType = "label";
         break;

      case 10:
          if(type->getIntegerBitWidth()==8){
              requiredParamType = "char";
          }else{
              requiredParamType = "int";
          }
          break;

      case 11:
          requiredParamType = "function";
          break;

      case 12:
          requiredParamType = "struct";
          break;

      case 13:
          requiredParamType = "array";
          break;

      case 14:
          requiredParamType = "pointer";
          break;   

      default :
          requiredParamType = "default";
          break;
    }
    return requiredParamType;
  }

  bool runOnSCC(CallGraphSCC &scc) override
  {
    vector<func_data> functions;
    auto it=scc.begin();
    auto ie=scc.end();
    for(;it!=ie;++it)
    {
      CallGraphNode *cgNode = *it;
      Function *f=cgNode->getFunction();
      if(f)
      {
        if(f->isDeclaration())
        {
          if(f->getName()=="llvm.dbg.declare")
          {
            continue;
          }

          FunctionType *func_type=f->getFunctionType();
          func_data fd;
          fd.func_name=f->getName();
          fd.param_nums=func_type->getNumParams();

          auto param_it=func_type->param_begin();
          auto param_ie=func_type->param_end();
          for(;param_it!=param_ie;++param_it)
          {
            const Type* OriginalType = *param_it;
            fd.params.push_back(OriginalType->getTypeID());
          }
          functions.push_back(fd);
          continue;
        }

        for(Function::iterator bb_it=f->begin(),bb_ie=f->end();bb_it!=bb_ie;++bb_it)
        {
          //Iterator over BasicBlock for Instructions in BB
          for(BasicBlock::iterator ii=bb_it->begin(), ie=bb_it->end();ii!=ie;++ii)
          {
            //Get Instruction and see if it's a calling instruction
            Instruction *inst = dyn_cast<Instruction>(ii);
            CallSite CS(cast<Value>(inst));
            if(CS)
            {
              errs()<<inst->getDebugLoc().getLine()<<" : ";
              CallInst &callInst = static_cast<CallInst&>(*inst);

              const Function* fnxCalled = dyn_cast<const Function>(callInst.getCalledValue()->stripPointerCasts());
              if(fnxCalled->getName() == "llvm.dbg.declare")
              {
                continue;
              }

              unsigned int numOfArgs =  callInst.getNumArgOperands();
              unsigned int numOfParams = fnxCalled->getFunctionType()->getNumParams();
              if(numOfArgs != numOfParams) 
              {
                //Argument Mistach 
                //Function ‘Z’ call on line ‘T’: expected ‘3’ arguments but ‘2’ are/is present.
                 // errs() << "Function "<<fnxCalled->getName() << " call on line " << inst->getDebugLoc().getLine() << " 
                 errs() << "Function " << fnxCalled->getName() << " call on line " << inst->getDebugLoc().getLine() << " " ;
                 errs() << " : expected " << numOfParams << " arguments " << " but " << numOfArgs << " is present \n" ; 
                 continue;
               }
               //arg type match
               FunctionType *fxnDecType = fnxCalled->getFunctionType();
               for(unsigned int i=0;i<numOfParams;++i)
               {
                  Type* paramType = fxnDecType->getParamType(i);
                                 
                  Type* argType = callInst.getArgOperand(i)->getType();

                  StringRef requiredParamType = "";
                  StringRef foundArgType = "";
                  if(paramType->isVectorTy() || argType->isVectorTy())
                  {
                    if(paramType->isVectorTy() && argType->isVectorTy())
                    {
                      argType = argType->getScalarType();
                      paramType = paramType->getScalarType();

                    }
                    else
                    {           
                      errs() << "Function " << fnxCalled->getName() << " call on line " << inst->getDebugLoc().getLine() << " " ;
                      errs() << " argument type mismatch. Expected vector  " << getTypeInString(paramType) << " but argument is of type " << getTypeInString(argType) << "\n";
                      break;
                    }
                  }

                  if(paramType->isPointerTy() || argType->isPointerTy())
                  {
                    if(paramType->isPointerTy() && argType->isPointerTy())
                    {
                      paramType = paramType->getPointerElementType();
                      requiredParamType = "pointer";
                      argType = argType->getPointerElementType();
                      foundArgType = "pointer";
                    }
                    else
                    {
                      errs() << "Function " << fnxCalled->getName() << " call on line " << inst->getDebugLoc().getLine() << " " ;
                      errs() << " argument type mismatch. Expected " << getTypeInString(paramType) << "* but argument is of type "<< getTypeInString(argType) <<" \n";
                      break;   
                    }
                  }

                  if( (argType->getTypeID() !=  paramType->getTypeID()) || (argType->getIntegerBitWidth() !=  paramType->getIntegerBitWidth()) ) 
                  {
                   
                      requiredParamType = getTypeInString(paramType);
                      foundArgType = getTypeInString(argType);
                      errs() << "Function " << fnxCalled->getName() << " call on line " << inst->getDebugLoc().getLine() << " " ;
                      errs() << " argument type mismatch. Expected " << requiredParamType << " but argument is of type " << foundArgType << "\n";
                      break;            
                  }

               }
            }
          }
        }

      }
    }
    return false;
  }
  
  // bool runOnFunction(Function &F) override 
  // {
  //   errs() << "Hello: ";
  //   errs().write_escaped(F.getName()) << '\n';
  //   return false;
  // }
};


char FuncPtrPass::ID = 0;
static RegisterPass<FuncPtrPass> X("funcptrpass", "Print function call instruction");
//static RegisterPass<FuncPtrPass> X("funcptrpass", "Print function call instruction",false,false);


static cl::opt<std::string>
InputFilename(cl::Positional,
              cl::desc("<filename>.bc"),
              cl::init(""));


int main(int argc, char **argv) {
   //LLVMContext &Context = getGlobalContext();
  static LLVMContext Context;
   SMDiagnostic Err;
   // Parse the command line to read the Inputfilename
   cl::ParseCommandLineOptions(argc, argv,
                              "FuncPtrPass \n My first LLVM too which does not do much.\n");


   // Load the input module
   std::unique_ptr<Module> M = parseIRFile(InputFilename, Err, Context);
   if (!M) {
      Err.print(argv[0], errs());
      return 1;
   }

   llvm::legacy::PassManager Passes;

   ///Transform it to SSA
   Passes.add(llvm::createPromoteMemoryToRegisterPass());

   /// Your pass to print Function and Call Instructions
   Passes.add(new FuncPtrPass());
   Passes.run(*M.get());
}

