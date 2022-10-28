#pragma once

class C_DOTA_Item : public C_DOTABaseAbility
{
public:

}; //Size=0x0060

class sSharedCooldownInfo
{
public:
	const char* name;
	float length;
	float time;
};

class C_DOTA_UnitInventory
{
public:
	inline CUtlVector<sSharedCooldownInfo>* GetSharedCooldownList()
	{
		return reinterpret_cast<CUtlVector<sSharedCooldownInfo>*>(reinterpret_cast<uintptr_t>(this) + Schema::m_SharedCooldownList);
	}

	inline sSharedCooldownInfo* GetSharedCooldownInfo(const char* name)
	{
		CUtlVector<sSharedCooldownInfo>* list = GetSharedCooldownList();
		for (int i = 0; i < list->Count(); ++i)
		{
			if (!strcmp(list->Element(i).name, name))
				return &list->Element(i);
		}
		return nullptr;
	}

	inline unsigned long* GetItems()
	{
		return reinterpret_cast<unsigned long*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hItems);
	}

	inline C_DOTA_Item* GetItemByIndex(int index)
	{
		return static_cast<C_DOTA_Item*>(I::EntitySystem->GetBaseEntityFromHandle(GetItems()[index]));
	}
}; //Size=0x00B0

enum DOTA_RUNES
{
	DOTA_RUNE_INVALID = -1,
	DOTA_RUNE_DOUBLEDAMAGE = 0,
	DOTA_RUNE_HASTE = 1,
	DOTA_RUNE_ILLUSION = 2,
	DOTA_RUNE_INVISIBILITY = 3,
	DOTA_RUNE_REGENERATION = 4,
	DOTA_RUNE_BOUNTY = 5,
	DOTA_RUNE_ARCANE = 6,
	DOTA_RUNE_WATER = 7,
	DOTA_RUNE_COUNT = 8,
};

class C_DOTA_Item_Rune : public C_BaseEntity
{
public:
	inline DOTA_RUNES GetRuneType()
	{
		return *reinterpret_cast<DOTA_RUNES*>(reinterpret_cast<uintptr_t>(this) + Schema::m_iRuneType);
	}
};