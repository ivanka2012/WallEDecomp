#pragma once
#include <DynArray_Z.h>

class BitArray_Z{
    U32DA bits;
    S32 bitsSize;
public:
    BitArray_Z();
    BitArray_Z(S32 i_Size);
    // BitArray_Z(const BitArray_Z& i_Src);
    ~BitArray_Z();
    // BitArray_Z& operator=(const BitArray_Z& i_Src);
    
    void SetAllBits();
    void ClearAllBits();
    void ClearBitRange(S32 i_StartIndex, S32 i_EndIndex);
    S32 FindFirstBit(bool i_State = TRUE, S32 i_firstBitToCheck = 0) const;
    S32 FindLastBit(bool i_State, S32 i_firstBitToCheck) const;

    inline void Minimize() {
        Z_SetBestBit(true);
        bits.Minimize();
        Z_SetBestBit(false);
    }

    inline void Flush() {
        bits.Flush();
        bitsSize = 0;
    }

    inline void SetSize(S32 size){
        bitsSize = size;
        S32 sizeInWords = (size >> 5) + 1;
        if(size && sizeInWords > bits.GetSize()){
            bits.SetSize(sizeInWords);
        }
    }

    inline S32 GetSize() const { return bitsSize; }

    inline U32 GetBit(S32 i_Bit) const {
        const U32DA& l_Bits = bits;
        return (l_Bits.Get(i_Bit >> 5)) & (1 << (i_Bit & 0x1F));
    }

    inline void SetBit(S32 i_Bit) {
        bits[i_Bit >> 5] |= (1 << (i_Bit & 0x1F));
    }

    inline void ClearBit(S32 i_Bit) {
        bits[i_Bit >> 5] &= ~(U32)(1 << (i_Bit & 0x1F));
    }
};