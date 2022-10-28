#pragma once

#include "CourierPrediction.h"
#include "ParticleMaphack.h"

namespace Features
{
	namespace Visuals
	{
		const int lineHeight = 12;

		void DrawSpellDmg(CVGuiPaintSurfaceMainThread* paintSurface, C_DOTA_BaseNPC_Hero* hero, C_DOTA_BaseNPC* entity, int screenX, int& screenY)
		{
			if (!Settings::ShowSpellDmg.GetInt())
				return;

			if (!entity->HasModifier(MODIFIER_PROPERTY_MIN_HEALTH) &&
				!hero->IsInState(MODIFIER_STATE_SILENCED) && !hero->IsInState(MODIFIER_STATE_MUTED) &&
				(hero->GetClientClass()->m_ClassID == ClassID::C_DOTA_Unit_Hero_Lion ||
				hero->GetClientClass()->m_ClassID == ClassID::C_DOTA_Unit_Hero_Lina))
			{
				C_DOTABaseAbility* ability = hero->GetAbilityByIndex(5);
				if (ability && ability->CanBeExecuted() && ability->CastFilterResult(entity) == UF_SUCCESS)
				{
					int buffDmg = 0;
					if (hero->GetClientClass()->m_ClassID == ClassID::C_DOTA_Unit_Hero_Lion)
					{
						CDOTA_Buff* killCounter = hero->FindModifierByName("modifier_lion_finger_of_death_kill_counter");
						if (killCounter)
						{
							static const int dmgPerKill = ability->GetLevelSpecialValueFor<int>("damage_per_kill");
							buffDmg = dmgPerKill * killCounter->GetStackCount();
						}
					}

					int hpLeft = entity->GetHealth() - 
						entity->GetIncomingDamage(ability->GetCurrentAbilityDamageType(), hero->GetOutgoingSpellDamage(ability->GetAbilityDamage() + buffDmg));

					if (hpLeft > 0)
					{
						wchar_t szText[16];
						swprintf_s(szText, _countof(szText), L"ult: %d", hpLeft);

						int W, H;
						paintSurface->GetTextSize(Draw::fontESP, szText, W, H);

						Draw::Text(paintSurface, szText, screenX - W / 2, screenY, Draw::fontESP, Color::White());
					}
					else
					{
						int W, H;
						paintSurface->GetTextSize(Draw::fontESP, L"ult: dead", W, H);

						Draw::Text(paintSurface, L"ult: dead", screenX - W / 2, screenY, Draw::fontESP, Color::LightRed());
					}

					screenY += lineHeight;
				}
			}
		}

		void DrawGem(CVGuiPaintSurfaceMainThread* paintSurface, C_DOTA_BaseNPC* entity, int screenX, int& screenY)
		{
			if (!Settings::ShowGem.GetInt())
				return;

			if (entity->FindItemByName("item_gem"))
			{
				int W, H;
				paintSurface->GetTextSize(Draw::fontESP, L"gem", W, H);

				Draw::Text(paintSurface, L"gem", screenX - W / 2, screenY, Draw::fontESP, Color::LightRed());

				screenY += lineHeight;
			}
		}

		void DrawCharge(C_DOTA_BaseNPC* entity)
		{
			if (!Settings::ShowCharge.GetInt())
				return;

			static CDOTA_Buff* prevBuff = nullptr;
			CDOTA_Buff* buff = entity->FindModifierByName("modifier_spirit_breaker_charge_of_darkness_vision");
			if (buff && prevBuff != buff)
			{
				prevBuff = buff;

				int index = (*G::pParticleManager)->NewParticleIndex();

				(*G::pParticleManager)->CreateParticle(
					index,
					"particles/units/heroes/hero_spirit_breaker/spirit_breaker_charge_target.vpcf", 
					PATTACH_OVERHEAD_FOLLOW, 
					buff->GetParent(), 
					buff->GetCaster());

				buff->AddParticle(index, false, false, -1, false, true);
			}
		}

		void DrawVisible(CVGuiPaintSurfaceMainThread* paintSurface, C_DOTA_BaseNPC* entity, DOTATeam_t entityTeam, int screenX, int& screenY)
		{
			if (!Settings::ShowVisibility.GetInt())
				return;

			if (entity->CanBeSeenByTeam(entityTeam == DOTA_TEAM_GOODGUYS ? DOTA_TEAM_BADGUYS : DOTA_TEAM_GOODGUYS))
			{
				int W, H;
				paintSurface->GetTextSize(Draw::fontESP, L"visible", W, H);

				Draw::Text(paintSurface, L"visible", screenX - W / 2, screenY, Draw::fontESP, Color::White());

				screenY += lineHeight;
			}
		}

		void DrawIllusion(C_DOTA_BaseNPC_Hero* entity)
		{
			if (!Settings::ShowIllusions.GetInt())
				return;

			if (entity->GhettoIsIllusion() && !entity->FindModifierByName("modifier_illusion"))
				entity->GetModifierManager()->AddNewModifier(entity, nullptr, "modifier_illusion", nullptr);
		}

		void Paint(CVGuiPaintSurfaceMainThread* paintSurface)
		{
			if (!I::EngineClient->IsInGame())
				return;

			int localIndex;
			I::EngineClient->GetLocalPlayer(localIndex);
			C_DotaPlayer* player = static_cast<C_DotaPlayer*>(I::EntitySystem->GetBaseEntity(localIndex));
			if (!player)
				return;

			C_DOTA_BaseNPC_Hero* hero = player->GetAssignedHero();
			if (!hero)
				return;

			for (int i = INDEX_SKIP_PLAYERS; i <= I::EntitySystem->GetHighestEntityIndex(); ++i)
			{
				C_BaseEntity* entity = I::EntitySystem->GetBaseEntity(i);
				if (!entity || entity->IsDormant() || !entity->IsAlive() || !entity->IsDOTANPC())
					continue;

				vec3 worldPos;
				entity->WorldSpaceCenter(worldPos);
				int screenX, screenY;
				if (!GetVectorInScreenSpace(worldPos, screenX, screenY))
					continue;

				C_DOTA_BaseNPC_Hero* entityHero = static_cast<C_DOTA_BaseNPC_Hero*>(entity);

				DOTATeam_t entityTeam = entity->GetTeamNum();
				if (entityTeam == hero->GetTeamNum())
				{
					if (entityHero->IsRealHero() || entityHero->IsWard())
						DrawVisible(paintSurface, entityHero, entityTeam, screenX, screenY);

					if (entityHero->IsRealHero())
						DrawCharge(entityHero);
				}
				else if (entityHero->IsHero())
				{
					if (!entityHero->GhettoIsIllusion())
					{
						DrawGem(paintSurface, entityHero, screenX, screenY);
						DrawSpellDmg(paintSurface, hero, entityHero, screenX, screenY);
					}
					else
						DrawIllusion(entityHero);
				}
			}
		}
	}
}