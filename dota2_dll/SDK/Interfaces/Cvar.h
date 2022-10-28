#pragma once

class ConCommandBase;
class ConCommand;
class ConVar;

class CCvar
{
public:
	inline void RegisterConCommand(ConCommandBase* pConCommand)
	{
		typedef void(__thiscall* Fn) (void*, ConCommandBase*);
		GetVF<Fn>(this, 12)(this, pConCommand);
	}

	inline void UnregisterConCommand(ConCommandBase* pConCommand)
	{
		typedef void(__thiscall* Fn) (void*, ConCommandBase*);
		GetVF<Fn>(this, 13)(this, pConCommand);
	}

	inline ConCommandBase* FindCommandBase(const char* varName)
	{
		typedef ConCommandBase* (__thiscall* Fn) (void*, const char*);
		return GetVF<Fn>(this, 16)(this, varName);
	}

	inline ConVar* FindVar(const char* varName)
	{
		typedef ConVar* (__thiscall* Fn) (void*, const char*);
		return GetVF<Fn>(this, 18)(this, varName);
	}

	inline ConCommand* FindCommand(const char* varName)
	{
		typedef ConCommand* (__thiscall* Fn) (void*, const char*);
		return GetVF<Fn>(this, 20)(this, varName);
	}
};
