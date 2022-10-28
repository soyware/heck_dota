#pragma once

namespace Hooks
{
	typedef void(__thiscall* RPUpdateFn)(CDOTARichPresence*, void*);
	RPUpdateFn oRPUpdate;

	void RPUpdate(CDOTARichPresence* _this, void* eventclientupdate)
	{
		oRPUpdate(_this, eventclientupdate);

		static std::chrono::time_point<std::chrono::steady_clock> lastUpdate;
		auto curTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(curTime - lastUpdate);

		if (5 < elapsed.count())
		{
			lastUpdate = curTime;

			if (Settings::CrashFriendsList.GetInt())
			{
				const char* params[] =
				{
					"#DOTA_RP_LOBBY_CUSTOM",
					"xyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\nxyecoc.club\n",
					"#DOTA_RP_PLAYING_AS"
				};
				_this->SetRPStatus("#DOTA_RP_PLAYING_AS", 3, params);
			}
			else if (Settings::CustomStatus.GetString()[0])
			{
				const char* params[] = { Settings::CustomStatus.GetString() };
				_this->SetRPStatus("#DOTA_RP_LOBBY_CUSTOM", 1, params);
			}
		}
	}
}