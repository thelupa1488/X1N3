#include "Entity.h"
#include "../Initialize/Offsets.h"

#define ptr( x, x1, x2 ) *(x*)( (DWORD)x1 + (DWORD)x2 )

using namespace Engine;

namespace SDK
{
	int& IClientEntity::GetModelIndex()
	{
		return *(int*)((DWORD)this + offsets[XorStr("m_nModelIndex")]);
	}

	CBaseEntity* IClientEntityList::GetClientEntityFromHandleknife(HANDLE hEnt)
	{
		typedef CBaseEntity* (__thiscall * OriginalFn)(PVOID, HANDLE);
		return GetFunction<OriginalFn>(this, 4)(this, hEnt);
	}
}

namespace Engine
{
	int CBaseEntity::GetSequenceActivity(int sequence)
	{
		studiohdr_t* hdr = I::ModelInfo()->GetStudioModel(this->GetModel());

		if (!hdr)
			return -1;

		static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(
			CSX::Memory::FindPatternV2(clientFactory, XorStr("55 8B EC 53 8B 5D 08 56 8B F1 83")));

		return GetSequenceActivity(this, hdr, sequence);
	}
	char* CBaseEntity::GetPlayerName()
	{
		if (IsPlayer())
		{
			static PlayerInfo Info;

			if (I::Engine()->GetPlayerInfo(EntIndex(), &Info))
				return Info.m_szPlayerName;
		}

		return "";
	}

	bool CBaseEntity::IsPlayer()
	{
		typedef bool(__thiscall * IsPlayerFn)(void*);
		return GetMethod<IsPlayerFn>(this, 157)(this); //156
	}

	bool CBaseEntity::m_bIsDefusing()
	{

		return *(bool*)((DWORD)this + offsets[XorStr("m_bIsDefusing")]);
	}

	Vector CBaseEntity::GetOrigin()
	{
		return *(Vector*)((DWORD)this + offsets[XorStr("m_vecOrigin")]);
	}

	bool CBaseEntity::IsValid()
	{
		if (!this)
			return false;
		else
			return (!IsDead() && GetHealth() > 0 && !IsDormant());
	}

	bool CBaseEntity::IsDead()
	{
		BYTE LifeState = *(PBYTE)((DWORD)this + offsets[XorStr("m_lifeState")]);
		return (LifeState != LIFE_ALIVE);
	}

	float CBaseEntity::GetFlashDuration()
	{
		return *(float*)((DWORD)this + offsets[XorStr("m_flFlashDuration")]);
	}

	bool CBaseEntity::IsFlashed()
	{
		return GetFlashDuration() > 0;
	}

	int CBaseEntity::GetMoney()
	{
		return *(int*)((DWORD)this + offsets[XorStr("m_iAccount")]);
	}

	bool CBaseEntity::IsVisible(CBaseEntity* pLocalEntity)
	{
		if (!pLocalEntity->IsValid())
			return false;

		Vector vSrcOrigin = pLocalEntity->GetEyePosition();

		if (vSrcOrigin.IsZero() || !vSrcOrigin.IsValid())
			return false;

		BYTE bHitBoxCheckVisible[6] = {
			HITBOX_HEAD,
			HITBOX_LOWER_CHEST,
			HITBOX_RIGHT_FOOT,
			HITBOX_LEFT_FOOT,
			HITBOX_RIGHT_HAND,
			HITBOX_LEFT_HAND,
		};

		CTraceFilter filter;

		filter.pSkip = pLocalEntity;

		for (int nHit = 0; nHit < 6; nHit++)
		{
			Vector vHitBox = GetBonePosition(bHitBoxCheckVisible[nHit]);

			if (vHitBox.IsZero() || !vHitBox.IsValid())
				continue;

			trace_t tr;
			Ray_t ray;

			ray.Init(vSrcOrigin, vHitBox);

			I::EngineTrace()->TraceRay(ray, PlayerVisibleMask, &filter, &tr);

			if (tr.m_pEnt == (IClientEntity*)this && !tr.allsolid)
				return true;
		}

		return false;
	}

