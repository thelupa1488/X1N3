#pragma once
#include "Engine.h"

namespace EnginePrediction
{
	float _curtime_backup;
	float _frametime_backup;
	CMoveData _movedata;
	CUserCmd* _prevcmd;
	int _fixedtick;

	int32_t* _prediction_seed;
	CBaseEntity*** _prediction_player;

	void Begin(CUserCmd* pCmd)
	{
		_curtime_backup = I::GlobalVars()->curtime;
		_frametime_backup = I::GlobalVars()->frametime;

		if (!_prevcmd || _prevcmd->hasbeenpredicted)
			_fixedtick = CGlobal::LocalPlayer->GetTickBase();
		else 
			_fixedtick++;

		if (!_prediction_seed || !_prediction_player) 
		{
			_prediction_seed = *(int32_t**)(CSX::Memory::FindPatternV2(clientFactory, XorStr("8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04")) + 2);
			_prediction_player = (CBaseEntity***)(CSX::Memory::FindPatternV2(clientFactory, XorStr("89 35 ? ? ? ? F3 0F 10 48 20")) + 2);
		}

		if (_prediction_seed)
			*_prediction_seed = MD5_PseudoRandom(pCmd->command_number) & 0x7FFFFFFF;

		if (_prediction_player)			**_prediction_player = CGlobal::LocalPlayer;

		CGlobal::LocalPlayer->GetCurrentCommand() = pCmd;

		I::GlobalVars()->curtime = _fixedtick * I::GlobalVars()->interval_per_tick;
		I::GlobalVars()->frametime = I::GlobalVars()->interval_per_tick;

		bool _inpred_backup = *(bool*)((uintptr_t)I::Prediction() + 8);

		memset(&_movedata, 0, sizeof(CMoveData));

		*(bool*)((uintptr_t)I::Prediction() + 8) = true;

		I::MoveHelper()->SetHost(CGlobal::LocalPlayer);
		I::GameMovement()->StartTrackPredictionErrors(CGlobal::LocalPlayer);
		I::Prediction()->SetupMove(CGlobal::LocalPlayer, pCmd, I::MoveHelper(), &_movedata);
		I::GameMovement()->ProcessMovement(CGlobal::LocalPlayer, &_movedata);
		I::Prediction()->FinishMove(CGlobal::LocalPlayer, pCmd, &_movedata);
		I::GameMovement()->FinishTrackPredictionErrors(CGlobal::LocalPlayer);

		*(bool*)((uintptr_t)I::GlobalVars() + 8) = _inpred_backup;

		if (_prediction_player)
			**_prediction_player = nullptr;

		if (_prediction_seed)
			*_prediction_seed = -1;

	    CGlobal::LocalPlayer->GetCurrentCommand() = nullptr;
		I::MoveHelper()->SetHost(nullptr);

		_prevcmd = pCmd;
	}

	void End() 
	{
		I::GlobalVars()->curtime = _curtime_backup;
		I::GlobalVars()->frametime = _frametime_backup;
		I::GameMovement()->Reset();
	}
}