#include "EnginePrediction.h"

namespace EnginePrediction
{
	int unPredFlags;
	float CurtimeBackup;
	float FrametimeBackup;
	CMoveData MoveData;
	CUserCmd* PrevCmd;
	int FixedTick;
	int32_t* PredictionSeed;
	CBaseEntity*** PredictionPlayer;

	void EnginePrediction::Run(CUserCmd* pCmd)
	{
		unPredFlags = CGlobal::LocalPlayer->GetFlags();
		CurtimeBackup = I::GlobalVars()->curtime;
		FrametimeBackup = I::GlobalVars()->frametime;

		if (!PrevCmd || PrevCmd->hasbeenpredicted)
			FixedTick = CGlobal::LocalPlayer->GetTickBase();
		else
			FixedTick++;

		if (!PredictionSeed || !PredictionPlayer)
		{
			PredictionSeed = *reinterpret_cast<int32**>(offsets["PredictionSeed"]);
			PredictionPlayer = reinterpret_cast<CBaseEntity***>(offsets["PredictionPlayer"]);
		}

		if (PredictionSeed)
			*PredictionSeed = MD5_PseudoRandom(pCmd->command_number) & 0x7FFFFFFF;

		if (PredictionPlayer)
			**PredictionPlayer = CGlobal::LocalPlayer;

		CGlobal::LocalPlayer->GetCurrentCommand() = pCmd;

		I::GlobalVars()->curtime = FixedTick * I::GlobalVars()->interval_per_tick;
		I::GlobalVars()->frametime = I::GlobalVars()->interval_per_tick;

		bool inPredBackup = *(bool*)((uintptr_t)I::Prediction() + 8);

		memset(&MoveData, 0, sizeof(CMoveData));

		*(bool*)((uintptr_t)I::Prediction() + 8) = true;

		I::MoveHelper()->SetHost(CGlobal::LocalPlayer);
		I::GameMovement()->StartTrackPredictionErrors(CGlobal::LocalPlayer);
		I::Prediction()->SetupMove(CGlobal::LocalPlayer, pCmd, I::MoveHelper(), &MoveData);
		I::GameMovement()->ProcessMovement(CGlobal::LocalPlayer, &MoveData);
		I::Prediction()->FinishMove(CGlobal::LocalPlayer, pCmd, &MoveData);
		I::GameMovement()->FinishTrackPredictionErrors(CGlobal::LocalPlayer);

		*(bool*)((uintptr_t)I::Prediction() + 8) = inPredBackup;

		if (PredictionPlayer)
			**PredictionPlayer = nullptr;

		if (PredictionSeed)
			*PredictionSeed = -1;

		CGlobal::LocalPlayer->GetCurrentCommand() = nullptr;
		I::MoveHelper()->SetHost(nullptr);

		PrevCmd = pCmd;
	}

	void EnginePrediction::End()
	{
		I::GlobalVars()->curtime = CurtimeBackup;
		I::GlobalVars()->frametime = FrametimeBackup;
		I::GameMovement()->Reset();
	}

	int EnginePrediction::GetFlags()
	{
		return unPredFlags;
	}
}