	bool CBaseEntity::IsVisibleHitBox(CBaseEntity* pLocalEntity, Vector& vecAbsStart, Vector& vecAbsEnd, bool smokeCheck, bool flashcheck)
	{
		if (!I::Engine()->IsInGame())
			return false;

		CTraceFilter filter;

		filter.pSkip = pLocalEntity;

		trace_t tr;
		Ray_t ray;

		ray.Init(vecAbsStart, vecAbsEnd);

		I::EngineTrace()->TraceRay(ray, MASK_VISIBLE, &filter, &tr);

		bool visible = false;

		if (tr.m_pEnt == (IClientEntity*)this && !tr.allsolid)
			visible = true;

		if (visible && smokeCheck)
			visible = !CGlobal::LineGoesThroughSmoke(vecAbsStart, vecAbsEnd);

		return visible;
	}

	float CBaseEntity::GetC4BlowTime()
	{
		return *(float*)((uintptr_t)this + offsets[XorStr("m_flC4Blow")]);
	}

	float CBaseEntity::GetC4DefuseCountDown()
	{
		return *(float*)((uintptr_t)this + offsets[XorStr("m_flDefuseCountDown")]);
	}

	float CBaseEntity::GetLowerBodyYawTarget()
	{
		return *(float*)((uintptr_t)this + offsets[XorStr("m_flLowerBodyYawTarget")]);
	}

	Vector CBaseEntity::GetPredicted(Vector p0)
	{
		return ExtrapolateTick(p0, this->GetVelocity());
	}

	QAngle& CBaseEntity::GetVAngles()
	{
		static auto deadflag = offsets[XorStr("deadflag")];
		return *(QAngle*)((uintptr_t)this + deadflag + 0x4);
	}

	void CBaseEntity::UpdateClientSideAnimation()
	{
	//	return call_vfunc<void(__thiscall*)(void*)>(this, 223)(this);
	}

	CCSGOPlayerAnimState* CBaseEntity::GetBasePlayerAnimState()
	{
		return *(CCSGOPlayerAnimState**)((DWORD)this + 0x3900);
	}

	AnimationLayer* CBaseEntity::GetAnimOverlays()
	{
		return *reinterpret_cast<AnimationLayer**>(uintptr_t(this) + 0x2980);
	}

	AnimationLayer* CBaseEntity::GetAnimOverlay(int i)
	{
		if (i < 15)
			return &GetAnimOverlays()[i];
	}

	CUserCmd*& CBaseEntity::GetCurrentCommand() 
	{
		static auto currentCommand = *(uint32_t*)(CSX::Memory::FindPatternV2(clientFactory, XorStr("89 BE ? ? ? ? E8 ? ? ? ? 85 FF")) + 2);
		return *(CUserCmd**)((uintptr_t)this + currentCommand);
	}

	float CBaseEntity::MaxRotation(CCSGOPlayerAnimState* AnimState)
	{
		auto animstate = uintptr_t(AnimState);
		float duckamount = *(float*)(animstate + 0xA4);
		float speedfraction = Maximum<float>(0.f, Minimum<float>(*reinterpret_cast<float*>(animstate + 0xF8), 1.f));

		float unk1 = ((*reinterpret_cast<float*>(animstate + 0x11C) * -0.3f) - 0.2f)* speedfraction;
		float unk2 = unk1 + 1.f;

		if (duckamount > 0.f)
		{
			float speedfactor = Maximum<float>(0.f, Minimum<float>(1.f, *reinterpret_cast<float*>(animstate + 0xFC)));
			unk2 += ((duckamount * speedfactor) * (0.5f - unk2));
		}
		return *(float*)(animstate + 0x334) * unk2;
	}

