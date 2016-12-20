#LLVM Value Range Analysis

`Value range analysis` is a type of `data flow analysis` that tracks the range (interval) of values that a numeric variable can take on at each point of a program's execution. <br>
The resulting information can be used in optimizations such as `redundancy elimination, dead code elimination, instruction selection, etc`. But can also be used to improve the `safety of programs`, e.g. in the detection of buffer overruns. 
Techniques for value range analysis typically use `symbolic analysis` extensively.

## Gen bitcode
- bitcode generation using following cmds
```
$ clang -c –emit-llvm –g3 funptr.c
$ opt -dot-cfg-only funcptr.bc
$ opt -dot-cfg-only funcptr.bc
$ opt -S –mem2reg funcptr.bc –o funcptr.opt
```
- with so many test cases, it may be anoying to generate the bitcode file one by one, `system` function may be useful, we can call `system()` like this.

```
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
int main(int argc, char const *argv[])
{
	for(int i=1;i<=34;++i)
	{
		stringstream ss;
		ss<<i;
		//char *num=itoa(i);
		string cmd_str="clang -c -emit-llvm -g3 test"+ss.str()+".c";
		printf("%s\n",cmd_str.c_str());
		system(cmd_str.c_str());

		cmd_str="opt -S -mem2reg test"+ss.str()+".bc -o test"+ss.str()+".opt";
		printf("%s\n",cmd_str.c_str());
		system(cmd_str.c_str());
		//delete num;
		ss.clear();
	}
	printf("done!\n");
	return 0;
}
```

## Reference
[1] [Birch, Johnnie; van Engelen, Robert; Gallivan, Kyle. "Value Range Analysis of Conditionally Updated Variables and Pointers".](http://www.cs.fsu.edu/~engelen/cpcpaper.pdf)<br>
[2] [Adding Range Analysis to LLVM](http://llvm.1065342.n5.nabble.com/Range-Analysis-GSoC-2011-Proposal-td40546.html)<br>
