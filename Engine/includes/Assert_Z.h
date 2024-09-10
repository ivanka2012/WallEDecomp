#pragma once

#include <Types_Z.h>

void BreakPoint_Z();
void ExceptionBool_Z(bool, bool, const char*, const char*, S32, const char*, ...);

#define Assert_Z(condition, msg) do { ExceptionBool_Z(false, condition, #condition, __FILE__, __LINE__, msg); } while(0); 
#define AssertV_Z(condition, msg, ...) do { ExceptionBool_Z(false, condition, #condition, __FILE__, __LINE__, msg, __VA_ARGS__); } while(0); 