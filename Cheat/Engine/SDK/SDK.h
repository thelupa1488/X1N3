#pragma once

#include "BaseTypes.h"
#include "Const.h"
#include "Definitions.hpp"
#include "CRC.hpp"
#include "IAppSystem.hpp"
#include "Vector.hpp"
#include "Vplane.h"
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include "QAngle.hpp"
#include "VMatrix.hpp"
#include "CHandle.hpp"
#include "CGlobalVarsBase.hpp"
#include "ClientClass.hpp"
#include "ClientState.hpp"
#include "Color.hpp"
#include "IBaseClientDll.hpp"
#include "IClientEntity.hpp"
#include "IClientEntityList.hpp"
#include "IClientNetworkable.hpp"
#include "IClientRenderable.hpp"
#include "IClientThinkable.hpp"
#include "IClientUnknown.hpp"
#include "IVEngineClient.hpp"
#include "IEngineTrace.hpp"
#include "ILocalize.hpp"
#include "Recv.hpp"
#include "IClientMode.hpp"
#include "IVModelInfoClient.hpp"
#include "CInput.hpp"
#include "ICollideable.h"
#include "IEngineSound.h"
#include "IVModelRender.h"
#include "IVRenderView.h"
#include "IMaterialSystem.h"
#include "ISurface.h"
#include "IGameEvent.h"
#include "TextureGroupNames.h"
#include "ICVar.h"
#include "CGlowObjManager.h"
#include "IPhysics.hpp"
#include "Math.hpp"
#include "Match.h"
#include "IPredition.hpp"
#include "checksum_md5.hpp"
#include "IGameRules.h"
#include "CUserCmd.hpp"
#include "IInputSystem.hpp"
#include "KeyValues.h"
//#include "memalloc.h"

#include <Windows.h>
#include <WinInet.h>

#include "../CSX/CSX.h"
#include "../../steam_sdk/steam_api.h"

#pragma comment(lib, "Wininet.lib")

#define engineFactory XorStr("engine.dll")
#define clientFactory XorStr("client.dll")
#define valveStdFactory XorStr("vstdlib.dll")
#define matSysFactory XorStr("materialsystem.dll")
#define vphysicsFactory XorStr("vphysics.dll")
#define inputSysFactory XorStr("inputsystem.dll")
#define localizeFactory XorStr("localize.dll")
#define steamApiFactory XorStr("steam_api.dll")
#define serverBrowserFactory XorStr("serverbrowser.dll")
#define vguiFactory XorStr("vgui2.dll")
#define vguimatFactory	XorStr("vguimatsurface.dll")
#define d3d9Factory XorStr("d3d9.dll")
#define shaderapidx9Factory XorStr("shaderapidx9.dll")
#define gameoverlayrenderFactory XorStr("GameOverlayRenderer.dll")

#define KEY_VALUES_MASK  XorStr("55 8B EC 51 33 C0 C7 45")
#define KEY_VALUES_LOAD_FROM_BUFFER_MASK  XorStr("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04")

#define d3d9_mask XorStr("x????xxxxxx")
#define gmor_mask XorStr("x????x????xxxx????xxxxxxx")

#define d3d9_pattern XorStr("\xA1\x00\x00\x00\x00\x50\x8B\x08\xFF\x51\x0C")
#define force_full_update_pattern XorStr("A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85")

#define gmor_pattern XorStr("\xA3\x00\x00\x00\x00\x68\x00\x00\x00\x00\xFF\x76\x54\xE8\x00\x00\x00\x00\x83\xC4\x08\x84\xC0\x75\x17")
#define smok_pattern XorStr("\x55\x8B\xEC\x83\xEC\x08\x8B\x15\x00\x00\x00\x00\x0F\x57\xC0")

#define CLIENT_MODE_PATTERN XorStr("\xB9\x00\x00\x00\x00\x83\x38\x02\x75\x0D\xFF\xB0\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x5D\xC3")
#define CLIENT_MODE_MASK XorStr("x????xxxxxxx????x????xx")

namespace SDK
{
	class I
	{
	public:
		static IVEngineClient*		Engine();
		static IBaseClientDLL*		Client();
		static IClientEntityList*	EntityList();
		static CGlobalVarsBase*		GlobalVars();
		static CInput*				Input();
		static CClientState*		ClientState();
		static IEngineTrace*		EngineTrace();
		static IPanel*              Panel();
		static IClientMode*			ClientMode();
		static IVModelInfo*	        ModelInfo();
		static IEngineSound*		Sound();
		static IVModelRender*		ModelRender();
		static CGlowObjectManager*  GlowObjManager();
		static IViewRender*		    RenderView();
		static IMaterialSystem*		MaterialSystem();
		static ISurface*			Surface();
		static IPhysicsSurfaceProps*PhysSurface();
		static IGameEventManager2*	GameEvent();
		static IInputSystem*		InputSystem();
		static ConVar*               GetConVar();
		static IClientEntityList*	g_pEntityList;
		static IGameEventManager2*  g_pGameEvents;
		static ILocalize*           Localize();
		static ISteamGameCoordinator* SteamGameCoordinator();
		static ISteamUser*          SteamUser();
		static IMatchFramework*     MatchFramework();
		static IPrediction*         Prediction();
		static IMoveHelper*         MoveHelper();
		static IGameMovement*       GameMovement();
		static IGameRules*          GameRules();
	private:
		static IVEngineClient*		g_pEngine;
		static IBaseClientDLL*		g_pClient;
		static CGlobalVarsBase*		g_pGlobals;
		static CInput*				g_pInput;
		static CClientState*		g_pClientState;
		static IEngineTrace*		g_pEngineTrace;
		static IClientMode*			g_pClientMode;
		static IPanel*              g_pPanel;
		static IVModelInfo*	        g_pModelInfo;
		static IEngineSound*		g_pSound;
		static IVModelRender*		g_pModelRender;
		static CGlowObjectManager*  g_pGlowObjManager;
		static IViewRender*		    g_pRenderView;
		static IMaterialSystem*		g_pMaterialSystem;
		static ISurface*			g_pSurface;
		static IPhysicsSurfaceProps* g_PhysSurface;
		static IGameEventManager2*	g_pGameEventMgr;
		static IInputSystem*		g_pInputSystem;
		static ConVar*               g_pConVar;
		static ILocalize*           g_pLocalize;
		static ISteamGameCoordinator* g_pSteamGameCoordinator;
		static ISteamUser*          g_pSteamUser;
		static IMatchFramework*     g_pMatchFramework;
		static IPrediction*         g_pPrediction;
		static IMoveHelper*         g_pMoveHelper;
		static IGameMovement*       g_pGameMovement;
		static IGameRules*          g_pGameRules;
	};

	template <typename T>
	T CallVFunc(void *vTable, int iIndex) 
	{
		return (*(T**)vTable)[iIndex];
	}
}


inline void**& GetVTable( void* instance )
{
	return *reinterpret_cast<void***>( (size_t)instance );
}

inline const void** GetVTable( const void* instance )
{
	return *reinterpret_cast<const void***>( (size_t)instance );
}

template<typename T>
inline T GetMethod( const void* instance , size_t index )
{
	return reinterpret_cast<T> ( GetVTable( instance )[index] );
}        