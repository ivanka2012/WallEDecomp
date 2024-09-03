#include <ModelOrder0C.h>

void ModelOrder0C::InitModel(){
    mCumCount = &mCumCountLookback;
    mCumCountLookback.Init(1);
    mCumCountCurrent.Init(0);
}

void ModelOrder0C::UpdateModel(U32 symbol){
    mCumCount = &mCumCountLookback;
    mCumCount->AddSymbol(symbol);
}

U32 ModelOrder0C::GetSymbolRange(SymbolRange& range, U32 param){
    U32 code = mCumCount->GetSymbolCode(range, param);
	if(code == 254){
		mCumCount = &mCumCountCurrent;
	}
	return code;
}

U32 ModelOrder0C::GetSymbolFromRange(U32 param, SymbolRange& range){
    U32 code = mCumCount->GetSymbolFromRange(param, range);
	if(code == 254 && !IsDefault()){
		mCumCount = &mCumCountCurrent;
	}
	return code;
}