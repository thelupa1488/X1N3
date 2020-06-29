#pragma once
#include "../Main.h"
#include "../Include/Def.h"
#include "../Initialize/Offsets.h"
#include "SDK/SDK.h"
#include "Entity.h"
#include "Weapon.h"
#include "EntityMem.h"

#define  lol(s) string(XorStr(s))

#define M_WEAPON_DEAGLE_STR		lol("Deagle")		
#define M_WEAPON_ELITE_STR		lol("Elite")		
#define M_WEAPON_FIVESEVEN_STR  lol("Five-Seven")			
#define M_WEAPON_GLOCK_STR		lol("Glock-18")		
#define M_WEAPON_TASER_STR		lol("Taser")	
#define M_WEAPON_HKP2000_STR	lol("P2000")		
#define M_WEAPON_P250_STR		lol("P250")			
#define M_WEAPON_USP_S_STR		lol("USP-S")		
#define M_WEAPON_CZ75A_STR		lol("CZ-75")			
#define M_WEAPON_REVOLVER_STR	lol("R8 Revolver")		
#define M_WEAPON_TEC9_STR		lol("Tec-9")		
#define M_WEAPON_AK47_STR		lol("AK-47")		
#define M_WEAPON_AUG_STR		lol("AUG")			
#define M_WEAPON_FAMAS_STR		lol("Famas")				
#define M_WEAPON_GALILAR_STR	lol("Galilar")	
#define M_WEAPON_M249_STR		lol("M249")			
#define M_WEAPON_M4A4_STR		lol("M4A4")			
#define M_WEAPON_M4A1_S_STR		lol("M4A1-S")	
#define M_WEAPON_MAC10_STR		lol("MAC-10")		
#define M_WEAPON_P90_STR		lol("P90")				
#define M_WEAPON_UMP45_STR		lol("UMP-45")				
#define M_WEAPON_MP5_STR		lol("MP5-SD")	
#define M_WEAPON_XM1014_STR		lol("XM1014")			
#define M_WEAPON_BIZON_STR		lol("Bizon")				
#define M_WEAPON_MAG7_STR		lol("MAG-7")				
#define M_WEAPON_NEGEV_STR		lol("Negev")	
#define M_WEAPON_SAWEDOFF_STR	lol("Sawed-Off")			
#define M_WEAPON_MP7_STR		lol("MP7")			
#define M_WEAPON_MP9_STR		lol("MP9")			
#define M_WEAPON_NOVA_STR		lol("Nova")				
#define M_WEAPON_SG553_STR		lol("SG 553")		
#define M_WEAPON_G3SG1_STR		lol("G3SG1")		
#define M_WEAPON_SCAR20_STR		lol("SCAR-20")			
#define M_WEAPON_AWP_STR		lol("AWP")			
#define M_WEAPON_SSG08_STR		lol("SSG 08")	

namespace SDK
{
	class IClientEntity;
}

using namespace SDK;

class CBind
{
private:
	bool IsDown = false;
	bool IsClicked = false;
	bool Ret = false;
public:
	bool Enable = false;
	bool Hold = false;
	int Button = 0;


	CBind(int _Button, bool _Enable = false, bool _Hold = false)
	{
		Button = _Button;
		Hold = _Hold;
		Enable = _Enable;
	}

	bool Check(bool full = false)
	{
		if (!Enable)
			return !full;

		if (Hold)
			return FastCall::G().t_GetAsyncKeyState(Button);

		if (FastCall::G().t_GetAsyncKeyState(Button))
		{
			IsClicked = false;
			IsDown = true;
		}
		else if (!FastCall::G().t_GetAsyncKeyState(Button) && IsDown)
		{
			IsClicked = true;
			IsDown = false;
		}
		else
		{
			IsClicked = false;
			IsDown = false;
		}

		if (IsClicked)
			Ret = !Ret;

		return Ret;
	}
};

namespace Engine
{
	class CBaseWeapon;
	class CBaseEntity;
	enum WEAPON_TYPE;
	enum WEAPON_ID;
}

using namespace Engine;

void ReadConfigs(LPCTSTR lpszFileName);

class CGlobal
{
public:

	static WEAPON_TYPE GWeaponType;
	static WEAPON_ID GWeaponID;
	static bool IsGuiVisble;
	static bool IsGameReady;
	static int iScreenWidth;
	static int iScreenHeight;
	static string SystemDisk;
	static float GFovView;
	static float GFovViewExt;
	static bool FullUpdateCheck;
	static Vector GViewAngle;
	static vector<string> ConfigList;
	static CBaseEntity* LocalPlayer;
	static CUserCmd* UserCmd;

	static ConVar* viewmodel_offset_convar_x;
	static ConVar* viewmodel_offset_convar_y;
	static ConVar* viewmodel_offset_convar_z;
	static int old_viewmodel_offset_x;
	static int old_viewmodel_offset_y;
	static int old_viewmodel_offset_z;

	static string WeaponNames[34];

	static WEAPON_TYPE GetWeaponType(CBaseWeapon* pWeaponEntity);

	static int WeaponItemIndex[34];

