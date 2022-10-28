#pragma once

namespace Hooks
{
	typedef const ConVar* (__thiscall* FindVarFn)(CCvar*, const char*);
	FindVarFn oFindVar;

	const ConVar* FindVar(CCvar* _this, const char* name)
	{
		void* stack;
		CaptureStackBackTrace(3, 1, &stack, 0);

		if (reinterpret_cast<uintptr_t>(stack) == Signatures::C_DOTA_BaseNPC__UpdateSelectionRing__sv_cheats_ReturnAddress)
			return oFindVar(_this, "dota_range_display");

		return oFindVar(_this, name);
	}
}