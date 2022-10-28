#pragma once

namespace Hooks
{
	extern CVTH hkParticleManager;

	DestructorFn oParticleManagerDestructor;

	void ParticleManagerDestructor(CDOTA_ParticleManager* _this, bool del)
	{
		hkParticleManager.Unhook();

		oParticleManagerDestructor(_this, del);
	}

	typedef void(__thiscall* CreateParticleEffectInternalFn)(CDOTA_ParticleManager*, int, CParticleSystemDefinition***, CreateParticleArgs*);
	CreateParticleEffectInternalFn oCreateParticleEffectInternal;

	void CreateParticleEffectInternal(CDOTA_ParticleManager* _this, int index, CParticleSystemDefinition*** definition, CreateParticleArgs* args)
	{
		oCreateParticleEffectInternal(_this, index, definition, args);

		Features::ParticleMaphack::Add(definition, args);
	}
}