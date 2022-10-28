#pragma once

class C_BaseEntity;

class CEntityIdentity
{
public:
	C_BaseEntity* m_pEntity; //0x0000 
private:
	std::byte pad_0x0008[0x8]; //0x0008
public:
	int32_t m_handle; //0x0010 
	int32_t m_nameStringableIndex; //0x0014 
	char* m_name; //0x0018 
	char* m_designerName; //0x0020 
	void* m_publicScriptScope; //0x0028
public:
	int32_t m_flags; //0x0030 
private:
	std::byte pad_0x0034[0x4]; //0x0034
public:
	int32_t m_fDataObjectTypes; //0x0038 
	int16_t m_PathIndex; //0x003C 
private:
	std::byte pad_0x003E[0x12]; //0x003E
public:
	CEntityIdentity* m_pPrev; //0x0050 
	CEntityIdentity* m_pNext; //0x0058 
	CEntityIdentity* m_pPrevByClass; //0x0060 
	CEntityIdentity* m_pNextByClass; //0x0068 
	void* m_pId; //0x0070 

	inline int GetIndex() { return (m_handle & 0x7FFF); }
}; //Size=0x0078

class CConcreteEntityList
{
public:
	struct EntityChunk
	{
		CEntityIdentity m_Identities[512];
	};

	EntityChunk* m_Chunks[64];
};

class CSource2EntitySystem
{
public:
	inline C_BaseEntity* GetBaseEntity(int index)
	{
		if (0 > index || index > 0x7FFE)
			return nullptr;

		int listIndex = index >> 9;
		if (listIndex > 63)
			return nullptr;

		return m_EntityList.m_Chunks[listIndex]->m_Identities[index % 512].m_pEntity;
	}

	inline C_BaseEntity* GetBaseEntityFromHandle(unsigned long handle)
	{
		return GetBaseEntity(handle & 0x7FFF);
	}

	inline int GetHighestEntityIndex()
	{
		static const int offset = *reinterpret_cast<int*>(GetVF<uintptr_t>(this, 14) + 49);
		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

private:
	std::byte pad_0x0000[0x10]; //0x0000
public:
	CConcreteEntityList m_EntityList; //0x0018 

}; //Size=0x0020