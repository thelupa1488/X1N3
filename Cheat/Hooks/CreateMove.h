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
		QAngle angleold = pCmd->viewangles;
		CCSGOPlayerAnimState g_AnimState;

		if (bReturn)
			I::Prediction()->SetLocalViewangles(Vector(pCmd->viewangles.x, pCmd->viewangles.y, pCmd->viewangles.z));

		if (GP_EntPlayers)
			GP_EntPlayers->Update();

		if (GP_Esp)
			if (GP_Esp->GranadePrediction)
				grenade_prediction::Get().Tick(pCmd->buttons);

		DWORD* FirstP;
		__asm mov FirstP, ebp;

		bool bSendPacket = true;

		if (CGlobal::IsGuiVisble)
			pCmd->buttons &= ~IN_ATTACK;
		else if (GP_Skins && !CGlobal::IsGuiVisble)
			GP_Skins->SelectedWeapon = CGlobal::GetWeaponId();

		if (GP_LegitAim)
		{
			GP_LegitAim->SetSelectedWeapon();

			GP_LegitAim->BacktrackCreateMove(pCmd);

			if (GP_LegitAim->Enable)
				GP_LegitAim->CreateMove(bSendPacket, flInputSampleTime, pCmd);

			if (GP_LegitAim->TriggerEnable)
				GP_LegitAim->TriggerCreateMove(pCmd);
		}
		if (GP_Misc)
		{
			if (GP_Misc->ShowCompetitiveRank && pCmd->buttons & IN_SCORE)
				GP_Misc->RankReveal();

			GP_Misc->CreateMove(bSendPacket, flInputSampleTime, pCmd);

			if (GP_Misc->Desync && I::ClientState()->chokedcommands >= GP_Misc->MaxChokeTicks())
			{
				bSendPacket = true;
				pCmd->viewangles = I::ClientState()->viewangles;
			}

			GP_Misc->EnginePrediction(bSendPacket, pCmd);

			CGlobal::CorrectMouse(pCmd);

			auto anim_state = CGlobal::LocalPlayer->GetBasePlayerAnimState();
			if (anim_state) 
			{
				CCSGOPlayerAnimState anim_state_backup = *anim_state;
				*anim_state = g_AnimState;
				CGlobal::LocalPlayer->GetVAngles() = pCmd->viewangles;
				//CGlobal::LocalPlayer->UpdateClientSideAnimation(); //need fix

				GP_Misc->UpdateLBY(anim_state);

				g_AnimState = *anim_state;
				*anim_state = anim_state_backup;
			}
			if (bSendPacket)
			{
				GP_Misc->anglereal = g_AnimState.m_flGoalFeetYaw;
				GP_Misc->view = pCmd->viewangles.y;
				if (anim_state)
					GP_Misc->anglefake = anim_state->m_flGoalFeetYaw;
				GP_Misc->vangle = pCmd->viewangles;
			}

			FixMovement(pCmd, angleold);
		}

		CGlobal::ClampAngles(pCmd->viewangles);
		CGlobal::AngleNormalize(pCmd->viewangles);
		*(bool*)(*FirstP - 0x1C) = bSendPacket;

		if (!bSendPacket)
			return false;
	}

	return bReturn;
}