#pragma once

class CPanel2D
{
	void* vt;
	CUIPanel* panel;
	PanelHandle_t handle;
	uintptr_t unk;
public:
	inline CUIPanel* UIPanel()
	{
		typedef CUIPanel* (__thiscall* Fn)(CPanel2D*);
		return GetVF<Fn>(this, 0)(this);
	}

	inline CPanoramaSymbol* GetPanelType(CPanoramaSymbol& out)
	{
		typedef CPanoramaSymbol* (__thiscall* Fn)(CPanel2D*, CPanoramaSymbol&);
		return GetVF<Fn>(this, 2)(this, out);
	}
};

class CUI_PopupManager;

enum EDOTAPopupBackgroundStyle
{
	POPUP_BG_NONE,
	POPUP_BG_DIM,
	POPUP_BG_BLUR
};

class CUI_Popup : public CPanel2D
{
	uint64_t parentPanelHandle;
	std::byte _pad[24];
	bool bCreatedByJob;
	bool bJobCleanup;
	CUI_PopupManager* manager;
	EDOTAPopupBackgroundStyle bgStyle;
public:
	explicit CUI_Popup(CUI_PopupManager* manager, const char* id, CPanel2D* parent)
	{
		typedef void(__thiscall* Fn)(CUI_Popup*, CUI_PopupManager*, const char*, CPanel2D*);
		reinterpret_cast<Fn>(Signatures::CDOTA_UI_Popup_Constructor)(this, manager, id, parent);
	}

	static void* operator new(size_t size)
	{
		return I::MemAlloc->Alloc(size);
	}

	static void operator delete(void* mem)
	{
		I::MemAlloc->Free(mem);
	}
};

class CUI_PopupManager : public CPanel2D
{
public:
	inline void ShowPopup(CUI_Popup* popup)
	{
		typedef void(__thiscall* Fn)(CUI_PopupManager*, CUI_Popup*);
		reinterpret_cast<Fn>(Signatures::CUI_PopupManager__ShowPopup)(this, popup);
	}

	// "onpopupsdismissed"
	inline void CloseAndDeletePopup(CUI_Popup* popup, float timeout)
	{
		typedef void(__thiscall* Fn)(CUI_PopupManager*, CUI_Popup*, float);
		GetVF<Fn>(this, 79)(this, popup, timeout);
	}
};

inline CUI_PopupManager* GetTopmostPopupManager()
{
	typedef CUI_PopupManager* (*Fn)();
	return reinterpret_cast<Fn>(Signatures::GetTopmostPopupManager)();
}

class CDOTA_DB_PopupSettings
{
public:
	// this isn't used
	static void CheckChildrenForSettingsConVars(CPanel2D* panel)
	{
		typedef void(*Fn)(CDOTA_DB_PopupSettings*, CPanel2D*);
		reinterpret_cast<Fn>(Signatures::CDOTA_DB_PopupSettings__CheckChildrenForSettingsConVars)(nullptr, panel);
	}
};

class CTextEntry : public CPanel2D
{
	void* vt;
public:
	inline const char* PchGetText()
	{
		typedef const char*(__thiscall* Fn)(void*);
		return GetVF<Fn>(&(CTextEntry::vt), 7)(&(CTextEntry::vt));
	}

	inline void SetText(const char* text)
	{
		typedef void(__thiscall* Fn)(CTextEntry*, const char*);
		reinterpret_cast<Fn>(Signatures::CTextEntry__SetText)(this, text);
	}
};

class CDropDown : public CPanel2D
{
public:
	inline CPanel2D* GetSelected()
	{
		CUIPanel* selected = I::PanoramaEngine->AccessUIEngine()->GetPanelPtr(*reinterpret_cast<PanelHandle_t*>(reinterpret_cast<uintptr_t>(this) + 40));
		if (selected)
			return selected->ClientPtr();
		return nullptr;
	}
};