#pragma once
#include "../../Engine/Engine.h"
#include "../../Render/DXOverlayManager.h"
#include "../Settings.h"
#include "../../X1API/MinHook/hook.h"

namespace HookTables
{
	using DrawModelExecuteFn = void(__thiscall*)(void*, IMatRenderContext*, const DrawModelState_t&,
		const ModelRenderInfo_t&, matrix3x4_t*);
	extern cDetour<DrawModelExecuteFn>* pDrawModelExecute;
}

namespace Engine
{
	class CBaseEntity;
	class CPlayer;
}

using namespace Engine;

class CHitListener : public IGameEventListener2
{
public:

	struct DamgeInfo_t
	{
		Vector Pos;
		int Number;
		float EndTime;
		float Alpha;
		float OffsetZ;
	};

	vector<DamgeInfo_t> DamageVector;

	bool DrawHit = false;
	float HitMarkerEndTime = 0;

	void RegListener();
	void UnRegListener();

	void FireGameEvent(IGameEvent *pEvent) override;
	void Draw();
};

class IMisc
{
protected:
	virtual void GetViewModelFOV(float &Fov) = 0;
	virtual void AutoAcceptEmit() = 0;
	virtual void DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld) = 0;
	virtual void ShowSpectatorList() = 0;
	virtual vector<int> GetObservervators(int playerId) = 0;
	virtual void Night() = 0;
	virtual void Reset() = 0;
	virtual void UpdateSoundList() = 0;
	virtual void CustomWalls() = 0;
	virtual void Menu() = 0;
	virtual void Draw() = 0;
	virtual void CreateMove(bool &bSendPacket, float flInputSampleTime, CUserCmd* pCmd) = 0;
	virtual void CreateMoveEP(CUserCmd* pCmd, bool& bSendPacket) = 0;
	virtual void Desync(CUserCmd* pCmd, bool& bSendPacket) = 0;
	virtual void OverrideView(CViewSetup* pSetup) = 0;
};

class CMisc : public IMisc
{
public:
	CConfig Config = CConfig(XorStr("Misc"));

	struct HitImpact_t
	{
		Vector Pos;
		Vector MyHeadPos;
		float EndTime;
		float Alpha;
	};

	virtual void Menu();
	virtual void Draw();
	virtual void CreateMove(bool &bSendPacket, float flInputSampleTime, CUserCmd* pCmd);
	virtual void CreateMoveEP(CUserCmd* pCmd, bool& bSendPacket);
	virtual void Desync(CUserCmd* pCmd, bool& bSendPacket);
	virtual void OverrideView(CViewSetup* pSetup);
	virtual void GetViewModelFOV(float &Fov);
	virtual void AutoAcceptEmit();
	virtual void DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
	virtual void ShowSpectatorList();
	virtual vector<int> GetObservervators(int playerId);
	virtual void Night();
	virtual void Reset();
	virtual void UpdateSoundList();
	virtual void CustomWalls();

	bool Enable = true;
	bool BHop = false;
	int BHopType = 0;
	int BHopChance = 0;
	int BHopLimit = 0;
	int BHopMaxHit = 0;
	bool AutoStrafe = false;
	int AutoStrafeSpeed = 0;
	bool EdgeJump = false;
	CBind EdgeJumpBind = CBind(0, true);

	bool LRHandKnife = false;
	bool SwapHand = false;
	CBind SwapHandBind = CBind(0, true);
	bool InfiniteCrouch = false;

	bool ThirdPerson = false;
	int ThirdPersonDistance = 150;
	CBind ThirdPersonBind = CBind(0, true);

	bool LDesync = false;
	CBind LDesyncBind = CBind(0, true);
	bool LDesyncArrows = false;

	bool FovChanger = false;
	int FovView = 100;
	bool FovModelChanger = false;
	int FovModel = 80;
	bool NoVisualRecoil = false;

	bool FreeCam = false;
	int FreeCamSpeed = 5;
	CBind FreeCamBind = CBind(0, true);

	bool Crosshair = false;
	int CrosshairStyle = 1;
	int CrosshairSize = 5;
	bool CrosshairRecoil = true;
	bool CrosshairOutline = true;
	bool SnipCrosshair = false;
	int SnipCrosshairStyle = 1;
	int SnipCrosshairSize = 5;
	bool SnipCrosshairRecoil = false;
	bool SnipCrosshairOutline = true;

	bool SpreadCircel = false;

	vector<HitImpact_t> HitImpacts;

	bool HitMarker = false;
	int HitMarkerTickness = 1;
	int HitMarkerSize = 15;
	bool HitSound = false;
	int HitSoundStyle = 0;

	bool AntiFlash = false;
	int AntiFlashAlpha = 255;

	bool NoSmoke = false;
	int NoSmokeStyle = 0;

	CHitListener HitWorker;

	bool NameStealer = false;
	bool ClanTagChanger = false;
	int ClanTagChangerStyle = 0;
	string ClanTagChangerText = XorStr("X1N3");

