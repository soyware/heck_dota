#pragma once

class CEngineClient
{
public:
	inline int* GetLocalPlayer(int& outIndex, int splitScreen = 0)
	{
		typedef int* (__thiscall* Fn) (CEngineClient*, int&, int);
		return GetVF<Fn>(this, 22)(this, outIndex, splitScreen);
	}

	inline float GetLastTimeStamp()
	{
		typedef float(__thiscall* Fn) (CEngineClient*);
		return GetVF<Fn>(this, 23)(this);
	}

	inline bool IsInGame()
	{
		typedef bool(__thiscall* Fn) (CEngineClient*);
		return GetVF<Fn>(this, 26)(this);
	}

	inline void ClientCmd_Unrestricted(const char* szCmdString)
	{
		typedef void(__thiscall* Fn) (CEngineClient*, const char*);
		GetVF<Fn>(this, 35)(this, szCmdString);
	}
};