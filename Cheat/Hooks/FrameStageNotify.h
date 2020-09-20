#pragma once
#include "Tables.h"

void __fastcall hkFrameStageNotify(void* ecx, void* edx, ClientFrameStage_t Stage)
{
	static auto ofunc = HookTables::pFrameStageNotify->GetTrampoline();

	if (GP_Skins && CGlobal::IsGameReady)
		GP_Skins->PostDataUpdate(Stage);

	if (GP_Esp && CGlobal::IsGameReady)
		GP_Esp->SoundFrameStage(Stage);

	if (GP_Misc && CGlobal::IsGameReady)
		GP_Misc->FrameStageNotify(Stage);

	ofunc(ecx, Stage);
}

