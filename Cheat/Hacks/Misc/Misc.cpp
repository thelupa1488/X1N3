#include "Misc.h"
#include  "../Setup.h"
#include "../../GUI/Gui.h"
#include "../../Engine/EnginePrediction.h"

//#define KEY_DOWN(VK_NNM) ((FastCall::G().t_GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)
#define KEY_DOWN(VK_NNM) (I::InputSystem()->IsButtonDown(VK_NNM))

int max_choke_ticks = 14;
float side = 1.0f;
CCSGOPlayerAnimState g_AnimState;
bool broke_lby = false;
float next_lby = 0.0f;
float vangle;

using namespace HookTables;

void CMisc::Draw()
{
	if (Enable)
	{
		if (CGlobal::LocalPlayer)
		{
			CBaseWeapon* pWeapon = CGlobal::LocalPlayer->GetBaseWeapon();

			if (pWeapon)
			{
				if (Crosshair)
				{
					if (CGlobal::GWeaponType != WEAPON_TYPE_SNIPER)
					{
						float punch_x = !CrosshairRecoil ? (CGlobal::iScreenWidth / 2.f) : 
							((CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().y * 0.9)));
						float punch_y = !CrosshairRecoil ? (CGlobal::iScreenHeight / 2.f) :
							((CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().x * 0.9)));

						switch (CrosshairStyle)
						{
						case 0:
						{
							GP_Render->DrawFilledBox(punch_x - CrosshairSize / 2, punch_y - CrosshairSize / 2, CrosshairSize, CrosshairSize, CrosshairColor);
							if (CrosshairOutline)
								GP_Render->DrawBox((punch_x - CrosshairSize / 2) - 1, (punch_y - CrosshairSize / 2) - 1, CrosshairSize + 1, CrosshairSize + 1, 1, Color::Black());
							break;
						}
						case 1:
						{
							GP_Render->DrawLine(punch_x - CrosshairSize, punch_y, punch_x + CrosshairSize + 1, punch_y, CrosshairColor);
							GP_Render->DrawLine(punch_x, punch_y - CrosshairSize, punch_x, punch_y + CrosshairSize + 1, CrosshairColor);

							if (CrosshairOutline)
							{
								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x, punch_y - 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y - 1, Color::Black());

								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y + 1, punch_x, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y + 1, punch_x + CrosshairSize + 1, punch_y + 1, Color::Black());

								GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x - CrosshairSize - 1, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + CrosshairSize + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y + 2, Color::Black());


								GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x - 1, punch_y - 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - 1, Color::Black());

								GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x - 1, punch_y + 1, Color::Black());
								GP_Render->DrawLine(punch_x + 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + 1, Color::Black());

								GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + CrosshairSize + 1, Color::Black());
								GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - CrosshairSize - 1, Color::Black());

							}
							break;
						}
						case 2:
						{
							auto lineSize = CrosshairSize;
							int screenCenterX = punch_x;
							int screenCenterY = punch_y;
							GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), CrosshairColor);
							GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), CrosshairColor);
							break;
						}
						default:
							break;
						}
					}
				}

				if (SnipCrosshair)
				{
					if (CGlobal::GWeaponType == WEAPON_TYPE_SNIPER && CGlobal::GWeaponID != WEAPON_AUG && CGlobal::GWeaponID != WEAPON_SG553)
					{
						CBaseWeapon* Wep = CGlobal::LocalPlayer->GetBaseWeapon();
						if (Wep)
						{
							if (Wep->GetZoomLevel() != 1 && Wep->GetZoomLevel() != 2)
							{
								float punch_x = !SnipCrosshairRecoil ? (CGlobal::iScreenWidth / 2.f) :
									((CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().y * 0.9)));
								float punch_y = !SnipCrosshairRecoil ? (CGlobal::iScreenHeight / 2.f) :
									((CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().x * 0.9)));

								switch (SnipCrosshairStyle)
								{
								case 0:
								{
									GP_Render->DrawFilledBox(punch_x - CrosshairSize / 2, punch_y - CrosshairSize / 2, CrosshairSize, CrosshairSize, SnipCrosshairColor);
									if (SnipCrosshairOutline)
										GP_Render->DrawBox((punch_x - CrosshairSize / 2) - 1, (punch_y - CrosshairSize / 2) - 1, CrosshairSize + 1, CrosshairSize + 1, 1, Color::Black());
									break;
								}
								case 1:
								{
									GP_Render->DrawLine(punch_x - CrosshairSize, punch_y, punch_x + CrosshairSize + 1, punch_y, SnipCrosshairColor);
									GP_Render->DrawLine(punch_x, punch_y - CrosshairSize, punch_x, punch_y + CrosshairSize + 1, SnipCrosshairColor);

									if (SnipCrosshairOutline)
									{
										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x, punch_y - 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y - 1, Color::Black());

										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y + 1, punch_x, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y + 1, punch_x + CrosshairSize + 1, punch_y + 1, Color::Black());

										GP_Render->DrawLine(punch_x - CrosshairSize - 1, punch_y - 1, punch_x - CrosshairSize - 1, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + CrosshairSize + 1, punch_y - 1, punch_x + CrosshairSize + 1, punch_y + 2, Color::Black());


										GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x - 1, punch_y - 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - 1, Color::Black());

										GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x - 1, punch_y + 1, Color::Black());
										GP_Render->DrawLine(punch_x + 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + 1, Color::Black());

										GP_Render->DrawLine(punch_x - 1, punch_y + CrosshairSize + 1, punch_x + 1, punch_y + CrosshairSize + 1, Color::Black());
										GP_Render->DrawLine(punch_x - 1, punch_y - CrosshairSize - 1, punch_x + 1, punch_y - CrosshairSize - 1, Color::Black());
									}
									break;
								}
								case 2:
								{
									auto lineSize = SnipCrosshairSize;
									int screenCenterX = punch_x;
									int screenCenterY = punch_y;
									GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), SnipCrosshairColor);
									GP_Render->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), SnipCrosshairColor);
									break;
								}
								default:
									break;
								}
							}
						}
					}
				}

				if (SpreadCircel)
				{
					WEAPON_TYPE WeapType = CGlobal::GWeaponType;

					if (!CGlobal::LocalPlayer->IsDead() &&
						WeapType != WEAPON_TYPE_GRENADE &&
						WeapType != WEAPON_TYPE_KNIFE &&
						WeapType != WEAPON_TYPE_C4 &&
						WeapType != WEAPON_TYPE_UNKNOWN)
					{
						GP_Render->DrawRing(
							(CGlobal::iScreenWidth / 2) - (int)((CGlobal::iScreenWidth / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().y * 0.9)),
							(CGlobal::iScreenHeight / 2) + (int)((CGlobal::iScreenHeight / CGlobal::GFovView) * (CGlobal::LocalPlayer->GetAimPunchAngle().x * 0.9)),
							pWeapon->GetInaccuracy() * 550.f, 42, SpreadColor);
					}
				}

				if (Desync)
				{
					if (DesyncArrows)
					{
						auto client_viewangles = QAngle();
						I::Engine()->GetViewAngles(client_viewangles);
						const auto screen_center = Vector2D(CGlobal::iScreenWidth / 2, CGlobal::iScreenHeight / 2);

						constexpr auto radius = 225.f;
						auto DrawArrow = [&](float rot, Color color) -> void
						{
							vector<Vec2> vertices;
							vertices.push_back((Vec2(screen_center.x + cosf(rot) * radius, screen_center.y + sinf(rot) * radius)));
							vertices.push_back((Vec2(screen_center.x + cosf(rot + DEG2RAD(2)) * (radius - 6), screen_center.y + sinf(rot + DEG2RAD(2)) * (radius - 6)))); //25
							vertices.push_back((Vec2(screen_center.x + cosf(rot - DEG2RAD(2)) * (radius - 6), screen_center.y + sinf(rot - DEG2RAD(2)) * (radius - 6)))); //25

							GP_Render->RenderTriangle(vertices.at(0), vertices.at(1), vertices.at(2), ArrowsColor, 2.f);
						};

						static auto alpha = 0.f; 
						static auto plus_or_minus = false;
						if (alpha <= 0.f || alpha >= 255.f) plus_or_minus = !plus_or_minus;
						alpha += plus_or_minus ? (255.f / 7 * 0.015) : -(255.f / 7 * 0.015); alpha = clamp(alpha, 0.f, 255.f);

						const auto FakeRot = DEG2RAD((side < 0.0f ? 90 : -90) - 90);
						DrawArrow(FakeRot, ArrowsColor);
					}
			
					//if (AngleLines && ThirdPersonBind.Check())
					//{
					//	auto DrawAngleLines = [&](const Vector& origin, const Vector& w2sOrigin, const float& angle, const char* text, Color clr)
					//	{
					//		Vector forward;
					//		AngleVectors(QAngle(0.f, angle, 0.f), forward);
					//		float AngleLinesLength = 30.0f;

					//		Vector w2sReal;
					//		if (CGlobal::WorldToScreen(origin + forward * AngleLinesLength, w2sReal))
					//		{
					//			GP_Render->DrawLine(w2sOrigin.x, w2sOrigin.y, w2sReal.x, w2sReal.y, Color::White(), 1.0f);
					//			GP_Render->DrawString(w2sReal.x, w2sReal.y /* - 5.0f, 14.f*/, clr, true, true, text);
					//		}
					//	};

					//	if (!CGlobal::LocalPlayer || !CGlobal::LocalPlayer->GetBasePlayerAnimState())
					//		return;

					//	if (CGlobal::LocalPlayer->IsDead())
					//		return;

					//	Vector w2sOrigin;
					//	if (CGlobal::WorldToScreen(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin))
					//	{
					//		static float view;
					//		if (CGlobal::bSendPacket)
					//			view = CGlobal::UserCmd->viewangles.y;

					//		DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, CGlobal::FakeAngle, "fake", Color::Orange());
					//		DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, CGlobal::LocalPlayer->GetLowerBodyYawTarget(), "lby", Color::Blue());
					//		DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, CGlobal::RealAngle, "real", Color::Green());
					//		DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, view, "view", Color::Red());
					//	}
					//}
				}

				Night();
				CustomWalls();
			}
		}

		HitWorker.Draw();
	}
}

