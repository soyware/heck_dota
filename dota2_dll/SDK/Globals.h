#pragma once

#include "GlobalVars.h"
#include "ParticleManager.h"
#include "RichPresence.h"
#include "HudIcons.h"

namespace G
{
	CGlobalVars**			pGlobals;
	C_DOTAGamerules**		pGameRules;
	CDOTA_ParticleManager**	pParticleManager;
	CDOTARichPresence*		RichPresence;
	CHudIcons*				HudIcons;

	void Init()
	{
		pGlobals			= reinterpret_cast<CGlobalVars**>(RelativeToDirect(GetVF<uintptr_t>(I::Client, 11) + 3));
		pGameRules			= reinterpret_cast<C_DOTAGamerules**>(RelativeToDirect(GetVF<uintptr_t>(I::ClientMode, 17) + 41));
		pParticleManager	= reinterpret_cast<CDOTA_ParticleManager**>(Signatures::pParticleManager);
		RichPresence		= reinterpret_cast<CDOTARichPresence*>(Signatures::s_RichPresence);
		HudIcons			= reinterpret_cast<CHudIcons*>(Signatures::g_HudIcons);
	}
}