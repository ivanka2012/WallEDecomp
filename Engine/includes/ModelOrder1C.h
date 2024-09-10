#ifndef __MODELORDER0C_H__
#define __MODELORDER0C_H__

#include "ModelI.h"
#include "ArithmeticCoderC.h"
#include "ArithProbaTable.h"

class ModelOrder1C : public ModelI  
{
public:
	ModelOrder1C();
	virtual ~ModelOrder1C();

	virtual void InitModel();
	virtual void UpdateModel(U32 symbol);
	virtual U32 GetSymbolRange(SymbolRange& range, U32);
	virtual U32 GetTotal(){
		return mCumCount->mTotal;
	}
	virtual U32 GetSymbolFromRange(U32, SymbolRange& range);
	virtual Bool IsDefault(){
		return mCumCount->mDefault;
	}
	
	unsigned int mLastSymbol;
	ArithProbaTable mCumCountCurrent;
	ArithProbaTable* mCumCountLookback[256];
	ArithProbaTable* mCumCount;
};

#endif 
