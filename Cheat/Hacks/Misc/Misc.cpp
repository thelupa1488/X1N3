#include "Misc.h"
#include  "../Setup.h"
#include "../../GUI/Gui.h"
#include "../../Engine/EnginePrediction.h"

//#define KEY_DOWN(VK_NNM) ((FastCall::G().t_GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)
#define KEY_DOWN(VK_NNM) (I::InputSystem()->IsButtonDown(VK_NNM))

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

				Night();
				CustomWalls();
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

				const auto FakeRot = DEG2RAD((CGlobal::side < 0.0f ? 90 : -90) - 90);
				DrawArrow(FakeRot, ArrowsColor);
			}

			if (AngleLines && ThirdPersonBind.Check())
			{
				auto DrawAngleLines = [&](const Vector& origin, const Vector& w2sOrigin, const float& angle, const char* text, Color clr)
				{
					Vector forward;
					AngleVectors(QAngle(0.f, angle, 0.f), forward);
					float AngleLinesLength = 30.0f;

					Vector w2sReal;
					if (CGlobal::WorldToScreen(origin + forward * AngleLinesLength, w2sReal))
					{
						GP_Render->DrawLine(w2sOrigin.x, w2sOrigin.y, w2sReal.x, w2sReal.y, Color::White(), 1.0f);
						GP_Render->DrawString(w2sReal.x, w2sReal.y /* - 5.0f, 14.f*/, clr, true, true, text);
					}
				};

				if (!CGlobal::LocalPlayer || !CGlobal::LocalPlayer->GetBasePlayerAnimState())
					return;

				if (CGlobal::LocalPlayer->IsDead())
					return;

				Vector w2sOrigin;
				if (CGlobal::WorldToScreen(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin))
				{
					static float view;
					if (CGlobal::bSendPacket)
						view = CGlobal::UserCmd->viewangles.y;

					DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, CGlobal::LocalPlayer->GetBasePlayerAnimState()->m_flGoalFeetYaw, XorStr("fake"), Color::Orange());
					DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, CGlobal::LocalPlayer->GetLowerBodyYawTarget(), XorStr("lby"), Color::Blue());
					DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, CGlobal::RealAngle, XorStr("real"), Color::Green()); //need fix
					DrawAngleLines(CGlobal::LocalPlayer->GetRenderOrigin(), w2sOrigin, view, XorStr("view"), Color::Red());
				}
			}
		}

		HitWorker.Draw();
	}
}

void CMisc::LegitPeek(CUserCmd* pCmd, bool& bSendPacket)
{
	if (!CGlobal::IsGameReady)
		return;

	int choke_factor = Desync ? min(MaxChokeTicks(), FakeLagFactor) : FakeLagFactor;

	static bool m_bIsPeeking = false;
	if (m_bIsPeeking)
	{
		bSendPacket = !(I::ClientState()->chokedcommands < choke_factor);
		if (bSendPacket)
			m_bIsPeeking = false;
		return;
	}

	auto speed = CGlobal::LocalPlayer->GetVelocity().Length();
	if (speed <= 70.0f)
		return;

	auto collidable = CGlobal::LocalPlayer->GetCollideable();

	Vector min, max;
	min = collidable->OBBMins();
	max = collidable->OBBMaxs();

	min += CGlobal::LocalPlayer->GetOrigin();
	max += CGlobal::LocalPlayer->GetOrigin();

	Vector center = (min + max) * 0.5f;

	for (int EntIndex = 1; EntIndex <= I::Engine()->GetMaxClients(); ++EntIndex)
	{
		CBaseEntity* Entity = (CBaseEntity*)I::EntityList()->GetClientEntity(EntIndex);

		if (!Entity || Entity->IsDead() || Entity->IsDormant())
			continue;

		if (Entity == CGlobal::LocalPlayer || (PLAYER_TEAM)CGlobal::LocalPlayer->GetTeam() == (PLAYER_TEAM)Entity->GetTeam())
			continue;

		CBaseWeapon* WeaponEntity = Entity->GetBaseWeapon();
		if (!WeaponEntity || WeaponEntity->GetWeaponAmmo() <= 0)
			continue;

		auto WeaponDataEntity = WeaponEntity->GetWeaponInfo();
		auto WeaponTypeEntity = CGlobal::GetWeaponType(WeaponEntity);

		if (!WeaponDataEntity || WeaponTypeEntity <= WEAPON_TYPE_KNIFE || WeaponTypeEntity >= WEAPON_TYPE_C4)
			continue;

		auto eye_pos = Entity->GetEyePosition();

		Vector direction;
		AngleVectors(Entity->GetEyeAngles(), direction);
		direction.NormalizeInPlace();

		Vector hit_point;
		bool hit = IntersectionBoundingBox(eye_pos, direction, min, max, &hit_point);
		if (hit && eye_pos.DistTo(hit_point) <= WeaponDataEntity->m_WeaponRange)
		{
			Ray_t ray;
			trace_t tr;
			CTraceFilterSkipEntity filter((CBaseEntity*)Entity);
			ray.Init(eye_pos, hit_point);

			I::EngineTrace()->TraceRay(ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &tr);
			if (tr.contents & CONTENTS_WINDOW) // skip windows
			{																					
				filter.pSkip = tr.m_pEnt;// at this moment, we dont care about local player
				ray.Init(tr.endpos, hit_point);
				I::EngineTrace()->TraceRay(ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &tr);
			}
			if (tr.fraction == 1.0f || tr.m_pEnt == CGlobal::LocalPlayer)
			{
				m_bIsPeeking = true;
				break;
			}
		}
	}
}

