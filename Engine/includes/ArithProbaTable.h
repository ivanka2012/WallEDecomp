#pragma once
#include "SymbolRange.h"
#include <Types_Z.h>

struct ArithProbaTable{
    U32 mCumCount[ 257 ];
	U32 mTotal;
	Bool mDefault;

    void Init(bool what);
    U32 GetSymbolCode(SymbolRange& range, U32 param);
    U32 GetSymbolFromRange(U32, SymbolRange& range);
    void AddSymbol(U32 code);
};