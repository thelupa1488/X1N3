#pragma once
#include "Tables.h"

void __stdcall hkEmitSound(SoundData data)
{

	//if (GP_Misc && !strcmp(data.soundEntry, XorStr("UIPanorama.popup_accept_match_beep")))
	//	GP_Misc->AutoAcceptEmit();

	HookTables::pEmitSound->GetTrampoline()(data);
}

void __fastcall hkPlaySound(void* thisptr, int edx, const char* pszSoundName)
{
//	if (GP_Misc)
//		GP_Misc->PlaySound(pszSoundName); 
	HookTables::pPlaySound->GetTrampoline()(thisptr, pszSoundName);
}