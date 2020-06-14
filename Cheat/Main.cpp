#include "Main.h"
#include "Initialize/Initialize.h"
#include "GUI/Gui.h"
#include "X1API/ThreadInMemory.h"

DWORD WINAPI SetupThread(_In_ LPVOID lpThreadParameter)
{
	VMP_MUTATION("SetupThread");
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
	VMP_END;
}

INT WINAPI DllMain(_In_ HINSTANCE hinstDll, _In_ DWORD fdwReason, _In_opt_ LPVOID lpvReserved)
{
	VMP_MUTATION("SetupThread");
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
		FastCall::G().t_DisableThreadLibraryCalls(hinstDll);
		std::make_unique<CreateThread_>((LPTHREAD_START_ROUTINE)SetupThread, hinstDll);
		ADD_LOG("2\n");
		return TRUE;
	case DLL_PROCESS_DETACH:
		GP_Setup->Shutdown();
		DELETE_PTR(GP_Setup);
		ADD_LOG("DLL DETACH\n");
	default:
		return TRUE;
	}
	VMP_END;
}

CMain& MainSettings()
{
	return CMain::Singleton();
}

void CMain::SetMenuColors()
{
	GuiStyle& style = X1Gui().GetStyle();

	auto AutoChangeColor = [&](Color col, float ch) -> Color
	{
		Color entry;

		entry.SetR(((col.r() + ch < 0) ? 0 : ((col.r() + ch > 255) ? 255 : (col.r() + ch))));
		entry.SetG(((col.g() + ch < 0) ? 0 : ((col.g() + ch > 255) ? 255 : (col.g() + ch))));
		entry.SetB(((col.b() + ch < 0) ? 0 : ((col.b() + ch > 255) ? 255 : (col.b() + ch))));
		entry.SetA(col.a());

		return entry;
	};

	style.clrLine = LineColor;
	style.clrBackground = BackgroundColor;
	style.clrText = TextColor;

	style.clrFrame = FrameColor;
	style.clrFrameHover = AutoChangeColor(FrameColor, -5);
	style.clrFrameHold = AutoChangeColor(FrameColor, -9);

	style.clrTabLabel = color_t(ButtonColor.r(), ButtonColor.g(), ButtonColor.b(), 120);
	style.clrTabLabelText = color_t(TextColor.r(), TextColor.g(), TextColor.b(), 160);

	style.clrButton = ButtonColor;
	style.clrButtonHover = AutoChangeColor(ButtonColor, -10);
	style.clrButtonHold = AutoChangeColor(ButtonColor, -20);

	style.clrDisButton = DisableButtonColor;
	style.clrDisButtonHover = AutoChangeColor(DisableButtonColor, -10);
	style.clrDisButtonHold = AutoChangeColor(DisableButtonColor, -20);

	style.clrScroll = AutoChangeColor(ButtonColor, -20);
	style.clrScrollHover = AutoChangeColor(ButtonColor, -20);
	style.clrScrollHold = AutoChangeColor(ButtonColor, -20);
	style.clrTitle = TitleColor;
}