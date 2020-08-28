#pragma once

#include <Windows.h>

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif

#define VirtualFn( cast ) typedef cast( __thiscall* OriginalFn )

template< typename Function > Function GetMethod( PVOID Base , DWORD Index )
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];

//	if (FastCall::G().t_IsBadReadPtr((Function)(dwAddress), sizeof(Function)))
//		return nullptr;

	return (Function)( dwAddress );
}


typedef struct con_nprint_s
{
	int		index;			// Row #
	float	time_to_live;	// # of seconds before it disappears. -1 means to display for 1 frame then go away.
	float	color[3];		// RGB colors ( 0.0 -> 1.0 scale )
	bool	fixed_width_font;
} con_nprint_t;

struct ScreenFade_t
{
	unsigned short 	duration;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration
	unsigned short 	holdTime;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration until reset (fade & hold)
	short			fadeFlags;		// flags
	BYTE			r , g , b , a;		// fade to color ( max alpha )
};

struct CHudTexture
{
	char	szShortName[64];	//0x0000
	char	szTextureFile[64];	//0x0040
	bool	bRenderUsingFont;	//0x0080
	bool	bPrecached;			//0x0081
	char	cCharacterInFont;	//0x0082
	BYTE	pad_0x0083;			//0x0083
	int		hFont;				//0x0084
	int		iTextureId;			//0x0088
	float	afTexCoords[4];		//0x008C
	int		iPosX[4];			//0x009C
}; //Size=0x00AC

enum CyrTeamID : int
{
	CYRT_CT,
	CYRT_TT,
	CYRT_ALL,
	CYRT_AUTO,
	CYRT_DISBLE
};

enum TeamID
{
	TEAM_UNASSIGNED,
	TEAM_SPECTATOR,
	TEAM_TERRORIST,
	TEAM_COUNTER_TERRORIST,
	TEAM_ALL
};

namespace SDK
{
	typedef void* ( *CreateInterfaceFn )( const char *pName , int *pReturnCode );
	typedef void* ( *InstantiateInterfaceFn )( );

	typedef void( *pfnDemoCustomDataCallback )( unsigned char *pData , size_t iSize );

	enum class ObserverMode_t : int
	{
		OBS_MODE_NONE = 0 ,
		OBS_MODE_DEATHCAM = 1 ,
		OBS_MODE_FREEZECAM = 2 ,
		OBS_MODE_FIXED = 3 ,
		OBS_MODE_IN_EYE = 4 ,
		OBS_MODE_CHASE = 5 ,
		OBS_MODE_ROAMING = 6
	};
}