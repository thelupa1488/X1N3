#include "Entity.h"
#include "../Initialize/Offsets.h"

#define ptr( x, x1, x2 ) *(x*)( (DWORD)x1 + (DWORD)x2 )

using namespace Engine;

namespace SDK
{
	int& IClientEntity::GetModelIndex()
	{
		return *(int*)((DWORD)this + offsets["m_nModelIndex"]);
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
				return Info.szName;
		}

		return "";
	}

	bool CBaseEntity::IsPlayer()
	{
		typedef bool(__thiscall * IsPlayerFn)(void*);
		return GetMethod<IsPlayerFn>(this, 157)(this); //156
	}

	bool CBaseEntity::IsWeapon()
	{
		//index: 160
		//ref: "CNewParticleEffect::DrawModel"
		//sig: 8B 80 ? ? ? ? FF D0 84 C0 74 6F 8B 4D A4
		return GetMethod<bool(__thiscall*)(CBaseEntity*)>(this, 165)(this);
	}

	bool CBaseEntity::IsDefusing()
	{

		return *(bool*)((DWORD)this + offsets["m_bIsDefusing"]);
	}

	Vector CBaseEntity::GetOrigin()
	{
		return *(Vector*)((DWORD)this + offsets["m_vecOrigin"]);
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
		BYTE LifeState = *(PBYTE)((DWORD)this + offsets["m_lifeState"]);
		return (LifeState != LIFE_ALIVE);
	}

	float CBaseEntity::GetFlashDuration()
	{
		return *(float*)((DWORD)this + offsets["m_flFlashDuration"]);
	}

	bool CBaseEntity::IsFlashed()
	{
		return GetFlashDuration() > 0;
	}

	int CBaseEntity::GetMoney()
	{
		return *(int*)((DWORD)this + offsets["m_iAccount"]);
	}

	bool CBaseEntity::IsVisible(CBaseEntity* pLocalEntity)
	{
		if (!pLocalEntity->IsValid())
			return false;

		Vector vSrcOrigin = pLocalEntity->GetEyePosition();

		if (vSrcOrigin.IsZero() || !vSrcOrigin.IsValid())
			return false;

		BYTE bHitBoxCheckVisible[6] = 
		{
			HITBOX_HEAD,
			HITBOX_LOWER_CHEST,
			HITBOX_RIGHT_FOOT,
			HITBOX_LEFT_FOOT,
			HITBOX_RIGHT_HAND,
			HITBOX_LEFT_HAND
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

			if (tr.hit_entity == (IClientEntity*)this && !tr.allsolid)
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

		if (tr.hit_entity == (IClientEntity*)this && !tr.allsolid)
			visible = true;

		if (visible && smokeCheck)
			visible = !CGlobal::LineGoesThroughSmoke(vecAbsStart, vecAbsEnd);

		return visible;
	}

	float CBaseEntity::GetC4BlowTime()
	{
		return *(float*)((uintptr_t)this + offsets["m_flC4Blow"]);
	}

	float CBaseEntity::GetC4DefuseCountDown()
	{
		return *(float*)((uintptr_t)this + offsets["m_flDefuseCountDown"]);
	}

	float CBaseEntity::GetLowerBodyYawTarget()
	{
		return *(float*)((uintptr_t)this + offsets["m_flLowerBodyYawTarget"]);
	}

	Vector CBaseEntity::GetPredicted(Vector p0)
	{
		return ExtrapolateTick(p0, this->GetVelocity());
	}

	QAngle& CBaseEntity::GetVAngles()
	{
		static auto deadflag = offsets["deadflag"];
		return *(QAngle*)((uintptr_t)this + deadflag + 0x4);
	}

	void CBaseEntity::UpdateClientSideAnimation()
	{
		return GetMethod<void(__thiscall*)(void*)>(this, 223)(this);
	}

	CCSGOPlayerAnimState* CBaseEntity::GetBasePlayerAnimState()
	{
		return *(CCSGOPlayerAnimState**)((DWORD)this + 0x3914);
	}

	AnimationLayer* CBaseEntity::GetAnimOverlays()
	{
		return *reinterpret_cast<AnimationLayer**>(uintptr_t(this) + 0x2990);
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

	float CBaseEntity::GetSpawnTime()
	{
		return *(float*)((uintptr_t)this + offsets["m_flSpawnTime"]);
	}

	int CBaseEntity::GetBombDefuser()
	{
		return *(int*)((uintptr_t)this + offsets["m_hBombDefuser"]);
	}

	int CBaseEntity::GetBombSite()
	{
		return *(int*)((uintptr_t)this + offsets["m_nBombSite"]);
	}

	int CBaseEntity::GetMoveType()
	{
		return *(int*)((uintptr_t)this + 0x25C);
	}

	bool CBaseEntity::IsBombDefused()
	{
		return *(bool*)((uintptr_t)this + offsets["m_bBombDefused"]);
	}

	bool CBaseEntity::GetGunGameImmunity()
	{
		return *(bool*)((uintptr_t)this + offsets["m_bGunGameImmunity"]);
	}

	bool CBaseEntity::HasHelmet()
	{
		return *(bool*)((DWORD)this + offsets["m_bHasHelmet"]);
	}

	bool CBaseEntity::HasDefuser()
	{
		return *(bool*)((DWORD)this + offsets["m_bHasDefuser"]);
	}

	bool* CBaseEntity::IsSpotted()
	{
		return (bool*)((DWORD)this + offsets["m_bSpotted"]);
	}

	int	CBaseEntity::GetFovStart()
	{
		return *(PINT)((DWORD)this + offsets["m_iFOVStart"]);
	}

	int	CBaseEntity::GetFlags()
	{
		return *(PINT)((DWORD)this + offsets["m_fFlags"]);
	}

	int CBaseEntity::GetOwner()
	{
		return *(PINT)((DWORD)this + offsets["m_hOwnerEntity"]);
	}

	int CBaseEntity::GetHealth()
	{
		return *(PINT)((DWORD)this + offsets["m_iHealth"]);
	}

	int	CBaseEntity::GetArmor()
	{
		return *(PINT)((DWORD)this + offsets["m_ArmorValue"]);
	}

	int	CBaseEntity::GetTeam()
	{
		return *(PINT)((DWORD)this + offsets["m_iTeamNum"]);
	}

	int CBaseEntity::GetShotsFired()
	{
		return *(PINT)((DWORD)this + (DWORD)offsets["m_iShotsFired"]);
	}

	int CBaseEntity::GetIsScoped()
	{
		return *(PINT)((DWORD)this + (DWORD)offsets["m_bIsScoped"]);
	}

	int CBaseEntity::GetGlowIndex()
	{
		return *(PINT)((DWORD)this + (DWORD)offsets["m_iGlowIndex"]);
	}

	int	CBaseEntity::GetTickBase()
	{
		if (this == nullptr)
			return 0;
		return *(PINT)((DWORD)this + (DWORD)offsets["m_nTickBase"]);
	}

	float* CBaseEntity::GetFlashMaxAlpha()
	{
		return (float*)((DWORD)this + (DWORD)offsets["m_flFlashMaxAlpha"]);
	}

	ObserverMode_t CBaseEntity::GetObserverMode()
	{
		return *(ObserverMode_t*)((DWORD)this + (DWORD)offsets["m_iObserverMode"]);
	}

	PVOID CBaseEntity::GetObserverTarget()
	{
		return (PVOID) * (PDWORD)((DWORD)this + (DWORD)offsets["m_hObserverTarget"]);
	}

	PVOID CBaseEntity::GetActiveWeapon()
	{
		if (!this)
			return nullptr;

		return (PVOID)((DWORD)this + (DWORD)offsets["m_hActiveWeapon"]);
	}

	CBaseWeapon* CBaseEntity::GetBaseWeapon()
	{
		if (!GetActiveWeapon() || !I::EntityList())
			return nullptr;

		return (CBaseWeapon*)I::EntityList()->GetClientEntityFromHandle((PVOID) * (PDWORD)GetActiveWeapon());
	}

	UINT* CBaseEntity::GetWeapons()
	{
		return (UINT*)((DWORD)this + offsets["m_hMyWeapons"]);
	}

	CBaseHandle* CBaseEntity::m_hMyWeapons()
	{
		return (CBaseHandle*)((uintptr_t)this + 0x2DF8);
	}

	UINT* CBaseEntity::GetWearables()
	{
		return (UINT*)((DWORD)this + offsets["m_hMyWearables"]);
	}

	CBaseViewModel* CBaseEntity::GetViewModel()
	{
		return (CBaseViewModel*)I::EntityList()->GetClientEntityFromHandle((PVOID) * (PDWORD)((DWORD)this + offsets["m_hViewModel"]));
	}

	Vector CBaseEntity::GetAimPunchAngle()
	{
		return *(Vector*)((DWORD)this + offsets["m_aimPunchAngle"]);
	}

	float CBaseEntity::GetSimTime()
	{
		return *(float*)((DWORD)this + offsets["m_flSimulationTime"]);
	}

	float CBaseEntity::GetDuckAmount()
	{
		return *(float*)((DWORD)this + offsets["m_flDuckAmount"]);
	}

	Vector CBaseEntity::GetViewPunchAngle()
	{
		return *(Vector*)((DWORD)this + offsets["m_viewPunchAngle"]);
	}

	Vector CBaseEntity::GetVelocity()
	{
		return *(Vector*)((DWORD)this + offsets["m_vecVelocity"]);
	}

	Vector CBaseEntity::GetViewOffset()
	{
		if (this == (CBaseEntity*)0xA)
			return Vector(0, 0, 0);

		if (this == (CBaseEntity*)0xE)
			return Vector(0, 0, 0);

		return *(Vector*)((DWORD)this + offsets["m_vecViewOffset"]);
	}

	Vector CBaseEntity::GetEyePosition()
	{
		return GetRenderOrigin() + GetViewOffset();
	}

	Vector CBaseEntity::GetPunchAngles()
	{
		if (!this)
			return Vector(0, 0, 0);

		return *(Vector*)((DWORD)this + offsets["m_vecPunchAngles"]);
	}

	QAngle CBaseEntity::GetEyeAngles()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + offsets["m_angEyeAngles"]);
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

		mstudiobone_t* pBone = pStudioModel->GetBone(nBone);

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

		pHitboxBox = pHitboxSet->GetHitbox(nHitbox);

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

		pHitboxSet = pStudioModel->GetHitboxSet(0);

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

		if (!pHitboxBox->bone || !pHitboxBox->bbmin.IsValid() || !pHitboxBox->bbmax.IsValid())
			return vRet;

		VectorTransform(pHitboxBox->bbmin, MatrixArray[pHitboxBox->bone], vMin);
		VectorTransform(pHitboxBox->bbmax, MatrixArray[pHitboxBox->bone], vMax);

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
		return *(int*)((DWORD)this + offsets["m_nSequence"]);
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
		return *(PDWORD)((DWORD)this + offsets["m_hOwner"]);
	}

	DWORD CBaseViewModel::GetWeapon()
	{
		return *(PDWORD)((DWORD)this + offsets["m_hWeapon"]);
	}

	template <class T>
	static T GetFunction(void* instance, int index)
	{
		const auto vtable = *static_cast<void***>(instance);
		return reinterpret_cast<T>(vtable[index]);
	}
}