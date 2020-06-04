#include "Weapon.h"
#include  "../Initialize/Offsets.h"
namespace Engine
{
	int CBaseWeapon::GetWeaponAmmo()
	{
		return *(PINT)((DWORD)this + offsets["m_iClip1"]);
	}

	float CBaseWeapon::GetInaccuracy()
	{
		typedef float(__thiscall* OriginalFn)(void*);
		return GetVFunc<OriginalFn>(this, 482)(this); //481
	}

	HANDLE* CBaseWeapon::GetWeaponWorldModel()
	{
		return (HANDLE*)((DWORD)this + offsets["m_hWeaponWorldModel"]);
	}

	int* CBaseWeapon::ModelIndex()
	{
		return (int*)((uintptr_t)this + offsets["m_nModelIndex"]);
	}

	int* CBaseWeapon::ViewModelIndex()
	{
		return (int*)((uintptr_t)this + offsets["m_iViewModelIndex"]);
	}

	int* CBaseWeapon::fixItemIDHigh()
	{
		return (int*)((uintptr_t)this + offsets["m_iItemIDHigh"]);
	}

	short* CBaseWeapon::fixskins()
	{
		return (short*)((uintptr_t)this + offsets["m_iItemDefinitionIndex"]);
	}

	int* CBaseWeapon::GetEntityQuality()
	{
		return (int*)((uintptr_t)this + offsets["m_iEntityQuality"]);
	}

	int* CBaseWeapon::OwnerXuidLow()
	{
		return (int*)((uintptr_t)this + offsets["m_OriginalOwnerXuidLow"]);
	}

	int* CBaseWeapon::OwnerXuidHigh()
	{
		return (int*)((uintptr_t)this + offsets["m_OriginalOwnerXuidHigh"]);
	}

	int CBaseWeapon::GetWeaponAmmoClp2()
	{
		return *(PINT)((DWORD)this + offsets["m_iClip2"]);
	}

	bool CBaseWeapon::IsReloading()
	{
		static auto inReload = *reinterpret_cast<uint32_t*>(
			CSX::Memory::FindPatternV2(XorStr("client.dll"), XorStr("C6 87 ? ? ? ? ? 8B 06 8B CE FF 90")));
		return *reinterpret_cast<bool*>(uintptr_t(this) + inReload);
	}

	bool CBaseWeapon::CanFire()
	{
		if (!CGlobal::LocalPlayer)
			return false;

		static auto stored_tick = 0;
		static decltype(this) stored_weapon = nullptr;
		if (stored_weapon != this || stored_tick >= CGlobal::LocalPlayer->GetTickBase())
		{
			stored_weapon = this;
			stored_tick = CGlobal::LocalPlayer->GetTickBase();

			return false;
		}

		if (IsReloading() || GetWeaponAmmo() <= 0 || !CGlobal::LocalPlayer)
			return false;

		auto flServerTime = CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick;

		return GetNextPrimaryAttack() <= flServerTime;
	}

	int	CBaseWeapon::GetZoomLevel()
	{
		if (!this)
			return 0;

		if (IsBadReadPtr(this, sizeof(CBaseWeapon)))
			return 0;


		return *(PINT)((DWORD)this + offsets["m_zoomLevel"]);
	}

	bool CBaseWeapon::GetWeaponReload()
	{
		return *(bool*)((DWORD)this + offsets["m_bCanReload"]);
	}

	float CBaseWeapon::GetNextPrimaryAttack()
	{
		return *(float*)((DWORD)this + offsets["m_flNextPrimaryAttack"]);
	}

	bool CBaseWeapon::GetPinPulled()
	{
		return *(bool*)((DWORD)this + offsets["m_bPinPulled"]);
	}

	float CBaseWeapon::GetThrowTime()
	{
		return *(float*)((DWORD)this + offsets["m_fThrowTime"]);
	}

	CWeaponInfo* CBaseWeapon::GetWeaponInfo()
	{
		typedef CWeaponInfo*(__thiscall* GetWeaponDataFn)(void*);
		return GetMethod< GetWeaponDataFn >(this, 460)(this);  //459
	}

	CBaseAttributableItem* CBaseWeapon::GeteAttributableItem()
	{
		return (CBaseAttributableItem*)(DWORD)this;
	}

	const char*	CBaseWeapon::GetName()
	{
		if (IsBadReadPtr(this, sizeof(CBaseWeapon)))
			return "";

		typedef const char* (__thiscall* GetNameFn)(void*);
		return GetMethod<GetNameFn>(this, 386)(this); //385
	}

	const char*	CBaseWeapon::GetPrintName()
	{
		typedef const char* (__thiscall* GetPrintNameFn)(void*);
		return GetMethod<GetPrintNameFn>(this, 379)(this);
	}

	short* CBaseAttributableItem::GetItemDefinitionIndex()
	{
		return (short*)((DWORD)this + offsets["m_iItemDefinitionIndex"]);
	}

	int* CBaseAttributableItem::GetIndex()
	{
		return (int*)((DWORD)this + offsets["m_bIsAutoaimTarget"]);
	}

	int* CBaseAttributableItem::ModelIndex()
	{
		return (int*)((uintptr_t)this + offsets["m_nModelIndex"]);
	}
	int* CBaseAttributableItem::ViewModelIndex()
	{
		return (int*)((uintptr_t)this + offsets["m_iViewModelIndex"]);
	}

	int* CBaseAttributableItem::GetItemIDHigh()
	{
		return (int*)((DWORD)this + offsets["m_iItemIDHigh"]);
	}

	int* CBaseAttributableItem::GetAccountID()
	{
		return (int*)((DWORD)this + offsets["m_iAccountID"]);
	}

	int* CBaseAttributableItem::GetEntityQuality()
	{
		return (int*)((DWORD)this + offsets["m_iEntityQuality"]);
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidLow()
	{
		return (int*)((DWORD)this + offsets["m_OriginalOwnerXuidLow"]);
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidHigh()
	{
		return (int*)((DWORD)this + offsets["m_OriginalOwnerXuidHigh"]);
	}

	int* CBaseAttributableItem::GetFallbackPaintKit()
	{
		return (int*)((DWORD)this + offsets["m_nFallbackPaintKit"]);
	}

	float* CBaseAttributableItem::GetFallbackWear()
	{
		return (float*)((DWORD)this + offsets["m_flFallbackWear"]);
	}

	int* CBaseAttributableItem::GetFallbackSeed()
	{
		return (int*)((DWORD)this + offsets["m_nFallbackSeed"]);
	}

	int* CBaseAttributableItem::GetFallbackStatTrak()
	{
		return (int*)((DWORD)this + offsets["m_nFallbackStatTrak"]);
	}

	char* CBaseAttributableItem::GetCustomName() {
		return reinterpret_cast<char*>(uintptr_t(this) + offsets["m_szCustomName"]);
	}

	CBaseViewModel* CBaseAttributableItem::GetViewModel()
	{
		return (CBaseViewModel*)(DWORD)this;
	}
}     