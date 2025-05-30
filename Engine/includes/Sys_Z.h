#ifndef _SYS_Z_H_
#define _SYS_Z_H_
#include <Types_Z.h>

class Sys_Z {
public:
    static void* MemCpyFrom(void* Dest, void* Src, const U32 Size);
    static void GetAbsoluteFromPath(const Char* Path, Char* AbsPath, Char* Unk);
};

#endif