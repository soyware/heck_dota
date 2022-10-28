#pragma once

class CEntityInstance
{
public:
	void* vt; //0x0000 
	void* m_iszPrivateVScripts; //0x0008 
	CEntityIdentity* m_pIdentity; //0x0010 
private:
	std::byte pad_0x0018[0x8]; //0x0018
public:
	int32_t m_worldGroupId; //0x0020 
private:
	std::byte pad_0x0024[0xC]; //0x0024
public:
	void* m_CScriptComponent; //0x0030 

}; //Size=0x0038

enum DOTATeam_t : uint8_t
{
	DOTA_TEAM_FIRST = 2,
	DOTA_TEAM_GOODGUYS = 2,
	DOTA_TEAM_BADGUYS = 3,
	DOTA_TEAM_NEUTRALS = 4,
	DOTA_TEAM_NOTEAM = 5,
	DOTA_TEAM_CUSTOM_1 = 6,
	DOTA_TEAM_CUSTOM_2 = 7,
	DOTA_TEAM_CUSTOM_3 = 8,
	DOTA_TEAM_CUSTOM_4 = 9,
	DOTA_TEAM_CUSTOM_5 = 10,
	DOTA_TEAM_CUSTOM_6 = 11,
	DOTA_TEAM_CUSTOM_7 = 12,
	DOTA_TEAM_CUSTOM_8 = 13,
	DOTA_TEAM_COUNT = DOTA_TEAM_CUSTOM_8 + 1,
	DOTA_TEAM_CUSTOM_MIN = DOTA_TEAM_CUSTOM_1,
	DOTA_TEAM_CUSTOM_MAX = DOTA_TEAM_CUSTOM_8,
	DOTA_TEAM_CUSTOM_COUNT = DOTA_TEAM_CUSTOM_MAX - DOTA_TEAM_CUSTOM_MIN + 1,
};

class CGameSceneNode
{
public:
	inline vec3 GetAbsOrigin()
	{
		return *reinterpret_cast<vec3*>(reinterpret_cast<uintptr_t>(this) + Schema::m_vecAbsOrigin);
	}
};

class C_BaseEntity : public CEntityInstance
{
public:
	inline bool IsDormant()
	{
		return m_pIdentity->m_flags & (1 << 7);
	}

	inline bool IsAlive()
	{
		return *reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(this) + Schema::m_lifeState) == 0;
	}

	inline CGameSceneNode* GetGameSceneNode()
	{
		return *reinterpret_cast<CGameSceneNode**>(reinterpret_cast<uintptr_t>(this) + Schema::m_pGameSceneNode);
	}

	inline vec3 GetAbsOrigin()
	{
		return GetGameSceneNode()->GetAbsOrigin();
	}

	inline DOTATeam_t GetTeamNum()
	{
		return *reinterpret_cast<DOTATeam_t*>(reinterpret_cast<uintptr_t>(this) + Schema::m_iTeamNum);
	}

	inline bool IsDOTANPC()
	{
		return (*reinterpret_cast<int8_t*>(reinterpret_cast<uintptr_t>(this) + Schema::m_somethinglikenpctype) == 3);
	}

	inline int GetHealth()
	{
		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + Schema::m_iHealth);
	}

	inline float GetLastMessageTime()
	{
		return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + Schema::m_flLastMessageTime);
	}

	inline C_BaseEntity* GetOwnerEntity()
	{
		return I::EntitySystem->GetBaseEntityFromHandle(
			*reinterpret_cast<unsigned long*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hOwnerEntity));
	}

	// "Dump entity list to console"
	inline ClientClass* GetClientClass()
	{
		typedef ClientClass* (__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 28)(this);
	}

	// NOTE: These use the collision OBB to compute a reasonable center point for the entity
	inline const vec3& WorldSpaceCenter(vec3& out)
	{
		typedef const vec3&(__thiscall* Fn)(void*, vec3&);
		return GetVF<Fn>(this, 62)(this, out);
	}
};