void CMisc::SetNewClan(string New, string Name)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)CSX::Memory::FindPatternV2(XorStr("engine.dll"), XorStr("53 56 57 8B DA 8B F9 FF 15"))));

	if (pSetClanTag)
		pSetClanTag(New.c_str(), Name.c_str());
}

static int LagCompBreak()
{
	if (!CGlobal::LocalPlayer || CGlobal::LocalPlayer->IsDead())
		return 1;

	auto velocity = CGlobal::LocalPlayer->GetVelocity();
	velocity.z = 0.f;
	auto speed = velocity.Length();
	auto distance_per_tick = speed * I::GlobalVars()->interval_per_tick;
	int choked_ticks = ceilf(64.f / distance_per_tick);
	return min<int>(choked_ticks, 14.f);
}

//static void updatelby(CCSGOPlayerAnimState* animstate)
//{
//	if (animstate->speed_2d > 0.1f || fabsf(animstate->flUpVelocity)) {
//		next_lby = I::GlobalVars()->curtime + 0.22f;
//	}
//	else if (I::GlobalVars()->curtime > next_lby) {
//		if (fabsf(CGlobal::AngleDiff(animstate->m_flGoalFeetYaw, animstate->m_flEyeYaw)) > 35.0f) {
//			next_lby = I::GlobalVars()->curtime + 1.1f;
//		}
//	}
//}

