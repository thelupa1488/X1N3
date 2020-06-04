#include "SDK.h"
#include "../../Main.h"
//#include "../Settings/Settings.h"

namespace SDK
{
	bool KeyValues::LoadFromBuffer(KeyValues* pThis, const char* pszFirst, const char* pszSecond, PVOID pSomething, PVOID pAnother, PVOID pLast)
	{
		typedef bool(__thiscall * _LoadFromBuffer)(KeyValues*, const char*, const char*, PVOID, PVOID, PVOID);

		static _LoadFromBuffer LoadFromBufferFn = 0;
		static bool SearchFunction = false;

		if (!SearchFunction)
		{
			DWORD dwFunctionAddress = CSX::Memory::FindPattern(XorStr("client.dll"), XorStr("55 8B EC 83 EC 44 53 56 57 8B F9 89 7D F8 FF 15 ? ? ? ? 8B F0 B9"), 0);


			if (dwFunctionAddress)
			{
				LoadFromBufferFn = (_LoadFromBuffer)dwFunctionAddress;
				SearchFunction = true;
			}
		}

		if (LoadFromBufferFn && SearchFunction)
		{
			return LoadFromBufferFn(pThis, pszFirst, pszSecond, pSomething, pAnother, pLast);
		}

		return false;
	}
}