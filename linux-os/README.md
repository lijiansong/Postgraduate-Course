## Linux Kernel
This archieve is mainly about linux kernel.

### Content

[1]使用`gcc -g -Wall hello-world.c -o hello-world`命令编译hello-world.c源文件，使用-v选项可以查看完整和详细的gcc编译过程，`gcc -g -Wall -v hello-world.c -o hello-world`.
使用readelf命令查看ELF格式的二进制可执行程序的内容`readelf -a hello-world`。
> ELF 文件的主要内容就是由各个 section 及 symbol表组成的。在上面的 section 列表中,主要是 text 段、 data 段和 bss 段。 text 段为代码段,用于保存可执行指令。 data 段为数据段,用于保存有非 0 初始值的全局变量和静态变量。 bss 段用于保存没有初始值或初值为 0 的全局变量和静态变量,当程序加载时, bss 段中的变量会被初始化为 0 。这个段并不占用物理空间 —— 因为完全没有必要,这些变量的值固定初始化为 0 .
其他的段有：
- debug 段:顾名思义,用于保存调试信息。
- dynamic 段:用于保存动态链接信息。
- fini 段:用于保存进程退出时的执行程序。当进程结束时,系统会自动执行这部分代码。
- init 段:用于保存进程启动时的执行程序。当进程启动时,系统会自动执行这部分代码。
- rodata 段:用于保存只读数据,如 const 修饰的全局变量、字符串常量。
- symtab 段:用于保存符号表。

### REF

[1]《程序员的自我修养--链接/装载和库》

[2]《Linkers & Loaders》

[3]Linux Kernel
