#pragma once

class C_DOTA_BaseNPC;
class C_DOTA_BaseNPC_Hero;

enum DAMAGE_TYPES
{
	DAMAGE_TYPE_NONE		= 0x0,
	DAMAGE_TYPE_PHYSICAL	= 0x1,
	DAMAGE_TYPE_MAGICAL		= 0x2,
	DAMAGE_TYPE_PURE		= 0x4,
	DAMAGE_TYPE_HP_REMOVAL	= 0x8,
	DAMAGE_TYPE_ALL			= 0x7,
};

enum EDOTASpecialBonusOperation
{
	SPECIAL_BONUS_ADD = 0,
	SPECIAL_BONUS_MULTIPLY = 1,
	SPECIAL_BONUS_SUBTRACT = 2,
	SPECIAL_BONUS_PERCENTAGE_ADD = 3,
	SPECIAL_BONUS_PERCENTAGE_SUBTRACT = 4,
};

class DOTASpecialAbility_t
{
public:
	char* m_pszName; //0x0000 
	char* m_pszValue; //0x0008 
	char* m_pszLevelKey; //0x0010 
	char* m_pszSpecialBonusAbility; //0x0018 LinkedSpecialBonus
	char* m_pszSpecialBonusField; //0x0020 LinkedSpecialBonusField
	fieldtype_t m_FieldType; //0x0028 
private:
	std::byte pad_0x0029[0x3]; //0x0029
public:
	int32_t m_nCount; //0x002C 
	CVariantBase m_Values[20]; //0x0030 
	bool m_bSpellDamageField; //0x0170 CalculateSpellDamageTooltip || name contains "damage"
	bool m_bScepterField; //0x0171 RequiresScepter
private:
	std::byte pad_0x0172[0x2];
public:
	EDOTASpecialBonusOperation m_eSpecialBonusOperation; //0x0174 LinkedSpecialBonusOperation

}; //Size=0x0178

class DOTAAbilityDefinition_t
{
public:
	inline DOTASpecialAbility_t* GetSpecialAbilities()
	{
		return *reinterpret_cast<DOTASpecialAbility_t**>(reinterpret_cast<uintptr_t>(this) + Schema::m_pSpecialAbilities);
	}

	inline int GetSpecialAbiltiesCount()
	{
		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + Schema::m_nSpecialAbilities);
	}
};

enum UnitFilterResult
{
	UF_SUCCESS = 0,
	UF_FAIL_FRIENDLY = 1,
	UF_FAIL_ENEMY = 2,
	UF_FAIL_HERO = 3,
	UF_FAIL_CONSIDERED_HERO = 4,
	UF_FAIL_CREEP = 5,
	UF_FAIL_BUILDING = 6,
	UF_FAIL_COURIER = 7,
	UF_FAIL_OTHER = 8,
	UF_FAIL_ANCIENT = 9,
	UF_FAIL_ILLUSION = 10,
	UF_FAIL_SUMMONED = 11,
	UF_FAIL_DOMINATED = 12,
	UF_FAIL_MELEE = 13,
	UF_FAIL_RANGED = 14,
	UF_FAIL_DEAD = 15,
	UF_FAIL_MAGIC_IMMUNE_ALLY = 16,
	UF_FAIL_MAGIC_IMMUNE_ENEMY = 17,
	UF_FAIL_INVULNERABLE = 18,
	UF_FAIL_IN_FOW = 19,
	UF_FAIL_INVISIBLE = 20,
	UF_FAIL_NOT_PLAYER_CONTROLLED = 21,
	UF_FAIL_ATTACK_IMMUNE = 22,
	UF_FAIL_CUSTOM = 23,
	UF_FAIL_INVALID_LOCATION = 24,
	UF_FAIL_DISABLE_HELP = 25,
	UF_FAIL_OUT_OF_WORLD = 26,
	UF_FAIL_NIGHTMARED = 27,
	UF_FAIL_OBSTRUCTED = 28,
};

