#include "Tables.h"

int __fastcall hkDoPostScreenEffects(void* ecx, int edx, int a1)
{
	static auto oDoPostScreenEffects = HookTables::pDoPostScreenEffects->GetTrampoline();

	if (GP_Esp && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
		GP_Esp->DrawGlow();

	return oDoPostScreenEffects(ecx, a1);
}

int __fastcall hkRetrieveMessage(void* ecx, void* edx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	static auto oRetrieveMessage = HookTables::pRetrieveMessage->GetTrampoline();
	int iStatus = oRetrieveMessage(ecx, punMsgType, pubDest, cubDest, pcubMsgSize);

	if (iStatus != k_EGCResultOK)
		return iStatus;

	uint32_t messageType = *punMsgType & 0x7FFFFFFF;

	//if (GP_Misc && messageType == k_EMsgGCCStrike15_v2_GCToClientSteamdatagramTicket)
	//	GP_Misc->AutoAcceptEmit();

	GP_Inventory->PostRetrieveMessage(punMsgType, pubDest, cubDest, pcubMsgSize);

	return iStatus;
}

int __fastcall hkSendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData)
{
	static auto oSendMessage = HookTables::pSendMessage->GetTrampoline();

	uint32_t messageType = unMsgType & 0x7FFFFFFF;
	void* pubDataMutable = const_cast<void*>(pubData);

	GP_Inventory->PreSendMessage(unMsgType, pubDataMutable, cubData);

	int iStatus = oSendMessage(ecx, unMsgType, pubDataMutable, cubData);

	if (iStatus != k_EGCResultOK)
		return iStatus;

	return iStatus;
}