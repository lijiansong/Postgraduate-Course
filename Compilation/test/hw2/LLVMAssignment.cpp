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

#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Use.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/Metadata.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Argument.h"

#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/BasicBlock.h"


#include <vector>

using namespace std;
using namespace llvm;


///!TODO TO BE COMPLETED BY YOU FOR ASSIGNMENT 2
struct FuncPtrPass : public FunctionPass 
{
  static char ID; // Pass identification, replacement for typeid
  FuncPtrPass() : FunctionPass(ID) {}

  //recursively process function ptr
  // void funcptr(Value *func_pointer)
  // {
  //   if(isa<LoadInst>(func_pointer))
  //   {
  //     Instruction *load_inst=dyn_cast<Instruction>(func_pointer);
  //     LoadInst *_load_inst=dyn_cast<LoadInst>(load_inst);
  //     Value *operand=_load_inst->getPointerOperand();

  //     for (User *U : operand->users())
  //     {
  //       if (Instruction *user_inst = dyn_cast<Instruction>(U))
  //       {
        
  //         if(isa<StoreInst>(user_inst))
  //         {
  //           StoreInst *user_store=dyn_cast<StoreInst>(user_inst);
  //           const Value *store_operand=user_store->getValueOperand();
  //           if(store_operand!=NULL)
  //           {
  //             errs()<<store_operand->getName()<<"\n";
  //             return ;
  //           }
  //           else
  //           {
  //             if(isa<LoadInst>(store_operand))
  //             {
  //               Instruction *operand_inst=dyn_cast<Instruction>(store_operand);
  //               LoadInst *_operand_inst=dyn_cast<LoadInst>(operand_inst);
  //               funcptr(_operand_inst->getPointerOperand());
  //             }
      
  //           }

  //         }
  //       }
  //     }//end of user