enum DOTA_ABILITY_BEHAVIOR : uint64_t
{
	DOTA_ABILITY_BEHAVIOR_NONE               = 0x0,
	DOTA_ABILITY_BEHAVIOR_HIDDEN             = 0x1,
	DOTA_ABILITY_BEHAVIOR_PASSIVE            = 0x2,
	DOTA_ABILITY_BEHAVIOR_NO_TARGET          = 0x4,
	DOTA_ABILITY_BEHAVIOR_UNIT_TARGET        = 0x8,
	DOTA_ABILITY_BEHAVIOR_POINT              = 0x10,
	DOTA_ABILITY_BEHAVIOR_AOE                = 0x20,
	DOTA_ABILITY_BEHAVIOR_NOT_LEARNABLE      = 0x40,
	DOTA_ABILITY_BEHAVIOR_CHANNELLED         = 0x80,
	DOTA_ABILITY_BEHAVIOR_ITEM               = 0x100,
	DOTA_ABILITY_BEHAVIOR_TOGGLE             = 0x200,
	DOTA_ABILITY_BEHAVIOR_DIRECTIONAL        = 0x400,
	DOTA_ABILITY_BEHAVIOR_IMMEDIATE          = 0x800,
	DOTA_ABILITY_BEHAVIOR_AUTOCAST           = 0x1000,
	DOTA_ABILITY_BEHAVIOR_OPTIONAL_UNIT_TARGET = 0x2000,
	DOTA_ABILITY_BEHAVIOR_OPTIONAL_POINT     = 0x4000,
	DOTA_ABILITY_BEHAVIOR_OPTIONAL_NO_TARGET = 0x8000,
	DOTA_ABILITY_BEHAVIOR_AURA               = 0x10000,
	DOTA_ABILITY_BEHAVIOR_ATTACK             = 0x20000,
	DOTA_ABILITY_BEHAVIOR_DONT_RESUME_MOVEMENT = 0x40000,
	DOTA_ABILITY_BEHAVIOR_ROOT_DISABLES      = 0x80000,
	DOTA_ABILITY_BEHAVIOR_UNRESTRICTED       = 0x100000,
	DOTA_ABILITY_BEHAVIOR_IGNORE_PSEUDO_QUEUE = 0x200000,
	DOTA_ABILITY_BEHAVIOR_IGNORE_CHANNEL     = 0x400000,
	DOTA_ABILITY_BEHAVIOR_DONT_CANCEL_MOVEMENT = 0x800000,
	DOTA_ABILITY_BEHAVIOR_DONT_ALERT_TARGET  = 0x1000000,
	DOTA_ABILITY_BEHAVIOR_DONT_RESUME_ATTACK = 0x2000000,
	DOTA_ABILITY_BEHAVIOR_NORMAL_WHEN_STOLEN = 0x4000000,
	DOTA_ABILITY_BEHAVIOR_IGNORE_BACKSWING   = 0x8000000,
	DOTA_ABILITY_BEHAVIOR_RUNE_TARGET        = 0x10000000,
	DOTA_ABILITY_BEHAVIOR_DONT_CANCEL_CHANNEL = 0x20000000,
	DOTA_ABILITY_BEHAVIOR_VECTOR_TARGETING   = 0x40000000,
	DOTA_ABILITY_BEHAVIOR_LAST_RESORT_POINT  = 0x80000000,
	DOTA_ABILITY_BEHAVIOR_CAN_SELF_CAST      = 0x100000000,
	DOTA_ABILITY_BEHAVIOR_SHOW_IN_GUIDES     = 0x200000000,
	DOTA_ABILITY_BEHAVIOR_UNLOCKED_BY_EFFECT_INDEX = 0x400000000,
	DOTA_ABILITY_BEHAVIOR_SUPPRESS_ASSOCIATED_CONSUMABLE = 0x800000000,
	DOTA_ABILITY_BEHAVIOR_FREE_DRAW_TARGETING = 0x1000000000,
	DOTA_ABILITY_BEHAVIOR_IGNORE_SILENCE     = 0x2000000000,
};

class C_DOTABaseAbility : public C_BaseEntity
{
public:
	inline DOTA_ABILITY_BEHAVIOR GetBehavior()
	{
		typedef DOTA_ABILITY_BEHAVIOR(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 200)(this);
	}

	// GetManaCost + 1
	inline int GetEffectiveManaCost(int level = -1)
	{
		typedef int(__thiscall* Fn)(void*, int);
		return GetVF<Fn>(this, 205)(this, level);
	}

	// find "CUSTOM ERROR" of C_DOTA_Ability_Lina_LagunaBlade, function which returns 3 above it, before function which returns 4
	inline DAMAGE_TYPES GetCurrentAbilityDamageType()
	{
		typedef DAMAGE_TYPES(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 209)(this);
	}

	inline float GetCastPoint()
	{
		typedef float(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 212)(this);
	}

