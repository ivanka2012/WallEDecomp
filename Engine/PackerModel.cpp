#include "ModelI.h"

void ModelI::Process( File_Z *source, File_Z *target, ModeE mode, U32 decompressedSize )
{
	mSource = source;
	mTarget = target;

	if( mode == MODE_ENCODE )
	{
		mCoder.SetFile( mTarget );

		// encode
		Encode();

		mCoder.EncodeFinish();
	}
	else // MODE_DECODE
	{
		mCoder.SetFile( mSource );

		mCoder.DecodeStart();

		// decode
		Decode(decompressedSize);
	}
};

void ModelI::Encode()
{
	InitModel();

	SymbolRange range;
	unsigned char symbol;

	while(!mSource->IsEOF())
	{
		if(mSource->Read(&symbol, sizeof(symbol))){
			unsigned int code;
			do{
				code = GetSymbolRange(range, symbol);
				mCoder.Encode(range);
			}while(code == 254);
			UpdateModel(symbol);
		}
	}

	for(unsigned int i = 0; i < 4; i++)
	{
		unsigned int code;
		do {
			code = GetSymbolRange(range, 0);
			mCoder.Encode(range);
		} while (code == 254);

		UpdateModel(0);
	}
}

void ModelI::Decode(U32 decompressedSize)
{
	InitModel();

	SymbolRange range;
	unsigned int symbol;

	do
	{
		U32 value = mCoder.DecodeTarget(GetTotal());
		Bool isDefault = IsDefault();
		symbol = GetSymbolFromRange(value, range);
		if (symbol < 256 && (symbol != 254 || isDefault)){
			unsigned char toWrite = symbol;
			mTarget->Write(&toWrite, sizeof(toWrite));
			if(mTarget->GetCurPos() == decompressedSize)
				break;
		}
		mCoder.Decode(range.low_count, range.high_count);
		if (symbol != 254 || isDefault != 0)
			UpdateModel( symbol );
	}while(symbol != 256);

	/*unsigned int symbol;

	do
	{
		unsigned int defaul = mCumCount->mDefault;

		unsigned int value = mAC.DecodeTarget( mCumCount->mTotal );

		unsigned int low_count, high_count;
		symbol = determineSymbol(value, low_count, high_count);

		if (symbol < 256 && (symbol != 254 || defaul != 0))
		{
			mTarget->write(reinterpret_cast<char*>(&symbol), sizeof(char));
			if (mTarget->tellp() >= mDecompressedSize)
				break;
		}

		mAC.Decode( low_count, high_count);

		if (symbol != 254 || defaul != 0)
			UpdateModel( symbol );
	}
	while( symbol != 256 ); // until termination symbol read*/
}
