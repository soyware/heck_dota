#pragma once

namespace Hooks
{
	typedef void(__thiscall* StartSoundEventNameFn)(CSoundOpSystem*, int*, const char*, int64_t, char, short, int64_t, int32_t);
	StartSoundEventNameFn oStartSoundEventName;

	void StartSoundEventName(CSoundOpSystem* _this, int* a2, const char* soundName, int64_t a4, char a5, short a6, int64_t a7, int32_t a8)
	{
		oStartSoundEventName(_this, a2, soundName, a4, a5, a6, a7, a8);
	}
}