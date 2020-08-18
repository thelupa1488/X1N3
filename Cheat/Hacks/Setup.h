#pragma once
#include "../Engine/EntityMem.h"
#include "Esp/Esp.h"
#include "LegitAim/LegitAim.h"
#include "Misc/Misc.h"
#include "Radar/Radar.h"
#include "Skins/Skins.h"
#include "Inventory/Inventory.h"
#include "GrenadeHelper/GreandeHelper.h"
#include "../Render/DXRender.h"
#include "../Engine/GrenadePrediction.h"
#include "../Engine/SDK/SDK.h"
#include "../Main.h"
#include "../Include/Def.h"
#include "../X1API/MinHook/hook.h"

#define DELETE_PTR(name) delete name; name = nullptr
namespace HookTables
{
	using CreateMoveFn = bool(__stdcall*)(float, CUserCmd*);
	using OverrideViewFn = bool(__stdcall*)(CViewSetup*);
	using GetViewModelFOVFn = float(__stdcall*)();
	using DoPostScreenEffectsFn = int(__thiscall*)(void*, int);
	using FrameStageNotifyFn = void(__thiscall*)(void*, int);
	using FireEventClientSideThinkFn = bool(__thiscall*)(void*, IGameEvent*);
	using DrawModelExecuteFn = void(__thiscall*)(void*, IMatRenderContext*, const DrawModelState_t&,
		const ModelRenderInfo_t&, matrix3x4_t*);
	using LockCursorFn = bool(__thiscall*)(void*);
	using PostDataUpdateFn = void(__stdcall*)(void*, int);
	using EmitSoundFn = void(__fastcall*)(IEngineSound*, int, IRecipientFilter&, int, int, const char*,
		unsigned int, const char*, float, float, int, int, int, const Vector*,
		const Vector*, CUtlVector<Vector>*, bool, int, int, SndInfo_t&);
#ifdef ENABLE_INVENTORY
	using RetrieveMessageFn = EGCResults(__thiscall*)(void*, uint32_t*, void*, uint32_t, uint32_t*);
	using SendMessageFn = EGCResults(__thiscall*)(void*, uint32_t, const void*, uint32_t);
#endif

	extern cDetour<CreateMoveFn>* pCreateMove;
	extern cDetour<OverrideViewFn>* pOverrideView;
	extern cDetour<GetViewModelFOVFn>* pGetViewModelFOV;
	extern cDetour<DoPostScreenEffectsFn>* pDoPostScreenEffects;
	extern cDetour<FrameStageNotifyFn>* pFrameStageNotify;
	extern cDetour<FireEventClientSideThinkFn>* pFireEventClientSideThink;
	extern cDetour<DrawModelExecuteFn>* pDrawModelExecute;
	extern cDetour<LockCursorFn>* pLockCursor;
	extern cDetour<PostDataUpdateFn>* pPostDataUpdate;
	extern cDetour<EmitSoundFn>* pEmitSound;
#ifdef ENABLE_INVENTORY
	extern cDetour<RetrieveMessageFn>* pRetrieveMessage;
	extern cDetour<SendMessageFn>* pSendMessage;
#endif
}
using namespace HookTables;

class IISetup
{
public:
	virtual class ISetup
	{
	public:
		virtual void Setup() = 0;
		virtual void Shutdown() = 0;
	};
};

extern CRender::IRender*	GP_Render;
extern CEntityPlayers*		GP_EntPlayers;
extern CEsp*				GP_Esp;
extern CMisc*				GP_Misc;
extern CLegitAim*			GP_LegitAim;
extern CRadar*				GP_Radar;
extern CSkins*				GP_Skins;
#ifdef ENABLE_INVENTORY
extern CInventory*          GP_Inventory;
#endif
extern CGHelper*			GP_GHelper;


class CSetup : public IISetup
{
public:
	virtual class ISetup
	{
	public:
		virtual void Setup()
		{
			VMP_ULTRA("SetupThread_Init_Setup")
			ADD_LOG("2-1-11-7-0\n");
			GP_Render =		new CRender::IRender();
			GP_EntPlayers = new CEntityPlayers();
			GP_Esp =		new CEsp();
			GP_Misc =		new CMisc();
			GP_LegitAim =	new CLegitAim();
			GP_Radar =		new CRadar();
			GP_Skins =		new CSkins();
#ifdef ENABLE_INVENTORY
			GP_Inventory =  new CInventory();
#endif
			GP_GHelper =	new CGHelper();
			ADD_LOG("2-1-11-7-1\n");
			CGSettings::G().UpdateList();
			GP_Misc->UpdateSoundList();
			ADD_LOG("2-1-11-7-2\n");
			GP_Esp->InitVisuals();
			GP_Esp->InitializeMaterials();
			GP_LegitAim->InitializeBacktrack();
			GP_Render->Initialize();
			GP_GHelper->Initialize();
			ADD_LOG("2-1-11-7-3\n");
#ifndef ONLY_DRAW_HOOK
			GP_Misc->HitWorker.RegListener();
			GP_Skins->FireEvent.RegListener();
			GP_Skins->initialize_kits();
			GP_Skins->ParseSortedKits();
			GP_Skins->PrepareSortedSkins();
#ifdef ENABLE_INVENTORY
			GP_Inventory->InitalizeMedals();
#endif
#endif
			ADD_LOG("2-1-11-7-4\n");
			GP_Skins->AllSkinsLoaded = true;
			ADD_LOG("2-1-11-7-5\n");
			VMP_END
		}
		virtual void Shutdown()
		{
			GP_Misc->HitWorker.UnRegListener();
			GP_Skins->FireEvent.UnRegListener();

			pCreateMove->Remove();
			pOverrideView->Remove();
			pGetViewModelFOV->Remove();
			pDoPostScreenEffects->Remove();
			pFrameStageNotify->Remove();
			pFireEventClientSideThink->Remove();
			pDrawModelExecute->Remove();
			pLockCursor->Remove();
			pPostDataUpdate->Remove();
			pEmitSound->Remove();
#ifdef ENABLE_INVENTORY
			pRetrieveMessage->Remove();
			pSendMessage->Remove();
#endif

			DELETE_PTR(GP_Render);
			DELETE_PTR(GP_EntPlayers);
			DELETE_PTR(GP_Esp);
			DELETE_PTR(GP_Misc);
			DELETE_PTR(GP_LegitAim);
			DELETE_PTR(GP_Radar);
			DELETE_PTR(GP_Skins);
#ifdef ENABLE_INVENTORY
			DELETE_PTR(GP_Inventory);
#endif
			DELETE_PTR(GP_GHelper);
		}
	};
};

extern CSetup::ISetup *GP_Setup;