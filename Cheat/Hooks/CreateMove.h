#pragma once
#include "Tables.h"

bool __stdcall hkCreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	bool bReturn = HookTables::pCreateMove->GetTrampoline()(flInputSampleTime, pCmd);

	if (CGlobal::IsGameReady && pCmd->command_number != 0 && !CGlobal::FullUpdateCheck)
	{
		CGlobal::GViewAngle = pCmd->viewangles;
		CGlobal::UserCmd = pCmd;
		CGlobal::LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

		if (bReturn)
			I::Prediction()->SetLocalViewangles(Vector(pCmd->viewangles.x, pCmd->viewangles.y, pCmd->viewangles.z));

		if (GP_EntPlayers)
			GP_EntPlayers->Update();

		if (GP_Esp)
			if (GP_Esp->GranadePrediction)
				grenade_prediction::Get().Tick(pCmd->buttons);

		uintptr_t* FPointer; __asm { MOV FPointer, EBP }
		byte* SendPacket = (byte*)(*FPointer - 0x1C);

		CGlobal::bSendPacket = *SendPacket;

		if (CGlobal::IsGuiVisble)
			pCmd->buttons &= ~IN_ATTACK;
		else if (GP_Skins && !CGlobal::IsGuiVisble)
			GP_Skins->SelectedWeapon = CGlobal::GetWeaponId();

		if (GP_LegitAim)
		{
			GP_LegitAim->SetSelectedWeapon();

			GP_LegitAim->BacktrackCreateMove(pCmd);

			if (GP_LegitAim->Enable)
				GP_LegitAim->CreateMove(CGlobal::bSendPacket, flInputSampleTime, pCmd);

			if (GP_LegitAim->TriggerEnable)
				GP_LegitAim->TriggerCreateMove(pCmd);
		}
		if (GP_Misc)
		{
			if (GP_Misc->ShowCompetitiveRank && pCmd->buttons & IN_SCORE)
				GP_Misc->RankReveal();

			GP_Misc->CreateMove(CGlobal::bSendPacket, flInputSampleTime, pCmd);

			if (GP_Misc->Desync && I::ClientState()->chokedcommands >= GP_Misc->MaxChokeTicks())
			{
				CGlobal::bSendPacket = true;
				pCmd->viewangles = I::ClientState()->viewangles;
			}
			GP_Misc->EnginePrediction(CGlobal::bSendPacket, pCmd);
		}

		CGlobal::ClampAngles(pCmd->viewangles);
		CGlobal::AngleNormalize(pCmd->viewangles);
		*SendPacket = CGlobal::bSendPacket;

		if (!CGlobal::bSendPacket)
			return false;
	}

	return bReturn;
}