void CMisc::CreateMove(bool& bSendPacket, float flInputSampleTime, CUserCmd* pCmd)
{
	ConVar* cl_righthand = I::GetConVar()->FindVar(XorStr("cl_righthand"));

	if (CGlobal::LocalPlayer && CGlobal::IsGameReady)
	{
		if (CGlobal::LocalPlayer->GetBaseWeapon())
		{
			CGlobal::GWeaponType = CGlobal::GetWeaponType(CGlobal::LocalPlayer->GetBaseWeapon());
			if (CGlobal::LocalPlayer->GetBaseWeapon()->GeteAttributableItem())
				CGlobal::GWeaponID = (WEAPON_ID)*CGlobal::LocalPlayer->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex();
		}
	}
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (CGlobal::LocalPlayer)
		{
			if (BHop)
			{
				if (CGlobal::LocalPlayer->GetMoveType() & MOVETYPE_LADDER ||
					CGlobal::LocalPlayer->GetMoveType() & MOVETYPE_NOCLIP)
					return;

				if (!CGlobal::LocalPlayer->IsDead())
				{
					if (pCmd->buttons & IN_JUMP && !(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						static bool bLastJumped = false;
						static bool bShouldFake = false;

						if (!bLastJumped && bShouldFake)
						{
							bShouldFake = false;
							pCmd->buttons |= IN_JUMP;
						}
						else if (pCmd->buttons & IN_JUMP)
						{
							if (CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND)
							{
								bLastJumped = true;
								bShouldFake = true;
							}
							else if (rand() % 100 < BHopChance)
							{
								pCmd->buttons &= ~IN_JUMP;
								bLastJumped = false;
							}
						}
						else
						{
							bLastJumped = false;
							bShouldFake = false;
						}
					}
					if (AutoStrafe && !(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						if (!KEY_DOWN(ButtonCode_t::KEY_SPACE) ||
							KEY_DOWN(ButtonCode_t::KEY_A) ||
							KEY_DOWN(ButtonCode_t::KEY_D) ||
							KEY_DOWN(ButtonCode_t::KEY_S) ||
							KEY_DOWN(ButtonCode_t::KEY_W))
							return;

						bool on_ground = (CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND) && !(pCmd->buttons & IN_JUMP);
						if (on_ground) {
							return;
						}

						static auto side = 1.0f;
						side = -side;

						auto velocity = CGlobal::LocalPlayer->GetVelocity();
						velocity.z = 0.0f;

						QAngle wish_angle = pCmd->viewangles;

						auto speed = velocity.Length2D();
						auto ideal_strafe = clamp(RAD2DEG(atan(15.f / speed)), 0.0f, 90.0f);

						if (pCmd->forwardmove > 0.0f)
							pCmd->forwardmove = 0.0f;

						static auto cl_sidespeed = I::GetConVar()->FindVar("cl_sidespeed");

						static float old_yaw = 0.f;
						auto yaw_delta = remainderf(wish_angle.y - old_yaw, 360.0f);
						auto abs_angle_delta = abs(yaw_delta);
						old_yaw = wish_angle.y;

						if (abs_angle_delta <= ideal_strafe || abs_angle_delta >= 30.0f) {
							QAngle velocity_direction;
							VectorAngles(velocity, velocity_direction);
							auto velocity_delta = remainderf(wish_angle.y - velocity_direction.y, 360.0f);
							auto retrack = clamp(RAD2DEG(atan(30.0f / speed)), 0.0f, 90.0f) * AutoStrafeSpeed;
							if (velocity_delta <= retrack || speed <= 15.0f) {
								if (-(retrack) <= velocity_delta || speed <= 15.0f) {
									wish_angle.y += side * ideal_strafe;
									pCmd->sidemove = cl_sidespeed->GetFloat() * side;
								}
								else {
									wish_angle.y = velocity_direction.y - retrack;
									pCmd->sidemove = cl_sidespeed->GetFloat();
								}
							}
							else {
								wish_angle.y = velocity_direction.y + retrack;
								pCmd->sidemove = -cl_sidespeed->GetFloat();
							}

							MovementFix(pCmd, wish_angle, pCmd->viewangles);
						}
						else if (yaw_delta > 0.0f) {
							pCmd->sidemove = -cl_sidespeed->GetFloat();
						}
						else if (yaw_delta < 0.0f) {
							pCmd->sidemove = cl_sidespeed->GetFloat();
						}
					}
				}
			}
			if (LeftHandKnife)
			{
				if (CGlobal::LocalPlayer && CGlobal::GWeaponType == WEAPON_TYPE_KNIFE)
				{
					cl_righthand->SetValue(0);
				}
				else
				{
					cl_righthand->SetValue(1);
				}
			}
			if (!LeftHandKnife)
			{
				cl_righthand->SetValue(1);
			}

			if (InfiniteCrouch)
			{
				if (!CGlobal::LocalPlayer->IsDead())
				{
					pCmd->buttons |= IN_BULLRUSH;
				}
			}

			static bool NoFlashReset = false;
			if (AntiFlash)
			{
				float* maxAlpha = CGlobal::LocalPlayer->GetFlashMaxAlpha();
				if (maxAlpha)
					*maxAlpha = (float)AntiFlashAlpha;

				NoFlashReset = true;
			}
			if (!AntiFlash && NoFlashReset)
			{
				float* maxAlpha = CGlobal::LocalPlayer->GetFlashMaxAlpha();
				if (maxAlpha)
					*maxAlpha = 255.f;
				NoFlashReset = false;
			}

			vector<const char*> smoke_materials =
			{
				"particle/vistasmokev1/vistasmokev1_smokegrenade",
				"particle/vistasmokev1/vistasmokev1_emods",
				"particle/vistasmokev1/vistasmokev1_emods_impactdust",
				"particle/vistasmokev1/vistasmokev1_fire",
			};
			static auto smoke_count = *reinterpret_cast<uint32_t**>(CSX::Memory::FindSignature(clientFactory, XorStr("A3 ? ? ? ? 57 8B CB")) + 1);
			static bool NoSmokeReset = false;
			if (NoSmoke)
			{
				for (auto mat : smoke_materials)
				{
					auto material = I::MaterialSystem()->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS);
					material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
					if (NoSmoke)
						*(int*)smoke_count = 0;
				}
				NoSmokeReset = true;
			}
			if (!NoSmoke && NoSmokeReset)
			{
				for (auto mat : smoke_materials)
				{
					auto material = I::MaterialSystem()->FindMaterial(mat, TEXTURE_GROUP_CLIENT_EFFECTS);
					material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
					if (!NoSmoke && NoSmokeReset)
						*(int*)smoke_count = 1;
				}
				NoSmokeReset = false;
			}

			static bool ClanTagReset = false;
			if (ClanTagChanger)
			{
				static string OldClan = "";
				string NewClan = ClanTagChangerText;

				switch (ClanTagChangerStyle)
				{
				case 0: NewClan = XorStr("X1N3 > All"); break;
				case 1: NewClan = XorStr("[VALV\xE1\xB4\xB1]"); break;
				case 2:
				{
					switch (int((float)CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick) % 10)
					{
					case 0: NewClan = XorStr("-----"); break;
					case 1: NewClan = XorStr("----X"); break;
					case 2: NewClan = XorStr("---X1"); break;
					case 3: NewClan = XorStr("--X1N"); break;
					case 4: NewClan = XorStr("-X1N3"); break;
					case 5: NewClan = XorStr("X1N3-"); break;
					case 6: NewClan = XorStr("1N3--"); break;
					case 7: NewClan = XorStr("N3---"); break;
					case 8: NewClan = XorStr("3----"); break;
					case 9: NewClan = XorStr("-----"); break;
					}
					break;
				}
				case 3:
				{
					switch (int((float)CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick) % 15)
					{
					case 0: NewClan = XorStr("-------"); break;
					case 1: NewClan = XorStr("------T"); break;
					case 2: NewClan = XorStr("-----TH"); break;
					case 3: NewClan = XorStr("----THE"); break;
					case 4: NewClan = XorStr("---THEL"); break;
					case 5: NewClan = XorStr("--THELU"); break;
					case 6: NewClan = XorStr("-THELUP"); break;
					case 7: NewClan = XorStr("THELUPA"); break;
					case 8: NewClan = XorStr("HELUPA-"); break;
					case 9: NewClan = XorStr("ELUPA--"); break;
					case 10: NewClan = XorStr("LUPA---"); break;
					case 11: NewClan = XorStr("UPA----"); break;
					case 12: NewClan = XorStr("PA-----"); break;
					case 13: NewClan = XorStr("A------"); break;
					case 14: NewClan = XorStr("-------"); break;
					}
					break;
				}
				default: break;
				}

				if (OldClan != NewClan)
					SetNewClan(NewClan, NewClan);

				OldClan = NewClan;
				ClanTagReset = true;
			}
			if (!ClanTagChanger && ClanTagReset)
			{
				SetNewClan("", "");
				ClanTagReset = false;
			}

			if (ChatSpam && ChatSpamStart)
			{
				vector<string> chatspam;

				switch (ChatSpamStyle)
				{
				case 0: chatspam = { XorStr("X1N3") }; break;
				case 1: chatspam = { ChatSpamText }; break;
				default:break;
				}

				static DWORD lastspammed = 0;
				if (FastCall::G().t_GetTickCount64() - lastspammed > 800)
				{
					lastspammed = (DWORD)FastCall::G().t_GetTickCount64();
					auto say = XorStr("say ");
					string msg = say + chatspam[rand() % chatspam.size()];
					I::Engine()->ExecuteClientCmd(msg.c_str());
				}
			}

			if (RadioSpam && RadioSpamStart)
			{
				vector<string> RadioSpam = { "coverme" , "takepoint" , "holdpos", "regroup", "followme",
					"takingfire", "go", "fallback", "sticktog",
					"report", "roger", "enemyspot", "needbackup",
					"sectorclear", "inposition", "reportingin",
					"getout", "negative", "enemydown" };

				static DWORD lastspammed = 0;
				if (FastCall::G().t_GetTickCount64() - lastspammed > 800)
				{
					lastspammed = GetTickCount();
					string msg = RadioSpam[rand() % RadioSpam.size()];
					I::Engine()->ExecuteClientCmd(msg.c_str());
				}
			}
			static int ticks = 0;

			CGlobal::viewmodel_offset_convar_x = I::GetConVar()->FindVar(XorStr("viewmodel_offset_x"));
			CGlobal::viewmodel_offset_convar_y = I::GetConVar()->FindVar(XorStr("viewmodel_offset_y"));
			CGlobal::viewmodel_offset_convar_z = I::GetConVar()->FindVar(XorStr("viewmodel_offset_z"));
			*(int*)((DWORD)&CGlobal::viewmodel_offset_convar_x->fnChangeCallback + 0xC) = NULL;
			*(int*)((DWORD)&CGlobal::viewmodel_offset_convar_y->fnChangeCallback + 0xC) = NULL;
			*(int*)((DWORD)&CGlobal::viewmodel_offset_convar_z->fnChangeCallback + 0xC) = NULL;
			CGlobal::old_viewmodel_offset_x = -CGlobal::viewmodel_offset_convar_x->GetFloat();
			CGlobal::old_viewmodel_offset_y = -CGlobal::viewmodel_offset_convar_y->GetFloat();
			CGlobal::old_viewmodel_offset_z = -CGlobal::viewmodel_offset_convar_z->GetFloat();

			if (ViewModelXYZ)
			{
				CGlobal::viewmodel_offset_convar_x->SetValue(ViewModelX);
				CGlobal::viewmodel_offset_convar_y->SetValue(ViewModelY);
				CGlobal::viewmodel_offset_convar_z->SetValue(ViewModelZ);
			}
			else
			{
				CGlobal::viewmodel_offset_convar_x->SetValue(-CGlobal::old_viewmodel_offset_x);
				CGlobal::viewmodel_offset_convar_y->SetValue(-CGlobal::old_viewmodel_offset_y);
				CGlobal::viewmodel_offset_convar_z->SetValue(-CGlobal::old_viewmodel_offset_z);
			}

			if (FakeLag && FakeLagBind.Check())
			{
				static int choke_amount = 0;
				static int choked_amount = 0;

				//auto net_channel = I::Engine->GetNetChannel();
				if (/*!net_channel ||*/ !CGlobal::LocalPlayer || CGlobal::LocalPlayer->GetHealth() <= 0)
				{
					bSendPacket = true;
					return;
				}

				if (pCmd->buttons & IN_ATTACK || pCmd->buttons & IN_ATTACK2 || (CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND && pCmd->buttons & IN_JUMP))
				{
					bSendPacket = true;
					return;
				}

				if (!(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
				{
					switch (FakeLagType % 2)
					{
					case 0: choke_amount = FakeLagJumpingAmount; break;
					case 1: choke_amount = LagCompBreak(); break;
					}
				}
				else if (CGlobal::LocalPlayer->GetVelocity().Length2D() > 0)
				{
					switch (FakeLagType % 2)
					{
					case 0: choke_amount = FakeLagMovingAmount; break;
					case 1: choke_amount = LagCompBreak(); break;
					}
				}
				else if (CGlobal::LocalPlayer->GetVelocity().Length2D() == 0)
				{
					switch (FakeLagType % 2)
					{
					case 0: choke_amount = FakeLagStandingAmount; break;
					case 1: choke_amount = LagCompBreak(); break;
					}
				}
				else
				{
					bSendPacket = true;
					return;
				}

				bSendPacket = choked_amount >= min(14, choke_amount);

				if (/*net_channel->m_nChokedPackets*/ bSendPacket)
					choked_amount = 0;
				else
					++choked_amount;
			}

			if (KnifeBot && KnifeBotBind.Check())
			{
				if (CGlobal::GWeaponType == WEAPON_TYPE_KNIFE)
				{
					CBaseWeapon* pLocalWeapon = CGlobal::LocalPlayer->GetBaseWeapon();
					if (pLocalWeapon)
					{
						for (int EntIndex = 0; EntIndex < MAX_ENTITY_PLAYERS; EntIndex++)
						{
							CEntityPlayer* Entity = &GP_EntPlayers->EntityPlayer[EntIndex];

							if (!Entity->IsUpdated)
								continue;

							if (Entity->IsLocal)
								continue;

							if (!Entity->IsPlayer)
								continue;

							if (Entity->IsDead)
								continue;

							float Distance = Entity->Distance * 33;

							if (Distance > KnifeBotDistance)
								continue;

							if (KnifeBotFilter == 1)
							{
								if ((int)Entity->Team != CGlobal::LocalPlayer->GetTeam())
									continue;
							}
							else if (KnifeBotFilter == 2)
							{
								if ((int)Entity->Team == CGlobal::LocalPlayer->GetTeam())
									continue;
							}

							Vector OrignWorld = Entity->RenderOrigin;
							Vector OrignScreen;

							if (!CGlobal::WorldToScreen(OrignWorld, OrignScreen))
								continue;

							switch (KnifeBotMode)
							{
							case 0:
							{
								static int cur_attack = 0;

								if (Distance > 60.f)
									pCmd->buttons |= IN_ATTACK;
								else
								{
									if ((CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick) - pLocalWeapon->GetNextPrimaryAttack() > 0)
									{
										if (Entity->Armor > 0)
										{
											if (Entity->Health - 21 <= 0)
												pCmd->buttons |= IN_ATTACK;
											else
												pCmd->buttons |= IN_ATTACK2;
										}
										else
										{
											if (Entity->Health - 34 <= 0)
												pCmd->buttons |= IN_ATTACK;
											else
												pCmd->buttons |= IN_ATTACK2;
										}
									}

								}
								break;
							}
							case 1:
							{
								static int cur_attack = 0;

								if (Distance > 60.f)
								{
									pCmd->buttons |= IN_ATTACK;
									cur_attack = 1;
								}
								else
								{
									float TimeSinceFire = (CGlobal::LocalPlayer->GetTickBase() * I::GlobalVars()->interval_per_tick) - pLocalWeapon->GetNextPrimaryAttack();

									if (cur_attack > 0 && TimeSinceFire > 0)
									{
										pCmd->buttons |= IN_ATTACK2;
										TimeSinceFire = -1;
										cur_attack = 0;
									}

									if (cur_attack == 0 && TimeSinceFire > 0)
									{
										pCmd->buttons |= IN_ATTACK;
										cur_attack++;
									}
								}
								break;
							}
							case 2: pCmd->buttons |= IN_ATTACK2; break;
							case 3: pCmd->buttons |= IN_ATTACK; break;
							default: break;
							}
						}
					}
				}
			}

			auto unpred_flags = CGlobal::LocalPlayer->GetFlags();
			QAngle angleold = pCmd->viewangles;
			EnginePrediction::Begin(pCmd);
			{
				if (EdgeJump && EdgeJumpBind.Check())
				{
					if (CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_LADDER ||
						CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
						return;

					if ((unpred_flags & FL_ONGROUND) && !(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND))
						pCmd->buttons |= IN_JUMP;
				}

				if (Desync)
				{
					
					if (pCmd->buttons & (IN_ATTACK | IN_ATTACK2 | IN_USE) ||
						CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_LADDER || CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP
						|| CGlobal::LocalPlayer->IsDead())
						return;

					//	if (*g_GameRules && (*g_GameRules)->IsFreezePeriod())  //need fix sdk
					//	return;

					if (CGlobal::LocalPlayer->GetGunGameImmunity() || CGlobal::LocalPlayer->GetFlags() & FL_FROZEN)
						return;

					auto weapon = (CBaseWeapon*)CGlobal::LocalPlayer->GetActiveWeapon();

					if (!weapon)
						return;

					if ((CGlobal::GWeaponID == WEAPON_GLOCK || CGlobal::GWeaponID == WEAPON_FAMAS) && weapon->GetNextPrimaryAttack() >= I::GlobalVars()->curtime)
						return;

					if (CGlobal::GWeaponType == WEAPON_TYPE_GRENADE) 
					{
						return;
						//if (!weapon->GetPinPulled()) 
						//{
						//	float throwTime = weapon->GetThrowTime();
						//	if (throwTime > 0.f)
						//		return;
						//}

						//if ((pCmd->buttons & IN_ATTACK) || (pCmd->buttons & IN_ATTACK2)) {
						//	if (weapon->GetThrowTime() > 0.f)
						//		return;
						//}
					}

				//	auto sideauto = CGlobal::GetBestHeadAngle(vangle); //need fix

					if (DesyncBind.Check())
						side = 1.0f;
					else
						side = -1.0f;
				

					if (fabsf(CGlobal::LocalPlayer->GetSpawnTime() - I::GlobalVars()->curtime) > 1.0f)
					{
						if (DesyncType == 0) // static
						{
							float minimal_move = 2.0f;
							if (CGlobal::LocalPlayer->GetFlags() & FL_DUCKING)
								minimal_move *= 3.f;

							if (CGlobal::UserCmd->buttons & IN_WALK)
								minimal_move *= 3.f;

							bool should_move = CGlobal::LocalPlayer->GetVelocity().Length2D() <= 0.0f
								|| fabsf(CGlobal::LocalPlayer->GetVelocity().z) <= 100.0f;

							if ((pCmd->command_number % 2) == 1) {
								pCmd->viewangles.y += 120.0f * side;
								if (should_move)
									pCmd->sidemove -= minimal_move;
								CGlobal::bSendPacket = false;
							}
							else if (should_move) {
								pCmd->sidemove += minimal_move;
							}
						}
						else if (DesyncType == 1) // balance
						{
							if (next_lby >= I::GlobalVars()->curtime)
							{
								if (!broke_lby && CGlobal::bSendPacket && I::ClientState()->chokedcommands > 0)
									return;

								broke_lby = false;
								CGlobal::bSendPacket = false;
								pCmd->viewangles.y += 120.0f * side;
							}
							else
							{
								broke_lby = true;
								CGlobal::bSendPacket = false;
								pCmd->viewangles.y += 120.0f * -side;
							}
						}
						FixAngles(pCmd->viewangles);
						FixMovement(pCmd, angleold);
					}

					FixAngles(pCmd->viewangles);
					pCmd->viewangles.y = remainderf(pCmd->viewangles.y, 360.0f);

					if (I::ClientState()->chokedcommands >= max_choke_ticks) {
						CGlobal::bSendPacket = true;
						pCmd->viewangles = I::ClientState()->viewangles;
					}

					CGlobal::CorrectMouse(pCmd);

					auto anim_state = CGlobal::LocalPlayer->GetBasePlayerAnimState();
					if (anim_state) {
						auto anim_state_backup = *anim_state;
						*anim_state = g_AnimState;
						CGlobal::LocalPlayer->GetVAngles() = pCmd->viewangles;
						CGlobal::LocalPlayer->UpdateClientSideAnimation();

						if (anim_state->speed_2d > 0.1f || fabsf(anim_state->flUpVelocity)) {
							next_lby = I::GlobalVars()->curtime + 0.22f;
						}
						else if (I::GlobalVars()->curtime > next_lby)
						{
							if (fabsf(CGlobal::AngleDiff(anim_state->m_flGoalFeetYaw, anim_state->m_flEyeYaw)) > 35.0f) {
								next_lby = I::GlobalVars()->curtime + 1.1f;
							}
						}

						g_AnimState = *anim_state;
						*anim_state = anim_state_backup;
					}

					if (CGlobal::bSendPacket)
					{
						CGlobal::RealAngle = (pCmd->viewangles.x, g_AnimState.m_flGoalFeetYaw, 0);
						CGlobal::FakeAngle = (pCmd->viewangles.x, g_AnimState.m_flEyeYaw, 0);
						vangle = pCmd->viewangles.y;
					}

					FixAngles(pCmd->viewangles);				
				}

				if (AutoBlock && AutoBlockBind.Check())
				{			
					float bestdist = 250.f;
					int index = -1;

					for (int i = 1; i < I::Engine()->GetMaxClients(); i++)
					{
						CBaseEntity* entity = (CBaseEntity*)I::ClientEntityList()->GetClientEntity(i);

						if (!entity)
							continue;

						if (entity->IsDead() || entity->IsDormant() || entity == CGlobal::LocalPlayer)
							continue;

						float dist = CGlobal::LocalPlayer->GetOrigin().DistTo(entity->GetOrigin());

						if (dist < bestdist)
						{
							bestdist = dist;
							index = i;
						}
					}

					if (index == -1)
						return;

					CBaseEntity* target = (CBaseEntity*)I::ClientEntityList()->GetClientEntity(index);

					if (!target)
						return;

					QAngle angles = CalcAngle(CGlobal::LocalPlayer->GetOrigin(), target->GetOrigin());

					angles.y -= CGlobal::LocalPlayer->GetEyeAngles().y;
					NormalizeAngles(angles);

					if (angles.y < 0.0f)
						pCmd->sidemove = 250.f;
					else if (angles.y > 0.0f)
						pCmd->sidemove = -250.f;
				}
			}
			EnginePrediction::End();
		}
	}
}

void CMisc::OverrideView(CViewSetup* pSetup)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (!pSetup)
			return;

		if (CGlobal::LocalPlayer)
		{
			CGlobal::GFovViewExt = pSetup->fov;
			if (FovChanger)
			{
				if (CGlobal::LocalPlayer->IsDead())
				{
					if (CGlobal::LocalPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && CGlobal::LocalPlayer->GetObserverTarget())
						CGlobal::LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(CGlobal::LocalPlayer->GetObserverTarget());

					if (!CGlobal::LocalPlayer)
						return;
				}
				bool ChangeFov = true;
				CBaseWeapon* Wep = CGlobal::LocalPlayer->GetBaseWeapon();
				if (Wep)
				{
					if (((WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_AWP ||
						(WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_SSG08) &&
						(CGlobal::GFovViewExt == 90 || CGlobal::GFovViewExt == FovView) && !CGlobal::LocalPlayer->IsDead())
					{
						ChangeFov = true;
					}
					else
					{
						WEAPON_TYPE WeapType = CGlobal::GWeaponType;
						if ((WeapType != WEAPON_TYPE_GRENADE &&
							WeapType != WEAPON_TYPE_KNIFE) &&
							(Wep->GetZoomLevel() == 1 ||
								Wep->GetZoomLevel() == 2))
						{
							ChangeFov = false;
						}
					}
				}

				if (ChangeFov)
					pSetup->fov = (float)FovView;
			}

			if (NoVisualRecoil)
			{
				pSetup->angles.x -= ((CGlobal::LocalPlayer->GetViewPunchAngle().x * 2.f) * 0.45f);
				pSetup->angles.y -= ((CGlobal::LocalPlayer->GetViewPunchAngle().y * 2.f) * 0.45f);
			}

			if (FreeCam)
			{
				static Vector newOrigin;

				float freecamspeed = FreeCamSpeed;

				if (!FreeCamBind.Check())
				{
					newOrigin = pSetup->origin;
				}
				else
				{
					float fSpeed = freecamspeed; //5.f;
					if (KEY_DOWN(ButtonCode_t::KEY_LCONTROL))
						fSpeed = fSpeed * 0.45f;
					if (KEY_DOWN(ButtonCode_t::KEY_LSHIFT))
						fSpeed = fSpeed * 1.65f;
					if (KEY_DOWN(ButtonCode_t::KEY_W)) 		
						newOrigin += pSetup->angles.Forward() * fSpeed;
					if (KEY_DOWN(ButtonCode_t::KEY_A))	
						newOrigin += pSetup->angles.Right() * fSpeed;
					if (KEY_DOWN(ButtonCode_t::KEY_D)) 	
						newOrigin -= pSetup->angles.Right() * fSpeed;
					if (KEY_DOWN(ButtonCode_t::KEY_S)) 
						newOrigin -= pSetup->angles.Forward() * fSpeed;
					if (KEY_DOWN(ButtonCode_t::KEY_SPACE))
						newOrigin += pSetup->angles.Up() * fSpeed;
					pSetup->origin = newOrigin;
				}
			}

			if (ThirdPerson)
			{
				static bool enable;

				if (ThirdPersonBind.Check())
					enable = I::Input()->m_fCameraInThirdPerson = true;
				else
					enable = I::Input()->m_fCameraInThirdPerson = false;

				if (enable && !CGlobal::LocalPlayer->IsDead())
				{
					auto GetCorrectDistance = [](float ideal_distance) -> float
					{
						/* vector for the inverse angles */
						QAngle inverseAngles;
						I::Engine()->GetViewAngles(inverseAngles);

						/* inverse angles by 180 */
						inverseAngles.x *= -1.f, inverseAngles.y += 180.f;

						/* vector for direction */
						Vector direction;
						AngleVectors(inverseAngles, direction);

						/* ray, trace & filters */
						Ray_t ray;
						trace_t trace;
						CTraceFilter filter;

						/* dont trace local player */
						filter.pSkip = CGlobal::LocalPlayer;

						/* create ray */
						ray.Init(CGlobal::LocalPlayer->GetEyePosition(), CGlobal::LocalPlayer->GetEyePosition() + (direction * ideal_distance));

						/* trace ray */
						I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &trace);

						/* return the ideal distance */
						return (ideal_distance * trace.fraction) - 10.f;
					};

					QAngle angles;
					I::Engine()->GetViewAngles(angles);
					angles.z = GetCorrectDistance(ThirdPersonDistance); // 150 is better distance
					I::Input()->m_vecCameraOffset = Vector(angles.x, angles.y, angles.z);
				}
			}
		}
	}

	if (CGlobal::LocalPlayer && !CGlobal::FullUpdateCheck)
	{
		if (GP_LegitAim)
		{
			if (GP_LegitAim->CanRCSStandelone && GP_LegitAim->CanRCS)
			{
				pSetup->angles.x -= ((CGlobal::LocalPlayer->GetViewPunchAngle().x * 2.f) * 0.2f);
				pSetup->angles.y -= ((CGlobal::LocalPlayer->GetViewPunchAngle().y * 2.f) * 0.2f);
			}
		}
	}
	
	CGlobal::GFovView = pSetup->fov;
}

void CMisc::GetViewModelFOV(float &Fov)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (CGlobal::LocalPlayer)
		{
			if (FovModelChanger)
			{
				if (CGlobal::LocalPlayer->IsDead())
				{
					if (CGlobal::LocalPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && CGlobal::LocalPlayer->GetObserverTarget())
						CGlobal::LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(CGlobal::LocalPlayer->GetObserverTarget());

					if (!CGlobal::LocalPlayer)
						return;
				}

				bool ChangeFov = true;
				CBaseWeapon* Wep = CGlobal::LocalPlayer->GetBaseWeapon();
				if (Wep)
				{
					if (((WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_AWP ||
						(WEAPON_ID)*Wep->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_SSG08) &&
						(CGlobal::GFovViewExt == 90 || CGlobal::GFovViewExt == FovView) && !CGlobal::LocalPlayer->IsDead())
					{
						ChangeFov = true;
					}
					else
					{
						WEAPON_TYPE WeapType = CGlobal::GWeaponType;
						if ((WeapType != WEAPON_TYPE_GRENADE &&
							WeapType != WEAPON_TYPE_KNIFE) &&
							(Wep->GetZoomLevel() == 1 ||
								Wep->GetZoomLevel() == 2))
						{
							ChangeFov = false;
						}
					}

				}

				if (ChangeFov)
					Fov = (float)FovModel;
			}
		}
	}
}

//void SetLocalPlayerReady()
//{
//	static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>
//		(CSX::Memory::FindPatternV2(XorStr("client.dll"),
//			XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
//
//	if (SetLocalPlayerReadyFn)
//		SetLocalPlayerReadyFn("");
//}

//void accept()
//{
//	typedef void(__cdecl* accept_t)(void);
//	static accept_t accept = (accept_t)CSX::Memory::FindPatternV2(XorStr("client.dll"),
//		XorStr("55 8B EC 51 56 8B 35 ? ? ? ? 57 83 BE"));
//
//	if (accept && **(unsigned long**)((unsigned long)accept + 0x7))
//	{
//		SetLocalPlayerReady();
//	}
//}

void CMisc::AutoAcceptEmit()
{
	if (AutoAccept && !CGlobal::FullUpdateCheck)
	{
		static auto fnAccept = reinterpret_cast<bool(__stdcall*)(const char*)>
			(CSX::Memory::FindPatternV2(clientFactory,
				XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));

		if (fnAccept)
		{
			fnAccept("");
			HWND window = FastCall::G().t_FindWindowA("Valve001", 0);
			FLASHWINFO flash{ sizeof(FLASHWINFO), window, FLASHW_TRAY | FLASHW_TIMERNOFG, 0, 0 };
			FlashWindowEx(&flash);
		}

		//typedef void(__cdecl* accept_t)(void);
		//static accept_t accept = (accept_t)CSX::Memory::FindPatternV2(XorStr("client.dll"),
		//	XorStr("55 8B EC 51 56 8B 35 ? ? ? ? 57 83 BE"));

		//static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>
		//	(CSX::Memory::FindPatternV2(XorStr("client.dll"),
		//		XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));

		//auto match_session = I::MatchFramework()->get_match_session();
		//if (match_session) 
		//{
		//	auto session_settings = match_session->get_session_settings();
		//	if (session_settings) 
		//	{
		//		string search_state = session_settings->GetString("game/mmqueue", "");

		//		if (search_state == "reserved") 
		//		{
		//			FLASHWINFO fi;
		//			fi.cbSize = sizeof(FLASHWINFO);
		//			fi.hwnd = FastCall::G().t_FindWindowA(NULL, XorStr("Counter-Strike: Global Offensive"));
		//			fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		//			fi.uCount = 0;
		//			fi.dwTimeout = 0;
		//			FlashWindowEx(&fi);
		//			ShowWindow(fi.hwnd, SW_RESTORE);
		//			Sleep(500);
		//			if (accept && **(unsigned long**)((unsigned long)accept + 0x7)) 
		//			{
		//				if (SetLocalPlayerReadyFn)
		//					SetLocalPlayerReadyFn("");
		//			}
		//		}
		//	}
		//}
	}
}

//void CMisc::PlaySound(const char* pszSoundName)
//{
//}

void CMisc::DrawModelExecute(void* thisptr, IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (Enable && !CGlobal::FullUpdateCheck)
	{
		static IMaterial* VisTex = nullptr;
		static IMaterial* VisFlat = nullptr;
		static IMaterial* VisFrame = nullptr;
		static IMaterial* VisMetallic = nullptr;

		if (!VisTex)
			VisTex = CGlobal::CreateMaterialBasic(false, true, false);

		if (!VisFlat)
			VisFlat = CGlobal::CreateMaterialBasic(false, false, false);

		if (!VisFrame)
			VisFrame = CGlobal::CreateMaterialBasic(false, true, true);

		if (!VisMetallic)
			VisMetallic = CGlobal::CreateMaterialMetallic(false, true);

		if (VisTex && VisFlat && VisFrame)
		{
			if (HandChams)
			{
				float HandColor[3] = { HandChamsColor.G1R(), HandChamsColor.G1G(), HandChamsColor.G1B() };
				const char* ModelName = I::ModelInfo()->GetModelName((model_t*)pInfo.pModel);

				if (strstr(ModelName, XorStr("arms")))
				{
					I::RenderView()->SetColorModulation(HandColor);
					I::RenderView()->SetBlend(HandChamsColor.G1A());

					if (HandChamsStyle == 0)
						I::ModelRender()->ForcedMaterialOverride(VisTex);
					else if (HandChamsStyle == 1)
						I::ModelRender()->ForcedMaterialOverride(VisFlat);
					else if (HandChamsStyle == 2)
						I::ModelRender()->ForcedMaterialOverride(VisFrame);
					else if (HandChamsStyle == 3)
						I::ModelRender()->ForcedMaterialOverride(VisMetallic);
					else if (HandChamsStyle == 5)
					{
						I::RenderView()->SetBlend(0.0f);
						I::ModelRender()->ForcedMaterialOverride(VisFlat);
					}
					HookTables::pDrawModelExecute->GetTrampoline()(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				}
			}
		}
	}
}
void CMisc::ShowSpectatorList()
{
	if (CGlobal::FullUpdateCheck)
		return;

	string spect = "";
	string mode = "";

	bool op = true;

	int LocalPlayerIdx = I::Engine()->GetLocalPlayer();
	vector<int> observs = GetObservervators(LocalPlayerIdx);

	if (observs.empty() && SpectatorListAutoHide && !CGlobal::IsGuiVisble)
		return;

	static bool Hovered = false;

	GuiStyle& style = X1Gui().GetStyle();
	Vec2 OldPadding = style.wndPadding;
	style.wndPadding = Vec2(3, 3);

	color_t old_color = style.clrBackground;
	style.clrBackground = Color(MainSettings().BackgroundColor.r(),
		MainSettings().BackgroundColor.g(),
		MainSettings().BackgroundColor.b(), SpectatorListAlpha);

	X1Gui().SetNextWindowPos(Vec2(SpectatorListPosX, SpectatorListPosY));

	static Vec2 old_cursor_pos = Vec2(200, 100);

	if (X1Gui().Begin(XorStr("Spectators"), GWF_Window, old_cursor_pos, Vec2(0, 0)))
	{
		X1Gui().Text(XorStr("Name"));
		X1Gui().SameLine(93);
		X1Gui().Text(XorStr("Mode"));
		X1Gui().Separator();

		bool Kastil = false;

		for (int playerId : observs)
		{
			if (playerId == LocalPlayerIdx)
				continue;

			CBaseEntity* pPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(playerId);
			if (!pPlayer)
				continue;

			PlayerInfo Pinfo;
			if (!I::Engine()->GetPlayerInfo(playerId, &Pinfo))
				continue;

			if (Pinfo.m_bIsFakePlayer)
				continue;

			spect = Pinfo.m_szPlayerName;

			if (spect != "")
			{
				switch (pPlayer->GetObserverMode())
				{
				case ObserverMode_t::OBS_MODE_IN_EYE:
					mode = XorStr("1st person");
					break;
				case ObserverMode_t::OBS_MODE_CHASE:
					mode = XorStr("3rd person");
					break;
				case ObserverMode_t::OBS_MODE_ROAMING:
					mode = XorStr("Free look");
					break;
				case ObserverMode_t::OBS_MODE_DEATHCAM:
					mode = XorStr("Deathcam");
					break;
				case ObserverMode_t::OBS_MODE_FREEZECAM:
					mode = XorStr("Freezecam");
					break;
				case ObserverMode_t::OBS_MODE_FIXED:
					mode = XorStr("Fixed");
					break;
				default:
					break;
				}

				X1Gui().Text((spect + "    ").c_str());
				X1Gui().SameLine(93);
				X1Gui().Text(mode.c_str());
			}
			Kastil = true;
		}
		X1Gui().VerticalSeparator(90);

		if (!Kastil)
		{
			X1Gui().Text("                ");
			X1Gui().SameLine(93);
			X1Gui().Text("                ");
		}

		X1Gui().SameLine();

		old_cursor_pos = Vec2(X1Gui().GetCursorPosEx().x + 10, X1Gui().GetCursorPosEx().y + 10 + 15);
	}
	X1Gui().End();

	style.clrBackground = old_color;
	style.wndPadding = OldPadding;
}

void CMisc::Reset()
{
	if (!HitWorker.DamageVector.empty())
		HitWorker.DamageVector.clear();

	if (!GP_Misc->HitImpacts.empty())
		GP_Misc->HitImpacts.clear();

	HitWorker.HitMarkerEndTime = 0;
}

vector<int> CMisc::GetObservervators(int playerId)
{
	vector<int> SpectatorList;

	CBaseEntity* pPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(playerId);

	if (!pPlayer)
		return SpectatorList;

	if (pPlayer->IsDead())
	{
		CBaseEntity* pObserverTarget = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

		if (!pObserverTarget)
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for (int PlayerIndex = 0; PlayerIndex < I::EntityList()->GetHighestEntityIndex(); PlayerIndex++)
	{
		CBaseEntity* pCheckPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(PlayerIndex);

		if (!pCheckPlayer)
			continue;

		if (!pCheckPlayer->IsPlayer())
			continue;

		if (pCheckPlayer->IsDormant() || !pCheckPlayer->IsDead())
			continue;

		CBaseEntity* pObserverTarget = (CBaseEntity*)I::EntityList()->GetClientEntityFromHandle(pCheckPlayer->GetObserverTarget());

		if (!pObserverTarget)
			continue;

		if (pPlayer != pObserverTarget)
			continue;

		SpectatorList.push_back(PlayerIndex);
	}

	return SpectatorList;
}

void CMisc::Night()
{
	static bool nightz = false;

	if (NightMode && CGlobal::IsGameReady)
	{
		if (!nightz)
		{
			static auto sv_skyname = I::GetConVar()->FindVar(XorStr("sv_skyname"));
			static auto r_DrawSpecificStaticProp = I::GetConVar()->FindVar(XorStr("r_DrawSpecificStaticProp"));

			r_DrawSpecificStaticProp->SetValue(1);
			sv_skyname->SetValue(XorStr("sky_csgo_night02"));

			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, XorStr("World textures")))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, XorStr("StaticProp")))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_bigdome")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_pillars")))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(group, XorStr("Particle textures")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				nightz = true;
			}
		}
	}
	else
	{
		if (nightz)
		{
			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, XorStr("World textures")))
				{
					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, XorStr("StaticProp")))
				{
					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_bigdome")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, XorStr("models/props/de_dust/palace_pillars")))
				{
					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, XorStr("Particle textures")))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}

			nightz = false;
		}
	}
}

