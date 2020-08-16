#include "CGlobalVarsBase.hpp"
#include "../Engine.h"

namespace SDK
{
	float CGlobalVarsBase::ServerTime(CUserCmd* pCmd)
	{
        static int tick;
        static CUserCmd* lastCmd;

        if (pCmd) 
        {
            if (CGlobal::LocalPlayer && (!lastCmd || lastCmd->hasbeenpredicted))
                tick = CGlobal::LocalPlayer->GetTickBase();
            else
                tick++;
            lastCmd = pCmd;
        }
        return tick * interval_per_tick;
	}
}