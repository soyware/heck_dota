#pragma once

namespace Hooks
{
	extern CVTH hkMinigame;

	typedef void(__thiscall* RegisterEventHandlerClientFn)(IUIEngine*, CPanoramaSymbol*, CPanel2D*, CUtlAbstractDelegate);
	RegisterEventHandlerClientFn oRegisterEventHandlerClient;

	void RegisterEventHandlerClient(IUIEngine* _this, CPanoramaSymbol* event, CPanel2D* panel, CUtlAbstractDelegate handler)
	{
		oRegisterEventHandlerClient(_this, event, panel, handler);

		/*
		if (Settings::AutoMinigame.GetInt())
		{
			static CPanoramaSymbol meepoChooseSym = _this->MakeSymbol("DOTAWhackAMeepoChoose");
			static CPanoramaSymbol chairsChooseSym = _this->MakeSymbol("DOTAChairsChoose");
			static CPanoramaSymbol findChooseSym = _this->MakeSymbol("DOTAFindTheHeroesChoose");

			if (*event == meepoChooseSym || *event == chairsChooseSym || *event == findChooseSym)
			{
				if (!hkMinigame.IsHooked())
				{
					hkMinigame.Hook(panel);
					oMinigameDestructor = hkMinigame.AddHook<DestructorFn>(57, &MinigameDestructor);
					oMinigame = hkMinigame.AddHook<MinigameFn>(79, &Minigame);

					MinigameChooseFunc.SetAbstractDelegate(handler);
				}
				return;
			}
		}
		*/

		static CPanoramaSymbol acceptEvent = _this->MakeSymbol("DOTAPlayAcceptMatch");
		static CPanoramaSymbol acceptPanel = _this->MakeSymbol("PopupAcceptMatch");

		CPanoramaSymbol curPanel;
		panel->GetPanelType(curPanel);
		if (*event == acceptEvent && curPanel == acceptPanel)
		{
			CUtlDelegate<void(CUI_Popup*)> OnAcceptMatch;
			OnAcceptMatch.SetAbstractDelegate(handler);
			OnAcceptMatch(static_cast<CUI_Popup*>(panel));
		}
	}
}