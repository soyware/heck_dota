#pragma once

namespace Features
{
	namespace CourierPrediction
	{
		struct CLastSeen
		{
			float moveSpeed = 0.f;
			float burstDieTime = 0.f;
			float burstRemainingTime = 0.f;
		};

		CLastSeen lastSeen[10];
		float burstMultiplier = 0.f;

		void Predict()
		{
			if (!Settings::PredictCourier.GetInt())
				return;

			if (!I::EngineClient->IsInGame())
				return;

			int localIndex;
			I::EngineClient->GetLocalPlayer(localIndex);
			C_DotaPlayer* player = static_cast<C_DotaPlayer*>(I::EntitySystem->GetBaseEntity(localIndex));
			if (!player)
				return;

			if (!(*G::pGameRules))
				return;

			int index = 0;

			for (int i = INDEX_SKIP_PLAYERS; i <= I::EntitySystem->GetHighestEntityIndex(); ++i)
			{
				C_BaseEntity* entity = I::EntitySystem->GetBaseEntity(i);
				if (!entity || entity->GetTeamNum() == player->GetTeamNum() || !entity->IsAlive())
					continue;

				if (!entity->IsDOTANPC() || (entity->GetClientClass()->m_ClassID != ClassID::C_DOTA_Unit_Courier))
					continue;

				vec3 predicted;

				if (entity->IsDormant())
				{
					if (!lastSeen[index].moveSpeed)
						continue;

					CourierState_t state = static_cast<C_DOTA_Unit_Courier*>(entity)->GetCourierState();
					vec3 start = entity->GetAbsOrigin();
					vec3 end;

					if (state == COURIER_STATE_DELIVERING_ITEMS)
					{
						C_DOTA_BaseNPC_Hero* ownerHero = static_cast<C_DotaPlayer*>(entity->GetOwnerEntity())->GetAssignedHero();
						if (!ownerHero)
							continue;

						end = ownerHero->GetAbsOrigin();

						vec3 fountain = (*G::pGameRules)->GetFountain(entity->GetTeamNum())->GetAbsOrigin();
						vec3 a = end - fountain;
						vec3 b = start - fountain;

						float degree = RAD2DEG(acos(DotProduct(a, b) / (a.Length() * b.Length())));
						// if predicted route from fountain differs by this much, don't draw
						if (10.f <= degree) 
							continue;
					}
					else if (state == COURIER_STATE_RETURNING_TO_BASE)
						end = (*G::pGameRules)->GetFountain(entity->GetTeamNum())->GetAbsOrigin();
					else
						continue;

					vec3 delta = start - end;

					float speed = lastSeen[index].moveSpeed * (*G::pGlobals)->interval_per_tick;
					float covered;

					if (lastSeen[index].burstDieTime && ((*G::pGameRules)->GetGameTime() >= lastSeen[index].burstDieTime))
						covered = speed * TIME_TO_TICKS(lastSeen[index].burstRemainingTime) +
							speed / burstMultiplier * TIME_TO_TICKS(I::EngineClient->GetLastTimeStamp() - (entity->GetLastMessageTime() + lastSeen[index].burstRemainingTime));
					else
						covered = speed * TIME_TO_TICKS(I::EngineClient->GetLastTimeStamp() - entity->GetLastMessageTime());

					float fraction = covered / delta.Length();
					if (0.9f < fraction)
						continue;

					VectorLerp(start, end, fraction, predicted);
				}
				else
				{
					lastSeen[index].moveSpeed = static_cast<C_DOTA_BaseNPC*>(entity)->GetIdealSpeed();

					CDOTA_Buff* buff = static_cast<C_DOTA_BaseNPC*>(entity)->FindModifierByName("modifier_courier_burst");
					if (buff)
					{
						lastSeen[index].burstDieTime = buff->GetDieTime();
						lastSeen[index].burstRemainingTime = lastSeen[index].burstDieTime - (*G::pGameRules)->GetGameTime();

						if (!burstMultiplier)
							burstMultiplier = 1.f + (buff->GetAbility()->GetLevelSpecialValueFor<float>("movement_speed") * 0.01f);
					}
					else
					{
						lastSeen[index].burstDieTime = 0.f;
						lastSeen[index].burstRemainingTime = 0.f;
					}
				}

				CDOTA_MinimapObject* minimapObject = CDOTA_MinimapObjectManager::AddNewObject(i, 12);
				if (!minimapObject)
					continue;

				static CHudTexture* icon = G::HudIcons->GetIcon("minimap_courier_dire");
				minimapObject->m_pIcon = icon;
				minimapObject->m_flSize = 390.f;

				if (entity->IsDormant())
				{
					minimapObject->m_vLocation = predicted;
					minimapObject->N00000497 = true;
				}

				if (_countof(lastSeen) <= ++index)
					break;
			}
		}
	}
}