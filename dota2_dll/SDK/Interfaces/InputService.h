#pragma once

class IInputService
{
public:
	inline void EnableKeyBindingSystem(bool on)
	{
		typedef void(__thiscall* Fn)(IInputService*, bool);
		GetVF<Fn>(this, 47)(this, on);
	}
};