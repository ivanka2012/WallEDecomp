#include <ArithProbaTable.h>

void ArithProbaTable::Init(bool what){
    if(what){
        mTotal = 2;
		for( unsigned int j=0; j<257; j++ )
			mCumCount[j] = 0;
		mCumCount[254] = 1;
		mCumCount[256] = 1;
        mDefault = 0;
    }else{
        mTotal = 257;
        for( unsigned int i=0; i<257; i++ )
            mCumCount[i] = 1;
        mDefault = 1;
    }
	
}

U32 ArithProbaTable::GetSymbolCode(SymbolRange& range, U32 param){
    U32 ret = 0;
    if(mCumCount[param]){
        if(param == 254 && !mDefault)
            ret = 254;   
    }else{
        ret = 254;
        param = 254; 
    }
    range.low_count = 0;

    unsigned int j;
	for (j = 0; j < param; j++)
		range.low_count += mCumCount[j];

    range.high_count = range.low_count + mCumCount[j];
	range.total = mTotal;

    return ret;
}

U32 ArithProbaTable::GetSymbolFromRange(U32 param, SymbolRange& range){
    unsigned int accum = 0;
	unsigned int symbol = 0;

	for (; accum + mCumCount[symbol] <= param; symbol++)
		accum += mCumCount[symbol];

    range.low_count = accum;
	range.high_count = range.low_count + mCumCount[symbol];

    range.total = mTotal;

    return symbol;
}

void ArithProbaTable::AddSymbol(U32 code){
    mCumCount[code]++;
    mTotal++;
}