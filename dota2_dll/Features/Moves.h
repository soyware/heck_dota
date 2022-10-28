#pragma once

#include "AutoDisable.h"

namespace Features
{
	namespace Moves
	{
		void AutoBountyRune(C_DotaPlayer* player, C_DOTA_BaseNPC_Hero* hero)
		{
			if (!Settings::AutoRune.GetInt())
				return;

			for (int i = INDEX_SKIP_PLAYERS; i <= I::EntitySystem->GetHighestEntityIndex(); ++i)
			{
				C_BaseEntity* entity = I::EntitySystem->GetBaseEntity(i);
				if (!entity || entity->IsDormant() || hero == entity)
					continue;

				if (entity->GetClientClass()->m_ClassID == ClassID::C_DOTA_Item_Rune &&
					((static_cast<C_DOTA_Item_Rune*>(entity)->GetRuneType() == DOTA_RUNE_BOUNTY) || (Settings::AutoRune.GetInt() == 2)) &&
					(hero->GetAbsOrigin() - entity->GetAbsOrigin()).Length() <= 150.f)
				{
					player->PrepareUnitOrders(DOTA_UNIT_ORDER_PICKUP_RUNE, i, vec3(), 0, DOTA_ORDER_ISSUER_HERO_ONLY);
					break;
				}
			}
		}

		void Run()
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

			static ConVar* dist = I::Cvar->FindVar("dota_camera_distance");
			static ConVar* farz = I::Cvar->FindVar("r_farz");
			farz->SetValue(dist->m_fValue * 2.204f);

			if (!hero->IsAlive())
				return;

			AutoBountyRune(player, hero);
			AutoDisable::Run(player, hero);
		}
	}
}