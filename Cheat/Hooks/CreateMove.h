#pragma once
#include "Tables.h"

void RankReveal()
{
	using ServerRankRevealAll = bool(__cdecl*)(int*);

	static auto fnServerRankRevealAll = reinterpret_cast<int(__thiscall*)(ServerRankRevealAll*, DWORD, void*)>
		(CSX::Memory::FindSignature(XorStr("client_panorama.dll"),
		XorStr("55 8B EC 8B 0D ? ? ? ? 85 C9 75 28 A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 04 85 C0 74 0B 8B C8 E8 ? ? ? ? 8B C8 EB 02 33 C9 89 0D ? ? ? ? 8B 45 08")));

	int v[3] = { 0,0,0 };

	reinterpret_cast<ServerRankRevealAll>(fnServerRankRevealAll)(v);
}

bool __fastcall SendNetMsg(NetChannel* pNetChan, void* edx, INetMessage& msg, bool bForceReliable, bool bVoice)
{
/*	
    if (msg.getType() == 14) // Return and don't send messsage if its FileCRCCheck
		return false;

	if (msg.GetGroup() == 9) // Fix lag when transmitting voice and fakelagging
		bVoice = true;
*/
	return HookTables::pSendNetMsg->GetTrampoline()(pNetChan, msg, bForceReliable, bVoice);
}

bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	bool bReturn = HookTables::pCreateMove->GetTrampoline()(flInputSampleTime, pCmd);

	if (CGlobal::IsGameReady && pCmd->command_number != 0 && !CGlobal::FullUpdateCheck)
	{
		CGlobal::GViewAngle = pCmd->viewangles;

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

			if (GP_LegitAim->Enable)
				GP_LegitAim->DesyncResolver();

			if (GP_LegitAim->TriggerEnable)
				GP_LegitAim->TriggerCreateMove(pCmd);
		}

		if (GP_Misc->ShowCompetitiveRank && pCmd->buttons & IN_SCORE)
			RankReveal();

		if (GP_Misc)
			GP_Misc->CreateMove(bSendPacket, flInputSampleTime, pCmd);

		if (GP_Misc)
			GP_Misc->Desync(pCmd, bSendPacket);

		CGlobal::ClampAngles(pCmd->viewangles);
		CGlobal::AngleNormalize(pCmd->viewangles);

		*(bool*)(*FirstP - 0x1C) = bSendPacket;

		if (!bSendPacket)
			return false;
	}

	return bReturn;
}
