#pragma once

namespace Hooks
{
	typedef void(__thiscall* DestructorFn)(void*, bool);

	typedef void(__thiscall* VoidThiscallFn)(void*);
	void EmptyVoidThiscall(void*) {	}
}

#include "PaintTraverse.h"
//#include "StartSoundEvent.h"
//#include "MinimapRenderer.h"
#include "ParticleManager.h"
#include "CreateMove.h"
#include "FindVar.h"
//#include "Minigames.h"
#include "RegisterEventHandlerClient.h"
#include "RPUpdate.h"
//#include "CreateParticleCollection.h"

namespace Hooks
{
	CVTH hkPanel;
	//CVTH hkSoundOpSystem;
	//CVTH* hkMinimapRenderer;
	CVTH hkParticleManager;
	CVTH hkClientMode;
	CVTH hkCvar;
	CVTH hkUIEngine;
	CVTH hkRichPresence;
	//CVTH hkParticleSystemMgr;
	CVTH hkMinigame;

	void Init()
	{
		hkPanel.Init(I::Panel, "vgui2.dll");
		oPaintTraverse = hkPanel.Hook<PaintTraverseFn>(55, &PaintTraverse);

		//hkSoundOpSystem.Init(Interfaces::SoundOpSystem, "soundsystem.dll");
		//oStartSoundEventName = hkSoundOpSystem.Hook<StartSoundEventNameFn>(12, &StartSoundEventName);

		//hkMinimapRenderer = nullptr;

		hkClientMode.Init(I::ClientMode, "client.dll");
		oCreateMove = hkClientMode.Hook<CreateMoveFn>(26, &CreateMove); // above "mapname"

		hkCvar.Init(I::Cvar, "tier0.dll");
		oFindVar = hkCvar.Hook<FindVarFn>(19, &FindVar);

		hkUIEngine.Init(I::PanoramaEngine->AccessUIEngine(), "panorama.dll");
		oRegisterEventHandlerClient = hkUIEngine.Hook<RegisterEventHandlerClientFn>(40, &RegisterEventHandlerClient); // above "CUIEngine::RegisterEventHandler"
#ifdef _DEBUG
		hkUIEngine.Hook<VoidThiscallFn>(28, &EmptyVoidThiscall); // disable Panorama Debugger
#endif // _DEBUG

		hkRichPresence.Init(G::RichPresence, "client.dll");
		oRPUpdate = hkRichPresence.Hook<RPUpdateFn>(23, &RPUpdate);

		//hkParticleSystemMgr.Init(Interfaces::ParticleSystemMgr, "particles.dll");
		//oCreateParticleCollection = hkParticleSystemMgr.Hook<CreateParticleCollectionFn>(17, &CreateParticleCollection);
	}

	void Unhook()
	{
		hkPanel.Unhook();
		//hkSoundOpSystem.Unhook();
		//delete hkMinimapRenderer;
		hkParticleManager.Unhook();
		hkClientMode.Unhook();
		hkCvar.Unhook();
		hkUIEngine.Unhook();
		hkRichPresence.Unhook();
		//hkParticleSystemMgr.Unhook();
		hkMinigame.Unhook();
	}
}