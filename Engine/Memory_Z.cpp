/*
Hi_MemoryManager_Z::Init(void)	__text	00062314	00000057	0000001C	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::Shut(void)	__text	0006236C	00000071	0000002C	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::Hi_MemoryManager_Z(void)	__text	000623DE	0000002F	0000001C	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::VerifyMem(void)	__text	0006240E	00000019	0000001C	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::Alloc(uS32,char const*,char const*,S32,uS32)	__text	00062428	00000046	0000002C	00000018	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::AllocEnd(uS32,char const*,char const*,S32,uS32)	__text	0006246E	00000038	0000001C	00000018	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::FindAlloc(void *,void *)	__text	000624A6	00000012	00000004	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::FindAllocNb(void *,void *)	__text	000624B8	00000012	00000004	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::FindAllocID(S32,char *,void *,void *)	__text	000624CA	00000012	00000004	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::Realloc(void *,uS32,char const*,char const*,S32)	__text	000624DC	00000034	0000001C	00000010	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::Free(void *)	__text	00062510	0000002A	0000001C	00000008	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::Update(float)	__text	0006253A	0000005B	0000001C	00000008	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::PrintStatus(void)	__text	00062596	0000004A	0000001C	00000004	R	.	.	.	.	.	B	T	.
MemoryGraphColor(void)	__text	000625E0	0000001A	00000004		R	.	.	.	.	.	B	T	.
Z_Verify(void)	__text	000625FA	00000018	0000001C		R	.	.	.	.	.	B	T	.
Z_Alloc(uS32,char const*,char const*,S32,uS32)	__text	00062612	00000038	0000002C	00000014	R	.	.	.	.	.	B	T	.
operator new(uS32,char const*,char const*,S32)	__text	0006264A	00000039	0000002C	00000010	R	.	.	.	.	.	B	T	.
operator new[](uS32,char const*,char const*,S32)	__text	00062684	00000039	0000002C	00000010	R	.	.	.	.	.	B	T	.
operator new(uS32)	__text	000626BE	0000003C	0000002C	00000004	R	.	.	.	.	.	B	T	.
Z_Free(void *)	__text	000626FA	0000001C	0000001C	00000004	R	.	.	.	.	.	B	T	.
operator delete[](void *,char const*,char const*,S32)	__text	00062716	00000017	00000004	00000008	R	.	.	.	.	.	B	T	.
operator delete(void *,char const*,char const*,S32)	__text	0006272E	00000017	00000004	00000008	R	.	.	.	.	.	B	T	.
operator delete[](void *)	__text	00062746	0000001C	0000001C	00000004	R	.	.	.	.	.	B	T	.
operator delete(void *)	__text	00062762	0000001C	0000001C	00000004	R	.	.	.	.	.	B	T	.
Z_AllocEnd(uS32,char const*,char const*,S32,uS32)	__text	0006277E	00000038	0000002C	00000014	R	.	.	.	.	.	B	T	.
Z_AllocContiguous(uS32,char const*,char const*,S32,uS32)	__text	000627B6	00000038	0000002C	00000014	R	.	.	.	.	.	B	T	.
Z_Realloc(void *,uS32,char const*,char const*,S32)	__text	000627EE	00000038	0000002C	00000014	R	.	.	.	.	.	B	T	.
Z_FreeContiguous(void *)	__text	00062826	0000001C	0000001C	00000004	R	.	.	.	.	.	B	T	.
Z_SetBestBit(bool)	__text	00062842	0000001D	0000001C	00000001	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::~Hi_MemoryManager_Z()	__text	00062860	00000018	00000004	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::~Hi_MemoryManager_Z()	__text	00062878	00000018	00000004	00000004	R	.	.	.	.	.	B	T	.
Hi_MemoryManager_Z::~Hi_MemoryManager_Z()	__text	00062890	00000032	0000001C	00000004	R	.	.	.	.	.	B	T	.
*/

#include <Memory_Z.h>
#include <MemoryManager_Z.h>
#include <Assert_Z.h>
#include <Main_Z.h>

void Hi_MemoryManager_Z::Init() {
    /*m_FreeMemCached = (U32)m_HeapEnd - (U32)m_HeapBase;
    m_MemoryBank.Init(m_HeapBase, m_FreeMemCached);
    m_NbAlloc = 0;
    m_FrameNbAlloc = 0;
    m_FreeMemCached = m_MemoryBank.GetFreeMem();
    m_MaxMemUsed = 0;
    m_AllocTimer = 0.0f;*/
}

void Hi_MemoryManager_Z::Shut() {
    MarkMem(0);
    S32 NbLeak = ShowUnMarkedMem();
    if (NbLeak != 1) {
        ShowMostNbMalloc();
    }
    ASSERTC_Z(NbLeak == 1, "Leaks Found");
}

Hi_MemoryManager_Z::Hi_MemoryManager_Z() {
    m_HeapEnd = NULL;
    m_HeapBase = NULL;
}

