#include "Bhop.h"
#include "FoxApi.h"
#include "CBasePlayer.h"

void FoxBhop::doBhop(CUserCmd* cmd)
{
	static bool jumped_last_tick = false;
	static bool should_fake_jump = false;

	stubCUserCmd* fakecmd = (stubCUserCmd*)cmd;
	stubPlayer* localPlayer = (stubPlayer*)FoxApi::g_EntityList->V_GetClientEntity(FoxApi::g_EngineClient->V_GetLocalPlayer());
	
	if (!jumped_last_tick && should_fake_jump)
	{
		should_fake_jump = false;
		fakecmd->buttons |= IN_JUMP;
	}
	else if (fakecmd->buttons & IN_JUMP)
	{
		if (localPlayer->flags & FL_ONGROUND)
		{
			jumped_last_tick = true;
			should_fake_jump = true;
		}
		else
		{
			fakecmd->buttons &= ~IN_JUMP;
			jumped_last_tick = false;
		}
	}
	else
	{
		jumped_last_tick = false;
		should_fake_jump = false;
	}
}

