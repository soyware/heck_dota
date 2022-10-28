#pragma once

namespace Schema
{
	int GetFieldOffset(const char* modName, const char* className, const char* varName)
	{
		CSchemaSystemTypeScope* scope = (modName ? I::SchemaSystem->FindTypeScopeForModule(modName) : I::SchemaSystem->GlobalTypeScope());
		if (scope)
		{
			SchemaClassInfoData_t* classInfo = scope->FindDeclaredClass(className);
			if (classInfo)
			{
				for (int16_t i = 0; i < classInfo->m_FieldCount; ++i)
				{
					if (!strcmp(classInfo->m_Fields[i].m_Name, varName))
					{
#ifdef _DEBUG
						Log::Msg("%s::%s -> 0x%X\n", className, varName, classInfo->m_Fields[i].m_Offset);
#endif // _DEBUG
						return classInfo->m_Fields[i].m_Offset;
					}
				}
			}
		}
		FatalError("Couldn't get schema field");
		return 0;
	}

	uintptr_t GetStaticMember(const char* modName, const char* className, const char* varName)
	{
		CSchemaSystemTypeScope* scope = (modName ? I::SchemaSystem->FindTypeScopeForModule(modName) : I::SchemaSystem->GlobalTypeScope());
		if (scope)
		{
			SchemaClassInfoData_t* classInfo = scope->FindDeclaredClass(className);
			if (classInfo)
			{
				for (int16_t i = 0; i < classInfo->m_staticMemberCount; ++i)
				{
					if (!strcmp(classInfo->m_staticMembers[i].m_Name, varName))
					{
#ifdef _DEBUG
						Log::Msg("%s::%s -> 0x%p\n", className, varName, classInfo->m_staticMembers[i].m_pInstance);
#endif // _DEBUG
						return reinterpret_cast<uintptr_t>(classInfo->m_staticMembers[i].m_pInstance);
					}
				}
			}
		}
		FatalError("Couldn't get schema static member");
		return 0;
	}


	void RegisterSchemaCommands()
	{
		for (unsigned int i = 0; i < 6; ++i)
		{
			CConCommandMemberAccessor<CSchemaSystem>* command = reinterpret_cast<CConCommandMemberAccessor<CSchemaSystem>*>(
				reinterpret_cast<uintptr_t>(I::SchemaSystem) + 0x38 + i * sizeof(CConCommandMemberAccessor<CSchemaSystem>));

			command->m_nFlags &= ~FCVAR_DEVELOPMENTONLY;
			I::Cvar->RegisterConCommand(command);
		}
	}

	int m_vecAbsOrigin,

		m_pGameSceneNode,
		m_iHealth,
		m_lifeState,
		m_iTeamNum,
		m_hOwnerEntity,
		m_flLastMessageTime,
		m_somethinglikenpctype,

		m_iUnitType,
		m_bStolenScepter,
		m_flMana,
		m_hAbilities,
		m_ModifierManager,
		m_Inventory,
		m_nUnitState64,
		m_bIsIllusion,
		m_bHasClientSeenIllusionModifier,

		m_flIntellectTotal,
		m_hReplicatingOtherHeroModel,

		m_nCourierState,

		m_hAssignedHero,
		
		m_SharedCooldownList,
		m_hItems,

		m_iRuneType,

		m_name,
		m_flDuration,
		m_flDieTime,
		m_hCaster,
		m_hAbility,
		m_hParent,
		m_iStackCount,
		//m_bAuraFlags,
		//m_hAuraUnits,

		m_pAbilityData,
		m_iLevel,

		m_nSpecialAbilities,
		m_pSpecialAbilities,

		m_pszName,
		m_FieldType,
		m_nCount,
		m_Values,
		
		m_hGameModeEntity,
		m_hTeamFountains,
		m_fGameTime,

		m_pParticles,
		m_hOwner,

		m_flIntelligenceSpellAmpPercent;

	uintptr_t CModifierParams__s_Default;

