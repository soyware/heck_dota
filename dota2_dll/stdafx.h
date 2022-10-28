#pragma once

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include <thread>
#include <Psapi.h>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#ifdef _DEBUG
#include <string>
#endif // _DEBUG

#include "SDK/Utl/UtlSymbol.h"
#include "SDK/Utl/UtlString.h"
#include "SDK/Utl/UtlMemory.h"
#include "SDK/Utl/UtlVector.h"
#include "SDK/Utl/UtlRBTree.h"
#include "SDK/Utl/UtlMap.h"
#include "SDK/Utl/UtlDelegate.h"

using namespace std::chrono_literals;

#pragma warning(disable : 4244) // conversion from 'float' to 'int', possible loss of data
#pragma warning(disable : 4100) // '_edx': unreferenced formal parameter

template <class T>
inline T GetVF(void* Instance, int Index)
{
	return (*reinterpret_cast<T**>(Instance))[Index];
}

extern void Uninject();
extern void FatalError(const char* err);