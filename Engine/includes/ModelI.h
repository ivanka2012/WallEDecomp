#ifndef __MODELI_H__
#define __MODELI_H__

#include "ArithmeticCoderC.h"

enum ModeE
{
	MODE_ENCODE = 0,
	MODE_DECODE
};

class ModelI  
{
public:
	virtual ~ModelI(){}
	virtual void InitModel(){}
	virtual void UpdateModel(U32 symbol) = 0;
	virtual U32 GetSymbolRange(SymbolRange& range, U32) = 0;
	virtual U32 GetTotal() = 0;
	virtual U32 GetSymbolFromRange(U32, SymbolRange& range) = 0;
	virtual Bool IsDefault() = 0;

	void Process( File_Z *source, File_Z *target, ModeE mode, U32 decompressedSize );

	void Encode();
	void Decode(U32 decompressedSize);

	ArithmeticCoderC mCoder;
	File_Z *mSource;
	File_Z *mTarget;
};

#endif
