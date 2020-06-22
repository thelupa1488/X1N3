#include "SDK.h"
#include <time.h>
#include  "../../Main.h"
//#include "../Settings/Settings.h"


namespace SDK
{
	IVEngineClient*     I::g_pEngine = nullptr;
	IBaseClientDLL*     I::g_pClient = nullptr;
	IClientEntityList*  I::g_pEntityList = nullptr;
	CGlobalVarsBase*    I::g_pGlobals = nullptr;
	CInput*             I::g_pInput = nullptr;
	CClientState*       I::g_pClientState = nullptr;
	IEngineTrace*       I::g_pEngineTrace = nullptr;
	IClientMode*        I::g_pClientMode = nullptr;
	IPanel*             I::g_pPanel = nullptr;
	IVModelInfo*	    I::g_pModelInfo = nullptr;
	IEngineSound*		I::g_pSound = nullptr;
	IVModelRender*		I::g_pModelRender = nullptr;
	CGlowObjectManager* I::g_pGlowObjManager = nullptr;
	IViewRender*		I::g_pRenderView = nullptr;
	IMaterialSystem*	I::g_pMaterialSystem = nullptr;
	ISurface*			I::g_pSurface = nullptr;
	IPhysicsSurfaceProps*I::g_PhysSurface = nullptr;
	IGameEventManager2*	I::g_pGameEvent = nullptr;
	IInputSystem*		I::g_pInputSystem = nullptr;
	ConVar*             I::g_pConVar = nullptr;
	ILocalize*          I::g_pLocalize = nullptr;
	ISteamGameCoordinator* I::g_pSteamGameCoordinator = nullptr;
	ISteamUser*         I::g_pSteamUser = nullptr;
	IMatchFramework*    I::g_pMatchFramework = nullptr;
	IPrediction*        I::g_pPrediction = nullptr;
	IMoveHelper*        I::g_pMoveHelper = nullptr;
	IGameMovement*      I::g_pGameMovement = nullptr;
	IGameRules*         I::g_pGameRules = nullptr;

	class InterfaceReg
	{
	private:
		using InstantiateInterfaceFn = void* (*)();

	public:

		InstantiateInterfaceFn m_CreateFn;
		const char* m_pName;

		InterfaceReg* m_pNext;
	};

	template<typename T>
	T* GetInterface(const char* modName, const char* ifaceName, bool exact = false)
	{
		T* iface = nullptr;
		InterfaceReg* ifaceRegList;
		int partMatchLen = strlen(ifaceName);

		DWORD ifaceFn = reinterpret_cast<DWORD>(FastCall::G().t_GetProcAddress(FastCall::G().t_GetModuleHandleA(modName), XorStr("CreateInterface")));

		if (!ifaceFn)
			return nullptr;

		unsigned int jmpStart = (unsigned int)(ifaceFn)+4;
		unsigned int jmpTarget = jmpStart + *(unsigned int*)(jmpStart + 1) + 5;

		ifaceRegList = **reinterpret_cast<InterfaceReg***>(jmpTarget + 6);

		for (InterfaceReg* cur = ifaceRegList; cur; cur = cur->m_pNext)
		{
			if (exact == true)
			{
				if (strcmp(cur->m_pName, ifaceName) == 0)
					iface = reinterpret_cast<T*>(cur->m_CreateFn());
			}
			else
			{
				if (!strncmp(cur->m_pName, ifaceName, partMatchLen) && std::atoi(cur->m_pName + partMatchLen) > 0)
					iface = reinterpret_cast<T*>(cur->m_CreateFn());
			}
		}
		return iface;
	}

