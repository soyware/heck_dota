#pragma once

class CDOTARichPresence
{
public:
	inline void SetRPStatus(const char* status, int paramCount = 0, const char** params = nullptr)
	{
		typedef void(__thiscall* Fn)(CDOTARichPresence*, const char*, int, const char**);
		reinterpret_cast<Fn>(Signatures::CDOTARichPresence__SetRPStatus)(this, status, paramCount, params);
	}
};