#pragma once

namespace SDK
{
	class ConVar
	{
	public:

		char pad_0x0000[0x4]; //0x0000
		ConVar* pNext; //0x0004 
		__int32 bRegistered; //0x0008 
		char* pszName; //0x000C 
		char* pszHelpString; //0x0010 
		__int32 nFlags; //0x0014 
		char pad_0x0018[0x4]; //0x0018
		ConVar* pParent; //0x001C 
		char* pszDefaultValue; //0x0020 
		char* strString; //0x0024 
		__int32 StringLength; //0x0028 
		float fValue; //0x002C 
		__int32 nValue; //0x0030 
		__int32 bHasMin; //0x0034 
		float fMinVal; //0x0038 
		__int32 bHasMax; //0x003C 
		float fMaxVal; //0x0040 
		void* fnChangeCallback; //0x0044 


		void ConVar::SetValue(const char* value)
		{
			typedef void(__thiscall* OriginalFn)(void*, const char*);
			return GetMethod<OriginalFn>(this, 14)(this, value);
		}

		void ConVar::SetValue(float value)
		{
			typedef void(__thiscall* OriginalFn)(void*, float);
			return GetMethod<OriginalFn>(this, 15)(this, value);
		}

		void ConVar::SetValue(int value)
		{
			typedef void(__thiscall* OriginalFn)(void*, int);
			return GetMethod<OriginalFn>(this, 16)(this, value);
		}

		void ConVar::SetValue(Color value)
		{
			typedef void(__thiscall* OriginalFn)(void*, Color);
			return GetMethod<OriginalFn>(this, 17)(this, value);
		}

		float ConVar::GetFloat(void)
		{
			DWORD xored = *(DWORD*)&this->fValue ^ (DWORD)this;
			return *(float*)&xored;
		}

		char* ConVar::GetName()
		{
			typedef char*(__thiscall* OriginalFn)(void*);
			return GetMethod<OriginalFn>(this, 5)(this);
		}

		char* ConVar::GetDefault()
		{
			return pszDefaultValue;
		}

		void RegisterConCommand(ConVar *pCvar)
		{
			typedef void(__thiscall* OriginalFn)(void*, ConVar*);
			return GetMethod<OriginalFn>(this, 1)(this, pCvar);
		}

		ConVar* FindVar(const char *var_name)
		{
			typedef ConVar*(__thiscall* OriginalFn)(void*, const char*);
			return GetMethod<OriginalFn>(this, 15)(this, var_name);
		}

	};//Size=0x0048

	class ICvar
	{
	public:
		ConVar* FindVar(const char* var_name)
		{
			typedef ConVar* (__thiscall* OriginalFn)(void*, const char*);
			return GetMethod<OriginalFn>(this, 15)(this, var_name);
		}
		void RegisterConCommand(ConVar* pCommandBase)
		{
			typedef ConVar* (__thiscall* FindVarFn)(void*, ConVar*);
			GetMethod< FindVarFn >(this, 12)(this, pCommandBase);
		}

		void UnRegisterConCommand(ConVar* pCommandBase)
		{
			typedef ConVar* (__thiscall* FindVarFn)(void*, ConVar*);
			GetMethod<FindVarFn>(this, 13)(this, pCommandBase);
		}
	};

	class SpoofedConvar
	{
	public:
		ICvar*  m_pCvar = nullptr;
		ConVar* m_pOriginalCVar = nullptr;
		ConVar* m_pDummyCVar = nullptr;

		char m_szDummyName[128];
		char m_szDummyValue[128];
		char m_szOriginalName[128];
		char m_szOriginalValue[128];
		int m_iOriginalFlags;

		SpoofedConvar::SpoofedConvar() {}

		SpoofedConvar::SpoofedConvar(const char* szCVar)
		{
			m_pOriginalCVar = m_pCvar->FindVar(szCVar);
			Spoof();
		}
		SpoofedConvar::SpoofedConvar(ConVar* pCVar)
		{
			m_pOriginalCVar = pCVar;
			Spoof();
		}
		SpoofedConvar::~SpoofedConvar() {
			if (IsSpoofed()) {
				DWORD dwOld;

				SetFlags(m_iOriginalFlags);
				SetString(m_szOriginalValue);

				VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);
				strcpy((char*)m_pOriginalCVar->pszName, m_szOriginalName);
				VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

				//Unregister dummy cvar
				m_pCvar->UnRegisterConCommand(m_pDummyCVar);
				free(m_pDummyCVar);
				m_pDummyCVar = nullptr;
			}
		}
		bool SpoofedConvar::IsSpoofed()
		{
			return m_pDummyCVar != nullptr;
		}
		void SpoofedConvar::Spoof()
		{
			if (!IsSpoofed() && m_pOriginalCVar)
			{
				//Save old name value and flags so we can restore the cvar lates if needed
				m_iOriginalFlags = m_pOriginalCVar->nFlags;
				strcpy(m_szOriginalName, m_pOriginalCVar->pszName);
				strcpy(m_szOriginalValue, m_pOriginalCVar->pszDefaultValue);

				sprintf_s(m_szDummyName, 128, "d_%s", m_szOriginalName);

				//Create the dummy cvar
				m_pDummyCVar = (ConVar*)malloc(sizeof(ConVar));
				if (!m_pDummyCVar) return;
				memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(ConVar));

				m_pDummyCVar->pNext = nullptr;
				//Register it
				m_pCvar->RegisterConCommand(m_pDummyCVar);

				//Fix "write access violation" bullshit
				DWORD dwOld;
				VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);

				//Rename the cvar
				strcpy((char*)m_pOriginalCVar->pszName, m_szDummyName);

				VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

				SetFlags(0);
			}
		}
		void SpoofedConvar::SetFlags(int flags)
		{
			if (IsSpoofed())
			{
				m_pOriginalCVar->nFlags = flags;
			}
		}
		int SpoofedConvar::GetFlags()
		{
			return m_pOriginalCVar->nFlags;
		}
		void SpoofedConvar::SetInt(int iValue)
		{
			if (IsSpoofed())
			{
				m_pOriginalCVar->SetValue(iValue);
			}
		}
		void SpoofedConvar::SetBool(bool bValue)
		{
			if (IsSpoofed())
			{
				m_pOriginalCVar->SetValue(bValue);
			}
		}
		void SpoofedConvar::SetFloat(float flValue)
		{
			if (IsSpoofed())
			{
				m_pOriginalCVar->SetValue(flValue);
			}
		}
		void SpoofedConvar::SetString(const char* szValue)
		{
			if (IsSpoofed())
			{
				m_pOriginalCVar->SetValue(szValue);
			}
		}
	};
}

                                                                             