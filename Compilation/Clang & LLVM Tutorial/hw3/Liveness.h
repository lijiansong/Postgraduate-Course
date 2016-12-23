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

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IntrinsicInst.h"

#include "Dataflow.h"
#include <string>
#include <vector>
using namespace llvm;
using namespace std;

struct LivenessInfo 
{
   std::set<Instruction *> LiveVars;/// Set of variables which are live
   
   // interval of each vars,name of each vars is the key, and vector<int> is its range 
   map<string,pair<int,int> > VarRanges;

   LivenessInfo() : LiveVars() {}
   LivenessInfo(const LivenessInfo & info) : LiveVars(info.LiveVars) {}
  
   bool operator == (const LivenessInfo & info) const 
   {
       return LiveVars == info.LiveVars;
   }
};

inline raw_ostream &operator<<(raw_ostream &out, const LivenessInfo &info) 
{
    for (std::set<Instruction *>::iterator ii=info.LiveVars.begin(), ie=info.LiveVars.end();
         ii != ie; ++ ii) 
    {
       const Instruction * inst = *ii;
       out << inst->getName();
       out << " ";
    }
    return out;
}

class LivenessVisitor : public DataflowVisitor<struct LivenessInfo> 
{
public:
   LivenessVisitor() {}

   void merge(LivenessInfo * dest, const LivenessInfo & src) override 
   {
       for (std::set<Instruction *>::const_iterator ii = src.LiveVars.begin(), 
            ie = src.LiveVars.end(); ii != ie; ++ii) 
       {
           //errs()<<"+++++ "<<*ii<<"\n";

           dest->LiveVars.insert(*ii);
           // if(isa<ICmpInst>(ii))
           // {
           //  //get its condition val and update its range 
           // }
       }
   }
    //handle the icmpinst of the bb's pred basic block
    void handlePredIcmp(/*const*/ BasicBlock &bb) override
    {
       //for each intruction in the basic block
       BasicBlock::iterator ii = bb->begin (), ie = bb->end ();
       for (; ii != ie; ++ii)
       {
         Instruction *inst = dyn_cast < Instruction > (ii);
         if (isa < ICmpInst > (inst))
         {
          //get its condition vars and the lhs and rhs
         }
         if(isa<BranchInst>)
       }
    }

    //handle binary op,e.g.: + - * /
    void handleBinaryOp(Instruction *inst,LivenessInfo *dfval) override
    {
      switch (inst->getOpcode()) 
      {
        case Instruction::Add:
            break;

        case Instruction::Mul:
            break;

        case Instruction::Sub:
            break;

        case Instruction::SDiv:
            break;
        case Instruction::UDiv:
            break;

        case Instruction::SRem:
        case Instruction::URem:
            break;

        case Instruction::Or:
            break;

        case Instruction::And:
            break;

        case Instruction::Xor:
            break;
      }
    }

   //compute the interval of each inst
   void compDFVal(Instruction *inst, LivenessInfo * dfval) override
   {
        if (isa<DbgInfoIntrinsic>(inst)) return;
        dfval->LiveVars.erase(inst);
        for(User::op_iterator oi = inst->op_begin(), oe = inst->op_end();
            oi != oe; ++oi) 
        {
           Value * val = *oi;
           if (isa<Instruction>(val)) 
           {
            dfval->LiveVars.insert(cast<Instruction>(val));
            errs()<<*val<<"\n";

           }
           // else if(isa<>(val))
           // {}
        }
   }
};


class Liveness : public FunctionPass 
{
public:

   static char ID;
   Liveness() : FunctionPass(ID) {} 

   bool runOnFunction(Function &F) override 
   {
       //F.dump();
    //for each basic block in the function
    // Function::iterator bb_it = F.begin (), bb_ie = F.end ();
    // for (; bb_it != bb_ie; ++bb_it)
    // {
    //  //for each intruction in the basic block
    //  BasicBlock::iterator ii = bb_it->begin (), ie = bb_it->end ();
    //  for (; ii != ie; ++ii)
    //  {
    //    Instruction *inst = dyn_cast < Instruction > (ii);
    //    if (isa < ReturnInst > (inst))
    //    {
    //      ReturnInst * ret = dyn_cast < ReturnInst > (ii);
    //      errs()<<"+++++++++++"<<ret->getName()<<"\n";

    //    }
    //  }//end of ii
    // }//end of bb_it
       LivenessVisitor visitor;
       DataflowResult<LivenessInfo>::Type result;
       LivenessInfo initval;

       //compBackwardDataflow(&F, &visitor, &result, initval);
       compForwardDataflow(&F, &visitor, &result, initval);
       //printDataflowResult<LivenessInfo>(errs(), result);
       return false;
   }
};



