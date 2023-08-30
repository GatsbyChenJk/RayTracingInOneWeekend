#include "Vec3.h"

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

inline void Vec3::normalize_amount()
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

inline Vec3 operator/(const Vec3& v,const float& t)
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
		e_item /= k;
	}
	return *this;
}

inline Vec3 GetNormalVec3(Vec3 v)
{
	return v / v.length();
}

inline Vec3 Vec3::normalize()
{

}

