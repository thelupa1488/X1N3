#pragma once
#include "SDK.h"

namespace SDK
{
	struct CEconItemDefinition
	{
		char pad_0000[0x8]; //0x0000
		int32_t m_iItemDefinitionIndex; //0x0008
		char pad_000C[0x40]; //0x000C
		char* m_szHudName; //0x004C
		char pad_0050[0x4]; //0x0050
		char* m_szWeaponType; //0x0054
		char pad_0058[0x4]; //0x0058
		char* m_szWeaponDescription; //0x005C
		char pad_0060[0xC]; //0x0060
		char* m_szViewModel; //0x006C
		char pad_0070[0x2C]; //0x0070
		char* m_szWorldModel; //0x009C
		char* m_szWorldModelDropped; //0x00A0
		char pad_00A4[0x10C]; //0x00A4
		char* m_szWeaponName1; //0x01B0
		char pad_01B4[0x8]; //0x01B4
		char* m_szWeaponName; //0x01BC
		char pad_01C0[0xA80]; //0x01C0
	}; //Size: 0x0C40

	struct CCStrike15ItemSchema
	{
		int GetItemDefinitionCount()
		{
			return GetMethod<int(__thiscall*)(void*)>(this, 3)(this);
		}

		CEconItemDefinition* GetItemDefinitionByName(const char* name)
		{
			static auto GetItemDefinitionByName = reinterpret_cast<CEconItemDefinition*(__fastcall*)(void*, const char*)>(offsets["ItemDefinitionByName"]);

			return GetItemDefinitionByName(this, name);
		}

		uintptr_t GetItemDefinitionMap()
		{
			static auto GetItemDefinitionMap = *(uint32_t*)(offsets["ItemDefinitionMap"]);
			return *(uintptr_t*)((uintptr_t)this + GetItemDefinitionMap);
		}

		/// This is inlined on Windows so it needs to be rebuilt
		CEconItemDefinition* GetItemDefinitionByMapIndex(int i)
		{
			if (i < 0 || i >= GetItemDefinitionCount())
				return nullptr;

			///												  (v4 = 3 * v3, v5 = v2[0x35], *(v5 + 4 * v4 + 8) < -1) )
			return *reinterpret_cast<CEconItemDefinition**>(GetItemDefinitionMap() + 0x4 * (i * 0x3) + sizeof(void*));
		}
	};

	struct CCStrike15ItemSystem
	{
		virtual CCStrike15ItemSchema* GetItemSchemaInterface() = 0;
	};
}