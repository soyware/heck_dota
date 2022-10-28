#pragma once

class C_DOTA_BaseNPC : public C_BaseEntity
{
public:
	inline bool IsHero()
	{
		return *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + Schema::m_iUnitType) & (1 << 0);
	}

	inline bool IsCreep()
	{
		return *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + Schema::m_iUnitType) & (1 << 7);
	}

	inline bool IsWard()
	{
		return *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + Schema::m_iUnitType) & (1 << 17);
	}

	inline modifierstate GetUnitState()
	{
		return *reinterpret_cast<modifierstate*>(reinterpret_cast<uintptr_t>(this) + Schema::m_nUnitState64);
	}

	inline bool IsInState(modifierstate state)
	{
		return GetUnitState() & (1i64 << state);
	}

	inline float GetMana()
	{
		return floor(*reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + Schema::m_flMana) + 0.1f);
	}

	inline unsigned long* GetAbilities()
	{
		return reinterpret_cast<unsigned long*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hAbilities);
	}

	inline C_DOTABaseAbility* GetAbilityByIndex(int index)
	{
		return static_cast<C_DOTABaseAbility*>(I::EntitySystem->GetBaseEntityFromHandle(GetAbilities()[index]));
	}

	inline C_DOTABaseAbility* FindAbilityByName(const char* name)
	{
		for (UINT i = 0; i < 31; ++i)
		{
			C_DOTABaseAbility* ability = GetAbilityByIndex(i);
			if (ability && !strcmp(ability->m_pIdentity->m_name, name))
				return ability;
		}
		return nullptr;
	}

	inline CDOTA_ModifierManager* GetModifierManager()
	{
		return reinterpret_cast<CDOTA_ModifierManager*>(reinterpret_cast<uintptr_t>(this) + Schema::m_ModifierManager);
	}

	inline CDOTA_Buff* FindModifierByName(const char* name)
	{
		CDOTA_ModifierManager* manager = GetModifierManager();
		for (int i = 0; i < manager->m_pBuffs.Count(); ++i)
		{
			if (!strcmp(manager->m_pBuffs[i]->GetName(), name))
				return manager->m_pBuffs[i];
		}
		return nullptr;
	}

	inline C_DOTA_UnitInventory* GetInventory()
	{
		return reinterpret_cast<C_DOTA_UnitInventory*>(reinterpret_cast<uintptr_t>(this) + Schema::m_Inventory);
	}

	inline C_DOTA_Item* FindItemByName(const char* name)
	{
		C_DOTA_UnitInventory* inventory = GetInventory();
		for (UINT i = 0; i < 19; ++i)
		{
			C_DOTA_Item* item = inventory->GetItemByIndex(i);
			if (item && !strcmp(item->m_pIdentity->m_name, name))
				return item;
		}
		return nullptr;
	}

	// C_DOTA_BaseNPC -> "ManhackCut" + 4
	// 48 89 5C 24 08 57 48 83 EC 20 48 8B 05 ? ? ? ? 8B FA
	inline bool CanBeSeenByTeam(DOTATeam_t team)
	{
		typedef bool(__thiscall* Fn)(void*, DOTATeam_t);
		return GetVF<Fn>(this, 209)(this, team);
	}

	inline float GetPhysicalArmorValue()
	{
		typedef float(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 292)(this);
	}

	inline float GetMagicalArmorValue()
	{
		typedef float(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 293)(this);
	}

	inline float GetIdealSpeed()
	{
		typedef float(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 297)(this);
	}

	// C_DOTA_BaseNPC -> "modifier_affects_abilities" + 1
	inline bool IsIllusion()
	{
		typedef bool(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 373)(this);
	}

	inline int GetOutgoingSpellDamage(int damage)
	{
		CDOTA_ModifierManager* modifierManager = GetModifierManager();

		float outDmg = modifierManager->GetModifier_Percentage_Additive_Internal(
			MODIFIER_PROPERTY_TOTALDAMAGEOUTGOING_PERCENTAGE, CModifierParams::s_Default(), false, false);

		return damage * (1.f + GetSpellAmp()) * outDmg;
	}

	inline int GetIncomingDamage(DAMAGE_TYPES type, int damage)
	{
		CDOTA_ModifierManager* modifierManager = GetModifierManager();

		float out = modifierManager->GetModifier_Percentage_Additive_Internal(
			MODIFIER_PROPERTY_INCOMING_DAMAGE_PERCENTAGE, CModifierParams::s_Default(), false, false);

		if (type == DAMAGE_TYPE_PHYSICAL)
			out -= GetPhysicalArmorValue();
		else if (type == DAMAGE_TYPE_MAGICAL)
			out -= GetMagicalArmorValue();

		return damage * out;
	}

	inline float GetSpellAmp()
	{
		// 7.26 Intelligence no longer grants 0.07 % spell damage amplification per point.
		//float out = *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + Schema::m_flIntellectTotal);

		//if ((*G::pGameRules) && (*G::pGameRules)->GetGameModeEntity())
		//	out *= (*G::pGameRules)->GetGameModeEntity()->GetIntelligenceSpellAmpPercent();
		//else
		//	out *= 0.07f;

		CDOTA_ModifierManager* modifierManager = GetModifierManager();
		float out = modifierManager->GetModifier_Constant_Additive_Internal(
			MODIFIER_PROPERTY_SPELL_AMPLIFY_PERCENTAGE, CModifierParams::s_Default(), false);
		out += modifierManager->GetModifier_Constant_Highest_Internal(
			MODIFIER_PROPERTY_SPELL_AMPLIFY_PERCENTAGE_UNIQUE, CModifierParams::s_Default());

		return out * 0.01f;
	}

	//void GetAbilityModifierValues(const char* name, float& add, float& multiply)
	//{
	//	add = 0.f;
	//	multiply = 1.f;

	//	CDOTA_ModifierManager* modMng = GetModifierManager();
	//	if (modMng->m_ModFuncIndexes[MODIFIER_PROPERTY_CHANGE_ABILITY_VALUE] == -1 || 
	//		modMng->m_pModFuncs.m_pElements[modMng->m_ModFuncIndexes[MODIFIER_PROPERTY_CHANGE_ABILITY_VALUE]].m_Size <= 0)
	//		return;

	//	if (modMng->m_pBuffs.m_Size <= 0)
	//		return;

	//	for (int i = 0; i < modMng->m_pBuffs.m_Size; ++i)
	//	{
	//		CDOTA_Buff* buff = modMng->m_pBuffs.m_pElements[i];
	//		if (buff && !buff->IsMarkedForDeletion() && *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(buff) + 1696))
	//		{
	//			C_DOTABaseAbility* ability = buff->GetAbility();
	//			if (ability)
	//			{

	//			}
	//		}
	//	}
	//}

	inline bool HasModifier(modifierfunction fn)
	{
		int index = GetModifierManager()->m_ModFuncIndexes[fn];
		return (index != -1 && 0 < GetModifierManager()->m_pModFuncs[index].Count());
	}

	// seems to be used to differ fake meepos
	inline bool bIsIllusion()
	{
		return *reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + Schema::m_bIsIllusion);
	}

	inline bool HasClientSeenIllusionModifier()
	{
		return *reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + Schema::m_bHasClientSeenIllusionModifier);
	}

	inline bool HasScepter()
	{
		if (*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + Schema::m_bStolenScepter))
			return true;

		return HasModifier(MODIFIER_PROPERTY_IS_SCEPTER);
	}

	inline bool IsBlockingSpells()
	{
		return HasModifier(MODIFIER_PROPERTY_ABSORB_SPELL) || HasModifier(MODIFIER_PROPERTY_REFLECT_SPELL);
	}
};

