/**
 * vim: set ts=4 :
 * =============================================================================
 * Left 4 Fix SourceMod Extension
 * Copyright (C) 2013 Spumer.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */
#ifndef _INCLUDE_SOURCEMOD_EVENT_ON_PLAYER_DEATH_H_
#define _INCLUDE_SOURCEMOD_EVENT_ON_PLAYER_DEATH_H_
#include "util.h"
#include "routine.h"
#include "extension.h"

using namespace Detours;

class PlayerDeath : public IGameEventListener2
{
	int GetEventDebugID(void) { return EVENT_DEBUG_ID_INIT; }
	void FireGameEvent(IGameEvent* pEvent)
	{
		int client = playerhelpers->GetClientOfUserId(pEvent->GetInt("userid"));
		if(client) {
			CBaseEntity *pPlayer = UTIL_GetCBaseEntity(client, true);
			if(pPlayer == NULL) return;
			IPlayerInfo *pInfo = playerhelpers->GetGamePlayer(client)->GetPlayerInfo();
			// if( *reinterpret_cast<uint8_t*>((unsigned char*)pPlayer + 588) == 2 ) {		// Get player team index
			// if(GET_TEAM(client) == 2) {
			if(pInfo && pInfo->GetTeamIndex() == 2) {
				r_nowDead( GetAbsOrigin(pPlayer), g_scores[client], g_players );
			}
		}
	}
};

#endif