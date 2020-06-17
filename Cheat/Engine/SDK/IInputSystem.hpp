#pragma once
#include "IAppSystem.hpp"
#include "ButtonCode.h"
#include "QAngle.hpp"

namespace SDK
{
	class IInputSystem : IAppSystem
	{
	public:
		void EnableInput(bool bEnable)
		{
			typedef void(__thiscall* OriginalFn)(void*, bool);
			return GetMethod< OriginalFn >(this, 11)(this, bEnable);
		}

		void ResetInputState()
		{
			typedef void(__thiscall* OriginalFn)(void*);
			return GetMethod< OriginalFn >(this, 39)(this);
		}

		bool IsButtonDown(ButtonCode_t code)
		{
			typedef bool(__thiscall* OriginalFn)(void*, ButtonCode_t);
			return GetMethod< OriginalFn >(this, 15)(this, code);
		}

		void GetCursorPosition(int* m_pX, int* m_pY)
		{
			typedef void(__thiscall* OriginalFn)(void*, int*, int*);
			return GetMethod< OriginalFn >(this, 56)(this, m_pX, m_pY);
		}

		ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey)
		{
			typedef ButtonCode_t(__thiscall* OriginalFn)(void*, int);
			return GetMethod< OriginalFn >(this, 45)(this, nVirtualKey);
		}

		int ButtonCodeToVirtualKey(ButtonCode_t code)
		{
			typedef int(__thiscall* OriginalFn)(void*, ButtonCode_t);
			return GetMethod< OriginalFn >(this, 46)(this, code);
		}

		void*& GetWindow()
		{
			static uint32_t offset = 0;
			if (!offset)
				offset = *reinterpret_cast<uint32_t*>((*reinterpret_cast<char***>(this))[10] + 5);

			return *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + offset);
		}
	};
}
