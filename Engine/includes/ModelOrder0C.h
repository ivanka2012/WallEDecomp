#pragma once
#include "ArithProbaTable.h"
#include "ModelI.h"

class ModelOrder0C : public ModelI  
{
public:
	ModelOrder0C(){}
	virtual ~ModelOrder0C(){}

	virtual void InitModel();
	virtual void UpdateModel(U32 symbol);
	virtual U32 GetSymbolRange(SymbolRange& range, U32 param);
	virtual U32 GetTotal(){
		return mCumCount->mTotal;
	}
	virtual U32 GetSymbolFromRange(U32 param, SymbolRange& range);
	virtual Bool IsDefault(){
		return mCumCount->mDefault;
	}
	
	ArithProbaTable mCumCountCurrent;
	ArithProbaTable mCumCountLookback;
	ArithProbaTable* mCumCount;
};