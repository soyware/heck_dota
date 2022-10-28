#pragma once

class VPanelWrapper
{
public:
	inline const char* GetName(ULONGLONG vguiPanel)
	{
		typedef const char* (__thiscall* Fn) (VPanelWrapper*, ULONGLONG);
		return GetVF<Fn>(this, 50)(this, vguiPanel);
	}

	inline void* Client(ULONGLONG vguiPanel)
	{
		typedef void* (__thiscall* Fn) (VPanelWrapper*, ULONGLONG);
		return GetVF<Fn>(this, 78)(this, vguiPanel);
	}
};