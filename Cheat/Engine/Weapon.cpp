#include "Weapon.h"
#include  "../Initialize/Offsets.h"
namespace Engine
{
	int CBaseWeapon::GetWeaponAmmo()
	{
		return ptr(*(PINT), this, offsets["m_iClip1"]);
	}

	float CBaseWeapon::GetInaccuracy()
	{
		typedef float(__thiscall* OriginalFn)(void*);
		return GetVFunc<OriginalFn>(this, 482)(this);
	}

	HANDLE* CBaseWeapon::GetWeaponWorldModel()
	{
		return ptr((HANDLE*), this, offsets["m_hWeaponWorldModel"]);
	}

	int* CBaseWeapon::ModelIndex()
	{
		return ptr((int*), this, offsets["m_nModelIndex"]);
	}

	int* CBaseWeapon::ViewModelIndex()
	{
		return ptr((int*), this, offsets["m_iViewModelIndex"]);
	}

	int* CBaseWeapon::fixItemIDHigh()
	{
		return ptr((int*), this, offsets["m_iItemIDHigh"]);
	}

	short* CBaseWeapon::fixskins()
	{
		return ptr((short*), this, offsets["m_iItemDefinitionIndex"]);
	}

	int* CBaseWeapon::GetEntityQuality()
	{
		return ptr((int*), this, offsets["m_iEntityQuality"]);
	}

	int* CBaseWeapon::OwnerXuidLow()
	{
		return ptr((int*), this, offsets["m_OriginalOwnerXuidLow"]);
	}

	int* CBaseWeapon::OwnerXuidHigh()
	{
		return ptr((int*), this, offsets["m_OriginalOwnerXuidHigh"]);
	}

	int CBaseWeapon::GetWeaponAmmoClp2()
	{
		return ptr(*(PINT), this, offsets["m_iClip2"]);
	}

	bool CBaseWeapon::IsReloading()
	{
		static auto inReload = *reinterpret_cast<uint32_t*>(offsets["IsReloading"]);
		return *reinterpret_cast<bool*>(DWORD(this) + inReload);
	}

	bool CBaseWeapon::CanFire()
	{
		static decltype(this) stored_weapon = nullptr;
		static auto stored_tick = 0;
		if (stored_weapon != this || stored_tick >= CGlobal::LocalPlayer->GetTickBase()) {
			stored_weapon = this;
			stored_tick = CGlobal::LocalPlayer->GetTickBase();
			return false; //cannot shoot first tick after switch
		}

		if (GetWeaponAmmo() <= 0 || !CGlobal::LocalPlayer)
			return false;

		auto flServerTime = CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick;

		return GetNextPrimaryAttack() <= flServerTime;
	}

	int	CBaseWeapon::GetZoomLevel()
	{
		if (!this)
			return 0;

		return ptr(*(PINT), this, offsets["m_zoomLevel"]);
	}

	bool CBaseWeapon::GetWeaponReload()
	{
		return ptr(*(bool*), this, offsets["m_bCanReload"]);
	}

	float CBaseWeapon::GetNextPrimaryAttack()
	{
		return ptr(*(float*), this, offsets["m_flNextPrimaryAttack"]);
	}

	bool CBaseWeapon::GetPinPulled()
	{
		return ptr(*(bool*), this, offsets["m_bPinPulled"]);
	}

	float CBaseWeapon::GetThrowTime()
	{
		return ptr(*(float*), this, offsets["m_fThrowTime"]);
	}

	CCSWeaponInfo* CBaseWeapon::GetWeaponInfo()
	{
		typedef CCSWeaponInfo*(__thiscall* GetWeaponDataFn)(void*);
		return GetMethod< GetWeaponDataFn >(this, 460)(this);
	}

	CBaseAttributableItem* CBaseWeapon::GeteAttributableItem()
	{
		return ptr((CBaseAttributableItem*), this, 0);
	}

	const char*	CBaseWeapon::GetName()
	{
		typedef const char* (__thiscall* GetNameFn)(void*);
		return GetMethod<GetNameFn>(this, 386)(this);
	}

	const char*	CBaseWeapon::GetPrintName()
	{
		typedef const char* (__thiscall* GetPrintNameFn)(void*);
		return GetMethod<GetPrintNameFn>(this, 379)(this);
	}

	short* CBaseAttributableItem::GetItemDefinitionIndex()
	{
		return ptr((short*), this, offsets["m_iItemDefinitionIndex"]);
	}

	int* CBaseAttributableItem::GetIndex()
	{
		return ptr((int*), this, offsets["m_bIsAutoaimTarget"]);
	}

	int* CBaseAttributableItem::ModelIndex()
	{
		return ptr((int*), this, offsets["m_nModelIndex"]);
	}
	int* CBaseAttributableItem::ViewModelIndex()
	{
		return ptr((int*), this, offsets["m_iViewModelIndex"]);
	}

	int* CBaseAttributableItem::GetItemIDHigh()
	{
		return ptr((int*), this, offsets["m_iItemIDHigh"]);
	}

	int* CBaseAttributableItem::GetAccountID()
	{
		return ptr((int*), this, offsets["m_iAccountID"]);
	}

	int* CBaseAttributableItem::GetEntityQuality()
	{
		return ptr((int*), this, offsets["m_iEntityQuality"]);
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidLow()
	{
		return ptr((int*), this, offsets["m_OriginalOwnerXuidLow"]);
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidHigh()
	{
		return ptr((int*), this, offsets["m_OriginalOwnerXuidHigh"]);
	}

	int* CBaseAttributableItem::GetFallbackPaintKit()
	{
		return ptr((int*), this, offsets["m_nFallbackPaintKit"]);
	}

	float* CBaseAttributableItem::GetFallbackWear()
	{
		return ptr((float*), this, offsets["m_flFallbackWear"]);
	}

	int* CBaseAttributableItem::GetFallbackSeed()
	{
		return ptr((int*), this, offsets["m_nFallbackSeed"]);
	}

	int* CBaseAttributableItem::GetFallbackStatTrak()
	{
		return ptr((int*), this, offsets["m_nFallbackStatTrak"]);
	}

	char* CBaseAttributableItem::GetCustomName() 
	{
		return ptr(reinterpret_cast<char*>, this, offsets["m_szCustomName"]);
	}
}     