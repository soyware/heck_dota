#pragma once

namespace Features
{
	namespace ParticleMaphack
	{
		struct CParticleRecord
		{
			C_BaseEntity* entity;
			CParticleCollection* particle;
			const char* name;
			bool tpEnd;
		};
		std::vector<CParticleRecord> particles;
		std::vector<C_BaseEntity*> added;

		const char* ignoreList[] =
		{
			"particles/units/heroes/hero_furion/furion_wrath_of_nature.vpcf"
		};

		const char* teleportEndList[] =
		{
			"particles/items2_fx/teleport_end.vpcf",
			"particles/units/heroes/hero_furion/furion_teleport_end.vpcf"
		};

		void Add(CParticleSystemDefinition*** definition, CreateParticleArgs* args)
		{
			if (!Settings::ParticleMaphack::Enable.GetInt())
				return;

			C_BaseEntity* entity = nullptr;

			if (args->m_parent)
				entity = args->m_parent;
			else if (args->m_caster)
				entity = args->m_caster;

			if (!entity || !entity->m_pIdentity || !entity->m_pIdentity->m_name || !entity->m_pIdentity->m_name[0] ||
				!entity->IsDormant() || !entity->IsDOTANPC() || !static_cast<C_DOTA_BaseNPC_Hero*>(entity)->IsRealHero())
				return;

			CParticleCollection* collection = (**definition)->FirstCollection();
			if (!collection)
				return;

			const char* name = **reinterpret_cast<const char***>(reinterpret_cast<uintptr_t>(*definition) + 8);

			bool tpEnd = false;

			if (name)
			{
				for (int i = 0; i < _countof(ignoreList); ++i)
				{
					if (!strcmp(name, ignoreList[i]))
						return;
				}

				for (int i = 0; i < _countof(teleportEndList); ++i)
				{
					if (!strcmp(name, teleportEndList[i]))
					{
						tpEnd = true;
						break;
					}
				}
			}

			particles.push_back({ entity, collection, name, tpEnd });
		}

		void AddEnemyToMinimap(const CParticleRecord& rec)
		{
			if (!rec.tpEnd)
			{
				for (auto it = added.begin(); it != added.end(); ++it)
				{
					if (*it == rec.entity)
						return;
				}
			}

			vec3* location = nullptr;
			int highest = rec.particle->GetHighestControlPoint();
			for (int i = 0; i <= highest; ++i)
			{
				if (!rec.particle->ReadsControlPoint(i) || rec.particle->IsNonPositionalControlPoint(i))
					continue;

				vec3* pos = rec.particle->GetControlPointPosition(i);
				if (pos && 500.f < pos->Length2D() && 500.f < (rec.entity->GetAbsOrigin() - *pos).Length2D())
				{
					location = pos;
					break;
				}
			}

			if (!location)
				return;

			if (!rec.tpEnd)
				added.push_back(rec.entity);

			CDOTA_MinimapObject* minimapObj = CDOTA_MinimapObjectManager::AddNewObject((rec.tpEnd ? 0x80000000 : -rec.entity->m_pIdentity->GetIndex()), 7);
			if (!minimapObj)
				return;

			float iconSize = Settings::ParticleMaphack::Size.GetFloat();
			if (rec.tpEnd)
				iconSize *= 0.65f;

			minimapObj->m_hParent = rec.entity->m_pIdentity->m_handle;
			static CHudTexture* icon = G::HudIcons->GetIcon("minimap_enemyicon");
			minimapObj->m_pIcon = icon;
			minimapObj->m_pszHero = rec.entity->m_pIdentity->m_name;
			minimapObj->m_vLocation = *location;
			minimapObj->m_color = Color(255, 255, 117, 51);
			minimapObj->m_flSize = iconSize;
			minimapObj->m_flDieTime = (*G::pGlobals)->curtime + 5.f;
			minimapObj->N00000497 = true;
		}

		void Draw()
		{
			if (!Settings::ParticleMaphack::Enable.GetInt())
				return;

			for (auto it = particles.begin(); it != particles.end(); ++it)
				AddEnemyToMinimap(*it);

			particles.clear();
			added.clear();
		}
	}
}