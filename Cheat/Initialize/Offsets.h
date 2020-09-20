#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include "../Include/Def.h"

extern std::map<std::string, DWORD> offsets;

namespace Offsets
{
	extern DWORD m_hMyWeapons;
	extern DWORD m_hMyWearables;
	extern DWORD m_hViewModel;
	extern DWORD m_nTickBase;
	extern DWORD m_flFlashMaxAlpha;
	extern DWORD m_hRagdoll;
	extern DWORD m_iObserverMode;
	extern DWORD m_hObserverTarget;
	extern DWORD m_vecOrigin;
	extern DWORD deadflag;

	extern DWORD m_nRenderMode;
	extern DWORD m_MoveType;
	extern DWORD m_bIsDefusing;

	extern DWORD m_lifeState;
	extern DWORD m_flFlashDuration;
	extern DWORD m_flSpawnTime;

	extern DWORD m_iAccount;

	extern DWORD m_bHasHelmet;
	extern DWORD m_bHasDefuser;

	extern DWORD m_flDefuseCountDown;
	extern DWORD m_flC4Blow;
	extern DWORD m_hBombDefuser;
	extern DWORD m_bBombDefused;
	extern DWORD m_nBombSite;

	extern DWORD m_bFreezePeriod;
	extern DWORD m_bIsValveDS;
	extern DWORD m_bBombPlanted;
	extern DWORD m_bBombDropped;

	extern DWORD m_bIsScoped;

	extern DWORD m_iGlowIndex;

	extern DWORD m_iFOVStart;
	extern DWORD m_fFlags;
	extern DWORD m_hOwnerEntity;
	extern DWORD m_iHealth;
	extern DWORD m_ArmorValue;
	extern DWORD m_iTeamNum;
	extern DWORD m_iShotsFired;

	extern DWORD m_aimPunchAngle;
	extern DWORD m_viewPunchAngle;

	extern DWORD m_flSimulationTime;
	extern DWORD m_flDuckAmount;

	extern DWORD m_vecVelocity;
	extern DWORD m_vecViewOffset;
	extern DWORD m_vecPunchAngles;

	extern DWORD m_angEyeAngles;

	extern DWORD m_hActiveWeapon;

	extern DWORD m_iClip1;
	extern DWORD m_iClip2;
	extern DWORD m_flNextPrimaryAttack;
	extern DWORD m_flLowerBodyYawTarget;
	extern DWORD m_iWorldModelIndex;
	extern DWORD m_nHitboxSet;
	extern DWORD m_bCanReload;
	extern DWORD m_bGunGameImmunity;
	extern DWORD m_bPinPulled;
	extern DWORD m_fThrowTime;

	extern DWORD PlayerAnimState;
	extern DWORD AnimOverlays;
	extern DWORD m_flPoseParameter;
	extern DWORD CreateAnimState;
	extern DWORD UpdateAnimState;
	extern DWORD ResetAnimState;

	extern DWORD m_iItemDefinitionIndex;
	extern DWORD m_iItemIDHigh;
	extern DWORD m_iAccountID;
	extern DWORD m_iEntityQuality;
	extern DWORD m_OriginalOwnerXuidLow;
	extern DWORD m_OriginalOwnerXuidHigh;
	extern DWORD m_nFallbackPaintKit;
	extern DWORD m_flFallbackWear;
	extern DWORD m_nFallbackSeed;
	extern DWORD m_nFallbackStatTrak;
	extern DWORD m_bIsAutoaimTarget;

	extern DWORD m_szCustomName;
	extern DWORD m_hWeaponWorldModel;

	extern DWORD m_nSequence;
	extern DWORD m_nModelIndex;
	extern DWORD  m_iViewModelIndex;
	extern DWORD m_hOwner;
	extern DWORD m_hWeapon;
	extern DWORD m_bSpotted;

	extern DWORD m_zoomLevel;

	extern DWORD m_CollisionGroup;
	extern DWORD m_rgflCoordinateFrame;

	extern DWORD m_vecMins;
	extern DWORD m_vecMaxs;
	extern DWORD m_Item;

	extern DWORD Input;
	extern DWORD MoveHelper;
	extern DWORD ClientState;
	extern DWORD GameRules;

	extern DWORD d3d9TablePtrPtr;

	extern DWORD PredictionSeed;
	extern DWORD PredictionPlayer;
	extern DWORD SetLocalPlayerReady;
	extern DWORD SmokeCount;
	extern DWORD SetClanTag;
	extern DWORD ItemDefinitionByName;
	extern DWORD ItemDefinitionMap;
	extern DWORD LineGoesThroughSmoke;
	extern DWORD ViewMatrix;
	extern DWORD SequenceActivity;
	extern DWORD CurrentCommand;
	extern DWORD InvalidateBoneCache;
	extern DWORD SetAbsAngles;
	extern DWORD SetAbsOrigin;
	extern DWORD FromString;
	extern DWORD FindKey;
	extern DWORD SetString;
	extern DWORD IsReloading;
	extern DWORD InitializeKits;
	extern DWORD InitializeStickers;
	extern DWORD MakeGlove;
	extern DWORD FindHudElementThis;
	extern DWORD FindHudElement;
	extern DWORD FullUpdate;
}

