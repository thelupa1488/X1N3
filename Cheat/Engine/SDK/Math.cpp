#include "Math.hpp"
#include "../Engine.h"
#include <algorithm>

namespace SDK
{
	inline Vector CrossProduct(const Vector& a, const Vector& b)
	{
		return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	void MovementFix(CUserCmd* m_Cmd, QAngle wish_angle, QAngle old_angles) {
		if (old_angles.x != wish_angle.x || old_angles.y != wish_angle.y || old_angles.z != wish_angle.z) {
			Vector wish_forward, wish_right, wish_up, cmd_forward, cmd_right, cmd_up;

			auto viewangles = old_angles;
			auto movedata = Vector(m_Cmd->forwardmove, m_Cmd->sidemove, m_Cmd->upmove);
			viewangles.Normalized();

			if (!(CGlobal::LocalPlayer->GetFlags() & FL_ONGROUND) && viewangles.z != 0.f)
				movedata.y = 0.f;

			AngleVectors(wish_angle, wish_forward, wish_right, wish_up);
			AngleVectors(viewangles, cmd_forward, cmd_right, cmd_up);

			auto v8 = sqrt(wish_forward.x * wish_forward.x + wish_forward.y * wish_forward.y), v10 = sqrt(wish_right.x * wish_right.x + wish_right.y * wish_right.y), v12 = sqrt(wish_up.z * wish_up.z);

			Vector wish_forward_norm(1.0f / v8 * wish_forward.x, 1.0f / v8 * wish_forward.y, 0.f),
				wish_right_norm(1.0f / v10 * wish_right.x, 1.0f / v10 * wish_right.y, 0.f),
				wish_up_norm(0.f, 0.f, 1.0f / v12 * wish_up.z);

			auto v14 = sqrt(cmd_forward.x * cmd_forward.x + cmd_forward.y * cmd_forward.y), v16 = sqrt(cmd_right.x * cmd_right.x + cmd_right.y * cmd_right.y), v18 = sqrt(cmd_up.z * cmd_up.z);

			Vector cmd_forward_norm(1.0f / v14 * cmd_forward.x, 1.0f / v14 * cmd_forward.y, 1.0f / v14 * 0.0f),
				cmd_right_norm(1.0f / v16 * cmd_right.x, 1.0f / v16 * cmd_right.y, 1.0f / v16 * 0.0f),
				cmd_up_norm(0.f, 0.f, 1.0f / v18 * cmd_up.z);

			auto v22 = wish_forward_norm.x * movedata.x, v26 = wish_forward_norm.y * movedata.x, v28 = wish_forward_norm.z * movedata.x, v24 = wish_right_norm.x * movedata.y, v23 = wish_right_norm.y * movedata.y, v25 = wish_right_norm.z * movedata.y, v30 = wish_up_norm.x * movedata.z, v27 = wish_up_norm.z * movedata.z, v29 = wish_up_norm.y * movedata.z;

			Vector correct_movement;
			correct_movement.x = cmd_forward_norm.x * v24 + cmd_forward_norm.y * v23 + cmd_forward_norm.z * v25 + (cmd_forward_norm.x * v22 + cmd_forward_norm.y * v26 + cmd_forward_norm.z * v28) + (cmd_forward_norm.y * v30 + cmd_forward_norm.x * v29 + cmd_forward_norm.z * v27);
			correct_movement.y = cmd_right_norm.x * v24 + cmd_right_norm.y * v23 + cmd_right_norm.z * v25 + (cmd_right_norm.x * v22 + cmd_right_norm.y * v26 + cmd_right_norm.z * v28) + (cmd_right_norm.x * v29 + cmd_right_norm.y * v30 + cmd_right_norm.z * v27);
			correct_movement.z = cmd_up_norm.x * v23 + cmd_up_norm.y * v24 + cmd_up_norm.z * v25 + (cmd_up_norm.x * v26 + cmd_up_norm.y * v22 + cmd_up_norm.z * v28) + (cmd_up_norm.x * v30 + cmd_up_norm.y * v29 + cmd_up_norm.z * v27);

			correct_movement.x = clamp(correct_movement.x, -450.f, 450.f);
			correct_movement.y = clamp(correct_movement.y, -450.f, 450.f);
			correct_movement.z = clamp(correct_movement.z, -320.f, 320.f);

			m_Cmd->forwardmove = correct_movement.x;
			m_Cmd->sidemove = correct_movement.y;
			m_Cmd->upmove = correct_movement.z;

			m_Cmd->buttons &= ~(IN_MOVERIGHT | IN_MOVELEFT | IN_BACK | IN_FORWARD);
			if (m_Cmd->sidemove != 0.0) {
				if (m_Cmd->sidemove <= 0.0)
					m_Cmd->buttons |= IN_MOVELEFT;
				else
					m_Cmd->buttons |= IN_MOVERIGHT;
			}

			if (m_Cmd->forwardmove != 0.0) {
				if (m_Cmd->forwardmove <= 0.0)
					m_Cmd->buttons |= IN_BACK;
				else
					m_Cmd->buttons |= IN_FORWARD;
			}
		}
	}

	void FixMovement(CUserCmd* cmd, QAngle& wishangle)
	{
		Vector view_fwd, view_right, view_up, cmd_fwd, cmd_right, cmd_up;
		AngleVectors(wishangle, view_fwd, view_right, view_up);
		AngleVectors(cmd->viewangles, cmd_fwd, cmd_right, cmd_up);

		const auto v8 = sqrtf((view_fwd.x * view_fwd.x) + (view_fwd.y * view_fwd.y));
		const auto v10 = sqrtf((view_right.x * view_right.x) + (view_right.y * view_right.y));
		const auto v12 = sqrtf(view_up.z * view_up.z);

		const Vector norm_view_fwd((1.f / v8) * view_fwd.x, (1.f / v8) * view_fwd.y, 0.f);
		const Vector norm_view_right((1.f / v10) * view_right.x, (1.f / v10) * view_right.y, 0.f);
		const Vector norm_view_up(0.f, 0.f, (1.f / v12) * view_up.z);

		const auto v14 = sqrtf((cmd_fwd.x * cmd_fwd.x) + (cmd_fwd.y * cmd_fwd.y));
		const auto v16 = sqrtf((cmd_right.x * cmd_right.x) + (cmd_right.y * cmd_right.y));
		const auto v18 = sqrtf(cmd_up.z * cmd_up.z);

		const Vector norm_cmd_fwd((1.f / v14) * cmd_fwd.x, (1.f / v14) * cmd_fwd.y, 0.f);
		const Vector norm_cmd_right((1.f / v16) * cmd_right.x, (1.f / v16) * cmd_right.y, 0.f);
		const Vector norm_cmd_up(0.f, 0.f, (1.f / v18) * cmd_up.z);

		const auto v22 = norm_view_fwd.x * cmd->forwardmove;
		const auto v26 = norm_view_fwd.y * cmd->forwardmove;
		const auto v28 = norm_view_fwd.z * cmd->forwardmove;
		const auto v24 = norm_view_right.x * cmd->sidemove;
		const auto v23 = norm_view_right.y * cmd->sidemove;
		const auto v25 = norm_view_right.z * cmd->sidemove;
		const auto v30 = norm_view_up.x * cmd->upmove;
		const auto v27 = norm_view_up.z * cmd->upmove;
		const auto v29 = norm_view_up.y * cmd->upmove;

		cmd->forwardmove = ((((norm_cmd_fwd.x * v24) + (norm_cmd_fwd.y * v23)) + (norm_cmd_fwd.z * v25))
			+ (((norm_cmd_fwd.x * v22) + (norm_cmd_fwd.y * v26)) + (norm_cmd_fwd.z * v28)))
			+ (((norm_cmd_fwd.y * v30) + (norm_cmd_fwd.x * v29)) + (norm_cmd_fwd.z * v27));
		cmd->sidemove = ((((norm_cmd_right.x * v24) + (norm_cmd_right.y * v23)) + (norm_cmd_right.z * v25))
			+ (((norm_cmd_right.x * v22) + (norm_cmd_right.y * v26)) + (norm_cmd_right.z * v28)))
			+ (((norm_cmd_right.x * v29) + (norm_cmd_right.y * v30)) + (norm_cmd_right.z * v27));
		cmd->upmove = ((((norm_cmd_up.x * v23) + (norm_cmd_up.y * v24)) + (norm_cmd_up.z * v25))
			+ (((norm_cmd_up.x * v26) + (norm_cmd_up.y * v22)) + (norm_cmd_up.z * v28)))
			+ (((norm_cmd_up.x * v30) + (norm_cmd_up.y * v29)) + (norm_cmd_up.z * v27));

		const auto ratio = 2.f - fmaxf(fabsf(cmd->sidemove), fabsf(cmd->forwardmove)) / 450.f;
		cmd->forwardmove *= ratio;
		cmd->sidemove *= ratio;

		wishangle = cmd->viewangles;
	}

	Vector ExtrapolateTick(Vector p0, Vector v0)
	{
		return p0 + (v0 * I::GlobalVars()->interval_per_tick);
	}

	//--------------------------------------------------------------------------------
	float VectorDistance(const Vector& v1, const Vector& v2)
	{
		return FASTSQRT(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
	}
	//--------------------------------------------------------------------------------
	void FixAngles(QAngle& angles)
	{
		lNormalizeAngles(angles);
		lClampAngles(angles);
	}
	template<class T>
	void lNormalizeAngles(T& vec)
	{
		for (auto i = 0; i < 2; i++) {
			while (vec[i] < -180.0f) vec[i] += 360.0f;
			while (vec[i] > 180.0f) vec[i] -= 360.0f;
		}
		vec[2] = 0.f;
	}
	void lClampAngles(QAngle& angles)
	{
		if (angles.x > 89.0f) angles.x = 89.0f;
		else if (angles.x < -89.0f) angles.x = -89.0f;

		if (angles.y > 180.0f) angles.y = 180.0f;
		else if (angles.y < -180.0f) angles.y = -180.0f;

		angles.z = 0;
	}
	//--------------------------------------------------------------------------------
	bool IntersectionBoundingBox(const Vector& src, const Vector& dir, const Vector& min, const Vector& max, Vector* hit_point)
	{
		/*
		Fast Ray-Box Intersection
		by Andrew Woo
		from "Graphics Gems", Academic Press, 1990
		*/

		constexpr auto NUMDIM = 3;
		constexpr auto RIGHT = 0;
		constexpr auto LEFT = 1;
		constexpr auto MIDDLE = 2;

		bool inside = true;
		char quadrant[NUMDIM];
		int i;

		// Rind candidate planes; this loop can be avoided if
		// rays cast all from the eye(assume perpsective view)
		Vector candidatePlane;
		for (i = 0; i < NUMDIM; i++) {
			if (src[i] < min[i]) {
				quadrant[i] = LEFT;
				candidatePlane[i] = min[i];
				inside = false;
			}
			else if (src[i] > max[i]) {
				quadrant[i] = RIGHT;
				candidatePlane[i] = max[i];
				inside = false;
			}
			else {
				quadrant[i] = MIDDLE;
			}
		}

		// Ray origin inside bounding box
		if (inside) {
			if (hit_point)
				*hit_point = src;
			return true;
		}

		// Calculate T distances to candidate planes
		Vector maxT;
		for (i = 0; i < NUMDIM; i++) {
			if (quadrant[i] != MIDDLE && dir[i] != 0.f)
				maxT[i] = (candidatePlane[i] - src[i]) / dir[i];
			else
				maxT[i] = -1.f;
		}

		// Get largest of the maxT's for final choice of intersection
		int whichPlane = 0;
		for (i = 1; i < NUMDIM; i++) {
			if (maxT[whichPlane] < maxT[i])
				whichPlane = i;
		}

		// Check final candidate actually inside box
		if (maxT[whichPlane] < 0.f)
			return false;

		for (i = 0; i < NUMDIM; i++) {
			if (whichPlane != i) {
				float temp = src[i] + maxT[whichPlane] * dir[i];
				if (temp < min[i] || temp > max[i]) {
					return false;
				}
				else if (hit_point) {
					(*hit_point)[i] = temp;
				}
			}
			else if (hit_point) {
				(*hit_point)[i] = candidatePlane[i];
			}
		}

		// ray hits box
		return true;
	}
	//--------------------------------------------------------------------------------
	void NormalizeAngles(QAngle& angles)
	{
		for (auto i = 0; i < 3; i++)
		{
			while (angles[i] < -180.0f)
			{
				angles[i] += 360.0f;
			}
			while (angles[i] > 180.0f)
			{
				angles[i] -= 360.0f;
			}
		}
	}
	void NormalizePitch(float& pitch)
	{
		while (pitch < -180.0f)
		{
			pitch += 360.0f;
		}
		while (pitch > 180.0f)
		{
			pitch -= 360.0f;
		}
	}

	void Clamp(float& value, float min, float max)
	{
		if (value < min) value = min;
		if (value > max) value = max;
	}

	int RandomInt(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}
	QAngle CalcAngle(Vector src, Vector dst)
	{
		QAngle angles;
		Vector delta = src - dst;
		VectorAngles(delta, angles);
		delta.Normalized();
		return angles;
	}

	Vector gCalcAngle(Vector src, Vector dst)
	{
		auto ret = Vector();
		auto delta = src - dst;
		double hyp = delta.Length2D();
		ret.y = (atan(delta.y / delta.x) * 57.295779513082f);
		ret.x = (atan(delta.z / hyp) * 57.295779513082f);
		ret[2] = 0.00;

		if (delta.x >= 0.0)
			ret.y += 180.0f;

		return ret;
	}

	Vector CrossProduct2(const Vector& a, const Vector& b)
	{
		return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	void VectorAngles(const Vector& forward, Vector& up, QAngle& angles)
	{
		Vector left = CrossProduct2(up, forward);
		left.NormalizeInPlace();

		float forwardDist = forward.Length2D();

		if (forwardDist > 0.001f)
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / PI_F;
			angles.y = atan2f(forward.y, forward.x) * 180 / PI_F;

			float upZ = (left.y * forward.x) - (left.x * forward.y);
			angles.z = atan2f(left.z, upZ) * 180 / PI_F;
		}
		else
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / PI_F;
			angles.y = atan2f(-left.x, left.y) * 180 / PI_F;
			angles.z = 0;
		}
	}
	float RandomFloat(float min, float max)
	{
		static auto ranFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleW(L"vstdlib.dll"), "RandomFloat"));
		if (ranFloat)
		{
			return ranFloat(min, max);
		}
		else
		{
			return 0.f;
		}
	}
	void RandomSeed(int iSeed)
	{
		static auto ranSeed = reinterpret_cast<void(*)(int)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"));
		if (ranSeed)
			ranSeed(iSeed);
	}
	//--------------------------------------------------------------------------------
	float GetFOV(const QAngle& viewAngle, const QAngle& aimAngle)
	{
		Vector ang, aim;

		AngleVectors(viewAngle, aim);
		AngleVectors(aimAngle, ang);

		return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
	}
	void AngleVector(const Vector& angles, Vector& forward)
	{
		Assert(s_bMathlibInitialized);
		Assert(forward);

		float sp, sy, cp, cy;

		SDK::SinCos(DEG2RAD(angles.y), &sy, &cy);
		SDK::SinCos(DEG2RAD(angles.x), &sp, &cp);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}
	//--------------------------------------------------------------------------------
	//void VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
	//{
	//	//auto t = in2[0];
	//	out[0] = in1.Dot(in2[0]) + in2[0][3];
	//	out[1] = in1.Dot(in2[1]) + in2[1][3];
	//	out[2] = in1.Dot(in2[2]) + in2[2][3];
	//}
	//--------------------------------------------------------------------------------
	void Normalize(Vector& f)
	{
		while (f.y <= -180) f.y += 360;
		while (f.y > 180) f.y -= 360;
		while (f.x <= -180) f.x += 360;
		while (f.x > 180) f.x -= 360;


		if (f.x > 89.0) f.x = 89;
		if (f.x < -89.0) f.x = -89;
		if (f.y < -180) f.y = -179.999;
		if (f.y > 180) f.y = 179.999;
	}
	//---------------------------------------------------------------------------------
	void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
	{
		// side/forward move correction
		float deltaView;
		float f1;
		float f2;

		if (vOldAngles.y < 0.f)
			f1 = 360.0f + vOldAngles.y;
		else
			f1 = vOldAngles.y;

		if (pCmd->viewangles.y < 0.0f)
			f2 = 360.0f + pCmd->viewangles.y;
		else
			f2 = pCmd->viewangles.y;

		if (f2 < f1)
			deltaView = abs(f2 - f1);
		else
			deltaView = 360.0f - abs(f1 - f2);

		deltaView = 360.0f - deltaView;

		pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
		pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	}
	//--------------------------------------------------------------------------------
	void gAngleVectors(const Vector& angles, Vector& forward)
	{
		float sp, sy, cp, cy;
		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);
		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}
	//--------------------------------------------------------------------------------
	void gVectorAngles(const Vector& forward, Vector& up, Vector& angles)
	{
		Vector left = CrossProduct(up, forward);
		left.NormalizeInPlace();
		float forwardDist = forward.Length2D();

		if (forwardDist > 0.001f)
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI;
			angles.y = atan2f(forward.y, forward.x) * 180 / M_PI;
			float upZ = (left.y * forward.x) - (left.x * forward.y);
			angles.z = atan2f(left.z, upZ) * 180 / M_PI;
		}

		else
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI;
			angles.y = atan2f(-left.x, left.y) * 180 / M_PI;
			angles.z = 0;
		}
	}
	//--------------------------------------------------------------------------------
	void AngleVectors(const QAngle& angles, Vector& forward)
	{
		float	sp, sy, cp, cy;

		DirectX::XMScalarSinCos(&sp, &cp, DEG2RAD(angles[0]));
		DirectX::XMScalarSinCos(&sy, &cy, DEG2RAD(angles[1]));

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}
	//--------------------------------------------------------------------------------
	void gVectorAngles(const Vector& forward, Vector& angles)
	{
		float tmp, yaw, pitch;

		if (forward[1] == 0 && forward[0] == 0)
		{
			yaw = 0;

			if (forward[2] > 0)
				pitch = 270;

			else
				pitch = 90;
		}

		else
		{
			yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);

			if (yaw < 0)
				yaw += 360;

			tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
			pitch = (atan2(-forward[2], tmp) * 180 / M_PI);

			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}
	//--------------------------------------------------------------------------------
	void AngleVectors(const QAngle& angles, Vector& forward, Vector& right, Vector& up)
	{
		float sr, sp, sy, cr, cp, cy;

		DirectX::XMScalarSinCos(&sp, &cp, DEG2RAD(angles[0]));
		DirectX::XMScalarSinCos(&sy, &cy, DEG2RAD(angles[1]));
		DirectX::XMScalarSinCos(&sr, &cr, DEG2RAD(angles[2]));

		forward.x = (cp * cy);
		forward.y = (cp * sy);
		forward.z = (-sp);
		right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right.y = (-1 * sr * sp * sy + -1 * cr * cy);
		right.z = (-1 * sr * cp);
		up.x = (cr * sp * cy + -sr * -sy);
		up.y = (cr * sp * sy + -sr * cy);
		up.z = (cr * cp);
	}
	//--------------------------------------------------------------------------------
	float Deg2Rad(float x)
	{
		return (x * (M_PI / 180.0f));
	}
	//--------------------------------------------------------------------------------
	void AngleVectors(const Vector& angles, Vector* forward, Vector* right, Vector* up)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(Deg2Rad(angles.x), &sp, &cp);
		SinCos(Deg2Rad(angles.y), &sy, &cy);
		SinCos(Deg2Rad(angles.z), &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
			right->y = (-1 * sr * sp * sy + -1 * cr * cy);
			right->z = -1 * sr * cp;
		}

		if (up)
		{
			up->x = (cr * sp * cy + -sr * -sy);
			up->y = (cr * sp * sy + -sr * cy);
			up->z = cr * cp;
		}
	}
	//--------------------------------------------------------------------------------
	void VectorAngles(const Vector& forward, QAngle& angles)
	{
		float	tmp, yaw, pitch;

		if (forward[1] == 0 && forward[0] == 0)
		{
			yaw = 0;
			if (forward[2] > 0)
			{
				pitch = 270;
			}
			else
			{
				pitch = 90;
			}
		}
		else
		{
			yaw = (atan2(forward[1], forward[0]) * 180 / DirectX::XM_PI);
			if (yaw < 0)
			{
				yaw += 360;
			}

			tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
			pitch = (atan2(-forward[2], tmp) * 180 / DirectX::XM_PI);
			if (pitch < 0)
			{
				pitch += 360;
			}
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}
	//--------------------------------------------------------------------------------
	static bool screen_transform(const Vector& in, Vector& out)
	{
		static auto& w2sMatrix = I::Engine()->WorldToScreenMatrix();

		out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
		out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
		out.z = 0.0f;

		float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

		if (w < 0.001f)
		{
			out.x *= 100000;
			out.y *= 100000;
			return false;
		}

		out.x /= w;
		out.y /= w;

		return true;
	}
	//--------------------------------------------------------------------------------
	bool WorldToScreen(const Vector& in, Vector& out)
	{
		if (screen_transform(in, out))
		{
			int w, h;
			I::Engine()->GetScreenSize(w, h);

			out.x = (w / 2.0f) + (out.x * w) / 2.0f;
			out.y = (h / 2.0f) - (out.y * h) / 2.0f;

			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------------
	QAngle calculate_angle(Vector src, Vector dst) {
		QAngle angles;

		Vector delta = src - dst;
		float hyp = delta.Length2D();

		angles.y = std::atanf(delta.y / delta.x) * 57.2957795131f;
		angles.x = std::atanf(-delta.z / hyp) * -57.2957795131f;
		angles.z = 0.0f;

		if (delta.x >= 0.0f)
			angles.y += 180.0f;

		return angles;
	}

	
	void VECTOR_Normalize(Vector& vIn, Vector& vOut)
	{
		float flLen = vIn.Length();
		if (flLen == 0) {
			vOut.Init(0, 0, 1);
			return;
		}
		flLen = 1 / flLen;
		vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
	}

	void QANGLE_Normalize(QAngle& vIn, QAngle& vOut)
	{
		float flLen = vIn.Length();
		if (flLen == 0) {
			vOut.Init(0, 0, 1);
			return;
		}
		flLen = 1 / flLen;
		vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
	}

	void VECTOR_NormaliseViewAngle(Vector& angle)
	{
		while (angle.y <= -180) angle.y += 360;
		while (angle.y > 180) angle.y -= 360;
		while (angle.x <= -180) angle.x += 360;
		while (angle.x > 180) angle.x -= 360;


		if (angle.x > 89) angle.x = 89;
		if (angle.x < -89) angle.x = -89;
		if (angle.y < -180) angle.y = -179.999;
		if (angle.y > 180) angle.y = 179.999;

		angle.z = 0;
	}

	void QANGLE_NormaliseViewAngle(QAngle& angle)
	{
		while (angle.y <= -180) angle.y += 360;
		while (angle.y > 180) angle.y -= 360;
		while (angle.x <= -180) angle.x += 360;
		while (angle.x > 180) angle.x -= 360;


		if (angle.x > 89) angle.x = 89;
		if (angle.x < -89) angle.x = -89;
		if (angle.y < -180) angle.y = -179.999;
		if (angle.y > 180) angle.y = 179.999;

		angle.z = 0;
	}

	QAngle VECTOR_TO_QANGLE(Vector& angle)
	{
		Vector angles;
		QAngle result;

		angles.x = result.x;
		angles.y = result.y;
		angles.z = result.z;

		return result;

	}

	Vector QANGLE_TO_VECTOR(QAngle& angle)
	{
		QAngle angles;
		Vector result;

		angles.x = result.x;
		angles.y = result.y;
		angles.z = result.z;

		return result;
	}
}