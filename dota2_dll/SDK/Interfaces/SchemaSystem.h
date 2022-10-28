#pragma once

class CSchemaType
{
private:
	std::byte pad_0x0000[0x8]; //0x0000
public:
	char* m_pszType; //0x0008 
private:
	std::byte pad_0x0010[0x8]; //0x0010
public:
	int32_t m_Size; //0x0018 
private:
	std::byte pad_0x001C[0x4]; //0x001C
public:
	void* m_pTypeScope; //0x0020 
private:
	std::byte pad_0x0028[0x8]; //0x0028

}; //Size=0x0030

class SchemaClassFieldData_t
{
public:
	char* m_Name; //0x0000 
	CSchemaType* m_pType; //0x0008 
	int32_t m_Offset; //0x0010 
	int32_t m_MetadataCount; //0x0014 
	void* m_pMetadata; //0x0018 

}; //Size=0x0020

class SchemaStaticFieldData_t
{
public:
	char* m_Name; //0x0000 
	CSchemaType* m_pType; //0x0008 
	void* m_pInstance; //0x0010 

}; //Size=0x0018

class SchemaClassInfoData_t
{
public:
	SchemaClassInfoData_t* m_pParent; //0x0000 
	char* m_pName; //0x0008 
	char* m_pProjectName; //0x0010 
	int32_t m_Size; //0x0018 
	int16_t m_FieldCount; //0x001C 
	int16_t m_staticMemberCount; //0x001E 
private:
	std::byte pad_0x0020[0x8]; //0x0020
public:
	SchemaClassFieldData_t* m_Fields; //0x0028 
	SchemaStaticFieldData_t* m_staticMembers; //0x0030 
private:
	std::byte pad_0x0038[0x20]; //0x0038
public:
	CSchemaType* m_pSchemaType; //0x0058 
private:
	std::byte pad_0x0060[0x10]; //0x0060

}; //Size=0x0070

class CSchemaSystemTypeScope
{
public:
	inline SchemaClassInfoData_t* FindDeclaredClass(const char* name)
	{
		typedef SchemaClassInfoData_t*(__thiscall* Fn)(void*, const char*);
		return GetVF<Fn>(this, 2)(this, name);
	}

	inline void* FindDeclaredEnum(const char* name)
	{
		typedef void*(__thiscall* Fn)(void*, const char*);
		return GetVF<Fn>(this, 3)(this, name);
	}
};

class CSchemaSystem
{
public:
	inline CSchemaSystemTypeScope* GlobalTypeScope()
	{
		typedef CSchemaSystemTypeScope*(__thiscall* Fn)(void*);
		return GetVF<Fn>(this, 11)(this);
	}
	inline CSchemaSystemTypeScope* FindTypeScopeForModule(const char* name)
	{
		typedef CSchemaSystemTypeScope*(__thiscall* Fn)(void*, const char*);
		return GetVF<Fn>(this, 13)(this, name);
	}
};