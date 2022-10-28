#pragma once

class CPanel2D;

class CUIPanel
{
public:
	inline CPanel2D* ClientPtr()
	{
		typedef CPanel2D* (__thiscall* Fn)(CUIPanel*);
		return GetVF<Fn>(this, 7)(this);
	}

	inline const char* GetID()
	{
		typedef const char*(__thiscall* Fn)(CUIPanel*);
		return GetVF<Fn>(this, 9)(this);
	}

	inline bool MustLoadLayoutFromString(const char* str, bool mbKeepString, bool mbKeepFile)
	{
		typedef bool(__thiscall* Fn)(CUIPanel*, const char*, bool, bool);
		return GetVF<Fn>(this, 15)(this, str, mbKeepString, mbKeepFile);
	}

	inline CUIPanel* GetParent()
	{
		typedef CUIPanel*(__thiscall* Fn)(CUIPanel*);
		return GetVF<Fn>(this, 32)(this);
	}

	inline CUIPanel* FindChild(const char* name)
	{
		typedef CUIPanel* (__thiscall* Fn)(CUIPanel*, const char*);
		return GetVF<Fn>(this, 48)(this, name);
	}

	inline CUIPanel* MustFindChild(const char* name)
	{
		typedef CUIPanel* (__thiscall* Fn)(CUIPanel*, const char*);
		return GetVF<Fn>(this, 49)(this, name);
	}

	inline CUIPanel* FindChildTraverse(const char* name)
	{
		typedef CUIPanel* (__thiscall* Fn)(CUIPanel*, const char*);
		return GetVF<Fn>(this, 50)(this, name);
	}

	inline CUIPanel* MustFindChildTraverse(const char* name)
	{
		typedef CUIPanel* (__thiscall* Fn)(CUIPanel*, const char*);
		return GetVF<Fn>(this, 51)(this, name);
	}

	inline CUIPanel* FindChildInLayoutFile(const char* name)
	{
		typedef CUIPanel* (__thiscall* Fn)(CUIPanel*, const char*);
		return GetVF<Fn>(this, 52)(this, name);
	}

	inline CUIPanel* MustFindChildInLayoutFile(const char* name)
	{
		typedef CUIPanel* (__thiscall* Fn)(CUIPanel*, const char*);
		return GetVF<Fn>(this, 53)(this, name);
	}

	inline int GetChildCount()
	{
		typedef int(__thiscall* Fn)(CUIPanel*);
		return GetVF<Fn>(this, 59)(this);
	}

	inline CUIPanel* GetChild(int index)
	{
		typedef CUIPanel* (__thiscall* Fn)(CUIPanel*, int);
		return GetVF<Fn>(this, 60)(this, index);
	}

	inline void ApplyStyles(bool val)
	{
		typedef void(__thiscall* Fn)(CUIPanel*, bool);
		GetVF<Fn>(this, 75)(this, val);
	}

	inline void AddClass(const char* name)
	{
		typedef void(__thiscall* Fn)(CUIPanel*, const char*);
		GetVF<Fn>(this, 141)(this, name);
	}

	inline void SetSelected(bool value)
	{
		typedef void(__thiscall* Fn)(CUIPanel*, bool);
		GetVF<Fn>(this, 196)(this, value);
	}

	inline void SetEnabled(bool value)
	{
		typedef void(__thiscall* Fn)(CUIPanel*, bool);
		GetVF<Fn>(this, 203)(this, value);
	}

	inline bool DispatchPanelEvent(CPanoramaSymbol* symbol)
	{
		typedef bool(__thiscall* Fn)(CUIPanel*, CPanoramaSymbol*);
		return GetVF<Fn>(this, 233)(this, symbol);
	}

	inline void* GetPanelEvents(CPanoramaSymbol* symbol)
	{
		typedef void* (__thiscall* Fn)(CUIPanel*, CPanoramaSymbol*);
		return GetVF<Fn>(this, 344)(this, symbol);
	}

	inline bool HasBeenLayedOut()
	{
		typedef bool(__thiscall* Fn)(CUIPanel*);
		return GetVF<Fn>(this, 345)(this);
	}
};