	bool ChatSpam = false;
	bool ChatSpamStart = false;
	int ChatSpamStyle = 0;
	string ChatSpamText = "";

	bool RadioSpam = false;
	bool RadioSpamStart = false;

	bool AutoAccept = false;
	bool ShowCompetitiveRank = false;
	bool SpectatorList = false;
	int SpectatorListAlpha = 255;
	int SpectatorListPosX = 500;
	int SpectatorListPosY = 500;
	bool SpectatorListAutoHide = true;

	bool NightMode = false;

	bool HandChams = false;
	int HCStyle = 0;
	int HCDouble = 0;

	bool HandGlow = false;
	int HGStyle = 0;
	int HGPSpeed = 0;
	float HGPRange = 0;

	bool WeaponChams = false;
	int WCStyle = 0;
	int WCDouble = 0;

	bool WeaponGlow = false;
	int WGStyle = 0;
	int WGPSpeed = 0;
	float WGPRange = 0;

	bool DamageInfo = false;
	int DamageInfoPosition = 1;
	int DamageInfoStyle = 0;
	float DamageInfoShowTime = 2;
	int DamageInfoPosX = 960;
	int DamageInfoPosY = 300;
	int DamageInfoSize = 300;
	int DamageInfoHeight = 90;
	int DamageInfoSpeed = 30;

	bool ViewModelXYZ = false;

	float ViewModelX = 0;
	float ViewModelY = 0;
	float ViewModelZ = 0;

	bool Aspect = false;
	float AspectRation = 0;

	bool FakeLag = false;
	int FakeLagFactor = 0;
	int FakeLagType = 0;
	bool FakeLagStanding = false;
	bool FakeLagMoving = false;
	bool FakeLagUnducking = false;
	CBind FakeLagBind = CBind(0, false);

	int TextDamageInfo = 38;

	bool ColoredWalls = false;

	bool KnifeBot = false;
	int KnifeBotDistance = 81;
	int KnifeBotFilter = 0;
	int KnifeBotMode = 0;
	CBind KnifeBotBind = CBind(0);
	bool AutoBlock = false;
	CBind AutoBlockBind = CBind(0);

	Color CrosshairColor = Color(255, 0, 0, 255);
	Color SnipCrosshairColor = Color(255, 0, 0, 255);
	Color SpreadColor = Color(255, 255, 50, 255);
	Color HitMarkerColor = Color(255, 0, 0, 255);
	Color HandChamsColor = Color(255, 198, 0, 255);
	Color HandGlowColor = Color(255, 198, 0, 255);
	Color WeaponChamsColor = Color(255, 198, 0, 255);
	Color WeaponGlowColor = Color(255, 198, 0, 255);
	Color DamageInfoColor = Color(255, 100, 100, 255);
	Color ColoredWallsColor = Color(255, 100, 100, 255);
	Color ArrowsColor = Color(255, 0, 0, 255);

	vector<string> SoundList;

