ELF parser
=======================
This archieve is mainly about a parser of ELF file.

In Unix-like system, the Executable and Linkable Format (ELF, formerly called Extensible Linking Format) is a common standard file format for executables, object code, shared libraries, and core dumps. <br>
First published in the System V Release 4 (SVR4) Application Binary Interface (ABI) specification,and later in the Tool Interface Standard, it was quickly accepted among different vendors of Unix systems, such as Linux and etc.<br>
ELF is flexible and extensible by design, and it is not bound to any particular processor or architecture. This has allowed it to be adopted by many different operating systems on many different platforms. <br>

Each ELF file is made up of one ELF header, followed by file data. The file data can include:
- Program header table, describing zero or more segments
- Section header table, describing zero or more sections
- Data referred to by entries in the program header table or section header table

The segments contain information that is necessary for runtime execution of the file, while sections contain important data for linking and relocation. Any byte in the entire file can be owned by at most one section, and there can be orphan bytes which are not owned by any section.
More details about ELF, see [here...](https://web.archive.org/web/20130403001804/http://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/binary-formats.html)
Many tools can be taken use of to parse the ELF file, such as `readelf, elfutils, elfdump, objdump`...

### Build
```
$ cd xxx_dir
$ make
$ ./elf-parser ./test-cases/hello/hello
$ make clean
```
To generate the assembly code, you can type the following cmds:
```
$ g++ -E hello.cpp -o hello.i
$ g++ -S hello.cpp -o hello.s
$ g++ -c hello.s -o hello.o
```