	// GetCastPoint + 2
	inline UnitFilterResult CastFilterResult()
	{	
		typedef UnitFilterResult(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 214)(this);
	}

	inline UnitFilterResult CastFilterResult(const vec3& location)
	{
		typedef UnitFilterResult(__thiscall* Fn)(void*, const vec3&);
		return GetVF<Fn>(this, 215)(this, location);
	}

	// find "modifier_gyrocopter_homing_missile" of CDOTA_Item_ForceStaff
	inline UnitFilterResult CastFilterResult(C_DOTA_BaseNPC* target)
	{
		typedef UnitFilterResult(__thiscall* Fn)(void*, C_DOTA_BaseNPC*);
		return GetVF<Fn>(this, 216)(this, target);
	}

	// GetCooldown + 2
	// cooldown length
	inline float GetEffectiveCooldown(int level = -1)
	{
		typedef float(__thiscall* Fn)(void*, int);
		return GetVF<Fn>(this, 226)(this, level);
	}

	// GetCooldownTime + 1
	// cooldown left
	inline float GetCooldownTime()
	{
		typedef float(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 227)(this);
	}

	inline bool CanBeExecuted()
	{
		typedef int(__thiscall* Fn)(void*);
		return (GetVF<Fn>(this, 233)(this) == -1);
	}

	// GetCastRange + 2
	inline int GetEffectiveCastRange(vec3* location = nullptr, C_DOTA_BaseNPC* target = nullptr)
	{
		static vec3 vec_zero;
		typedef int(__thiscall* Fn)(void*, vec3*, C_DOTA_BaseNPC*);
		return GetVF<Fn>(this, 249)(this, location ? location : &vec_zero, target);
	}

	// find "damage" of C_DOTA_Ability_Lina_LagunaBlade
	int GetAbilityDamage();

	inline int GetLevel()
	{
		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + Schema::m_iLevel);
	}

	inline DOTAAbilityDefinition_t* GetAbilityData()
	{
		return *reinterpret_cast<DOTAAbilityDefinition_t**>(reinterpret_cast<uintptr_t>(this) + Schema::m_pAbilityData);
	}

	inline DOTASpecialAbility_t* GetSpecialAbility(const char* name, bool substring = false)
	{
		DOTAAbilityDefinition_t* abilityData = GetAbilityData();
		DOTASpecialAbility_t* abilities = abilityData->GetSpecialAbilities();
		int count = abilityData->GetSpecialAbiltiesCount();
		for (int i = 0; i < count; ++i)
		{
			if (substring)
			{
				if (strstr(abilities[i].m_pszName, name))
					return &abilities[i];
			}
			else if (!strcmp(abilities[i].m_pszName, name))
				return &abilities[i];
		}
		return nullptr;
	}

	template <class T>
	T GetLevelSpecialValueFor(const char* name, bool substring = false, int level = -1)
	{
		if (level == -1)
		{
			level = GetLevel() - 1;
			if (level == -1)
				return 0.f;
		}

		//float add = 0.f;
		//float multiply = 1.f;
		//C_DOTA_BaseNPC* caster = GetOwnerEntity();
		//if (caster)
		//	caster->GetAbilityModifierValues(name, &add, &multiply);

		DOTASpecialAbility_t* specialAbility = GetSpecialAbility(name, substring);
		if (!specialAbility)
			return 0.f;

		if (level > specialAbility->m_nCount - 1)
			level = specialAbility->m_nCount - 1;

		if (specialAbility->m_FieldType == FIELD_FLOAT32)
		{
			if (specialAbility->m_Values[level].m_type == FIELD_FLOAT64)
				return *reinterpret_cast<double*>(&specialAbility->m_Values[level].m_value);
			else
				return *reinterpret_cast<float*>(&specialAbility->m_Values[level].m_value);
		}
		else if (specialAbility->m_FieldType == FIELD_INT32)
		{
			if (specialAbility->m_Values[level].m_type == FIELD_FLOAT32)
				return *reinterpret_cast<float*>(&specialAbility->m_Values[level].m_value);
			else if (specialAbility->m_Values[level].m_type == FIELD_FLOAT64)
				return *reinterpret_cast<double*>(&specialAbility->m_Values[level].m_value);
			else
				return *reinterpret_cast<int32_t*>(&specialAbility->m_Values[level].m_value);
		}
		return 0.f;
	}
};