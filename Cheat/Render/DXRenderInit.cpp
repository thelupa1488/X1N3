#pragma comment(lib, "detours.lib")
#include "../X1API/detours.h"

#include "DXRender.h"
#include "DirectData/Reset.h"
#include "DirectData/Present.h"
#include "DirectData/EndScene.h"

cDetour<oEndScene>* pEndScene;
cDetour<oPresent>* pPresent;
cDetour<oReset>* pReset;

#define ResetIndex 16
#define PresentIndex 17
#define EndSceneIndex 42

LPDIRECT3DDEVICE9 nm_pD3Ddev = nullptr;

LRESULT CALLBACK MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CRender::IRender::DX_Init(DWORD* table)
{
	LPDIRECT3DDEVICE9 pd3dDevice = NULL;
	do
	{
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, FastCall::G().t_GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, XorStr("SEGUARD_Window"), NULL };
		RegisterClassEx(&wc);
		HWND hWnd = CreateWindowA(XorStr("SEGUARD_Window"), NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, FastCall::G().t_GetDesktopWindow(), NULL, wc.hInstance, NULL);
		LPDIRECT3D9 pD3D = FastCall::G().t_Direct3DCreate9(D3D_SDK_VERSION);
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		d3dpp.BackBufferCount = 3;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		HRESULT res = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);

		if (res == D3D_OK)
			int tt = FastCall::G().t_GetLastError();
		else if (res == D3DERR_DEVICELOST)
			int tt = FastCall::G().t_GetLastError();
		else if (res == D3DERR_INVALIDCALL)
			int tt = FastCall::G().t_GetLastError();
		else if (res == D3DERR_NOTAVAILABLE)
			int tt = FastCall::G().t_GetLastError();
		else if (res == D3DERR_OUTOFVIDEOMEMORY)
			int tt = FastCall::G().t_GetLastError();

		FastCall::G().t_DestroyWindow(hWnd);

		FastCall::G().t_Sleep(1000);
		ADD_LOG("device!!!\n");
	} while (!pd3dDevice);

	DWORD* pVTable = (DWORD*)pd3dDevice;
	pVTable = (DWORD*)pVTable[0];
	table[0] = pVTable[ResetIndex];
#ifdef PRESENT_ENABLE
	table[1] = pVTable[PresentIndex];
#else
	table[2] = pVTable[EndSceneIndex];
#endif
}

void CRender::IRender::Initialize()
{
	VMP_ULTRA("RenderInitialize")
	ADD_LOG("2-1-11-7-3-0\n");
	m_pDevice = nullptr;
	m_pDrawMngr = nullptr;
	m_pFont = nullptr;
	m_pStateBlockDraw = nullptr;
	ADD_LOG("2-1-11-7-3-1\n");
	Fonts.clear();
	Fonts.resize(0);
	ADD_LOG("2-1-11-7-3-2\n");
	ScreenWidth = 1920;
	ScreenHeight = 1080;
	ADD_LOG("2-1-11-7-3-3\n");

	auto& pContext = cContext::GetInstance();

	DWORD d3d9TablePtrPtr = offsets["d3d9TablePtrPtr"];
	if (d3d9TablePtrPtr)
	{
		g_pDevice = (IDirect3DDevice9*)(**(PDWORD*)d3d9TablePtrPtr);
		PVOID* IDirect3DDevice9Table = *reinterpret_cast<PVOID**>(g_pDevice);

		if (IDirect3DDevice9Table)
		{
			pContext.ApplyDetour<oReset>(static_cast<oReset>(IDirect3DDevice9Table[ResetIndex]),
				reinterpret_cast<oReset>
				(MyReset),
				&pReset);
			ADD_LOG("Hook: Reset\n");
#ifdef PRESENT_ENABLE
			pContext.ApplyDetour<oPresent>(static_cast<oPresent>(IDirect3DDevice9Table[PresentIndex]),
				reinterpret_cast<oPresent>
				(MyPresent),
				&pPresent);
			ADD_LOG("Hook: Present\n");
#else
			pContext.ApplyDetour<oEndScene>(static_cast<oEndScene>(IDirect3DDevice9Table[EndSceneIndex]),
				reinterpret_cast<oEndScene>
				(MyEndScene),
				&pEndScene);
			ADD_LOG("Hook: EndScene\n");
#endif
			ADD_LOG("2-1-11-7-3-9\n");
		}
		else
		{
			ADD_LOG("2-1-11-7-3-10\n");
			ADD_LOG("Setup: InitTable Device Error\n");
			FastCall::G().t_MessageBoxA(0, XorStr("InitTable error"), XorStr("Error!"), 0);
		}
		ADD_LOG("2-1-11-7-3-11\n");
	}
	else
	{
		ADD_LOG("Setup: Hook Present Error\n");
		FastCall::G().t_MessageBoxA(0, XorStr("Present error"), XorStr("Error!"), 0);
	}
	ADD_LOG("2-1-11-7-3-12\n");

	ADD_LOG("Waith device...\n");
	while (!nm_pD3Ddev) { nm_pD3Ddev = m_pDevice; FastCall::G().t_Sleep(50); }
	ADD_LOG("2-1-11-7-3-13\n");
	g_pDevice = m_pDevice;

	ADD_LOG("2-1-11-7-3-14\n");
#ifdef ENABLE_HOOK_CS_WND_PROC
	HWND hWindow = FastCall::G().t_FindWindowA(XorStr("Valve001"), 0);
#else
	HWND hWindow = FastCall::G().t_FindWindowA(XorStr("winA"), 0);
#endif 
	ADD_LOG("->Window -> %X\n", (DWORD)hWindow);
	ADD_LOG("2-1-11-7-3-15\n");
	WndProc_o = (WNDPROC)FastCall::G().t_SetWindowLongA(hWindow, GWL_WNDPROC, (LONG)(LONG_PTR)WndProcHandler);
	VMP_END
}