void CMisc::SetNewClan(string New, string Name)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)CSX::Memory::FindPatternV2(engineFactory, XorStr("53 56 57 8B DA 8B F9 FF 15"))));

	if (pSetClanTag)
		pSetClanTag(New.c_str(), Name.c_str());
}

float CMisc::GetFullLatency() 
{
	return I::Engine()->GetNetChannelInfo()->GetLatency(FLOW_INCOMING) + I::Engine()->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
}

bool CMisc::ChangeName(bool reconnect, const char* newName, float delay)
{
	static auto exploitInitialized = false;

	static auto name = I::GetConVar()->FindVar(XorStr("name"));

	if (reconnect)
	{
		exploitInitialized = false;
		return false;
	}

	if (!exploitInitialized && CGlobal::IsGameReady)
	{
		PlayerInfo playerInfo;
		if (CGlobal::LocalPlayer && I::Engine()->GetPlayerInfo(CGlobal::LocalPlayer->EntIndex(), &playerInfo) && (!strcmp(playerInfo.m_szPlayerName, XorStr("?empty")) ||
			!strcmp(playerInfo.m_szPlayerName, XorStr("\n\xAD\xAD\xAD"))))
		{
			exploitInitialized = true;
		}
		else
		{
			*(int*)((DWORD)&name->fnChangeCallback + 0xC) = NULL;
			name->SetValue(XorStr("\n\xAD\xAD\xAD"));
			return false;
		}
	}
	static auto nextChangeTime = 0.0f;
	if (nextChangeTime <= I::GlobalVars()->realtime)
	{
		name->SetValue(newName);
		nextChangeTime = I::GlobalVars()->realtime + delay;
		return true;
	}
	return false;
}

int CMisc::GetBestHeadAngle(float yaw)
{
	float Back, Right, Left;

	Vector src3D, dst3D, forward, right, up, src, dst;
	trace_t tr;
	Ray_t ray, ray2, ray3, ray4, ray5;
	CTraceFilter filter;

	QAngle engineViewAngles;

	engineViewAngles.x = 0;
	engineViewAngles.y = yaw;

	AngleVectors(engineViewAngles, forward, right, up);

	filter.pSkip = CGlobal::LocalPlayer;
	src3D = CGlobal::LocalPlayer->GetEyePosition();
	dst3D = src3D + (forward * 384);

	ray.Init(src3D, dst3D);

	I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

	Back = (tr.endpos - tr.startpos).Length();

	ray2.Init(src3D + right * 35, dst3D + right * 35);

	I::EngineTrace()->TraceRay(ray2, MASK_SHOT, &filter, &tr);

	Right = (tr.endpos - tr.startpos).Length();

	ray3.Init(src3D - right * 35, dst3D - right * 35);

	I::EngineTrace()->TraceRay(ray3, MASK_SHOT, &filter, &tr);

	Left = (tr.endpos - tr.startpos).Length();

	static int result = 0;

	if (Left > Right)
	{
		result = -1;
	}
	else if (Right > Left)
	{
		result = 1;
	}

	return result;
}

