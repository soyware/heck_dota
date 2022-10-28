#pragma once

#include "Cvar.h"
#include "Input.h"
#include "Panel.h"
#include "Surface.h"
#include "EntitySystem.h"
#include "Engine.h"
#include "SchemaSystem.h"
#include "Client.h"
#include "UIEngine.h"
#include "MemAlloc.h"
#include "KeyValues.h"
#include "MinimapObjectManager.h"
#include "InputService.h"

//class CSoundOpSystem;
class C_DOTAGamerules;
class CParticleSystemMgr;

namespace I
{
	CCvar*					Cvar;
	CInputSystem*			InputSystem;
	VPanelWrapper*			Panel;
	CVGuiRenderSurface*		Surface;
	//CSoundOpSystem*			SoundOpSystem;
	CSource2EntitySystem*	EntitySystem;
	CEngineClient*			EngineClient;
	CSchemaSystem*			SchemaSystem;
	CSource2Client*			Client;
	ClientModeDOTANormal*	ClientMode;
	CPanoramaUIEngine*		PanoramaEngine;
	CKeyValuesSystem*		KeyValuesSystem;
	CParticleSystemMgr*		ParticleSystemMgr;
	IMemAlloc*				MemAlloc;
	IInputService*			InputService;

	template <class T>
	T Find(const char* Module, const char* Interface)
	{
		typedef void* (*Fn) (const char*, int*);
		Fn CreateInterface = reinterpret_cast<Fn>(GetProcAddress(GetModuleHandle(Module), "CreateInterface"));
		if (CreateInterface)
		{
			for (unsigned int i = 1; i < 100; ++i)
			{
				char tmpName[32];
				sprintf_s(tmpName, sizeof(tmpName), "%s%03u", Interface, i);
				void* tmpInterface = CreateInterface(tmpName, 0);
				if (tmpInterface)
					return reinterpret_cast<T>(tmpInterface);
			}
		}
		FatalError("Interface not found");
		return 0;
	}

	void Init()
	{
		Cvar				= Find<CCvar*>("tier0.dll", "VEngineCvar");
		InputSystem			= Find<CInputSystem*>("inputsystem.dll", "InputSystemVersion");
		Panel				= Find<VPanelWrapper*>("vgui2.dll", "VGUI_Panel");
		Surface				= Find<CVGuiRenderSurface*>("vguirendersurface.dll", "VGUI_Surface");
		//SoundOpSystem		= Find<CSoundOpSystem*>("soundsystem.dll", "SoundOpSystem");
		EngineClient		= Find<CEngineClient*>("engine2.dll", "Source2EngineToClient");
		SchemaSystem		= Find<CSchemaSystem*>("schemasystem.dll", "SchemaSystem_");
		Client				= Find<CSource2Client*>("client.dll", "Source2Client");
		EntitySystem		= *reinterpret_cast<CSource2EntitySystem**>(RelativeToDirect(GetVF<uintptr_t>(Client, 25) + 3));
		ClientMode			= *reinterpret_cast<ClientModeDOTANormal**>(RelativeToDirect(GetVF<uintptr_t>(Client, 35) + 3));
		PanoramaEngine		= Find<CPanoramaUIEngine*>("panorama.dll", "PanoramaUIEngine");
		KeyValuesSystem		= reinterpret_cast<CKeyValuesSystem* (*)()>(GetProcAddress(GetModuleHandle("tier0.dll"), "KeyValuesSystem"))();
		ParticleSystemMgr	= Find<CParticleSystemMgr*>("particles.dll", "ParticleSystemMgr");
		MemAlloc			= *reinterpret_cast<IMemAlloc**>(GetProcAddress(GetModuleHandle("tier0.dll"), "g_pMemAlloc"));
		InputService		= Find<IInputService*>("engine2.dll", "InputService_");
	}
}