	IBaseClientDLL* I::Client()
	{
		if (!g_pClient)
		{
			g_pClient = GetInterface<IBaseClientDLL>(clientFactory, XorStr("VClient0"));
			while (!((DWORD) * *(IClientMode***)((*(uint32_t**)Client())[10] + 0x5)) || !((DWORD) * *(CGlobalVarsBase***)((*(uint32_t**)Client())[0] + 0x1B)))
			{
				FastCall::G().t_Sleep(1000);
			}
			ADD_LOG("->Client -> %X\n", (DWORD)g_pClient);
		}
		return g_pClient;
	}

	IClientEntityList* I::EntityList()
	{
		if (!g_pEntityList)
		{
			g_pEntityList = GetInterface<IClientEntityList>(clientFactory, XorStr("VClientEntityList"));
			ADD_LOG("->EntityList -> %X\n", (DWORD)g_pEntityList);
		}
		return g_pEntityList;
	}

	IPrediction* I::Prediction()
	{
		if (!g_pPrediction)
		{
			g_pPrediction = GetInterface<IPrediction>(clientFactory, XorStr("VClientPrediction"));
			ADD_LOG("->Prediction -> %X\n", (DWORD)g_pPrediction);
		}
		return g_pPrediction;
	}

	IGameMovement* I::GameMovement()
	{
		if (!g_pGameMovement)
		{
			g_pGameMovement = GetInterface<CGameMovement>(clientFactory, XorStr("GameMovement"));
			ADD_LOG("->GameMovement -> %X\n", (DWORD)g_pGameMovement);
		}
		return g_pGameMovement;
	}

	IVEngineClient* I::Engine()
	{
		if ( !g_pEngine )
		{
			g_pEngine = GetInterface<IVEngineClient>(engineFactory, XorStr("VEngineClient"));
			ADD_LOG("->Engine -> %X\n", (DWORD)g_pEngine);
		}	
		return g_pEngine;
	}

	IVModelInfo* I::ModelInfo()
	{
		if (!g_pModelInfo)
		{
			g_pModelInfo = GetInterface<IVModelInfo>(engineFactory, XorStr("VModelInfoClient"));
			ADD_LOG("->ModelInfo -> %X\n", (DWORD)g_pModelInfo);
		}
		return g_pModelInfo;
	}

	IVModelRender* I::ModelRender()
	{
		if (!g_pModelRender)
		{
			g_pModelRender = GetInterface<IVModelRender>(engineFactory, XorStr("VEngineModel"));
			ADD_LOG("->ModelRender -> %X\n", (DWORD)g_pModelRender);
		}
		return g_pModelRender;
	}

	IViewRender* I::RenderView()
	{
		if (!g_pRenderView)
		{
			g_pRenderView = GetInterface<IViewRender>(engineFactory, XorStr("VEngineRenderView"));
			ADD_LOG("->RenderView -> %X\n", (DWORD)g_pRenderView);
		}
		return g_pRenderView;
	}

	IEngineTrace* I::EngineTrace()
	{
		if (!g_pEngineTrace)
		{
			g_pEngineTrace = GetInterface<IEngineTrace>(engineFactory, XorStr("EngineTraceClient"));
			ADD_LOG("->EngineTrace -> %X\n", (DWORD)g_pEngineTrace);
		}
		return g_pEngineTrace;
	}

	IGameEventManager2* I::GameEvent()
	{
		if (!g_pGameEvent)
		{
			g_pGameEvent = GetInterface<IGameEventManager2>(engineFactory, XorStr("GAMEEVENTSMANAGER002"), true);
			ADD_LOG("->GameEvent -> %X\n", (DWORD)g_pGameEvent);
		}
		return g_pGameEvent;
	}

	IEngineSound* I::Sound()
	{
		if (!g_pSound)
		{
			g_pSound = GetInterface<IEngineSound>(engineFactory, XorStr("IEngineSoundClient"));
			ADD_LOG("->Sound -> %X\n", (DWORD)g_pSound);
		}
		return g_pSound;
	}

