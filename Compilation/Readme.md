# Compilation

This archieve mainly focus on compilation technology, such as LLVM, Clang, self-making programming language and etc.

## Clang & LLVM Tutorials

Clang tutorials, see [here...](https://github.com/lijiansong/Postgraduate-Course/tree/master/Compilation/Clang)

LLVM tutorials, see [here...](https://github.com/lijiansong/Postgraduate-Course/tree/master/Compilation/LLVM)

### Self-making Tools Based on LLVM & Clang

cmd to get the ast
```
$clang -Xclang -ast-dump -fsyntax-only file.c &> filename
```
cmd to get the dot file
```
$clang -fsyntax-only -Xclang -ast-view file.c 
$xdot file.dot
```


## Reference
[CGO-2004, LLVM tech report...](http://llvm.org/pubs/2004-01-30-CGO-LLVM.html)<br>
[Build system tools, Ninja](http://www.aosabook.org/en/posa/ninja.html)<br>
[LLVM Core Libraries Infrastruction](http://llvm.org/releases/3.0/docs/UsingLibraries.html)<br>
[LLVM Programmers' Manual...](http://llvm.org/docs/ProgrammersManual.html)<br>
[Clang Libraries...](http://clang.llvm.org/doxygen/group__CINDEX.html)<br>
[TableGen Language Reference...](http://llvm.org/docs/TableGen/LangRef.html)<br>
[Translation unit manipulation](http://clang.llvm.org/doxygen/group__CINDEX__TRANSLATION__UNIT.html)<br>
[Stmt Class Reference](http://clang.llvm.org/doxygen/classclang_1_1Stmt.html)<br>
[Clang Plugins...](http://clang.llvm.org/docs/ClangPlugins.html)<br>
[Kaleidoscope: Implementing a Language with LLVM](http://llvm.org/docs/tutorial/)<br>
[Clang design...](http://clang.llvm.org/docs/InternalsManual.html)<br>
[How to parse C programs with clang](http://amnoid.de/tmp/clangtut/tut.html)<br>
[other refs... course](http://swtv.kaist.ac.kr/courses/cs453-fall13)<br>
