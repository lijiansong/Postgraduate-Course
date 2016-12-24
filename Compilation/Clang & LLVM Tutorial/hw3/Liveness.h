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
#define MINUS_INF -0x7ffffff
#define INF 0x7ffffff
//typedef pair<>
typedef pair< map<string,vector<int> >,map<string,vector<int> > > true_false_out_pair;
struct LivenessInfo 
{
   std::set<Instruction *> LiveVars;/// Set of variables which are live

   // interval of each vars,name of each vars is the key, and vector<int> is its range 
   map<string,vector<int> > VarRanges;
   map<string,vector<int> > TrueOut;
   map<string,vector<int> > FalseOut;

   LivenessInfo() : LiveVars(),VarRanges(),TrueOut(),FalseOut() {}
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
         // for (std::set<Instruction *>::const_iterator ii = src.LiveVars.begin(), 
         //      ie = src.LiveVars.end(); ii != ie; ++ii) 
         // {
         //     //errs()<<"+++++ "<<*ii<<"\n";

         //     dest->LiveVars.insert(*ii);
         //     // if(isa<ICmpInst>(ii))
         //     // {
         //     //  //get its condition val and update its range 
         //     // }
         // }
    }

    ConstantInt * tryGetConstantValue(Value * value) 
    {
        ConstantInt * CI = dyn_cast<ConstantInt>(value);
        if (CI && CI->getBitWidth() <= 32) 
        {
            return CI;
        }
        return NULL;
    }

    vector<int> tryGetRange(Value * value,LivenessInfo *dfval) 
    {
        map<string,vector<int> > varRanges = dfval->VarRanges;
        if( varRanges.count(value->getName().str()) > 0 )
        return varRanges[value->getName().str()];
        vector<int> empty;
        // //assign [-inf,inf]
        // empty.push_back(MINUS_INF);
        // empty.push_back(INF);
        return empty;
    }

    //intersect operation
    vector<int> intersect(vector<int> left, vector<int> right)
    {
        vector<int> result;
        if (left.empty())
            result = left;
        else if (right.empty())
            result = right;
        else
        {
            int varmin = max(left[0], right[0]);
            int varmax = min(left[1], right[1]);
            if (varmin <= varmax) 
            { 
                result.push_back(varmin);
                result.push_back(varmax);
            }
        }
        return result;
    }

    true_false_out_pair getTrueFalseOut(BranchInst *inst)
    {
        map<string,vector<int> > trueOut;
        map<string,vector<int> > falseOut;

        Value *condition = inst->getCondition();
        //ICmpInst *cmpInst = (ICmpInst *)condition;
        ICmpInst *cmpInst=dyn_cast<ICmpInst>(condition);

        int predicate = cmpInst->isSigned() ? cmpInst->getSignedPredicate() : cmpInst->getUnsignedPredicate();
        //get the lhs and the rhs
        Value * lhs = cmpInst->getOperand(0);
        Value * rhs = cmpInst->getOperand(1);
        ConstantInt * rhsConstant = tryGetConstantValue(rhs);
        ConstantInt * lhsConstant = tryGetConstantValue(lhs);
        vector<int> lhsRange = tryGetRange(lhs,(*result)[pred_bb].second);
        vector<int> rhsRange = tryGetRange(rhs,(*result)[pred_bb].second);

        vector<int> range; //empty

        Value * variable = NULL;
        ConstantInt * constant = NULL;

        if((lhsConstant && rhsConstant) || (lhsRange.empty() && rhsRange.empty()))//both lhs and rhs is constant
        {
            errs()<<"both lhs and rhs is constant!"<<"\n";
            return;
        }
        //rhs is a constant int, but lhs is not
        else if(rhsConstant)
        {
            variable=lhs;
            constant=rhsConstant;
        }
        //lhs is a constant int, but rhs is not
        else if(lhsConstant)
        {
            variable=rhs;
            constant=lhsConstant;
        }
        //both variables
        else
        {
            //both have ranges, we have to assign new may ranges to both variables!
            if (!lhsRange.empty() && !rhsRange.empty()) 
            {
                variable = NULL; 
            }
            // assign to rhs, since it has no range
            else if(!lhsRange.empty())
            {
                range=lhsRange;
                variable=rhs;
            }
            //assign to lhs, since it has no range
            else if(!rhsRange.empty())
            {
                range=rhsRange;
                variable=lhs;
            }
        }//end of else

        BasicBlock * trueBlock = branchInst->getSuccessor(0);
        BasicBlock * falseBlock = branchInst->getSuccessor(1);
        //process each probably case
        if(variable && constant)
        {
            vector<int> variableRange = tryGetRange(variable,(*result)[pred_bb].second);
            // X == C
            if(predicate == CmpInst::ICMP_EQ)
            {
                vector<int> constantRange;
                map<string,vector<int>> trueMap=&((*result)[pred_bb].second).VarRanges;
                if(trueMap.count(variable->getName().str())>0)
                {
                    trueMap.erase(variable->getName().str());
                    constantRange.push_back(constant->getSExtValue());
                    constantRange.push_back(constant->getSExtValue());
                    vector<int> intersection = intersect(variableRange, constantRange);
                    if (!intersection.empty()) 
                    {
                        trueMap[variable->getName().str()] = intersection;
                    }
                }
                else
                {
                }
            }
            // X != C
            else if(predicate == CmpInst::ICMP_NE)
            {
            }
            // X > C
            else if( ( (predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == lhs ) 
                      || ( (predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == rhs ) )
            {
            }
            // X < C
            else if( ( (predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == lhs ) 
                      || ( (predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == rhs ) )
            {
            }
            // X >= C
            else if( ( (predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == lhs ) 
                      || ( (predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == rhs ) )
            {
            }
            // X <= C
            else if( ( (predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == lhs ) 
                      || ( (predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == rhs ) )
            {
            }

            else if (variable && !range.empty())
            {
            }
            //both operands are ranges
            else
            {
            }
        }//end of if variable && constant
        return make_pair<trueOut,falseOut>;
    }
    //handle the icmpinst of the pred_bb's pred basic block
    void handlePredIcmp(/*const*/ BasicBlock *pred_bb,
                                  /*BasicBlock *bb,*/
                                  typename DataflowResult<LivenessInfo>::Type &result) override
    {
       //for each intruction in the basic block
       BasicBlock::iterator ii = pred_bb->begin (), ie = pred_bb->end ();
       for (; ii != ie; ++ii)
       {
         Instruction *inst = dyn_cast < Instruction > (*ii);

         if (isa < ICmpInst > (inst) )
         {
          Instruction *next_inst=dyn_cast<Instruction>(*(ii+1));
          //get its condition vars and the lhs and rhs
          //branchInst->isConditional()
          if(isa<BranchInst>(next_inst))
          {
              ICmpInst *cmpInst=dyn_cast<ICmpInst>(inst);
              BranchInst *branchInst=dyn_cast<BranchInst>(next_inst);
              int predicate = cmpInst->isSigned() ? cmpInst->getSignedPredicate() : cmpInst->getUnsignedPredicate();
              
              //get the lhs and the rhs
              Value * lhs = cmpInst->getOperand(0);
              Value * rhs = cmpInst->getOperand(1);
              ConstantInt * rhsConstant = tryGetConstantValue(rhs);
              ConstantInt * lhsConstant = tryGetConstantValue(lhs);
              vector<int> lhsRange = tryGetRange(lhs,(*result)[pred_bb].second);
              vector<int> rhsRange = tryGetRange(rhs,(*result)[pred_bb].second);

              vector<int> range; //empty

              Value * variable = NULL;
              ConstantInt * constant = NULL;

              if((lhsConstant && rhsConstant) || (lhsRange.empty() && rhsRange.empty()))//both lhs and rhs is constant
              {
                  errs()<<"both lhs and rhs is constant!"<<"\n";
                  return;
              }
              //rhs is a constant int, but lhs is not
              else if(rhsConstant)
              {
                  variable=lhs;
                  constant=rhsConstant;
              }
              //lhs is a constant int, but rhs is not
              else if(lhsConstant)
              {
                  variable=rhs;
                  constant=lhsConstant;
              }
              //both variables
              else
              {
                  //both have ranges, we have to assign new may ranges to both variables!
                  if (!lhsRange.empty() && !rhsRange.empty()) 
                  {
                      variable = NULL; 
                  }
                  // assign to rhs, since it has no range
                  else if(!lhsRange.empty())
                  {
                      range=lhsRange;
                      variable=rhs;
                  }
                  //assign to lhs, since it has no range
                  else if(!rhsRange.empty())
                  {
                      range=rhsRange;
                      variable=lhs;
                  }
              }

              BasicBlock * trueBlock = branchInst->getSuccessor(0);
              BasicBlock * falseBlock = branchInst->getSuccessor(1);
              //process each probably case
              if(variable && constant)
              {
                  vector<int> variableRange = tryGetRange(variable,(*result)[pred_bb].second);
                  // X == C
                  if(predicate == CmpInst::ICMP_EQ)
                  {
                      vector<int> constantRange;
                      map<string,vector<int>> trueMap=&((*result)[pred_bb].second).VarRanges;
                      if(trueMap.count(variable->getName().str())>0)
                      {
                          trueMap.erase(variable->getName().str());
                          constantRange.push_back(constant->getSExtValue());
                          constantRange.push_back(constant->getSExtValue());
                          vector<int> intersection = intersect(variableRange, constantRange);
                          if (!intersection.empty()) 
                          {
                              trueMap[variable->getName().str()] = intersection;
                          }
                      }
                      else
                      {

                      }
                  }
                  // X != C
                  else if(predicate == CmpInst::ICMP_NE)
                  {
                  }
                  // X > C
                  else if( ( (predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == lhs ) 
                            || ( (predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == rhs ) )
                  {
                  }
                  // X < C
                  else if( ( (predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == lhs ) 
                            || ( (predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == rhs ) )
                  {
                  }
                  // X >= C
                  else if( ( (predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == lhs ) 
                            || ( (predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == rhs ) )
                  {
                  }
                  // X <= C
                  else if( ( (predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == lhs ) 
                            || ( (predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == rhs ) )
                  {
                  }

                  else if (variable && !range.empty())
                  {
                  }
                  //both operands are ranges
                  else
                  {
                  }


              }
          }//end of if isa<BranchInst>(next_inst)
         }//end of if isa < ICmpInst > (inst)
       }//end of for
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
        // if(isa<ICmpInst>(inst))
        // {
        //   ICmpInst *icmpInst= dyn_cast<ICmpInst>(inst);

        // }
        if(isa<BranchInst>(inst))
        {
          BranchInst *branch=dyn_cast<BranchInst>(inst);
          if(branch->isConditional())
          {
            Value * condition = branch->getCondition();
            ICmpInst * cmpInst = (ICmpInst *)condition;

            //handleConditionalBranch();
          }
        }
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



