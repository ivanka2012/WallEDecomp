/*
MemoryBank_Z::GetAllocatedMem(void)	__text	001FFBBC	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetNbFreeBlocks(void)	__text	001FFBCA	0000001D	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::MemoryBank_Z(void)	__text	001FFBEA	0000002A	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::~MemoryBank_Z()	__text	001FFC16	0000002A	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::SetBestBit(bool)	__text	001FFC42	00000051	00000018	00000005	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FindBucket(long)	__text	001FFC96	0000006C	00000004	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::CheckBlock(MemoryBlock_Z *)	__text	001FFD02	000000A9	0000001C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::CheckBuckets(void)	__text	001FFDAC	00000065	0000003C	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::SetFitLimits(ulong,ulong)	__text	001FFE14	00000089	0000003C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetFreeMem(void)	__text	001FFE9E	0000007D	0000003C	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetLargestFreeBlock(void)	__text	001FFF1C	00000084	0000003C	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetLargestFree(void)	__text	001FFFA0	00000009	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FindFirstBlock(long)	__text	001FFFAA	000000C5	0000003C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Dicho_RecEqual(MemoryBlock_Z **,ulong,long,long)	__text	00200070	000000DB	0000002C	00000014	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetInBucket(long,MemoryBlock_Z *)	__text	0020014C	000000C0	0000003C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::RemoveBlockFromBucket(long,MemoryBlock_Z *)	__text	0020020E	00000072	0000002C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::RemoveBlock(MemoryBlock_Z *)	__text	00200280	00000042	0000001C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FindSomeBlock(MemoryBlock_Z *)	__text	002002C2	0000004B	0000001C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::TestIntegrity(MemoryBlock_Z *)	__text	0020030E	00000138	0000002C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Dicho_RecAfter(MemoryBlock_Z **,ulong,long,long)	__text	00200446	0000017C	0000002C	00000014	R	.	.	.	.	.	B	T	.
MemoryBank_Z::AddBlockToBucket(long,MemoryBlock_Z *)	__text	002005C2	000000C2	0000004C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::AddBlock(MemoryBlock_Z *)	__text	00200684	00000042	0000001C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::SplitToAllocAndFreeBlock(MemoryBlock_Z *,ulong)	__text	002006C6	00000110	0000003C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Init(void *,ulong)	__text	002007D6	000000D2	0000001C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Dicho_RecBigger(MemoryBlock_Z **,ulong,long,long)	__text	002008A8	0000012F	0000002C	00000014	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FindBlock(long,long)	__text	002009D8	0000017D	0000005C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FindBestBlock(long)	__text	00200B56	00000065	0000002C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FindBlock(long)	__text	00200BBC	0000003A	0000001C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Malloc(ulong,char const*,char const*,ulong,ulong)	__text	00200BF6	0000010E	0000004C	00000018	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Extend(void)	__text	00200D04	0000011A	0000005C	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::MergeWithNextRealloc(void *,ulong)	__text	00200E1E	000000B5	0000003C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Malloc_end(ulong,ulong,char const*)	__text	00200ED4	000001B5	0000004C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Free(void *)	__text	0020108A	00000166	0000003C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FullRealloc(void *,ulong,char const*)	__text	002011F0	000000E9	0000004C	00000010	R	.	.	.	.	.	B	T	.
MemoryBank_Z::Realloc(void *,ulong,char const*)	__text	002012DA	0000016D	0000004C	00000010	R	.	.	.	.	.	B	T	.
MemoryBank_Z::VerifyMem(void)	__text	00201448	00000033	0000001C	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetNbFindAlloc(void *,void *)	__text	0020147C	000000DC	0000002C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::ShowMostNbMalloc(void)	__text	00201558	000001E7	0000404C	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z::MarkMem(ulong)	__text	00201740	0000009B	0000002C	00000005	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetUserSize(MemoryBlock_Z *)	__text	002017DE	0000004C	0000001C	00000008	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetCommentText(char *,MemoryBlock_Z *)	__text	0020182A	00000051	0000002C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::GetFindAlloc(long,char *,void *,void *)	__text	0020187C	0000013F	0000004C	00000014	R	.	.	.	.	.	B	T	.
MemoryBank_Z::FindAlloc(void *,void *)	__text	002019BC	00000064	0000023C	0000000C	R	.	.	.	.	.	B	T	.
MemoryBank_Z::ShowUnMarkedMem(void)	__text	00201A20	00000120	0000022C	00000004	R	.	.	.	.	.	B	T	.
*/

