#pragma once

class C_BaseEntity;

class C_DOTABaseGameMode : public C_BaseEntity
{
public:
	inline float GetIntelligenceSpellAmpPercent()
	{
		return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + Schema::m_flIntelligenceSpellAmpPercent);
	}
};

class C_DOTAGamerules : public C_BaseEntity
{
public:
	inline C_DOTABaseGameMode* GetGameModeEntity()
	{
		return reinterpret_cast<C_DOTABaseGameMode*>(I::EntitySystem->GetBaseEntityFromHandle(
			*reinterpret_cast<unsigned long*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hGameModeEntity)));
	}

	inline float GetGameTime()
	{
		return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + Schema::m_fGameTime);
	}

	inline C_BaseEntity* GetFountain(DOTATeam_t team)
	{
		return reinterpret_cast<C_DOTABaseGameMode*>(I::EntitySystem->GetBaseEntityFromHandle(
			reinterpret_cast<unsigned long*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hTeamFountains)[team]));
	}
};