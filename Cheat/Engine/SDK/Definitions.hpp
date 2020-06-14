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

template< typename Function > Function call_vfunc(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)(dwAddress);
}

template <typename T>
T GetVFunc(void *vTable, int iIndex) {
	return (*(T**)vTable)[iIndex];
}

template< typename Function > Function GetMethod(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)(dwAddress);
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
	byte			r, g, b, a;		// fade to color ( max alpha )
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

class CWeaponInfo
{
public:
	char pad_0x0000[0x4]; //0x0000
	char* m_WeaponName; //0x0004 
	char pad_0x0008[0xC]; //0x0008
	__int32 m_MaxClip; //0x0014 
	char pad_0x0018[0xC]; //0x0018
	__int32 m_MaxReservedAmmo; //0x0024 
	char pad_0x0028[0x4]; //0x0028
	char* m_WeaponMdlPath; //0x002C 
	char pad_0x0030[0x4]; //0x0030
	char* m_DropWeaponMdlPath; //0x0034 
	char pad_0x0038[0x48]; //0x0038
	char* m_BulletType; //0x0080 
	char pad_0x0084[0x4]; //0x0084
	char* m_WeaponHudName; //0x0088 
	char pad_0x008C[0x40]; //0x008C
	__int32 m_WeaponType; //0x00CC 
	__int32 m_WeaponPrice; //0x00D0 
	__int32 m_WeaponReward; //0x00D4 
	char* m_WeaponGroupName; //0x00D8 
	char pad_0x00DC[0x10]; //0x00DC
	unsigned char m_FullAuto; //0x00EC 
	char pad_0x00ED[0x3]; //0x00ED
	__int32 m_WeaponDamage; //0x00F0 
	float m_ArmorRatio; //0x00F4 
	__int32 m_iBullets;
	float m_Penetration; //0x00F8
	char pad_0x00F8[0x8]; //0x00FC
	float m_WeaponRange; //0x0108 
	float m_RangeModifier; //0x010C 
	char pad_0x0110[0x10]; //0x0110
	unsigned char m_HasSilencer; //0x0120 
	char pad_0x0121[0xF]; //0x0121
	float m_MaxSpeed; //0x0130 
	float m_MaxSpeed2; //0x0134 
	char pad_0x0138[0x4C]; //0x0138
	__int32 m_RecoilSeed; //0x0184 
	char pad_0x0188[0x68]; //0x0188
	char* m_WeaponTracesType; //0x01F0 
	char pad_0x01F4[0x638]; //0x01F4
};

class IWeaponSystem
{
	virtual void unused0() = 0;
	virtual void unused1() = 0;
public:
	virtual CWeaponInfo* GetWpnData(unsigned ItemDefinitionIndex) = 0;
};

