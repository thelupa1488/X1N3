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
			VMP_ULTRA("InitHooks");
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

				offsets["m_hMyWeapons"] =  mGetOffset("DT_BasePlayer", "m_hActiveWeapon") / 2;
				offsets["m_hMyWearables"] = mGetOffset("DT_BasePlayer", "m_hMyWearables");
				offsets["m_vecOrigin"] = mGetOffset("DT_BasePlayer", "m_vecOrigin");
				offsets["m_hViewModel"] = mGetOffset("DT_BasePlayer", "m_hViewModel[0]");
				offsets["m_nTickBase"] = mGetOffset("DT_BasePlayer", "m_nTickBase");
				offsets["m_iObserverMode"] = mGetOffset("DT_BasePlayer", "m_iObserverMode");
				offsets["m_hObserverTarget"] = mGetOffset("DT_BasePlayer", "m_hObserverTarget");
				offsets["deadflag"] = mGetOffset("DT_BasePlayer", "deadflag");
				offsets["m_bIsDefusing"] = mGetOffset("DT_CSPlayer", "m_bIsDefusing");
				offsets["m_iAccount"] = mGetOffset("DT_CSPlayer", "m_iAccount");
				offsets["m_lifeState"] = mGetOffset("DT_CSPlayer", "m_lifeState");
				offsets["m_flFlashDuration"] = mGetOffset("DT_CSPlayer", "m_flFlashDuration");
				offsets["m_flSpawnTime"] = mGetOffset("DT_CSPlayer", "m_flSpawnTime");
				offsets["m_flC4Blow"] = mGetOffset("DT_PlantedC4", "m_flC4Blow");
				offsets["m_flDefuseCountDown"] = mGetOffset("DT_PlantedC4", "m_flDefuseCountDown");
				offsets["m_hBombDefuser"] = mGetOffset("DT_PlantedC4", "m_hBombDefuser");
				offsets["m_bBombDefused"] = mGetOffset("DT_PlantedC4", "m_bBombDefused");
				offsets["m_nBombSite"] = mGetOffset("DT_PlantedC4", "m_nBombSite");
				offsets["m_flFlashMaxAlpha"] = mGetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
				offsets["m_bHasHelmet"] = mGetOffset("DT_CSPlayer", "m_bHasHelmet");
				offsets["m_bHasDefuser"] = mGetOffset("DT_CSPlayer", "m_bHasDefuser");
				offsets["m_bIsScoped"] = mGetOffset("DT_CSPlayer", "m_bIsScoped");
				offsets["m_iGlowIndex"] = mGetOffset("DT_CSPlayer", "m_iGlowIndex");
				offsets["m_iFOVStart"] = mGetOffset("DT_CSPlayer", "m_iFOVStart");
				offsets["m_fFlags"] = mGetOffset("DT_CSPlayer", "m_fFlags");
				offsets["m_hOwnerEntity"] = mGetOffset("DT_BaseEntity", "m_hOwnerEntity");
				offsets["m_iHealth"] = mGetOffset("DT_BasePlayer", "m_iHealth");
				offsets["m_ArmorValue"] = mGetOffset("DT_CSPlayer", "m_ArmorValue");
				offsets["m_iTeamNum"] = mGetOffset("DT_BasePlayer", "m_iTeamNum");
				offsets["m_iShotsFired"] = mGetOffset("DT_CSPlayer", "m_iShotsFired");
				offsets["m_aimPunchAngle"] = mGetOffset("DT_BasePlayer", "m_aimPunchAngle");
				offsets["m_viewPunchAngle"] = mGetOffset("DT_BasePlayer", "m_viewPunchAngle");
				offsets["m_vecVelocity"] = mGetOffset("DT_CSPlayer", "m_vecVelocity[0]");
				offsets["m_vecPunchAngles"] = mGetOffset("DT_BasePlayer", "m_aimPunchAngle");
				offsets["m_vecViewOffset"] = mGetOffset("DT_CSPlayer", "m_vecViewOffset[0]");
				offsets["m_angEyeAngles"] = mGetOffset("DT_CSPlayer", "m_angEyeAngles");
				offsets["m_hActiveWeapon"] = mGetOffset("DT_BasePlayer", "m_hActiveWeapon");
				offsets["m_iClip1"] = mGetOffset("DT_BaseCombatWeapon", "m_iClip1");
				offsets["m_iClip2"] = mGetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
				offsets["m_flNextPrimaryAttack"] = mGetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
				offsets["m_flLowerBodyYawTarget"] = mGetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
				offsets["m_bCanReload"] = offsets["m_flNextPrimaryAttack"] + 0x6D;
				offsets["m_bGunGameImmunity"] = mGetOffset("DT_CSPlayer", "m_bGunGameImmunity");
				offsets["m_bPinPulled"] = mGetOffset("DT_BaseCSGrenade", "m_bPinPulled");
				offsets["m_fThrowTime"] = mGetOffset("DT_BaseCSGrenade", "m_fThrowTime");
				offsets["m_iItemDefinitionIndex"] = mGetOffset("DT_BaseCombatWeapon", "m_iItemDefinitionIndex");
				offsets["m_bIsAutoaimTarget"] = mGetOffset("DT_BaseEntity", "m_bIsAutoaimTarget");
				offsets["m_iItemIDHigh"] = mGetOffset("DT_BaseAttributableItem", "m_iItemIDHigh");
				offsets["m_iAccountID"] = mGetOffset("DT_BaseAttributableItem", "m_iAccountID");
				offsets["m_iEntityQuality"] = mGetOffset("DT_BaseAttributableItem", "m_iEntityQuality");
				offsets["m_OriginalOwnerXuidLow"] = mGetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
				offsets["m_OriginalOwnerXuidHigh"] = mGetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
				offsets["m_nFallbackPaintKit"] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit");
				offsets["m_flFallbackWear"] = mGetOffset("DT_BaseAttributableItem", "m_flFallbackWear");
				offsets["m_nFallbackSeed"] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackSeed");
				offsets["m_szCustomName"] = mGetOffset("DT_BaseAttributableItem", "m_szCustomName");
				offsets["m_nFallbackStatTrak"] = mGetOffset("DT_BaseAttributableItem", "m_nFallbackStatTrak");
				offsets["m_nModelIndex"] = mGetOffset("DT_BaseViewModel", "m_nModelIndex");
				offsets["m_nSequence"] = mGetOffset("DT_BaseViewModel", "m_nSequence");
				offsets["m_iViewModelIndex"] = mGetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");
				offsets["m_hOwner"] = mGetOffset("DT_PredictedViewModel", "m_hOwner");
				offsets["m_hWeapon"] = mGetOffset("DT_BaseViewModel", "m_hWeapon");
				offsets["m_bSpotted"] = mGetOffset("DT_BaseEntity", "m_bSpotted");
				offsets["m_zoomLevel"] = mGetOffset("DT_WeaponAWP", "m_zoomLevel");
				offsets["m_flSimulationTime"] = mGetOffset("DT_BaseEntity", "m_flSimulationTime");
				offsets["m_hWeaponWorldModel"] = mGetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
				offsets["m_iWorldModelIndex"] = mGetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
				offsets["m_Item"] = mGetOffset("DT_BaseAttributableItem", "m_Item");
				ADD_LOG("2-1-9-1\n");
				offsets["KeyValues_KeyValues"] = CSX::Memory::FindPatternV2(clientFactory, KEY_VALUES_MASK);
				offsets["KeyValues_LoadFromBuffer"] = CSX::Memory::FindPatternV2(clientFactory, KEY_VALUES_LOAD_FROM_BUFFER_MASK);
				ADD_LOG("All Offsets sucessful\n");
				ADD_LOG("2-1-9-2\n");
	 		};
			LInitOffsets();
			ADD_LOG("2-1-9-3\n");
		}	
		virtual bool Init()
		{
			VMP_ULTRA("SetupThread_Init");
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
					FastCall::G().t_MessageBoxA(0, "AllClasses error", "Error!", 0);
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