  //   }
  // }
  bool runOnFunction(Function &F) override 
  {
    for(Function::iterator bb_it=F.begin(),bb_ie=F.end();bb_it!=bb_ie;++bb_it)
    {
      //Iterator over BasicBlock for Instructions in BB
      //errs()<<"Function :"<<bb_it->getName()<<"\n";
      for(BasicBlock::iterator ii=bb_it->begin(), ie=bb_it->end();ii!=ie;++ii)
      {
        //Get Instruction and see if it is a calling instruction
        Instruction *inst=dyn_cast<Instruction>(ii);
        if(CallInst *call_inst=dyn_cast<CallInst>(inst))
        {
          Function *func=call_inst->getCalledFunction();
          if(func!=NULL)
          {
            //filtering useless dgb info
            if(func->getName()=="llvm.dbg.value") 
              continue;
            else
              errs()<<call_inst->getDebugLoc().getLine()<<" : "<<func->getName()<<"\n";
          }
          //function pointer
          else
          {
            Value *func_pointer=call_inst->getCalledValue();

            // for(User *user : func_pointer->users())
            // {
            //   if (Instruction *user_inst = dyn_cast<Instruction>(user))
            //   {
            //     errs()<<user_inst->getName()<<"\n";
            //     errs()<<*user_inst<<"\n";
            //   }
            // }

            if(isa<Argument>(func_pointer))
            {
              errs()<<call_inst->getDebugLoc().getLine()<<" : ";
              Argument *argument=dyn_cast<Argument>(func_pointer);
              errs()<<"argument"<<"\n";
              Function *parent_func=argument->getParent();
              errs()<<parent_func->getName()<<"\n";
              int count=0;
              //auto arg_list=parent_func->getArgumentList();
              for(Function::arg_iterator arg_it=parent_func->arg_begin(),arg_ie=parent_func->arg_end();arg_it!=arg_ie;++arg_it,++count)
              {
                //errs()<<arg_it->getName()<<"\n";
                if(arg_it->getName() == func_pointer->getName())
                {
                  errs()<<count<<" "<<arg_it->getName()<<"\n";
                  for(User *parent_user : parent_func->users())
                  {
                    if(Instruction *parent_inst=dyn_cast<Instruction>(parent_user))
                    {
                      errs()<<*parent_inst<<"\n";
                      Value *funcptr_operand=parent_inst->getOperand(count);
                      errs()<<funcptr_operand->getName()<<"\n";
                    }
                  }
                  //Instruction *parent=dyn_cast<Instruction>(parent_func);
                  //errs()<<*parent<<"\n";
                }//end of if

              }//end of for arg_iterator
            }
            else
            {
              Instruction *funcptr_inst=dyn_cast<Instruction>(func_pointer);
              int count=0;
              vector<StringRef> func_name;
              for (User::op_iterator i = funcptr_inst->op_begin(), e = funcptr_inst->op_end(); i != e; ++i,++count)
              {
                //int index=isa<StoreInst>(funcptr_inst)?0:1;

                Value *operand=funcptr_inst->getOperand(count);
                func_name.push_back(operand->getName());
                //errs()<<call_inst->getDebugLoc().getLine()<<" : "<<operand->getName()<<"\n";
                //errs()<<*funcptr_inst<<"\n";
                count=0;
              }
              errs()<<call_inst->getDebugLoc().getLine()<<" : ";
              for(unsigned i=0;i<func_name.size();++i)
                errs()<<func_name[i]<<" ";
              errs()<<"\n";
              func_name.clear();
            }//end of else
            

            // for(Value::use_iterator i=funcptr_inst->use_begin(),e=funcptr_inst->use_end();i!=e;++i)
            // {
            //   int index=isa<StoreInst>(funcptr_inst)?0:1;
            //   Value *operand=inst->getOperand(index);
            //   errs()<<call_inst->getDebugLoc().getLine()<<" : "<<operand->getName()<<"\n";
            // }
            
            // for (Use &def_inst : inst->operands())
            // {
            //   Value *v=def_inst.get();
            //   if(inst->getName()==func_pointer)
            //     errs()<<*def_inst<<"\n";
            // }


            // if(isa<LoadInst>(func_pointer))
            // {
            //   //LoadInst *load_inst=dyn_cast<LoadInst>(func_pointer);
            //   //const Value *operand=load_inst->getPointerOperand();
            //   Instruction *load_inst=dyn_cast<Instruction>(func_pointer);
            //   LoadInst *_load_inst=dyn_cast<LoadInst>(load_inst);
            //   Value *operand=_load_inst->getPointerOperand();

            //   for (User *U : operand->users())
            //   {
            //     if (Instruction *user_inst = dyn_cast<Instruction>(U))
            //     {
            //       // int index=isa<StoreInst>(user_inst)?0:1;
            //       // Value *operand=user_inst->getOperand(index);
            //       // errs()<<call_inst->getDebugLoc().getLine()<<" : "<<operand->getName()<<"\n";
            //       if(isa<StoreInst>(user_inst))
            //       {
            //         StoreInst *user_store=dyn_cast<StoreInst>(user_inst);
            //         const Value *store_operand=user_store->getValueOperand();
            //         if(store_operand!=NULL)
            //           errs()<<call_inst->getDebugLoc().getLine()<<" : "<<store_operand->getName()<<"\n";
            //         else
            //         {
            //           errs()<<"bb1";
            //         }
            //       }
              
            //     }
            //   }//end of user

            // }
          }//end of function pointer

        }
      }
    }
    // for (User *U : F.users())
    // {
    //   if (Instruction *inst = dyn_cast<Instruction>(U)) 
    //   {
    //     errs() << "F is used in instruction:\n";
    //     errs() << *inst << "\n";
    //     int index=isa<StoreInst>(inst)?0:1;

    //     Value *operand=inst->getOperand(index);
    //     errs()<<"operand: "<<operand->getName()<<"\n";
    //     for (User::op_iterator i = inst->op_begin(), e = inst->op_end(); i != e; ++i)
    //     {
    //       int index=isa<StoreInst>(inst)?1:0;
    //       Value *operand=inst->getOperand(index);
    //       errs()<<"def "<<operand->getName()<<"\n";

    //     }
    //     //if(isa<StoreInst>(inst))
    //     //{
    //       // for(Value::use_iterator i=inst->use_begin(),e=inst->use_end();i!=e;++i)
    //       // {
    //       //   int index=isa<StoreInst>(inst)?1:0;
    //       //   Value *operand=inst->getOperand(index);
    //       //   errs()<<"operand: "<<operand->getName()<<"\n";
    //       // }
    //     //}
    //   }
    // }
    //Instruction *pi
    //errs() << "Hello: ";
    //errs().write_escaped(F.getName()) << '\n';
    
    // for(Function::iterator bb_it=F.begin(),bb_ie=F.end();bb_it!=bb_ie;++bb_it)
    // {
    //   errs()<<"Function: "<<F.getName()<<"\n";
    //   for(BasicBlock::iterator ii=bb_it->begin(),ie=bb_it->end();ii!=ie;++ii)
    //   {
    //     //errs()<<"BasicBlock: "<<bb_it->getName()<<"\n";
    //     Instruction *inst=dyn_cast<Instruction>(ii);
    //     //errs()<<"Instruction: "<<inst->getName()<<"\n";

    //     if(CallInst *call=dyn_cast<CallInst>(inst))
    //     {
    //       errs()<<"Call: "<<call->getName()<<"\n";
    //     }
    //     for(Value::use_iterator i=inst->use_begin(),e=inst->use_end();i!=e;++i)
    //     {
    //       int index=isa<StoreInst>(inst)?1:0;
    //       Value *operand=inst->getOperand(index);
    //       if(Instruction *Inst=dyn_cast<Instruction>(*i))
    //       {
    //         //errs()<<"used Instructions: "<<operand->getName()<<"\n";
    //         //unsigned line=inst->getDebugLoc().getLine();
    //         //errs()<<"Line no : "<<line<<"\n";
    //       }
    //     }
    //     //for(Instruction::iterator inst_it=ii->begin(),inst_ie=ii->end();inst_it!=inst_ie;++inst_it)
    //     // for(auto &inst_it : bb_it)
    //     // {
    //     //   errs()<<"Instruction: "<<inst_it->getName()<<"\n";
    //     // }
    //   }
    // }
    return false;
  }
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
