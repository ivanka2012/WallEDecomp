#include <ModelOrder1C.h>
#include <Memory_Z.h>
#include <Assert_Z.h>

/*
ModelOrder1C::ModelOrder1C()
{
	for( unsigned int i=0; i<256; i++ )
	{
		mCumCountLookback[i] = new CountBackingStore;
		for( unsigned int j=0; j<257; j++ )
			mCumCountLookback[i]->mCumCount[j] = 0;
		mCumCountLookback[i]->mCumCount[254] = 1;
		mCumCountLookback[i]->mCumCount[256] = 1;
		mCumCountLookback[i]->mTotal = 2;
		mCumCountLookback[i]->mDefault = 0;
	}

	for( unsigned int i=0; i<257; i++ )
		mCumCountCurrent.mCumCount[i] = 1;
	mCumCountCurrent.mTotal = 257;
	mCumCountCurrent.mDefault = 1;

	mLastSymbol = -1;
	mCumCount = mCumCountLookback[0];
}

ModelOrder1C::~ModelOrder1C()
{
	for( unsigned int i=0; i<256; i++ )
	{
		delete mCumCountLookback[i];
	}
}

void ModelOrder1C::Encode()
{
	int i = 0;

	unsigned char symbol;
	while(mSource->read(reinterpret_cast<char*>(&symbol), sizeof(symbol)))
	{
		unsigned char ret = 0;
		do
		{
			unsigned int low_count, high_count, total;
			ret = CumulateFreqencies(symbol, low_count, high_count, total);

			mAC.Encode(low_count, high_count, total);
		}
		while (ret == 254);

		UpdateModel(symbol);
	}

	auto pos = mTarget->tellp();
	while (pos == mTarget->tellp())
	{
		unsigned char ret = 0;
		do
		{
			unsigned int low_count, high_count, total;
			ret = CumulateFreqencies(0, low_count, high_count, total);

			mAC.Encode(low_count, high_count, total);
		} while (ret == 254);

		UpdateModel(0);
	}
}

unsigned char ModelOrder1C::CumulateFreqencies(unsigned char symbol, unsigned int& low_count, unsigned int& high_count, unsigned int& total)
{
	unsigned int ret = 0;
	if (mCumCount->mCumCount[symbol])
	{
		if (symbol == 254 && mCumCount->mDefault == 0)
			ret = 254;
	}
	else
	{
		ret = 254;
		symbol = 254;
	}

	low_count = 0;
	unsigned char j = 0;
	for (; j < symbol; j++)
		low_count += mCumCount->mCumCount[j];

	high_count = low_count + mCumCount->mCumCount[j];
	total = mCumCount->mTotal;

	if (ret == 254)
		mCumCount = &mCumCountCurrent;

	return ret;
}
*/

ModelOrder1C::ModelOrder1C(){
	for( unsigned int i=0; i<256; i++ ){
		mCumCountLookback[i] = New_Z ArithProbaTable;
		//This seems to be grammatically incorrect French. To machine translate: "Lack of memory allocation arithmetic packer".
		//DU HAST NICHT MEMORY
		EXCEPTC_Z(mCumCountLookback[i], "Manque de mémoire allocation packer arithmetique");
	}
}

ModelOrder1C::~ModelOrder1C(){
	for( unsigned int i=0; i<256; i++ ){
		Delete_Z mCumCountLookback[i];
	}
}

void ModelOrder1C::InitModel(){
	mCumCount = mCumCountLookback[0];
	for( unsigned int i=0; i<256; i++ ){
		mCumCountLookback[i]->Init(true);
	}
	mCumCountCurrent.Init(false);
	mLastSymbol = -1;
}

U32 ModelOrder1C::GetSymbolRange(SymbolRange& range, U32 param){
	U32 code = mCumCount->GetSymbolCode(range, param);
	if(code == 254){
		mCumCount = &mCumCountCurrent;
	}
	return code;
}


U32 ModelOrder1C::GetSymbolFromRange(U32 param, SymbolRange& range){
	U32 code = mCumCount->GetSymbolFromRange(param, range);
	if(code == 254 && !IsDefault()){
		mCumCount = &mCumCountCurrent;
	}
	return code;
}

void ModelOrder1C::UpdateModel(U32 symbol)
{
	if (symbol == 256)
	{
		mCumCount->AddSymbol(256);
	}
	else
	{
		if (mLastSymbol != -1)
		{
			mCumCount = mCumCountLookback[mLastSymbol];
			mCumCount->AddSymbol(symbol);
		}
		mLastSymbol = symbol;
		mCumCount = mCumCountLookback[symbol];
	}
}

/*
unsigned int ModelOrder1C::determineSymbol(unsigned int value, unsigned int &low_count, unsigned int& high_count)
{
	low_count = 0;
	unsigned int symbol = 0;

	for (; low_count + mCumCount->mCumCount[symbol] <= value; symbol++)
		low_count += mCumCount->mCumCount[symbol];

	high_count = low_count + mCumCount->mCumCount[symbol];

	if (symbol == 254 && mCumCount->mDefault == 0)
		mCumCount = &mCumCountCurrent;
	
	return symbol;
}

void ModelOrder1C::Decode()
{
	unsigned int symbol;

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
	while( symbol != 256 ); // until termination symbol read
}
*/