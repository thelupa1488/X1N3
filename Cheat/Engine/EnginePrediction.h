#include "../Include/Def.h"
#include "Engine.h"

namespace Engine
{
	class CBaseEntity;
}
using namespace Engine;

namespace EnginePrediction
{
	float _curtime_backup;
	float _frametime_backup;
	CMoveData _movedata;
	CUserCmd* _prevcmd;
	int _fixedtick;

	int32_t* _prediction_seed;
	CBaseEntity* _prediction_player;

	void Begin(CUserCmd* cmd)
	{
		CBaseEntity* plocal = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

		if (!plocal)
			return;

		_curtime_backup = I::GlobalVars()->curtime;
		_frametime_backup = I::GlobalVars()->frametime;

		if (!_prevcmd || _prevcmd->hasbeenpredicted)
			_fixedtick = plocal->GetTickBase();
		else 
			_fixedtick++;

		if (!_prediction_seed || !_prediction_player) 
		{
			_prediction_seed = *(int32_t**)(CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), XorStr("8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04")) + 0x2);
			_prediction_player = (CBaseEntity*)(CSX::Memory::NewPatternScan(GetModuleHandleW(L"client_panorama.dll"), XorStr("89 35 ? ? ? ? F3 0F 10 48 20")) + 0x2);
		}

		if (_prediction_seed)
			*_prediction_seed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

		if (_prediction_player)
			_prediction_player = plocal;

		plocal->GetCurrentCommand() = cmd;

		I::GlobalVars()->curtime = _fixedtick * I::GlobalVars()->interval_per_tick;
		I::GlobalVars()->frametime = I::GlobalVars()->interval_per_tick;

		bool _inpred_backup = *(bool*)((uintptr_t)I::Prediction() + 0x8);

		memset(&_movedata, 0, sizeof(CMoveData));

		*(bool*)((uintptr_t)I::Prediction() + 0x8) = true;

		//g_LocalPlayer->SetLocalViewangles(Vector(cmd->viewangles.pitch, cmd->viewangles.yaw, cmd->viewangles.roll));

		I::MoveHelper()->SetHost(plocal);

		I::GameMovement()->StartTrackPredictionErrors(plocal);
		I::Prediction()->SetupMove(plocal, cmd, I::MoveHelper(), &_movedata);
		I::GameMovement()->ProcessMovement(plocal, &_movedata);
		I::Prediction()->FinishMove(plocal, cmd, &_movedata);
		//g_MoveHelper->unknown_func();
		I::GameMovement()->FinishTrackPredictionErrors(plocal);

		*(bool*)((uintptr_t)I::Prediction() + 0x8) = _inpred_backup;

		if (_prediction_player)
			_prediction_player = nullptr;

		if (_prediction_seed)
			*_prediction_seed = -1;

		plocal->GetCurrentCommand() = nullptr;

		I::MoveHelper()->SetHost(nullptr);

		_prevcmd = cmd;
	}

	void End() 
	{
		I::GlobalVars()->curtime = _curtime_backup;
		I::GlobalVars()->frametime = _frametime_backup;
		I::GameMovement()->Reset();
	}
}