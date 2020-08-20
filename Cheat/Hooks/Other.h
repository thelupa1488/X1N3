#include "Tables.h"

#ifdef ENABLE_INVENTORY
EGCResults __fastcall hkRetrieveMessage(void* ecx, void* edx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	EGCResults status = HookTables::pRetrieveMessage->GetTrampoline()(ecx, punMsgType, pubDest, cubDest, pcubMsgSize);

	if (status != k_EGCResultOK)
		return status;

	uint32_t messageType = *punMsgType & 0x7FFFFFFF;

	GP_Inventory->RetrieveMessage(ecx, edx, punMsgType, pubDest, cubDest, pcubMsgSize);

	return status;
}
EGCResults __fastcall hkSendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData)
{
	uint32_t messageType = unMsgType & 0x7FFFFFFF;
	void* pubDataMutable = const_cast<void*>(pubData);

	GP_Inventory->SSendMessage(ecx, edx, unMsgType, pubDataMutable, cubData);

	EGCResults status = HookTables::pSendMessage->GetTrampoline()(ecx, unMsgType, pubDataMutable, cubData);

	if (status != k_EGCResultOK)
		return status;

	return status;
}
#endif