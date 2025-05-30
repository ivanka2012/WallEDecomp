#pragma once
#include <Types_Z.h>
#include <Memory_Z.h>

/**
 * dd offset __ZN15MemoryManager_ZD1Ev
__const:00395908                                         ; DATA XREF: MemoryManager_Z::MemoryManager_Z(void)+12↑o
__const:00395908                                         ; MemoryManager_Z::~MemoryManager_Z()+6↑o ...
__const:00395908                                         ; MemoryManager_Z::~MemoryManager_Z()
__const:0039590C                 dd offset __ZN15MemoryManager_ZD0Ev ; MemoryManager_Z::~MemoryManager_Z()
__const:00395910                 dd offset __ZN15MemoryManager_Z4InitEv ; MemoryManager_Z::Init(void)
__const:00395914                 dd offset __ZN15MemoryManager_Z4ShutEv ; MemoryManager_Z::Shut(void)
__const:00395918                 dd offset __ZN15MemoryManager_Z5AllocEmPKcS1_lm ; MemoryManager_Z::Alloc(ulong,char const*,char const*,long,ulong)
__const:0039591C                 dd offset __ZN15MemoryManager_Z8AllocEndEmPKcS1_lm ; MemoryManager_Z::AllocEnd(ulong,char const*,char const*,long,ulong)
__const:00395920                 dd offset __ZN15MemoryManager_Z7ReallocEPvmPKcS2_l ; MemoryManager_Z::Realloc(void *,ulong,char const*,char const*,long)
__const:00395924                 dd offset __ZN15MemoryManager_Z4FreeEPv ; MemoryManager_Z::Free(void *)
__const:00395928                 dd offset __ZN18Hi_MemoryManager_Z9FindAllocEPvS0_ ; Hi_MemoryManager_Z::FindAlloc(void *,void *)
__const:0039592C                 dd offset __ZN18Hi_MemoryManager_Z11FindAllocNbEPvS0_ ; Hi_MemoryManager_Z::FindAllocNb(void *,void *)
__const:00395930                 dd offset __ZN18Hi_MemoryManager_Z11FindAllocIDElPcPvS1_ ; Hi_MemoryManager_Z::FindAllocID(long,char *,void *,void *)
__const:00395934                 dd offset __ZN15MemoryManager_Z15AllocContiguousEmPKcS1_lm ; MemoryManager_Z::AllocContiguous(ulong,char const*,char const*,long,ulong)
__const:00395938                 dd offset __ZN15MemoryManager_Z14FreeContiguousEPv ; MemoryManager_Z::FreeContiguous(void *)
__const:0039593C                 dd offset __ZN18Hi_MemoryManager_Z6UpdateEf ; Hi_MemoryManager_Z::Update(float)
__const:00395940                 dd offset __ZN18Hi_MemoryManager_Z11PrintStatusEv ; Hi_MemoryManager_Z::PrintStatus(void)
__const:00395944                 dd offset sub_26920A    ; GetHeapSize
__const:00395948                 dd offset sub_269218    ; GetHeapBase
__const:0039594C                 dd offset sub_269224    ; GetNbAlloc
__const:00395950                 dd offset __ZN15MemoryManager_Z15GetAllocatedMemEv ; MemoryManager_Z::GetAllocatedMem(void)
__const:00395954                 dd offset __ZN15MemoryManager_Z10GetFreeMemEv ; MemoryManager_Z::GetFreeMem(void)
__const:00395958                 dd offset __ZN15MemoryManager_Z12GetFragmentsEv ; MemoryManager_Z::GetFragments(void)
__const:0039595C                 dd offset __ZN15MemoryManager_Z14GetLargestFreeEv ; MemoryManager_Z::GetLargestFree(void)
__const:00395960                 dd offset sub_269230    ; GetFrameNbAlloc
__const:00395964                 dd offset sub_26923C    ; GetMemUsed
__const:00395968                 dd offset sub_269264    ; GetMaxMemUsed
__const:0039596C                 dd offset __ZN15MemoryManager_Z7MarkMemEm ; MemoryManager_Z::MarkMem(ulong)
__const:00395970                 dd offset __ZN15MemoryManager_Z15ShowUnMarkedMemEv ; MemoryManager_Z::ShowUnMarkedMem(void)
__const:00395974                 dd offset __ZN15MemoryManager_Z16ShowMostNbMallocEv ; MemoryManager_Z::ShowMostNbMalloc(void)
__const:00395978                 dd offset __ZN15MemoryManager_Z12SetFitLimitsEmm ; MemoryManager_Z::SetFitLimits(ulong,ulong)
__const:0039597C                 dd offset __ZN15MemoryManager_Z10SetBestBitEb ; MemoryManager_Z::SetBestBit(bool)
__const:00395980                 dd offset __ZN15MemoryManager_Z9VerifyMemEv ; MemoryManager_Z::VerifyMem(void)
__const:00395984                 dd offset __ZN15MemoryManager_Z16SetCallStackPtrsEPml ; MemoryManager_Z::SetCallStackPtrs(ulong *,long)
 */

/**
 * I think that the following functions/classes were declared in LibMAC 
 */

class MemoryManager_Z : public Hi_MemoryManager_Z{
public:
    MemoryManager_Z();
    ~MemoryManager_Z();

    void Init();
    void Shut();

    /**
     * @brief Allocate a `size` memory block with `align` alignment. 
     * Returns null on failure.
     * 
     * First verified to match: 2024-03-22 18:29:51
     * 
     * @param size 
     * @param comment 
     * @param filename Which file is this being allocated?
     * @param line What line of the file exactly?
     * @param align 
     * @return void* 
     */
    void* Alloc(U32 size, const Char* comment, const Char* filename, S32 line, U32 align);

    void* AllocEnd(U32 size, const Char* comment, const Char* filename, S32 line, U32 align);

    /**
     * @brief Reallocate a memory block to `size`.
     * Returns null on failure.
     * 
     * First verified to match: 2024-03-22 22:43:40
     * 
     * @param ptr 
     * @param size 
     * @param comment 
     * @param filename 
     * @param line 
     * @return void* 
     */
    void* Realloc(void* ptr, U32 size, const Char* comment, const Char* filename, S32 line);

    /**
     * @brief Free a memory block allocated by MemoryManager_Z. Works like C `free`.
     * 
     * First verified to match: 2024-03-22 22:42:53
     * 
     * @param ptr 
     */
    void Free(void* ptr);

    void* AllocContiguous(U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line, U32 i_Align);
    void FreeContiguous(void* i_Ptr);

    U32 GetAllocatedMem();
    U32 GetFreeMem();
    U32 GetFragments();
    U32 GetLargestFree();

    void MarkMem(U32 a1);
    U32 ShowUnMarkedMem();
    void ShowMostNbMalloc();
    void SetFitLimits(U32 low, U32 high);
    void SetBestBit(bool bit);
    bool VerifyMem();
    void SetCallStackPtrs(U32* a1, S32 a2);
};

extern MemoryManager_Z MemManager;