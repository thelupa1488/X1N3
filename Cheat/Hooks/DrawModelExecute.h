#pragma once
#include "Tables.h"

void __fastcall DrawModelExecute(void* thisptr, int edx, IMatRenderContext* ctx, const DrawModelState_t &state,
	const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	bool bShadowDepth = (pInfo.flags & STUDIO_SHADOWDEPTHTEXTURE) != 0;

	if (GP_Esp && CGlobal::IsGameReady && ctx && &state && &pInfo && pCustomBoneToWorld && !CGlobal::FullUpdateCheck)
		GP_Esp->DrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	if (GP_Misc && CGlobal::IsGameReady  && ctx && &state && &pInfo && pCustomBoneToWorld && !CGlobal::FullUpdateCheck)
		GP_Misc->DrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	HookTables::pDrawModelExecute->GetTrampoline()(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

	if (bShadowDepth)
		return;

	I::ModelRender()->ForcedMaterialOverride(0);
}

//int __fastcall DoPostScreenEffects(void* thisptr, int edx, int a1)
//{
//	static auto ofunc = HookTables::pDoPostScreenEffects->GetTrampoline();
//
//	if (GP_Esp)
//		GP_Esp->DrawGlow();
//
//	return ofunc(thisptr, edx, a1);
//}