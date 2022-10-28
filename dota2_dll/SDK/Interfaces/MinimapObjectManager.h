#pragma once

class CHudTexture;

class CDOTA_MinimapObject
{
public:
	CHudTexture* m_pIcon; //0x0000 
	char* m_pszHero; //0x0008 
	vec3 m_vLocation; //0x0010 
	DWORD m_hParent; //0x001C 
	DWORD m_hTarget; //0x0020 
	Color m_color; //0x0024 
	int32_t m_entIndex; //0x0028 
	int32_t m_type; //0x002C 4 - simple, 5 - team, 7 - enemy, 8 - ping, 10 - event, 11 - scan, 12 - courier   
	int32_t m_subtype; //0x0030 14 - attack, 18 - going here, 22 - simple, 23 - retreat, 29 - vision, 31 - thumbs up, 4096 - DOTA_MINIMAP_EVENT_RADAR
	float N000004E1; //0x0034 non zero on teleport, tower under attack
private:
	std::byte pad_0x0038[0x4]; //0x0038
public:
	float m_flSize; //0x003C 
	float m_flDieTime; //0x0040 
	unsigned char N000004D3; //0x0044 non zero on teleport
	unsigned char N00000496; //0x0045 
	unsigned char N0000049A; //0x0046 
	unsigned char N00000497; //0x0047 

}; //Size=0x0048

class CDOTA_MinimapObjectManager
{
public:
	static CDOTA_MinimapObject* AddNewObject(int entIndex, int type)
	{
		typedef CDOTA_MinimapObject* (__thiscall* Fn)(CDOTA_MinimapObjectManager*, int, int);
		return reinterpret_cast<Fn>(Signatures::CDOTA_MinimapObjectManager__AddNewObject)(nullptr, entIndex, type);
	}
};