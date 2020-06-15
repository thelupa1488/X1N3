#pragma once

#include "Engine.h"

namespace SDK
{
	class IClientEntity;
}

using namespace SDK;

namespace Engine
{
	class CBaseAttributableItem;
	class CBaseViewModel;

	class CBaseWeapon : public IClientEntity
	{
	public:
		int				GetWeaponAmmo();
		int             GetWeaponAmmoClp2();
		bool            IsReloading();
		bool            CanFire();
		int				GetZoomLevel();
		bool			GetWeaponReload();
		float			GetNextPrimaryAttack();
		bool			GetPinPulled();
		float			GetThrowTime();
		float           GetInaccuracy();
		HANDLE*         GetWeaponWorldModel();
		int*            ModelIndex();
		int*            ViewModelIndex();
		int*            fixItemIDHigh();
		short*          fixskins();
		int*            OwnerXuidLow();
		int*            OwnerXuidHigh();
		CCSWeaponInfo*  GetWeaponInfo();
		CBaseAttributableItem* GeteAttributableItem();
		int*            GetEntityQuality();

		const char*     GetName();
		const char*     GetPrintName();

	};

	class CBaseAttributableItem : public IClientEntity
	{
	public:

		short* GetItemDefinitionIndex();
		int* GetItemIDHigh();
		int* GetAccountID();
		int* GetEntityQuality();
		int* GetOriginalOwnerXuidLow();
		int* GetOriginalOwnerXuidHigh();
		int* GetFallbackPaintKit();
		float* GetFallbackWear();
		int* GetFallbackSeed();
		int* GetFallbackStatTrak();
		char* GetCustomName();
		CBaseViewModel* GetViewModel();
		int* GetIndex();
		int* ModelIndex();
		int* ViewModelIndex();
	};

	enum WEAPON_TYPE
	{
		WEAPON_TYPE_KNIFE,
		WEAPON_TYPE_RIFEL,
		WEAPON_TYPE_PISTOL,
		WEAPON_TYPE_SHOTGUN,
		WEAPON_TYPE_SNIPER,
		WEAPON_TYPE_C4,
		WEAPON_TYPE_GRENADE,
		WEAPON_TYPE_UNKNOWN,
	};


	enum WEAPON_ID
	{
		//	WEAPON_INVALID = -1,
		WEAPON_NONE = 0,
		WEAPON_DEAGLE = 1,
		WEAPON_ELITE = 2,
		WEAPON_FIVESEVEN = 3,
		WEAPON_GLOCK = 4,
		WEAPON_AK47 = 7,
		WEAPON_AUG = 8,
		WEAPON_AWP = 9,
		WEAPON_FAMAS = 10,
		WEAPON_G3SG1 = 11,
		WEAPON_GALILAR = 13,
		WEAPON_M249 = 14,
		WEAPON_M4A4 = 16,
		WEAPON_MAC10 = 17,
		WEAPON_P90 = 19,
		WEAPON_MP5 = 23,
		WEAPON_UMP45 = 24,
		WEAPON_XM1014 = 25,
		WEAPON_BIZON = 26,
		WEAPON_MAG7 = 27,
		WEAPON_NEGEV = 28,
		WEAPON_SAWEDOFF = 29,
		WEAPON_TEC9 = 30,
		WEAPON_TASER = 31,
		WEAPON_HKP2000 = 32,
		WEAPON_MP7 = 33,
		WEAPON_MP9 = 34,
		WEAPON_NOVA = 35,
		WEAPON_P250 = 36,
		WEAPON_SHIELD = 37,
		WEAPON_SCAR20 = 38,
		WEAPON_SG553 = 39,
		WEAPON_SSG08 = 40,
		WEAPON_KNIFEGG = 41,
		WEAPON_KNIFE = 42,
		WEAPON_FLASHBANG = 43,
		WEAPON_HEGRENADE = 44,
		WEAPON_SMOKEGRENADE = 45,
		WEAPON_MOLOTOV = 46,
		WEAPON_DECOY = 47,
		WEAPON_INCGRENADE = 48,
		WEAPON_C4 = 49,
		WEAPON_HEALTHSHOT = 57,
		WEAPON_KNIFE_T = 59,
		WEAPON_M4A1_SILENCER = 60,
		WEAPON_USP_SILENCER = 61,
		WEAPON_CZ75A = 63,
		WEAPON_REVOLVER = 64,
		WEAPON_TAGRENADE = 68,
		WEAPON_FISTS = 69,
		WEAPON_BREACHCHARGE = 70,
		WEAPON_TABLET = 72,
		WEAPON_MELEE = 74,
		WEAPON_AXE = 75,
		WEAPON_HAMMER = 76,
		WEAPON_SPANNER = 78,
		WEAPON_KNIFE_GHOST = 80,
		WEAPON_FIREBOMB = 81,
		WEAPON_DIVERSION = 82,
		WEAPON_FRAG_GRENADE = 83,
		WEAPON_SNOWBALL = 84,
		WEAPON_BUMPMINE = 85,
		WEAPON_KNIFE_BAYONET = 500,
		WEAPON_KNIFE_CSS = 503,
		WEAPON_KNIFE_FLIP = 505,
		WEAPON_KNIFE_GUT = 506,
		WEAPON_KNIFE_KARAMBIT = 507,
		WEAPON_KNIFE_M9_BAYONET = 508,
		WEAPON_KNIFE_TACTICAL = 509,
		WEAPON_KNIFE_FALCHION = 512,
		WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
		WEAPON_KNIFE_BUTTERFLY = 515,
		WEAPON_KNIFE_PUSH = 516,
		WEAPON_KNIFE_CORD = 517,
		WEAPON_KNIFE_CANIS = 518,
		WEAPON_KNIFE_URSUS = 519,
		WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
		WEAPON_KNIFE_OUTDOOR = 521,
		WEAPON_KNIFE_STILETTO = 522,
		WEAPON_KNIFE_WIDOWMAKER = 523,
		WEAPON_KNIFE_SKELETON = 525,
		GLOVE_STUDDED_BLOODHOUND = 5027,
		GLOVE_T_SIDE = 5028,
		GLOVE_CT_SIDE = 5029,
		GLOVE_SPORTY = 5030,
		GLOVE_SLICK = 5031,
		GLOVE_LEATHER_WRAP = 5032,
		GLOVE_MOTORCYCLE = 5033,
		GLOVE_SPECIALIST = 5034,
		GLOVE_HYDRA = 5035,
		MAX_ITEMDEFINITIONINDEX
	};

