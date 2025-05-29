/*
VolatileMgr_Z::Minimize(void)	__text	000E1D84	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
VolatileMgr_Z::AddIndex(long &,int)	__text	000E1D8A	0000004D	00000010	0000000C	R	.	.	.	.	.	B	T	.
VolatileMgr_Z::RemoveIndex(long &,int)	__text	000E1DD8	0000006D	00000010	0000000C	R	.	.	.	.	.	B	T	.
VolatileMgr_Z::SetState(int,long)	__text	000E1E46	0000009E	0000003C	0000000C	R	.	.	.	.	.	B	T	.
VolatileMgr_Z::FreeVolatileBlock_Z(ulong)	__text	000E1EE4	00000076	0000002C	00000008	R	.	.	.	.	.	B	T	.
VolatileMgr_Z::UpdateVolatileBlocks(float)	__text	000E1F5C	0000008F	0000002C	00000008	R	.	.	.	.	.	B	T	.
VolatileMgr_Z::VolatileMgr_Z(void)	__text	000E1FEE	00000090	0000001C	00000004	R	.	.	.	.	.	B	T	.
*/

#include <VolatileMgr_Z.h>

void VolatileMgr_Z::Minimize() {
    return;
}

void VolatileMgr_Z::AddIndex(S32& block, int offset){
    VolatileBlock& l_VolBlock = m_VolatileBlockArray[offset];
    l_VolBlock.m_NextBlockToUpdate = block;
    l_VolBlock.m_PrevBlockToUpdate = -1;
    if (block >= 0) {
        m_VolatileBlockArray[block].m_PrevBlockToUpdate = offset;
    }
    block = offset;
}

void VolatileMgr_Z::RemoveIndex(S32& block, int offset){
    S16 l_PrevBlockToUpdate;
    S16 l_NextBlockToUpdate;
    VolatileBlock& l_VolBlock = m_VolatileBlockArray[offset];
    l_NextBlockToUpdate = l_VolBlock.m_NextBlockToUpdate;
    if (l_NextBlockToUpdate >= 0) {
        m_VolatileBlockArray[l_NextBlockToUpdate].m_PrevBlockToUpdate = l_VolBlock.m_PrevBlockToUpdate;
    }
    l_PrevBlockToUpdate = l_VolBlock.m_PrevBlockToUpdate;
    if (l_PrevBlockToUpdate >= 0) {
        m_VolatileBlockArray[l_PrevBlockToUpdate].m_NextBlockToUpdate = l_VolBlock.m_NextBlockToUpdate;
    }
    else {
        block = l_VolBlock.m_NextBlockToUpdate;

    }
}

void VolatileMgr_Z::SetState(int i_ArrayOffset, S32 i_State) {
    VolatileBlock& l_VolBlock = m_VolatileBlockArray[i_ArrayOffset];
    if (l_VolBlock.m_State != i_State) {
        switch (l_VolBlock.m_State) {
            case 0: {
                RemoveIndex(m_FirstFreeBlock, i_ArrayOffset);
                break;
            }
            case 1: {
                RemoveIndex(m_FirstAllocatedBlock, i_ArrayOffset);
                break;
            }
        }
        
        l_VolBlock.m_State = i_State;
        
        switch (l_VolBlock.m_State) {
            case 0: {
                AddIndex(m_FirstFreeBlock, i_ArrayOffset);
                break;
            }
            case 1: {
                AddIndex(m_FirstAllocatedBlock, i_ArrayOffset);
                break;
            }
        }
    }
}
VolatileMgr_Z::VolatileMgr_Z() {
    m_FirstFreeBlock = -1;
    m_FirstAllocatedBlock = -1;
    for (int i = 0; i < 0x500; i++) {
        S32 l_BlockId = m_VolatileBlockArray.Add();
        VolatileBlock& l_VolBlock = m_VolatileBlockArray[l_BlockId];
        l_VolBlock.m_Pointer = NULL;
        l_VolBlock.m_Key = 1;
        l_VolBlock.m_State = -1;
        SetState(l_BlockId,0);
    }
}


void VolatileMgr_Z::FreeVolatileBlock_Z(U32 i_BlockIdx) {
    if (i_BlockIdx < m_VolatileBlockArray.GetSize()) {
        int l_BlockIdx = i_BlockIdx;
        VolatileBlock& l_VolBlock = m_VolatileBlockArray[l_BlockIdx];
        if (l_VolBlock.m_Pointer) 
        {
            Free_Z(l_VolBlock.m_Pointer);
            l_VolBlock.m_Pointer = NULL;
        }
        l_VolBlock.m_Zero = 0;
        l_VolBlock.m_Key++;
        l_VolBlock.m_Key = l_VolBlock.m_Key & 0xFFFF;
        if (!l_VolBlock.m_Key) {
            l_VolBlock.m_Key += 1;
        }
        SetState(i_BlockIdx, 0);

    }
}