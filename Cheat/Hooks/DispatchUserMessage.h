#pragma once
#include "Tables.h"

bool __fastcall DispatchUserMessage(void* ecx, void* edx, int type, unsigned int a3, unsigned int length, const void* msg_data)
{
	static auto ofunc = HookTables::pDispatchUserMessage->GetTrampoline();

	if (GP_Misc && I::Engine()->IsConnected())
		GP_Misc->Anti_Kick(type, a3, length, msg_data);

	return ofunc(ecx, type, a3, length, msg_data);
}