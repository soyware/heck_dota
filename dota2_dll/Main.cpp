#include "stdafx.h"
#include "SDK/Misc.h"
#include "SDK/Vector.h"
#include "SDK/Color.h"
#include "SDK/Logging.h"
#include "Signatures.h"
#include "SDK/Panorama/Panorama.h"
#include "SDK/Interfaces/Interfaces.h"
#include "SDK/Globals.h"
#include "SDK/Panorama/UIPanel.h"
#include "SDK/Panorama/Panel2D.h"
#include "SDK/Panorama/UIEvent.h"
#include "SDK/ConVar.h"
#include "Settings.h"
#include "Menu.h"
#include "Schema.h"

#include "SDK/Entity.h"
#include "SDK/GameRules.h"
#include "SDK/Ability.h"
#include "SDK/Modifier.h"
#include "SDK/Item.h"
#include "SDK/NPC.h"
#include "SDK/Player.h"
#include "SDK/Particle.h"

#include "Draw.h"
#include "Features/Features.h"
#include "VTH.h"
#include "Hooks/Hooks.h"

HINSTANCE g_hModule;

#if _DEBUG
void DumpClassIds()
{
	std::string str = "enum class ClassID\n{";
	for (ClientClass* cc = I::Client->GetAllClasses(); cc != nullptr; cc = cc->m_pNext)
	{
		str += "\t";
		str += cc->m_pClassName;
		str += " = ";
		str += cc->m_pszClassID;
		str += ",\n";
	}
	str += "};";
	__debugbreak();
}
#endif // _DEBUG

void FatalError(const char* err)
{
#if _DEBUG
	__debugbreak();
#else

	I::EngineClient->ClientCmd_Unrestricted("showconsole");

	//static CCommand empty;

	//static ConCommand* showconsole = I::Cvar->FindCommand("showconsole");
	//showconsole->Dispatch(empty);

	Log::Msg(Color::Red(), "FATAL ERROR: %s\n", err);
	Log::Msg(Color::Red(), "Game will shutdown in 5 sec...\n");

	std::this_thread::sleep_for(5s);

	I::EngineClient->ClientCmd_Unrestricted("quit");

	//static ConCommand* quit = I::Cvar->FindCommand("quit");
	//quit->Dispatch(empty);

#endif // _DEBUG
}

void Uninject()
{
	Log::Msg("Uninjecting\n");
	Menu::Close();
	Hooks::Unhook();

	std::thread([]() {
		FreeLibrary(g_hModule);
	}).detach();
}

void Init(HINSTANCE hModule)
{
	while (!GetModuleHandle("navsystem.dll"))
		std::this_thread::sleep_for(10s);

	if (!GetModuleHandle("vgui2.dll"))
	{
		MessageBox(NULL, "Enable console and add -vguiconsole to lunch params for cheat to work", NULL, MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(hModule, 0);
	}

	g_hModule = hModule;

	Log::Init();
	Signatures::Init();
	I::Init();
	G::Init();
	Schema::Init();
	Settings::Init();
	Draw::Init();
	Hooks::Init();

	Log::Msg("Initialized. Build date: " __DATE__ "\n");
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD ulReason, LPVOID)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), hModule, 0, 0);
	}
	return TRUE;
}