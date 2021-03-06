## Linux Kernel
This archieve is mainly about linux kernel.

### Content

[1] 使用`gcc -g -Wall hello-world.c -o hello-world`命令编译hello-world.c源文件，使用-v选项可以查看完整和详细的gcc编译过程，`gcc -g -Wall -v hello-world.c -o hello-world`.
使用readelf命令查看ELF格式的二进制可执行程序的内容`readelf -a hello-world`。
> ELF 文件的主要内容就是由各个 section 及 symbol表组成的。在上面的 section 列表中,主要是 text 段、 data 段和 bss 段。 text 段为代码段,用于保存可执行指令。 data 段为数据段,用于保存有非 0 初始值的全局变量和静态变量。 bss 段用于保存没有初始值或初值为 0 的全局变量和静态变量,当程序加载时, bss 段中的变量会被初始化为 0 。这个段并不占用物理空间 —— 因为完全没有必要,这些变量的值固定初始化为 0 .
其他的段有：
- debug 段:顾名思义,用于保存调试信息。
- dynamic 段:用于保存动态链接信息。
- fini 段:用于保存进程退出时的执行程序。当进程结束时,系统会自动执行这部分代码。
- init 段:用于保存进程启动时的执行程序。当进程启动时,系统会自动执行这部分代码。
- rodata 段:用于保存只读数据,如 const 修饰的全局变量、字符串常量。
- symtab 段:用于保存符号表。

g++ -E hello.cpp -o hello.i<br>
g++ -S hello.cpp -o hello.s<br>
g++ -c hello.s -o hello.o<br>
readelf -a hello<br>

[2] 在linux环境下可以利用strace命令跟踪系统调用`strace ./hello-world`,该命令会将操作系统加载/运行和退出的整个过程都显示出来。
```
execve("./hello-world", ["./hello-world"], [/* 61 vars */]) = 0
brk(0)                                  = 0x9ea000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f8752d4d000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=95723, ...}) = 0
mmap(NULL, 95723, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f8752d35000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P \2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1840928, ...}) = 0
mmap(NULL, 3949248, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f8752768000
mprotect(0x7f8752922000, 2097152, PROT_NONE) = 0
mmap(0x7f8752b22000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ba000) = 0x7f8752b22000
mmap(0x7f8752b28000, 17088, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f8752b28000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f8752d34000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f8752d32000
arch_prctl(ARCH_SET_FS, 0x7f8752d32740) = 0
mprotect(0x7f8752b22000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f8752d4f000, 4096, PROT_READ) = 0
munmap(0x7f8752d35000, 95723)           = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f8752d4c000
write(1, "hello world!\n", 13hello world!
)          = 13
exit_group(0)                           = ?
+++ exited with 0 +++

```
> 在 Linux 环境中,执行一个命令时,`首先是由 shell 调用 fork ,然后在子进程中来真正执行这个命令(这一过程在 strace 输出中无法体现)。 strace 是 hello_world 开始执行后的输出`。首先是调用 execve 来加载 hello_world ,然后 ld 会分别检查 ld.so.nohwcap 和 ld.so.preload 。其中,如果ld.so.nohwcap 存在,则 ld 会加载其中未优化版本的库。如果 ld.so.preload 存在,则 ld 会加载其中的库 —— `在一些项目中,我们需要拦截或替换系统调用或 C 库,此时就会利用这个机制,使用 LD_PRELOAD 来实现。`之后利用 mmap 将 ld.so.cache 映射到内存中, ld.so.cache 中保存了库的路径,这样就完成了所有的准备工作。接着 ld 加载 c 库 ——libc.so.6 ,利用 mmap 及 mprotect 设置程序的各个内存区域,到这里,程序运行的环境已经完成。后面的 write 会向文件描述符 1 (即标准输出)输出 "Hello world ! \n" ,返回值为 13 ,它表示 write 成功的字符个数。最后调用 exit_group 退出程序,此时参数为 0 ,表示程序退出的状态 —— 此例中 hello-world 程序返回 0 。

[3] 系统调用是操作系统提供的服务,是应用程序与内核通信的接口。用户空间的程序默认是通过栈来传递参数的。对于系统调用来说,内核态和用户态使用的是不同
的栈,这使得系统调用的参数只能通过寄存器的方式进行传递。Linux 环境下,使用的 C 库一般都是 [glibc](https://ftp.gnu.org/gnu/glibc/) ,它封装了几乎所有的系统调用,代码中使用的 “ 系统调用 ” ,实际上就是调用 C 库中的函数。 `C 库函数同样位于用户态,所以编译器可以统一处理所有的函数调用,而不用区分该函数到底是不是系统调用`。

[4] `交叉编译`，简单来说，如果目标平台没有办法安装编译器，或者由于资源有限等无法完成正常的编译过程，那就需要另一个平台来辅助生成可执行文件。e.g. 很多情况下，我们是在PC平台上进行Android系统的研发工作，这时就需要交叉编译器来生成运行于Arm平台上的系统包。这里的平台是指硬件平台和操作系统环境的综合。
交叉编译主要包含以下几个对象：<br>
`宿主机（Host）`:指的是我们开发和编译代码所在的平台。 <br>
`目标机（Target）`:相对于宿主机的就是目标机，这是编译生成的系统包的目标平台。 <br>
`交叉编译器(Cross Compiler)`:本身运行于宿主机上，用于生产目标机可执行文件的编译器。<br>


### REF

[1]《程序员的自我修养--链接/装载和库》

[2]《Linkers & Loaders》

[3]Linux Kernel
