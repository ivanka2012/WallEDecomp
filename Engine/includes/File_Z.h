#pragma once
#include <Types_Z.h>

class File_Z{
    char stub[28];
public:
    File_Z();
    ~File_Z();
    void BuildDir(const char*);
    void Close();
    void DoFileExists(const char*);
    void Flush();
    U32 GetCurPos();
    void GetFileDate(const char*);
    void GetRealFileName(const char*, char*);
    void GetSize();
    void GotoNextString();
    Bool IsEOF();
    void Open(const char*, U32, U32, const char*);
    Bool Read(void*, U32);
    void ReadChar();
    void ReadFloat(float*);
    void ReadInt(S32*);
    void ReadInt(U32*);
    void ReadLine(char*);
    void ReadShort(U16*);
    void ReadString(char*);
    void ReadStringNumber(char*);
    void ReadStringUnderQuote(char*);
    void SeekTo(U32, U32);
    void SetCurPos(U32);
    void SetFileDate(const char*, S32);
    void Write(const void*, U32);
};