void CMisc::UpdateLBY(CCSGOPlayerAnimState* animstate)
{
	if (animstate->speed_2d > 0.1f || fabsf(animstate->flUpVelocity))
	{
		CGlobal::next_lby = I::GlobalVars()->curtime + 0.22f;
	}
	else if (I::GlobalVars()->curtime > CGlobal::next_lby)
	{
		if (fabsf(CGlobal::AngleDiff(animstate->m_flGoalFeetYaw, animstate->m_flEyeYaw)) > 35.0f) 
			CGlobal::next_lby = I::GlobalVars()->curtime + 1.1f;
	}
}

int CMisc::MaxChokeTicks() 
{
	int maxticks = I::GameRules() && I::GameRules()->IsValveDS() ? 11 : 15;
	static int max_choke_ticks = 0;
	static int latency_ticks = 0;
	float fl_latency = I::Engine()->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
	int latency = TIME_TO_TICKS(fl_latency);;
	if (I::ClientState()->chokedcommands <= 0)
		latency_ticks = latency;
	else latency_ticks = max(latency, latency_ticks);

	if (fl_latency >= I::GlobalVars()->interval_per_tick)
		max_choke_ticks = 11 - latency_ticks;
	else max_choke_ticks = 11;
	return max_choke_ticks;
}

