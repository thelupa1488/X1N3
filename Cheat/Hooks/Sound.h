#pragma once
#include "Tables.h"

void __fastcall EmitSound(void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume,
	float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* pOrigin, const Vector* pDirection, Vector* pUtlVecOrigins, bool bUpdatePositions, float soundtime,
	int speakerentity, StartSoundParams_t& params)
{

	if (GP_Misc && !strcmp(pSoundEntry, XorStr("UIPanorama.popup_accept_match_beep")))
		CGlobal::AcceptMatchBeep = true;

	HookTables::pEmitSound->GetTrampoline()(ecx, edx, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume,
		flAttenuation, nSeed, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, params);
}

void __fastcall PlaySound(void* thisptr, int edx, const char* pszSoundName)
{
//	if (GP_Misc)
//		GP_Misc->PlaySound(pszSoundName); 
	HookTables::pPlaySound->GetTrampoline()(thisptr, pszSoundName);
}