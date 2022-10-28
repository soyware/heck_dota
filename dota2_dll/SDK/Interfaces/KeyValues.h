#pragma once

class KeyValues
{
public:
	explicit KeyValues(const char* setName)
	{
		typedef void(__thiscall* Fn) (KeyValues*, const char*);
		static const Fn func = reinterpret_cast<Fn>(GetProcAddress(GetModuleHandle("tier0.dll"), "??0KeyValues@@QEAA@PEBD@Z"));
		reinterpret_cast<Fn>(func)(this, setName);
	}

	bool LoadFromBuffer(char const* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = nullptr, void* pfnEvaluateSymbolProc = nullptr)
	{
		typedef bool(__thiscall* Fn) (KeyValues*, char const*, const char*, void*, const char*, void*);
		static const Fn func = reinterpret_cast<Fn>(GetProcAddress(GetModuleHandle("tier0.dll"), "?LoadFromBuffer@KeyValues@@QEAA_NPEBD0PEAVIBaseFileSystem@@0P6A_N0PEAX@ZPEAVIKeyValuesErrorSpew@@20@Z"));
		return reinterpret_cast<Fn>(func)(this, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
	}
};

class CKeyValuesSystem
{
public:
	inline KeyValues* AllocKeyValuesMemory(size_t)
	{
		typedef KeyValues* (__thiscall* Fn) (CKeyValuesSystem*);
		return GetVF<Fn>(this, 0)(this);
	}

	inline void FreeKeyValuesMemory(void* pMem)
	{
		typedef void(__thiscall* Fn) (CKeyValuesSystem*, void*);
		GetVF<Fn>(this, 1)(this, pMem);
	}
};