void CMisc::RankReveal()
{
	using ServerRankRevealAll = bool(__cdecl*)(int*);

	static auto fnServerRankRevealAll = reinterpret_cast<int(__thiscall*)(ServerRankRevealAll*, DWORD, void*)>
		(CSX::Memory::FindPatternV2(clientFactory,
			XorStr("55 8B EC 8B 0D ? ? ? ? 85 C9 75 28 A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 04 85 C0 74 0B 8B C8 E8 ? ? ? ? 8B C8 EB 02 33 C9 89 0D ? ? ? ? 8B 45 08")));

	int v[3] = { 0,0,0 };

	reinterpret_cast<ServerRankRevealAll>(fnServerRankRevealAll)(v);
}

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

						static auto cl_sidespeed = I::GetConVar()->FindVar(XorStr("cl_sidespeed"));

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
				lolc("particle/vistasmokev1/vistasmokev1_smokegrenade"),
				lolc("particle/vistasmokev1/vistasmokev1_emods"),
				lolc("particle/vistasmokev1/vistasmokev1_emods_impactdust"),
				lolc("particle/vistasmokev1/vistasmokev1_fire"),
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

			if (NameStealer)
			{
				static std::vector<int> stolenIds;
				for (int EntIndex = 1; EntIndex <= I::Engine()->GetMaxClients(); ++EntIndex)
				{
					const auto entity = I::ClientEntityList()->GetClientEntity(EntIndex);

					if (!entity || entity == CGlobal::LocalPlayer)
						continue;

					PlayerInfo playerInfo;
					if (!I::Engine()->GetPlayerInfo(entity->EntIndex(), &playerInfo))
						continue;

					if (playerInfo.m_bIsFakePlayer || std::find(stolenIds.cbegin(), stolenIds.cend(), playerInfo.m_nUserID) != stolenIds.cend())
						continue;

					if (ChangeName(false, (std::string(playerInfo.m_szPlayerName) +'\x1').c_str(), 1.0f))
						stolenIds.push_back(playerInfo.m_nUserID);

					return;
				}
				stolenIds.clear();
			}

			static bool ClanTagReset = false;
			if (ClanTagChanger)
			{
				static string old_tag = "";
				static int oldvalue = 0;
				static int old_setting_mode = -1;
				string tag = ClanTagChangerText;
				int setting_mode = ClanTagChangerStyle;
				static int str_size = tag.size();

				if (old_setting_mode != setting_mode)
				{
					old_tag = "";
					old_setting_mode = setting_mode;
				}

				if (old_tag != tag && setting_mode > 1)
				{
					oldvalue = 0;
					old_tag = tag;
					str_size = tag.size();
				}

				int ServerTime = (float)I::Engine()->GetServerTick() * I::GlobalVars()->interval_per_tick;

				switch (setting_mode)
				{
				case 0:
				{
					if (old_tag != tag)
					{
						old_tag = tag;
						SetNewClan("", " ");
					}

					break;
				}
				case 1:
				{
					if (old_tag != tag)
					{
						old_tag = tag;
						SetNewClan(tag.c_str(), " ");
					}

					break;
				}
				case 2:
				{
					int value = (ServerTime % (str_size * 2)) + 1;

					if (oldvalue != value)
					{
						if (value > str_size)
							value = str_size - (value - str_size);

						tag.erase(value);
						SetNewClan(tag.c_str(), " ");
						oldvalue = value;
					}
					break;
				}
				case 3:
				{
					int value = ServerTime % str_size + 1;

					if (oldvalue != value)
					{
						std::string tag_now = "";

						tag_now.append(tag, value);

						tag.erase(value);
						tag_now += tag;

						SetNewClan(tag_now.c_str(), " ");
						oldvalue = value;
					}

					break;
				}
				case 4:
				{
					int value = str_size - (ServerTime % str_size + 1);

					if (oldvalue != value)
					{
						std::string tag_now = "";

						tag_now.append(tag, value);

						tag.erase(value);
						tag_now += tag;

						SetNewClan(tag_now.c_str(), " ");
						oldvalue = value;
					}

					break;
				}
				case 5:
				{
					int value = (ServerTime % (str_size * 2)) + 1;

					if (oldvalue != value)
					{
						if (value > str_size)
						{
							value -= str_size;
							tag.erase(0, value);
						}
						else
							tag.erase(value);

						SetNewClan(tag.c_str(), " ");
						oldvalue = value;
					}

					break;
				}
				default:
					break;
				}
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
				vector<string> RadioSpam = { lols("coverme") , lols("takepoint"), lols("holdpos"), lols("regroup"), lols("followme"),
					lols("takingfire"), lols("go"), lols("fallback"), lols("sticktog"),
					lols("report"), lols("roger"), lols("enemyspot"), lols("needbackup"),
					lols("sectorclear"), lols("inposition"), lols("reportingin"),
					lols("getout"), lols("negative"), lols("enemydown") };

				static DWORD lastspammed = 0;
				if (FastCall::G().t_GetTickCount64() - lastspammed > 800)
				{
					lastspammed = GetTickCount();
					string msg = RadioSpam[rand() % RadioSpam.size()];
					I::Engine()->ExecuteClientCmd(msg.c_str());
				}
			}
			static int ticks = 0;

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
				if (FakeLagUnducking && CGlobal::LocalPlayer->GetDuckAmount() > 0.05f && CGlobal::LocalPlayer->GetDuckAmount() < 0.95f)
				{
					bSendPacket = !(I::ClientState()->chokedcommands < MaxChokeTicks());
					return;
				}

				if (FakeLagFactor <= 0)
					return;

				int choke_factor = Desync ? min(MaxChokeTicks(), FakeLagFactor) : FakeLagFactor;

				auto speed = CGlobal::LocalPlayer->GetVelocity().Length();
				bool standing = speed <= 1.0f;

				if (!FakeLagStanding && standing)
					return;

				if (!FakeLagMoving && !standing)
					return;

				enum FakelagMode
				{
					FakelagStatic = 0,
					FakelagSwitch,
					FakelagAdaptive,
					FakelagRandom,
					FakelagLegitPeek
				};

				float UnitsPerTick = 0.0f;

				int WishTicks = 0;
				int AdaptiveTicks = 2;
				static int LastRandomNumber = 5;
				static int randomSeed = 12345;

				switch (FakeLagType)
				{
				case FakelagSwitch:
					// apply same logic as static fakelag
					if (pCmd->command_number % 30 > 15)
						break;
				case FakelagStatic:
					bSendPacket = !(I::ClientState()->chokedcommands < choke_factor);
					break;
				case FakelagAdaptive:
					if (standing) {
						bSendPacket = !(I::ClientState()->chokedcommands < choke_factor);
						break;
					}

					UnitsPerTick = CGlobal::LocalPlayer->GetVelocity().Length() * I::GlobalVars()->interval_per_tick;
					while ((WishTicks * UnitsPerTick) <= 68.0f) {
						if (((AdaptiveTicks - 1) * UnitsPerTick) > 68.0f) {
							++WishTicks;
							break;
						}
						if ((AdaptiveTicks * UnitsPerTick) > 68.0f) {
							WishTicks += 2;
							break;
						}
						if (((AdaptiveTicks + 1) * UnitsPerTick) > 68.0f) {
							WishTicks += 3;
							break;
						}
						if (((AdaptiveTicks + 2) * UnitsPerTick) > 68.0f) {
							WishTicks += 4;
							break;
						}
						AdaptiveTicks += 5;
						WishTicks += 5;
						if (AdaptiveTicks > 16)
							break;
					}

					bSendPacket = !(I::ClientState()->chokedcommands < WishTicks);
					break;
				case FakelagRandom:
					if (I::ClientState()->chokedcommands < LastRandomNumber) {
						bSendPacket = false;
					}
					else {
						randomSeed = 0x41C64E6D * randomSeed + 12345;
						LastRandomNumber = (randomSeed / 0x10000 & 0x7FFFu) % choke_factor;
						bSendPacket = true;
					}
					break;
				case FakelagLegitPeek:
					LegitPeek(pCmd, bSendPacket);
					break;
				}
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
		}
	}
}
void CMisc::EnginePrediction(bool& bSendPacket, CUserCmd* pCmd)
{
	if (Enable && CGlobal::IsGameReady && !CGlobal::FullUpdateCheck)
	{
		if (CGlobal::LocalPlayer)
		{
			static int unpred_flags = CGlobal::LocalPlayer->GetFlags();
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

				/*QAngle angleold = pCmd->viewangles;
				if (Desync)
				{
					if (pCmd->buttons & (IN_ATTACK | IN_ATTACK2 | IN_USE) ||
						CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_LADDER || CGlobal::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP
						|| CGlobal::LocalPlayer->IsDead())
						return;

					if (I::GameRules() && I::GameRules()->IsFreezePeriod()) //need fix
						return;

					CBaseWeapon* weapon = CGlobal::LocalPlayer->GetBaseWeapon();

					if (!weapon)
						return;

					if ((CGlobal::GWeaponID == WEAPON_GLOCK || CGlobal::GWeaponID == WEAPON_FAMAS) && weapon->GetNextPrimaryAttack() >= I::GlobalVars()->curtime)
						return;

					if (CGlobal::GWeaponType == WEAPON_TYPE_GRENADE)
					{
						if (!weapon->GetPinPulled())
						{
							float throwTime = weapon->GetThrowTime();
							if (throwTime > 0.f)
								return;
						}

						if ((pCmd->buttons & IN_ATTACK) || (pCmd->buttons & IN_ATTACK2))
						{
							if (weapon->GetThrowTime() > 0.f)
								return;
						}
					}

					if (fabsf(CGlobal::LocalPlayer->GetSpawnTime() - I::GlobalVars()->curtime) < 1.0f)
						return;

					static bool broke_lby = false;

					auto sideauto = GetBestHeadAngle(CGlobal::vangle.y);

					if (!DesyncAd)
					{
						if (DesyncBind.Check())
						{
							CGlobal::side = 1.0f;
						}
						else
							CGlobal::side = -1.0f;
					}
					else
						CGlobal::side = sideauto;

					if (DesyncType == 1)
					{
						float minimal_move = CGlobal::LocalPlayer->GetFlags() & IN_DUCK ? 3.0f : 1.0f;

						if (!bSendPacket)
							pCmd->viewangles.y += 120.f * CGlobal::side;

						static bool flip = 1;
						flip = !flip;

						pCmd->sidemove += flip ? minimal_move : -minimal_move;
					}
					else if (DesyncType == 2)
					{
						if (CGlobal::next_lby >= I::GlobalVars()->curtime)
						{
							if (!broke_lby && bSendPacket)
								return;

							broke_lby = false;
							bSendPacket = false;
							pCmd->viewangles.y += 120.0f * CGlobal::side;
						}
						else
						{
							broke_lby = true;
							bSendPacket = false;
							pCmd->viewangles.y += 120.0f * -(CGlobal::side);
						}
					}
					else if (DesyncType == 3)
					{
						static bool switchaa = false;
						switchaa = !switchaa;

						if (!bSendPacket)
							pCmd->viewangles.y += switchaa ? 180.f : 0.f;
					}
					FixAngles(pCmd->viewangles);
				}
				CGlobal::CorrectMouse(pCmd);
				auto anim_state = CGlobal::LocalPlayer->GetBasePlayerAnimState();
				if (anim_state)
				{
					CCSGOPlayerAnimState anim_state_backup = *anim_state;
					*anim_state = g_AnimState;
					CGlobal::LocalPlayer->GetVAngles() = pCmd->viewangles;
					CGlobal::LocalPlayer->UpdateClientSideAnimation();

					GP_Misc->UpdateLBY(anim_state);

					g_AnimState = *anim_state;
					*anim_state = anim_state_backup;
				}
				if (CGlobal::bSendPacket)
				{
					CGlobal::RealAngle = g_AnimState.m_flGoalFeetYaw;
					if (anim_state)
						CGlobal::FakeAngle = anim_state->m_flGoalFeetYaw;
					CGlobal::vangle = pCmd->viewangles;
				}
				FixMovement(pCmd, angleold);*/

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
			if (!ThirdPerson)
				I::Input()->m_fCameraInThirdPerson = false;

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
//		(CSX::Memory::FindPatternV2(clientFactory,
//			XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
//
//	if (SetLocalPlayerReadyFn)
//		SetLocalPlayerReadyFn("");
//}

//void accept()
//{
//	typedef void(__cdecl* accept_t)(void);
//	static accept_t accept = (accept_t)CSX::Memory::FindPatternV2(clientFactory,
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
			HWND window = FastCall::G().t_FindWindowA(XorStr("Valve001"), 0);
			FLASHWINFO flash{ sizeof(FLASHWINFO), window, FLASHW_TRAY | FLASHW_TIMERNOFG, 0, 0 };
			FlashWindowEx(&flash);
		}

		CGlobal::AcceptMatchBeep = false;
		//typedef void(__cdecl* accept_t)(void);
		//static accept_t accept = (accept_t)CSX::Memory::FindPatternV2(clientFactory,
		//	XorStr("55 8B EC 51 56 8B 35 ? ? ? ? 57 83 BE"));

		//static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>
		//	(CSX::Memory::FindPatternV2(clientFactory,
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
					switch (HandChamsStyle)
					{
					case 0: I::ModelRender()->ForcedMaterialOverride(VisTex); break; //tex
					case 1: I::ModelRender()->ForcedMaterialOverride(VisFlat); break; //flat
					case 2: I::ModelRender()->ForcedMaterialOverride(VisFrame); break; //frame
					case 3: I::ModelRender()->ForcedMaterialOverride(VisMetallic); break; //metallic		
					case 5: I::RenderView()->SetBlend(0.0f); I::ModelRender()->ForcedMaterialOverride(VisFlat); break; //disable
					default: break;
					}

					if (HandChamsStyle == 4) //material
					{
						if (MaterialFixColorHand > 1.f)
							MaterialFixColorHand /= 100.f;
						float FixColor = 100.01f - (99.f + MaterialFixColorHand);
						HandColor[0] = HandColor[0] / FixColor;
						HandColor[1] = HandColor[1] / FixColor;
						HandColor[2] = HandColor[2] / FixColor;

						I::RenderView()->SetColorModulation(HandColor);
						I::RenderView()->SetBlend(HandChamsColor.G1A());
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