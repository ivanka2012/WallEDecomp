#pragma once

/*
GetAllocatedMem();	__text	001FFBBC	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
GetNbFreeBlocks();	__text	001FFBCA	0000001D	00000004	00000004	R	.	.	.	.	.	B	T	.
MemoryBank_Z();	__text	001FFBEA	0000002A	00000004	00000004	R	.	.	.	.	.	B	T	.
~MemoryBank_Z();	__text	001FFC16	0000002A	00000004	00000004	R	.	.	.	.	.	B	T	.
SetBestBit(bool);	__text	001FFC42	00000051	00000018	00000005	R	.	.	.	.	.	B	T	.
FindBucket(S32);	__text	001FFC96	0000006C	00000004	00000008	R	.	.	.	.	.	B	T	.
CheckBlock(MemoryBlock_Z *);	__text	001FFD02	000000A9	0000001C	00000008	R	.	.	.	.	.	B	T	.
CheckBuckets();	__text	001FFDAC	00000065	0000003C	00000004	R	.	.	.	.	.	B	T	.
SetFitLimits(U32,U32);	__text	001FFE14	00000089	0000003C	0000000C	R	.	.	.	.	.	B	T	.
GetFreeMem();	__text	001FFE9E	0000007D	0000003C	00000004	R	.	.	.	.	.	B	T	.
GetLargestFreeBlock();	__text	001FFF1C	00000084	0000003C	00000004	R	.	.	.	.	.	B	T	.
GetLargestFree();	__text	001FFFA0	00000009	00000004	00000004	R	.	.	.	.	.	B	T	.
FindFirstBlock(S32);	__text	001FFFAA	000000C5	0000003C	00000008	R	.	.	.	.	.	B	T	.
Dicho_RecEqual(MemoryBlock_Z **,U32,S32,S32);	__text	00200070	000000DB	0000002C	00000014	R	.	.	.	.	.	B	T	.
GetInBucket(S32,MemoryBlock_Z *);	__text	0020014C	000000C0	0000003C	0000000C	R	.	.	.	.	.	B	T	.
RemoveBlockFromBucket(S32,MemoryBlock_Z *);	__text	0020020E	00000072	0000002C	0000000C	R	.	.	.	.	.	B	T	.
RemoveBlock(MemoryBlock_Z *);	__text	00200280	00000042	0000001C	00000008	R	.	.	.	.	.	B	T	.
FindSomeBlock(MemoryBlock_Z *);	__text	002002C2	0000004B	0000001C	00000008	R	.	.	.	.	.	B	T	.
TestIntegrity(MemoryBlock_Z *);	__text	0020030E	00000138	0000002C	00000008	R	.	.	.	.	.	B	T	.
Dicho_RecAfter(MemoryBlock_Z **,U32,S32,S32);	__text	00200446	0000017C	0000002C	00000014	R	.	.	.	.	.	B	T	.
AddBlockToBucket(S32,MemoryBlock_Z *);	__text	002005C2	000000C2	0000004C	0000000C	R	.	.	.	.	.	B	T	.
AddBlock(MemoryBlock_Z *);	__text	00200684	00000042	0000001C	00000008	R	.	.	.	.	.	B	T	.
SplitToAllocAndFreeBlock(MemoryBlock_Z *,U32);	__text	002006C6	00000110	0000003C	0000000C	R	.	.	.	.	.	B	T	.
Init(void *,U32);	__text	002007D6	000000D2	0000001C	0000000C	R	.	.	.	.	.	B	T	.
Dicho_RecBigger(MemoryBlock_Z **,U32,S32,S32);	__text	002008A8	0000012F	0000002C	00000014	R	.	.	.	.	.	B	T	.
FindBlock(S32,S32);	__text	002009D8	0000017D	0000005C	0000000C	R	.	.	.	.	.	B	T	.
FindBestBlock(S32);	__text	00200B56	00000065	0000002C	00000008	R	.	.	.	.	.	B	T	.
FindBlock(S32);	__text	00200BBC	0000003A	0000001C	00000008	R	.	.	.	.	.	B	T	.
Malloc(U32,const Char*,const Char*,U32,U32);	__text	00200BF6	0000010E	0000004C	00000018	R	.	.	.	.	.	B	T	.
Extend();	__text	00200D04	0000011A	0000005C	00000004	R	.	.	.	.	.	B	T	.
MergeWithNextRealloc(void *,U32);	__text	00200E1E	000000B5	0000003C	0000000C	R	.	.	.	.	.	B	T	.
Malloc_end(U32,U32,const Char*);	__text	00200ED4	000001B5	0000004C	0000000C	R	.	.	.	.	.	B	T	.
Free(void *);	__text	0020108A	00000166	0000003C	00000008	R	.	.	.	.	.	B	T	.
FullRealloc(void *,U32,const Char*);	__text	002011F0	000000E9	0000004C	00000010	R	.	.	.	.	.	B	T	.
Realloc(void *,U32,const Char*);	__text	002012DA	0000016D	0000004C	00000010	R	.	.	.	.	.	B	T	.
VerifyMem();	__text	00201448	00000033	0000001C	00000004	R	.	.	.	.	.	B	T	.
GetNbFindAlloc(void *,void *);	__text	0020147C	000000DC	0000002C	0000000C	R	.	.	.	.	.	B	T	.
ShowMostNbMalloc();	__text	00201558	000001E7	0000404C	00000004	R	.	.	.	.	.	B	T	.
MarkMem(U32);	__text	00201740	0000009B	0000002C	00000005	R	.	.	.	.	.	B	T	.
GetUserSize(MemoryBlock_Z *);	__text	002017DE	0000004C	0000001C	00000008	R	.	.	.	.	.	B	T	.
GetCommentText(char *,MemoryBlock_Z *);	__text	0020182A	00000051	0000002C	0000000C	R	.	.	.	.	.	B	T	.
GetFindAlloc(S32,char *,void *,void *);	__text	0020187C	0000013F	0000004C	00000014	R	.	.	.	.	.	B	T	.
FindAlloc(void *,void *);	__text	002019BC	00000064	0000023C	0000000C	R	.	.	.	.	.	B	T	.
ShowUnMarkedMem();	__text	00201A20	00000120	0000022C	00000004	R	.	.	.	.	.	B	T	.
*/

