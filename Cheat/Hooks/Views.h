#pragma once
#include "Tables.h"

bool WINAPI OverrideView(CViewSetup* pSetup)
{
	if (GP_Misc)
		GP_Misc->OverrideView(pSetup);

	if (GP_Esp && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
		if (GP_Esp->GranadePrediction)
			grenade_prediction::Get().View();

	//if (GP_Misc)
	//	GP_Misc->Thirdperson();

	return HookTables::pOverrideView->GetTrampoline()(pSetup);
}

float WINAPI GetViewModelFOV()
{
	float fov = HookTables::pGetViewModelFOV->GetTrampoline()();

	if (GP_Misc && !CGlobal::FullUpdateCheck)
		GP_Misc->GetViewModelFOV(fov);

	return fov;
}

void __fastcall LockCursor(void* thisptr, int edx)
{
	HookTables::pLockCursor->GetTrampoline()(thisptr);

	if (CGlobal::IsGuiVisble)
		I::Surface()->UnlockCursor();
}