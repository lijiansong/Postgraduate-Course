/************************************************************************
 *
 * @file Dataflow.tpp
 *
 * General dataflow framework - template implementation
 *
 ***********************************************************************/

#include <map>
#include <set>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Function.h>
#include <vector>

//todo: all process logic to be written here
using namespace std;
void printBasicBlock(BasicBlock *bb)
{
	BasicBlock::iterator bb_it=bb->begin(),bb_ie=bb->end();
	for(;bb_it!=bb_ie;++bb_it)
	{
		Instruction *inst = dyn_cast < Instruction > (bb_it);
		errs()<<*inst<<"\n";
	}
}

template<class T>
void compForwardDataflow (Function *fn,
                          DataflowVisitor<T> *visitor,
                          typename DataflowResult<T>::Type *result,
                          typename DataflowBackEdge<T>::BackEdge *back_edge,
                          const T & initval)
{
    std::/*set*/vector<BasicBlock *> worklist;
    map<BasicBlock *,bool> visited;
    // Initialize the worklist with all exit blocks
    for(Function::iterator bi=fn->begin(),be=fn->end();bi!=be;++bi)
    {
        BasicBlock *bb=&*bi;
        result->insert(std::make_pair(bb,std::make_pair(initval,initval)));
        worklist.push_back(bb);
        visited[bb]=false;
    }

    //find loop,it may be wrong
    vector<BasicBlock *> tmp = worklist;
    auto it=tmp.begin();
    auto ie=tmp.end();
    for( ;it != ie; ++it )
    {
    	BasicBlock *bb = *it;
    	visited[bb]=true;
    	for (succ_iterator si = succ_begin(bb), se = succ_end(bb); si != se; si ++) 
	    {
	        BasicBlock *succ = *si;
	        if(visited[succ])
	        {
	        	back_edge->insert(make_pair(bb,succ));
	        	//printBasicBlock(bb);
	        	//errs()<<"\n\n";
	        	//printBasicBlock(succ);
	        }
	    }
    }
    tmp.clear();
    
    // Iteratively compute the dataflow result
    
    //the start block has no in dataflow, process independently
    BasicBlock *bb=*worklist.begin();
    worklist.erase(worklist.begin());
    //T bbEnterVal = (*result)[bb].first;
    //compute the start block's out-flow value(each var's interval)
    visitor->compDFVal( bb, &((*result)[bb].second),result,back_edge, true );


    while(!worklist.empty())
    {
        bb=*worklist.begin();
        worklist.erase(worklist.begin());


        //conditionalbranch
        for (pred_iterator pi = pred_begin(bb), pe = pred_end(bb); pi != pe; ++pi) 
        {
            visitor->handlePredIcmp(*pi,result);
        }

        T *bbEnterVal = &((*result)[bb].first);

        for (pred_iterator pi = pred_begin(bb), pe = pred_end(bb); pi != pe; ++pi) 
        {
            //merge all pred basic blocks
            //visitor->merge(&bbexitval, (*result)[succ].first);
            visitor->merge(bbEnterVal,(*result)[*pi].second,bb,result);
        }

        visitor->compDFVal(bb, bbEnterVal,result,back_edge, true);
        //compute the basic block's out-flow
        (*result)[bb].second = *bbEnterVal;

    }
    return;
}



template<class T>
void compBackwardDataflow (Function *fn, 
                           DataflowVisitor<T> *visitor,
                           typename DataflowResult<T>::Type *result,
                           typename DataflowBackEdge<T>::BackEdge *back_edge,
                           const T &initval) 
{

    std::set<BasicBlock *> worklist;

    // Initialize the worklist with all exit blocks
    for ( Function::iterator bi = fn->begin(); bi != fn->end(); ++bi ) 
    {
        BasicBlock * bb = &*bi;
        result->insert(std::make_pair(bb, std::make_pair(initval, initval)));
        worklist.insert(bb);
    }

    // Iteratively compute the dataflow result
    while (!worklist.empty()) 
    {
        BasicBlock *bb = *worklist.begin();
        worklist.erase(worklist.begin());

        // Merge all incoming value
        T bbexitval = (*result)[bb].second;
        for (succ_iterator si = succ_begin(bb), se = succ_end(bb); si != se; si ++) 
        {
            BasicBlock *succ = *si;
            visitor->merge(&bbexitval, (*result)[succ].first);
        }

        (*result)[bb].second = bbexitval;
        visitor->compDFVal(bb, &bbexitval, result,back_edge,false);

        // If outgoing value changed, propagate it along the CFG
        if (bbexitval == (*result)[bb].first) continue;
        (*result)[bb].first = bbexitval;

        for (pred_iterator pi = pred_begin(bb), pe = pred_end(bb); pi != pe; pi++) 
        {
            worklist.insert(*pi);
        }
    }
}