class input {
public:
	char pad_0x00[0x0C]; // 0x00
	bool m_trackir_available; //0x0C
	bool m_mouse_initiated; //0x0D
	bool m_mouse_active; //0x0E
	char pad_0x0F[0xFBE];
}; // size = 0xFCC


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
	typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
	typedef void* (*InstantiateInterfaceFn)();

	typedef void(*pfnDemoCustomDataCallback)(unsigned char *pData, size_t iSize);

	enum class FontFeature {
		FONT_FEATURE_ANTIALIASED_FONTS = 1,
		FONT_FEATURE_DROPSHADOW_FONTS = 2,
		FONT_FEATURE_OUTLINE_FONTS = 6,
	};

	enum class FontDrawType {
		FONT_DRAW_DEFAULT = 0,
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,
		FONT_DRAW_TYPE_COUNT = 2,
	};

	enum class FontFlags {
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
		FONTFLAG_ANTIALIAS = 0x010,
		FONTFLAG_GAUSSIANBLUR = 0x020,
		FONTFLAG_ROTARY = 0x040,
		FONTFLAG_DROPSHADOW = 0x080,
		FONTFLAG_ADDITIVE = 0x100,
		FONTFLAG_OUTLINE = 0x200,
		FONTFLAG_CUSTOM = 0x400,
		FONTFLAG_BITMAP = 0x800,
	};

	enum class ClientFrameStage_t {
		FRAME_UNDEFINED = -1,
		FRAME_START,
		FRAME_NET_UPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_END,
		FRAME_NET_UPDATE_END,
		FRAME_RENDER_START,
		FRAME_RENDER_END
	};

	enum class ObserverMode_t : int
	{
		OBS_MODE_NONE = 0,
		OBS_MODE_DEATHCAM = 1,
		OBS_MODE_FREEZECAM = 2,
		OBS_MODE_FIXED = 3,
		OBS_MODE_IN_EYE = 4,
		OBS_MODE_CHASE = 5,
		OBS_MODE_ROAMING = 6
	};

	enum MaterialPropertyTypes_t
	{
		MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0, // bool
		MATERIAL_PROPERTY_OPACITY, // int (enum MaterialPropertyOpacityTypes_t)
		MATERIAL_PROPERTY_REFLECTIVITY, // vec3_t
		MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS // bool
	};

	enum ImageFormat
	{
		IMAGE_FORMAT_UNKNOWN = -1,
		IMAGE_FORMAT_RGBA8888 = 0,
		IMAGE_FORMAT_ABGR8888,
		IMAGE_FORMAT_RGB888,
		IMAGE_FORMAT_BGR888,
		IMAGE_FORMAT_RGB565,
		IMAGE_FORMAT_I8,
		IMAGE_FORMAT_IA88,
		IMAGE_FORMAT_P8,
		IMAGE_FORMAT_A8,
		IMAGE_FORMAT_RGB888_BLUESCREEN,
		IMAGE_FORMAT_BGR888_BLUESCREEN,
		IMAGE_FORMAT_ARGB8888,
		IMAGE_FORMAT_BGRA8888,
		IMAGE_FORMAT_DXT1,
		IMAGE_FORMAT_DXT3,
		IMAGE_FORMAT_DXT5,
		IMAGE_FORMAT_BGRX8888,
		IMAGE_FORMAT_BGR565,
		IMAGE_FORMAT_BGRX5551,
		IMAGE_FORMAT_BGRA4444,
		IMAGE_FORMAT_DXT1_ONEBITALPHA,
		IMAGE_FORMAT_BGRA5551,
		IMAGE_FORMAT_UV88,
		IMAGE_FORMAT_UVWQ8888,
		IMAGE_FORMAT_RGBA16161616F,
		IMAGE_FORMAT_RGBA16161616,
		IMAGE_FORMAT_UVLX8888,
		IMAGE_FORMAT_R32F, // Single-channel 32-bit floating Point
		IMAGE_FORMAT_RGB323232F, // NOTE: D3D9 does not have this format
		IMAGE_FORMAT_RGBA32323232F,
		IMAGE_FORMAT_RG1616F,
		IMAGE_FORMAT_RG3232F,
		IMAGE_FORMAT_RGBX8888,

		IMAGE_FORMAT_NULL, // Dummy format which takes no video memory

						   // Compressed normal map formats
						   IMAGE_FORMAT_ATI2N, // One-surface ATI2N / DXN format
						   IMAGE_FORMAT_ATI1N, // Two-surface ATI1N format

						   IMAGE_FORMAT_RGBA1010102, // 10 bit-per component render targets
						   IMAGE_FORMAT_BGRA1010102,
						   IMAGE_FORMAT_R16F, // 16 bit FP format

											  // Depth-stencil texture formats
											  IMAGE_FORMAT_D16,
											  IMAGE_FORMAT_D15S1,
											  IMAGE_FORMAT_D32,
											  IMAGE_FORMAT_D24S8,
											  IMAGE_FORMAT_LINEAR_D24S8,
											  IMAGE_FORMAT_D24X8,
											  IMAGE_FORMAT_D24X4S4,
											  IMAGE_FORMAT_D24FS8,
											  IMAGE_FORMAT_D16_SHADOW, // Specific formats for shadow mapping
											  IMAGE_FORMAT_D24X8_SHADOW, // Specific formats for shadow mapping

																		 // supporting these specific formats as non-tiled for procedural cpu access (360-specific)
																		 IMAGE_FORMAT_LINEAR_BGRX8888,
																		 IMAGE_FORMAT_LINEAR_RGBA8888,
																		 IMAGE_FORMAT_LINEAR_ABGR8888,
																		 IMAGE_FORMAT_LINEAR_ARGB8888,
																		 IMAGE_FORMAT_LINEAR_BGRA8888,
																		 IMAGE_FORMAT_LINEAR_RGB888,
																		 IMAGE_FORMAT_LINEAR_BGR888,
																		 IMAGE_FORMAT_LINEAR_BGRX5551,
																		 IMAGE_FORMAT_LINEAR_I8,
																		 IMAGE_FORMAT_LINEAR_RGBA16161616,

																		 IMAGE_FORMAT_LE_BGRX8888,
																		 IMAGE_FORMAT_LE_BGRA8888,

																		 NUM_IMAGE_FORMATS
	};
}