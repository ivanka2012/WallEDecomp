#pragma once

#include <Types_Z.h>

struct Name_Z{
    U32 ID;

	Name_Z(){}
    Name_Z(U32 ID) { this->ID = ID; }

    static U32 GetID(const U8* data, U32 size, U32 init);
    static U32 GetID(const Char* data, U32 init);

    Bool operator==(const Name_Z& a1) const { return ID == a1.ID; }
    Bool operator==(Name_Z a1) { return ID == a1.ID; }
    Bool operator!=(const Name_Z& a1) const { return ID != a1.ID; }
    Bool operator!=(Name_Z a1) { return ID != a1.ID; }
};