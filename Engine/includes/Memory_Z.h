#ifndef MEMORY_Z_H
#define MEMORY_Z_H

#include <Types_Z.h>
#include <string.h>
#include <MemoryBank_Z.h>

class Hi_MemoryManager_Z {
public:
    void* m_HeapBase; //+0x4
    void* m_HeapEnd; //+0x8
    U32 m_FreeMemCached; //+0xC
    U32 m_MaxMemUsed; //+0x10
    U8 m_Pad_0x10[0x4]; //+0x14
    U32 m_NbAlloc; //+0x18
    U32 m_FrameNbAlloc; //+0x1C
    Float m_AllocTimer; //+0x20 32
    // TODO
    MemoryBank_Z m_MemoryBank; //+0x24 36

    Hi_MemoryManager_Z();
    virtual ~Hi_MemoryManager_Z();

    virtual void Init();
    virtual void Shut();
    virtual void* Alloc(U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line, U32 i_Align);
    virtual void* AllocEnd(U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line, U32 i_Align);
    virtual void* Realloc(void* i_Ptr, U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line);
    virtual void Free(void* i_Ptr);
    virtual void* FindAlloc(void* i_RangeStart, void* i_RangeEnd);
    virtual U32 FindAllocNb(void* i_RangeStart, void* i_RangeEnd);
    virtual void* FindAllocID(S32 i_AllocId, Char* i_ResultDescription, void* i_RangeStart, void* i_RangeEnd);
    virtual void* AllocContiguous(U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line, U32 i_Align) {
        return Alloc(i_Size, i_Comment, i_File, i_Line, i_Align);
    }
    virtual void FreeContiguous(void* i_Ptr) {
        Free(i_Ptr);
    }
    virtual U32 Update(Float i_DeltaTime);
    virtual void PrintStatus();
    virtual U32 GetHeapSize() {
        return (U32)m_MemoryBank.GetHeapEnd() - (U32)m_MemoryBank.GetHeapBase();
    }
    virtual void* GetHeapBase() {
        return m_MemoryBank.GetHeapBase();
    }
    virtual U32 GetNbAlloc() {
        return m_NbAlloc;
    }
    virtual U32 GetAllocatedMem() {
        return m_MemoryBank.GetAllocatedMem();
    }
    virtual U32 GetFreeMem() {
        m_FreeMemCached = m_MemoryBank.GetFreeMem();
        return m_FreeMemCached;
    }
    virtual U32 GetFragments() {
        return m_MemoryBank.GetNbFreeBlocks();
    }
    virtual U32 GetLargestFree() {
        return m_MemoryBank.GetLargestFree();
    }
    virtual U32 GetFrameNbAlloc() {
        return m_FrameNbAlloc;
    }
    virtual U32 GetMemUsed() {
        return GetHeapSize() - GetFreeMem();
    }
    virtual U32 GetMaxMemUsed() {
        return m_MaxMemUsed;
    }
    virtual void MarkMem(U32 a1) {
        m_MemoryBank.MarkMem(a1);
    }
    virtual U32 ShowUnMarkedMem() {
        return m_MemoryBank.ShowUnMarkedMem();
    }
    virtual void ShowMostNbMalloc() {
        m_MemoryBank.ShowMostNbMalloc();
    }
    
    virtual void SetFitLimits(U32 low, U32 high) {
        m_MemoryBank.SetFitLimits(low, high);
    }
    
    virtual void SetBestBit(bool bit) {
        m_MemoryBank.SetBestBit(bit);
    }
    virtual bool VerifyMem();
    virtual void SetCallStackPtrs(U32* a1, S32 a2){
        memset(a1, 0, 32);
    }
};

//Placement new
//Implied to be an inline function
inline void* operator new(U32 size, void* ptr) {return ptr;}

/**
 * @brief C++ allocate a `size` memory block. Used in pair with `New_Z`
 * 
 * First verified to match: 2024-03-22 18:28:24
 * 
 * @param size 
 * @param comment 
 * @param filename 
 * @param line 
 * @return void* 
 */
void* operator new(U32 size);

void* operator new(U32 size, const Char* comment, const Char* filename, S32 line);

void* operator new[](U32 size, const Char* comment, const Char* filename, S32 line);

void operator delete(void* ptr);

void operator delete(void* ptr, const Char* comment, const Char* filename, S32 line);

void operator delete[](void* ptr);

void operator delete[](void* ptr, const Char* comment, const Char* filename, S32 line);

U32 MemoryGraphColor();
bool Z_Verify();

void Z_SetBestBit(bool bit);

/**
 * @brief Zouna's free function
 * 
 * First verified to match: 2024-03-22 22:44:26
 * 
 * @param ptr 
 */
void Z_Free(void* ptr);
/**
 * @brief Zouna's alloc function
 * 
 * First verified to match: 2024-03-22 22:44:39
 * 
 * @param ptr 
 */
void* Z_Alloc(U32 size, const Char* comment, const Char* filename, S32 line, U32 align);

void* Z_AllocEnd(U32 size, const Char* comment, const Char* filename, S32 line, U32 align);

/**
 * @brief Zouna's realloc function
 * 
 * First verified to match:  2024-03-22 22:44:41
 * 
 * @param ptr 
 */
void* Z_Realloc(void* ptr, U32 size, const Char* comment, const Char* filename, S32 line);

#define Alloc_Z(size) Z_Alloc(size, "Anonymous Alloc", __FILE__, __LINE__, 4)
#define AllocC_Z(size, comment) Z_Alloc(size, comment, __FILE__, __LINE__, 4)
#define Realloc_Z(ptr, size) Z_Realloc(ptr, size, "Anonymous Alloc", __FILE__, __LINE__)
#define Free_Z(ptr) Z_Free(ptr)

#define New_Z new ("Anonymous New", __FILE__, __LINE__)
#define NewC_Z(comment) new(comment, __FILE__, __LINE__)
#define Delete_Z delete

#endif