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

typedef pair< map<string,vector<int> >,map<string,vector<int> > > true_false_out_pair;

struct LivenessInfo 
{
   std::set<Instruction *> LiveVars;/// Set of variables which are live

   // interval of each vars,name of each vars is the key, and vector<int> is its range 
   map<string,vector<int> > VarRanges;
   // map<string,vector<int> > TrueOut;
   // map<string,vector<int> > FalseOut;

   LivenessInfo() : LiveVars()/*,VarRanges(),TrueOut(),FalseOut()*/ {}
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
        //merge
    }
    vector<int> join(vector<int> left, vector<int> right)
    {
        vector<int> result;
        if (left.empty())
            result = right;
        else if (right.empty())
            result = left;
        else
        {
            if()
        }
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
        empty.push_back(MINUS_INF);
        empty.push_back(INF);
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

    //cut right from left
    vector<int> cut(vector<int> left,vector<int> right)
    {
      vector<int> result;
      if(left[0]<=right[0] && right[1]<=left[1])
      {
        int tmp_left=right[0]-left[0];
        int tmp_right=right[1]-left[1];
        if(!tmp_left&&!tmp_right)
        {
          result.push_back( left[0] );
          result.push_back( right[0]-1 );
          result.push_back( right[1]+1 );
          result.push_back( left[1] );
        }
        else
        {
          errs()<<"cut: other cases"<<"\n";
        }
      }
      return result;
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
            if(inst->isConditional())
            {
                Value * condition = inst->getCondition();
                //ICmpInst * cmpInst = (ICmpInst *)condition;
                ICmpInst * cmpInst=dyn_cast<ICmpInst>(condition);

                int predicate = cmpInst->isSigned() ? cmpInst->getSignedPredicate() : cmpInst->getUnsignedPredicate();
                //get the lhs and the rhs
                Value * lhs = cmpInst->getOperand(0);
                Value * rhs = cmpInst->getOperand(1);
                ConstantInt * rhsConstant = tryGetConstantValue(rhs);
                ConstantInt * lhsConstant = tryGetConstantValue(lhs);
                vector<int> lhsRange = tryGetRange(lhs,(*result)[pred_bb].second);
                vector<int> rhsRange = tryGetRange(rhs,(*result)[pred_bb].second);

                //range is empty
                vector<int> range; 

                Value * variable = NULL;
                ConstantInt * constant = NULL;

                //both lhs and rhs is constant
                if((lhsConstant && rhsConstant) /*|| (lhsRange.empty() && rhsRange.empty())*/)
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
                  variable=NULL;
                }
                // else
                // {
                //     //both have ranges, we have to assign new may ranges to both variables!
                //     if (!lhsRange.empty() && !rhsRange.empty()) 
                //     {
                //         variable = NULL;
                //     }
                //     // assign to rhs, since it has no range
                //     else if(!lhsRange.empty())
                //     {
                //         range=lhsRange;
                //         variable=rhs;
                //     }
                //     //assign to lhs, since it has no range
                //     else if(!rhsRange.empty())
                //     {
                //         range=rhsRange;
                //         variable=lhs;
                //     }
                // }//end of else

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
                                //trueMap[variable->getName().str()] = intersection;
                                //(*result)[trueBlock].first.VarRanges[variable->getName().str()]=intersection;
                                (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersection));
                            }
                            vector<int> _cut=cut(variableRange,constantRange);
                            (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),_cut));
                            //(*result)[trueBlock].first.VarRanges
                        }
                        //[-inf,inf]
                        else
                        {
                        }
                    }
                    // X != C
                    else if(predicate == CmpInst::ICMP_NE)
                    {
                        vector<int> constantRange;
                        map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                        falseMap.erase(variable->getName().str());
                        constantRange.push_back(constant->getSExtValue()); // min
                        constantRange.push_back(constant->getSExtValue()); // max
                        vector<int> intersection = intersect(variableRange, constantRange);
                        if (!intersection.empty())
                        {
                          (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersection));
                        }
                        vector<int> _cut=cut(variableRange,constantRange);
                        (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),_cut));
                      
                    }
                    // X > C
                    else if( ( (predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == lhs ) 
                              || ( (predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == rhs ) )
                    {
                        vector<int> constantRangeTrue;
                        vector<int> constantRangeFalse;
                        map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                        falseMap.erase(variable->getName().str());      
                        constantRangeTrue.push_back(constant->getSExtValue()+1); // min
                        constantRangeTrue.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max

                        //falseMap.erase(variable->getName().str());        
                        constantRangeFalse.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                        constantRangeFalse.push_back(constant->getSExtValue()); // max
                        
                        vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                        vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                        if (!intersectTrue.empty()) 
                        {
                          //trueMap[variable->getName().str()] = intersectTrue;
                          (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                        }
                        if (!intersectFalse.empty()) 
                        {
                          // falseMap[variable->getName().str()] = intersectFalse;
                          (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                        }
                        
                    }
                    // X < C
                    else if( ( (predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == lhs ) 
                              || ( (predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == rhs ) )
                    {
                        vector<int> constantRangeTrue;
                        vector<int> constantRangeFalse;
                        map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                        falseMap.erase(variable->getName().str());

                        constantRangeTrue.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                        constantRangeTrue.push_back(constant->getSExtValue()-1); // max
      
                        constantRangeFalse.push_back(constant->getSExtValue()); // min
                        constantRangeFalse.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max
                        
                        vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                        vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                        if (!intersectTrue.empty()) 
                        {
                          //trueMap[variable->getName().str()] = intersectTrue;
                          (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                        }
                        if (!intersectFalse.empty()) 
                        {
                          //falseMap[variable->getName().str()] = intersectFalse;
                          (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                        }
                    }
                    // X >= C
                    else if( ( (predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == lhs ) 
                              || ( (predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == rhs ) )
                    {
                        vector<int> constantRangeTrue;
                        vector<int> constantRangeFalse;
                      
                        map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                        falseMap.erase(variable->getName().str());

                        constantRangeTrue.push_back(constant->getSExtValue()); // min
                        constantRangeTrue.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max

                        constantRangeFalse.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                        constantRangeFalse.push_back(constant->getSExtValue()-1); // max
                        
                        vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                        vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                        if (!intersectTrue.empty()) 
                        {
                          //trueMap[variable->getName().str()] = intersectTrue;
                          (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                        }
                        if (!intersectFalse.empty()) 
                        {
                          //falseMap[variable->getName().str()] = intersectFalse;
                          (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                        }
                    }
                    // X <= C
                    else if( ( (predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == lhs ) 
                              || ( (predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == rhs ) )
                    {
                        vector<int> constantRangeTrue;
                        vector<int> constantRangeFalse;
                            
                        map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                        falseMap.erase(variable->getName().str());

                        constantRangeTrue.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                        constantRangeTrue.push_back(constant->getSExtValue()); // max
      
                        constantRangeFalse.push_back(constant->getSExtValue()+1); // min
                        constantRangeFalse.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max
                        
                        vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                        vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                        if (!intersectTrue.empty()) 
                        {
                          //trueMap[variable->getName().str()] = intersectTrue;
                          (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                        }
                        if (!intersectFalse.empty()) 
                        {
                          //falseMap[variable->getName().str()] = intersectFalse;
                          (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                        }

                    }
                    // else if (variable && !range.empty())
                    // {
                    // }
                    //both operands are ranges
                    else
                    {
                        //assign LHS first
                        range = rhsRange;
                        variable = lhs;
                        vector<int> variableRange = tryGetRange(variable);
                        // X==Y
                        if(predicate == CmpInst::ICMP_EQ)
                        {

                        }
                        //X!=Y
                        else if(predicate == CmpInst::ICMP_NE)
                        {

                        }
                        // X > Y, Y->(min,max)
                        else if( ((predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == lhs) || ((predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == rhs) ) 
                        {
                            vector<int> constantRangeTrue;
                            vector<int> constantRangeFalse;

                            map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                            falseMap.erase(variable->getName().str());

                            constantRangeTrue.push_back(range[0]+1); // min
                            constantRangeTrue.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max

                            constantRangeFalse.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                            constantRangeFalse.push_back(range[1]); // max

                            vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                            vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }

                            range=lhsRange;
                            variable=rhs;
                            variableRange.clear();
                            variableRange = tryGetRange(variable);
                            constantRangeTrue.clear();
                            constantRangeFalse.clear();
                            intersectTrue.clear();
                            intersectFalse.clear();
                            falseMap.erase(variable->getName().str());

                            constantRangeTrue.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                            constantRangeTrue.push_back(range[1]-1); // max

                            constantRangeFalse.push_back(range[0]); // min
                            constantRangeFalse.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max
                          
                            intersectTrue = intersect(constantRangeTrue, variableRange);        
                            intersectFalse = intersect(constantRangeFalse, variableRange);

                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }

                        }
                        // X < Y, Y->(min,max)
                        else if( ((predicate == CmpInst::ICMP_ULT || predicate == CmpInst::ICMP_SLT) && variable == lhs) || ((predicate == CmpInst::ICMP_UGT || predicate == CmpInst::ICMP_SGT) && variable == rhs) )
                        {
                            vector<int> constantRangeTrue;
                            vector<int> constantRangeFalse;

                            map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                            falseMap.erase(variable->getName().str());

                            constantRangeTrue.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                            constantRangeTrue.push_back(range[1]-1); // max

                            constantRangeFalse.push_back(range[0]); // min
                            constantRangeFalse.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max
                          
                            intersectTrue = intersect(constantRangeTrue, variableRange);        
                            intersectFalse = intersect(constantRangeFalse, variableRange);

                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }
                            
                            range=lhsRange;
                            variable=rhs;
                            variableRange.clear();
                            variableRange = tryGetRange(variable);
                            constantRangeTrue.clear();
                            constantRangeFalse.clear();
                            intersectTrue.clear();
                            intersectFalse.clear();
                            falseMap.erase(variable->getName().str());

                            
                            constantRangeTrue.push_back(range[0]+1); // min
                            constantRangeTrue.push_back(INF /*APInt::getSignedMaxValue(32).getSExtValue()*/); // max

                            constantRangeFalse.push_back(MINUS_INF /*APInt::getSignedMinValue(32).getSExtValue()*/); // min
                            constantRangeFalse.push_back(range[1]); // max

                            vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                            vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }

                        }
                        // X >= Y, Y->(min,max)
                        else if( ((predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == lhs) || ((predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == rhs) )
                        {
                            vector<int> constantRangeTrue;
                            vector<int> constantRangeFalse;

                            map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                            falseMap.erase(variable->getName().str());

                            constantRangeTrue.push_back(range[0]); // min
                            constantRangeTrue.push_back(INF); // max

                            constantRangeFalse.push_back(MINUS_INF); // min
                            constantRangeFalse.push_back(range[1]-1); // max
                          
                            intersectTrue = intersect(constantRangeTrue, variableRange);        
                            intersectFalse = intersect(constantRangeFalse, variableRange);

                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }
                            
                            range=lhsRange;
                            variable=rhs;
                            variableRange.clear();
                            variableRange = tryGetRange(variable);
                            constantRangeTrue.clear();
                            constantRangeFalse.clear();
                            intersectTrue.clear();
                            intersectFalse.clear();
                            falseMap.erase(variable->getName().str());

                            
                            constantRangeTrue.push_back(MINUS_INF); // min
                            constantRangeTrue.push_back(range[1]); // max

                            constantRangeFalse.push_back(range[0]+1); // min
                            constantRangeFalse.push_back(INF); // max

                            vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                            vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }
                        }
                        // X <= Y, Y->(min,max)
                        else if( ((predicate == CmpInst::ICMP_ULE || predicate == CmpInst::ICMP_SLE) && variable == lhs) || ((predicate == CmpInst::ICMP_UGE || predicate == CmpInst::ICMP_SGE) && variable == rhs) )
                        {
                            vector<int> constantRangeTrue;
                            vector<int> constantRangeFalse;

                            map<string,vector<int>> falseMap=&((*result)[pred_bb].second).VarRanges;
                            falseMap.erase(variable->getName().str());

                            constantRangeTrue.push_back(MINUS_INF); // min
                            constantRangeTrue.push_back(range[1]); // max

                            constantRangeFalse.push_back(range[0]+1); // min
                            constantRangeFalse.push_back(INF); // max
                          
                            intersectTrue = intersect(constantRangeTrue, variableRange);        
                            intersectFalse = intersect(constantRangeFalse, variableRange);

                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }
                            
                            range=lhsRange;
                            variable=rhs;
                            variableRange.clear();
                            variableRange = tryGetRange(variable);
                            constantRangeTrue.clear();
                            constantRangeFalse.clear();
                            intersectTrue.clear();
                            intersectFalse.clear();
                            falseMap.erase(variable->getName().str());

                            constantRangeTrue.push_back(range[0]); // min
                            constantRangeTrue.push_back(INF); // max

                            constantRangeFalse.push_back(MINUS_INF); // min
                            constantRangeFalse.push_back(range[1]-1); // max

                            vector<int> intersectTrue = intersect(constantRangeTrue, variableRange);        
                            vector<int> intersectFalse = intersect(constantRangeFalse, variableRange);      
                            if (!intersectTrue.empty()) 
                            {
                              //trueMap[variable->getName().str()] = intersectTrue;
                              (*result)[trueBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectTrue));
                            }
                            if (!intersectFalse.empty()) 
                            {
                              //falseMap[variable->getName().str()] = intersectFalse;
                              (*result)[falseBlock].first.VarRanges.insert(pair<string,vector<int> >(variable->getName().str(),intersectFalse));
                            }
                        }

                    }
                }//end of if variable && constant
            }//end of if
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