	IMaterialSystem* I::MaterialSystem()
	{
		if (!g_pMaterialSystem)
		{
			g_pMaterialSystem = GetInterface<IMaterialSystem>(matSysFactory, XorStr("VMaterialSystem"));
			ADD_LOG("->MaterialSystem -> %X\n", (DWORD)g_pMaterialSystem);
		}
		return g_pMaterialSystem;
	}

	ConVar* I::GetConVar()
	{
		if (!g_pConVar)
		{
			g_pConVar = GetInterface<ConVar>(valveStdFactory, XorStr("VEngineCvar"));
			ADD_LOG("->ConVar -> %X\n", (DWORD)g_pConVar);
		}
		return g_pConVar;
	}

	IPanel* I::Panel()
	{
		if (!g_pPanel)
		{
			g_pPanel = GetInterface<IPanel>(vguiFactory, XorStr("VGUI_Panel"));
			ADD_LOG("->Panel -> %X\n", (DWORD)g_pPanel);
		}
		return g_pPanel;
	}

	ISurface* I::Surface()
	{
		if (!g_pSurface)
		{
			g_pSurface = GetInterface<ISurface>(vguimatFactory, XorStr("VGUI_Surface"));
			ADD_LOG("->Surface -> %X\n", (DWORD)g_pSurface);
		}
		return g_pSurface;
	}

	IPhysicsSurfaceProps* I::PhysSurface()
	{
		if (!g_PhysSurface)
		{
			g_PhysSurface = GetInterface<IPhysicsSurfaceProps>(vphysicsFactory, XorStr("VPhysicsSurfaceProps"));
			ADD_LOG("->PhysSurface -> %X\n", (DWORD)g_PhysSurface);
		}
		return g_PhysSurface;
	}

	IInputSystem* I::InputSystem()
	{
		if (!g_pInputSystem)
		{
			g_pInputSystem = GetInterface<IInputSystem>(inputSysFactory, XorStr("InputSystemVersion"));
			ADD_LOG("->InputSystem -> %X\n", (DWORD)g_pInputSystem);
		}
		return g_pInputSystem;
	}

	ILocalize* I::Localize()
	{
		if (!g_pLocalize)
		{
			g_pLocalize = GetInterface<ILocalize>(localizeFactory, XorStr("Localize_"));
			ADD_LOG("->Localize -> %X\n", (DWORD)g_pLocalize);
		}

		return g_pLocalize;
	}

	CGlobalVarsBase* I::GlobalVars()
	{
		if (!g_pGlobals)
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pGlobals = **(CGlobalVarsBase***)(pClientVFTable[0] + 0x1B);
			ADD_LOG("->Globals -> %X\n", (DWORD)g_pGlobals);
		}

