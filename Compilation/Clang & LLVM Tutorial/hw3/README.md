#LLVM Value Range Analysis

`Value range analysis` is a type of `data flow analysis` that tracks the range (interval) of values that a numeric variable can take on at each point of a program's execution. <br>
The resulting information can be used in optimizations such as `redundancy elimination, dead code elimination, instruction selection, etc`. But can also be used to improve the `safety of programs`, e.g. in the detection of buffer overruns. 
Techniques for value range analysis typically use `symbolic analysis` extensively.

## Gen bitcode
- bitcode generation using following cmds
```
$ clang -c –emit-llvm –g3 funptr.c
$ opt -dot-cfg-only funcptr.bc
$ opt –mem2reg -S funcptr.bc –o funcptr.opt
```

## Reference
[1] [Birch, Johnnie; van Engelen, Robert; Gallivan, Kyle. "Value Range Analysis of Conditionally Updated Variables and Pointers".](http://www.cs.fsu.edu/~engelen/cpcpaper.pdf)
[2] [Adding Range Analysis to LLVM](http://llvm.1065342.n5.nabble.com/Range-Analysis-GSoC-2011-Proposal-td40546.html)
