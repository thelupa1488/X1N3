#pragma once

#include "Engine.h"

namespace SDK
{
	class IClientEntity;
}

using namespace SDK;

namespace Engine
{
	class CBaseWeapon;
	class CBaseViewModel;
	class AnimationLayer;

	class AnimationLayer
	{
	public:
		char  pad_0000[20];
		// These should also be present in the padding, don't see the use for it though
		//float	m_flLayerAnimtime;
		//float	m_flLayerFadeOuttime;
		uint32_t m_nOrder; //0x0014
		uint32_t m_nSequence; //0x0018
		float_t m_flPrevCycle; //0x001C
		float_t m_flWeight; //0x0020
		float_t m_flWeightDeltaRate; //0x0024
		float_t m_flPlaybackRate; //0x0028
		float_t m_flCycle; //0x002C
		void* m_pOwner; //0x0030 // player's thisptr
		char  pad_0038[4]; //0x0034
	}; //Size: 0x0038

	class CCSGOPlayerAnimState
	{
	public:
		void* pThis;
		char pad2[91];
		void* pBaseEntity; //0x60
		void* pActiveWeapon; //0x64
		void* pLastActiveWeapon; //0x68
		float m_flLastClientSideAnimationUpdateTime; //0x6C
		int m_iLastClientSideAnimationUpdateFramecount; //0x70
		float m_flEyePitch; //0x74
		float m_flEyeYaw; //0x78
		float m_flPitch; //0x7C
		float m_flGoalFeetYaw; //0x80
		float m_flCurrentFeetYaw; //0x84
		float m_flCurrentTorsoYaw; //0x88
		float m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
		float m_flLeanAmount; //0x90
		char pad4[4]; //NaN
		float m_flFeetCycle; //0x98 0 to 1
		float m_flFeetYawRate; //0x9C 0 to 1
		float m_fUnknown2;
		float m_fDuckAmount; //0xA4
		float m_fLandingDuckAdditiveSomething; //0xA8
		float m_fUnknown3; //0xAC
		Vector m_vOrigin; //0xB0, 0xB4, 0xB8
		Vector m_vLastOrigin; //0xBC, 0xC0, 0xC4
		float m_vVelocityX; //0xC8
		float m_vVelocityY; //0xCC
		char pad5[4];
		float m_flUnknownFloat1; //0xD4 Affected by movement and direction
		char pad6[8];
		float m_flUnknownFloat2; //0xE0 //from -1 to 1 when moving and affected by direction
		float m_flUnknownFloat3; //0xE4 //from -1 to 1 when moving and affected by direction
		float m_unknown; //0xE8
		float speed_2d; //0xEC
		float flUpVelocity; //0xF0
		float m_flSpeedNormalized; //0xF4 //from 0 to 1
		float m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
		float m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
		float m_flTimeSinceStartedMoving; //0x100
		float m_flTimeSinceStoppedMoving; //0x104
		unsigned char m_bOnGround; //0x108
		unsigned char m_bInHitGroundAnimation; //0x109
		char pad7[10];
		float m_flLastOriginZ; //0x114
		float m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
		float m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
		char pad8[4]; //NaN
		float m_flUnknownFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
		char pad9[4]; //NaN
		float m_flUnknown3;
		char pad10[528];
	}; //Size=0x344

	class CBaseEntity : public IClientEntity
	{
	public:
		//[swap_lines]
		int     GetSequenceActivity(int sequence);
		char*	GetPlayerName();
		bool    m_bIsDefusing();

		bool	IsPlayer();
		bool	IsValid();
		bool	IsDead();
		bool	IsVisibleHitBox(CBaseEntity* pLocalEntity, Vector& vecAbsStart, Vector& vecAbsEnd, bool smokeCheck = true, bool flashcheck = false);
		bool	IsVisible(CBaseEntity* pLocalEntity);
		float   GetFlashDuration();
		bool    IsFlashed();
		int     GetMoney();
		Vector  GetOrigin();

		float   GetC4BlowTime();

		float   GetC4DefuseCountDown();
		float   GetLowerBodyYawTarget();
		QAngle& GetVAngles();
		void    UpdateClientSideAnimation();
		CCSGOPlayerAnimState* GetBasePlayerAnimState();
		AnimationLayer* GetAnimOverlays();
		AnimationLayer* GetAnimOverlay(int i);
		CUserCmd*&      GetCurrentCommand();
		float           GetMaxDesyncAngle();
		float           MaxRotation(CCSGOPlayerAnimState* AnimState);
		float           GetSpawnTime();


		int     GetBombDefuser();
		int     GetBombSite();
		int     GetMoveType();
		bool    IsBombDefused();
		bool    GetGunGameImmunity();

		bool	HasHelmet();
		bool	HasDefuser();
		bool*	IsSpotted();

		int		GetFovStart();
		int		GetFlags();
		int		GetOwner();
		int		GetHealth();
		int		GetArmor();
		int		GetTeam();
		float	GetSimTime();
		int		GetShotsFired();
		int		GetIsScoped();
		int		GetGlowIndex();
		int		GetTickBase();

		float* GetFlashMaxAlpha();

		ObserverMode_t GetObserverMode();
		PVOID GetObserverTarget();

		PVOID			GetActiveWeapon();
		CBaseWeapon*	GetBaseWeapon();
		UINT*			GetWeapons();
		CBaseHandle*    m_hMyWeapons();
		UINT*			GetWearables();
		CBaseViewModel* GetViewModel();

		Vector	GetAimPunchAngle();
		Vector	GetViewPunchAngle();

		Vector	    GetVelocity();
		Vector	    GetViewOffset();
		Vector	    GetEyePosition();
		Vector      GetPunchAngles();

		QAngle	            GetEyeAngles();
		//QAngle	        GetPunch();

		Vector	GetBonePosition(int nBone);
		Vector	GetHitboxPosition(int nHitbox);

		studiohdr_t* GetStudioModel();

		mstudiobone_t* GetBone(int nBone);
		mstudiobbox_t* GetHitBox(int nHitbox);

		mstudiohitboxset_t* GetHitBoxSet();
	};

	class CBaseViewModel : public IClientEntity
	{
	public:

		int     GetSequence();
		void	SetModelIndex(int nModelIndex);
		void	SendViewModelMatchingSequence(int Sequence);
		void	SetWeaponModel(const char* Filename, IClientEntity* Weapon);

		DWORD	GetOwner();
		DWORD	GetWeapon();

	};

	class CBaseWeaponWorldModel : public CBaseEntity
	{
	};

	enum PLAYER_TEAM
	{
		TEAM_SPEC = 1,
		TEAM_TT,
		TEAM_CT
	};
}