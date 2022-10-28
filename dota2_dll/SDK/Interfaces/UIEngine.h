#pragma once

class CUIPanel;
class CPanel2D;
class CUIEventBase;

class IUIEngine
{
public:
	inline CUtlMap<CUIPanel*, unsigned int, int>* GetPanelsMap()
	{
		static const int offset = *reinterpret_cast<int*>(GetVF<uintptr_t>(this, 33) + 2) - 24;
		return reinterpret_cast<CUtlMap<CUIPanel*, unsigned int, int>*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	inline CUIPanel* CreatePanel(CPanoramaSymbol* symbol, const char* id, CUIPanel* parent)
	{
		typedef CUIPanel*(__thiscall* Fn)(IUIEngine*, CPanoramaSymbol*, const char*, CUIPanel*);
		return GetVF<Fn>(this, 30)(this, symbol, id, parent);
	}

	inline bool IsValidPanelPointer(CUIPanel* panel)
	{
		typedef bool(__thiscall* Fn)(IUIEngine*, CUIPanel*);
		return GetVF<Fn>(this, 33)(this, panel);
	}

	inline PanelHandle_t* GetPanelHandle(PanelHandle_t& out, CUIPanel* panel)
	{
		typedef PanelHandle_t* (__thiscall* Fn)(IUIEngine*, PanelHandle_t&, CUIPanel*);
		return GetVF<Fn>(this, 34)(this, out, panel);
	}

	inline CUIPanel* GetPanelPtr(PanelHandle_t& handle)
	{
		typedef CUIPanel*(__thiscall* Fn)(IUIEngine*, PanelHandle_t&);
		return GetVF<Fn>(this, 35)(this, handle);
	}

	inline void RegisterEventHandlerClient(CPanoramaSymbol* event, CPanel2D* panel, CUtlAbstractDelegate handler)
	{
		typedef void(__thiscall* Fn)(IUIEngine*, CPanoramaSymbol*, CPanel2D*, CUtlAbstractDelegate);
		GetVF<Fn>(this, 40)(this, event, panel, handler);
	}

	inline void DispatchEvent(CUIEventBase* event)
	{
		typedef void(__thiscall* Fn)(IUIEngine*, CUIEventBase*);
		GetVF<Fn>(this, 50)(this, event);
	}

	inline void RunScript(CUIPanel* panel, char const* script, char const* context, int unk1, int unk2, bool print)
	{
		typedef void(__thiscall* Fn)(IUIEngine*, CUIPanel*, char const*, char const*, int, int, bool);
		GetVF<Fn>(this, 109)(this, panel, script, context, unk1, unk2, print);
	}

	inline CPanoramaSymbol MakeSymbol(const char* name)
	{
		typedef CPanoramaSymbol(__thiscall* Fn)(IUIEngine*, const char*);
		return GetVF<Fn>(this, 145)(this, name);
	}
};

class CPanoramaUIEngine
{
public:
	inline IUIEngine* AccessUIEngine()
	{
		typedef IUIEngine* (__thiscall* Fn)(CPanoramaUIEngine*);
		return GetVF<Fn>(this, 13)(this);
	}
};