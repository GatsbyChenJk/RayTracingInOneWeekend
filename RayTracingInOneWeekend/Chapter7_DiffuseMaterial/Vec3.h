#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>


class Vec3
{
public:
	float e[3];
	//init vec and set value
	Vec3() {}
	Vec3(float e0, float e1, float e2): e {e0,e1,e2}{}
	//get coordinate and rgb
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	//some operation
	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline Vec3& operator+=(const Vec3& v2);
	inline Vec3& operator-=(const Vec3& v2);
	inline Vec3& operator*=(const Vec3& v2);
	inline Vec3& operator/=(const Vec3& v2);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);

	//get vector info
	inline float length() const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	inline float length2() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void normalize();
	//inline Vec3 normalize();

};

inline std::istream& operator>>(std::istream& is, Vec3& t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& t)
{
	os << t.e[0] << "" << t.e[1] << "" << t.e[2];
	return os;
}

inline void Vec3::normalize()
{
	float unitFactor = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	for (auto& e_item : Vec3::e)
		e_item *= unitFactor;
}
//basic operation
inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2)
{
	return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
//operation with constant t
inline Vec3 operator*(const float& t, const Vec3& v)
{
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator/(const Vec3& v, const float& t)
{
	return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}
//other operation
inline float dot(const Vec3& v1, const Vec3& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2)
{
	return Vec3(
		(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])
	);
}

inline Vec3& Vec3::operator+=(const Vec3& v)
{
	for (int i = 0; i < 3;i++)
	{
		e[i] += v.e[i];
	}
	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& v)
{
	for (int i = 0; i < 3;i++)
	{
		e[i] *= v.e[i];
	}
	return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& v)
{
	for (int i = 0; i < 3;i++)
	{
		e[i] /= v.e[i];
	}
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v)
{
	for (int i = 0; i < 3;i++)
	{
		e[i] -= v.e[i];
	}
	return *this;
}

inline Vec3& Vec3::operator*=(const float t)
{
	for (auto& e_item : Vec3::e)
	{
		e_item *= t;
	}
	return *this;
}

inline Vec3& Vec3::operator/=(const float t)
{
	float k = 1.0 / t;

	for (auto& e_item : Vec3::e)
	{
		//k is the inverse of t
		//e_item /= k
		e_item *= k;
	}

	return *this;
}

inline Vec3 GetNormalVec3(Vec3 v)
{
	return v / v.length();
}

inline float clamp(float x, float min, float max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}
