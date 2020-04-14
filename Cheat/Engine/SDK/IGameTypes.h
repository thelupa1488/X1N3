#pragma once

#include "SDK.h"

namespace SDK
{
	class IGameTypes
	{
	public:
		virtual ~IGameTypes() {}
		virtual bool Initialize(bool force) = 0;
		virtual bool IsInitialized() const = 0;

		virtual bool SetGameTypeAndMode(const char* gameType, const char* gameMode) = 0;
		virtual bool GetGameTypeAndModeFromAlias(const char* alias, int& gameType, int& gameMode) = 0;

		virtual bool SetGameTypeAndMode(int gameType, int gameMode) = 0;

		virtual void SetAndParseExtendedServerInfo(void* pExtendedServerInfo) = 0;

		virtual bool CheckShouldSetDefaultGameModeAndType(const char* mapName) = 0;

		virtual int GetCurrentGameType() const = 0;
		virtual int GetCurrentGameMode() const = 0;

		virtual const char* GetCurrentMapName() = 0;

		virtual const char* GetCurrentGameTypeNameID() = 0;
		virtual const char* GetCurrentGameModeNameID() = 0;

	};
}