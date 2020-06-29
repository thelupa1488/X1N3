#pragma once
#include "Tables.h"

void __fastcall hkEmitSound(IEngineSound* thisptr, int edx, IRecipientFilter& filter, int nEntityIndex, int iChannel, const char* szSoundEntry, 
	unsigned int uSoundEntryHash, const char* szSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vector* vecOrigin, 
	const Vector* vecDirection, CUtlVector<Vector>* pUtlVecOrigins, bool bUpdatePositions, int flSoundTime, int nSpeakerEntity, SndInfo_t& parameters)
{
	static auto oEmitSound = HookTables::pEmitSound->GetTrampoline();

	// @note: for sound esp use: "player/footsteps", "player/land", "clipout" sounds check

	//if (GP_Misc && !strcmp(szSoundEntry, XorStr("UIPanorama.popup_accept_match_beep")))
	//	GP_Misc->AutoAcceptEmit();

	oEmitSound(thisptr, edx, filter, nEntityIndex, iChannel, szSoundEntry, uSoundEntryHash, szSample, flVolume, flAttenuation, nSeed, iFlags, iPitch, 
		vecOrigin, vecDirection, pUtlVecOrigins, bUpdatePositions, flSoundTime, nSpeakerEntity, parameters);
}

void __fastcall hkPlaySound(void* thisptr, int edx, const char* pszSoundName)
{
	static auto oPlaySound = HookTables::pPlaySound->GetTrampoline();

	oPlaySound(thisptr, pszSoundName);
}