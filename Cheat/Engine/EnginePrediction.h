#include "../Main.h"
#include "../Include/Def.h"
#include "../Initialize/Offsets.h"
#include "SDK/SDK.h"
#include "Entity.h"
#include "Weapon.h"
#include "EntityMem.h"

namespace Engine
{
	class CBaseEntity;
}
using namespace Engine;

namespace SDK
{
	float _curtime_backup;
	float _frametime_backup;
	CMoveData _movedata;
	CUserCmd* _prevcmd;
	int _fixedtick;
	int32_t* _prediction_seed;
	CBaseEntity*** _prediction_player;

	void BeginPrediction(CUserCmd* cmd)
	{
		CBaseEntity* g_LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());
		_curtime_backup = I::GlobalVars()->curtime;
		_frametime_backup = I::GlobalVars()->frametime;

		if (!_prevcmd || _prevcmd->hasbeenpredicted)
			_fixedtick = g_LocalPlayer->GetTickBase();
		else
			_fixedtick++;

		if (!_prediction_seed || !_prediction_player)
		{
			_prediction_seed = *(int32_t**)(CSX::Memory::FindPatternV2(XorStr("client_panorama.dll"), XorStr("8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04")) + 0x2);
			_prediction_player = (CBaseEntity***)(CSX::Memory::FindPatternV2(XorStr("client_panorama.dll"), XorStr("89 35 ? ? ? ? F3 0F 10 48 20")) + 0x2);
		}

		if (_prediction_seed)
			*_prediction_seed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

		if (_prediction_player)
			**_prediction_player = g_LocalPlayer;

		g_LocalPlayer->GetCurrentCommand() = cmd;

		I::GlobalVars()->curtime = _fixedtick * I::GlobalVars()->interval_per_tick;
		I::GlobalVars()->frametime = I::GlobalVars()->interval_per_tick;

		bool _inpred_backup = *(bool*)((uintptr_t)I::Prediction() + 0x8);

		memset(&_movedata, 0, sizeof(CMoveData));

		*(bool*)((uintptr_t)I::Prediction() + 0x8) = true;

		//g_LocalPlayer->SetLocalViewangles(Vector(cmd->viewangles.pitch, cmd->viewangles.yaw, cmd->viewangles.roll));

		I::MoveHelper()->SetHost((IClientEntity*)g_LocalPlayer);

		I::GameMovement()->StartTrackPredictionErrors(g_LocalPlayer);
		I::Prediction()->SetupMove(g_LocalPlayer, cmd, I::MoveHelper(), &_movedata);
		I::GameMovement()->ProcessMovement(g_LocalPlayer, &_movedata);
		I::Prediction()->FinishMove(g_LocalPlayer, cmd, &_movedata);
		//g_MoveHelper->unknown_func();
		I::GameMovement()->FinishTrackPredictionErrors(g_LocalPlayer);

		*(bool*)((uintptr_t)I::Prediction() + 0x8) = _inpred_backup;

		if (_prediction_player)
			**_prediction_player = nullptr;

		if (_prediction_seed)
			*_prediction_seed = -1;

		g_LocalPlayer->GetCurrentCommand() = nullptr;

		I::MoveHelper()->SetHost(nullptr);

		_prevcmd = cmd;
	}
	void EndPrediction()
	{
		I::GlobalVars()->curtime = _curtime_backup;
		I::GlobalVars()->frametime = _frametime_backup;
		I::GameMovement()->Reset();
	}
}
