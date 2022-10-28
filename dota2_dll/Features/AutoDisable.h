#pragma once

namespace Features
{
	namespace AutoDisable
	{
		C_DOTABaseAbility* FindDisable(C_DOTA_BaseNPC* hero, C_DOTA_BaseNPC* target, int dist)
		{
			if (!Settings::AutoStun.GetInt())
				return nullptr;

			static const char* const itemsDisable[] =
			{
				"item_rod_of_atos",
				"item_cyclone",
				"item_sheepstick",
				"item_heavens_halberd" // not a stun
			};

			/*
				"item_ethereal_blade",
				"item_nullifier",
				"item_orchid",
				"item_bloodthorn"
			*/

			static const char* abilitiesDisable0[] =
			{
				"centaur_hoof_stomp",
				"huskar_inner_fire",
				"chaos_knight_chaos_bolt",
				"enigma_malefice",
				"ogre_magi_fireblast",
				"rubick_telekinesis",
				"sven_storm_bolt",
				"vengefulspirit_magic_missile",
				"skeleton_king_hellfire_blast",
				"witch_doctor_paralyzing_cask",
				"bane_nightmare",
				"earthshaker_fissure",
				"lion_impale",
				"monkey_king_boundless_strike",
				"nyx_assassin_impale",
				"sandking_burrowstrike",
				"shadow_demon_disruption",
				"tiny_avalanche",
				"windrunner_shackleshot",
				"ember_spirit_searing_chains",
				"meepo_earthbind"
			};

			static const char* abilitiesDisable1[] =
			{
				"slardar_slithereen_crush",
				"dragon_knight_dragon_tail",
				"jakiro_ice_path",
				"lina_light_strike_array",
				"obsidian_destroyer_astral_imprisonment",
				"storm_spirit_electric_vortex",
				"crystal_maiden_frostbite",
				"naga_siren_ensnare",
				"abyssal_underlord_pit_of_malice",
				"lion_voodoo",
				"shadow_shaman_voodoo"
			};

			static const char* abilitiesDisable2[] =
			{
				"nyx_assassin_spiked_carapace",
				"morphling_adaptive_strike_str"
			};

			static const char* abilitiesDisable3[] =
			{
				// neutrals (doom)
				"centaur_khan_war_stomp",
				"dark_troll_warlord_ensnare",

				"invoker_cold_snap",
				"invoker_tornado",
				"invoker_deafening_blast"
			};

			static const char* abilitiesDisable4[] =
			{
				"invoker_cold_snap",
				"invoker_tornado",
				"invoker_deafening_blast"
			};

			static const char* abilitiesDisable5[] =
			{
				"tusk_walrus_punch"
			};

			static const char** abilitiesDisable[] =
			{
				abilitiesDisable0,
				abilitiesDisable1,
				abilitiesDisable2,
				abilitiesDisable3,
				abilitiesDisable4,
				abilitiesDisable5
			};

			static const size_t abilitiesCount[] =
			{
				_countof(abilitiesDisable0),
				_countof(abilitiesDisable1),
				_countof(abilitiesDisable2),
				_countof(abilitiesDisable3),
				_countof(abilitiesDisable4),
				_countof(abilitiesDisable5)
			};

			C_DOTA_UnitInventory* inventory = hero->GetInventory();
			for (UINT i = 0; i < 19; ++i)
			{
				C_DOTA_Item* item = inventory->GetItemByIndex(i);
				if (!item)
					continue;

				for (UINT j = 0; j < _countof(itemsDisable); ++j)
				{
					if (!strcmp(item->m_pIdentity->m_name, itemsDisable[j]) &&
						dist <= item->GetEffectiveCastRange() &&
						item->CanBeExecuted() &&
						item->CastFilterResult(target) == UF_SUCCESS)
						return item;
				}
			}

			C_DOTABaseAbility* bestAbility = nullptr;
			float bestCastTime = FLT_MAX;

			bool checkRubick = false;

			for (int i = 0; i < _countof(abilitiesDisable); ++i)
			{
				C_DOTABaseAbility* ability = hero->GetAbilityByIndex(checkRubick ? 3 : i);
				if (!ability)
					continue;

				for (size_t j = 0; j < abilitiesCount[i]; ++j)
				{
					if (strcmp(ability->m_pIdentity->m_name, abilitiesDisable[i][j]))
						continue;

					DOTA_ABILITY_BEHAVIOR behavior = ability->GetBehavior();

					int range;

					// nyx's carapace
					if (i == 2 && j == 0)
						range = dist;
					else if (behavior & DOTA_ABILITY_BEHAVIOR_NO_TARGET)
						range = ability->GetLevelSpecialValueFor<int>("radius", true);
					else
						range = ability->GetEffectiveCastRange();

					if (range < dist || !ability->CanBeExecuted())
						continue;

					if (behavior & DOTA_ABILITY_BEHAVIOR_UNIT_TARGET)
					{
						if (ability->CastFilterResult(target) != UF_SUCCESS)
							continue;
					}
					else if (behavior & DOTA_ABILITY_BEHAVIOR_POINT)
					{
						if (ability->CastFilterResult(target->GetAbsOrigin()) != UF_SUCCESS)
							continue;
					}
					else if (behavior & DOTA_ABILITY_BEHAVIOR_NO_TARGET)
					{
						if (ability->CastFilterResult() != UF_SUCCESS)
							continue;
					}

					float castTime = ability->GetCastPoint();
					if (castTime <= 0.f)
						return ability;

					if (castTime < bestCastTime)
					{
						bestCastTime = castTime;
						bestAbility = ability;
						break;
					}
				}

				if (!checkRubick && (i == (_countof(abilitiesDisable) - 1)) && (hero->GetClientClass()->m_ClassID == ClassID::C_DOTA_Unit_Hero_Rubick))
				{
					checkRubick = true;
					i = -1;
				}
			}

			return bestAbility;
		}

