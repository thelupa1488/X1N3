#pragma once
#include "../DXRender.h"
#include "../../Hacks/Setup.h"

HRESULT WINAPI MyReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* param)
{
	if (GP_Render)
		GP_Render->InvalidateDeviceObjects();

	if (GP_Render)
		GP_Render->CreateDeviceObjects();

	return HookTables::pReset->GetTrampoline()(pDevice, param);
}