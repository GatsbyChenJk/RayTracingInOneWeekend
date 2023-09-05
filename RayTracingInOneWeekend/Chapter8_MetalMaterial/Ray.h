#pragma once
#ifndef RAYH
#define RAYH
#include "Vec3.h"


class Ray
{
public:
	Vec3 A;
	Vec3 B;
	Ray(){}
	Ray(const Vec3& a, const Vec3& b):A(a),B(b){}
	Vec3 Origin() const
	{
		return A;
	}
	
	Vec3 Direction() const
	{
		return B;
	}

	Vec3 PointWithParameter_t(const float& t) const
	{
		return A + t * B;
	}
};

#endif
