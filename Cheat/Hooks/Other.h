#include "Tables.h"

int __fastcall DoPostScreenEffects(void* ecx, int edx, int a1)
{
	static auto oDoPostScreenEffects = HookTables::pDoPostScreenEffects->GetTrampoline();

	if (GP_Esp && CGlobal::IsGameReady)
		GP_Esp->DrawGlow();

	return oDoPostScreenEffects(ecx, a1);
}