/*
BitArray_Z::ClearBitRange(long,long)	__text	0003788E	00000092	00000014	0000000C	R	.	.	.	.	.	B	T	.
BitArray_Z::ClearAllBits(void)	__text	00037920	00000022	00000004	00000004	R	.	.	.	.	.	B	T	.
BitArray_Z::FindFirstBit(bool,long)	__text	00037942	00000147	0000001C	0000000C	R	.	.	.	.	.	B	T	.
BitArray_Z::CountSetBits(void)	__text	00037A8C	0000004C	00000014	00000004	R	.	.	.	.	.	B	T	.
BitArray_Z::FindLastBit(bool,long)	__text	00037AD8	00000072	00000018	0000000C	R	.	.	.	.	.	B	T	.
BitArray_Z::SetAllBits(void)	__text	00037B4A	00000022	00000004	00000004	R	.	.	.	.	.	B	T	.
BitArray_Z::BitArray_Z(void)	__text	00037B6E	00000021	00000004	00000004	R	.	.	.	.	.	B	T	.
BitArray_Z::~BitArray_Z()	__text	00037B92	00000026	0000001C	00000004	R	.	.	.	.	.	B	T	.
BitArray_Z::BitArray_Z(long)	__text	00037BB8	0000005C	0000001C	00000008	R	.	.	.	.	.	B	T	.
*/

#include <BitArray_Z.h>

BitArray_Z::BitArray_Z() {
    bitsSize = 0;
}

BitArray_Z::~BitArray_Z() {
}

BitArray_Z::BitArray_Z(S32 i_Size) {
    bitsSize = 0;
    SetSize(i_Size);
}

void BitArray_Z::ClearBitRange(S32 i_StartIndex, S32 i_EndIndex) {
    S32 l_Start = i_StartIndex >> 5;
    S32 l_BitCpt = i_StartIndex & 0x1F;
    U32 l_Bit = (1 << l_BitCpt) - 1;

    S32 l_End = i_EndIndex >> 5;
    U32 l_BitCptEnd = 1 << (i_EndIndex & 0x1F);
    U32 l_BitEnd = -(2 * l_BitCptEnd);

    if (l_Start == l_End) {
        bits[l_Start] &= l_Bit | l_BitEnd;
        return;
    }

    bits[l_Start] &= l_Bit;

    if (l_Start < l_End) {
        l_Start++;
        for (; l_Start < l_End; bits[l_Start] = 0, l_Start++);
    }
    bits[l_End] &= l_BitEnd;
}

void BitArray_Z::SetAllBits() {
    U32* l_Bits = bits.GetArrayPtr();
    S32 l_Size = bits.GetSize();
    while (l_Size--) {
        *l_Bits++ = 0xFFFFFFFF;
    }
}

void BitArray_Z::ClearAllBits() {
    U32* l_Bits = bits.GetArrayPtr();
    S32 l_Size = bits.GetSize();
    while (l_Size--) {
        *l_Bits++ = 0;
    }
}

S32 BitArray_Z::FindFirstBit(bool i_State, S32 i_firstBitToCheck) const {
    if (i_firstBitToCheck >= bitsSize) {
        return -1;
    }
    S32 l_Index;
    S32 l_CurBits;
    S32 l_BitIndex = i_firstBitToCheck >> 5;
    S32 l_BitCpt = i_firstBitToCheck & 0x1F;
    S32 l_Size = bits.GetSize();
    if (l_BitCpt) {
        U32 l_Bit = 1 << l_BitCpt;
        l_CurBits = bits[l_BitIndex];
        if (!i_State)
            l_CurBits = ~l_CurBits;
        l_CurBits &= ~(l_Bit - 1);
        if (l_CurBits) {
            S32 x = ((l_CurBits) & (-l_CurBits));
            S32 a = 0;
            if (x & 0xFFFF0000) a += 16;
            if (x & 0xFF00FF00) a += 8;
            if (x & 0xF0F0F0F0) a += 4;
            if (x & 0xCCCCCCCC) a += 2;
            if (x & 0xAAAAAAAA) a += 1;
            l_Index = (l_BitIndex << 5) + a;
            if (l_Index >= bitsSize) {
                return -1;
            }
            return l_Index;
        }
        l_BitIndex++;
    }

    if (i_State) {
        for (; (l_BitIndex < l_Size) && (!(l_CurBits = bits[l_BitIndex])); l_BitIndex++);
        if (l_BitIndex < l_Size) {
            S32 x = ((l_CurBits) & (-l_CurBits));
            S32 a = 0;
            if (x & 0xFFFF0000) a += 16;
            if (x & 0xFF00FF00) a += 8;
            if (x & 0xF0F0F0F0) a += 4;
            if (x & 0xCCCCCCCC) a += 2;
            if (x & 0xAAAAAAAA) a += 1;
            l_Index = (l_BitIndex << 5) + a;
            if (l_Index >= bitsSize) {
                return -1;
            }
            return l_Index;
        }
    }
    else {
        for (; (l_BitIndex < l_Size) && (!(l_CurBits = ~bits[l_BitIndex])); l_BitIndex++);
        if (l_BitIndex < l_Size) {
            S32 x = ((l_CurBits) & (-l_CurBits));
            S32 a = 0;
            if (x & 0xFFFF0000) a += 16;
            if (x & 0xFF00FF00) a += 8;
            if (x & 0xF0F0F0F0) a += 4;
            if (x & 0xCCCCCCCC) a += 2;
            if (x & 0xAAAAAAAA) a += 1;
            l_Index = (l_BitIndex << 5) + a;
            if (l_Index >= bitsSize) {
                return -1;
            }
            return l_Index;
        }
    }
    return -1;
}

S32 BitArray_Z::FindLastBit(bool i_State, S32 i_firstBitToCheck) const {
    while (i_firstBitToCheck >= 0) {
        if (i_State) {
            if (GetBit(i_firstBitToCheck)) {
                break;
            }
        }
        else {
            if (!GetBit(i_firstBitToCheck)) {
                break;
            }
        }
        i_firstBitToCheck--;
    }
    return i_firstBitToCheck;
}
