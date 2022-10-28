#pragma once

#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif

#ifndef M_PI_F
#define M_PI_F	((float)(M_PI))
#endif

#ifndef RAD2DEG
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

// Returns A + (B-A)*flPercent.
template <class T>
inline T Lerp(float flPercent, T const& A, T const& B)
{
	return A + (B - A) * flPercent;
}

inline float Sqr(float f)
{
	return f * f;
}

struct vec3;
float VectorNormalize(vec3& vec);

struct vec2
{
	float x, y;

	vec2() : x(0.f), y(0.f) {}

	vec2(float xx, float yy) : x(xx), y(yy) {}

	vec2(const vec2& vec) : x(vec.x), y(vec.y) {}

	inline bool isZero() const { static_assert(sizeof(float) == 4); return (*reinterpret_cast<const uint32_t*>(&x) == 0 && *reinterpret_cast<const uint32_t*>(&y) == 0); }

	inline float LengthSqr() const { return x * x + y * y; }
	inline float Length() const { return sqrtf(LengthSqr()); }

	vec2& operator*=(const vec2& vec) { x *= vec.x; y *= vec.y; return *this; }
	vec2& operator*=(float fl) { x *= fl; y *= fl; return *this; }

	vec2& operator/=(const vec2& vec) { x /= vec.x; y /= vec.y; return *this; }
	vec2& operator/=(float fl) { x /= fl; y /= fl; return *this; }

	vec2& operator+=(const vec2& vec) { x += vec.x; y += vec.y; return *this; }
	vec2& operator+=(float fl) { x += fl; y += fl; return *this; }

	vec2& operator-=(const vec2& vec) { x -= vec.x; y -= vec.y; return *this; }
	vec2& operator-=(float fl) { x -= fl; y -= fl; return *this; }
};
inline vec2 operator*(vec2 vec0, const vec2& vec1) { return vec0 *= vec1; }
inline vec2 operator*(vec2 vec0, float fl) { return vec0 *= fl; }

inline vec2 operator/(vec2 vec0, const vec2& vec1) { return vec0 /= vec1; }
inline vec2 operator/(vec2 vec0, float fl) { return vec0 /= fl; }

inline vec2 operator+(vec2 vec0, const vec2& vec1) { return vec0 += vec1; }
inline vec2 operator+(vec2 vec0, float fl) { return vec0 += fl; }

inline vec2 operator-(vec2 vec0, const vec2& vec1) { return vec0 -= vec1; }
inline vec2 operator-(vec2 vec0, float fl) { return vec0 -= fl; }

struct vec3
{
	float x, y, z;

	vec3() : x(0.f), y(0.f), z(0.f) {}

	vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	vec3(const vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {}

	inline float Pitch() const { return x; }
	inline float Yaw() const { return y; }
	inline float Roll() const { return z; }

	inline bool isZero() const { static_assert(sizeof(float) == 4); return (*reinterpret_cast<const uint32_t*>(&x) == 0 && *reinterpret_cast<const uint32_t*>(&y) == 0 && *reinterpret_cast<const uint32_t*>(&z) == 0); }

	inline float LengthSqr() const { return x * x + y * y + z * z; }
	inline float Length() const { return sqrtf(LengthSqr()); }
	inline float Length2D() const { return sqrtf(x * x + y * y); }

	inline vec3 Normalized() const
	{
		vec3 norm(*this);
		VectorNormalize(norm);
		return norm;
	}

	vec3& operator*=(const vec3& vec) { x *= vec.x; y *= vec.y; z *= vec.z; return *this; }
	vec3& operator*=(float fl) { x *= fl; y *= fl; z *= fl; return *this; }

	vec3& operator/=(const vec3& vec) { x /= vec.x; y /= vec.y; z /= vec.z; return *this; }
	vec3& operator/=(float fl) { x /= fl; y /= fl; z /= fl; return *this; }

	vec3& operator+=(const vec3& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
	vec3& operator+=(float fl) { x += fl; y += fl; z += fl; return *this; }

	vec3& operator-=(const vec3& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
	vec3& operator-=(float fl) { x -= fl; y -= fl; z -= fl; return *this; }
};
inline vec3 operator*(vec3 vec0, const vec3& vec1) { return vec0 *= vec1; }
inline vec3 operator*(vec3 vec, float fl) { return vec *= fl; }

inline vec3 operator/(vec3 vec0, const vec3& vec1) { return vec0 /= vec1; }
inline vec3 operator/(vec3 vec, float fl) { return vec /= fl; }

inline vec3 operator+(vec3 vec0, const vec3& vec1) { return vec0 += vec1; }
inline vec3 operator+(vec3 vec, float fl) { return vec += fl; }

inline vec3 operator-(vec3 vec0, const vec3& vec1) { return vec0 -= vec1; }
inline vec3 operator-(vec3 vec, float fl) { return vec -= fl; }

class alignas(16) VectorAligned : public vec3
{
public:
	VectorAligned() : vec3()
	{
	}

	VectorAligned(float xx, float yy, float zz) : vec3(xx, yy, zz)
	{
	}

	VectorAligned(const vec3& vec) : vec3(vec)
	{
	}

private:
	float w;
};

typedef vec3 Vector;
typedef vec3 QAngle;
typedef float matrix3x4_t[3][4];
typedef __declspec(align(16)) matrix3x4_t matrix3x4a_t;

typedef float VMatrix[4][4];


inline void VectorLerp(const vec3& a, const vec3& b, float t, vec3& dest)
{
	dest = a + (b - a) * t;
}

inline float DotProduct(const float* a, const float* b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

inline float DotProduct(const vec3& a, const vec3& b)
{
	return DotProduct(&a.x, &b.x);
}

float VectorNormalize(vec3& vec)
{
	float radius = vec.Length();

	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (radius + FLT_EPSILON);

	vec *= iradius;

	return radius;
}

inline float AngleNormalize(float angle)
{
	return std::remainderf(angle, 360.f);
}

void AnglesNormalize(vec3& v)
{
	if (v.x > 89.f)
		v.x = 89.f;
	else if (v.x < -89.f)
		v.x = -89.f;

	if (!isnormal(v.y) || 1.e+5f < v.y || v.y < -1.e+5f)
		v.y = 0.f;
	else
		v.y = AngleNormalize(v.y);

	v.z = 0.f;
}

// ensure that 0 <= angle <= 360
float AngleNormalizePositive(float angle)
{
	angle = fmodf(angle, 360.f);

	if (angle < 0.f)
		angle += 360.f;

	return angle;
}

inline void SinCos(float radians, float& sine, float& cosine)
{
	sine = sinf(radians);
	cosine = cosf(radians);
}

void AngleVectors(const vec3& angles, vec3* forward, vec3* right = nullptr, vec3* up = nullptr)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles.Yaw()), sy, cy);
	SinCos(DEG2RAD(angles.Pitch()), sp, cp);
	SinCos(DEG2RAD(angles.Roll()), sr, cr);

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

void VectorAngles(const vec3& forward, vec3& angles)
{
	float yaw, pitch;

	if (forward.y == 0.f && forward.x == 0.f)
	{
		yaw = 0.f;
		if (forward.z > 0.f)
			pitch = 270.f;
		else
			pitch = 90.f;
	}
	else
	{
		yaw = RAD2DEG(atan2(forward.y, forward.x));
		if (yaw < 0.f)
			yaw += 360.f;

		pitch = RAD2DEG(atan2(-forward.z, forward.Length2D()));
		if (pitch < 0.f)
			pitch += 360.f;
	}

	angles.x = pitch;
	angles.y = yaw;
	angles.z = 0.f;
}

void MatrixGetColumn(const matrix3x4_t& in, int column, vec3& out)
{
	out.x = in[0][column];
	out.y = in[1][column];
	out.z = in[2][column];
}

void MatrixSetColumn(const Vector& in, int column, matrix3x4_t& out)
{
	out[0][column] = in.x;
	out[1][column] = in.y;
	out[2][column] = in.z;
}

inline void MatrixPosition(const matrix3x4_t& matrix, vec3& position)
{
	MatrixGetColumn(matrix, 3, position);
}

void VectorTransform(const float* in, const matrix3x4_t& matrix, vec3& out)
{
	out.x = DotProduct(in, matrix[0]) + matrix[0][3];
	out.y = DotProduct(in, matrix[1]) + matrix[1][3];
	out.z = DotProduct(in, matrix[2]) + matrix[2][3];
}

float ApproachAngle(float target, float value, float speed)
{
	target = AngleNormalize(target);
	value = AngleNormalize(value);

	float delta = AngleNormalize(target - value);

	// Speed is assumed to be positive
	if (speed < 0.f)
		speed = -speed;

	if (delta > speed)
		value += speed;
	else if (delta < -speed)
		value -= speed;
	else
		value = target;

	return value;
}

void Vector2DRotate(const vec2& point, float degrees, vec2& out)
{
	float radians = DEG2RAD(degrees);

	float c = cos(radians);
	float s = sin(radians);

	out.x = point.x * c - point.y * s;
	out.y = point.x * s + point.y * c;
}

void AngleMatrix(const QAngle& angles, matrix3x4_t& matrix)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles.Yaw()), sy, cy);
	SinCos(DEG2RAD(angles.Pitch()), sp, cp);
	SinCos(DEG2RAD(angles.Roll()), sr, cr);

	// matrix = (YAW * PITCH) * ROLL
	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	// NOTE: Do not optimize this to reduce multiplies! optimizer bug will screw this up.
	matrix[0][1] = sr * sp * cy + cr * -sy;
	matrix[1][1] = sr * sp * sy + cr * cy;
	matrix[2][1] = sr * cp;
	matrix[0][2] = (cr * sp * cy + -sr * -sy);
	matrix[1][2] = (cr * sp * sy + -sr * cy);
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.f;
	matrix[1][3] = 0.f;
	matrix[2][3] = 0.f;
}

void AngleMatrix(const QAngle& angles, const Vector& position, matrix3x4_t& matrix)
{
	AngleMatrix(angles, matrix);
	MatrixSetColumn(position, 3, matrix);
}