#pragma once

namespace SDK
{
    struct ConVar 
    {
		char pad_0x0000[0x4]; //0x0000
		ConVar* pNext; //0x0004 
		__int32 bRegistered; //0x0008 
		char* pszName; //0x000C 
		char* pszHelpString; //0x0010 
		__int32 nFlags; //0x0014 
		char pad_0x0018[0x4]; //0x0018
		ConVar* pParent; //0x001C 
		const char* pszDefaultValue; //0x0020 
		char* strString; //0x0024 
		__int32 StringLength; //0x0028 
		float fValue; //0x002C 
		__int32 nValue; //0x0030 
		__int32 bHasMin; //0x0034 
		float fMinVal; //0x0038 
		__int32 bHasMax; //0x003C 
		float fMaxVal; //0x0040 
		CUtlVector<void(__cdecl*)()> fnChangeCallback; //0x0044 


		void SetValue(const char* value)
		{
			typedef void(__thiscall* OriginalFn)(void*, const char*);
			return GetMethod<OriginalFn>(this, 14)(this, value);
		}

		void SetValue(float value)
		{
			typedef void(__thiscall* OriginalFn)(void*, float);
			return GetMethod<OriginalFn>(this, 15)(this, value);
		}

		void SetValue(int value)
		{
			typedef void(__thiscall* OriginalFn)(void*, int);
			return GetMethod<OriginalFn>(this, 16)(this, value);
		}

		void SetValue(Color value)
		{
			typedef void(__thiscall* OriginalFn)(void*, Color);
			return GetMethod<OriginalFn>(this, 17)(this, value);
		}

		float GetFloat(void)
		{
			DWORD xored = *(DWORD*)&this->fValue ^ (DWORD)this;
			return *(float*)&xored;
		}

		char* GetName()
		{
			typedef char* (__thiscall* OriginalFn)(void*);
			return GetMethod<OriginalFn>(this, 5)(this);
		}

		const char* GetDefault()
		{
			return pszDefaultValue;
		}
    };

    class Cvar
    {
    public:
		ConVar* FindVar(const char* var_name)
		{
			typedef ConVar* (__thiscall* OriginalFn)(void*, const char*);
			return GetMethod<OriginalFn>(this, 15)(this, var_name);
		}
    };
}
