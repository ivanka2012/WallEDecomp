#pragma once
#include <Types_Z.h>
#include <DynArray_Z.h>
#include <HashTable_Z.h>

struct BaseObject_Z{
public:

};

/**
 * @brief Numeric handle to a BaseObject_Z
 * 
 * First verified to match: 2024-03-19 16:37:20
 */
struct BaseObject_ZHdl {
    union{
        long val;
        struct {
            U32 key : 8, id : 24;
        };
    };
    BaseObject_ZHdl() {}
    BaseObject_ZHdl(S32 val) : val(val) {}
    BaseObject_ZHdl(const BaseObject_ZHdl& other){
        val = other.val;
    }
};

struct Name_Z{
    U32 name;

	Name_Z(){}
    Name_Z(U32 Name) { name = Name; }
};

class DrawInfo_Z;
class Vec4f;

struct HandleRec_Z {
    enum Flags{
        NONE = 0,
        RSC = 1<<3 //Resource?
    };

    unsigned char aa; //Handle id key?
    U8 Flag; //Dirty flag?
    Bool Marked;
    unsigned char dd;
    BaseObject_Z* ObjPtr;
    U32 Name; //This is **NOT** a Name_Z. Constructor inlining will fail in DynArray_Z<HandleRec_Z>::SetSize otherwise.
    U32 d; 
    HandleRec_Z() {
        /*a = 0;
        b = 0;
        c = 1;
        d = 0;*/
        Name = 0;
        ObjPtr = 0;
        aa = 1;
        Flag = NONE;
    }
    ~HandleRec_Z(){}
};

//struct Name_ZHash_TZ {};

class HandleManager_Z{
    DynArray_Z<HandleRec_Z> handleRecArray;
    DynArray_Z<S32> freeRecArray;
    char padding2[4];
    //HashTable_Z<Name_ZHash_TZ> refs;
    S32 numElems;
    S32 lastExpansionSize;
    
public:
    HandleManager_Z();
    virtual ~HandleManager_Z();


    void ExpandSize(S32 size);

    void CreateNewHandle(BaseObject_Z* obj, const Name_Z& name, short unk1, unsigned char unk2);

    virtual void CheckHandles();
    virtual void MarkHandles(long);
    virtual void Update(float);
    virtual void Draw(DrawInfo_Z&);
    virtual void Minimize();
    virtual void ClearMark();
    virtual void Unk1(); //InvalidClassSize(short)?
    virtual void Unk2(); //Who knows...
    virtual void ChangeHandleName(const BaseObject_ZHdl&, const Name_Z&);
    virtual void RequestRegion(const Vec4f&, float);
    virtual void DeleteHandle(const BaseObject_ZHdl&);
    virtual void Unk3(); //GetNameStrFromId?


    /**
     * @brief 
     * 
     * First verified to match: 2024-03-19 16:28:24
     * 
     * @param val 
     * @return BaseObject_ZHdl 
     */
    BaseObject_ZHdl U32ToHandle(S32 val);

    /**
     * @brief 
     * 
     * First verified to match: 2024-03-19 16:31:02
     * 
     * @param handle 
     * @return long 
     */
    S32 HandleToU32(const BaseObject_ZHdl& handle);
};