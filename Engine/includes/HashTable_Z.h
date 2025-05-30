#pragma once
#include <BitArray_Z.h>
#include <Name_Z.h>
#include <Types_Z.h>
#include <Memory_Z.h>

#define HASHTABLE_DEFAULT_SIZE 16

class S32Hash_Z {
public:
    S32 m_Value;
    S32 m_Ref;

    S32Hash_Z() { }

    S32Hash_Z(S32 i_Value) { m_Value = i_Value; }

    S32Hash_Z(S32 i_Value, S32 i_Ref) {
        m_Value = i_Value;
        m_Ref = i_Ref;
    }

    inline S32 HashBase() const { return m_Value; }

    inline S32 HashIncrement() const {
        return HashBase() == 0;
    }

    inline Bool IsEmpty() { return !m_Ref; }

    inline void SetShadow() { m_Ref = -1; }

    Bool operator==(const S32Hash_Z& i_Elem) { return i_Elem.m_Value == m_Value; }

    Bool operator!=(const S32Hash_Z& i_Elem) { return i_Elem.m_Value != m_Value; }
};

class Name_ZHash_Z {
public:
    Name_Z m_Value;
    S32 m_Ref;

    Name_ZHash_Z() { }

    Name_ZHash_Z(Name_Z i_Value) { m_Value = i_Value; }

    Name_ZHash_Z(Name_Z i_Value, S32 i_Ref) {
        m_Value = i_Value;
        m_Ref = i_Ref;
    }

    inline S32 HashBase() const { return m_Value.ID; }

    inline S32 HashIncrement() const {
        return HashBase() == 0;
    }

    inline Bool IsEmpty() { return !m_Ref; }

    inline void SetShadow() { m_Ref = -1; }

    Bool operator==(const Name_ZHash_Z& i_Elem) { return i_Elem.m_Value == m_Value; }

    Bool operator!=(const Name_ZHash_Z& i_Elem) { return i_Elem.m_Value != m_Value; }
};

template<typename T>
class HashTableBase_Z{
    BitArray_Z* presentBits;
    T* Hash;
    S32 numElems;
    S32 numFree;
    S32 m_ScanID;
public:
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
        T* oldValues = Hash;

        presentBits = NewC_Z("HashTableBase_Z::BitArray_Z") BitArray_Z(newSize);
        Hash = (T*) AllocC_Z(sizeof(T) * newSize, "HashTableBase_Z::Hash");
        presentBits->ClearAllBits();
        memset(Hash, 0, sizeof(T) * newSize);

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

    

    HashTableBase_Z() {
        numElems = 0;
        numFree = 0;
        m_ScanID = -1;
        presentBits = NULL;
        Hash = NULL;
        Resize(HASHTABLE_DEFAULT_SIZE);
    }

    HashTableBase_Z(S32 i_Size) {
        numElems = 0;
        numFree = 0;
        m_ScanID = -1;
        presentBits = NULL;
        Hash = NULL;
        Resize(i_Size);
    }

    ~HashTableBase_Z() {
        Flush();
    }

    void Flush() {
        if (presentBits) {
            Delete_Z presentBits;
            presentBits = NULL;
        }
        if (Hash) {
            Free_Z(Hash);
            Hash = NULL;
        }
        numElems = 0;
        numFree = 0;
        m_ScanID = -1;
    }

    void Minimize() {
        Z_SetBestBit(true);
        Resize(numElems);
        Z_SetBestBit(false);
    }

    Bool Insert(const T& i_Ele) {
        if (!presentBits) {
            Resize(HASHTABLE_DEFAULT_SIZE);
        }

        S32 l_HashSize = presentBits->GetSize() - 1;
        S32 l_HashID = i_Ele.HashBase() & l_HashSize;
        S32 l_HashInc = i_Ele.HashIncrement();
        S32 l_ShadowHashID = -1;
        if (!(l_HashInc & 0x1)) {
            l_HashInc++;
        }

        for (;;) {
            if (!presentBits->GetBit(l_HashID)) {
                if (!Hash[l_HashID].m_Ref) {
                    //if (values[l_HashID].IsEmpty()) {
                    if (l_ShadowHashID < 0)
                        numFree--;
                    else
                        l_HashID = l_ShadowHashID;

                    presentBits->SetBit(l_HashID);
                    *(Hash + l_HashID) = i_Ele;

                    numElems++;

                    if ((numFree == 0) || (numFree < (presentBits->GetSize() >> 2))) {
                        Resize(numElems);
                    }
                    return TRUE;
                }
                else if (l_ShadowHashID < 0) {
                    l_ShadowHashID = l_HashID;
                }
            }
            else if (Hash[l_HashID] == i_Ele) {
                return FALSE;
            }
            l_HashID = (l_HashID + l_HashInc) & l_HashSize;
        }
    }

    const T* Search(const T& Element) const {
        if (!numElems)
            return NULL;
        S32 l_HashSize = presentBits->GetSize() - 1;
        S32 l_HashID = Element.HashBase() & l_HashSize;
        S32 l_HashInc = Element.HashIncrement();
        if (!(l_HashInc & 0x1))
            l_HashInc++;

        for (;;) {
            if (!presentBits->GetBit(l_HashID)) {
                if (Hash[l_HashID].IsEmpty())
                    return NULL;
            }
            else {
                T* l_Ptr = Hash + l_HashID;
                if (*l_Ptr == Element)
                    return l_Ptr;
            }
            l_HashID = (l_HashID + l_HashInc) & l_HashSize;
        }
        return NULL;
    }

    inline void InitScan() {
        if (!numElems)
            m_ScanID = -1;
        else
            m_ScanID = 0;
    }

    inline T* NextScan() {
        if (m_ScanID < 0) return NULL;
        if (m_ScanID >= presentBits->GetSize()) {
            m_ScanID = -1;
            return NULL;
        }

        S32 NextScan = presentBits->FindFirstBit(TRUE, m_ScanID);

        if (NextScan < 0) {
            m_ScanID = -1;
            return NULL;
        }

        m_ScanID = NextScan + 1;
        return Hash + NextScan;
    }
};


typedef HashTableBase_Z<S32Hash_Z> HashS32Table_Z;
typedef HashTableBase_Z<Name_ZHash_Z> HashName_ZTable_Z;