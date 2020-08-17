#pragma once
#include "Definitions.hpp"

#include"IClientNetworkable.hpp"
#include"IClientRenderable.hpp"
#include"IClientUnknown.hpp"
#include"IClientThinkable.hpp"

namespace SDK
{
	struct SpatializationInfo_t;

	class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
	{
	public:
		virtual void             Release(void) = 0;
		virtual const Vector&    GetAbsOrigin(void) const = 0;
		virtual const QAngle&    GetAbsAngles(void) const = 0;
		virtual void*            GetMouth(void) = 0;
		virtual bool             GetSoundSpatialization(SpatializationInfo_t info) = 0;
		virtual bool             IsBlurred(void) = 0;
		template <typename Fn = void*>
		Fn get_vfunc(void* class_base, const std::size_t index)
		{
			return (*reinterpret_cast<Fn**>(class_base))[index];
		}
		void SetModelIndex(const int index)
		{
			get_vfunc<void(__thiscall*)(IClientEntity*, int)>(this, 75)(this, index);
		}
		int& GetModelIndex();
	};

#pragma pack(push, 1)
	class CCSWeaponInfo
	{ //xSeeker
	public:
		int8_t pad0[20];
		int32_t iMaxClip1;
		int8_t pad1[12];
		int32_t iMaxReservedAmmo;
		int8_t pad2[96];
		char* szHudName;
		char* szWeaponName;
		int8_t pad3[56];
		int32_t iWeaponType;
		int8_t pad4[4];
		int32_t iWeaponPrice;
		int32_t iKillAward;
		int8_t pad5[20];
		uint8_t bFullAuto;
		int8_t pad6[3];
		int32_t iDamage;
		float_t flArmorRatio;
		int32_t iBullets;
		float_t flPenetration;
		int8_t pad7[8];
		float_t flRange;
		float_t flRangeModifier;
		int8_t pad8[16];
		uint8_t bHasSilencer;
		int8_t pad9[15];
		float_t flSpread;
		float_t flSpreadAlt;
		int8_t pad10[76];
		int32_t iRecoilSeed;
		int8_t pad11[32];
	};
#pragma pack(pop)

	class IWeaponSystem
	{
		virtual void unused0() = 0;
		virtual void unused1() = 0;
	public:
		virtual CCSWeaponInfo* GetWpnData(unsigned ItemDefinitionIndex) = 0;
	};
}