void CMisc::FrameStageNotify()
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (CGlobal::LocalPlayer)
		{
			//...
		}
	}
}

void CMisc::CustomWalls()
{
	static bool reset = false;

	static KeyValues* KeyValTex;
	static KeyValues* KeyValFlat;

	if (!KeyValTex)
		KeyValTex = CGlobal::KeyValNew(false);

	if (!KeyValFlat)
		KeyValFlat = CGlobal::KeyValNew(false, false);

	if (ColoredWalls && CGlobal::IsGameReady)
	{
		static float old_r = ColoredWallsColor.G1R();
		static float old_g = ColoredWallsColor.G1G();
		static float old_b = ColoredWallsColor.G1B();
		static float old_a = ColoredWallsColor.G1A();

		static int old_style = ColoredWallsStyle;

		if (!reset || old_style != ColoredWallsStyle ||
			(old_r != ColoredWallsColor.G1R() ||
				old_g != ColoredWallsColor.G1G() ||
				old_b != ColoredWallsColor.G1B() ||
				old_a != ColoredWallsColor.G1A()))
		{

			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				if (strstr(pMaterial->GetTextureGroupName(), XorStr("World")) ||
					strstr(pMaterial->GetTextureGroupName(), XorStr("Particle textures")) ||
					strstr(pMaterial->GetTextureGroupName(), XorStr("StaticProp")) ||
					strstr(pMaterial->GetTextureGroupName(), XorStr("SkyBox")))
				{
					/*if (ColoredWallsStyle == 1)
					{
						if (KeyValTex)
							pMaterial->SetShaderAndParams(KeyValTex);
					}
					else if (ColoredWallsStyle == 2)
					{
						if (KeyValFlat)
							pMaterial->SetShaderAndParams(KeyValFlat);
					}*/

					pMaterial->AlphaModulate(ColoredWallsColor.G1A());
					pMaterial->ColorModulate(ColoredWallsColor.G1R(), ColoredWallsColor.G1G(), ColoredWallsColor.G1B());
				}

			}

			reset = true;
		}

		old_r = ColoredWallsColor.G1R();
		old_g = ColoredWallsColor.G1G();
		old_b = ColoredWallsColor.G1B();
		old_a = ColoredWallsColor.G1A();
		old_style = ColoredWallsStyle;
	}
	else
	{
		if (reset && CGlobal::IsGameReady)
		{
			for (MaterialHandle_t i = I::MaterialSystem()->FirstMaterial(); i != I::MaterialSystem()->InvalidMaterial(); i = I::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = I::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				if (strstr(pMaterial->GetTextureGroupName(), XorStr("World")))
				{
					pMaterial->AlphaModulate(1);
					pMaterial->ColorModulate(1, 1, 1);
				}
			}
			reset = false;
		}
	}
}