	enum CLIENT_CLASS_ID
	{
		CAI_BaseNPC,
		CAK47,
		CAnimating,
		CAnimatingOverlay,
		CAttributableItem,
		CButton,
		CCombatCharacter,
		CCombatWeapon,
		CCSGrenade,
		CCSGrenadeProjectile,
		CDoor,
		CEntity,
		CFlex,
		CGrenade,
		CParticleEntity,
		CPlayer,
		CPropDoor,
		CTeamObjectiveResource,
		CTempEntity,
		CToggle,
		CTrigger,
		CViewModel,
		CVPhysicsTrigger,
		CWeaponWorldModel,
		CBeam,
		CBeamSpotlight,
		CBoneFollower,
		CBRC4Target,
		CBreachCharge,
		CBreachChargeProjectile,
		CBreakableProp,
		CBreakableSurface,
		CBumpMine,
		CBumpMineProjectile,
		CC4,
		CCascadeLight,
		CChicken,
		CColorCorrection,
		CColorCorrectionVolume,
		CCSGameRulesProxy,
		CCSPlayer,
		CCSPlayerResource,
		CCSRagdoll,
		CCSTeam,
		CDangerZone,
		CDangerZoneController,
		CDEagle,
		CDecoyGrenade,
		CDecoyProjectile,
		CDrone,
		CDronegun,
		CDynamicLight,
		CDynamicProp,
		CEconEntity,
		CEconWearable,
		CEmbers,
		CEntityDissolve,
		CEntityFlame,
		CEntityFreezing,
		CEntityParticleTrail,
		CEnvAmbientLight,
		CEnvDetailController,
		CEnvDOFController,
		CEnvGasCanister,
		CEnvParticleScript,
		CEnvProjectedTexture,
		CEnvQuadraticBeam,
		CEnvScreenEffect,
		CEnvScreenOverlay,
		CEnvTonemapController,
		CEnvWind,
		CFEPlayerDecal,
		CFireCrackerBlast,
		CFireSmoke,
		CFireTrail,
		CFish,
		CFists,
		CFlashbang,
		CFogController,
		CFootstepControl,
		CFunc_Dust,
		CFunc_LOD,
		CFuncAreaPortalWindow,
		CFuncBrush,
		CFuncConveyor,
		CFuncLadder,
		CFuncMonitor,
		CFuncMoveLinear,
		CFuncOccluder,
		CFuncReflectiveGlass,
		CFuncRotating,
		CFuncSmokeVolume,
		CFuncTrackTrain,
		CGameRulesProxy,
		CGrassBurn,
		CHandleTest,
		CHEGrenade,
		CHostage,
		CHostageCarriableProp,
		CIncendiaryGrenade,
		CInferno,
		CInfoLadderDismount,
		CInfoMapRegion,
		CInfoOverlayAccessor,
		CItem_Healthshot,
		CItemCash,
		CItemDogtags,
		CKnife,
		CKnifeGG,
		CLightGlow,
		CMaterialModifyControl,
		CMelee,
		CMolotovGrenade,
		CMolotovProjectile,
		CMovieDisplay,
		CParadropChopper,
		CParticleFire,
		CParticlePerformanceMonitor,
		CParticleSystem,
		CPhysBox,
		CPhysBoxMultiplayer,
		CPhysicsProp,
		CPhysicsPropMultiplayer,
		CPhysMagnet,
		CPhysPropAmmoBox,
		CPhysPropLootCrate,
		CPhysPropRadarJammer,
		CPhysPropWeaponUpgrade,
		CPlantedC4,
		CPlasma,
		CPlayerPing,
		CPlayerResource,
		CPointCamera,
		CPointCommentaryNode,
		CPointWorldText,
		CPoseController,
		CPostProcessController,
		CPrecipitation,
		CPrecipitationBlocker,
		CPredictedViewModel,
		CProp_Hallucination,
		CPropCounter,
		CPropDoorRotating,
		CPropJeep,
		CPropVehicleDriveable,
		CRagdollManager,
		CRagdollProp,
		CRagdollPropAttached,
		CRopeKeyframe,
		CSCAR17,
		CSceneEntity,
		CSensorGrenade,
		CSensorGrenadeProjectile,
		CShadowControl,
		CSlideshowDisplay,
		CSmokeGrenade,
		CSmokeGrenadeProjectile,
		CSmokeStack,
		CSnowball,
		CSnowballPile,
		CSnowballProjectile,
		CSpatialEntity,
		CSpotlightEnd,
		CSprite,
		CSpriteOriented,
		CSpriteTrail,
		CStatueProp,
		CSteamJet,
		CSun,
		CSunlightShadowControl,
		CSurvivalSpawnChopper,
		CTablet,
		CTeam,
		CTeamplayRounddRulesProxy,
		CTEArmorRicochet,
		CTEBeam,
		CTEBeamEntPoint,
		CTEBeamEnts,
		CTEBeamFollow,
		CTEBeamLaser,
		CTEBeamPoints,
		CTEBeamRing,
		CTEBeamRingPoint,
		CTEBeamSpline,
		CTEBloodSprite,
		CTEBloodStream,
		CTEBreakModel,
		CTEBSPDecal,
		CTEBubbles,
		CTEBubbleTrail,
		CTEClientProjectile,
		CTEDecal,
		CTEDust,
		CTEDynamicLight,
		CTEEffectDispatch,
		CTEEnergySplash,
		CTEExplosion,
		CTEFireBullets,
		CTEFizz,
		CTEFootprintDecal,
		CTEFoundryHelpers,
		CTEGaussExplosion,
		CTEGlowSprite,
		CTEImpact,
		CTEKillPlayerAttachments,
		CTELargeFunnel,
		CTEMetalSparks,
		CTEMuzzleFlash,
		CTEParticleSystem,
		CTEPhysicsProp,
		CTEPlantBomb,
		CTEPlayerAnimEvent,
		CTEPlayerDecal,
		CTEProjectedDecal,
		CTERadioIcon,
		CTEShatterSurface,
		CTEShowLine,
		CTesla,
		CTESmoke,
		CTESparks,
		CTESprite,
		CTESpriteSpray,
		CTest_ProxyToggle_Networkable,
		CTestTraceline,
		CTEWorldDecal,
		CTriggerPlayerMovement,
		CTriggerSoundOperator,
		CVGuiScreen,
		CVoteController,
		CWaterBullet,
		CWaterLODControl,
		CWeaponAug,
		CWeaponAWP,
		CWeaponItem,
		CWeaponBizon,
		CWeaponCS,
		CWeaponCSGun,
		CWeaponCycler,
		CWeaponElite,
		CWeaponFamas,
		CWeaponFiveSeven,
		CWeaponG3SG1,
		CWeaponGalil,
		CWeaponGalilAR,
		CWeaponGlock,
		CWeaponHKP2000,
		CWeaponM249,
		CWeaponM3,
		CWeaponM4A1,
		CWeaponMAC10,
		CWeaponMag7,
		CWeaponMP5Navy,
		CWeaponMP7,
		CWeaponMP9,
		CWeaponNegev,
		CWeaponNOVA,
		CWeaponP228,
		CWeaponP250,
		CWeaponP90,
		CWeaponSawedoff,
		CWeaponSCAR20,
		CWeaponScout,
		CWeaponSG550,
		CWeaponSG552,
		CWeaponSG556,
		CWeaponShield,
		CWeaponSSG08,
		CWeaponTaser,
		CWeaponTec9,
		CWeaponTMP,
		CWeaponUMP45,
		CWeaponUSP,
		CWeaponXM1014,
		CWeaponZoneRepulsor,
		CWorld,
		CWorldVguiText,
		DustTrail,
		MovieExplosion,
		ParticleSmokeGrenade,
		RocketTrail,
		SmokeTrail,
		SporeExplosion,
		SporeTrail
	};
}