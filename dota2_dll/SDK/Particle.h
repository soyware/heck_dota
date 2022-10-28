#pragma once

enum ParticleAttachment_t
{
	PATTACH_INVALID = -1,
	PATTACH_ABSORIGIN = 0,
	PATTACH_ABSORIGIN_FOLLOW = 1,
	PATTACH_CUSTOMORIGIN = 2,
	PATTACH_CUSTOMORIGIN_FOLLOW = 3,
	PATTACH_POINT = 4,
	PATTACH_POINT_FOLLOW = 5,
	PATTACH_EYES_FOLLOW = 6,
	PATTACH_OVERHEAD_FOLLOW = 7,
	PATTACH_WORLDORIGIN = 8,
	PATTACH_ROOTBONE_FOLLOW = 9,
	PATTACH_RENDERORIGIN_FOLLOW = 10,
	PATTACH_MAIN_VIEW = 11,
	PATTACH_WATERWAKE = 12,
	PATTACH_CENTER_FOLLOW = 13,
	PATTACH_CUSTOM_GAME_STATE_1 = 14,
	PATTACH_HEALTHBAR = 15,
	MAX_PATTACH_TYPES = 16,
};

class CParticleCollection;

class CParticleSystemDefinition
{
public:
	inline CParticleCollection* FirstCollection()
	{
		typedef CParticleCollection* (__thiscall* Fn)(CParticleSystemDefinition*);
		return GetVF<Fn>(this, 1)(this);
	}
};

class CParticleCollection
{
public:
	inline int GetHighestControlPoint()
	{
		static const int offset = *reinterpret_cast<int*>(GetVF<uintptr_t>(this, 16) + 17);
		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	inline vec3* GetControlPointPosition(int cp)
	{
		typedef vec3*(__thiscall* Fn)(CParticleCollection*, int);
		return GetVF<Fn>(this, 21)(this, cp);
	}

	inline bool ReadsControlPoint(int cp)
	{
		typedef bool(__thiscall* Fn)(CParticleCollection*, int);
		return GetVF<Fn>(this, 26)(this, cp);
	}

	inline bool IsNonPositionalControlPoint(int cp)
	{
		typedef bool(__thiscall* Fn)(CParticleCollection*, int);
		return GetVF<Fn>(this, 27)(this, cp);
	}
};

class CNewParticleEffect
{
public:
	inline CParticleCollection* GetParticles()
	{
		return *reinterpret_cast<CParticleCollection**>(reinterpret_cast<uintptr_t>(this) + Schema::m_pParticles);
	}

	inline C_BaseEntity* GetOwner()
	{
		return I::EntitySystem->GetBaseEntityFromHandle(
			*reinterpret_cast<ULONG*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hOwner));
	}
};

class CDOTA_ParticleElement
{
public:
	std::byte pad_0x0000[0x10]; //0x0000
public:
	CNewParticleEffect* m_pParticleEffect; //0x0010 
private:
	std::byte pad_0x0018[0x8]; //0x0018
public:
	int32_t m_Index; //0x0020 
private:
	std::byte pad_0x0024[0xC]; //0x0024

}; //Size=0x0030


inline CNewParticleEffect* CDOTA_ParticleManager::GetParticleEffectByIndex(int index)
{
	auto particles = GetParticlesElements();
	for (int i = 0; i < particles->Count(); ++i)
	{
		if (particles->Element(i)->m_Index == index)
			return particles->Element(i)->m_pParticleEffect;
	}
	return nullptr;
}