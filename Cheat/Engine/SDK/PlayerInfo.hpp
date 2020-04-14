#pragma once

#include "Definitions.hpp"

namespace SDK
{
    typedef struct PlayerInfo
	{
		__int64         unknown;            //0x0000 
		union
		{
			__int64       steamID64;          //0x0008 - SteamID64
			struct
			{
				__int32     m_nXuidLow;
				__int32     m_nXuidHigh;
			};
		};
		char            m_szPlayerName[128];        //0x0010 - Player Name
		int             m_nUserID;             //0x0090 - Unique Server Identifier
		char            m_szSteamID[20];      //0x0094 - STEAM_X:Y:Z
		char            pad_0x00A8[0x10];   //0x00A8
		unsigned long   m_nSteam3ID;           //0x00B8 - SteamID 
		char            m_szFriendsName[128];
		bool            m_bIsFakePlayer;
		bool            m_bIsHLTV;
		unsigned int    m_dwCustomFiles[4];
		unsigned char   m_FilesDownloaded;
	} PlayerInfo;
}