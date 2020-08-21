#include "Offsets.h"
#include <map>
#include <string>

std::map<std::string, DWORD> offsets;

namespace Offsets
{
	DWORD m_hMyWeapons = 0;
	DWORD m_hMyWearables = 0;
	DWORD m_hViewModel = 0;
	DWORD m_nTickBase = 0;
	DWORD m_flFlashMaxAlpha = 0;
	DWORD m_iObserverMode = 0;
	DWORD m_hObserverTarget = 0;

	DWORD deadflag = 0;

	DWORD m_lifeState = 0;
	DWORD m_flFlashDuration = 0;
	DWORD m_flSpawnTime = 0;

	DWORD m_iAccount = 0;

	DWORD m_bHasHelmet = 0;
	DWORD m_bHasDefuser = 0;

	DWORD m_flDefuseCountDown = 0;
	DWORD m_flC4Blow = 0;
	DWORD m_hBombDefuser = 0;
	DWORD m_bBombDefused = 0;
	DWORD m_nBombSite = 0;

	DWORD m_bFreezePeriod = 0;
	DWORD m_bIsValveDS = 0;
	DWORD m_bBombPlanted = 0;
	DWORD m_bBombDropped = 0;

	DWORD m_bIsScoped = 0;

	DWORD m_iGlowIndex = 0;

	DWORD m_iFOVStart = 0;
	DWORD m_fFlags = 0;
	DWORD m_hOwnerEntity = 0;

	DWORD m_iHealth = 0;
	DWORD m_ArmorValue = 0;
	DWORD m_iTeamNum = 0;
	DWORD m_iShotsFired = 0;

	DWORD m_aimPunchAngle = 0;
	DWORD m_viewPunchAngle = 0;

	DWORD m_flSimulationTime = 0;
	DWORD m_flDuckAmount = 0;

	DWORD m_vecVelocity = 0;
	DWORD m_vecViewOffset = 0;
	DWORD m_vecPunchAngles = 0;

	DWORD m_vecOrigin = 0;

	DWORD m_nRenderMode = 0;
	DWORD m_MoveType = 0;
	DWORD m_bIsDefusing = 0;

	DWORD m_angEyeAngles = 0;

	DWORD m_hActiveWeapon = 0;

	DWORD m_iClip1 = 0;
	DWORD m_iClip2 = 0;
	DWORD m_flNextPrimaryAttack = 0;
	DWORD m_flLowerBodyYawTarget = 0;
	DWORD m_iWorldModelIndex = 0;
	DWORD m_nHitboxSet = 0;
	DWORD m_bCanReload = 0;
	DWORD m_bGunGameImmunity = 0;
	DWORD m_bPinPulled = 0;
	DWORD m_fThrowTime = 0;

	DWORD m_iItemDefinitionIndex = 0;
	DWORD m_iItemIDHigh = 0;
	DWORD m_iAccountID = 0;
	DWORD m_iEntityQuality = 0;
	DWORD m_OriginalOwnerXuidLow = 0;
	DWORD m_OriginalOwnerXuidHigh = 0;
	DWORD m_nFallbackPaintKit = 0;
	DWORD m_flFallbackWear = 0;
	DWORD m_nFallbackSeed = 0;
	DWORD m_nFallbackStatTrak = 0;
	DWORD m_szCustomName = 0;
	DWORD m_hWeaponWorldModel = 0;
	DWORD m_bIsAutoaimTarget = 0;

	DWORD m_nSequence = 0;
	DWORD m_nModelIndex = 0;
	DWORD m_iViewModelIndex = 0;
	DWORD m_hOwner = 0;
	DWORD m_hWeapon = 0;
	DWORD m_bSpotted = 0;

	DWORD m_zoomLevel = 0;

	DWORD m_CollisionGroup = 0;
	DWORD m_rgflCoordinateFrame = 0;

	DWORD m_vecMins = 0;
	DWORD m_vecMaxs = 0;
	DWORD m_Item = 0;

	DWORD Input = 0;
	DWORD MoveHelper = 0;
	DWORD ClientState = 0;

	DWORD d3d9TablePtrPtr = 0;

	DWORD PredictionSeed = 0;
	DWORD PredictionPlayer = 0;
	DWORD SetLocalPlayerReady = 0;
	DWORD SmokeCount = 0;
	DWORD SetClanTag = 0;
	DWORD ItemDefinitionByName = 0;
	DWORD ItemDefinitionMap = 0;
	DWORD LineGoesThroughSmoke = 0;
	DWORD ViewMatrix = 0;
	DWORD SequenceActivity = 0;
	DWORD CurrentCommand = 0;
	DWORD InvalidateBoneCache = 0;
	DWORD SetAbsAngles = 0;
	DWORD SetAbsOrigin = 0;
	DWORD FromString = 0;
	DWORD FindKey = 0;
	DWORD SetString = 0;
	DWORD IsReloading = 0;
	DWORD InitializeKits = 0;
	DWORD InitializeStickers = 0;
	DWORD MakeGlove = 0;
	DWORD FindHudElementThis = 0;
	DWORD FindHudElement = 0;
	DWORD FullUpdate = 0;
}