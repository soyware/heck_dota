#pragma once

class CUIEventBase
{
public:
	void* vt;
	CPanoramaSymbol symbol;
	PanelHandle_t panelHandle;

	explicit CUIEventBase(CPanoramaSymbol* psymbol, CUIPanel* panel) : vt(nullptr), symbol(*psymbol), panelHandle(PanelHandle_t::InvalidHandle())
	{
		if (panel)
			I::PanoramaEngine->AccessUIEngine()->GetPanelHandle(panelHandle, panel);
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

//class CUIEvent0 : public CUIEventBase
//{
//public:
//	explicit CUIEvent0(CPanoramaSymbol* psymbol, CUIPanel* panel) : CUIEventBase(psymbol, panel)
//	{
//		vt = reinterpret_cast<void*>(Signatures::CUIEvent0VT);
//	}
//};

//template <class T>
//class CRegisterEvent
//{
//public:
//	static T symbol;
//
//	static CUIEvent0* MakeEvent(CPanel2D* panelClient)
//	{
//		return new CUIEvent0(&symbol, panelClient ? panelClient->UIPanel() : nullptr);
//	}
//
//	static CUtlString FormatEventArgs(char const*)
//	{
//		return CUtlString::GetEmptyString();
//	}
//
//	static CUIEvent0* CreateEventFromString(CUIPanel* panel, char const* str, char const** pstr)
//	{
//		const char* pc;
//		for (pc = str; *pc && *pc != ')'; ++pc)
//		{
//			if (static_cast<unsigned int>(*pc - 9) > 4 && *pc != ' ')
//				return nullptr;
//		}
//		const char* next = pc + 1;
//		if (*pc != ')')
//			next = pc;
//		*pstr = next;
//
//		return MakeEvent(panel ? panel->ClientPtr() : nullptr);
//	}
//	// cant get this to work
//	static int Register(char const* pchEvent)
//	{
//		static char const* emptyString = "";
//
//		typedef int (*Fn)(CPanoramaSymbol*,
//			char const*,
//			int,
//			bool,
//			CUIEvent0* (*)(CUIPanel*, char const*, char const**),
//			CUtlString(*)(char const*),
//			CUIEvent0* (*)(CPanel2D*),
//			CUIEventBase* (*)(CPanel2D const*, int),
//			CUIEventBase* (*)(CPanel2D const*, int),
//			char const*,
//			char const*,
//			uint8_t);
//
//		return reinterpret_cast<Fn>(Signatures::RegisterUIEvent)(&symbol,
//			pchEvent,
//			0,
//			false,
//			CreateEventFromString,
//			FormatEventArgs,
//			MakeEvent,
//			nullptr,
//			nullptr,
//			emptyString,
//			emptyString,
//			0);
//	}
//};
//
//template <class T>
//T CRegisterEvent<T>::symbol = -1;