#pragma once
#include "SDK.h"

namespace Engine
{
	class CBaseEntity;
}
using namespace Engine;

namespace SDK 
{
	class IMoveHelper
	{
	private:
		virtual void unknown() = 0;
	public:
		virtual void SetHost(CBaseEntity* host) = 0;
	private:
		virtual void unknown1() = 0;
		virtual void unknown2() = 0;
	public:
		virtual bool unknown_func() = 0;
	};

	class CMoveData
	{
	public:
		bool    m_bFirstRunOfFunctions : 1;
		bool    m_bGameCodeMovedPlayer : 1;
		int     m_nPlayerHandle;        // edict index on server, client entity handle on client=
		int     m_nImpulseCommand;      // Impulse command issued.
		QAngle  m_vecViewAngles;        // Command view angles (local space)
		Vector  m_vecAbsViewAngles;     // Command view angles (world space)
		int     m_nButtons;             // Attack buttons.
		int     m_nOldButtons;          // From host_client->oldbuttons;
		float   m_flForwardMove;
		float   m_flSideMove;
		float   m_flUpMove;
		float   m_flMaxSpeed;
		float   m_flClientMaxSpeed;
		Vector  m_vecVelocity;          // edict::velocity        // Current movement direction.
		QAngle  m_vecAngles;            // edict::angles
		Vector  m_vecOldAngles;
		float   m_outStepHeight;        // how much you climbed this move
		Vector  m_outWishVel;           // This is where you tried 
		Vector  m_outJumpVel;           // This is your jump velocity
		Vector  m_vecConstraintCenter;
		float   m_flConstraintRadius;
		float   m_flConstraintWidth;
		float   m_flConstraintSpeedFactor;
		float   m_flUnknown[5];
		Vector  m_vecAbsOrigin;
	};

	class IGameMovement
	{
	public:
		virtual			~IGameMovement(void) {}

		virtual void	            ProcessMovement(CBaseEntity* pPlayer, CMoveData* pMove) = 0;
		virtual void	            Reset(void) = 0;
		virtual void	            StartTrackPredictionErrors(CBaseEntity* pPlayer) = 0;
		virtual void	            FinishTrackPredictionErrors(CBaseEntity* pPlayer) = 0;
		virtual void	            DiffPrint(char const* fmt, ...) = 0;
		virtual Vector const&       GetPlayerMins(bool ducked) const = 0;
		virtual Vector const&       GetPlayerMaxs(bool ducked) const = 0;
		virtual Vector const&       GetPlayerViewOffset(bool ducked) const = 0;
		virtual bool		        IsMovingPlayerStuck(void) const = 0;
		virtual CBaseEntity*        GetMovingPlayer(void) const = 0;
		virtual void		        UnblockPusher(CBaseEntity* pPlayer, CBaseEntity* pPusher) = 0;
		virtual void                SetupMovementBounds(CMoveData* pMove) = 0;
	};

	class CGameMovement : public IGameMovement
	{
	public:
		virtual ~CGameMovement(void) {}
	};

	class IPrediction
	{
	public:
		void SetLocalViewangles(Vector& angle)
		{
			using original_fn = void(__thiscall*)(void*, Vector&);
			GetMethod<original_fn>(this, 13)(this, angle);
		}

		bool InPrediction()
		{
			typedef bool(__thiscall* oInPrediction)(void*);
			return GetMethod<oInPrediction>(this, 14)(this);
		}

		void RunCommand(CBaseEntity* player, CUserCmd* pCmd, IMoveHelper* moveHelper)
		{
			typedef void(__thiscall* oRunCommand)(void*, CBaseEntity*, CUserCmd*, IMoveHelper*);
			return GetMethod<oRunCommand>(this, 19)(this, player, pCmd, moveHelper);
		}

		void SetupMove(CBaseEntity* player, CUserCmd* pCmd, IMoveHelper* moveHelper, void* pMoveData)
		{
			typedef void(__thiscall* oSetupMove)(void*, CBaseEntity*, CUserCmd*, IMoveHelper*, void*);
			return GetMethod<oSetupMove>(this, 20)(this, player, pCmd, moveHelper, pMoveData);
		}

		void FinishMove(CBaseEntity* player, CUserCmd* pCmd, void* pMoveData)
		{
			typedef void(__thiscall* oFinishMove)(void*, CBaseEntity*, CUserCmd*, void*);
			return GetMethod<oFinishMove>(this, 21)(this, player, pCmd, pMoveData);
		}
	};
}