		void Run(C_DotaPlayer* player, C_DOTA_BaseNPC_Hero* hero)
		{
			if (!Settings::AutoStun.GetInt() && !Settings::AutoEscape.GetInt() && !Settings::AutoSilence.GetInt())
				return;

			if (!(*G::pGameRules))
				return;

			bool enemyNear = false;
			static bool enemyNearPrev = true;

			for (int i = INDEX_SKIP_PLAYERS; i <= I::EntitySystem->GetHighestEntityIndex(); ++i)
			{
				C_BaseEntity* entity = I::EntitySystem->GetBaseEntity(i);
				if (!entity || entity->IsDormant() || entity->GetTeamNum() == hero->GetTeamNum() || !entity->IsAlive())
					continue;

				if (!entity->IsDOTANPC() || !static_cast<C_DOTA_BaseNPC_Hero*>(entity)->IsRealHero())
					continue;

				C_DOTA_BaseNPC_Hero* enemy = static_cast<C_DOTA_BaseNPC_Hero*>(entity);

				vec3 entityOrigin = enemy->GetAbsOrigin();
				float dist = (hero->GetAbsOrigin() - entityOrigin).Length();
				if (dist > 960.f ||
					enemy->FindModifierByName("modifier_earthshaker_enchant_totem_leap") ||
					enemy->FindModifierByName("modifier_faceless_void_time_walk") ||
					enemy->FindModifierByName("modifier_rattletrap_hookshot") ||
					enemy->FindModifierByName("modifier_storm_spirit_ball_lightning"))
					continue;

				if (!enemyNearPrev &&
					(dist < 550.f) &&
					!hero->IsInState(MODIFIER_STATE_SILENCED) &&
					!hero->IsInState(MODIFIER_STATE_MUTED) &&
					!enemy->IsInState(MODIFIER_STATE_ROOTED) &&
					!enemy->IsInState(MODIFIER_STATE_DISARMED) &&
					!enemy->IsInState(MODIFIER_STATE_SILENCED) &&
					!enemy->IsInState(MODIFIER_STATE_MUTED) &&
					!enemy->IsInState(MODIFIER_STATE_STUNNED) &&
					!enemy->IsInState(MODIFIER_STATE_HEXED) &&
					!enemy->IsInState(MODIFIER_STATE_INVULNERABLE) &&
					!enemy->IsInState(MODIFIER_STATE_NIGHTMARED) &&
					!enemy->IsInState(MODIFIER_STATE_FROZEN) &&
					!enemy->IsInState(MODIFIER_STATE_NOT_ON_MINIMAP) &&
					!enemy->IsBlockingSpells())
				{
					// didn't just teleport or blink
					C_DOTA_Item* blink = hero->FindItemByName("item_blink");
					sSharedCooldownInfo* tp = hero->GetInventory()->GetSharedCooldownInfo("teleport");
					CDOTA_Buff* fountainBuff = enemy->FindModifierByName("modifier_fountain_aura_buff");

					if ((!blink || (0.3f < (blink->GetEffectiveCooldown() - blink->GetCooldownTime()))) &&
						(!tp || (0.3f < ((*G::pGameRules)->GetGameTime() - tp->time))) &&
						(!fountainBuff || ((fountainBuff->GetDieTime() - (*G::pGameRules)->GetGameTime()) < (fountainBuff->GetDuration() - 0.3f))))
					{
						C_DOTABaseAbility* disable = FindDisable(hero, enemy, dist);
						if (disable)
						{
							DOTA_ABILITY_BEHAVIOR behavior = disable->GetBehavior();

							if (behavior & DOTA_ABILITY_BEHAVIOR_UNIT_TARGET)
								player->PrepareUnitOrders(DOTA_UNIT_ORDER_CAST_TARGET, i, vec3(), disable->m_pIdentity->GetIndex(), DOTA_ORDER_ISSUER_HERO_ONLY);

							else if (behavior & DOTA_ABILITY_BEHAVIOR_POINT)
								player->PrepareUnitOrders(DOTA_UNIT_ORDER_CAST_POSITION, 0, entityOrigin, disable->m_pIdentity->GetIndex(), DOTA_ORDER_ISSUER_HERO_ONLY);

							else if (behavior & DOTA_ABILITY_BEHAVIOR_NO_TARGET)
								player->PrepareUnitOrders(DOTA_UNIT_ORDER_CAST_NO_TARGET, 0, vec3(), disable->m_pIdentity->GetIndex(), DOTA_ORDER_ISSUER_HERO_ONLY);
						}
					}
				}

				enemyNear = true;
				break;
			}

			enemyNearPrev = enemyNear;
		}
	}
}