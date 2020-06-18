#include "Tables.h"

int __fastcall hkDoPostScreenEffects(void* ecx, int edx, int a1)
{
	static auto oDoPostScreenEffects = HookTables::pDoPostScreenEffects->GetTrampoline();

	if (GP_Esp && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
		GP_Esp->DrawGlow();

	return oDoPostScreenEffects(ecx, a1);
}