	typedef void(*LPSEARCHFUNC)(LPCTSTR lpszFileName);

	static BOOL SearchFiles(LPCTSTR lpszFileName, LPSEARCHFUNC lpSearchFunc, BOOL bInnerFolders)
	{
		LPTSTR part;
		char tmp[MAX_PATH];
		char name[MAX_PATH];

		HANDLE hSearch = NULL;
		WIN32_FIND_DATA wfd;
		memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

		if (bInnerFolders)
		{
			if (FastCall::G().t_GetFullPathNameA(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
			strcpy(name, part);
			strcpy(part, XorStr("*.*"));
			wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			if (!((hSearch = FastCall::G().t_FindFirstFileA(tmp, &wfd)) == INVALID_HANDLE_VALUE))
				do
				{
					if (!strncmp(wfd.cFileName, XorStr("."), 1) || !strncmp(wfd.cFileName, XorStr(".."), 2))
						continue;

					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						char next[MAX_PATH];
						if (FastCall::G().t_GetFullPathNameA(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
						strcpy(part, wfd.cFileName);
						strcat(next, XorStr("\\"));
						strcat(next, name);

						SearchFiles(next, lpSearchFunc, TRUE);
					}
				} while (FastCall::G().t_FindNextFileA(hSearch, &wfd));
				FastCall::G().t_FindClose(hSearch);
		}

		if ((hSearch = FastCall::G().t_FindFirstFileA(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
			return TRUE;
		do
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				char file[MAX_PATH];
				if (FastCall::G().t_GetFullPathNameA(lpszFileName, MAX_PATH, file, &part) == 0)
				{
					FastCall::G().t_FindClose(hSearch);
					return FALSE;
				}
				strcpy(part, wfd.cFileName);

				lpSearchFunc(wfd.cFileName);
			}
		while (FastCall::G().t_FindNextFileA(hSearch, &wfd));
		FastCall::G().t_FindClose(hSearch);
		return TRUE;
	}

	static void RefreshConfigs()
	{
		ConfigList.clear();
		string ConfigDir = SystemDisk + XorStr("X1N3\\Configurations\\*.json");

		SearchFiles(ConfigDir.c_str(), ReadConfigs, FALSE);
	}

	static int GetWeaponSettingsSelectID(int GameIndex)
	{
		for (size_t i = 0; i < 34; i++)
		{
			if (WeaponItemIndex[i] == GameIndex)
				return i;
		}

		return -1;
	}

	static int GetWeaponId();

	static bool LineGoesThroughSmoke(Vector vStartPos, Vector vEndPos)
	{
		static auto LineGoesThroughSmokeFn = (bool(*)(Vector vStartPos, Vector vEndPos))Utils::PatternScan(clientFactory, XorStr("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
		return LineGoesThroughSmokeFn(vStartPos, vEndPos);
	}

	static void ClampAngles(Vector& v)
	{
		if (v.x > 89.0f && v.x <= 180.0f)
			v.x = 89.0f;

		if (v.x > 180.0f)
			v.x = v.x - 360.0f;

		if (v.x < -89.0f)
			v.x = -89.0f;

		v.y = fmodf(v.y + 180, 360) - 180;

		v.z = 0;
	}

	static void AngleNormalize(Vector& vAngles)
	{
		if (vAngles.x > 89.0f && vAngles.x <= 180.0f)
			vAngles.x = 89.0f;
		while (vAngles.x > 180.f)
			vAngles.x -= 360.f;
		while (vAngles.x < -89.0f)
			vAngles.x = -89.0f;
		while (vAngles.y > 180.f)
			vAngles.y -= 360.f;
		while (vAngles.y < -180.f)
			vAngles.y += 360.f;
		vAngles.z = 0;
	}

	static Vector CalcDir(const Vector& vAngles)
	{
		Vector vForward;
		float	sp, sy, cp, cy;

		sy = sin(DEG2RAD(vAngles[1]));
		cy = cos(DEG2RAD(vAngles[1]));

		sp = sin(DEG2RAD(vAngles[0]));
		cp = cos(DEG2RAD(vAngles[0]));

		vForward.x = cp * cy;
		vForward.y = cp * sy;
		vForward.z = -sp;

		return vForward;
	}

	static void CorrectMouse(CUserCmd* cmd)
	{
		static ConVar* m_yaw = m_yaw = I::GetConVar()->FindVar(XorStr("m_yaw"));
		static ConVar* m_pitch = m_pitch = I::GetConVar()->FindVar(XorStr("m_pitch"));
		static ConVar* sensitivity = I::GetConVar()->FindVar(XorStr("sensitivity"));

		static QAngle m_angOldViewangles = I::ClientState()->viewangles;

		float delta_x = std::remainderf(cmd->viewangles.x - m_angOldViewangles.x, 360.0f);
		float delta_y = std::remainderf(cmd->viewangles.y - m_angOldViewangles.y, 360.0f);

		if (delta_x != 0.0f) {
			float mouse_y = -((delta_x / m_pitch->GetFloat()) / sensitivity->GetFloat());
			short mousedy;
			if (mouse_y <= 32767.0f) {
				if (mouse_y >= -32768.0f) {
					if (mouse_y >= 1.0f || mouse_y < 0.0f) {
						if (mouse_y <= -1.0f || mouse_y > 0.0f)
							mousedy = static_cast<short>(mouse_y);
						else
							mousedy = -1;
					}
					else {
						mousedy = 1;
					}
				}
				else {
					mousedy = 0x8000u;
				}
			}
			else {
				mousedy = 0x7FFF;
			}

			cmd->mousedy = mousedy;
		}

		if (delta_y != 0.0f) {
			float mouse_x = -((delta_y / m_yaw->GetFloat()) / sensitivity->GetFloat());
			short mousedx;
			if (mouse_x <= 32767.0f) {
				if (mouse_x >= -32768.0f) {
					if (mouse_x >= 1.0f || mouse_x < 0.0f) {
						if (mouse_x <= -1.0f || mouse_x > 0.0f)
							mousedx = static_cast<short>(mouse_x);
						else
							mousedx = -1;
					}
					else {
						mousedx = 1;
					}
				}
				else {
					mousedx = 0x8000u;
				}
			}
			else {
				mousedx = 0x7FFF;
			}

			cmd->mousedx = mousedx;
		}
	}

	static float AngleDiff(float destAngle, float srcAngle) 
	{
		float delta;

		delta = fmodf(destAngle - srcAngle, 360.0f);
		if (destAngle > srcAngle) {
			if (delta >= 180)
				delta -= 360;
		}
		else {
			if (delta <= -180)
				delta += 360;
		}
		return delta;
	}

	static bool WorldToScreen(const Vector& origin, Vector& screen)
	{
		auto LWorldToScreen = [&]()->bool
		{
			if (!origin.IsValid())
				return false;

			const auto screenTransform = [&origin, &screen]() -> bool
			{
				static std::uintptr_t pViewMatrix;
				if (!pViewMatrix)
				{
					pViewMatrix = static_cast<std::uintptr_t>(Utils::PatternScan(clientFactory, XorStr("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9")));
					pViewMatrix += 3;
					pViewMatrix = *reinterpret_cast<std::uintptr_t*>(pViewMatrix);
					pViewMatrix += 176;

					return true;
				}
				else
				{
					const VMatrix& w2sMatrix = *reinterpret_cast<VMatrix*>(pViewMatrix);
					screen.x = w2sMatrix.m[0][0] * origin.x + w2sMatrix.m[0][1] * origin.y + w2sMatrix.m[0][2] * origin.z + w2sMatrix.m[0][3];
					screen.y = w2sMatrix.m[1][0] * origin.x + w2sMatrix.m[1][1] * origin.y + w2sMatrix.m[1][2] * origin.z + w2sMatrix.m[1][3];
					screen.z = 0.0f;

					float w = w2sMatrix.m[3][0] * origin.x + w2sMatrix.m[3][1] * origin.y + w2sMatrix.m[3][2] * origin.z + w2sMatrix.m[3][3];

					if (w < 0.001f)
					{
						screen.x *= 100000;
						screen.y *= 100000;
						return true;
					}

					float invw = 1.f / w;
					screen.x *= invw;
					screen.y *= invw;

					return false;
				}
			};

			if (!screenTransform())
			{
				screen.x = (iScreenWidth * 0.5f) + (screen.x * iScreenWidth) * 0.5f;
				screen.y = (iScreenHeight * 0.5f) - (screen.y * iScreenHeight) * 0.5f;

				return true;
			}

			return false;
		};
		return LWorldToScreen();
	}

	static string FindSkinURl(string paintName, string weapon)
	{
		ifstream inFile;
		inFile.open(XorStr(".\\csgo\\scripts\\items\\items_game_cdn.txt"));
		string line;

		unsigned int curLine = 0;
		string search = paintName.append("=");

		while (getline(inFile, line)) {
			curLine++;
			if (line.find(search, 0) != string::npos) {
				if (line.find(weapon, 0) != string::npos)
				{
					return line.substr(line.find(search)).erase(0, search.length());
				}
			}
		}
		return XorStr("nf");
	}

	static string DownloadSkinBytes(const char* const szUrl)
	{
		HINTERNET hOpen = NULL;
		HINTERNET hFile = NULL;
		char* lpBuffer = NULL;
		DWORD dwBytesRead = 0;
		//Pointer to dynamic buffer.
		char* data = 0;
		//Dynamic data size.
		DWORD dataSize = 0;

		hOpen = InternetOpenA("", NULL, NULL, NULL, NULL);
		if (!hOpen) return (char*)"";

		hFile = InternetOpenUrlA(hOpen, szUrl, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, NULL);

		if (!hFile) {
			InternetCloseHandle(hOpen);
			return (char*)"";
		}

		string output;
		do {
			char buffer[2000];
			InternetReadFile(hFile, (LPVOID)buffer, _countof(buffer), &dwBytesRead);
			output.append(buffer, dwBytesRead);
		} while (dwBytesRead);

		InternetCloseHandle(hFile);
		InternetCloseHandle(hOpen);

		return output;
	}
};

