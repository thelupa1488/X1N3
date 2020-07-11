#pragma once
#include "../../Initialize/Offsets.h"

namespace SDK
{
	class IGameRules
	{
	public:
		bool IsFreezePeriod() 
		{
			return ptr(*(bool*), this, offsets["m_bFreezePeriod"]);
		}
		bool IsValveDS() 
		{
			return ptr(*(bool*), this, offsets["m_bIsValveDS"]);
		}
		bool IsBombPlanted() 
		{
			return ptr(*(bool*), this, offsets["m_bBombDropped"]);
		}
		bool IsBombDropped()
		{
			return ptr(*(bool*), this, offsets["m_bBombDropped"]);
		}
	};
}