	void Init()
	{
#ifdef _DEBUG
		Schema::RegisterSchemaCommands();

		Log::Msg("--- Schema ---\n");
#endif // _DEBUG
		m_vecAbsOrigin					= GetFieldOffset("client.dll", "CGameSceneNode", "m_vecAbsOrigin");

		m_pGameSceneNode				= GetFieldOffset("client.dll", "C_BaseEntity", "m_pGameSceneNode");
		m_iHealth						= GetFieldOffset("client.dll", "C_BaseEntity", "m_iHealth");
		m_lifeState						= GetFieldOffset("client.dll", "C_BaseEntity", "m_lifeState");
		m_iTeamNum						= GetFieldOffset("client.dll", "C_BaseEntity", "m_iTeamNum");
		m_hOwnerEntity					= GetFieldOffset("client.dll", "C_BaseEntity", "m_hOwnerEntity");
		m_flLastMessageTime				= GetFieldOffset("client.dll", "C_BaseEntity", "m_flLastMessageTime");
		m_somethinglikenpctype			= GetFieldOffset("client.dll", "C_BaseEntity", "m_bAnimTimeChanged") - 1;

		m_iUnitType						= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_iUnitType");
		m_bStolenScepter				= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_bStolenScepter");
		m_flMana						= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_flMana");
		m_hAbilities					= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_hAbilities");
		m_ModifierManager				= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_ModifierManager");
		m_Inventory						= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_Inventory");
		m_nUnitState64					= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_nUnitState64");
		m_bIsIllusion					= GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_bIsIllusion");
		m_bHasClientSeenIllusionModifier = GetFieldOffset("client.dll", "C_DOTA_BaseNPC", "m_bHasClientSeenIllusionModifier");

		m_flIntellectTotal				= GetFieldOffset("client.dll", "C_DOTA_BaseNPC_Hero", "m_flIntellectTotal");
		m_hReplicatingOtherHeroModel	= GetFieldOffset("client.dll", "C_DOTA_BaseNPC_Hero", "m_hReplicatingOtherHeroModel");

		m_nCourierState					= GetFieldOffset("client.dll", "C_DOTA_Unit_Courier", "m_nCourierState");

		m_hAssignedHero					= GetFieldOffset("client.dll", "C_DOTAPlayer", "m_hAssignedHero");

		m_SharedCooldownList			= GetFieldOffset("client.dll", "C_DOTA_UnitInventory", "m_SharedCooldownList");
		m_hItems						= GetFieldOffset("client.dll", "C_DOTA_UnitInventory", "m_hItems");

		m_iRuneType						= GetFieldOffset("client.dll", "C_DOTA_Item_Rune", "m_iRuneType");

		m_name							= GetFieldOffset("client.dll", "CDOTA_Buff", "m_name");
		m_flDuration					= GetFieldOffset("client.dll", "CDOTA_Buff", "m_flDuration");
		m_flDieTime						= GetFieldOffset("client.dll", "CDOTA_Buff", "m_flDieTime");
		m_hCaster						= GetFieldOffset("client.dll", "CDOTA_Buff", "m_hCaster");
		m_hAbility						= GetFieldOffset("client.dll", "CDOTA_Buff", "m_hAbility");
		m_hParent						= GetFieldOffset("client.dll", "CDOTA_Buff", "m_hParent");
		m_iStackCount					= GetFieldOffset("client.dll", "CDOTA_Buff", "m_iStackCount");
		//m_bAuraFlags					= GetFieldOffset("client.dll", "CDOTA_Buff", "m_iPaddingToMakeSchemaHappy2") + 0x2;
		//m_hAuraUnits					= GetFieldOffset("client.dll", "CDOTA_Buff", "m_hAuraUnits");

		m_pAbilityData					= GetFieldOffset("client.dll", "C_DOTABaseAbility", "m_bAltCastState") - 0x8;
		m_iLevel						= GetFieldOffset("client.dll", "C_DOTABaseAbility", "m_iLevel");

		m_nSpecialAbilities				= GetFieldOffset("client.dll", "DOTAAbilityDefinition_t", "m_nSpecialAbilities");
		m_pSpecialAbilities				= GetFieldOffset("client.dll", "DOTAAbilityDefinition_t", "m_pSpecialAbilities");

		m_pszName						= GetFieldOffset("client.dll", "DOTASpecialAbility_t", "m_pszName");
		m_FieldType						= GetFieldOffset("client.dll", "DOTASpecialAbility_t", "m_FieldType");
		m_nCount						= GetFieldOffset("client.dll", "DOTASpecialAbility_t", "m_nCount");
		m_Values						= GetFieldOffset("client.dll", "DOTASpecialAbility_t", "m_Values");

		m_hGameModeEntity				= GetFieldOffset("client.dll", "C_DOTAGamerules", "m_hGameModeEntity");
		m_hTeamFountains				= GetFieldOffset("client.dll", "C_DOTAGamerules", "m_hTeamFountains");
		m_fGameTime						= GetFieldOffset("client.dll", "C_DOTAGamerules", "m_fGameTime");

		m_flIntelligenceSpellAmpPercent = GetFieldOffset("client.dll", "C_DOTABaseGameMode", "m_flIntelligenceSpellAmpPercent");

		m_pParticles					= GetFieldOffset("particles.dll", "CNewParticleEffect", "m_pParticles");
		m_hOwner						= GetFieldOffset("particles.dll", "CNewParticleEffect", "m_hOwner");

		CModifierParams__s_Default		= GetStaticMember("client.dll", "CModifierParams", "s_Default");

#ifdef _DEBUG
		Log::Msg("--------------\n");
#endif // _DEBUG
	}
}