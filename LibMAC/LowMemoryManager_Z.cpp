/*
MemoryManager_Z::MemoryManager_Z(void)	__text	0000DFD8	0000001E	0000001C	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::~MemoryManager_Z()	__text	0000DFF6	00000015	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::~MemoryManager_Z()	__text	0000E00C	00000025	0000001C	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Shut(void)	__text	0000E032	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Init(void)	__text	0000E038	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::SetCallStackPtrs(uS32 *,S32)	__text	0000E03E	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Alloc(uS32,char const*,char const*,S32,uS32)	__text	0000E044	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::AllocEnd(uS32,char const*,char const*,S32,uS32)	__text	0000E054	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::AllocContiguous(uS32,char const*,char const*,S32,uS32)	__text	0000E064	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Realloc(void *,uS32,char const*,char const*,S32)	__text	0000E074	00000015	00000004	0000000C	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Free(void *)	__text	0000E08A	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::FreeContiguous(void *)	__text	0000E09A	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetFreeMem(void)	__text	0000E0AA	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetAllocatedMem(void)	__text	0000E0B4	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetLargestFree(void)	__text	0000E0BC	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetFragments(void)	__text	0000E0CA	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::MarkMem(uS32)	__text	0000E0D2	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::SetFitLimits(uS32,uS32)	__text	0000E0D8	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::SetBestBit(bool)	__text	0000E0DE	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::ShowUnMarkedMem(void)	__text	0000E0E4	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::ShowMostNbMalloc(void)	__text	0000E0EE	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::VerifyMem(void)	__text	0000E0F4	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
sub_E0FE	__text	0000E0FE	00000010	00000004	00000004	R	.	.	.	.	.	B	.	.
*/

#include <MemoryManager_Z.h>
#include <stdlib.h>

MemoryManager_Z MemManager;

MemoryManager_Z::MemoryManager_Z() {

}

MemoryManager_Z::~MemoryManager_Z() {

}


void MemoryManager_Z::Init() {

}

void MemoryManager_Z::Shut() {

}

void* MemoryManager_Z::Alloc(U32 size, const Char* comment, const Char* filename, S32 line, U32 align){
    return malloc(size);
}

void* MemoryManager_Z::AllocEnd(U32 size, const Char* comment, const Char* filename, S32 line, U32 align) {
    return malloc(size);
}

void* MemoryManager_Z::Realloc(void* ptr, U32 size, const Char* comment, const Char* filename, S32 line){
    return realloc(ptr, size);
}

void MemoryManager_Z::Free(void* ptr){
    free(ptr);
}

void* MemoryManager_Z::AllocContiguous(U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line, U32 i_Align) {
    return malloc(i_Size);
}

void MemoryManager_Z::FreeContiguous(void* i_Ptr) {
    free(i_Ptr);
}

U32 MemoryManager_Z::GetAllocatedMem() {
    return 0;
}

U32 MemoryManager_Z::GetFreeMem() {
    return 666666; //SATAN!
}

U32 MemoryManager_Z::GetFragments() {
    return 0;
}

U32 MemoryManager_Z::GetLargestFree() {
    return GetFreeMem();
}

void MemoryManager_Z::MarkMem(U32 a1) {

}

U32 MemoryManager_Z::ShowUnMarkedMem() {
    return 1;
}

void MemoryManager_Z::ShowMostNbMalloc() {

}

void MemoryManager_Z::SetFitLimits(U32 low, U32 high) {

}

void MemoryManager_Z::SetBestBit(bool bit) {

}

bool MemoryManager_Z::VerifyMem() {
    return 1;
}

void MemoryManager_Z::SetCallStackPtrs(U32* a1, S32 a2) {

}
