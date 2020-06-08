#pragma once
#include "../Include/Def.h"
#include "../Hooks/Tables.h"
#include "../Engine/CSX/CSX_Memory.h"
#include "../Engine/CSX/CSX_Utils.h"
#include "../Engine/SDK/SDK.h"
#include "../Engine/NetVar.h"
#include "../Hooks/CreateMove.h"
#include "../Hooks/Views.h"
#include  "../Hooks/Sound.h"
#include "../Hooks/FrameStageNotify.h"
#include "../Hooks/DrawModelExecute.h"
#include "../Hacks/Setup.h"
#include "Offsets.h"

using namespace SDK;
using namespace Engine;

class IIInit
{
public:
	virtual class IInit
	{
	public:
		virtual void InitHooks() = 0;
		virtual void InitOffsets() = 0;
		virtual bool Init() = 0;
	};
};

inline int decod(const char *s)
{
	int z = 0, n = 0;
	while (isspace(*s)) s++;
	if (*s == '-') { z = 1; s++; }
	else if (*s == '+') s++;
	while (isdigit(*s)) n = 10 * n + *s++ - '0';
	return (z ? -n : n);
}

//#define RetrieveMessageIdx XorStr("2")
#define EmitSoundIdx XorStr("5")
//#define FireEventClientSideThinkIdx XorStr("9")
//#define ResetIdx XorStr("16")
#define OverrideViewIdx XorStr("18")
//#define RunCommandIdx XorStr("19")
#define DrawModelExecuteIdx XorStr("21")
#define CreateMoveIdx XorStr("24")
#define GetViewModelFOVIdx XorStr("35")
#define FrameStageNotifyIdx XorStr("37")
#define DoPostScreenEffectsIdx XorStr("44")
#define LockCursorIdx XorStr("67")
#define PlaySoundIdx XorStr("82")

using namespace HookTables;

