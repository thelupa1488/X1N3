#pragma once

#include "SDK.h"
#include <DirectXMath.h>

#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( M_PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( M_PI ) ) )
#define M_PI 3.14159265358979323846
#define PI_F	((float)(M_PI))

#define Assert(_exp) ((void)0)

#define TICK_INTERVAL			(I::GlobalVars()->interval_per_tick)
#define TIME_TO_TICKS(dt)		((int)(0.5f + (float)(dt) / TICK_INTERVAL))
#define TICKS_TO_TIME(t)		(I::GlobalVars()->interval_per_tick * (t))


namespace SDK
{
	static float FASTSQRT(float x)
	{
		unsigned int i = *(unsigned int*)&x;

		i += 127 << 23;
		// approximation of square root
		i >>= 1;
		return *(float*)&i;
	}
	static float ClampYaw(float yaw)
	{
		while (yaw > 180.f)
			yaw -= 360.f;
		while (yaw < -180.f)
			yaw += 360.f;
		return yaw;
	}
	void FixAngles(QAngle& angles);
	template<class T>
	void lNormalizeAngles(T& vec);
	void lClampAngles(QAngle& angles);

	Vector ExtrapolateTick(Vector p0, Vector v0);
	float VectorDistance(const Vector& v1, const Vector& v2);
	QAngle CalcAngle(Vector src, Vector dst);
	float GetFOV(const QAngle& viewAngle, const QAngle& aimAngle);
	float RandomFloat(float min, float max);
	void RandomSeed(int iSeed);
	void VectorAngles(const Vector& forward, Vector& up, QAngle& angles);
	Vector CrossProduct2(const Vector& a, const Vector& b);
	Vector gCalcAngle(Vector src, Vector dst);
	void AngleVectors(const Vector& angles, Vector* forward, Vector* right, Vector* up);
	void NormalizeAngles(QAngle& angles);
	void NormalizePitch(float& pitch);
	bool IntersectionBoundingBox(const Vector& start, const Vector& dir, const Vector& min, const Vector& max, Vector* hit_point = nullptr);
	void Clamp(float& value, float min, float max);
	int RandomInt(int min, int max);
	float AngleDiff(float destAngle, float srcAngle);

	template<class T>
	void Normalize3(T& vec)
	{
		for (auto i = 0; i < 3; i++) {
			while (vec[i] < -180.0f) vec[i] += 360.0f;
			while (vec[i] > 180.0f) vec[i] -= 360.0f;
		}
		vec[2] = 0.f;
	}
	void inline SinCos(float x, float* s, float* c)
	{
		__asm
		{
			fld dword ptr[x]
			fsincos
			mov edx, dword ptr[c]
			mov eax, dword ptr[s]
			fstp dword ptr[edx]
			fstp dword ptr[eax]
		}
	}

	void AngleVector(const Vector& angles, Vector& forward);
	void MovementFix(CUserCmd* m_Cmd, Vector wish_angle, Vector old_angles);
	void Normalize(Vector& f);
	//void correct_movement(CUserCmd* cmd, const QAngle& old_angles);
	void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
	void gVectorAngles(const Vector& forward, Vector& up, Vector& angles);
	void AngleVectors(const QAngle& angles, Vector& forward);
	void gVectorAngles(const Vector& forward, Vector& angles);
	void gAngleVectors(const Vector& angles, Vector& forward);
	void AngleVectors(const QAngle& angles, Vector& forward, Vector& right, Vector& up);
	void VectorAngles(const Vector& forward, QAngle& angles);
	QAngle calculate_angle(Vector src, Vector dst);
	void VECTOR_Normalize(Vector& vIn, Vector& vOut);
	void QANGLE_Normalize(QAngle& vIn, QAngle& vOut);
	void VECTOR_NormaliseViewAngle(Vector& angle);
	void QANGLE_NormaliseViewAngle(QAngle& angle);
	QAngle VECTOR_TO_QANGLE(Vector& angle);
	Vector QANGLE_TO_VECTOR(QAngle& angle);
	//float TicksToTime(int tick);

		// SIMD Math

	inline float NormalizeYaw(float yaw)
	{
		if (yaw > 180)
			yaw -= (round(yaw / 360) * 360.f);
		else if (yaw < -180)
			yaw += (round(yaw / 360) * -360.f);

		return yaw;
	}

	template<class T, class U>
	inline T clamp(T in, U low, U high)
	{
		if (in <= low)
			return low;

		if (in >= high)
			return high;

		return in;
	}

	template <typename T = float>
	static T Minimum(const T& a, const T& b)
	{
		// check type.
		static_assert(std::is_arithmetic<T>::value, "Math::Minimum only supports integral types.");
		return (T)_mm_cvtss_f32(
			_mm_min_ss(_mm_set_ss((float)a),
				_mm_set_ss((float)b))
		);
	}

	template <typename T = float>
	static T Maximum(const T& a, const T& b)
	{
		// check type.
		static_assert(std::is_arithmetic<T>::value, "Math::Maximum only supports integral types.");
		return (T)_mm_cvtss_f32(
			_mm_max_ss(_mm_set_ss((float)a),
				_mm_set_ss((float)b))
		);
	}
}