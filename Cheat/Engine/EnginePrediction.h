#pragma once
#include "Engine.h"

namespace EnginePrediction
{
	float curtime_backup;
	float frametime_backup;
	CMoveData movedata;
	CUserCmd* prevcmd;
	int fixedtick;

	int32_t* prediction_seed;
	CBaseEntity*** prediction_player;

	void Begin(CUserCmd* pCmd)
	{
		curtime_backup = I::GlobalVars()->curtime;
		frametime_backup = I::GlobalVars()->frametime;

		if (!prevcmd || prevcmd->hasbeenpredicted)
			fixedtick = CGlobal::LocalPlayer->GetTickBase();
		else 
			fixedtick++;

		if (!prediction_seed || !prediction_player) 
		{
			prediction_seed = *(int32_t**)(Utils::PatternScan(clientFactory, XorStr("8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04")) + 2);
			prediction_player = (CBaseEntity***)(Utils::PatternScan(clientFactory, XorStr("89 35 ? ? ? ? F3 0F 10 48 20")) + 2);
		}

		if (prediction_seed)
			*prediction_seed = MD5_PseudoRandom(pCmd->command_number) & 0x7FFFFFFF;

		if (prediction_player) 
			**prediction_player = CGlobal::LocalPlayer;

		CGlobal::LocalPlayer->GetCurrentCommand() = pCmd;

		I::GlobalVars()->curtime = fixedtick * I::GlobalVars()->interval_per_tick;
		I::GlobalVars()->frametime = I::GlobalVars()->interval_per_tick;

		bool inpred_backup = *(bool*)((uintptr_t)I::Prediction() + 8);

		memset(&movedata, 0, sizeof(CMoveData));

		*(bool*)((uintptr_t)I::Prediction() + 8) = true;

		I::MoveHelper()->SetHost(CGlobal::LocalPlayer);
		I::GameMovement()->StartTrackPredictionErrors(CGlobal::LocalPlayer);
		I::Prediction()->SetupMove(CGlobal::LocalPlayer, pCmd, I::MoveHelper(), &movedata);
		I::GameMovement()->ProcessMovement(CGlobal::LocalPlayer, &movedata);
		I::Prediction()->FinishMove(CGlobal::LocalPlayer, pCmd, &movedata);
		I::GameMovement()->FinishTrackPredictionErrors(CGlobal::LocalPlayer);

		*(bool*)((uintptr_t)I::GlobalVars() + 8) = inpred_backup;

		if (prediction_player)
			**prediction_player = nullptr;

		if (prediction_seed)
			*prediction_seed = -1;

	    CGlobal::LocalPlayer->GetCurrentCommand() = nullptr;
		I::MoveHelper()->SetHost(nullptr);

		prevcmd = pCmd;
	}

	void End() 
	{
		I::GlobalVars()->curtime = curtime_backup;
		I::GlobalVars()->frametime = frametime_backup;
		I::GameMovement()->Reset();
	}
}