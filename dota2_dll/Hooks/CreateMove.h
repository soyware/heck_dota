#pragma once

class CUserCmd
{
private:
	std::byte pad_0x0000[0x8]; //0x0000
public:
	int32_t command_number; //0x0008 
	int32_t tick_count; //0x000C 
	vec3 viewangles; //0x0010 
	float forwardmove; //0x001C 
	float sidemove; //0x0020 
	float upmove; //0x0024 
	DWORD64 buttons; //0x0028 
	unsigned char impulse; //0x0030 
private:
	std::byte pad_0x0031[0x3]; //0x0031
public:
	int32_t weaponselect; //0x0034 
	int32_t weaponsubtype; //0x0038 
	int32_t random_seed; //0x003C 
	int16_t mousedx; //0x0040 
	int16_t mousedy; //0x0042 
	unsigned char hasbeenpredicted; //0x0044 
private:
	std::byte pad_0x0045[0x1]; //0x0045
public:
	int16_t cameraPosX; //0x0046 
	int16_t cameraPosY; //0x0048 
	unsigned char cursorCommand; //0x004A attack, spell, move etc
	unsigned char scoreboardOpen; //0x004B 
private:
	std::byte pad_0x004C[0x4]; //0x004C
public:
	vec3 crosshairtrace; //0x0050 world location directly beneath the player's crosshair
private:
	std::byte pad_0x005C[0x3]; //0x005C

}; //Size=0x005F

namespace Hooks
{
	typedef bool(__thiscall* CreateMoveFn)(ClientModeDOTANormal*, CUserCmd*, vec3&, vec3&);
	CreateMoveFn oCreateMove;

	bool CreateMove(ClientModeDOTANormal* _this, CUserCmd* cmd, vec3& angle, vec3& pos)
	{
		//if (!hkMinimapRenderer)
		//{
		//	auto map = Interfaces::PanoramaEngine->AccessUIEngine()->GetPanelsMap();
		//	for (int i = 1024; i < 2048; ++i)
		//	{
		//		if (!strcmp(map->Key(i)->GetID(), "Hud"))
		//		{
		//			CUIPanel* minimap = map->Key(i)->FindChildInLayoutFile("minimap");
		//			void* renderer = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(minimap->ClientPtr()) + 0x30);

		//			hkMinimapRenderer = new CVTH("client.dll", renderer);
		//			oMinimapRendererDestructor = hkMinimapRenderer->Hook<MinimapRendrererDestructorFn>(0, &MinimapRendererDestructor);
		//			oMinimapRendererPaint = hkMinimapRenderer->Hook<MinimapRendererPaintFn>(2, &MinimapRendererPaint);

		//			break;
		//		}
		//	}
		//}

		if (!hkParticleManager.IsHooked())
		{
			hkParticleManager.Init(*G::pParticleManager);
			oParticleManagerDestructor = hkParticleManager.Hook<DestructorFn>(0, &ParticleManagerDestructor);
			oCreateParticleEffectInternal = hkParticleManager.Hook<CreateParticleEffectInternalFn>(8, &CreateParticleEffectInternal);
		}

		Features::Moves::Run();
		return oCreateMove(_this, cmd, angle, pos);
	}
}