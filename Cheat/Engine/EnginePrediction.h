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

	void Begin(CUserCmd* cmd)
	{
		_curtime_backup = I::GlobalVars()->curtime;
		_frametime_backup = I::GlobalVars()->frametime;

		if (!_prevcmd || _prevcmd->hasbeenpredicted)
			_fixedtick = CGlobal::LocalPlayer->GetTickBase();
		else 
			_fixedtick++;

		if (!_prediction_seed || !_prediction_player) 
		{
			_prediction_seed = *(int32_t**)(CSX::Memory::FindPatternV2("client_panorama.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 0x2);
			_prediction_player = (CBaseEntity***)(CSX::Memory::FindPatternV2("client_panorama.dll", "89 35 ? ? ? ? F3 0F 10 48 20") + 0x2);
		}

		if (_prediction_seed)
			*_prediction_seed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

		if (_prediction_player)
			**_prediction_player = CGlobal::LocalPlayer;

		CGlobal::LocalPlayer->GetCurrentCommand() = cmd;

		I::GlobalVars()->curtime = _fixedtick * I::GlobalVars()->interval_per_tick;
		I::GlobalVars()->frametime = I::GlobalVars()->interval_per_tick;

		bool _inpred_backup = *(bool*)((uintptr_t)I::Prediction() + 0x8);

		memset(&_movedata, 0, sizeof(CMoveData));

		*(bool*)((uintptr_t)I::Prediction() + 0x8) = true;

		I::MoveHelper()->SetHost(CGlobal::LocalPlayer);
		I::GameMovement()->StartTrackPredictionErrors(CGlobal::LocalPlayer);
		I::Prediction()->SetupMove(CGlobal::LocalPlayer, cmd, I::MoveHelper(), &_movedata);
		I::GameMovement()->ProcessMovement(CGlobal::LocalPlayer, &_movedata);
		I::Prediction()->FinishMove(CGlobal::LocalPlayer, cmd, &_movedata);
		I::GameMovement()->FinishTrackPredictionErrors(CGlobal::LocalPlayer);
		I::MoveHelper()->SetHost(nullptr);

		*(bool*)((uintptr_t)I::GlobalVars() + 0x8) = _inpred_backup;

		if (_prediction_player)
			**_prediction_player = nullptr;

		if (_prediction_seed)
			*_prediction_seed = -1;

		_prevcmd = cmd;
	}

	void End() 
	{
		I::GlobalVars()->curtime = _curtime_backup;
		I::GlobalVars()->frametime = _frametime_backup;
		I::GameMovement()->Reset();
	}
}