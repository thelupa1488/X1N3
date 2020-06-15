#pragma once
#include "../../Initialize/Offsets.h"

namespace SDK
{
	class IGameRules
	{
	public:
		bool IsFreezePeriod() 
		{
			return *(bool*)((uintptr_t)this + offsets["m_bFreezePeriod"]);
		}
		bool IsValveDS() 
		{
			return *(bool*)((uintptr_t)this + offsets["m_bIsValveDS"]);
		}
		bool IsBombPlanted() 
		{
			return *(bool*)((uintptr_t)this + offsets["m_bBombDropped"]);
		}
		bool IsBombDropped()
		{
			return *(bool*)((uintptr_t)this + offsets["m_bBombDropped"]);
		}
	};
}