		return g_pGlobals;
	}

	IClientMode* I::ClientMode()
	{
		if (!g_pClientMode)
		{
			auto pClientVFTable = *(uint32_t**)Client();
			g_pClientMode = **(IClientMode***)(pClientVFTable[10] + 0x5);
			ADD_LOG("->ClientMode -> %X\n", (DWORD)g_pClientMode);
		}
		return g_pClientMode;
	}

	CInput* I::Input()
	{
		if (!g_pInput)
		{
			g_pInput = *(CInput**)(Utils::PatternScan(clientFactory, XorStr("B9 ? ? ? ? F3 0F 11 04 24 FF 50 10")) + 1);
			ADD_LOG("->Input -> %X\n", (DWORD)g_pInput);
		}
		return g_pInput;
	}

	IMoveHelper* I::MoveHelper()
	{
		if (!g_pMoveHelper)
		{
			g_pMoveHelper = **(IMoveHelper***)(Utils::PatternScan(clientFactory, XorStr("8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01")) + 2);
			ADD_LOG("->MoveHelper -> %X\n", (DWORD)g_pMoveHelper);
		}

		return g_pMoveHelper;
	}

	CGlowObjectManager* I::GlowObjManager()
	{
		if (!g_pGlowObjManager)
		{
			g_pGlowObjManager = *(CGlowObjectManager**)(Utils::PatternScan(clientFactory, XorStr("0F 11 05 ? ? ? ? 83 C8 01")) + 3);
			ADD_LOG("->GlowObjectManager -> %X\n", (DWORD)g_pGlowObjManager);
		}
		return g_pGlowObjManager;
	}

	IMatchFramework* I::MatchFramework()
	{
		if (!g_pMatchFramework)
		{
			g_pMatchFramework = **(IMatchFramework***)(Utils::PatternScan(clientFactory, XorStr("8B 0D ? ? ? ? 8B 01 FF 50 2C 8D 4B 18")) + 2);
			ADD_LOG("->MatchFramework -> %X\n", (DWORD)g_pMatchFramework);
		}

		return g_pMatchFramework;
	}

	CClientState* I::ClientState()
	{
		if (!g_pClientState)
		{
			g_pClientState = **(CClientState***)(Utils::PatternScan(engineFactory, XorStr("A1 ? ? ? ? 8B 80 ? ? ? ? C3")) + 1);
			ADD_LOG("->ClientState -> %X\n", (DWORD)g_pClientState);
		}

		return g_pClientState;
	}

	IGameRules* I::GameRules()
	{
		if (!g_pGameRules)
		{
			g_pGameRules = *(IGameRules**)(Utils::PatternScan(clientFactory, XorStr("8B 0D ?? ?? ?? ?? 85 C0 74 0A 8B 01 FF 50 78 83 C0 54")) + 2);
			ADD_LOG("->GameRules -> %X\n", (DWORD)g_pGameRules);
		}
		return g_pGameRules;
	}

	ISteamUser* I::SteamUser()
	{
		if (!g_pSteamUser) {
			SteamGameCoordinator();
		}

		return g_pSteamUser;
	}

	ISteamGameCoordinator* I::SteamGameCoordinator()
	{
		if (!g_pSteamGameCoordinator) {
			typedef uint32_t SteamPipeHandle;
			typedef uint32_t SteamUserHandle;

			SteamUserHandle hSteamUser = ((SteamUserHandle(__cdecl*)(void))FastCall::G().t_GetProcAddress(FastCall::G().t_GetModuleHandleA(XorStr("steam_api.dll")), XorStr("SteamAPI_GetHSteamUser")))();
			SteamPipeHandle hSteamPipe = ((SteamPipeHandle(__cdecl*)(void))FastCall::G().t_GetProcAddress(FastCall::G().t_GetModuleHandleA(XorStr("steam_api.dll")), XorStr("SteamAPI_GetHSteamPipe")))();

			auto SteamClient = ((ISteamClient*(__cdecl*)(void))FastCall::G().t_GetProcAddress(FastCall::G().t_GetModuleHandleA(XorStr("steam_api.dll")), XorStr("SteamClient")))();

			auto SteamHTTP = SteamClient->GetISteamHTTP(hSteamUser, hSteamPipe, XorStr("STEAMHTTP_INTERFACE_VERSION002"));
			g_pSteamUser = SteamClient->GetISteamUser(hSteamUser, hSteamPipe, XorStr("SteamUser019"));
			auto SteamFriends = SteamClient->GetISteamFriends(hSteamUser, hSteamPipe, XorStr("SteamFriends015"));
			auto SteamInventory = SteamClient->GetISteamInventory(hSteamUser, hSteamPipe, XorStr("STEAMINVENTORY_INTERFACE_V002"));
			g_pSteamGameCoordinator = (ISteamGameCoordinator*)SteamClient->GetISteamGenericInterface(hSteamUser, hSteamPipe, XorStr("SteamGameCoordinator001"));
			ADD_LOG("->SteamUser -> %X\n", (DWORD)g_pSteamUser);
			ADD_LOG("->SteamGameCoordinator -> %X\n", (DWORD)g_pSteamGameCoordinator);
		}

		return g_pSteamGameCoordinator;
	}
}  