void ReadSounds(LPCTSTR lpszFileName)
{
	if (GP_Misc)
		GP_Misc->SoundList.push_back(lpszFileName);
}

void CMisc::UpdateSoundList()
{
	SoundList.clear();
	string SoundsDir = CGlobal::SystemDisk + XorStr("X1N3\\Resources\\Sounds\\*.wav");
	CGlobal::SearchFiles(SoundsDir.c_str(), ReadSounds, FALSE);
}

void CHitListener::RegListener()
{
	I::GameEvent()->AddListener(this, XorStr("player_hurt"), false);
	I::GameEvent()->AddListener(this, XorStr("bullet_impact"), false);
}

void CHitListener::UnRegListener()
{
	I::GameEvent()->RemoveListener(this);
}

#define HIT_TRACE_SHOW_TIME 2.f
void CHitListener::FireGameEvent(IGameEvent *event)
{
	if (GP_Misc)
	{
		if (GP_Misc->Enable)
		{
			if (CGlobal::LocalPlayer)
			{
				if (!strcmp(event->GetName(), XorStr("bullet_impact")))
				{
					int PlayerIdx = I::Engine()->GetPlayerForUserID(event->GetInt(XorStr("userid")));

					if (PlayerIdx == I::Engine()->GetLocalPlayer())
					{
						Vector ImpactPos(event->GetFloat(XorStr("x")), event->GetFloat(XorStr("y")), event->GetFloat(XorStr("z")));

						Ray_t ray;
						ray.Init(CGlobal::LocalPlayer->GetEyePosition(), ImpactPos);

						CTraceFilter filter;
						filter.pSkip = CGlobal::LocalPlayer;

						trace_t tr;
						I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

						if (tr.m_pEnt && tr.DidHit())
						{
							if (reinterpret_cast<CBaseEntity*>(tr.m_pEnt)->IsPlayer())
							{
								CMisc::HitImpact_t ImpEntry;
								ImpEntry.Pos = ImpactPos;
								ImpEntry.MyHeadPos = CGlobal::LocalPlayer->GetEyePosition();
								ImpEntry.EndTime = I::GlobalVars()->curtime + HIT_TRACE_SHOW_TIME;
								ImpEntry.Alpha = 255;
								GP_Misc->HitImpacts.push_back(ImpEntry);
							}
						}
					}
				}

				if (!strcmp(event->GetName(), XorStr("player_hurt")))
				{
					if (I::Engine()->GetPlayerForUserID(event->GetInt(XorStr("attacker"))) == I::Engine()->GetLocalPlayer())
					{

						if (GP_Misc->HitMarker)
						HitMarkerEndTime = I::GlobalVars()->curtime + 0.29f;

						if (GP_Misc->HitSound)
							if (!GP_Misc->SoundList.empty() && GP_Misc->HitSoundStyle >= 0 && GP_Misc->HitSoundStyle < (int)GP_Misc->SoundList.size())
								FastCall::G().t_PlaySoundA((CGlobal::SystemDisk + XorStr("X1N3\\Resources\\Sounds\\") + GP_Misc->SoundList[GP_Misc->HitSoundStyle]).c_str(),
									NULL, SND_FILENAME | SND_ASYNC);

						if (GP_Misc->DamageInfo)
						{
							DamgeInfo_t BufInfo;

							CBaseEntity* pHurtEnt = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetPlayerForUserID(event->GetInt(XorStr("userid"))));
							if (pHurtEnt)
							{
								BufInfo.Pos = pHurtEnt->GetHitboxPosition(0);
								if (!BufInfo.Pos.IsZero())
								{
									if (GP_Misc->DamageInfoStyle == 0)
										BufInfo.Number = event->GetInt(XorStr("dmg_health"));
									else if (GP_Misc->DamageInfoStyle == 1)
										BufInfo.Number = pHurtEnt->GetHealth() - event->GetInt(XorStr("dmg_health"));

									BufInfo.EndTime = I::GlobalVars()->curtime + GP_Misc->DamageInfoShowTime;
									BufInfo.Pos.z += 20;
									BufInfo.Alpha = 255;
									BufInfo.OffsetZ = 1;
									DamageVector.push_back(BufInfo);
								}
							}
						}
					}
				}
			}
		}
	}
}

