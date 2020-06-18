#pragma once
#include "Tables.h"

void __fastcall hkFrameStageNotify(void* ecx, void* edx, int Stage)
{
	static auto ofunc = HookTables::pFrameStageNotify->GetTrampoline();

	if ((ClientFrameStage_t)Stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START && CGlobal::IsGameReady && GP_Skins)
	{
		if (GP_Skins->SkinsEnable)
			GP_Skins->PostDataUpdate();
	}

	if (GP_Esp && CGlobal::IsGameReady && (ClientFrameStage_t)Stage == ClientFrameStage_t::FRAME_NET_UPDATE_END)
	{
		if (GP_Esp->SoundEspEnable)
			GP_Esp->SoundFrameStage();
	}

	if (GP_Misc && CGlobal::IsGameReady && (ClientFrameStage_t)Stage == ClientFrameStage_t::FRAME_RENDER_START)
	{
		if (GP_Misc->Enable)
			GP_Misc->FrameStageNotify();
	}

	ofunc(ecx, Stage);
}

