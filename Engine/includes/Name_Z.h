#include <Types_Z.h>

class Name_Z{
public:
    static U32 GetID(const U8* data, U32 size, U32 init);
    static U32 GetID(const Char* data, U32 init);
};