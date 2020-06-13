#pragma once
//#include "../Engine/CSX/CSX_Hook.h"
#include "../Hacks/Setup.h"
#include "../Engine/SDK/SDK.h"
#include "../X1API/MinHook/hook.h"
#include "../Engine/SDK/StartSoundParams.h"
using namespace SDK;

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
	using PlaySoundFn = bool(__thiscall*)(void*, const char*);
	using LockCursorFn = bool(__thiscall*)(void*);
	using RetrieveMessageFn = EGCResults(__thiscall*)(void*, uint32_t*, void*, uint32_t, uint32_t*);
	using SendMessageFn = EGCResults(__thiscall*)(void*, uint32_t, const void*, uint32_t);
	using PostDataUpdateFn = void(__stdcall*)(void*, int);
	using EmitSoundFn = void(__fastcall*)(void*, void*, void*, int, int, const char*, unsigned int, const char*, float,
		float, int, int, int, const Vector*, const Vector*, Vector*, bool, float,
		int, StartSoundParams_t&);

	cDetour<CreateMoveFn>* pCreateMove;
	cDetour<OverrideViewFn>* pOverrideView;
	cDetour<GetViewModelFOVFn>* pGetViewModelFOV;
	cDetour<DoPostScreenEffectsFn>* pDoPostScreenEffects;
	cDetour<FrameStageNotifyFn>* pFrameStageNotify;
	cDetour<FireEventClientSideThinkFn>* pFireEventClientSideThink;
	cDetour<DrawModelExecuteFn>* pDrawModelExecute;
	cDetour<PlaySoundFn>* pPlaySound;
	cDetour<LockCursorFn>* pLockCursor;
	cDetour<RetrieveMessageFn>* pRetrieveMessage;
	cDetour<SendMessageFn>* pSendMessage;
	cDetour<PostDataUpdateFn>* pPostDataUpdate;
	cDetour<EmitSoundFn>* pEmitSound;
}