	float CBaseEntity::GetMaxDesyncAngle()
	{
		if (!this)
			return 0.f;

		auto anim_state = this->GetBasePlayerAnimState();
		if (!anim_state)
			return 0.f;

		float duck_amount = anim_state->m_fDuckAmount;
		float speed_fraction = Minimum<float>(0, Minimum<float>(anim_state->m_flFeetSpeedForwardsOrSideWays, 1));
		float speed_factor = Maximum<float>(0, Minimum<float>(1, anim_state->m_flFeetSpeedUnknownForwardOrSideways));

		float yaw_modifier = (((anim_state->m_flStopToFullRunningFraction * -0.3f) - 0.2f) * speed_fraction) + 1.0f;

		if (duck_amount > 0.f)
			yaw_modifier += ((duck_amount * speed_factor) * (0.5f - yaw_modifier));

		return *(float*)((uintptr_t)anim_state + 0x334) * yaw_modifier;
	}

	float CBaseEntity::GetSpawnTime()
	{
		return *(float*)((uintptr_t)this + offsets[XorStr("m_flSpawnTime")]);
	}

	int CBaseEntity::GetBombDefuser()
	{
		return *(int*)((uintptr_t)this + offsets[XorStr("m_hBombDefuser")]);
	}

	int CBaseEntity::GetBombSite()
	{
		return *(int*)((uintptr_t)this + offsets[XorStr("m_nBombSite")]);
	}

	int CBaseEntity::GetMoveType()
	{
		return *(int*)((uintptr_t)this + 0x25C);
	}

	bool CBaseEntity::IsBombDefused()
	{
		return *(bool*)((uintptr_t)this + offsets[XorStr("m_bBombDefused")]);
	}

	bool CBaseEntity::GetGunGameImmunity()
	{
		return *(bool*)((uintptr_t)this + offsets[XorStr("m_bGunGameImmunity")]);
	}

	bool CBaseEntity::HasHelmet()
	{
		return *(bool*)((DWORD)this + offsets[XorStr("m_bHasHelmet")]);
	}

	bool CBaseEntity::HasDefuser()
	{
		return *(bool*)((DWORD)this + offsets[XorStr("m_bHasDefuser")]);
	}

	bool* CBaseEntity::IsSpotted()
	{
		return (bool*)((DWORD)this + offsets[XorStr("m_bSpotted")]);
	}

	int	CBaseEntity::GetFovStart()
	{
		return *(PINT)((DWORD)this + offsets[XorStr("m_iFOVStart")]);
	}

	int	CBaseEntity::GetFlags()
	{
		return *(PINT)((DWORD)this + offsets[XorStr("m_fFlags")]);
	}

	int CBaseEntity::GetOwner()
	{
		return *(PINT)((DWORD)this + offsets[XorStr("m_hOwnerEntity")]);
	}

	int CBaseEntity::GetHealth()
	{
		return *(PINT)((DWORD)this + offsets[XorStr("m_iHealth")]);
	}

	int	CBaseEntity::GetArmor()
	{
		return *(PINT)((DWORD)this + offsets[XorStr("m_ArmorValue")]);
	}

	int	CBaseEntity::GetTeam()
	{
		return *(PINT)((DWORD)this + offsets[XorStr("m_iTeamNum")]);
	}

	int CBaseEntity::GetShotsFired()
	{
		return *(PINT)((DWORD)this + (DWORD)offsets[XorStr("m_iShotsFired")]);
	}

	int CBaseEntity::GetIsScoped()
	{
		return *(PINT)((DWORD)this + (DWORD)offsets[XorStr("m_bIsScoped")]);
	}

	int CBaseEntity::GetGlowIndex()
	{
		return *(PINT)((DWORD)this + (DWORD)offsets[XorStr("m_iGlowIndex")]);
	}

	int	CBaseEntity::GetTickBase()
	{
		if (this == nullptr)
			return 0;
		return *(PINT)((DWORD)this + (DWORD)offsets[XorStr("m_nTickBase")]);
	}

	float* CBaseEntity::GetFlashMaxAlpha()
	{
		return (float*)((DWORD)this + (DWORD)offsets[XorStr("m_flFlashMaxAlpha")]);
	}

	ObserverMode_t CBaseEntity::GetObserverMode()
	{
		return *(ObserverMode_t*)((DWORD)this + (DWORD)offsets[XorStr("m_iObserverMode")]);
	}

