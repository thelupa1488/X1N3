#pragma once
#include "Tables.h"

bool WINAPI hkOverrideView(CViewSetup* pSetup)
{
	if (GP_Misc)
		GP_Misc->OverrideView(pSetup);

	if (GP_Esp && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
		if (GP_Esp->GranadePrediction)
			grenade_prediction::Get().View();

	return HookTables::pOverrideView->GetTrampoline()(pSetup);
}

float WINAPI hkGetViewModelFOV()
{
	float fov = HookTables::pGetViewModelFOV->GetTrampoline()();

	if (GP_Misc && !CGlobal::FullUpdateCheck)
		GP_Misc->GetViewModelFOV(fov);

	return fov;
}

void __fastcall hkLockCursor(void* thisptr, int edx)
{
	HookTables::pLockCursor->GetTrampoline()(thisptr);

	if (CGlobal::IsGuiVisible)
		I::Surface()->UnlockCursor();
}