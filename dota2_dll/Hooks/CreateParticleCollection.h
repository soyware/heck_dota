#pragma once

namespace Hooks
{
	typedef CParticleCollection* (__thiscall* CreateParticleCollectionFn)(CParticleSystemMgr*, void*, void*, void*, bool, float, int);
	CreateParticleCollectionFn oCreateParticleCollection;

	CParticleCollection* CreateParticleCollection(CParticleSystemMgr* _this, void* definition, void* a3, void* query, bool a5, float flDelay, int randomSeed)
	{
		CParticleCollection* ret = oCreateParticleCollection(_this, definition, a3, query, a5, flDelay, randomSeed);

		if (Interfaces::EngineClient->IsInGame())
			Features::ParticleMaphack::Add2(ret);

		return ret;
	}
}