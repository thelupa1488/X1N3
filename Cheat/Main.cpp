#include "Main.h"
#include "Initialize/Initialize.h"
#include "GUI/Gui.h"
#include "X1API/ThreadInMemory.h"

DWORD WINAPI SetupThread(_In_ LPVOID lpThreadParameter)
{
	VMP_ULTRA("SetupThread")
	auto LSetupThread = [&]() -> DWORD
	{
		ADD_LOG("2-1-0\n");
		ADD_LOG("======================Setup: Started\n");
		ADD_LOG("2-1-1\n");
		CInit::IInit* pInit = new CInit::IInit();
		pInit->Init();
		DELETE_PTR(pInit);
		ADD_LOG("2-1-2\n");
		ADD_LOG("======================Setup: Sucessful\n");
		ADD_LOG("2-1-3\n");
		return FALSE;
	};
	return LSetupThread();
	VMP_END
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDll, _In_ DWORD fdwReason, _In_opt_ LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
#ifdef ENABLE_CONSOLE_LOG
		AllocConsole();
		AttachConsole(FastCall::G().t_GetCurrentProcessId());
		freopen("CONOUT$", "w", stdout);

		ADD_LOG("DLL ATTACH\n");
		ADD_LOG("DLL BUILD: %s | %s\n", __TIME__, __DATE__);
#endif
		ADD_LOG("1\n");
		make_unique<CreateThread_>(&SetupThread, hinstDll);
		ADD_LOG("2\n");
		return TRUE;
	case DLL_PROCESS_DETACH:
		GP_Setup->Shutdown();
		DELETE_PTR(GP_Setup);
		ADD_LOG("DLL DETACH\n");
	default:
		return TRUE;
	}
}