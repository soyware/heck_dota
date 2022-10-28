#pragma once

enum ParticleAttachment_t : int;
class CDOTA_ParticleElement;
class CNewParticleEffect;

struct CreateParticleArgs
{
	const char* m_name;
	ParticleAttachment_t m_flags;
	C_BaseEntity* m_parent;
	CRecipientFilter* m_filter;
	C_BaseEntity* m_caster;
	int m_unk1;
	bool m_voice;

	CreateParticleArgs(const char* name, ParticleAttachment_t flags, C_BaseEntity* parent, CRecipientFilter* filter, C_BaseEntity* caster)
	{
		m_name = name;
		m_flags = flags;
		m_parent = parent;
		m_filter = filter;
		m_caster = caster;
		m_unk1 = 0;
		m_voice = false;
	}
};

class CDOTA_ParticleManager
{
public:
	inline CUtlVector<CDOTA_ParticleElement*>* GetParticlesElements()
	{
		return reinterpret_cast<CUtlVector<CDOTA_ParticleElement*>*>(reinterpret_cast<uintptr_t>(this) + 0x88);
	}

	inline CNewParticleEffect* GetParticleEffectByIndex(int index);

	inline int NewParticleIndex()
	{
		return (*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0xA0))++;
	}

	inline void CreateParticle(int index, const char* name, ParticleAttachment_t flags, C_BaseEntity* parent, C_BaseEntity* caster)
	{
		CreateParticleArgs particle(name, flags, parent, nullptr, caster);

		typedef void(__thiscall* Fn)(CDOTA_ParticleManager*, int, CreateParticleArgs*);
		GetVF<Fn>(this, 7)(this, index, &particle);
	}
};