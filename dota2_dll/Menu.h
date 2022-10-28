#pragma once

#include "popup_heck.h"

namespace Menu
{
	CUI_PopupManager* manager = nullptr;
	CUI_Popup* menu = nullptr;
	void* validVT = nullptr;

	inline bool IsValid()
	{
		return (menu && *reinterpret_cast<void**>(menu) == validVT);
	}

	void SetRichPresence()
	{
		Settings::CrashFriendsList.SetValue(0);
		CDOTA_DB_PopupSettings::CheckChildrenForSettingsConVars(menu);

		CTextEntry* textEntryRP = static_cast<CTextEntry*>(menu->UIPanel()->MustFindChildInLayoutFile("RPTextEntry")->ClientPtr());
		Settings::CustomStatus.SetValue(textEntryRP->PchGetText());
	}

	// for now we use dota events because we cant create our own yet
	void RegisterHandlers()
	{
		static CPanoramaSymbol symbolUninject = I::PanoramaEngine->AccessUIEngine()->MakeSymbol("DOTADisconnectClicked");
		static FastDelegate0<void> handlerUninject(Uninject);
		I::PanoramaEngine->AccessUIEngine()->RegisterEventHandlerClient(&symbolUninject, menu, handlerUninject.GetAbstractDelegate());

		static CPanoramaSymbol symbolRP = I::PanoramaEngine->AccessUIEngine()->MakeSymbol("DOTASearchTextSubmitted");
		static FastDelegate0<void> handlerRP(SetRichPresence);
		I::PanoramaEngine->AccessUIEngine()->RegisterEventHandlerClient(&symbolRP, menu, handlerRP.GetAbstractDelegate());

		static CPanoramaSymbol symbolSave = I::PanoramaEngine->AccessUIEngine()->MakeSymbol("DOTAApplyResolutionChoice");
		static FastDelegate0<void> handlerSave(Settings::Save);
		I::PanoramaEngine->AccessUIEngine()->RegisterEventHandlerClient(&symbolSave, menu, handlerSave.GetAbstractDelegate());
	}

	void Show()
	{
		manager = GetTopmostPopupManager();
		menu = new CUI_Popup(manager, nullptr, nullptr);
		if (!validVT)
			validVT = *reinterpret_cast<void**>(menu);

		menu->UIPanel()->MustLoadLayoutFromString(g_MenuXML, false, false);
		RegisterHandlers();
		CDOTA_DB_PopupSettings::CheckChildrenForSettingsConVars(menu);
		menu->UIPanel()->MustFindChildInLayoutFile("MovesTabButton")->SetSelected(true);
		CTextEntry* textEntryRP = static_cast<CTextEntry*>(menu->UIPanel()->MustFindChildInLayoutFile("RPTextEntry")->ClientPtr());
		textEntryRP->SetText(Settings::CustomStatus.GetString());

		manager->ShowPopup(menu);
	}

	inline void Close()
	{
		if (IsValid())
			manager->CloseAndDeletePopup(menu, 0.5f);
	}
}