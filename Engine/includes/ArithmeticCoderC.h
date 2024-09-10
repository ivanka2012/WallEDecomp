#ifndef __ARITHMETICCODERC_H__
#define __ARITHMETICCODERC_H__

#include <File_Z.h>
#include <Types_Z.h>
#include "SymbolRange.h"

class ArithmeticCoderC  
{
public:
	ArithmeticCoderC();

	void SetFile( File_Z *file );

	void Encode( const SymbolRange& range );
	void EncodeFinish();

	void DecodeStart();
	unsigned int DecodeTarget( U32 total );
	void Decode( U32 low_count, U32 high_count );

protected:
	// bit operations
	void SetBit( const unsigned char bit );
	void SetBitFlush();
	unsigned char GetBit();

	unsigned char mBitBuffer;
	unsigned char mBitCount;

	// in-/output stream
	File_Z *mFile;

	// encoder & decoder
	unsigned int mLow;
	unsigned int mHigh;
	unsigned int mStep;
	unsigned int mScale;

	// decoder
	unsigned int mBuffer;
};

#endif