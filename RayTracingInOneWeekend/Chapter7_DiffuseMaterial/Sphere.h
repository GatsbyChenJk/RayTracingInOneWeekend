#pragma once
#ifndef SPHEREH
#define SPHEREH
#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Vec3 center;
	float radius;

	Sphere(){}
	Sphere(Vec3 Center, float r) : center(Center), radius(r) {};
	virtual bool Hit(
		const Ray& r,
		float t_min,
		float t_max,
		hit_record& rec
	) const;
};

bool Sphere::Hit(const Ray& r,
	float t_min,
	float t_max,
	hit_record& rec) const
{
	// sphere equation:
	//t*t*dot(B,B) + 2*t*t*dot(B,A-C) + dot(A-C,A-C)-R*R = 0
	Vec3 oc = r.Origin() - center;
	float factor_a = dot(r.Direction(), r.Direction());
	float factor_b = dot(oc, r.Direction());
	float factor_c = dot(oc, oc) - radius * radius;
	//delta = b*b - ac
	float delta = factor_b * factor_b - factor_a * factor_c;
	//
	if (delta > 0)
	{
		float temp = (-factor_b - sqrt(factor_b * factor_b - factor_a * factor_c)) / factor_a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.PointWithParameter_t(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-factor_b - sqrt(factor_b * factor_b + factor_a * factor_c)) / factor_a;
		if (temp<t_max && temp>t_min)
		{
			rec.t = temp;
			rec.p = r.PointWithParameter_t(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;

}

#endif 
