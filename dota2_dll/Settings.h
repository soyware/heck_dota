#pragma once

namespace Settings
{
	ConVar AutoRune;

	ConVar AutoStun;
	ConVar AutoSilence;
	ConVar AutoEscape;

	ConVar ShowIllusions;
	ConVar ShowCharge;
	ConVar ShowSpellDmg;
	ConVar ShowGem;
	ConVar ShowVisibility;
	ConVar PredictCourier;

	namespace ParticleMaphack
	{
		ConVar Enable;
		ConVar Size;
	}

	ConVar Weather;
	ConVar CameraDistance;
	ConVar RangeDisplay;
	ConVar NoFoW;
	//ConVar AutoMinigame;
	ConVar CrashFriendsList;
	ConVar CustomStatus;

	void ParticleMaphackChanged(void* var, const char* pOldValue, float flOldValue)
	{
		static ConVar* dota_use_particle_fow = I::Cvar->FindVar("dota_use_particle_fow");
		dota_use_particle_fow->m_nFlags &= ~FCVAR_CHEAT;
		dota_use_particle_fow->SetValue(!ParticleMaphack::Enable.GetInt());
	}

	void WeatherChanged(void* var, const char* pOldValue, float flOldValue)
	{
		static ConVar* cl_weather = I::Cvar->FindVar("cl_weather");
		cl_weather->m_nFlags &= ~FCVAR_CHEAT;
		cl_weather->SetValue(Weather.GetInt());
	}

	void CameraDistanceChanged(void* var, const char* pOldValue, float flOldValue)
	{
		static ConVar* dota_camera_distance = I::Cvar->FindVar("dota_camera_distance");
		dota_camera_distance->m_nFlags &= ~FCVAR_CHEAT;
		dota_camera_distance->SetValue(CameraDistance.GetInt());
	}

	void RangeDisplayChanged(void* var, const char* pOldValue, float flOldValue)
	{
		static ConVar* dota_range_display = I::Cvar->FindVar("dota_range_display");
		dota_range_display->SetValue(RangeDisplay.GetInt());
	}

	void NoFoWChanged(void* var, const char* pOldValue, float flOldValue)
	{
		static ConVar* fog_enable = I::Cvar->FindVar("fog_enable");
		fog_enable->m_nFlags &= ~FCVAR_CHEAT;
		fog_enable->SetValue(!NoFoW.GetInt());
	}

	void Save()
	{
		static char Path[MAX_PATH] = { 0 };
		if (!Path[0])
		{
			const char* gameDir = reinterpret_cast<const char* (*)(int)>(GetProcAddress(GetModuleHandle("tier0.dll"), "Plat_GetGameDirectory"))(0);
			if (!gameDir)
				return;

			strcpy_s(Path, sizeof(Path), gameDir);
			strcat_s(Path, sizeof(Path), "\\dota\\cfg\\heck.cfg");
		}

		FILE* pFile;
		if (fopen_s(&pFile, Path, "w") != 0)
		{
			Log::Msg("Failed to save config!\n");
			return;
		}

		for (size_t i = 0; i < g_CreatedConVars.size(); ++i)
			fprintf(pFile, "%s \"%s\"\n", g_CreatedConVars[i]->m_pszName, g_CreatedConVars[i]->GetString());

		fclose(pFile);

		Log::Msg("Successfully saved\n");
	}

	void Init()
	{
		AutoRune				.Create("heck_autorune",				"0", 0, nullptr, true, 0.f, true, 2.f);

		AutoStun				.Create("heck_autostun",				"0", 0, nullptr, true, 0.f, true, 1.f);
		AutoSilence				.Create("heck_autosilence",				"0", 0, nullptr, true, 0.f, true, 1.f);
		AutoEscape				.Create("heck_autoescape",				"0", 0, nullptr, true, 0.f, true, 1.f);

		ShowIllusions			.Create("heck_show_illusions",			"0", 0, nullptr, true, 0.f, true, 1.f);
		ShowCharge				.Create("heck_show_charge",				"0", 0, nullptr, true, 0.f, true, 1.f);
		ShowSpellDmg			.Create("heck_show_spell_dmg",			"0", 0, nullptr, true, 0.f, true, 1.f);
		ShowGem					.Create("heck_show_gem",				"0", 0, nullptr, true, 0.f, true, 1.f);
		ShowVisibility			.Create("heck_show_visibility",			"0", 0, nullptr, true, 0.f, true, 1.f);
		PredictCourier			.Create("heck_predict_courier",			"0", 0, nullptr, true, 0.f, true, 1.f);

		ParticleMaphack::Enable	.Create("heck_particle_maphack_enable",	"0", 0, nullptr, true, 0.f, true, 1.f,			&ParticleMaphackChanged);
		ParticleMaphack::Size	.Create("heck_particle_maphack_size",	"750", 0, nullptr, true, 500.f, true, 1500.f);
		Weather					.Create("heck_weather",					"0", 0, nullptr, true, 0.f, true, 9.f,			&WeatherChanged);
		CameraDistance			.Create("heck_camera_distance",			"1200", 0, nullptr, true, 1200.f, true, 5000.f,	&CameraDistanceChanged);
		RangeDisplay			.Create("heck_range_display",			"0", 0, nullptr, true, 0.f, true, 2000.f,		&RangeDisplayChanged);
		NoFoW					.Create("heck_no_fow",					"0", 0, nullptr, true, 0.f, true, 1.f,			&NoFoWChanged);
		//AutoMinigame			.Create("heck_autominigame",			"0", 0, nullptr, true, 0.f, true, 1.f);
		CrashFriendsList		.Create("heck_crash_friendslist",		"0", 0, nullptr, true, 0.f, true, 1.f);
		CustomStatus			.Create("heck_custom_status",			"",	0, nullptr);

		I::InputService->EnableKeyBindingSystem(false);
		I::EngineClient->ClientCmd_Unrestricted("exec heck");
	}
}