class CInit : public IIInit
{
public:
	virtual class IInit
	{
	public:
		virtual void InitHooks()
		{
			VMP_MUTATION("InitHooks");
			auto LInitHooks = [&]() -> void
			{
				ADD_LOG("======================Init hooks:\n");
				ADD_LOG("2-1-11-0\n");
				auto& pContext = cContext::GetInstance();
				ADD_LOG("2-1-11-1\n");
				PVOID* SoundTable = *reinterpret_cast<PVOID * *>(I::Sound());
				PVOID* SurfaceTable = *reinterpret_cast<PVOID**>(I::Surface());
				PVOID* ClientModeTable = *reinterpret_cast<PVOID**>(I::ClientMode());
				PVOID* ClientTable = *reinterpret_cast<PVOID**>(I::Client());
				PVOID* ClientStateTable = *reinterpret_cast<PVOID**>(I::ClientState());
				PVOID* ModelRenderTable = *reinterpret_cast<PVOID**>(I::ModelRender());

				CGlobal::viewmodel_offset_convar_x = I::GetConVar()->FindVar(XorStr("viewmodel_offset_x"));
				CGlobal::viewmodel_offset_convar_y = I::GetConVar()->FindVar(XorStr("viewmodel_offset_y"));
				CGlobal::viewmodel_offset_convar_z = I::GetConVar()->FindVar(XorStr("viewmodel_offset_z"));
				*(int*)((DWORD)&CGlobal::viewmodel_offset_convar_x->fnChangeCallback + 0xC) = NULL;
				*(int*)((DWORD)&CGlobal::viewmodel_offset_convar_y->fnChangeCallback + 0xC) = NULL;
				*(int*)((DWORD)&CGlobal::viewmodel_offset_convar_z->fnChangeCallback + 0xC) = NULL;
				CGlobal::old_viewmodel_offset_x = -CGlobal::viewmodel_offset_convar_x->GetFloat();
				CGlobal::old_viewmodel_offset_y = -CGlobal::viewmodel_offset_convar_y->GetFloat();
				CGlobal::old_viewmodel_offset_z = -CGlobal::viewmodel_offset_convar_z->GetFloat();

				ADD_LOG("2-1-11-2\n");
#ifndef ONLY_DRAW_HOOK
				ADD_LOG("2-1-11-3\n");
				if (SoundTable)
				{
					pContext.ApplyDetour<EmitSoundFn>(static_cast<EmitSoundFn>(SoundTable[decod(EmitSoundIdx)]),
						reinterpret_cast<EmitSoundFn>
						(EmitSound),
						&pEmitSound);
					ADD_LOG("Hook: Emit Sound\n");
				}
				ADD_LOG("2-1-11-4\n");
				if (SurfaceTable)
				{
					pContext.ApplyDetour<PlaySoundFn>(static_cast<PlaySoundFn>(SurfaceTable[decod(PlaySoundIdx)]),
						reinterpret_cast<PlaySoundFn>
						(PlaySound),
						&pPlaySound);
					ADD_LOG("Hook: Sound\n");

					pContext.ApplyDetour<LockCursorFn>(static_cast<LockCursorFn>(SurfaceTable[decod(LockCursorIdx)]),
						reinterpret_cast<LockCursorFn>
						(LockCursor),
						&pLockCursor);
					ADD_LOG("Hook: Cursor\n");
				}
				ADD_LOG("2-1-11-5\n");
				if (ClientModeTable)
				{
					pContext.ApplyDetour<CreateMoveFn>(static_cast<CreateMoveFn>(ClientModeTable[decod(CreateMoveIdx)]),
						reinterpret_cast<CreateMoveFn>
						(CreateMove),
						&pCreateMove);
					ADD_LOG("Hook: CreateMove\n");

					pContext.ApplyDetour<OverrideViewFn>(static_cast<OverrideViewFn>(ClientModeTable[decod(OverrideViewIdx)]),
						reinterpret_cast<OverrideViewFn>
						(OverrideView),
						&pOverrideView);
					ADD_LOG("Hook: OverrideView\n");

					pContext.ApplyDetour<GetViewModelFOVFn>(static_cast<GetViewModelFOVFn>(ClientModeTable[decod(GetViewModelFOVIdx)]),
						reinterpret_cast<GetViewModelFOVFn>
						(GetViewModelFOV),
						&pGetViewModelFOV);
					ADD_LOG("Hook: GetViewModelFOV\n");
				}
				ADD_LOG("2-1-11-6\n");
				if (ClientTable)
				{
					pContext.ApplyDetour<FrameStageNotifyFn>(static_cast<FrameStageNotifyFn>(ClientTable[decod(FrameStageNotifyIdx)]),
						reinterpret_cast<FrameStageNotifyFn>
						(FrameStageNotify),
						&pFrameStageNotify);
					ADD_LOG("Hook: StageNotify\n");
				}
				ADD_LOG("2-1-11-7\n");
				if (ClientStateTable)
				{

				}
				ADD_LOG("2-1-11-8\n");
				if (ModelRenderTable)
				{
					pContext.ApplyDetour<DrawModelExecuteFn>(static_cast<DrawModelExecuteFn>(ModelRenderTable[decod(DrawModelExecuteIdx)]),
						reinterpret_cast<DrawModelExecuteFn>
						(DrawModelExecute),
						&pDrawModelExecute);
					ADD_LOG("Hook: DME\n");
				}
#endif
				ADD_LOG("2-1-11-9\n");
				GP_Setup = new CSetup::ISetup();
				GP_Setup->Setup();
				ADD_LOG("2-1-11-10\n");
				ADD_LOG("All Hooks sucessful\n");
			};
			LInitHooks();
			ADD_LOG("2-1-11-11\n");

			VMP_END;
		}
		virtual void InitOffsets()
		{
#define mGetOffset(table, prop) g_NetVar.GetOffset(XorStr(table), XorStr(prop))
			auto LInitOffsets = [&]() -> void
			{
				ADD_LOG("2-1-9-0\n");
				ADD_LOG("======================Init Offsets:\n");

				offsets[XorStr("m_hMyWeapons")] =  mGetOffset("DT_BasePlayer", "m_hActiveWeapon") / 2;
				offsets[XorStr("m_hMyWearables")] = mGetOffset("DT_BasePlayer", "m_hMyWearables");
				offsets[XorStr("m_vecOrigin")] = mGetOffset("DT_BasePlayer", "m_vecOrigin");
				offsets[XorStr("m_hViewModel")] = mGetOffset("DT_BasePlayer", "m_hViewModel[0]");
				offsets[XorStr("m_nTickBase")] = mGetOffset("DT_BasePlayer", "m_nTickBase");
				offsets[XorStr("m_iObserverMode")] = mGetOffset("DT_BasePlayer", "m_iObserverMode");
				offsets[XorStr("m_hObserverTarget")] = mGetOffset("DT_BasePlayer", "m_hObserverTarget");
				offsets[XorStr("deadflag")] = mGetOffset("DT_BasePlayer", "deadflag");
				offsets[XorStr("m_bIsDefusing")] = mGetOffset("DT_CSPlayer", "m_bIsDefusing");
				offsets[XorStr("m_iAccount")] = mGetOffset("DT_CSPlayer", "m_iAccount");
				offsets[XorStr("m_lifeState")] = mGetOffset("DT_CSPlayer", "m_lifeState");
				offsets[XorStr("m_flFlashDuration")] = mGetOffset("DT_CSPlayer", "m_flFlashDuration");
				offsets[XorStr("m_flSpawnTime")] = mGetOffset("DT_CSPlayer", "m_flSpawnTime");
				offsets[XorStr("m_flC4Blow")] = mGetOffset("DT_PlantedC4", "m_flC4Blow");
				offsets[XorStr("m_flDefuseCountDown")] = mGetOffset("DT_PlantedC4", "m_flDefuseCountDown");
				offsets[XorStr("m_hBombDefuser")] = mGetOffset("DT_PlantedC4", "m_hBombDefuser");
				offsets[XorStr("m_bBombDefused")] = mGetOffset("DT_PlantedC4", "m_bBombDefused");
				offsets[XorStr("m_nBombSite")] = mGetOffset("DT_PlantedC4", "m_nBombSite");
				offsets[XorStr("m_bFreezePeriod")] = mGetOffset("DT_CSGameRulesProxy", "m_bFreezePeriod");
				offsets[XorStr("m_bIsValveDS")] = mGetOffset("DT_CSGameRulesProxy", "m_bIsValveDS");
				offsets[XorStr("m_bBombPlanted")] = mGetOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
				offsets[XorStr("m_bBombDropped")] = mGetOffset("DT_CSGameRulesProxy", "m_bBombDropped");
				offsets[XorStr("m_flFlashMaxAlpha")] = mGetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
				offsets[XorStr("m_bHasHelmet")] = mGetOffset("DT_CSPlayer", "m_bHasHelmet");
				offsets[XorStr("m_bHasDefuser")] = mGetOffset("DT_CSPlayer", "m_bHasDefuser");
				offsets[XorStr("m_bIsScoped")] = mGetOffset("DT_CSPlayer", "m_bIsScoped");
				offsets[XorStr("m_iGlowIndex")] = mGetOffset("DT_CSPlayer", "m_iGlowIndex");
				offsets[XorStr("m_iFOVStart")] = mGetOffset("DT_CSPlayer", "m_iFOVStart");
				offsets[XorStr("m_fFlags")] = mGetOffset("DT_CSPlayer", "m_fFlags");
				offsets[XorStr("m_hOwnerEntity")] = mGetOffset("DT_BaseEntity", "m_hOwnerEntity");
				offsets[XorStr("m_iHealth")] = mGetOffset("DT_BasePlayer", "m_iHealth");
				offsets[XorStr("m_ArmorValue")] = mGetOffset("DT_CSPlayer", "m_ArmorValue");
				offsets[XorStr("m_iTeamNum")] = mGetOffset("DT_BasePlayer", "m_iTeamNum");
				offsets[XorStr("m_iShotsFired")] = mGetOffset("DT_CSPlayer", "m_iShotsFired");
				offsets[XorStr("m_aimPunchAngle")] = mGetOffset("DT_BasePlayer", "m_aimPunchAngle");
				offsets[XorStr("m_viewPunchAngle")] = mGetOffset("DT_BasePlayer", "m_viewPunchAngle");
				offsets[XorStr("m_vecVelocity")] = mGetOffset("DT_CSPlayer", "m_vecVelocity[0]");
				offsets[XorStr("m_vecPunchAngles")] = mGetOffset("DT_BasePlayer", "m_aimPunchAngle");
				offsets[XorStr("m_vecViewOffset")] = mGetOffset("DT_CSPlayer", "m_vecViewOffset[0]");
				offsets[XorStr("m_angEyeAngles")] = mGetOffset("DT_CSPlayer", "m_angEyeAngles");
				offsets[XorStr("m_hActiveWeapon")] = mGetOffset("DT_BasePlayer", "m_hActiveWeapon");
				offsets[XorStr("m_iClip1")] = mGetOffset("DT_BaseCombatWeapon", "m_iClip1");
				offsets[XorStr("m_iClip2")] = mGetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
				offsets[XorStr("m_flNextPrimaryAttack")] = mGetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
				offsets[XorStr("m_flLowerBodyYawTarget")] = mGetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
				offsets[XorStr("m_bCanReload")] = offsets[XorStr("m_flNextPrimaryAttack")] + 0x6D;
				offsets[XorStr("m_bGunGameImmunity")] = mGetOffset("DT_CSPlayer", "m_bGunGameImmunity");
				offsets[XorStr("m_bPinPulled")] = mGetOffset("DT_BaseCSGrenade", "m_bPinPulled");
				offsets[XorStr("m_fThrowTime")] = mGetOffset("DT_BaseCSGrenade", "m_fThrowTime");
				offsets[XorStr("m_iItemDefinitionIndex")] = mGetOffset("DT_BaseCombatWeapon", "m_iItemDefinitionIndex");
				offsets[XorStr("m_bIsAutoaimTarget")] = mGetOffset("DT_BaseEntity", "m_bIsAutoaimTarget");
				offsets[XorStr("m_iItemIDHigh")] = mGetOffset("DT_BaseAttributableItem", "m_iItemIDHigh");
				offsets[XorStr("m_iAccountID")] = mGetOffset("DT_BaseAttributableItem", "m_iAccountID");
				offsets[XorStr("m_iEntityQuality")] = mGetOffset("DT_BaseAttributableItem", "m_iEntityQuality");
				offsets[XorStr("m_OriginalOwnerXuidLow")] = mGetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
				offsets[XorStr("m_OriginalOwnerXuidHigh")] = mGetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
				offsets[XorStr("m_nFallbackPaintKit")] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit");
				offsets[XorStr("m_flFallbackWear")] = mGetOffset("DT_BaseAttributableItem", "m_flFallbackWear");
				offsets[XorStr("m_nFallbackSeed")] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackSeed");
				offsets[XorStr("m_szCustomName")] = mGetOffset("DT_BaseAttributableItem", "m_szCustomName");
				offsets[XorStr("m_nFallbackStatTrak")] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackStatTrak");
				offsets[XorStr("m_nModelIndex")] = mGetOffset("DT_BaseViewModel", "m_nModelIndex");
				offsets[XorStr("m_nSequence")] = mGetOffset("DT_BaseViewModel", "m_nSequence");
				offsets[XorStr("m_iViewModelIndex")] = mGetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");
				offsets[XorStr("m_hOwner")] = mGetOffset("DT_PredictedViewModel", "m_hOwner");
				offsets[XorStr("m_hWeapon")] = mGetOffset("DT_BaseViewModel", "m_hWeapon");
				offsets[XorStr("m_bSpotted")] = mGetOffset("DT_BaseEntity", "m_bSpotted");
				offsets[XorStr("m_zoomLevel")] = mGetOffset("DT_WeaponAWP", "m_zoomLevel");
				offsets[XorStr("m_flSimulationTime")] = mGetOffset("DT_BaseEntity", "m_flSimulationTime");
				offsets[XorStr("m_hWeaponWorldModel")] = mGetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
				offsets[XorStr("m_iWorldModelIndex")] = mGetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
				offsets[XorStr("m_Item")] = mGetOffset("DT_BaseAttributableItem", "m_Item");
				ADD_LOG("2-1-9-1\n");
				offsets[XorStr("KeyValues_KeyValues")] = CSX::Memory::FindPatternV2(clientFactory, KEY_VALUES_MASK);
				offsets[XorStr("KeyValues_LoadFromBuffer")] = CSX::Memory::FindPatternV2(clientFactory, KEY_VALUES_LOAD_FROM_BUFFER_MASK);
				ADD_LOG("All Offsets sucessful\n");
				ADD_LOG("2-1-9-2\n");
	 		};
			LInitOffsets();
			ADD_LOG("2-1-9-3\n");
		}	
		virtual bool Init()
		{
			VMP_MUTATION("SetupThread_Init");
			auto LInit = [&]() -> bool
			{
#ifndef ONLY_DRAW_HOOK			
				ADD_LOG("2-1-1\n");
				if (!CSX::Utils::IsModuleLoad(engineFactory, 5001))
					return false;
				if (!CSX::Utils::IsModuleLoad(vguiFactory, 5001))
					return false;
				if (!CSX::Utils::IsModuleLoad(vguimatFactory, 5001))
					return false;
				if (!CSX::Utils::IsModuleLoad(valveStdFactory, 5001))
					return false;
				if (!CSX::Utils::IsModuleLoad(steamApiFactory, 5001))
					return false;
				if (!CSX::Utils::IsModuleLoad(serverBrowserFactory, 40000))
					return false;

				FastCall::G().t_Sleep(1500);

				if (!CSX::Utils::IsModuleLoad(clientFactory, 5001))
					return false;

				ADD_LOG("2-1-2\n");
				if (!g_NetVar.Init(I::Client()->GetAllClasses()))
				{
					ADD_LOG("2-1-9-8-1\n");
					FastCall::G().t_MessageBoxA(0, XorStr("AllClasses error"), XorStr("Error!"), 0);
					return false;
				}
				ADD_LOG("2-1-3\n");
				InitOffsets();
				ADD_LOG("2-1-4\n");
#endif 
				InitHooks();
				return true;
			};
			return LInit();

			VMP_END;
		}
	};
};