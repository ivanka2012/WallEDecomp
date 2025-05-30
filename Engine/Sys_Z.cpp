#include <Sys_Z.h>
#include <string.h>

void* Sys_Z::MemCpyFrom(void* Dest, void* Src, const U32 Size){
    memcpy(Dest, Src, Size);
    return Src + Size;
}