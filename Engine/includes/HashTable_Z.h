#pragma once
#include <BitArray_Z.h>

template<typename T>
class HashTableBase_Z{
protected:
    BitArray_Z* presentBits;
    T* values;
    S32 numElems;
    S32 numFree;

    void Resize(S32 newSize){
        S32 oldSize;
        S32 nextScan;

        oldSize = 1;
        while(oldSize < newSize){
            oldSize <<= 1;
        }
        oldSize <<= 1;
        newSize = oldSize;

        BitArray_Z* oldBits = presentBits;
        T* oldValues = values;

        presentBits = New_Z BitArray_Z(newSize);
        values = (T*) Alloc_Z(sizeof(T) * newSize);
        presentBits->ClearAllBits();
        memset(values, 0, sizeof(T) * newSize);

        numElems = 0;
        numFree = newSize;

        if(!oldBits){
            return;
        }

        S32 nextBit = 0;
        while((nextBit = oldBits->FindFirstBit(1, nextBit)) >= 0){
            Bool result = Insert(oldValues[nextBit]);
            nextBit++;
        }

        Free_Z(oldValues);
        Delete_Z oldBits;
    }
};