/*
MemoryManager_Z::MemoryManager_Z(void)	__text	0000DFD8	0000001E	0000001C	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::~MemoryManager_Z()	__text	0000DFF6	00000015	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::~MemoryManager_Z()	__text	0000E00C	00000025	0000001C	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Shut(void)	__text	0000E032	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Init(void)	__text	0000E038	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::SetCallStackPtrs(ulong *,long)	__text	0000E03E	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Alloc(ulong,char const*,char const*,long,ulong)	__text	0000E044	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::AllocEnd(ulong,char const*,char const*,long,ulong)	__text	0000E054	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::AllocContiguous(ulong,char const*,char const*,long,ulong)	__text	0000E064	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Realloc(void *,ulong,char const*,char const*,long)	__text	0000E074	00000015	00000004	0000000C	R	.	.	.	.	.	B	T	.
MemoryManager_Z::Free(void *)	__text	0000E08A	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::FreeContiguous(void *)	__text	0000E09A	0000000F	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetFreeMem(void)	__text	0000E0AA	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetAllocatedMem(void)	__text	0000E0B4	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetLargestFree(void)	__text	0000E0BC	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::GetFragments(void)	__text	0000E0CA	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::MarkMem(ulong)	__text	0000E0D2	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::SetFitLimits(ulong,ulong)	__text	0000E0D8	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::SetBestBit(bool)	__text	0000E0DE	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::ShowUnMarkedMem(void)	__text	0000E0E4	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::ShowMostNbMalloc(void)	__text	0000E0EE	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryManager_Z::VerifyMem(void)	__text	0000E0F4	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
sub_E0FE	__text	0000E0FE	00000010	00000004	00000004	R	.	.	.	.	.	B	.	.
*/

#include <MemoryManager_Z.h>
#include <stdlib.h>

MemoryManager_Z MemManager;

void* MemoryManager_Z::Alloc(unsigned long size, const char* comment, const char* filename, long line, unsigned long align){
    return malloc(size);
}

void* MemoryManager_Z::Realloc(void* ptr, unsigned long size, const char* comment, const char* filename, long line){
    return realloc(ptr, size);
}

void MemoryManager_Z::Free(void* ptr){
    free(ptr);
}