	CMisc()
	{
		RV(CrosshairColor, "CrosshairColor");
		RV(SnipCrosshairColor, "SnipCrosshairColor");
		RV(SpreadColor, "SpreadColor");
		RV(HitMarkerColor, "HitMarkerColor");
		RV(HandChamsColor, "HandChamsColor");
		RV(HandGlowColor, "HandGlowColor");
		RV(WeaponChamsColor, "WeaponChamsColor");
		RV(WeaponGlowColor, "WeaponGlowColor");
		RV(DamageInfoColor, "DamageInfoColor");
		RV(ColoredWallsColor, "ColoredWallsColor");
		RV(ArrowsColor, "ArrowsColor");

		RV(BHop, "BHop");
		RV(BHopType, "BHopType");
		RV(BHopChance, "BHopHitChance");
		RV(BHopLimit, "BHopLimit");
		RV(BHopMaxHit, "BHopMaxHit")
		RV(AutoStrafe, "AutoStrafe");
		RV(AutoStrafeSpeed, "AutoStrafeSpeed");
		RV(EdgeJump, "EdgeJump");
		RV(EdgeJumpBind, "EdgeJumpBind");
		RV(LRHandKnife, "LRHandKnife");
		RV(SwapHand, "SwapHand");
		RV(SwapHandBind, "SwapHandBind")
		RV(InfiniteCrouch, "InfiniteCrouch");
		RV(ThirdPerson, "ThirdPerson");
		RV(ThirdPersonDistance, "ThirdPersonDistance");
		RV(ThirdPersonBind, "ThirdPersonBind");
		RV(LDesync, "LDesync");
		RV(LDesyncBind, "LDesyncBind");
		RV(LDesyncArrows, "LDesyncArrows");
		RV(FovChanger, "FovChanger");
		RV(FovView, "FovView");
		RV(FovModelChanger, "FovModelChanger");
		RV(FovModel, "FovModel");
		RV(NoVisualRecoil, "NoVisualRecoil");
		RV(FreeCam, "FreeCam");
		RV(FreeCamSpeed, "FreeCamSpeed");
		RV(FreeCamBind, "FreeCamBind");
		RV(Crosshair, "Crosshair");
		RV(CrosshairStyle, "CrosshairStyle");
		RV(CrosshairSize, "CrosshairSize");
		RV(CrosshairRecoil, "CrosshairRecoil");
		RV(CrosshairOutline, "CrosshairOutline");
		RV(SnipCrosshair, "SnipCrosshair");
		RV(SnipCrosshairStyle, "SnipCrosshairStyle");
		RV(SnipCrosshairSize, "SnipCrosshairSize");
		RV(SnipCrosshairRecoil, "SnipCrosshairRecoil");
		RV(SnipCrosshairOutline, "SnipCrosshairOutline");
		RV(SpreadCircel, "SpreadCircel");
		RV(HitMarker, "HitMarker");
		RV(HitMarkerTickness, "HitMarkerTickness");
		RV(HitMarkerSize, "HitMarkerSize");
		RV(HitSound, "HitSound");
		RV(HitSoundStyle, "HitSoundStyle");
		RV(AntiFlash, "AntiFlash");
		RV(AntiFlashAlpha, "AntiFlashAlpha");
		RV(NoSmoke, "NoSmoke");
		RV(NoSmokeStyle, "NoSmokeStyle")
		RV(NameStealer, "NameStealer")
		RV(ClanTagChanger, "ClanTagChanger");
		RV(ClanTagChangerStyle, "ClanTagChangerStyle");
		RV(ClanTagChangerText, "ClanTagChangerText");
		RV(ChatSpam, "ChatSpam");
		RV(ChatSpamStart, "ChatSpamStart");
		RV(ChatSpamStyle, "ChatSpamStyle");
		RV(ChatSpamText, "ChatSpamText");
		RV(RadioSpam, "RadioSpam");
		RV(RadioSpamStart, "RadioSpamStart");
		RV(AutoAccept, "AutoAccept");
		RV(ShowCompetitiveRank, "ShowCompetitiveRank");
		RV(SpectatorList, "SpectatorList");
		RV(SpectatorListAlpha, "SpectatorListAlpha");
		RV(SpectatorListPosX, "SpectatorListPosX");
		RV(SpectatorListPosY, "SpectatorListPosY");
		RV(SpectatorListAutoHide, "SpectatorListAutoHide");
		RV(NightMode, "NightMode");
		RV(HandChams, "HandChams");
		RV(HCStyle, "HCStyle");
		RV(HCDouble, "HCDouble");
		RV(HandGlow, "HandGlow");
		RV(HGStyle, "HGStyle");
		RV(HGPSpeed, "HGPSpeed");
		RV(HGPRange, "HGPRange");
		RV(WeaponChams, "WeaponChams");
		RV(WCStyle, "WCStyle");
		RV(WCDouble, "WCDouble");
		RV(WeaponGlow, "WeaponGlow");
		RV(WGStyle, "WGStyle");
		RV(WGPSpeed, "WGPSpeed");
		RV(WGPRange, "WGPRange");
		RV(DamageInfo, "DamageInfo");
		RV(DamageInfoPosition, "DamageInfoPosition");
		RV(DamageInfoStyle, "DamageInfoStyle");
		RV(DamageInfoShowTime, "DamageInfoShowTime");
		RV(DamageInfoPosX, "DamageInfoPosX");
		RV(DamageInfoPosY, "DamageInfoPosY");
		RV(DamageInfoSize, "DamageInfoSize");
		RV(DamageInfoHeight, "DamageInfoHeight");
		RV(DamageInfoSpeed, "DamageInfoSpeed");
		RV(ViewModelXYZ, "ViewModelXYZ");
		RV(ViewModelX, "ViewModelX");
		RV(ViewModelY, "ViewModelY");
		RV(ViewModelZ, "ViewModelZ");
		RV(Aspect, "Aspect");
		RV(AspectRation, "Aspect Ration");
		RV(FakeLag, "FakeLag");
		RV(FakeLagType, "FakeLagType");
		RV(FakeLagStanding, "FakeLagStanding");
		RV(FakeLagMoving, "FakeLagMoving");
		RV(FakeLagUnducking, "FakeLagUnducking");
		RV(FakeLagBind, "FakeLagBind");

		RV(TextDamageInfo, "TextDamageInfo");
		RV(ColoredWalls, "ColoredWalls");
		RV(KnifeBot, "KnifeBot");
		RV(KnifeBotDistance, "KnifeBotDistance");
		RV(KnifeBotFilter, "KnifeBotFilter");
		RV(KnifeBotBind, "KnifeBotBind");
		RV(KnifeBotMode, "KnifeBotMode");
		
		RV(AutoBlock, "AutoBlock");
		RV(AutoBlockBind, "AutoBlockBind");

		ADD_LOG("Setup: CMisc sucessful\n");
	}
};