#pragma once
#include <Types_Z.h>

class MemoryBlock_Z{
public:

};

class MemoryBank_Z {
    //TODO These have official names.
    void* HeapBase; //+0x00 0
    void* HeapEnd; //+0x04 4
public:
    void* GetHeapBase() const {
        return HeapBase;
    }

    void* GetHeapEnd() const{
        return HeapEnd;
    }

    U32 GetAllocatedMem();
    U32 GetNbFreeBlocks();
    MemoryBank_Z();
    ~MemoryBank_Z();
    void SetBestBit(bool);
    U32 FindBucket(S32);
    Bool CheckBlock(MemoryBlock_Z *);
    Bool CheckBuckets();
    void SetFitLimits(U32,U32);
    U32 GetFreeMem();
    U32 GetLargestFreeBlock();
    U32 GetLargestFree();
    U32 FindFirstBlock(S32);
    U32 Dicho_RecEqual(MemoryBlock_Z **,U32,S32,S32);
    U32 GetInBucket(S32,MemoryBlock_Z *);
    void RemoveBlockFromBucket(S32,MemoryBlock_Z *);
    void RemoveBlock(MemoryBlock_Z *);
    Bool FindSomeBlock(MemoryBlock_Z *);
    bool TestIntegrity(MemoryBlock_Z *);
    U32 Dicho_RecAfter(MemoryBlock_Z **,U32,S32,S32);
    void AddBlockToBucket(S32,MemoryBlock_Z *);
    void AddBlock(MemoryBlock_Z *);
    void SplitToAllocAndFreeBlock(MemoryBlock_Z *,U32);
    void Init(void *,U32);
    U32 Dicho_RecBigger(MemoryBlock_Z **,U32,S32,S32);
    U32 FindBlock(S32,S32);
    U32 FindBestBlock(S32);
    U32 FindBlock(S32);
    void* Malloc(U32,const Char*,const Char*,U32,U32);
    void Extend();
    U32 MergeWithNextRealloc(void *,U32);
    void* Malloc_end(U32,U32,const Char*);
    void Free(void *);
    void* FullRealloc(void *,U32,const Char*);
    void* Realloc(void *,U32,const Char*);
    bool VerifyMem();
    U32 GetNbFindAlloc(void *,void *);
    void ShowMostNbMalloc();
    void MarkMem(U32);
    U32 GetUserSize(MemoryBlock_Z *);
    void GetCommentText(char *,MemoryBlock_Z *);
    void* GetFindAlloc(S32,char *,void *,void *);
    void* FindAlloc(void *,void *);
    U32 ShowUnMarkedMem();
};