Hi_MemoryManager_Z::~Hi_MemoryManager_Z() {

}

void Hi_MemoryManager_Z::VerifyMem() {
    // m_MemoryBank.VerifyMem();
}

void* Hi_MemoryManager_Z::Alloc(U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line, U32 i_Align) {
    // void* l_Mem = m_MemoryBank.Malloc(i_Size, i_Comment, i_File, i_Line, i_Align);
    // m_NbAlloc++;
    // m_FrameNbAlloc++;
    // return l_Mem;
}

void* Hi_MemoryManager_Z::AllocEnd(U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line, U32 i_Align) {
    // void* l_Mem = m_MemoryBank.Malloc_end(i_Size, i_Align, i_Comment);
    // m_NbAlloc++;
    // m_FrameNbAlloc++;
    // return l_Mem;
}

void* Hi_MemoryManager_Z::FindAlloc(void* i_RangeStart, void* i_RangeEnd) {
    //return m_MemoryBank.FindAlloc(i_RangeStart, i_RangeEnd);
}

U32 Hi_MemoryManager_Z::FindAllocNb(void* i_RangeStart, void* i_RangeEnd) {
    //return m_MemoryBank.GetNbFindAlloc(i_RangeStart, i_RangeEnd);
}

void* Hi_MemoryManager_Z::FindAllocID(S32 i_AllocID, Char* i_ResultDescription, void* i_RangeStart, void* i_RangeEnd) {
    //return m_MemoryBank.GetFindAlloc(i_AllocID, i_ResultDescription, i_RangeStart, i_RangeEnd);
}

void* Hi_MemoryManager_Z::Realloc(void* i_Ptr, U32 i_Size, const Char* i_Comment, const Char* i_File, S32 i_Line) {
    // void* l_Mem = m_MemoryBank.Realloc(i_Ptr, i_Size, i_Comment);
    // m_FrameNbAlloc++;
    // return l_Mem;
}

void Hi_MemoryManager_Z::Free(void* i_Ptr) {
    if (!i_Ptr) return;
    //m_MemoryBank.Free(i_Ptr);
    m_NbAlloc--;
}

U32 Hi_MemoryManager_Z::Update(Float i_DeltaTime) {
    U32 l_DidReset;

    m_AllocTimer = m_AllocTimer + i_DeltaTime;
    if (m_AllocTimer > 2.0f) {
        if (m_MaxMemUsed < GetMemUsed()) {
            m_MaxMemUsed = GetMemUsed();
        }
        l_DidReset = 1;
        m_AllocTimer = 0.0f;
        m_FrameNbAlloc = 0;
    }
    else {
        l_DidReset = 0;
    }
    return l_DidReset;
}

void Hi_MemoryManager_Z::PrintStatus() {
    GetMemUsed();
    GetMemUsed();
    GetFreeMem();
    GetFreeMem();
    GetHeapSize();
    GetHeapSize();
    // m_MemoryBank.ShowMostNbMalloc();
}


U32 MemoryGraphColor() {
    S32 l_NumParam = gData.Cons->GetNbParam();
    if (l_NumParam >= 2) {
        return TRUE;
    }
    return FALSE;
}

void Z_Verify() {
    MemManager.VerifyMem();
}


void Z_Free(void* ptr){
    MemManager.Free(ptr);
}
void Z_FreeContiguous(void* i_Ptr) {
    MemManager.FreeContiguous(i_Ptr);
}

void* Z_Alloc(U32 size, const Char* comment, const Char* filename, S32 line, U32 align){
    return MemManager.Alloc(size, comment, filename, line, align);
}
void* Z_Alloc(U32 size, const Char* comment, const Char* filename, S32 line, U32 align){
    return MemManager.AllocContiguous(size, comment, filename, line, align);
}

void* Z_AllocEnd(U32 size, const Char* comment, const Char* filename, S32 line, U32 align){
    return MemManager.AllocEnd(size, comment, filename, line, align);
}

void* Z_Realloc(void* ptr, U32 size, const Char* comment, const Char* filename, S32 line){
    return MemManager.Realloc(ptr, size, comment, filename, line);
}

void* operator new(U32 size){
    return MemManager.Alloc(size, "Anonymous New", "No File", 0, 4 /*_ALLOCDEFAULTALIGN*/);
}

void* operator new(U32 size, const Char* comment, const Char* filename, S32 line){
    return MemManager.Alloc(size, comment, filename, line, 4);
}

void* operator new[](U32 size, const Char* comment, const Char* filename, S32 line){
    return MemManager.Alloc(size, comment, filename, line, 4);
}

void operator delete(void* ptr){
    MemManager.Free(ptr);
}

void operator delete(void* ptr, const Char* comment, const Char* filename, S32 line){
    MemManager.Free(ptr);
}

void operator delete[](void* ptr){
    MemManager.Free(ptr);
}

void operator delete[](void* ptr, const Char* comment, const Char* filename, S32 line){
    MemManager.Free(ptr);
}