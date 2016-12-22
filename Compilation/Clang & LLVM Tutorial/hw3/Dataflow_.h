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

//todo: all process logic to be written here
//using namespace std;

template<class T>
void compForwardDataflow (Function *fn,
                          DataflowVisitor<T> *visitor,
                          typename DataflowResult<T>::Type *result,
                          const T & initval)
{
    std::set<BasicBlock *> worklist;
    // Initialize the worklist with all exit blocks
    for(Function::iterator bi=fn->begin(),be=fn->end();bi!=be;++bi)
    {
        BasicBlock *bb=&*bi;
        result->insert(std::make_pair(bb,std::make_pair(initval,initval)));
        worklist.insert(bb);
    }

    // Iteratively compute the dataflow result
    
    //init
    BasicBlock *bb=*worklist.begin();
    worklist.erase(worklist.begin());



    while(!worklist.empty())
    {
        bb=*worklist.begin();
        worklist.erase(worklist.begin());

        T bbEnterVal = (*result)[bb].first;

        for (pred_iterator pi = pred_begin(bb), pe = pred_end(bb); pi != pe; ++pi) 
        {
            //merge(map<string,aaa> dest,map<string,aaa> src);  
        }

        visitor->compDFVal(bb, &bbEnterVal, true);
        (*result)[bb].second = bbEnterVal;

    }
    return;
}



template<class T>
void compBackwardDataflow (Function *fn, 
                           DataflowVisitor<T> *visitor,
                           typename DataflowResult<T>::Type *result,
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
        visitor->compDFVal(bb, &bbexitval, false);

        // If outgoing value changed, propagate it along the CFG
        if (bbexitval == (*result)[bb].first) continue;
        (*result)[bb].first = bbexitval;

        for (pred_iterator pi = pred_begin(bb), pe = pred_end(bb); pi != pe; pi++) 
        {
            worklist.insert(*pi);
        }
    }
}