	PVOID CBaseEntity::GetObserverTarget()
	{
		return (PVOID) * (PDWORD)((DWORD)this + (DWORD)offsets[XorStr("m_hObserverTarget")]);
	}

	PVOID CBaseEntity::GetActiveWeapon()
	{
		if (!this)
			return nullptr;

		return (PVOID)((DWORD)this + (DWORD)offsets[XorStr("m_hActiveWeapon")]);
	}

	CBaseWeapon* CBaseEntity::GetBaseWeapon()
	{
		if (!GetActiveWeapon() || !I::EntityList())
			return nullptr;

		return (CBaseWeapon*)I::EntityList()->GetClientEntityFromHandle((PVOID) * (PDWORD)GetActiveWeapon());
	}

	UINT* CBaseEntity::GetWeapons()
	{
		return (UINT*)((DWORD)this + offsets[XorStr("m_hMyWeapons")]);
	}

	CBaseHandle* CBaseEntity::m_hMyWeapons()
	{
		return (CBaseHandle*)((uintptr_t)this + 0x2DF8);
	}

	UINT* CBaseEntity::GetWearables()
	{
		return (UINT*)((DWORD)this + offsets[XorStr("m_hMyWearables")]);
	}

	CBaseViewModel* CBaseEntity::GetViewModel()
	{
		return (CBaseViewModel*)I::EntityList()->GetClientEntityFromHandle((PVOID) * (PDWORD)((DWORD)this + offsets[XorStr("m_hViewModel")]));
	}

	Vector CBaseEntity::GetAimPunchAngle()
	{
		return *(Vector*)((DWORD)this + offsets[XorStr("m_aimPunchAngle")]);
	}

	float CBaseEntity::GetSimTime()
	{
		return *(float*)((DWORD)this + offsets[XorStr("m_flSimulationTime")]);
	}

	Vector CBaseEntity::GetViewPunchAngle()
	{
		return *(Vector*)((DWORD)this + offsets[XorStr("m_viewPunchAngle")]);
	}

	Vector CBaseEntity::GetVelocity()
	{
		return *(Vector*)((DWORD)this + offsets[XorStr("m_vecVelocity")]);
	}

	Vector CBaseEntity::GetViewOffset()
	{
		if (this == (CBaseEntity*)0xA)
			return Vector(0, 0, 0);

		if (this == (CBaseEntity*)0xE)
			return Vector(0, 0, 0);

		return *(Vector*)((DWORD)this + offsets[XorStr("m_vecViewOffset")]);
	}

	Vector CBaseEntity::GetEyePosition()
	{
		//if (this == (CBaseEntity*)0xA)
		//	return Vector(0, 0, 0);

		//if (this == (CBaseEntity*)0xE)
		//	return Vector(0, 0, 0);

		//if (IsBadReadPtr(this, sizeof(Vector)))
		//	return Vector(0, 0, 0);

		//return GetRenderOrigin() + GetViewOffset();
		return GetOrigin() + GetViewOffset();
	}

	Vector CBaseEntity::GetPunchAngles()
	{
		if (!this)
			return Vector(0, 0, 0);

		if (IsBadReadPtr(this, sizeof(CBaseEntity*)))
			return Vector(0, 0, 0);

		return *(Vector*)((DWORD)this + offsets[XorStr("m_vecPunchAngles")]);
	}

