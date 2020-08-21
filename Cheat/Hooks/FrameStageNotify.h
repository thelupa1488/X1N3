#pragma once
#include "Tables.h"

void __fastcall hkFrameStageNotify(void* ecx, void* edx, ClientFrameStage_t Stage)
{
	static auto ofunc = HookTables::pFrameStageNotify->GetTrampoline();

	if (GP_Skins && CGlobal::IsGameReady && Stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		GP_Skins->PostDataUpdate();

	if (GP_Esp && CGlobal::IsGameReady && Stage == FRAME_NET_UPDATE_END)
		GP_Esp->SoundFrameStage();

	ofunc(ecx, Stage);
}