void HitMark(const int &size, const int &tick, const int& pos_x, const int& pos_y, const Color& color)
{
	GP_Render->DrawLine(pos_x - size, pos_y - size, pos_x - (size / 4), pos_y - (size / 4), color, tick);
	GP_Render->DrawLine(pos_x - size, pos_y + size, pos_x - (size / 4), pos_y + (size / 4), color, tick);
	GP_Render->DrawLine(pos_x + size, pos_y + size, pos_x + (size / 4), pos_y + (size / 4), color, tick);
	GP_Render->DrawLine(pos_x + size, pos_y - size, pos_x + (size / 4), pos_y - (size / 4), color, tick);
}

void CHitListener::Draw()
{
	if (GP_Misc)
	{
		if (GP_Misc->HitMarker)
		{
			if (HitMarkerEndTime > I::GlobalVars()->curtime)
			{
				HitMark(GP_Misc->HitMarkerSize, GP_Misc->HitMarkerTickness,
					CGlobal::iScreenWidth / 2, CGlobal::iScreenHeight / 2, GP_Misc->HitMarkerColor);
			}
		}

		if (GP_Misc->DamageInfo)
		{
			if (!DamageVector.empty())
			{
				if (GP_Misc->DamageInfoPosition == 0)
					GP_Render->DrawString(GP_Misc->TextDamageInfo, Vec2(GP_Misc->DamageInfoPosX, GP_Misc->DamageInfoPosY), GP_Misc->DamageInfoColor,
						to_string(DamageVector.back().Number).c_str());

				int Height = GP_Misc->DamageInfoHeight;
				int Speed = GP_Misc->DamageInfoSpeed;

				for (size_t i(0); i < DamageVector.size(); i++)
				{
					if (GP_Misc->DamageInfoPosition == 1)
					{
						if (DamageVector[i].OffsetZ < Height)
							DamageVector[i].OffsetZ += (Height - DamageVector[i].OffsetZ) * (Speed / 1195.f);

						if (DamageVector[i].OffsetZ > Height - (Height / 5))
							if (DamageVector[i].Alpha > 0)
								DamageVector[i].Alpha -= 10;

						if (DamageVector[i].Alpha < 0)
							DamageVector[i].Alpha = 0;

						Vector ScreenPosition;
						Vector WorldPosition = Vector(DamageVector[i].Pos.x,
							DamageVector[i].Pos.y,
							DamageVector[i].Pos.z + DamageVector[i].OffsetZ);

						Color DamageColor = Color(GP_Misc->DamageInfoColor.r(), GP_Misc->DamageInfoColor.g(), GP_Misc->DamageInfoColor.b(), DamageVector[i].Alpha);

						if (CGlobal::WorldToScreen(WorldPosition, ScreenPosition))
							GP_Render->DrawString(GP_Misc->TextDamageInfo, Vec2(ScreenPosition.x, ScreenPosition.y), DamageColor, false, true,
								to_string(DamageVector.back().Number).c_str());

						if (DamageVector[i].OffsetZ > Height - 1)
							DamageVector.erase(DamageVector.begin() + i);
					}

					if (GP_Misc->DamageInfoPosition == 0)
						if (DamageVector[i].EndTime < I::GlobalVars()->curtime)
							if (CGlobal::IsGameReady)
								DamageVector.erase(DamageVector.begin() + i);
				}
			}
		}
	}

}

int CHitListener::GetEventDebugID(void)
{
	return 0x2A;
}