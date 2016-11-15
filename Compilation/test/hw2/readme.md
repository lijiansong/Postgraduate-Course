##FuncPtrPass

Toy code about use-def chains based on the LLVM IR and bitcode. Output the function call info in the bitcode file, e.g.
- Direct function calls. Print the function name and line no.
- FuncPtr i.e. function pointer. Calculate the functions that may call, if it is determined, replace it with direct function call. Consider the situation that the function pointers are stored in the memory.

## Postscripts
- Remove every uses of [getGlobalContext](https://reviews.llvm.org/rL266379), but the C API, and the [solution...](https://reviews.llvm.org/D19094)
