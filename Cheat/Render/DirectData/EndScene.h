#pragma once
#include "../DXRender.h"

HRESULT WINAPI MyEndScene(IDirect3DDevice9* pDevice)
{
	if (pDevice)
	{

	}
	return pEndScene->GetTrampoline()(pDevice);
}