	QAngle CBaseEntity::GetEyeAngles()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + offsets[XorStr("m_angEyeAngles")]);
	}

	Vector CBaseEntity::GetBonePosition(int nBone)
	{
		Vector vRet;
		matrix3x4_t MatrixArray[MAXSTUDIOBONES];

		if (!SetupBones(MatrixArray, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, I::GlobalVars()->curtime))
			return vRet;

		matrix3x4_t HitboxMatrix = MatrixArray[nBone];

		vRet = Vector(HitboxMatrix[0][3], HitboxMatrix[1][3], HitboxMatrix[2][3]);

		return vRet;
	}

	studiohdr_t* CBaseEntity::GetStudioModel()
	{
		const model_t* model = nullptr;

		if (!this->IsValid())
			return nullptr;


		model = GetModel();

		if (!model)
			return nullptr;

		if (IsBadReadPtr(model, sizeof(model_t*)))
			return nullptr;


		studiohdr_t* pStudioModel = I::ModelInfo()->GetStudioModel(model);

		if (!pStudioModel)
			return nullptr;

		return pStudioModel;
	}

	mstudiobone_t* CBaseEntity::GetBone(int nBone)
	{
		mstudiobone_t* pBoneBox = nullptr;

		studiohdr_t* pStudioModel = GetStudioModel();

		if (!pStudioModel)
			return pBoneBox;

		mstudiobone_t* pBone = pStudioModel->pBone(nBone);

		if (!pBone)
			return nullptr;

		return pBone;
	}

	mstudiobbox_t* CBaseEntity::GetHitBox(int nHitbox)
	{
		if (nHitbox < 0 || nHitbox >= 19)
			return nullptr;

		mstudiohitboxset_t* pHitboxSet = nullptr;
		mstudiobbox_t* pHitboxBox = nullptr;

		pHitboxSet = GetHitBoxSet();

		if (!pHitboxSet)
			return pHitboxBox;

		pHitboxBox = pHitboxSet->pHitbox(nHitbox);

		if (!pHitboxBox)
			return nullptr;

		return pHitboxBox;
	}

	mstudiohitboxset_t* CBaseEntity::GetHitBoxSet()
	{
		studiohdr_t* pStudioModel = nullptr;
		mstudiohitboxset_t* pHitboxSet = nullptr;

		pStudioModel = GetStudioModel();

		if (!pStudioModel)
			return pHitboxSet;

		pHitboxSet = pStudioModel->pHitboxSet(0);

		if (!pHitboxSet)
			return nullptr;

		return pHitboxSet;
	}

	Vector CBaseEntity::GetHitboxPosition(int nHitbox)
	{
		matrix3x4_t MatrixArray[MAXSTUDIOBONES];
		Vector vRet, vMin, vMax;

		vRet = Vector(0, 0, 0);

		mstudiobbox_t* pHitboxBox = GetHitBox(nHitbox);

		if (!pHitboxBox || !IsValid())
			return vRet;

		if (!SetupBones(MatrixArray, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
			return vRet;

		if (!pHitboxBox->m_Bone || !pHitboxBox->m_vBbmin.IsValid() || !pHitboxBox->m_vBbmax.IsValid())
			return vRet;

		VectorTransform(pHitboxBox->m_vBbmin, MatrixArray[pHitboxBox->m_Bone], vMin);
		VectorTransform(pHitboxBox->m_vBbmax, MatrixArray[pHitboxBox->m_Bone], vMax);

		vRet = (vMin + vMax) * 0.5f;

		return vRet;
	}

	void CBaseViewModel::SetModelIndex(int nModelIndex)
	{
		VirtualFn(void)(PVOID, int);
		GetMethod< OriginalFn >(this, 75)(this, nModelIndex);
	}

	int CBaseViewModel::GetSequence()
	{
		return *(int*)((DWORD)this + offsets[XorStr("m_nSequence")]);
	}

	void CBaseViewModel::SendViewModelMatchingSequence(int Sequence)
	{
		VirtualFn(void)(PVOID, int);
		GetMethod<OriginalFn>(this, 246)(this, Sequence);
	}

	void CBaseViewModel::SetWeaponModel(const char* Filename, IClientEntity* Weapon)
	{
		typedef void(__thiscall * SetWeaponModelFn)(void*, const char*, IClientEntity*);
		return GetMethod<SetWeaponModelFn>(this, 247)(this, Filename, Weapon);
	}

	DWORD CBaseViewModel::GetOwner()
	{
		return *(PDWORD)((DWORD)this + offsets[XorStr("m_hOwner")]);
	}

	DWORD CBaseViewModel::GetWeapon()
	{
		return *(PDWORD)((DWORD)this + offsets[XorStr("m_hWeapon")]);
	}

	template <class T>
	static T GetFunction(void* instance, int index)
	{
		const auto vtable = *static_cast<void***>(instance);
		return reinterpret_cast<T>(vtable[index]);
	}
}