// stdio.c
#include "minicrt.h"

int mini_crt_io_init()
{
    return 1;
}

#ifdef WIN32
#include <Windows.h>

FILE* fopen(const char * filename, const char * mode)
{
    HANDLE hFile = 0;
    int access = 0;
    int creation = 0;

    if (strcmp(mode, "w") == 0) {
        access |= GENERIC_WRITE;
        creation |= CREATE_ALWAYS;
    }

    if (strcmp(mode, "w+") == 0) {
        access |= GENERIC_WRITE | GENERIC_READ;
        creation |= CREATE_ALWAYS;
    }

    if (strcmp(mode, "r") == 0) {
        access |= GENERIC_READ;
        creation += OPEN_EXISTING;
    }

    if (strcmp(mode, "r+") == 0) {
        access |= GENERIC_WRITE | GENERIC_READ;
        creation |= TRUNCATE_EXISTING;
    }

    hFile = CreateFileA(filename, access, 0, 0, creation, 0, 0);
    if (hFile == INVALID_HANDLE_VALUE)
        return 0;

    return (FILE*)hFile;
}

int fread(void * buffer, int size, int count, FILE * stream)
{
    int read = 0;
    if (!ReadFile((HANDLE)stream, buffer, size * count, &read, 0))
        return 0;
    return read;
}

int fwrite(const void * buffer, int size, int count, FILE * stream)
{
    int written = 0;
    if (!WriteFile((HANDLE)stream, buffer, size * count, *written, 0))
        return 0;
    return written;
}

int fclose(FILE * fp)
{
    return CloseHandle((HANDLE)fp);
}

int fseek(FILE * fp, int offset, int set)
{
    return SetFilePointer((HANDLE)fp, offset, 0, set);
}

#else // #ifdef WIN32

static int open(const char * pathname, int flags, int mode)
{
    int fd = 0;
    asm("movl $5, %%eax  \n\t"
        "movl %1, %%ebx  \n\t"
        "movl %2, %%ecx  \n\t"
        "movl %3, %%edx  \n\t"
        "int $0x80       \n\t"
        "movl %%eax, %0  \n\t"
        :"=m"(fd)
        :"m"(pathname), "m"(flags), "m"(mode));
}

static int read(int fd, void * buffer, unsigned size)
{
}
}
