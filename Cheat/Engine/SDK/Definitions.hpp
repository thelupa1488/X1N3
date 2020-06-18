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

template <typename T>
T GetVFunc(void *vTable, int iIndex) {
	return (*(T**)vTable)[iIndex];
}

template< typename Function > Function GetMethod( PVOID Base , DWORD Index )
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];

	if (IsBadReadPtr((Function)(dwAddress), sizeof(Function)))
		return nullptr;

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
	byte			r , g , b , a;		// fade to color ( max alpha )
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

class CCSWeaponInfo 
{
public:
	char        pad0[20];
	int         iMaxClip1;                  // 0x0014
	int         iMaxClip2;                  // 0x0018
	int         iDefaultClip1;              // 0x001C
	int         iDefaultClip2;              // 0x0020
	char        pad_0024[8];                // 0x0024
	char*       szWorldModel;               // 0x002C
	char*       szViewModel;                // 0x0030
	char*       szDroppedMode;              // 0x0034
	char        pad_0038[4];                // 0x0038
	char*       szShotSound;                // 0x003C
	char        pad_0040[56];               // 0x0040
	char*       szEmptySound;               // 0x0078
	char        pad_007C[4];                // 0x007C
	char*       szBulletType;               // 0x0080
	char        pad_0084[4];                // 0x0084
	char*       szHudName;
	char*       szWeaponName;
	char        pad3[56];
	int         iWeaponType;
	char        pad4[4];
	int         iWeaponPrice;
	int         iKillAward;
	char        pad5[20];
	char        bFullAuto;
	char        pad6[3];
	int         iDamage;
	float       flArmorRatio;
	int         iBullets;
	float       flPenetration;
	char        pad7[8];
	float       flRange;
	float       flRangeModifier;            
	float		flThrowVelocity;			// 0x010C
	char        pad8[16];
	bool		bHasSilencer;				// 0x011C
	char		pad_0x0119[3];			    // 0x011D
	char*       pSilencerModel;				// 0x0120
	int			iCrosshairMinDistance;		// 0x0124
	float		flMaxPlayerSpeed;	        // 0x0128
	float		flMaxPlayerSpeedAlt;		// 0x012C
	char		pad_0x0130[4];		        // 0x0130
	float		flSpread;					// 0x0134
	float		flSpreadAlt;				// 0x0138
	float		flInaccuracyCrouch;			// 0x013C
	float		flInaccuracyCrouchAlt;		// 0x0140
	float		flInaccuracyStand;			// 0x0144
	float		flInaccuracyStandAlt;		// 0x0148
	float		flInaccuracyJumpInitial;	// 0x014C
	float		flInaccuracyJump;			// 0x0150
	float		flInaccuracyJumpAlt;		// 0x0154
	float		flInaccuracyLand;			// 0x0158
	float		flInaccuracyLandAlt;		// 0x015C
	float		flInaccuracyLadder;			// 0x0160
	float		flInaccuracyLadderAlt;		// 0x0164
	float		flInaccuracyFire;			// 0x0168
	float		flInaccuracyFireAlt;		// 0x016C
	float		flInaccuracyMove;			// 0x0170
	float		flInaccuracyMoveAlt;		// 0x0174
	float		flInaccuracyReload;			// 0x0178
	int			iRecoilSeed;				// 0x017C
	float		flRecoilAngle;				// 0x0180
	float		flRecoilAngleAlt;			// 0x0184
	float		flRecoilAngleVariance;		// 0x0188
	float		flRecoilAngleVarianceAlt;	// 0x018C
	float		flRecoilMagnitude;			// 0x0190
	float		flRecoilMagnitudeAlt;		// 0x0194
	float		flRecoilMagnitudeVariance;	// 0x0198
	float		flRecoilMagnitudeVarianceAlt;	// 0x019C
	float		flRecoveryTimeCrouch;		// 0x01A0
	float		flRecoveryTimeStand;		// 0x01A4
	float		flRecoveryTimeCrouchFinal;	// 0x01A8
	float		flRecoveryTimeStandFinal;	// 0x01AC
	int			iRecoveryTransitionStartBullet;	// 0x01B0 
	int			iRecoveryTransitionEndBullet;	// 0x01B4
	bool		bUnzoomAfterShot;			// 0x01B8
	bool		bHideViewModelZoomed;		// 0x01B9
	char		pad_0x01B5[2];			    // 0x01BA
	char		iZoomLevels[3];			    // 0x01BC
	int			iZoomFOV[2];				// 0x01C0
	float		fZoomTime[3];				// 0x01C4
	char*       szWeaponClass;			    // 0x01D4
	float		flAddonScale;				// 0x01D8
	char		pad_0x01DC[4];			    // 0x01DC
	char*       szEjectBrassEffect;			// 0x01E0
	char*       szTracerEffect;				// 0x01E4
	int			iTracerFrequency;			// 0x01E8
	int			iTracerFrequencyAlt;		// 0x01EC
	char*       szMuzzleFlashEffect_1stPerson;	// 0x01F0
	char		pad_0x01F4[4];				// 0x01F4
	char*       szMuzzleFlashEffect_3rdPerson;	// 0x01F8
	char		pad_0x01FC[4];			    // 0x01FC
	char*       szMuzzleSmokeEffect;		// 0x0200
	float		flHeatPerShot;				// 0x0204
	char*       szZoomInSound;				// 0x0208
	char*       szZoomOutSound;				// 0x020C
	float		flInaccuracyPitchShift;		// 0x0210
	float		flInaccuracySoundThreshold;	// 0x0214
	float		flBotAudibleRange;			// 0x0218
	char		pad_0x0218[8];			    // 0x0220
	char*       pWrongTeamMsg;				// 0x0224
	bool		bHasBurstMode;				// 0x0228
	char		pad_0x0225[3];			    // 0x0229
	bool		bIsRevolver;				// 0x022C
	bool		bCannotShootUnderwater;		// 0x0230
};

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

	enum class FontFeature {
		FONT_FEATURE_ANTIALIASED_FONTS = 1 ,
		FONT_FEATURE_DROPSHADOW_FONTS = 2 ,
		FONT_FEATURE_OUTLINE_FONTS = 6 ,
	};

	enum class FontDrawType {
		FONT_DRAW_DEFAULT = 0 ,
		FONT_DRAW_NONADDITIVE ,
		FONT_DRAW_ADDITIVE ,
		FONT_DRAW_TYPE_COUNT = 2 ,
	};

	enum class FontFlags {
		FONTFLAG_NONE ,
		FONTFLAG_ITALIC = 0x001 ,
		FONTFLAG_UNDERLINE = 0x002 ,
		FONTFLAG_STRIKEOUT = 0x004 ,
		FONTFLAG_SYMBOL = 0x008 ,
		FONTFLAG_ANTIALIAS = 0x010 ,
		FONTFLAG_GAUSSIANBLUR = 0x020 ,
		FONTFLAG_ROTARY = 0x040 ,
		FONTFLAG_DROPSHADOW = 0x080 ,
		FONTFLAG_ADDITIVE = 0x100 ,
		FONTFLAG_OUTLINE = 0x200 ,
		FONTFLAG_CUSTOM = 0x400 ,
		FONTFLAG_BITMAP = 0x800 ,
	};

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