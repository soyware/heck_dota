#pragma once

#define INDEX_SKIP_PLAYERS (1 + 64 + DOTA_TEAM_COUNT)

/*
inline bool IsTyping()
{
	return *reinterpret_cast<bool*>(Signatures::bOverlayOpen) ||
		I::ClientMode->GetMessageMode();
}
*/

#include "Visuals.h"
#include "Moves.h"