#include <MemoryBank_Z.h>

// This class is not fun... it has nothing to do with Mac WALL-E but it's crucial for console ports...
// Thanks to vtables this didn't get stripped out by the linker

U32 MemoryBank_Z::GetAllocatedMem() {
    return 0;
}

U32  MemoryBank_Z::GetNbFreeBlocks() {
    return 0;
}

MemoryBank_Z::MemoryBank_Z() {

}

MemoryBank_Z::~MemoryBank_Z() {

}

void MemoryBank_Z::SetBestBit(bool) {

}

U32 MemoryBank_Z::FindBucket(S32) {
    return 0;
}

Bool MemoryBank_Z::CheckBlock(MemoryBlock_Z *) {
    return 0;
}

Bool MemoryBank_Z::CheckBuckets() {
    return 0;
}

void MemoryBank_Z::SetFitLimits(U32,U32) {

}

U32 MemoryBank_Z::GetFreeMem() {
    return 0;
}

U32 MemoryBank_Z::GetLargestFreeBlock() {
    return 0;
}

U32 MemoryBank_Z::GetLargestFree() {
    return 0;
}

U32 MemoryBank_Z::FindFirstBlock(S32) {
    return 0;
}

U32 MemoryBank_Z::Dicho_RecEqual(MemoryBlock_Z **,U32,S32,S32) {
    return 0;
}

U32 MemoryBank_Z::GetInBucket(S32,MemoryBlock_Z *) {
    return 0;
}

void MemoryBank_Z::RemoveBlockFromBucket(S32,MemoryBlock_Z *) {

}

void MemoryBank_Z::RemoveBlock(MemoryBlock_Z *) {

}

Bool MemoryBank_Z::FindSomeBlock(MemoryBlock_Z *) {
    return 0;
}

bool MemoryBank_Z::TestIntegrity(MemoryBlock_Z *) {

}

U32 MemoryBank_Z::Dicho_RecAfter(MemoryBlock_Z **,U32,S32,S32) {
    return 0;
}

void MemoryBank_Z::AddBlockToBucket(S32,MemoryBlock_Z *) {

}

void MemoryBank_Z::AddBlock(MemoryBlock_Z *) {

}

void MemoryBank_Z::SplitToAllocAndFreeBlock(MemoryBlock_Z *,U32) {

}

void MemoryBank_Z::Init(void *,U32) {

}

U32 MemoryBank_Z::Dicho_RecBigger(MemoryBlock_Z **,U32,S32,S32) {
    return 0;
}

U32 MemoryBank_Z::FindBlock(S32,S32) {
    return 0;
}

U32 MemoryBank_Z::FindBestBlock(S32) {
    return 0;
}

U32 MemoryBank_Z::FindBlock(S32) {
    return 0;
}

void* MemoryBank_Z::Malloc(U32,const Char*,const Char*,U32,U32) {
    return 0;
}

void MemoryBank_Z::Extend() {

}

U32 MemoryBank_Z::MergeWithNextRealloc(void *,U32) {
    return 0;
}

void* MemoryBank_Z::Malloc_end(U32,U32,const Char*) {
    return 0;
}

void MemoryBank_Z::Free(void *) {

}

void* MemoryBank_Z::FullRealloc(void *,U32,const Char*) {
    return 0;
}

void* MemoryBank_Z::Realloc(void *,U32,const Char*) {
    return 0;
}

bool MemoryBank_Z::VerifyMem() {
    return false;
}

U32 MemoryBank_Z::GetNbFindAlloc(void *,void *) {
    return 0;
}

void MemoryBank_Z::ShowMostNbMalloc() {

}

void MemoryBank_Z::MarkMem(U32) {

}

U32 MemoryBank_Z::GetUserSize(MemoryBlock_Z *) {
    return 0;
}

void MemoryBank_Z::GetCommentText(char *,MemoryBlock_Z *) {

}

void* MemoryBank_Z::GetFindAlloc(S32,char *,void *,void *) {
    return 0;
}

void* MemoryBank_Z::FindAlloc(void *,void *) {
    return 0;
}

U32 MemoryBank_Z::ShowUnMarkedMem() {
    return 0;
}
