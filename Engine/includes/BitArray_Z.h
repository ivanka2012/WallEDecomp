#pragma once
#include <DynArray_Z.h>

class BitArray_Z{
    DynArray_Z<U32> bits;
    S32 bitsSize;
public:
    BitArray_Z(S32 size);

    void SetSize(S32 size){
        bitsSize = size;
        S32 sizeInWords = (size >> 5) + 1;
        if(size && sizeInWords > bits.GetSize()){
            bits.SetSize(sizeInWords);
        }
    }

    void ClearAllBits();

    S32	FindFirstBit(Bool state=1,S32 firstBit=0) const;
};