class C_DOTA_BaseNPC_Hero : public C_DOTA_BaseNPC
{
public:
	inline ULONG ReplicatingOtherHeroModel()
	{
		return *reinterpret_cast<ULONG*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hReplicatingOtherHeroModel);
	}

	inline bool GhettoIsIllusion()
	{
		return bIsIllusion() ||
			HasClientSeenIllusionModifier() ||
			(ReplicatingOtherHeroModel() != -1 && 
				GetClientClass()->m_ClassID != ClassID::C_DOTA_Unit_Hero_Meepo && 
				(GetClientClass()->m_ClassID != ClassID::C_DOTA_Unit_Hero_Morphling || 
					!FindModifierByName("modifier_morphling_replicate")));
	}

	inline bool IsRealHero()
	{
		return IsHero() && !GhettoIsIllusion();
	}
};

int C_DOTABaseAbility::GetAbilityDamage()
{
	int talantBonus = 0;

	DOTASpecialAbility_t* dmgSpec;
	C_DOTA_BaseNPC* caster = static_cast<C_DOTA_BaseNPC*>(GetOwnerEntity());
	if (caster->HasScepter())
		dmgSpec = GetSpecialAbility("damage_scepter");
	else
		dmgSpec = GetSpecialAbility("damage");

	if (dmgSpec && dmgSpec->m_pszSpecialBonusAbility)
	{
		C_DOTABaseAbility* talantAbil = caster->FindAbilityByName(dmgSpec->m_pszSpecialBonusAbility);
		if (talantAbil)
		{
			const char* bonusFieldName;
			if (dmgSpec->m_pszSpecialBonusField)
				bonusFieldName = dmgSpec->m_pszSpecialBonusField;
			else
				bonusFieldName = "value";

			talantBonus = talantAbil->GetLevelSpecialValueFor<int>(bonusFieldName);
		}
	}

	typedef int(__thiscall* Fn)(C_DOTABaseAbility*);
	return GetVF<Fn>(this, 279)(this) + talantBonus;
}

enum CourierState_t
{
	COURIER_STATE_INIT					= -1,
	COURIER_STATE_IDLE					= 0,
	COURIER_STATE_AT_BASE				= 1,
	COURIER_STATE_MOVING				= 2,
	COURIER_STATE_DELIVERING_ITEMS		= 3,
	COURIER_STATE_RETURNING_TO_BASE		= 4,
	COURIER_STATE_DEAD					= 5,
	COURIER_NUM_STATES
};

class C_DOTA_Unit_Courier : public C_DOTA_BaseNPC
{
public:
	inline CourierState_t GetCourierState()
	{
		return *reinterpret_cast<CourierState_t*>(reinterpret_cast<uintptr_t>(this) + Schema::m_nCourierState);
	}
};